#include "ot_coap.h"

LOG_MODULE_REGISTER(ot_coap, LOG_LEVEL_DBG);

static struct sockaddr_in6 multicast_local_addr = {
	.sin6_family = AF_INET6,
	.sin6_port = htons(COAP_PORT),
	.sin6_addr.s6_addr = { 
		0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 
	},
	.sin6_scope_id = 0U
};

struct tx_msgq {
    const char *const uri[2];
	struct sockaddr_in6 addr;
	uint8_t msg[PROTO_MSG_MAX_SIZE];
    uint8_t msg_size;
}_tx_msgq;

static struct k_msgq msg_queue;
static struct k_timer temperature_publicaion_timer;
static struct k_work temperature_publicaion_worker;

static char __aligned(4) tx_msgq_buffer[QUEUE_SIZE * sizeof(struct tx_msgq)];
static bool ot_connected = false;

static void publication_work_hanlder(struct k_work *work);
static void publication_timer_expiry_function(struct k_timer *timer_id);
static void on_light_request(uint8_t command);
static void on_config_request(uint8_t command);
static void on_thread_state_changed(__uint32_t flags, void *context);

void init_ot_coap()
{
	setup_chip_temp_sensor();

	coap_init(AF_INET6, NULL);

	k_msgq_init(&msg_queue, tx_msgq_buffer, sizeof(struct tx_msgq), QUEUE_SIZE);
	k_timer_init(&temperature_publicaion_timer, publication_timer_expiry_function, NULL);
	k_work_init(&temperature_publicaion_worker, publication_work_hanlder);
	
    ot_coap_init(&on_light_request, &on_config_request);
    openthread_set_state_changed_cb(on_thread_state_changed);
	openthread_start(openthread_get_default_context());
}

void publisher()
{
	while (true)
	{
		struct tx_msgq q_item;
		k_msgq_get(&msg_queue, &q_item, K_FOREVER);
		if (ot_connected)
		{
			coap_send(q_item.uri, q_item.addr, &q_item.msg[0], q_item.msg_size);
		}
	}
}

static void publication_work_hanlder(struct k_work *work)
{
	struct sensor_value die_temp = get_chip_temp();
	uint8_t msg_buffer[PROTO_MSG_MAX_SIZE] = {0};
	uint8_t msg_size = serialize_sensor_data(msg_buffer, &die_temp);
	LOG_INF("message size %d", msg_size);

	struct tx_msgq packet = {
		.addr = multicast_local_addr,
		.msg = {msg_buffer[0], msg_buffer[1],msg_buffer[2]},
		.msg_size = 3,
		.uri = TEMP_URI_PATH
	};
	k_msgq_put(&msg_queue, &packet, K_NO_WAIT);
}

static void publication_timer_expiry_function(struct k_timer *timer_id)
{
	k_work_submit(&temperature_publicaion_worker);	
}

static void on_light_request(uint8_t command)
{
	static uint8_t val;

	switch (command) {
	case THREAD_COAP_LIGHT_CMD_ON:
		dk_set_led_on(LIGHT_LED);
		val = 1;
		break;

	case THREAD_COAP_LIGHT_CMD_OFF:
		dk_set_led_off(LIGHT_LED);
		val = 0;
		break;

	case THREAD_COAP_LIGHT_CMD_TOGGLE:
		val = !val;
		dk_set_led(LIGHT_LED, val);
		break;

	default:
		break;
	}
}

static void on_config_request(uint8_t command)
{
	switch (command) {
	case THREAD_COAP_TEMP_PUBLISH_ON_CMD:
		dk_set_led_on(TEMP_PUB_LED);
		k_timer_start(&temperature_publicaion_timer, K_SECONDS(0), K_SECONDS(5));
		break;

	case THREAD_COAP_TEMP_PUBLISH_OFF_CMD:
		dk_set_led_off(TEMP_PUB_LED);
		k_timer_stop(&temperature_publicaion_timer);
		break;

	default:
		break;
	}
}

static void on_thread_state_changed(__uint32_t flags, void *context)
{
	struct openthread_context *ot_context = context;

	if (flags & OT_CHANGED_THREAD_ROLE) {
		switch (otThreadGetDeviceRole(ot_context->instance)) {
		case OT_DEVICE_ROLE_CHILD:
		case OT_DEVICE_ROLE_ROUTER:
		case OT_DEVICE_ROLE_LEADER:
			dk_set_led_on(OT_CONNECTION_LED);
			ot_connected = true;
			break;

		case OT_DEVICE_ROLE_DISABLED:
		case OT_DEVICE_ROLE_DETACHED:
		default:
			dk_set_led_off(OT_CONNECTION_LED);
			ot_connected = false;
			break;
		}
	}
}

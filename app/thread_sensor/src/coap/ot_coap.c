#include "ot_coap.h"

LOG_MODULE_REGISTER(ot_coap, LOG_LEVEL_DBG);

static const char *const temp_uri[] = { TEMP_URI_PATH, NULL };

static struct sockaddr_in6 multicast_local_addr = {
	.sin6_family = AF_INET6,
	.sin6_port = htons(COAP_PORT),
	.sin6_addr.s6_addr = { 
		0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 
	},
	.sin6_scope_id = 0U
};

bool state = false;

struct k_timer temperature_publicaion_timer;
struct k_work temperature_publicaion_worker;

static void publication_work_hanlder(struct k_work *work)
{
	state = !state;
	dk_set_led(LIGHT_LED, state);
	
	// Program crashes when trying to transmit the message, 
	// Need to tryout to use otCoapSendRequest to send a message instead, 
	// since you pass the OT instance to it, hoping it will make it 
	struct sensor_value die_temp = get_chip_temp();
	uint8_t msg_buffer[CHIP_TEMP_MSG_SIZE] = {0};
	gen_chip_temp_msg(msg_buffer, &die_temp);
	//coap_send(temp_uri, multicast_local_addr, msg_buffer, sizeof(msg_buffer));
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
		//k_work_submit(&temperature_publicaion_worker);
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

static void on_thread_state_changed(uint32_t flags, void *context)
{
	struct openthread_context *ot_context = context;

	if (flags & OT_CHANGED_THREAD_ROLE) {
		switch (otThreadGetDeviceRole(ot_context->instance)) {
		case OT_DEVICE_ROLE_CHILD:
		case OT_DEVICE_ROLE_ROUTER:
		case OT_DEVICE_ROLE_LEADER:
			dk_set_led_on(OT_CONNECTION_LED);
			break;

		case OT_DEVICE_ROLE_DISABLED:
		case OT_DEVICE_ROLE_DETACHED:
		default:
			dk_set_led_off(OT_CONNECTION_LED);
			break;
		}
	}
}

void init_ot_coap()
{
	setup_chip_temp_sensor();

	coap_init(AF_INET6, NULL);

	k_timer_init(&temperature_publicaion_timer, publication_timer_expiry_function, NULL);
	k_work_init(&temperature_publicaion_worker, publication_work_hanlder);

	
    ot_coap_init(&on_light_request, &on_config_request);
    openthread_set_state_changed_cb(on_thread_state_changed);
	openthread_start(openthread_get_default_context());
}

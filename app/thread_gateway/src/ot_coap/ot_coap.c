#include "ot_coap.h"

LOG_MODULE_REGISTER(ot_coap, LOG_LEVEL_DBG);

static const char *const light_uri[] = { LIGHT_URI_PATH, NULL };
static const char *const config_uri[] = { CONFIG_URI_PATH, NULL };

static struct sockaddr_in6 multicast_local_addr = {
	.sin6_family = AF_INET6,
	.sin6_port = htons(COAP_PORT),
	.sin6_addr.s6_addr = { 
		0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 
	},
	.sin6_scope_id = 0U
};

static void on_temp_publish(OtData msg)
{
	char addr_buffer[38] = {};
	otIp6AddressToString(&msg.addr_sender, &addr_buffer[0], 38);
	LOG_INF("Msg received from %s with size %d", log_strdup(addr_buffer), msg.msg_size);
	deserialize_sensor_data_to_console(&msg.msg, msg.msg_size);
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
    coap_init(AF_INET6, NULL);

    int ret = ot_coap_init(&on_temp_publish);
	if (ret) {
		LOG_ERR("Could not initialize OpenThread CoAP");
		return;
	}

    openthread_set_state_changed_cb(on_thread_state_changed);
	openthread_start(openthread_get_default_context());
}

void light_set_state(bool state)
{
    uint8_t command = state ? THREAD_COAP_LIGHT_CMD_ON : THREAD_COAP_LIGHT_CMD_OFF;
    coap_send(light_uri, multicast_local_addr, command);
}

void light_toggle()
{
	coap_send(light_uri, multicast_local_addr, THREAD_COAP_LIGHT_CMD_TOGGLE);
}

void temp_monitor_set_state(bool state)
{
	uint8_t command = state ? THREAD_COAP_TEMP_PUBLISH_ON_CMD : THREAD_COAP_TEMP_PUBLISH_OFF_CMD;
	int ret = coap_send(config_uri, multicast_local_addr, command);
	LOG_DBG("Transmitted msg with return code %d", ret);
}

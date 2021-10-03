#include "ot_coap.h"

LOG_MODULE_REGISTER(ot_coap, LOG_LEVEL_DBG);

static bool ot_coap_connected = false;

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

static void on_thread_state_changed(uint32_t flags, void *context)
{
	struct openthread_context *ot_context = context;

	if (flags & OT_CHANGED_THREAD_ROLE) {
		switch (otThreadGetDeviceRole(ot_context->instance)) {
		case OT_DEVICE_ROLE_CHILD:
		case OT_DEVICE_ROLE_ROUTER:
		case OT_DEVICE_ROLE_LEADER:
			dk_set_led_on(OT_CONNECTION_LED);
			ot_coap_connected = true;
			break;

		case OT_DEVICE_ROLE_DISABLED:
		case OT_DEVICE_ROLE_DETACHED:
		default:
			dk_set_led_off(OT_CONNECTION_LED);
			ot_coap_connected = false;
			break;
		}
	}
}

void init_ot_coap()
{

	coap_init(AF_INET6, NULL);
	
    ot_coap_init();
    openthread_set_state_changed_cb(on_thread_state_changed);
	openthread_start(openthread_get_default_context());
}

bool get_ot_connection_status(){
	return ot_coap_connected;
}

void test_send()
{
	uint8_t msg_buffer[3] = {0};
	coap_send(temp_uri, multicast_local_addr, msg_buffer, sizeof(msg_buffer));
	//new_send();
}
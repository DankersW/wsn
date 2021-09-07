#include "ot_coap.h"

LOG_MODULE_REGISTER(ot_coap, LOG_LEVEL_DBG);

static void on_light_request(uint8_t command)
{
	static uint8_t val;

	switch (command) {
	case 0:
		dk_set_led_on(LIGHT_LED);
		val = 1;
		break;

	case 1:
		dk_set_led_off(LIGHT_LED);
		val = 0;
		break;

	case 2:
		val = !val;
		dk_set_led(LIGHT_LED, val);
		break;

	default:
		break;
	}
}

static void deactivate_provisionig(void)
{
    LOG_ERR("Deactivate prov called");
}


static void on_thread_state_changed(uint32_t flags, void *context)
{
	struct openthread_context *ot_context = context;

	if (flags & OT_CHANGED_THREAD_ROLE) {
		switch (otThreadGetDeviceRole(ot_context->instance)) {
		case OT_DEVICE_ROLE_CHILD:
		case OT_DEVICE_ROLE_ROUTER:
		case OT_DEVICE_ROLE_LEADER:
			//dk_set_led_on(OT_CONNECTION_LED);
			dk_set_led_on(DK_LED3);
			break;

		case OT_DEVICE_ROLE_DISABLED:
		case OT_DEVICE_ROLE_DETACHED:
		default:
			//dk_set_led_off(OT_CONNECTION_LED);
			dk_set_led_off(DK_LED3);
			deactivate_provisionig();
			break;
		}
	}
}



void init_ot_coap()
{
    coap_init(AF_INET6, NULL);

    int ret = ot_coap_init(&deactivate_provisionig, &on_light_request);
	if (ret) {
		LOG_ERR("Could not initialize OpenThread CoAP");
		return;
	}

    openthread_set_state_changed_cb(on_thread_state_changed);
	openthread_start(openthread_get_default_context());
}
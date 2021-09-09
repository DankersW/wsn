#include <zephyr.h>
#include <dk_buttons_and_leds.h>
#include <logging/log.h>
#include <net/openthread.h>
#include <openthread/thread.h>
#include <net/coap_utils.h>

#include "ot_coap_utils.h"

LOG_MODULE_REGISTER(coap_server, LOG_LEVEL_DBG);

#define OT_CONNECTION_LED DK_LED1
#define LIGHT_LED DK_LED4
#define TEMP_PUB_LED DK_LED2

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

//static const struct device *chip_dev;

/*
static int get_chip_temp(struct sensor_value *rsp)
{
    sensor_sample_fetch(chip_dev);

	int err = sensor_channel_get(chip_dev, SENSOR_CHAN_DIE_TEMP, rsp);
	if (err) 
    {
		printk("Error getting temperature sensor data (%d)\n", err);
	}
	return err;
}
*/

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
	uint8_t send_command;
	switch (command) {
	case THREAD_COAP_TEMP_PUBLISH_ON_CMD:
		dk_set_led_on(TEMP_PUB_LED);
		send_command = 10;
		coap_send(temp_uri, multicast_local_addr, send_command);
		break;

	case THREAD_COAP_TEMP_PUBLISH_OFF_CMD:
		dk_set_led_off(TEMP_PUB_LED);
		send_command = 11;
		coap_send(temp_uri, multicast_local_addr, send_command);
		break;

	default:
		break;
	}
}

static void on_button_changed(uint32_t button_state, uint32_t has_changed)
{
	uint32_t buttons = button_state & has_changed;

	if (buttons & DK_BTN1_MSK) {
		on_light_request(THREAD_COAP_LIGHT_CMD_TOGGLE);
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

/*
static void init_chip_temp()
{
	chip_dev = device_get_binding(DT_PROP(DT_NODELABEL(temp), label));

	if (chip_dev == NULL) 
    {
		LOG_ERR("Could not initiate temperature sensor");
	} 
    else 
    {
		LOG_INF("Temperature sensor (%s) initiated", chip_dev->name);
	}
}
*/

void main(void)
{
	int ret;

	LOG_INF("Start CoAP-server sample");

	ret = ot_coap_init(&on_light_request, &on_config_request);
	if (ret) {
		LOG_ERR("Could not initialize OpenThread CoAP");
		goto end;
	}

	ret = dk_leds_init();
	if (ret) {
		LOG_ERR("Could not initialize leds, err code: %d", ret);
		goto end;
	}

	ret = dk_buttons_init(on_button_changed);
	if (ret) {
		LOG_ERR("Cannot init buttons (error: %d)", ret);
		goto end;
	}

	//init_chip_temp();

	openthread_set_state_changed_cb(on_thread_state_changed);
	openthread_start(openthread_get_default_context());

end:
	return;
}

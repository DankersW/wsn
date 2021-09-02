

#include <zephyr.h>
#include <dk_buttons_and_leds.h>
#include <logging/log.h>
#include <ram_pwrdn.h>
#include <device.h>

#include "coap_client_utils.h"

LOG_MODULE_REGISTER(coap_client, LOG_LEVEL_DBG);

#define CONSOLE_LABEL DT_LABEL(DT_CHOSEN(zephyr_console))

#define OT_CONNECTION_LED DK_LED1
#define BLE_CONNECTION_LED DK_LED2
#define MTD_SED_LED DK_LED3

static void on_ot_connect(struct k_work *item)
{
	ARG_UNUSED(item);

	dk_set_led_on(OT_CONNECTION_LED);
}

static void on_ot_disconnect(struct k_work *item)
{
	ARG_UNUSED(item);

	dk_set_led_off(OT_CONNECTION_LED);
}

static void on_mtd_mode_toggle(uint32_t med)
{
#if IS_ENABLED(CONFIG_DEVICE_POWER_MANAGEMENT)
	const struct device *cons = device_get_binding(CONSOLE_LABEL);

	if (med) {
		device_set_power_state(cons, DEVICE_PM_ACTIVE_STATE,
				       NULL, NULL);
	} else {
		device_set_power_state(cons, DEVICE_PM_OFF_STATE,
				       NULL, NULL);
	}
#endif
	dk_set_led(MTD_SED_LED, med);
}

static void on_button_changed(uint32_t button_state, uint32_t has_changed)
{
	uint32_t buttons = button_state & has_changed;

	if (buttons & DK_BTN1_MSK) {
		coap_client_toggle_mesh_lights();
		
	}

	if (buttons & DK_BTN2_MSK) {
		coap_client_toggle_one_light();
	}

	if (buttons & DK_BTN3_MSK) {
		coap_client_toggle_minimal_sleepy_end_device();
	}

	if (buttons & DK_BTN4_MSK) {
		coap_client_send_provisioning_request();
	}
}

void _main(void)
{
	int ret;

	LOG_INF("Start CoAP-client sample");

	if (IS_ENABLED(CONFIG_RAM_POWER_DOWN_LIBRARY)) {
		power_down_unused_ram();
	}

	ret = dk_buttons_init(on_button_changed);
	if (ret) {
		LOG_ERR("Cannot init buttons (error: %d)", ret);
		return;
	}

	ret = dk_leds_init();
	if (ret) {
		LOG_ERR("Cannot init leds, (error: %d)", ret);
		return;
	}

	coap_client_utils_init(on_ot_connect, on_ot_disconnect, on_mtd_mode_toggle);
}







#include <zephyr.h>

#include "cli_shell.h"

void main(void)
{
	_main();
	//enable_shell();
}


#include <zephyr.h>
#include <dk_buttons_and_leds.h>
#include <logging/log.h>

#include "cli_shell.h"
#include "coap_client_utils.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

#define OT_CONNECTION_LED DK_LED1

static void on_button_changed(uint32_t button_state, uint32_t has_changed)
{
	uint32_t buttons = button_state & has_changed;

	if (buttons & DK_BTN1_MSK) {
		coap_client_toggle_mesh_lights();
	}	
}

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
}


void main(void)
{

	int ret = dk_buttons_init(on_button_changed);
	if (ret) {
		LOG_ERR("Cannot init buttons (error: %d)", ret);
		return;
	}

	ret = dk_leds_init();
	if (ret) {
		LOG_ERR("Cannot init leds, (error: %d)", ret);
		return;
	}

	dk_set_led_on(3);
	coap_client_utils_init(on_ot_connect, on_ot_disconnect, on_mtd_mode_toggle);

	enable_shell();
}
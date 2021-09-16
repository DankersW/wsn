#include <zephyr.h>
#include <sys/printk.h>
#include <usb/usb_device.h>
#include <logging/log.h>
#include <dk_buttons_and_leds.h>

#define LOG_MODULE_NAME usb_print_example
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

static void on_button_changed(uint32_t button_state, uint32_t has_changed)
{
	uint32_t buttons = button_state & has_changed;

	if (buttons & DK_BTN1_MSK) {
		printk("hello\n");
	}
}

void main(void)
{
	int ret = dk_buttons_init(on_button_changed);
	if (ret) {
		LOG_ERR("Cannot init buttons (error: %d)", ret);
		return;
	}

	if (usb_enable(NULL)) {
		return;
	}
}

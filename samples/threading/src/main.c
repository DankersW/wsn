#include <zephyr.h>
#include <sys/printk.h>
#include <usb/usb_device.h>
#include <logging/log.h>
#include <dk_buttons_and_leds.h>

#define LOG_MODULE_NAME usb_print_example
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

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

#include <zephyr.h>
#include <sys/printk.h>
#include <usb/usb_device.h>
#include <logging/log.h>
#include <dk_buttons_and_leds.h>

#define LOG_MODULE_NAME usb_print_example
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

bool timer_active = false;

struct k_timer my_timer;

void my_expiry_function(struct k_timer *timer_id)
{
	LOG_INF("timer called");
}

void toggle_timer()
{
	timer_active = !timer_active;
	if (timer_active)
	{
		LOG_INF("stating timer");
		k_timer_start(&my_timer, K_SECONDS(0), K_SECONDS(5));
	}
	else
	{
		LOG_INF("Stopping timer");
		k_timer_stop(&my_timer);
	}
}

static void on_button_changed(uint32_t button_state, uint32_t has_changed)
{
	uint32_t buttons = button_state & has_changed;

	if (buttons & DK_BTN1_MSK) {
		toggle_timer();	
	}
}

void main(void)
{
	int ret = dk_buttons_init(on_button_changed);
	if (ret) {
		LOG_ERR("Cannot init buttons (error: %d)", ret);
		return;
	}

	k_timer_init(&my_timer, my_expiry_function, NULL);

	if (usb_enable(NULL)) {
		return;
	}
}

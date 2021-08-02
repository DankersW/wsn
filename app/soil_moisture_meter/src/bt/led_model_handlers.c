#include "led_model_handlers.h"

void _led_transition_start(struct led_ctx *led, struct led_ctx led_ctx[])
{
	int led_idx = led - &led_ctx[0];
	dk_set_led(led_idx, true);
	k_delayed_work_submit(&led->work, K_MSEC(led->remaining));
	led->remaining = 0;
}
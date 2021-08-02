#include "model_handler.h"

void led_transition_start__(struct led_ctx *led, struct led_ctx led_ctx[])
{
	int led_idx = led - &led_ctx[0];

	// As long as the transition is in progress, the onoff state is "on":
	dk_set_led(led_idx, true);
	k_delayed_work_submit(&led->work, K_MSEC(led->remaining));
	led->remaining = 0;
}
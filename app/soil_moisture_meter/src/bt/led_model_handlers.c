#include "led_model_handlers.h"

void handler_led_transition_start(struct led_ctx *led, struct led_ctx led_ctx[])
{
	int led_idx = led - &led_ctx[0];
	dk_set_led(led_idx, true);
	k_delayed_work_submit(&led->work, K_MSEC(led->remaining));
	led->remaining = 0;
}

void handler_led_status(struct led_ctx *led, struct bt_mesh_onoff_status *status)
{
	status->remaining_time = k_delayed_work_remaining_get(&led->work) + led->remaining;
	status->target_on_off = led->value;
	status->present_on_off = led->value || status->remaining_time;
}
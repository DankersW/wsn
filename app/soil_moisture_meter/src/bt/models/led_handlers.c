#include "led_handlers.h"

static void led_transition_start(struct led_ctx *led, struct led_ctx led_ctx[])
{
	int led_idx = led - &led_ctx[0];
	//set_led1(true);
	//dk_set_led(led_idx, true);
	k_delayed_work_submit(&led->work, K_MSEC(led->remaining));
	led->remaining = 0;
}

static void led_status(struct led_ctx *led, struct bt_mesh_onoff_status *status)
{
	status->remaining_time = k_delayed_work_remaining_get(&led->work) + led->remaining;
	status->target_on_off = led->value;
	status->present_on_off = led->value || status->remaining_time;
}

void handler_led_work(struct k_work *work, struct led_ctx led_ctx[])
{
	struct led_ctx *led = CONTAINER_OF(work, struct led_ctx, work.work);
	int led_idx = led - &led_ctx[0];

	if (led->remaining) 
	{
		led_transition_start(led, led_ctx);
	} 
	else 
	{
		set_led1(led->value);
		struct bt_mesh_onoff_status status;
		led_status(led, &status);
		bt_mesh_onoff_srv_pub(&led->srv, NULL, &status);
	}
}

void handler_led_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, struct bt_mesh_onoff_status *rsp)
{
	struct led_ctx *led = CONTAINER_OF(srv, struct led_ctx, srv);
	led_status(led, rsp);
}

void handler_led_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, const struct bt_mesh_onoff_set *set,
 					 struct bt_mesh_onoff_status *rsp, struct led_ctx led_ctx[])
{
	struct led_ctx *led = CONTAINER_OF(srv, struct led_ctx, srv);
	int led_idx = led - &led_ctx[0];

	if (set->on_off != led->value)
	{
		led->value = set->on_off;
		led->remaining = set->transition->time;

		if (set->transition->delay > 0) 
		{
			k_delayed_work_submit(&led->work, K_MSEC(set->transition->delay));
		} 
		else if (set->transition->time > 0) 
		{
			led_transition_start(led, led_ctx);
		} 
		else 
		{
			set_led1(set->on_off);
			//dk_set_led(led_idx, set->on_off);
		}
	}

	if (rsp) {
		led_status(led, rsp);
	}
}

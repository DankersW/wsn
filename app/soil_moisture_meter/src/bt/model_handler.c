#include "model_handler.h"

/*
struct led_ctx dummy_led_ctx[4] = {
	[0 ... 3] = {}
};
*/
struct led_ctx led_ctx[4] = {
	[0 ... 3] = {
		.srv = BT_MESH_ONOFF_SRV_INIT(&onoff_handlers),
	}
};

void led_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, struct bt_mesh_onoff_status *rsp)
{
	struct led_ctx *led = CONTAINER_OF(srv, struct led_ctx, srv);
	led_status(led, rsp);
}

void led_work(struct k_work *work)
{
	struct led_ctx *led = CONTAINER_OF(work, struct led_ctx, work.work);
	//int led_idx = led - &dummy_led_ctx[0];
	int led_idx = led - &led_ctx[0];

	if (led->remaining) {
		led_transition_start(led);
	} else {
		dk_set_led(led_idx, led->value);

		// Publish the new value at the end of the transition
		struct bt_mesh_onoff_status status;

		led_status(led, &status);
		bt_mesh_onoff_srv_pub(&led->srv, NULL, &status);
	}
}

void led_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, const struct bt_mesh_onoff_set *set,
		     struct bt_mesh_onoff_status *rsp)
{
	struct led_ctx *led = CONTAINER_OF(srv, struct led_ctx, srv);
	int led_idx = led - &led_ctx[0];

	if (set->on_off == led->value) {
		goto respond;
	}

	led->value = set->on_off;
	led->remaining = set->transition->time;

	if (set->transition->delay > 0) {
		k_delayed_work_submit(&led->work, K_MSEC(set->transition->delay));
	} else if (set->transition->time > 0) {
		led_transition_start(led);
	} else {
		dk_set_led(led_idx, set->on_off);
	}

respond:
	if (rsp) {
		led_status(led, rsp);
	}
}

void led_transition_start(struct led_ctx *led)
{
	//int led_idx = led - &dummy_led_ctx[0];
	int led_idx = led - &led_ctx[0];

	// As long as the transition is in progress, the onoff state is "on":
	dk_set_led(led_idx, true);
	k_delayed_work_submit(&led->work, K_MSEC(led->remaining));
	led->remaining = 0;
}

void led_status(struct led_ctx *led, struct bt_mesh_onoff_status *status)
{
	status->remaining_time = k_delayed_work_remaining_get(&led->work) + led->remaining;
	status->target_on_off = led->value;
	// As long as the transition is in progress, the onoff state is "on":
	status->present_on_off = led->value || status->remaining_time;
}





void attention_blink(struct k_work *work)
{
	static int idx;
	const uint8_t pattern[] = {
		BIT(0) | BIT(1),
		BIT(1) | BIT(2),
		BIT(2) | BIT(3),
		BIT(3) | BIT(0),
	};
	dk_set_leds(pattern[idx++ % ARRAY_SIZE(pattern)]);
	k_delayed_work_submit(&attention_blink_work, K_MSEC(30));
}

void attention_on(struct bt_mesh_model *mod)
{
	k_delayed_work_submit(&attention_blink_work, K_NO_WAIT);
}

void attention_off(struct bt_mesh_model *mod)
{
	k_delayed_work_cancel(&attention_blink_work);
	dk_set_leds(DK_NO_LEDS_MSK);
}













/*
const struct bt_mesh_comp *model_handler_init(void)
{
	k_delayed_work_init(&attention_blink_work, attention_blink);

	for (int i = 0; i < ARRAY_SIZE(led_ctx); ++i) {
		k_delayed_work_init(&led_ctx[i].work, led_work);
	}

	//return &comp;
}
*/
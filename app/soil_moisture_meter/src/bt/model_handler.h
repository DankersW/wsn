#ifndef MODEL_HANDLER_H
#define MODEL_HANDLER_H

#include <bluetooth/mesh.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <dk_buttons_and_leds.h>

struct led_ctx {
	struct bt_mesh_onoff_srv srv;
	struct k_delayed_work work;
	uint32_t remaining;
	bool value;
};

struct k_delayed_work attention_blink_work;


void led_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, struct bt_mesh_onoff_status *rsp);
void led_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, const struct bt_mesh_onoff_set *set, struct bt_mesh_onoff_status *rsp);

void led_status(struct led_ctx *led, struct bt_mesh_onoff_status *status);
void led_work(struct k_work *work);
void led_transition_start(struct led_ctx *led);

void attention_off(struct bt_mesh_model *mod);
void attention_on(struct bt_mesh_model *mod);
void attention_blink(struct k_work *work);

static const struct bt_mesh_onoff_srv_handlers onoff_handlers = {
	.set = led_set,
	.get = led_get,
};

#endif // MODEL_HANDLER_H

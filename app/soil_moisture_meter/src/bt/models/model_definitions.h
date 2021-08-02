#ifndef MODEL_DEFINITION_H
#define MODEL_DEFINITION_H

#include <bluetooth/mesh.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <dk_buttons_and_leds.h>

#include "bt_types.h"
#include "led_handlers.h"
#include "attention_handlers.h"


const struct bt_mesh_comp *model_handler_init(void);

void led_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, const struct bt_mesh_onoff_set *set, struct bt_mesh_onoff_status *rsp);
void led_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, struct bt_mesh_onoff_status *rsp);
void led_work(struct k_work *work);

static const struct bt_mesh_onoff_srv_handlers onoff_handlers = {
	.set = led_set,
	.get = led_get,
};

static const struct bt_mesh_health_srv_cb health_srv_cb = {
	.attn_on = attention_on,
	.attn_off = attention_off
};

#endif // MODEL_DEFINITION_H


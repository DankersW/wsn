#ifndef MODEL_HANDLER_H
#define MODEL_HANDLER_H

#include <bluetooth/mesh.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <dk_buttons_and_leds.h>

#include "bt_types.h"

void handler_led_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, struct bt_mesh_onoff_status *rsp);
void handler_led_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, const struct bt_mesh_onoff_set *set, 
                     struct bt_mesh_onoff_status *rsp, struct led_ctx led_ctx[]);
void handler_led_work(struct k_work *work, struct led_ctx led_ctx[]);

void attention_blink(struct k_work *work);
void attention_on(struct bt_mesh_model *mod);
void attention_off(struct bt_mesh_model *mod);

struct k_delayed_work *get_attention_blink_work();


#endif // MODEL_HANDLER_H

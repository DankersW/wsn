#ifndef LED_HANDLER_H
#define LED_HANDLER_H

#include <bluetooth/mesh.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <dk_buttons_and_leds.h>

#include "bt_types.h"

void handler_led_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, struct bt_mesh_onoff_status *rsp);
void handler_led_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, const struct bt_mesh_onoff_set *set, 
                     struct bt_mesh_onoff_status *rsp, struct led_ctx led_ctx[]);
void handler_led_work(struct k_work *work, struct led_ctx led_ctx[]);

#endif // LED_HANDLER_H

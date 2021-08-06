#ifndef LED_HANDLER_H
#define LED_HANDLER_H

#include "bt_types.h"
#include "led_driver.h"


void led_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, struct bt_mesh_onoff_status *rsp);
void led_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, const struct bt_mesh_onoff_set *set, struct bt_mesh_onoff_status *rsp);
void led_work(struct k_work *work);

#endif // LED_HANDLER_H

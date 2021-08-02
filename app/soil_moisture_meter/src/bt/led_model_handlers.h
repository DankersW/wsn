#ifndef MODEL_HANDLER_H
#define MODEL_HANDLER_H

#include <bluetooth/mesh.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <dk_buttons_and_leds.h>

#include "bt_types.h"

void handler_led_transition_start(struct led_ctx *led, struct led_ctx led_ctx[]);
void handler_led_status(struct led_ctx *led, struct bt_mesh_onoff_status *status);

#endif // MODEL_HANDLER_H

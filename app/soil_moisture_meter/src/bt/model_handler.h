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

void led_transition_start__(struct led_ctx *led, struct led_ctx led_ctx[]);

#endif // MODEL_HANDLER_H

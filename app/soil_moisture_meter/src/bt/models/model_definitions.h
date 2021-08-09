#ifndef MODEL_DEFINITION_H
#define MODEL_DEFINITION_H

#include <bluetooth/mesh/models.h>
#include <logging/log.h>

#include "bt_types.h"
#include "led_handlers.h"
#include "attention_handlers.h"
#include "sensor_handlers.h"


const struct bt_mesh_comp *model_handler_init(void);

static const struct bt_mesh_onoff_srv_handlers onoff_handlers = {
	.set = led_set,
	.get = led_get,
};

static const struct bt_mesh_health_srv_cb health_srv_cb = {
	.attn_on = attention_on,
	.attn_off = attention_off
};

#endif // MODEL_DEFINITION_H


#ifndef BT_TYPES_H
#define BT_TYPES_H

#include <kernel.h>
#include <bluetooth/mesh/models.h>

struct led_ctx {
	struct bt_mesh_onoff_srv srv;
	struct k_delayed_work work;
	uint32_t remaining;
	bool value;
};

#endif // BT_TYPES_H
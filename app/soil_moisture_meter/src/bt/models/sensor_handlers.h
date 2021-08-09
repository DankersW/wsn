#ifndef SENSOR_HANDLERS_H
#define SENSOR_HANDLERS_H

#include <bluetooth/mesh/models.h>


#include "chip_temp.h"

void sensors_init(void);
int _chip_temp_get(struct bt_mesh_sensor *sensor, struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp);

#endif // SENSOR_HANDLERS_H
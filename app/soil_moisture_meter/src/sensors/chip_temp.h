#ifndef CHIP_TEMP_H
#define CHIP_TEMP_H

#include <bluetooth/mesh/models.h>
#include <logging/log.h>

void setup_chip_temp_sensor(void);
int get_chip_temp(struct bt_mesh_sensor *sensor, struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp);

#endif // CHIP_TEMP_H
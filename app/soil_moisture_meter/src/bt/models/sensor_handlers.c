#include "sensor_handlers.h"

void sensors_init(void)
{
    setup_chip_temp_sensor();
}

int _chip_temp_get(struct bt_mesh_sensor *sensor, struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp)
{
    get_chip_temp(sensor, ctx, rsp);
}

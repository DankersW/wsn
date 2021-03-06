#include "sensor_handlers.h"

void sensors_init(void)
{
    setup_chip_temp_sensor();
}

int chip_temp_get(struct bt_mesh_sensor *sensor, struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp)
{
    return get_chip_temp(rsp);
}

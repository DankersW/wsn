#include "chip_temp.h"

LOG_MODULE_REGISTER(chip_temp_sensor, LOG_LEVEL_DBG);

void setup_chip_temp_sensor(void)
{
    LOG_INF("Sensor setup");
}

int get_chip_temp(struct bt_mesh_sensor *sensor, struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp)
{
    LOG_INF("GET VALUE");
    return 0;
}
#include "proto_deserializer.h"

#define LOG_MODULE_NAME proto_deserializer
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

void deserialize_sensor_data_to_console(uint8_t *msg, uint8_t size)
{
    LOG_INF("hi: size %d", size);
}
#include "proto_deserializer.h"

#define LOG_MODULE_NAME proto_deserializer
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

void deserialize_sensor_data_to_console(uint8_t *msg, uint8_t size)
{
    wsn_SensorData message = wsn_SensorData_init_zero;
    pb_istream_t stream = pb_istream_from_buffer(msg, size);
    if (!pb_decode(&stream, wsn_SensorData_fields, &message))
    {
        printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
        return;
    }
    LOG_INF("Sensor ID: %s Temperature: %d Humidity: %d", log_strdup(message.sensor_id), (int)message.temperature, (int)message.humidity);
}
#ifndef PROTO_SERIALIZER_H
#define PROTO_SERIALIZER_H

#include <drivers/sensor.h>

// TODO: some file with application info

uint8_t serialize_sensor_data_msg(uint8_t *msg_buf, struct sensor_value *tempature_data);

#endif // PROTO_SERIALIZER_H
#ifndef PROTO_SERIALIZER_H
#define PROTO_SERIALIZER_H

#include <drivers/sensor.h>
#include <pb_encode.h>
#include <pb_decode.h>

#include "definitions.h"
#include "wsn.pb.h"

// TODO: some file with application definitions

uint8_t serialize_sensor_data(uint8_t *msg_buf, struct sensor_value *tempature_data);

#endif // PROTO_SERIALIZER_H
#ifndef PROTO_DESERIALIZER_H
#define PROTO_DESERIALIZER_H

#include <zephyr.h>
#include <logging/log.h>
#include <pb_encode.h>
#include <pb_decode.h>

#include "wsn.pb.h"

void deserialize_sensor_data_to_console(uint8_t *msg, uint8_t size);

#endif //PROTO_DESERIALIZER_H
#ifndef PROTO_DESERIALIZER_H
#define PROTO_DESERIALIZER_H

#include <zephyr.h>
#include <logging/log.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include <string.h>

#include "wsn.pb.h"

void deserialize_sensor_data(uint8_t *msg, uint8_t size, char *buffer);
void protobuf2str(uint8_t *data, size_t size, char *buffer);

#endif //PROTO_DESERIALIZER_H
#ifndef COAP_MESSAGE_DEFINITION_H
#define COAP_MESSAGE_DEFINITION_H

#include <drivers/sensor.h>

#include "ot_definitions.h"

#define CHIP_TEMP_MSG_SIZE 3

void gen_chip_temp_msg(uint8_t *msg_buf, struct sensor_value *tempature_data);

#endif // COAP_MESSAGE_DEFINITION_H
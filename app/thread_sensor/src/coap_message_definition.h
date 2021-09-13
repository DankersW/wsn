#ifndef COAP_MESSAGE_DEFINITION_H
#define COAP_MESSAGE_DEFINITION_H

#include <drivers/sensor.h>

#include "ot_definitions.h"

void gen_chip_temp_msg(uint8_t *msg_buf, struct sensor_value tempature_data);

#endif // COAP_MESSAGE_DEFINITION_H
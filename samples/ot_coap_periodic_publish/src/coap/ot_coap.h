#ifndef OT_COAP_H
#define OT_COAP_H

#include <zephyr.h>
#include <logging/log.h>
#include <net/openthread.h>
#include <openthread/thread.h>
#include <net/coap_utils.h>
#include <drivers/sensor.h>

#include "ot_definitions.h"
#include "ot_coap_utils.h"

void init_ot_coap();
bool get_ot_connection_status();
void test_send(uint8_t counter);

#endif // OT_COAP_H
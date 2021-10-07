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
#include "die_temp.h"
#include "coap_message_definition.h"

#define QUEUE_SIZE 10

void init_ot_coap();
void publisher();

#endif // OT_COAP_H
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

void init_ot_coap();

#endif // OT_COAP_H
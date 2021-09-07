#ifndef OT_COAP_H
#define OT_COAP_H

#include <zephyr.h>
#include <net/openthread.h>
#include <openthread/thread.h>
#include <dk_buttons_and_leds.h>

#include "ot_coap_utils.h"

#define OT_CONNECTION_LED DK_LED1
#define LIGHT_LED DK_LED2

void init_ot_coap();

#endif // OT_COAP_H
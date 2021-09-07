#ifndef OT_COAP_H
#define OT_COAP_H


#include <zephyr.h>
#include <net/openthread.h>
#include <openthread/thread.h>
#include <dk_buttons_and_leds.h>

#define OT_CONNECTION_LED DK_LED1

void init_ot_coap();

#endif // OT_COAP_H
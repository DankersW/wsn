#ifndef OT_H
#define OT_H

#include <zephyr.h>
#include <dk_buttons_and_leds.h>

#include "coap_client_utils.h"

#define OT_CONNECTION_LED DK_LED1

void init_ot();

#endif // OT_H
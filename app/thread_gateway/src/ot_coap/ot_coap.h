#ifndef OT_COAP_H
#define OT_COAP_H

#include <zephyr.h>
#include <net/openthread.h>
#include <openthread/thread.h>
#include <dk_buttons_and_leds.h>

#include "ot_definitions.h"
#include "ot_coap_utils.h"
#include "proto_deserializer.h"

#define LIGHT_LED DK_LED2

void init_ot_coap();

void light_set_state(bool state);
void light_toggle();

void temp_monitor_set_state(bool state);
void set_raw_monitor(bool state);

#endif // OT_COAP_H
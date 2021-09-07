#ifndef OT_COAP_H
#define OT_COAP_H

#include <zephyr.h>
#include <net/openthread.h>
#include <openthread/thread.h>
#include <dk_buttons_and_leds.h>

#include "ot_coap_utils.h"

#define OT_CONNECTION_LED DK_LED1
#define LIGHT_LED DK_LED2

#define LIGHT_URI_PATH "light"
#define COAP_PORT 5683

const struct sockaddr_in6 multicast_local_addr = {
	.sin6_family = AF_INET6,
	.sin6_port = htons(COAP_PORT),
	.sin6_addr.s6_addr = { 
		0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 
	},
	.sin6_scope_id = 0U
};

const char *const *light_option[] = { LIGHT_URI_PATH, NULL };

void init_ot_coap();

void light_set_state(bool state);
void light_toggle();

#endif // OT_COAP_H
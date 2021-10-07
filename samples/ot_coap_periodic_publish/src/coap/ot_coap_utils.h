#ifndef __OT_COAP_UTILS_H__
#define __OT_COAP_UTILS_H__

#include <stdint.h>
#include <logging/log.h>
#include <net/net_pkt.h>
#include <net/net_l2.h>
#include <net/openthread.h>
#include <openthread/coap.h>
#include <openthread/ip6.h>
#include <openthread/message.h>
#include <openthread/thread.h>
#include <net/coap_utils.h>
#include <net/socket.h>

#include "ot_definitions.h"

int ot_coap_init();
int coap_send(const char *const uri[], struct sockaddr_in6 addr, uint8_t *message, uint8_t size);

int test_trans();
int new_send();

#endif

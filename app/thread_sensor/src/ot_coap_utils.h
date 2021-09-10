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

typedef void (*light_request_callback_t)(uint8_t cmd);
typedef void (*config_request_callback_t)(uint8_t cmd);

int ot_coap_init(light_request_callback_t on_light_request, config_request_callback_t on_config_request);
int coap_send(const char *const uri[], struct sockaddr_in6 addr, uint8_t message);

#endif

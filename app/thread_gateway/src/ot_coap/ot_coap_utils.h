#ifndef OT_COAP_UTILS_H
#define OT_COAP_UTILS_H

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

#include "ot_definitions.h"

typedef void (*temp_publish_callback_t)(OtData temperature_data);

int ot_coap_init(temp_publish_callback_t on_temp_publish);

int coap_send(const char *const uri[], struct sockaddr_in6 addr, uint8_t message);

#endif // OT_COAP_UTILS_H
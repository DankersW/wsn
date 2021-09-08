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

#define COAP_PORT 5683
#define PROVISIONING_URI_PATH "provisioning"
#define LIGHT_URI_PATH "light"

/*
enum light_command {
	THREAD_COAP_UTILS_LIGHT_CMD_OFF = '0',
	THREAD_COAP_UTILS_LIGHT_CMD_ON = '1',
	THREAD_COAP_UTILS_LIGHT_CMD_TOGGLE = '2'
};
*/

typedef void (*light_request_callback_t)(uint8_t cmd);
typedef void (*provisioning_request_callback_t)();

int ot_coap_init(provisioning_request_callback_t on_provisioning_request, light_request_callback_t on_light_request);

int coap_send(const char *const uri[], struct sockaddr_in6 addr, uint8_t message);

#endif // OT_COAP_UTILS_H
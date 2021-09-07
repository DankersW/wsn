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

#define COAP_PORT 5683
#define PROVISIONING_URI_PATH "provisioning"
#define LIGHT_URI_PATH "light"

enum light_command {
	THREAD_COAP_UTILS_LIGHT_CMD_OFF = '0',
	THREAD_COAP_UTILS_LIGHT_CMD_ON = '1',
	THREAD_COAP_UTILS_LIGHT_CMD_TOGGLE = '2'
};

typedef void (*light_request_callback_t)(uint8_t cmd);
typedef void (*provisioning_request_callback_t)();

int ot_coap_init(provisioning_request_callback_t on_provisioning_request, light_request_callback_t on_light_request);
void ot_coap_activate_provisioning(void);
void ot_coap_deactivate_provisioning(void);
bool ot_coap_is_provisioning_active(void);

#endif // OT_COAP_UTILS_H
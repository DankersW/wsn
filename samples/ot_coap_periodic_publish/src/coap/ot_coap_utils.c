#include "ot_coap_utils.h"

LOG_MODULE_REGISTER(ot_coap_utils, LOG_LEVEL_DBG);

struct server_context {
	struct otInstance *ot;
};

static struct server_context srv_context = {
	.ot = NULL,
};

static void coap_default_handler(void *context, otMessage *message, const otMessageInfo *message_info)
{
	ARG_UNUSED(context);
	ARG_UNUSED(message);
	ARG_UNUSED(message_info);

	LOG_INF("Received CoAP message that does not match any request or resource");
}

int ot_coap_init()
{
	otError error;

	srv_context.ot = openthread_get_default_instance();
	if (!srv_context.ot) {
		LOG_ERR("There is no valid OpenThread instance");
		error = OT_ERROR_FAILED;
		goto end;
	}

	otCoapSetDefaultHandler(srv_context.ot, coap_default_handler, NULL);

	error = otCoapStart(srv_context.ot, COAP_PORT);
	if (error != OT_ERROR_NONE) {
		LOG_ERR("Failed to start OT CoAP. Error: %d", error);
		goto end;
	}

end:
	return error == OT_ERROR_NONE ? 0 : 1;
}

int coap_send(const char *const uri[], struct sockaddr_in6 addr, uint8_t *message, uint8_t size)
{
	return coap_send_request(COAP_METHOD_PUT, (const struct sockaddr *)&addr, uri, message, size, NULL);
}

#include "ot_coap_utils.h"

LOG_MODULE_REGISTER(ot_coap_utils, LOG_LEVEL_DBG);

struct server_context {
	struct otInstance *ot;
	temp_publish_callback_t on_temp_publish;
};

static struct server_context srv_context = {
	.ot = NULL,
	.on_temp_publish = NULL,
};

static otCoapResource temp_monitor_resource = {
	.mUriPath = TEMP_URI_PATH,
	.mHandler = NULL,
	.mContext = NULL,
	.mNext = NULL,
};

static void temp_publish_handler(void *context, otMessage *message, const otMessageInfo *message_info)
{
	uint8_t command;

	ARG_UNUSED(context);

	if (otCoapMessageGetType(message) != OT_COAP_TYPE_NON_CONFIRMABLE) {
		LOG_ERR("Temp pub handler - Unexpected type of message");
		goto end;
	}

	if (otCoapMessageGetCode(message) != OT_COAP_CODE_PUT) {
		LOG_ERR("Temp pub handler - Unexpected CoAP code");
		goto end;
	}

	if (otMessageRead(message, otMessageGetOffset(message), &command, 1) !=1) {
		LOG_ERR("Temp pub handler - Missing command");
		goto end;
	}

	LOG_WRN("ip: %d", message_info->mPeerAddr);

	srv_context.on_temp_publish(message);

end:
	return;
}

static void coap_default_handler(void *context, otMessage *message, const otMessageInfo *message_info)
{
	ARG_UNUSED(context);
	ARG_UNUSED(message);
	ARG_UNUSED(message_info);

	LOG_INF("Received CoAP message that does not match any request or resource");
}

int ot_coap_init(temp_publish_callback_t on_temp_publish)
{
	otError error;

	srv_context.on_temp_publish = on_temp_publish;

	srv_context.ot = openthread_get_default_instance();
	if (!srv_context.ot) {
		LOG_ERR("There is no valid OpenThread instance");
		error = OT_ERROR_FAILED;
		goto end;
	}

	temp_monitor_resource.mContext = srv_context.ot;
	temp_monitor_resource.mHandler = temp_publish_handler;

	otCoapSetDefaultHandler(srv_context.ot, coap_default_handler, NULL);
	otCoapAddResource(srv_context.ot, &temp_monitor_resource);

	error = otCoapStart(srv_context.ot, COAP_PORT);
	if (error != OT_ERROR_NONE) {
		LOG_ERR("Failed to start OT CoAP. Error: %d", error);
		goto end;
	}

end:
	return error == OT_ERROR_NONE ? 0 : 1;
}

int coap_send(const char *const uri[], struct sockaddr_in6 addr, uint8_t message)
{
	return coap_send_request(COAP_METHOD_PUT, (const struct sockaddr *)&addr, uri, &message, sizeof(message), NULL);
}

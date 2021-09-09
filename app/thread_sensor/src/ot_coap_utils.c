/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

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

#include <net/coap_utils.h>
#include <logging/log.h>
#include <net/openthread.h>
#include <net/socket.h>
#include <openthread/thread.h>

#include "ot_coap_utils.h"

LOG_MODULE_REGISTER(ot_coap_utils, LOG_LEVEL_DBG);

struct server_context {
	struct otInstance *ot;
	light_request_callback_t on_light_request;
	config_request_callback_t on_config_request;
};

static struct server_context srv_context = {
	.ot = NULL,
	.on_light_request = NULL,
	.on_config_request = NULL,
};

static otCoapResource light_resource = {
	.mUriPath = LIGHT_URI_PATH,
	.mHandler = NULL,
	.mContext = NULL,
	.mNext = NULL,
};

static otCoapResource config_resource = {
	.mUriPath = CONFIG_URI_PATH,
	.mHandler = NULL,
	.mContext = NULL,
	.mNext = NULL,
};

static void light_request_handler(void *context, otMessage *message, const otMessageInfo *message_info)
{
	uint8_t command;

	ARG_UNUSED(context);

	if (otCoapMessageGetType(message) != OT_COAP_TYPE_NON_CONFIRMABLE) {
		LOG_ERR("Light handler - Unexpected type of message");
		goto end;
	}

	if (otCoapMessageGetCode(message) != OT_COAP_CODE_PUT) {
		LOG_ERR("Light handler - Unexpected CoAP code");
		goto end;
	}

	if (otMessageRead(message, otMessageGetOffset(message), &command, 1) !=1) {
		LOG_ERR("Light handler - Missing light command");
		goto end;
	}

	LOG_INF("Received light request: %c", command);

	srv_context.on_light_request(command);

end:
	return;
}

static void config_request_handler(void *context, otMessage *message, const otMessageInfo *message_info)
{
	uint8_t command;

	ARG_UNUSED(context);

	if (otCoapMessageGetType(message) != OT_COAP_TYPE_NON_CONFIRMABLE) {
		LOG_ERR("Config handler - Unexpected type of message");
		goto end;
	}

	if (otCoapMessageGetCode(message) != OT_COAP_CODE_PUT) {
		LOG_ERR("Config handler - Unexpected CoAP code");
		goto end;
	}

	if (otMessageRead(message, otMessageGetOffset(message), &command, 1) !=1) {
		LOG_ERR("Config handler - Missing config command");
		goto end;
	}

	LOG_INF("Received Config request: %c", command);

	srv_context.on_config_request(command);

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

int ot_coap_init(light_request_callback_t on_light_request, config_request_callback_t on_config_request)
{

	coap_init(AF_INET6, NULL);


	otError error;

	srv_context.on_light_request = on_light_request;
	srv_context.on_config_request = on_config_request;

	srv_context.ot = openthread_get_default_instance();
	if (!srv_context.ot) {
		LOG_ERR("There is no valid OpenThread instance");
		error = OT_ERROR_FAILED;
		goto end;
	}

	light_resource.mContext = srv_context.ot;
	light_resource.mHandler = light_request_handler;

	config_resource.mContext = srv_context.ot;
	config_resource.mHandler = config_request_handler;

	otCoapSetDefaultHandler(srv_context.ot, coap_default_handler, NULL);
	otCoapAddResource(srv_context.ot, &light_resource);
	otCoapAddResource(srv_context.ot, &config_resource);

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
	//return 0;
}
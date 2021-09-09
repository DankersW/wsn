/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef __OT_COAP_UTILS_H__
#define __OT_COAP_UTILS_H__

#define COAP_PORT 5683

enum ot_thread_commands {
	THREAD_COAP_LIGHT_CMD_OFF = '0',
	THREAD_COAP_LIGHT_CMD_ON = '1',
	THREAD_COAP_LIGHT_CMD_TOGGLE = '2',
	THREAD_COAP_TEMP_PUBLISH_ON_CMD = '3',
	THREAD_COAP_TEMP_PUBLISH_OFF_CMD = '4'
};

#define LIGHT_URI_PATH "light"

/**@brief Type definition of the function used to handle light resource change.
 */
typedef void (*light_request_callback_t)(uint8_t cmd);
typedef void (*temp_request_callback_t)(uint8_t cmd);

int ot_coap_init(light_request_callback_t on_light_request, temp_request_callback_t on_temp_request);

#endif

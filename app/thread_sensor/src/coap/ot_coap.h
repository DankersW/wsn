#ifndef OT_COAP_H
#define OT_COAP_H

#include <zephyr.h>
#include <logging/log.h>
#include <net/openthread.h>
#include <openthread/thread.h>
#include <net/coap_utils.h>
#include <drivers/sensor.h>

#include "ot_definitions.h"
#include "ot_coap_utils.h"
#include "die_temp.h"
#include "coap_message_definition.h"

extern bool ot_connected;

#define QUEUE_SIZE 10
extern struct msg_q_data_type {
    bool state;
	bool something;
	int8_t counter;
};
extern char msg_q_buffer[QUEUE_SIZE * sizeof(struct msg_q_data_type)];
extern struct k_msgq msg_queue;

void init_ot_coap();

#endif // OT_COAP_H
#include <zephyr.h>
#include <dk_buttons_and_leds.h>
#include <logging/log.h>
#include <sys/printk.h>
#include <usb/usb_device.h> // USB printing

#include "ot_coap.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

#define QUEUE_SIZE 10

bool state = false;
uint8_t msg_counter = 0;

struct k_timer temperature_publicaion_timer;
struct k_work temperature_publicaion_worker;

struct msg_q_data_type {
    bool state;
	bool something;
	int8_t counter;
};

char msg_q_buffer[QUEUE_SIZE * sizeof(struct msg_q_data_type)];
struct k_msgq msg_queue;

static void publication_work_hanlder(struct k_work *work);
static void publication_timer_expiry_function(struct k_timer *timer_id);
static void on_button_changed(__uint32_t button_state, __uint32_t has_changed);

void setup()
{
	dk_leds_init();
	dk_buttons_init(on_button_changed);
	k_timer_init(&temperature_publicaion_timer, publication_timer_expiry_function, NULL);
	k_work_init(&temperature_publicaion_worker, publication_work_hanlder);
	k_msgq_init(&msg_queue, msg_q_buffer, sizeof(struct msg_q_data_type), QUEUE_SIZE);
	init_ot_coap();
}

void main(void)
{	
	setup();

	usb_enable(NULL);

	while (true)
	{
		struct msg_q_data_type data;
		k_msgq_get(&msg_queue, &data, K_FOREVER);
		if (get_ot_connection_status())
		{
			test_send(data.counter);	
		}
	}
}

static void on_button_changed(__uint32_t button_state, __uint32_t has_changed)
{
	int32_t buttons = button_state & has_changed;
	if (buttons & DK_BTN1_MSK) {
		k_timer_start(&temperature_publicaion_timer, K_SECONDS(0), K_SECONDS(5));
	}
}

static void publication_work_hanlder(struct k_work *work)
{
	struct msg_q_data_type data = {
		.state = true,
		.something = false,
		.counter = ++msg_counter,
	};
	k_msgq_put(&msg_queue, &data, K_NO_WAIT);
}

static void publication_timer_expiry_function(struct k_timer *timer_id)
{
	k_work_submit(&temperature_publicaion_worker);	
}

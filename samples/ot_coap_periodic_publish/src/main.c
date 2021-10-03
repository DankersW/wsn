#include <zephyr.h>
#include <dk_buttons_and_leds.h>
#include <logging/log.h>
#include <sys/printk.h>
#include <usb/usb_device.h>

// USB printing
#include <usb/usb_device.h>

#include "ot_coap.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

bool state = false;

struct k_timer temperature_publicaion_timer;
struct k_work temperature_publicaion_worker;

static void publication_work_hanlder(struct k_work *work);
static void publication_timer_expiry_function(struct k_timer *timer_id);
static void on_button_changed(uint32_t button_state, uint32_t has_changed);



struct data_item_type {
    bool state;
	bool something;
};

char __aligned(4) my_msgq_buffer[10 * sizeof(struct data_item_type)];
struct k_msgq my_msgq;


void main(void)
{
	dk_leds_init();

	int ret = dk_buttons_init(on_button_changed);
	if (ret) {
		LOG_ERR("Cannot init buttons (error: %d)", ret);
		return;
	}

	k_timer_init(&temperature_publicaion_timer, publication_timer_expiry_function, NULL);
	k_work_init(&temperature_publicaion_worker, publication_work_hanlder);

	k_msgq_init(&my_msgq, my_msgq_buffer, sizeof(struct data_item_type), 10);

	init_ot_coap();

	usb_enable(NULL);

	while (true)
	{
		struct data_item_type data;
		k_msgq_get(&my_msgq, &data, K_FOREVER);
		if (get_ot_connection_status())
		{
			test_send();	
		}
		
	}
	

	// trying to use a busy loop for sending, using a queue that we fill from the timer
}

static void on_button_changed(uint32_t button_state, uint32_t has_changed)
{
	uint32_t buttons = button_state & has_changed;

	if (buttons & DK_BTN1_MSK) {
		k_timer_start(&temperature_publicaion_timer, K_SECONDS(0), K_SECONDS(5));
	}
}

static void publication_work_hanlder(struct k_work *work)
{
	state = !state;
	dk_set_led(LIGHT_LED, state);
	
	// Program crashes when trying to transmit the message, 
	// Need to tryout to use otCoapSendRequest to send a message instead, 
	// since you pass the OT instance to it, hoping it will make it 
	//struct sensor_value die_temp = get_chip_temp();

	struct data_item_type data = {
		.state = true,
		.something = false,
	};

	int status = k_msgq_put(&my_msgq, &data, K_NO_WAIT);
	LOG_INF("state %d, connected %d, status %d", state, get_ot_connection_status(), status);
}

static void publication_timer_expiry_function(struct k_timer *timer_id)
{
	k_work_submit(&temperature_publicaion_worker);	
}
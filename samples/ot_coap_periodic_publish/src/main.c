#include <zephyr.h>
#include <dk_buttons_and_leds.h>
#include <logging/log.h>

// USB printing
#include <usb/usb_device.h>

#include "ot_coap.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

bool state = false;

struct k_timer temperature_publicaion_timer;
struct k_work temperature_publicaion_worker;

static void publication_work_hanlder(struct k_work *work)
{
	state = !state;
	dk_set_led(LIGHT_LED, state);
	
	// Program crashes when trying to transmit the message, 
	// Need to tryout to use otCoapSendRequest to send a message instead, 
	// since you pass the OT instance to it, hoping it will make it 
	//struct sensor_value die_temp = get_chip_temp();
	uint8_t msg_buffer[3] = {0};

	LOG_INF("state %d", state);
	
	//coap_send(temp_uri, multicast_local_addr, msg_buffer, sizeof(msg_buffer));
}

static void publication_timer_expiry_function(struct k_timer *timer_id)
{
	k_work_submit(&temperature_publicaion_worker);	
}

void main(void)
{
	dk_leds_init();

	k_timer_init(&temperature_publicaion_timer, publication_timer_expiry_function, NULL);
	k_work_init(&temperature_publicaion_worker, publication_work_hanlder);

	init_ot_coap();

	usb_enable(NULL);

	k_timer_start(&temperature_publicaion_timer, K_SECONDS(0), K_SECONDS(5));	
}

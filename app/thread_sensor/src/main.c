#include <zephyr.h>
#include <dk_buttons_and_leds.h>
#include <logging/log.h>

#include "ot_coap.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);



//static const struct device *chip_dev;

/*
static int get_chip_temp(struct sensor_value *rsp)
{
    sensor_sample_fetch(chip_dev);

	int err = sensor_channel_get(chip_dev, SENSOR_CHAN_DIE_TEMP, rsp);
	if (err) 
    {
		printk("Error getting temperature sensor data (%d)\n", err);
	}
	return err;
}
*/


/*
static void init_chip_temp()
{
	chip_dev = device_get_binding(DT_PROP(DT_NODELABEL(temp), label));

	if (chip_dev == NULL) 
    {
		LOG_ERR("Could not initiate temperature sensor");
	} 
    else 
    {
		LOG_INF("Temperature sensor (%s) initiated", chip_dev->name);
	}
}
*/

void main(void)
{
	dk_leds_init();

	init_ot_coap();
}

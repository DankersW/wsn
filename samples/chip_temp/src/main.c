#include <zephyr.h>
#include <sys/printk.h>
#include <usb/usb_device.h>
#include <logging/log.h>
#include <drivers/sensor.h>

#define LOG_MODULE_NAME usb_print_example
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

static const struct device *chip_dev;

void setup_chip_temp_sensor(void)
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


int get_chip_temp()
{
	sensor_sample_fetch(chip_dev);

	struct sensor_value temp_val;
	
	int err = sensor_channel_get(chip_dev, SENSOR_CHAN_DIE_TEMP, &temp_val);
	if (err) 
    {
		printk("Error getting temperature sensor data (%d)\n", err);
	}
	double die_temp = (temp_val.val1 + temp_val.val2) * (10^(-6));
	printk("val1: %f \n", die_temp);

	printk("v1: %d - v2: %d\n", temp_val.val1, temp_val.val2);
	float t = temp_val.val1 / 1.5;
	printk("%f \n", t);
	return err;
}

void main(void)
{
	if (usb_enable(NULL)) {
		return;
	}

	k_sleep(K_SECONDS(3));
	
	setup_chip_temp_sensor();
	while (1) {
		k_sleep(K_SECONDS(2));
		get_chip_temp();
	}
}

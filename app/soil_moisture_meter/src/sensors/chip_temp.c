#include "chip_temp.h"

LOG_MODULE_REGISTER(chip_temp_sensor, LOG_LEVEL_DBG);

static const struct device *chip_dev;

void setup_chip_temp_sensor(void)
{
    LOG_INF("Sensor setup");
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

int get_chip_temp(struct sensor_value *rsp)
{
    sensor_sample_fetch(chip_dev);

	int err = sensor_channel_get(chip_dev, SENSOR_CHAN_DIE_TEMP, rsp);
	if (err) 
    {
		printk("Error getting temperature sensor data (%d)\n", err);
	}
	return err;
}
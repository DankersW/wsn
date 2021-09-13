#include "die_temp.h"

LOG_MODULE_REGISTER(die_temp, LOG_LEVEL_DBG);

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

struct sensor_value get_chip_temp()
{
	sensor_sample_fetch(chip_dev);

	struct sensor_value die_temp;
	
	int err = sensor_channel_get(chip_dev, SENSOR_CHAN_DIE_TEMP, &die_temp);
	if (err) 
    {
		LOG_ERR("Error getting temperature sensor data (%d)\n", err);
	}
	return die_temp;
}

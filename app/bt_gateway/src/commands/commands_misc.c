#include "commands_misc.h"

void blink(uint8_t blinks, uint16_t sleep)
{
	const struct device *dev = device_get_binding(LED0);
	if (dev == NULL) {
		return;
	}

	int ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret < 0) {
		return;
	}

    bool state = true;
	for (size_t i = 0; i < blinks*2; ++i)
    {
        gpio_pin_set(dev, PIN, (int)state);
		state = !state;
        k_msleep(sleep);
    }
    gpio_pin_set(dev, PIN, 0);
}

char * get_version()
{
	return PROJECT_VER;
}
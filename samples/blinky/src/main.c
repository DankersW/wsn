#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <random/rand32.h>
#include "gpio_definitions.h"

#define SLEEP_TIME_MS   500

const struct device *rgb_led_gpio[3];

enum rbg_colors {RED, GREEN, BLUE};

void setup_led()
{
	rgb_led_gpio[RED] = device_get_binding(LED_R);
	gpio_pin_configure(rgb_led_gpio[RED], PIN_R, GPIO_OUTPUT_ACTIVE | FLAGS_R);
	gpio_pin_set(rgb_led_gpio[RED], PIN_R, 0);
}

void random_blinking_gpio(uint8_t state)
{
	gpio_pin_set(rgb_led_gpio[RED], PIN_R, state % 2);
}

void main(void)
{
	setup_led();
	bool state = false;
	while (1) {
		state = !state;
		gpio_pin_set(rgb_led_gpio[RED], PIN_R, state);
		k_msleep(SLEEP_TIME_MS);
	}
}

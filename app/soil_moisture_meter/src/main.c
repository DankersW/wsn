#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <random/rand32.h>
#include "gpio_definitions.h"

#define SLEEP_TIME_MS   250

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
	while (1) {
		uint8_t random_number = sys_rand32_get() % 2;
		random_blinking_gpio(random_number);
		k_msleep(SLEEP_TIME_MS);
	}
}

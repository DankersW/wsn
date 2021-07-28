#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <random/rand32.h>
#include "gpio_definitions.h"

#define SLEEP_TIME_MS   250

const struct device *rgb_led_gpio[3];

enum rbg_colors {RED, GREEN, BLUE};

void setup_rgb_led()
{
	rgb_led_gpio[RED] = device_get_binding(LED_R);
	rgb_led_gpio[GREEN] = device_get_binding(LED_G);
	rgb_led_gpio[BLUE] = device_get_binding(LED_B);
	gpio_pin_configure(rgb_led_gpio[RED], PIN_R, GPIO_OUTPUT_ACTIVE | FLAGS_R);
	gpio_pin_configure(rgb_led_gpio[GREEN], PIN_G, GPIO_OUTPUT_ACTIVE | FLAGS_G);
	gpio_pin_configure(rgb_led_gpio[BLUE], PIN_B, GPIO_OUTPUT_ACTIVE | FLAGS_B);
	gpio_pin_set(rgb_led_gpio[RED], PIN_R, 0);
	gpio_pin_set(rgb_led_gpio[GREEN], PIN_G, 0);
	gpio_pin_set(rgb_led_gpio[BLUE], PIN_B, 0);
}

void random_blinking_gpio(uint8_t state)
{
	switch (state)
	{
	case 0 ... 1:
		gpio_pin_set(rgb_led_gpio[RED], PIN_R, state % 2);
		break;
	case 2 ... 3:
		gpio_pin_set(rgb_led_gpio[GREEN], PIN_G, state % 2);
		break;
	case 4 ... 5:
		gpio_pin_set(rgb_led_gpio[BLUE], PIN_B, state % 2);
		break;
	default:
		break;
	}
}

void main(void)
{
	setup_rgb_led();
	while (1) {
		uint8_t random_number = sys_rand32_get() % 6;
		random_blinking_gpio(random_number);
		k_msleep(SLEEP_TIME_MS);
	}
}

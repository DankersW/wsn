#include "led_driver.h"

const struct device *rgb_led_gpio[3];

void setup_leds(void)
{
    rgb_led_gpio[RED] = device_get_binding(LED_R);
	gpio_pin_configure(rgb_led_gpio[RED], PIN_R, GPIO_OUTPUT_ACTIVE | FLAGS_R);
	gpio_pin_set(rgb_led_gpio[RED], PIN_R, 0);
}

void random_blinking()
{
    uint8_t random_number = sys_rand32_get() % 2;
    gpio_pin_set(rgb_led_gpio[RED], PIN_R, random_number % 2);
}
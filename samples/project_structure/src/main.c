#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

#define SLEEP_TIME_MS   500

#define LED_R_NODE DT_PATH(leds, led_1)
#define LED_R	DT_GPIO_LABEL(LED_R_NODE, gpios)
#define PIN_R	DT_GPIO_PIN(LED_R_NODE, gpios)
#define FLAGS_R	DT_GPIO_FLAGS(LED_R_NODE, gpios)

void main(void)
{
	const struct device *led = device_get_binding(LED_R);
	gpio_pin_configure(led, PIN_R, GPIO_OUTPUT_ACTIVE | FLAGS_R);
	gpio_pin_set(led, PIN_R, 0);

	while (1) {
		gpio_pin_toggle(led, PIN_R);
		k_msleep(SLEEP_TIME_MS);
	}
}

#include "led_driver.h"

const struct device *rgb_led2[3];
const struct device *led1;

void setup_leds(void)
{
    rgb_led2[RED] = device_get_binding(LED2_R);
	gpio_pin_configure(rgb_led2[RED], LED2_PIN_R, GPIO_OUTPUT_ACTIVE | LED2_FLAG_R);
	gpio_pin_set(rgb_led2[RED], LED2_PIN_R, 0);
    rgb_led2[GREEN] = device_get_binding(LED2_G);
	gpio_pin_configure(rgb_led2[GREEN], LED2_PIN_G, GPIO_OUTPUT_ACTIVE | LED2_FLAG_G);
	gpio_pin_set(rgb_led2[GREEN], LED2_PIN_G, 0);
    rgb_led2[BLUE] = device_get_binding(LED2_B);
	gpio_pin_configure(rgb_led2[BLUE], LED2_PIN_B, GPIO_OUTPUT_ACTIVE | LED2_FLAG_B);
	gpio_pin_set(rgb_led2[BLUE], LED2_PIN_B, 0);
    led1 = device_get_binding(LED1);
	gpio_pin_configure(led1, LED1_PIN, GPIO_OUTPUT_ACTIVE | LED1_FLAG);
	gpio_pin_set(led1, LED1_PIN, 0);
}

void random_state_led2()
{
    uint8_t random_number = sys_rand32_get() % 6;
    switch (random_number)
	{
	case 0 ... 1:
		gpio_pin_set(rgb_led2[RED], LED2_PIN_R, random_number % 2);
		break;
	case 2 ... 3:
		gpio_pin_set(rgb_led2[GREEN], LED2_PIN_G, random_number % 2);
		break;
	case 4 ... 5:
		gpio_pin_set(rgb_led2[BLUE], LED2_PIN_B, random_number % 2);
		break;
	default:
		break;
	}
}

void set_led1(bool state)
{
    gpio_pin_set(led1, LED1_PIN, state);
}

void blink_rgb(uint8_t led)
{
    switch (led)
    {
    case RED:
        gpio_pin_toggle(rgb_led2[RED], LED2_PIN_R);
        break;

    case GREEN:
        gpio_pin_toggle(rgb_led2[GREEN], LED2_PIN_G);
        break;

    case BLUE:
        gpio_pin_toggle(rgb_led2[BLUE], LED2_PIN_B);
        break;
    
    default:
        break;
    }
}
#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <devicetree.h>
#include <drivers/gpio.h>
#include <random/rand32.h>
#include <logging/log.h>

#include "gpio_definitions.h"

enum rbg_colors {RED, GREEN, BLUE};

void setup_leds(void);
void setup_led1(void);
void setup_led_rgb(void);

void blink_rgb(enum rbg_colors led);
void set_led1(bool state);

void random_state_led2(void);
//bool is_initialized(const struct device *led);

#endif // LED_DRIVER_H

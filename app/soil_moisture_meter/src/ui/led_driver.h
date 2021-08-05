#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <devicetree.h>
#include <drivers/gpio.h>
#include <random/rand32.h>

#include "gpio_definitions.h"

enum rbg_colors {RED, GREEN, BLUE};

void setup_leds(void);

void random_blinking();


#endif // LED_DRIVER_H

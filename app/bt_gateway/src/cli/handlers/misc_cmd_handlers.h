#ifndef MISC_CMD_HANDLERS_H
#define MISC_CMD_HANDLERS_H

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)

#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN	DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS	DT_GPIO_FLAGS(LED0_NODE, gpios)

// TODO: fix so that we can get version from CMAKE correctly
#define PROJECT_VER "@PROJECT_VERSION@"

void blink(uint8_t blinks, uint16_t sleep);
char * get_version();

#endif // MISC_CMD_HANDLERS_H
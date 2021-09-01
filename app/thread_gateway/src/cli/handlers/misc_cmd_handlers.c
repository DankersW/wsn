#include "misc_cmd_handlers.h"

int cmd_misc_ping(const struct shell *shell, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	shell_print(shell, "pong");
	return 0;
}

int cmd_misc_blinky(const struct shell *shell, size_t argc, char **argv)
{
	uint8_t blinks = 5;
	uint16_t sleep = 250;
	shell_print(shell, "Blinking %d times with an sleep period of %d ms", blinks, sleep);
	blink(blinks, sleep);
	return 0;
}

int cmd_misc_version(const struct shell *shell, size_t argc, char **argv)
{
	char *version = get_version();
	shell_print(shell, "version: %s", version);
	return 0;
}

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
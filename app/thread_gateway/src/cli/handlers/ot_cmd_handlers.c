#include "ot_cmd_handlers.h"

#define OT_CONNECTION_LED DK_LED1
#define MTD_SED_LED DK_LED3

static void on_ot_connect(struct k_work *item)
{
	ARG_UNUSED(item);

	//dk_set_led_on(OT_CONNECTION_LED);
}

static void on_ot_disconnect(struct k_work *item)
{
	ARG_UNUSED(item);

	//dk_set_led_off(OT_CONNECTION_LED);
}

static void on_mtd_mode_toggle(uint32_t med)
{
	//dk_set_led(MTD_SED_LED, med);
}

int cmd_ot_start(const struct shell *shell, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	//int ret = dk_leds_init();
	//if (ret) {
	//	return 1;
	//}

	//coap_client_utils_init(on_ot_connect, on_ot_disconnect, on_mtd_mode_toggle);

	shell_print(shell, "started");
	return 0;
}
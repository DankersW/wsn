#include "ot_cmd_handlers.h"

//#define OT_CONNECTION_LED DK_LED1
//#define MTD_SED_LED DK_LED3



int cmd_ot_start(const struct shell *shell, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	//int ret = dk_leds_init();
	//if (ret) {
	//	return 1;
	//}

	//coap_client_utils_init(on_ot_connect, on_ot_disconnect, on_mtd_mode_toggle);
	coap_client_toggle_mesh_lights();


	shell_print(shell, "started");
	return 0;
}
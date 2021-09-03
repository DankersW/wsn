#include "ot.h"

static void on_ot_connect(struct k_work *item)
{
	ARG_UNUSED(item);
	dk_set_led_on(OT_CONNECTION_LED);
}

static void on_ot_disconnect(struct k_work *item)
{
	ARG_UNUSED(item);
	dk_set_led_off(OT_CONNECTION_LED);
}

static void on_mtd_mode_toggle(uint32_t med)
{
}

void init_ot()
{
    coap_client_utils_init(on_ot_connect, on_ot_disconnect, on_mtd_mode_toggle);
}

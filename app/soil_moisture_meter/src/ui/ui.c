#include "ui.h"

LOG_MODULE_REGISTER(ui, LOG_LEVEL_DBG);

void enable_ui(void)
{
    setup_leds();
    LOG_INF("UI enabled");
}

void show_heartbeat()
{
    random_state_led2();
}
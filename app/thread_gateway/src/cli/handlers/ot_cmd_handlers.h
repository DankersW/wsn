#ifndef OT_CMD_HANDLERS_H
#define OT_CMD_HANDLERS_H

#include <zephyr.h>
#include <shell/shell.h>
#include <dk_buttons_and_leds.h>

#include "coap_client_utils.h"


int cmd_ot_start(const struct shell *shell, size_t argc, char **argv);

#endif // OT_CMD_HANDLERS_H
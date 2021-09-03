#ifndef OT_CMD_HANDLERS_H
#define OT_CMD_HANDLERS_H

#include <zephyr.h>
#include <shell/shell.h>

#include "ot.h"


int cmd_ot_multi_light_toggle(const struct shell *shell, size_t argc, char **argv);

#endif // OT_CMD_HANDLERS_H
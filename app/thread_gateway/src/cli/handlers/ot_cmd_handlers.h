#ifndef OT_CMD_HANDLERS_H
#define OT_CMD_HANDLERS_H

#include <zephyr.h>
#include <shell/shell.h>

#include "ot_coap.h"


int cmd_ot_multi_light_toggle(const struct shell *shell, size_t argc, char **argv);
int cmd_ot_multi_light_on(const struct shell *shell, size_t argc, char **argv);
int cmd_ot_multi_light_off(const struct shell *shell, size_t argc, char **argv);

int cmd_ot_monitor_temp_on(const struct shell *shell, size_t argc, char **argv);
int cmd_ot_monitor_temp_off(const struct shell *shell, size_t argc, char **argv);
int cmd_ot_monitor_decode_on(const struct shell *shell, size_t argc, char **argv);
int cmd_ot_monitor_decode_off(const struct shell *shell, size_t argc, char **argv);

#endif // OT_CMD_HANDLERS_H
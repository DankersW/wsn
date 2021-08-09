#ifndef COMMANDS_BT_H
#define COMMANDS_BT_H

#include <zephyr.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <sys/printk.h>

bool enable_bluetooth();
void beacon_scanning();
void scan_cb(const bt_addr_le_t *addr, int8_t rssi, uint8_t adv_type, struct net_buf_simple *buf);

#endif // COMMANDS_BT_H
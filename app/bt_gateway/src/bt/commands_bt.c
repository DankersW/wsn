#include "commands_bt.h"

bool enable_bluetooth()
{
	int err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return false;
	}
	return true;
}

void scan_cb(const bt_addr_le_t *addr, int8_t rssi, uint8_t adv_type, struct net_buf_simple *buf)
{
	uint8_t uuid_size = 6;
	for (size_t i=0; i<uuid_size; ++i)
	{
		printk("%02x", addr->a.val[i]);
		if (i==(uuid_size-1)) { printk("\n"); }
		else { printk(":"); }
	}
}

void beacon_scanning()
{
	struct bt_le_scan_param scan_param = {
		.type       = BT_HCI_LE_SCAN_PASSIVE,
		.options    = BT_LE_SCAN_OPT_NONE,
		.interval   = 0x0010,
		.window     = 0x0010,
	};
	
	int err = bt_le_scan_start(&scan_param, scan_cb);
	if (err) {
		printk("Starting scanning failed (err %d)\n", err);
		return;
	}
	k_sleep(K_SECONDS(5));
	bt_le_scan_stop();
}


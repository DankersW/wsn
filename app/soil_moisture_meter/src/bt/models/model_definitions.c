#include "model_definitions.h"

LOG_MODULE_REGISTER(bt_model_def, LOG_LEVEL_DBG);

BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);


////// TEST

static const struct device *dev;

static int chip_temp_get(struct bt_mesh_sensor *sensor, struct bt_mesh_msg_ctx *ctx, struct sensor_value *rsp)
{
	//_chip_temp_get(sensor, ctx, rsp);
	sensor_sample_fetch(dev);

	int err = sensor_channel_get(dev, SENSOR_CHAN_DIE_TEMP, rsp);

	if (err) {
		printk("Error getting temperature sensor data (%d)\n", err);
	}
	return err;
}

static struct bt_mesh_sensor chip_temp = {
	.type = &bt_mesh_sensor_present_dev_op_temp,
	.get = _chip_temp_get,
};

static struct bt_mesh_sensor *const sensors[] = {
	&chip_temp
};

static struct bt_mesh_sensor_srv sensor_srv = BT_MESH_SENSOR_SRV_INIT(sensors, ARRAY_SIZE(sensors));

/////// END TESt


struct led_ctx led_ctx = {
	.srv = BT_MESH_ONOFF_SRV_INIT(&onoff_handlers),
};

static struct bt_mesh_health_srv health_srv = {
	.cb = &health_srv_cb,
};

static struct bt_mesh_elem elements[] = {
	BT_MESH_ELEM(1, BT_MESH_MODEL_LIST
					(
						BT_MESH_MODEL_CFG_SRV,
						BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub)
					),
					BT_MESH_MODEL_NONE),
	BT_MESH_ELEM(2, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_SRV(&led_ctx.srv)), BT_MESH_MODEL_NONE),
	BT_MESH_ELEM(3, BT_MESH_MODEL_LIST(BT_MESH_MODEL_SENSOR_SRV(&sensor_srv)), BT_MESH_MODEL_NONE),
};

static const struct bt_mesh_comp comp = {
	.cid = CONFIG_BT_COMPANY_ID,
	.elem = elements,
	.elem_count = ARRAY_SIZE(elements),
};

const struct bt_mesh_comp *model_handler_init(void)
{
	k_delayed_work_init(get_attention_blink_work(), attention_blink);
	k_delayed_work_init(&led_ctx.work, led_work);

	led_init();
	sensors_init();

	// TEST
	/*
	dev = device_get_binding(DT_PROP(DT_NODELABEL(temp), label));

	if (dev == NULL) {
		LOG_ERR("Could not initiate temperature sensor");
	} else {
		LOG_INF("Temperature sensor (%s) initiated", dev->name);
	}
	*/
	// END TEST

	return &comp;
}

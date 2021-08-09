#include "model_definitions.h"

LOG_MODULE_REGISTER(bt_model_def, LOG_LEVEL_DBG);

BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);

// Sensors
static struct bt_mesh_sensor chip_temp = {
	.type = &bt_mesh_sensor_present_dev_op_temp,
	.get = chip_temp_get,
};
static struct bt_mesh_sensor *const sensors[] = {
	&chip_temp
};
static struct bt_mesh_sensor_srv sensor_srv = BT_MESH_SENSOR_SRV_INIT(sensors, ARRAY_SIZE(sensors));

// LED's
struct led_ctx led_ctx = {
	.srv = BT_MESH_ONOFF_SRV_INIT(&onoff_handlers),
};

// Health
static struct bt_mesh_health_srv health_srv = {
	.cb = &health_srv_cb,
};

// Model
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

	return &comp;
}

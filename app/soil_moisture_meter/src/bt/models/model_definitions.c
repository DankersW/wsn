#include "model_definitions.h"

BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);


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

	return &comp;
}

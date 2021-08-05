#include "model_definitions.h"

BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);

struct led_ctx led_ctx[4] = {
	[0 ... 3] = {
		.srv = BT_MESH_ONOFF_SRV_INIT(&onoff_handlers),
	}
};

static struct bt_mesh_health_srv health_srv = {
	.cb = &health_srv_cb,
};

static struct bt_mesh_elem elements[] = {
	BT_MESH_ELEM(1, BT_MESH_MODEL_LIST
					(
						BT_MESH_MODEL_CFG_SRV,
						BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub),
						BT_MESH_MODEL_ONOFF_SRV(&led_ctx[0].srv)),
					BT_MESH_MODEL_NONE),
	BT_MESH_ELEM(2, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_SRV(&led_ctx[1].srv)), BT_MESH_MODEL_NONE),
	//BT_MESH_ELEM(3, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_SRV(&led_ctx[2].srv)), BT_MESH_MODEL_NONE),
	//BT_MESH_ELEM(4, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_SRV(&led_ctx[3].srv)), BT_MESH_MODEL_NONE),
};

static const struct bt_mesh_comp comp = {
	.cid = CONFIG_BT_COMPANY_ID,
	.elem = elements,
	.elem_count = ARRAY_SIZE(elements),
};

const struct bt_mesh_comp *model_handler_init(void)
{
	k_delayed_work_init(get_attention_blink_work(), attention_blink);

	for (int i = 0; i < ARRAY_SIZE(led_ctx); ++i) 
	{
		k_delayed_work_init(&led_ctx[i].work, led_work);
	}
	return &comp;
}

void led_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, const struct bt_mesh_onoff_set *set,
		     struct bt_mesh_onoff_status *rsp)
{
	handler_led_set(srv, ctx, set, rsp, led_ctx);
}

void led_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx, struct bt_mesh_onoff_status *rsp)
{
	handler_led_get(srv, ctx, rsp);
}

void led_work(struct k_work *work)
{
	handler_led_work(work, led_ctx);
}

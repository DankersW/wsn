#include "model_definitions.h"


struct led_ctx led_ctx[4] = {
	[0 ... 3] = {
		.srv = BT_MESH_ONOFF_SRV_INIT(&onoff_handlers),
	}
};

static void led_work(struct k_work *work)
{
	handler_led_work(work, led_ctx);
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





// Set up a repeating delayed work to blink the DK's LEDs when attention is requested.

static struct k_delayed_work attention_blink_work;

//static void attention_blink(struct k_work *work)
void attention_blink(struct k_work *work)
{
	static int idx;
	const uint8_t pattern[] = {
		BIT(0) | BIT(1),
		BIT(1) | BIT(2),
		BIT(2) | BIT(3),
		BIT(3) | BIT(0),
	};
	dk_set_leds(pattern[idx++ % ARRAY_SIZE(pattern)]);
	k_delayed_work_submit(&attention_blink_work, K_MSEC(30));
}

//static void attention_on(struct bt_mesh_model *mod)
void attention_on(struct bt_mesh_model *mod)
{
	k_delayed_work_submit(&attention_blink_work, K_NO_WAIT);
}

//static void attention_off(struct bt_mesh_model *mod)
void attention_off(struct bt_mesh_model *mod)
{
	k_delayed_work_cancel(&attention_blink_work);
	dk_set_leds(DK_NO_LEDS_MSK);
}



static const struct bt_mesh_health_srv_cb health_srv_cb = {
	.attn_on = attention_on,
	.attn_off = attention_off
};

static struct bt_mesh_health_srv health_srv = {
	.cb = &health_srv_cb,
};

BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);

static struct bt_mesh_elem elements[] = {
	BT_MESH_ELEM(
		1, BT_MESH_MODEL_LIST(
			BT_MESH_MODEL_CFG_SRV,
			BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub),
			BT_MESH_MODEL_ONOFF_SRV(&led_ctx[0].srv)),
		BT_MESH_MODEL_NONE),
	BT_MESH_ELEM(
		2, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_SRV(&led_ctx[1].srv)),
		BT_MESH_MODEL_NONE),
	BT_MESH_ELEM(
		3, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_SRV(&led_ctx[2].srv)),
		BT_MESH_MODEL_NONE),
	BT_MESH_ELEM(
		4, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_SRV(&led_ctx[3].srv)),
		BT_MESH_MODEL_NONE),
};


static const struct bt_mesh_comp comp = {
	.cid = CONFIG_BT_COMPANY_ID,
	.elem = elements,
	.elem_count = ARRAY_SIZE(elements),
};


const struct bt_mesh_comp *model_handler_init(void)
{
	k_delayed_work_init(&attention_blink_work, attention_blink);

	for (int i = 0; i < ARRAY_SIZE(led_ctx); ++i) {
		k_delayed_work_init(&led_ctx[i].work, led_work);
	}

	return &comp;
}


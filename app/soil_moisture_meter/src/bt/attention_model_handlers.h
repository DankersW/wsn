#ifndef ATTENTION_MODEL_HANDLERS_H
#define ATTENTION_MODEL_HANDLERS_H

#include <bluetooth/mesh.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <dk_buttons_and_leds.h>

void attention_blink(struct k_work *work);
void attention_on(struct bt_mesh_model *mod);
void attention_off(struct bt_mesh_model *mod);
struct k_delayed_work *get_attention_blink_work();

#endif // ATTENTION_MODEL_HANDLERS_H
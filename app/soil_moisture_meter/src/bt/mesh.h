#ifndef MESH_H
#define MESH_H

#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <bluetooth/mesh/dk_prov.h>
#include <logging/log.h>

#include "model_definitions.h"

void enable_bt();
void bt_ready(int err);

#endif // MESH_H
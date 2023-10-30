#pragma once

#include "building/building.h"
#include "grid/point.h"

void building_river_update_open_water_access();
int building_dock_count_idle_dockers(building* dock);
bool building_dock_is_connected_to_open_water(tile2i tile);
int building_dock_get_free_destination(int ship_id, tile2i* tile);
int building_dock_get_queue_destination(int ship_id, tile2i *tile);

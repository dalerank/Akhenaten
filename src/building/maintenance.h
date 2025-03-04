#pragma once

#include "grid/point.h"
#include "building/building.h"
#include <map>
#include <functional>

struct event_fire_damage { building_id bid; };

void building_maintenance_update_fire_direction();
int building_maintenance_fire_direction();
void building_maintenance_update_burning_ruins();
void building_maintenance_check_fire_collapse();
std::pair<int, tile2i> building_maintenance_get_closest_burning_ruin(tile2i tile);
void building_maintenance_check_kingdome_access();
void building_maintenance_init();
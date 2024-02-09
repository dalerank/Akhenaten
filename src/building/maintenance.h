#pragma once

#include "grid/point.h"
#include <map>

void building_maintenance_update_fire_direction(void);
void building_maintenance_update_burning_ruins(void);
void building_maintenance_check_fire_collapse(void);
std::pair<int, tile2i> building_maintenance_get_closest_burning_ruin(tile2i tile);

void building_maintenance_check_kingdome_access(void);

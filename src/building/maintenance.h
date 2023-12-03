#pragma once

#include "grid/point.h"

void building_maintenance_update_fire_direction(void);
void building_maintenance_update_burning_ruins(void);
void building_maintenance_check_fire_collapse(void);
int building_maintenance_get_closest_burning_ruin(tile2i tile, int* distance);

void building_maintenance_check_kingdome_access(void);

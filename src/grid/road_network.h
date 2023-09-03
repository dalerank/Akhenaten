#pragma once

#include "grid/point.h"

void map_road_network_clear();

int map_road_network_get(int grid_offset);

inline int map_road_network_get(map_point tile) { return map_road_network_get(tile.grid_offset()); }

void map_road_network_update();
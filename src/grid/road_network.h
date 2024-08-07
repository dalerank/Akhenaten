#pragma once

#include "grid/point.h"

void map_road_network_clear();

int map_road_network_get(int grid_offset);

inline int map_road_network_get(tile2i tile) { return map_road_network_get(tile.grid_offset()); }
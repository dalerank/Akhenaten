#pragma once

#include "city/constants.h"
#include "grid/grid.h"
#include "grid/point.h"

extern grid_xx g_architect_reach_distance;

void map_architect_reach_calculate(tile2i origin, e_permission perm, int max_tiles);

int map_architect_reach_distance(tile2i tile);
inline int map_architect_reach_distance(int grid_offset) {
    return map_architect_reach_distance(tile2i(grid_offset));
}

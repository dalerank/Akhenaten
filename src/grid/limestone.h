#pragma once

#include "grid/grid.h"

int map_get_limestone(int grid_offset);
inline int map_get_limestone(tile2i tile) { return map_get_limestone(tile.grid_offset()); }

void map_limestone_deplete(int grid_offset, int amount);
inline void map_limestone_deplete(tile2i tile, int amount) { return map_limestone_deplete(tile.grid_offset(), amount); }

void map_limestone_init();


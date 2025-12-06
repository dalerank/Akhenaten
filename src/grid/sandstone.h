#pragma once

#include "grid/grid.h"

int map_get_sandstone(int grid_offset);
inline int map_get_sandstone(tile2i tile) { return map_get_sandstone(tile.grid_offset()); }

void map_sandstone_deplete(int grid_offset, int amount);
inline void map_sandstone_deplete(tile2i tile, int amount) { return map_sandstone_deplete(tile.grid_offset(), amount); }

void map_sandstone_init();


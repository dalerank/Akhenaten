#pragma once

#include "grid/grid.h"

int map_get_clay(int grid_offset);
inline int map_get_clay(tile2i tile) { return map_get_clay(tile.grid_offset()); }

void map_clay_deplete(int grid_offset, int amount);
inline void map_clay_deplete(tile2i tile, int amount) { return map_clay_deplete(tile.grid_offset(), amount); }

void map_clay_init();


#pragma once

#include "grid/grid.h"

int map_get_granite(int grid_offset);
inline int map_get_granite(tile2i tile) { return map_get_granite(tile.grid_offset()); }

void map_granite_deplete(int grid_offset, int amount);
inline void map_granite_deplete(tile2i tile, int amount) { return map_granite_deplete(tile.grid_offset(), amount); }

void map_granite_init();


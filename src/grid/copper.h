#pragma once

#include "grid/grid.h"

int map_get_copper(int grid_offset);
inline int map_get_copper(tile2i tile) { return map_get_copper(tile.grid_offset()); }

void map_copper_deplete(int grid_offset, int amount);
inline void map_copper_deplete(tile2i tile, int amount) { return map_copper_deplete(tile.grid_offset(), amount); }

void map_copper_init();


#pragma once

#include "grid/grid.h"

int map_get_gems(int grid_offset);
inline int map_get_gems(tile2i tile) { return map_get_gems(tile.grid_offset()); }

void map_gems_deplete(int grid_offset, int amount);
inline void map_gems_deplete(tile2i tile, int amount) { return map_gems_deplete(tile.grid_offset(), amount); }

void map_gems_init();


#pragma once

#include "grid/grid.h"

int map_get_golden(int grid_offset);
inline int map_get_golden(tile2i tile) { return map_get_golden(tile.grid_offset()); }

void map_golden_deplete(int grid_offset, int amount);
inline void map_golden_deplete(tile2i tile, int amount) { return map_golden_deplete(tile.grid_offset(), amount); }

void map_golden_init();


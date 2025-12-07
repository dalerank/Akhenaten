#pragma once

#include "grid/grid.h"

int map_get_stone(int grid_offset);
inline int map_get_stone(tile2i tile) { return map_get_stone(tile.grid_offset()); }

void map_stone_deplete(int grid_offset, int amount);
inline void map_stone_deplete(tile2i tile, int amount) { return map_stone_deplete(tile.grid_offset(), amount); }

void map_stone_init();


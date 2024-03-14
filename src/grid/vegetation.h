#pragma once

#include "tile_cache.h"

extern tile_cache marshland_tiles_cache;
extern tile_cache trees_tiles_cache;

void foreach_marshland_tile(void (*callback)(int grid_offset));
void foreach_tree_tile(void (*callback)(int grid_offset));

int map_get_vegetation_growth(int grid_offset);
inline int map_get_vegetation_growth(tile2i tile) { return map_get_vegetation_growth(tile.grid_offset()); }
void vegetation_deplete(int grid_offset);
inline void vegetation_deplete(tile2i tile) { return vegetation_deplete(tile.grid_offset()); }
void vegetation_growth_update();

int gatherers_harvesting_point(int grid_offset);
inline int gatherers_harvesting_point(tile2i tile) { return gatherers_harvesting_point(tile.grid_offset()); }
bool can_harvest_point(int grid_offset, int max_gatherers = 1);
inline bool can_harvest_point(tile2i tile, int max_gatherers = 1) { return can_harvest_point(tile.grid_offset(), max_gatherers); }

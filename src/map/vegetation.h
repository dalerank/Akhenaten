#ifndef OZYMANDIAS_VEGETATION_H
#define OZYMANDIAS_VEGETATION_H

#include "tile_cache.h"

extern tile_cache marshland_tiles_cache;
extern tile_cache trees_tiles_cache;

void foreach_marshland_tile(void (*callback)(int grid_offset));
void foreach_tree_tile(void (*callback)(int grid_offset));

int map_get_vegetation_growth(int grid_offset);
void vegetation_deplete(int grid_offset);
void vegetation_growth_update();

int gatherers_harvesting_point(int grid_offset);
bool can_harvest_point(int grid_offset, int max_gatherers = 1);

#endif //OZYMANDIAS_VEGETATION_H

#ifndef OZYMANDIAS_VEGETATION_H
#define OZYMANDIAS_VEGETATION_H

#include "tile_cache.h"

extern tile_cache vegetation_tiles_cache;

int map_get_vegetation_growth(int grid_offset);
void vegetation_deplete(int grid_offset);
void vegetation_growth_update();

int gatherers_harvesting_point(int grid_offset);
bool can_harvest_point(int grid_offset, int max_gatherers = 1);

#endif //OZYMANDIAS_VEGETATION_H

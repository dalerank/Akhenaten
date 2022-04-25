#ifndef OZYMANDIAS_TILE_CACHE_H
#define OZYMANDIAS_TILE_CACHE_H

#include "grid.h"

class tile_cache {
    int all_river_tiles[GRID_SIZE_PH * GRID_SIZE_PH];
    int river_total_tiles = 0;
};


#endif //OZYMANDIAS_TILE_CACHE_H

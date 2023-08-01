#ifndef OZYMANDIAS_TILE_CACHE_H
#define OZYMANDIAS_TILE_CACHE_H

#include "grid.h"

class tile_cache {
private:
    int pCache[GRID_SIZE_TOTAL];
    int pSize = 0;

public:
    void clear();
    void add(int grid_offset);
    int at(int i);
    const int size();
};

#endif // OZYMANDIAS_TILE_CACHE_H

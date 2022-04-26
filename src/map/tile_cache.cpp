#include "tile_cache.h"

void tile_cache::clear() {
    pSize = 0;
}
void tile_cache::add(int grid_offset) {
    // if not full
    if (pSize < GRID_SIZE_TOTAL) {
        pCache[pSize] = grid_offset;
        pSize++;
    }
}
int tile_cache::at(int i) {
    if (i < 0 || i >= pSize)
        return -1;
    return pCache[i];
}
const int tile_cache::size() {
    return pSize;
}
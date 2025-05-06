#include "bookmark.h"

void map_bookmarks_t::reset(void) {
    for (auto &b: points) {
        b = tile2i::invalid;
    }
}

void map_bookmarks_t::set(int i, tile2i tile) {
    if (i >= 0 && i < MAX_BOOKMARKS) {
        points[i] = tile;
    }
}

tile2i map_bookmarks_t::get(int i) {
    if (i >= 0 && i < MAX_BOOKMARKS) {
        return points[i];
    }
    return tile2i::invalid;
}
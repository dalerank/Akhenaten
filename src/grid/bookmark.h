#pragma once

#include "grid/point.h"

struct map_bookmarks_t {
    enum {
        MAX_BOOKMARKS = 4
    };

    tile2i points[MAX_BOOKMARKS];

    tile2i get(int i);
    void set(int i, tile2i tile);
    void reset();
};
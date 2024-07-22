#pragma once

#include "grid/point.h"

struct city_fishing_points_t {
    void create();
    void reset();
    void clear();
    void update(int points_num = -1);
    tile2i closest_fishing_point(tile2i pos);
};
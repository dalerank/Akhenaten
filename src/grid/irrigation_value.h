#pragma once

#include "grid/point.h"
#include "core/archive.h"

struct irrigation_value_t {
    void clear_map();
    void update();
    void update_water_lifts();
    void update_canals();
    
    void add_irrigation_at_distance(tile2i tile, int size, int distance, int value);
    void add_irrigation(tile2i tile, int size, int base_value, int range);
    
    int get(int grid_offset);
    inline int get(tile2i tile) { return get(tile.grid_offset()); }
    int get_max(tile2i tile, int size);
    int get_avg(tile2i tile, int size);
};

extern irrigation_value_t g_irrigation_value;


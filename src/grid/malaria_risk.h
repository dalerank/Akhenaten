#pragma once

#include "grid/point.h"
#include "core/archive.h"

struct malaria_risk_t {
    void update_terrain();
    void clear_map();
    void update();
    void update_buildings();

    void add_to_terrain_at_distance(tile2i tile, int size, int distance, int risk);
    void add_to_terrain(tile2i tile, int size, int risk, int step, int step_size, int range);
    int get(int grid_offset);
    inline int get(tile2i tile) { return get(tile.grid_offset()); }
    int get_max(tile2i tile, int size);
    int get_avg(tile2i tile, int size);
};

extern malaria_risk_t g_malaria_risk;


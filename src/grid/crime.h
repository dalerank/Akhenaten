#pragma once

#include "grid/point.h"
#include "core/archive.h"

struct crime_t {
    struct influence_t {
        int size = 0;
        int value = 0;
        int step = 0;
        int step_size = 0;
        int range = 0;
    };

    struct env_influence_t {
        influence_t gold_rock;
    } env_influence;

    void update_terrain();
    void clear_map();
    void update();
    void update_buildings();
    void update_houses();

    void add_to_terrain_at_distance(tile2i tile, int size, int distance, int crime);
    void add_to_terrain(tile2i tile, int size, int crime, int step, int step_size, int range);
    int get(int grid_offset);
    inline int get(tile2i tile) { return get(tile.grid_offset()); }
    int get_max(tile2i tile, int size);
    int get_avg(tile2i tile, int size);
};
ANK_CONFIG_STRUCT(crime_t::influence_t, size, value, step, step_size, range)
ANK_CONFIG_STRUCT(crime_t::env_influence_t, gold_rock)
ANK_CONFIG_STRUCT(crime_t, env_influence)

extern crime_t g_crime;


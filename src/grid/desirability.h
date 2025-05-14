#pragma once

#include "grid/point.h"
#include "core/runtime_item.h"

struct desirability_t : config::runtime {
    struct influence_t {
        int size = 0;
        int value = 0;
        int step = 0;
        int step_size = 0;
        int range = 0;

         void load(archive arch);
    };

    struct {
        influence_t plaza;
        influence_t earthquake;
        influence_t garden;
        influence_t rubble;
    } influence;

    desirability_t(pcstr s) : runtime(s) {}

    void update_terrain();
    void clear_map();
    void update();
    void update_buildings();

    void reset() {}
    void load(archive arch);
    void init() {}

    void add_to_terrain_at_distance(tile2i tile, int size, int distance, int desirability);
    void add_to_terrain(tile2i tile, int size, int desirability, int step, int step_size, int range);
    int get(int grid_offset);
    inline int get(tile2i tile) { return get(tile.grid_offset()); }
    int get_max(tile2i tile, int size);
    int get_avg(tile2i tile, int size);
};

extern desirability_t g_desirability;
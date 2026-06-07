#pragma once

#include "core/vec2i.h"
#include "grid/grid.h"
#include "grid/point.h"

#include <vector>

struct screentile_lookup_t {
    static constexpr int map_size = 500;
    static constexpr int orientations = 4;
    static constexpr int table_size = orientations * map_size * map_size;
    static constexpr int max_grid_offset = table_size;

    struct orientation_params_t {
        vec2i start;
        vec2i column_step;
        vec2i row_step;
    };

    std::vector<tile2i> tables;
    std::vector<vec2i> mappoint_to_pixel;

    static constexpr int index(int orientation, int x, int y) {
        return orientation * map_size * map_size + x * map_size + y;
    }

    tile2i& at(int orientation, int x, int y);
    tile2i at(int orientation, int x, int y) const;

    void ensure_tables();
    static orientation_params_t calc_params_by_orientation(int city_orientation);
    void fill_in_for_orientation(int city_orientation);
    void calculate();
};

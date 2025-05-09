#pragma once

#include "figure/figure.h"
#include "building/building.h"
#include "grid/building.h"

constexpr uint8_t MAX_COVERAGE = 96;

template<typename T>
inline int figure_provide_service(tile2i tile, figure* f, T callback) {
    int serviced = 0;
    grid_area area = map_grid_get_area(tile, 1, 2);

    map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i tile) {
        int grid_offset = tile.grid_offset();
        int building_id = map_building_at(grid_offset);
        if (building_id) {
            building *b = building_get(building_id);
            callback(b, f);
            serviced++;
        }
    });
    return serviced;
}

template<typename T>
static int figure_provide_culture(tile2i tile, figure* f, T callback) {
    return figure_provide_service(tile, f, callback);
}
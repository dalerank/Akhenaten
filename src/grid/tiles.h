#pragma once

#include "image_context.h"
#include "grid/grid.h"
#include "grid/point.h"

void map_tiles_update_all_rocks(void);

void map_tiles_update_region_shrub(int x_min, int y_min, int x_max, int y_max);

void map_tiles_update_all_plazas(void);

void map_tiles_update_all_roads(void);
void map_tiles_update_area_roads(int x, int y, int size);

void map_tiles_update_all_cleared_land();
void map_tiles_update_all_empty_land();
void map_tiles_update_region_empty_land(bool clear, tile2i tmin, tile2i tmax);

void map_tiles_update_all_meadow(void);
void map_tiles_update_region_meadow(int x_min, int y_min, int x_max, int y_max);

void map_tiles_update_vegetation(int grid_offset);
void map_tiles_upadte_all_marshland_tiles();

void map_tiles_river_refresh_entire(void);
void map_tiles_river_refresh_region(int x_min, int y_min, int x_max, int y_max);
void map_tiles_set_water(int grid_offset);

void map_tiles_update_region_canals(tile2i pmin, tile2i pmax);
int map_tiles_set_canal(tile2i tile);

namespace detail {
    template<bool is_tile, typename Func>
    void map_tiles_foreach_map_tile(Func callback) {
        int grid_offset = scenario_map_data()->start_offset;
        for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
            for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
                if constexpr (is_tile) {
                    tile2i tile(grid_offset);
                    callback(tile);
                } else {
                    callback(grid_offset);
                }
            }
        }
    }
} // namespace detail

template<typename Func>
void map_tiles_foreach_map_tile(Func callback) {
    using EventType = typename type_traits::first_func_argument<decltype(&Func::operator())>::type;
    constexpr bool is_tile = std::is_same_v<EventType, tile2i>;
    detail::map_tiles_foreach_map_tile<is_tile>(callback);
}

template<typename EventType>
void map_tiles_foreach_map_tile(void (*callback)(EventType)) {
    constexpr bool is_tile = std::is_same_v<EventType, tile2i>;
    detail::map_tiles_foreach_map_tile<is_tile>(callback);
}

template<typename Func>
void map_tiles_foreach_region_tile(tile2i tmin, tile2i tmax, Func callback) {
    map_grid_bound_area(tmin, tmax);

    map_grid_area_foreach(tmin, tmax, [&] (tile2i tile) {
        callback(tile.grid_offset());
    });
}

template<typename Func>
void map_tiles_foreach_region_tile_ex(tile2i tmin, tile2i tmax, Func callback) {
    map_grid_bound_area(tmin, tmax);
    map_grid_area_foreach(tmin, tmax, [&] (tile2i tile) {
        callback(tile);
    });
}

void map_tiles_update_all_rubble(void);
void map_tiles_update_region_rubble(int x_min, int y_min, int x_max, int y_max);

void map_tiles_update_all_elevation(void);
void map_refresh_river_image_at(int grid_offset, bool force);

enum {
    CLEAR_LAND_DONT_CHECK_FIGURES = 0,
    CLEAR_LAND_CHECK_FIGURES_OUTSIDE_ROAD = 1,
    CLEAR_LAND_CHECK_FIGURES_ANYWHERE = 2
};

int map_tiles_are_clear(int x, int y, int size, int disallowed_terrain, int check_figures = CLEAR_LAND_CHECK_FIGURES_ANYWHERE);

void map_tiles_add_entry_exit_flags(void);
void map_tiles_remove_entry_exit_flags(void);

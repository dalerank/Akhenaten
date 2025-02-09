#pragma once

#include "image_context.h"
#include "grid/point.h"

void map_tiles_update_all_rocks(void);

void map_tiles_update_region_shrub(int x_min, int y_min, int x_max, int y_max);

void map_tiles_set_canal_image(int grid_offset);

void map_tiles_update_all_plazas(void);

void map_tiles_update_all_walls(void);
void map_tiles_update_area_walls(tile2i tile, int size);
int map_tiles_set_wall(tile2i tile);

int map_tiles_is_paved_road(int grid_offset);
void map_tiles_update_all_roads(void);
void map_tiles_update_area_roads(int x, int y, int size);
int map_tiles_set_road(tile2i tile);

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

int get_canal_image(int grid_offset, bool is_road, int terrain, const terrain_image* img);
void map_tiles_update_all_canals(int include_construction);
void map_tiles_update_region_canals(int x_min, int y_min, int x_max, int y_max);
int map_tiles_set_canal(tile2i tile);

void map_tiles_foreach_region_tile(tile2i tmin, tile2i tmax, void (*callback)(tile2i));
void map_tiles_foreach_map_tile(void (*callback)(int));

void map_tiles_update_all_rubble(void);
void map_tiles_update_region_rubble(int x_min, int y_min, int x_max, int y_max);

void map_tiles_update_all_elevation(void);
void map_tiles_foreach_region_tile(tile2i tmin, tile2i tmax, void (*callback)(int grid_offset));
void map_refresh_river_image_at(int grid_offset, bool force);

enum {
    CLEAR_LAND_DONT_CHECK_FIGURES = 0,
    CLEAR_LAND_CHECK_FIGURES_OUTSIDE_ROAD = 1,
    CLEAR_LAND_CHECK_FIGURES_ANYWHERE = 2
};

int map_tiles_are_clear(int x, int y, int size, int disallowed_terrain, int check_figures = CLEAR_LAND_CHECK_FIGURES_ANYWHERE);

void map_tiles_add_entry_exit_flags(void);
void map_tiles_remove_entry_exit_flags(void);

#ifndef MAP_TILES_H
#define MAP_TILES_H

#include "image_context.h"

void map_tiles_update_all_rocks(void);

void map_tiles_update_region_trees(int x_min, int y_min, int x_max, int y_max);
void map_tiles_update_region_shrub(int x_min, int y_min, int x_max, int y_max);

void map_tiles_update_all_gardens(void);
void map_tiles_determine_gardens(void);

void map_tiles_update_all_plazas(void);

void map_tiles_update_all_walls(void);
void map_tiles_update_area_walls(int x, int y, int size);
int map_tiles_set_wall(int x, int y);

int map_tiles_is_paved_road(int grid_offset);
void map_tiles_update_all_roads(void);
void map_tiles_update_area_roads(int x, int y, int size);
int map_tiles_set_road(int x, int y);

void map_tiles_update_all_empty_land(void);
void map_tiles_update_region_empty_land(bool clear, int x_min, int y_min, int x_max, int y_max);

void map_tiles_update_all_meadow(void);
void map_tiles_update_region_meadow(int x_min, int y_min, int x_max, int y_max);

void map_tiles_update_vegetation(int grid_offset);
void map_tiles_update_all_vegetation_tiles();

void map_tiles_river_refresh_entire(void);
void map_tiles_river_refresh_region(int x_min, int y_min, int x_max, int y_max);
void map_tiles_set_water(int grid_offset);

void map_advance_floodplain_growth();
void map_update_floodplain_inundation(int leading_row, int is_flooding, int flooding_ticks);

int get_aqueduct_image(int grid_offset, bool is_road, int terrain, const terrain_image* img);
void map_tiles_update_all_aqueducts(int include_construction);
void map_tiles_update_region_aqueducts(int x_min, int y_min, int x_max, int y_max);
int map_tiles_set_aqueduct(int x, int y);

void map_tiles_update_all_earthquake(void);
void map_tiles_set_earthquake(int x, int y);

void map_tiles_update_all_rubble(void);
void map_tiles_update_region_rubble(int x_min, int y_min, int x_max, int y_max);

void map_tiles_update_all_elevation(void);

enum {
    CLEAR_LAND_DONT_CHECK_FIGURES = 0,
    CLEAR_LAND_CHECK_FIGURES_OUTSIDE_ROAD = 1,
    CLEAR_LAND_CHECK_FIGURES_ANYWHERE = 2
};

int map_tiles_are_clear(int x, int y, int size, int disallowed_terrain,
                        int check_figures = CLEAR_LAND_CHECK_FIGURES_ANYWHERE);

void map_tiles_add_entry_exit_flags(void);
void map_tiles_remove_entry_exit_flags(void);

#endif // MAP_TILES_H

#include "tiles.h"
#include <core/random.h>

#include "city/map.h"
#include "core/direction.h"
#include "core/game_environment.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "grid/aqueduct.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/desirability.h"
#include "grid/elevation.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/image_context.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "scenario/map.h"
#include <building/destruction.h>
#include <building/industry.h>
#include <city/data_private.h>
#include <city/floods.h>
#include <core/calc.h>
#include <scenario/map.h>

// #define OFFSET(x,y) (x + GRID_SIZE_PH * y)

#define FORBIDDEN_TERRAIN_MEADOW                                                                                       \
    (TERRAIN_AQUEDUCT | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP | TERRAIN_RUBBLE | TERRAIN_ROAD | TERRAIN_BUILDING     \
     | TERRAIN_GARDEN)

#define FORBIDDEN_TERRAIN_RUBBLE                                                                                       \
    (TERRAIN_AQUEDUCT | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP | TERRAIN_ROAD | TERRAIN_BUILDING | TERRAIN_GARDEN)

static int aqueduct_include_construction = 0;

// #include <chrono>
#include "floodplain.h"
#include "moisture.h"
#include "vegetation.h"

static int is_clear(int grid_offset, int size, int allowed_terrain, bool check_image, int check_figures = 2) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    if (!map_grid_is_inside(x, y, size))
        return 0;

    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = MAP_OFFSET(x + dx, y + dy);
            if (map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR & allowed_terrain))
                return 0;
            else if (check_figures && map_has_figure_at(grid_offset)) {
                // check for figures in the way?
                if (check_figures = CLEAR_LAND_CHECK_FIGURES_ANYWHERE)
                    return 0;
                else if (check_figures == CLEAR_LAND_CHECK_FIGURES_OUTSIDE_ROAD
                         && !map_terrain_is(grid_offset, TERRAIN_ROAD))
                    return 0;
            } else if (check_image && map_image_at(grid_offset))
                return 0;
            if (allowed_terrain & TERRAIN_FLOODPLAIN) {
                if (map_terrain_exists_tile_in_radius_with_type(x + dx, y + dy, 1, 1, TERRAIN_FLOODPLAIN))
                    return 0;
            }
        }
    }
    return 1;
}
int map_tiles_are_clear(int grid_offset, int size, int disallowed_terrain, int check_figures) {
    return is_clear(grid_offset, size, disallowed_terrain, false, check_figures);
}
static void foreach_map_tile(void (*callback)(int grid_offset)) {
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++)
            callback(grid_offset);
    }
}
static void foreach_region_tile(int x_min, int y_min, int x_max, int y_max, void (*callback)(int grid_offset)) {
    map_grid_bound_area(&x_min, &y_min, &x_max, &y_max);
    int grid_offset = MAP_OFFSET(x_min, y_min);
    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            callback(grid_offset);
            ++grid_offset;
        }
        grid_offset += GRID_LENGTH - (x_max - x_min + 1);
    }
}

static bool terrain_no_image_at(int grid_offset, int radius) {
    //    if (map_image_at(grid_offset) != 0) return false;
    if (radius >= 2) {
        if (map_image_at(grid_offset + GRID_OFFSET(1, 0)) != 0)
            return false;
        if (map_image_at(grid_offset + GRID_OFFSET(1, 1)) != 0)
            return false;
        if (map_image_at(grid_offset + GRID_OFFSET(0, 1)) != 0)
            return false;
    }
    if (radius >= 3) {
        if (map_image_at(grid_offset + GRID_OFFSET(2, 0)) != 0)
            return false;
        if (map_image_at(grid_offset + GRID_OFFSET(2, 1)) != 0)
            return false;
        if (map_image_at(grid_offset + GRID_OFFSET(2, 2)) != 0)
            return false;
        if (map_image_at(grid_offset + GRID_OFFSET(1, 2)) != 0)
            return false;
        if (map_image_at(grid_offset + GRID_OFFSET(0, 2)) != 0)
            return false;
    }
    return true;
}
static bool is_updatable_rock(int grid_offset) {
    return map_terrain_is(grid_offset, TERRAIN_ROCK) && !map_property_is_plaza_or_earthquake(grid_offset)
           && !map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP);
}
static void clear_rock_image(int grid_offset) {
    if (is_updatable_rock(grid_offset)) {
        map_image_set(grid_offset, 0);
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
}
static void set_rock_image(int grid_offset) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    if (is_updatable_rock(grid_offset)) {
        if (!map_image_at(grid_offset)) {
            if (map_terrain_all_tiles_in_area_are(x, y, 3, TERRAIN_ROCK)
                && terrain_no_image_at(grid_offset, 3)) { // 3-tile large rock
                int image_id = 12 + (map_random_get(grid_offset) & 1);
                if (map_terrain_exists_tile_in_radius_with_type(x, y, 3, 4, TERRAIN_ELEVATION))
                    image_id += image_id_from_group(GROUP_TERRAIN_ELEVATION_ROCK);
                else
                    image_id += image_id_from_group(GROUP_TERRAIN_ROCK);
                map_building_tiles_add(0, x, y, 3, image_id, TERRAIN_ROCK);
            } else if (map_terrain_all_tiles_in_area_are(x, y, 2, TERRAIN_ROCK)
                       && terrain_no_image_at(grid_offset, 2)) { // 2-tile large rock
                int image_id = 8 + (map_random_get(grid_offset) & 3);
                if (map_terrain_exists_tile_in_radius_with_type(x, y, 2, 4, TERRAIN_ELEVATION))
                    image_id += image_id_from_group(GROUP_TERRAIN_ELEVATION_ROCK);
                else
                    image_id += image_id_from_group(GROUP_TERRAIN_ROCK);
                map_building_tiles_add(0, x, y, 2, image_id, TERRAIN_ROCK);
            } else { // 1-tile large rock
                int image_id = map_random_get(grid_offset) & 7;
                if (map_terrain_exists_tile_in_radius_with_type(x, y, 1, 4, TERRAIN_ELEVATION))
                    image_id += image_id_from_group(GROUP_TERRAIN_ELEVATION_ROCK);
                else
                    image_id += image_id_from_group(GROUP_TERRAIN_ROCK);
                map_image_set(grid_offset, image_id);
            }
        }
    }
}
static void set_ore_rock_image(int grid_offset) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    if (is_updatable_rock(grid_offset)) {
        if (!map_image_at(grid_offset)) {
            if (map_terrain_all_tiles_in_area_are(x, y, 3, TERRAIN_ORE)
                && terrain_no_image_at(grid_offset, 3)) { // 3-tile large rock
                int image_id = 12 + (map_random_get(grid_offset) & 1);
                //                if (map_terrain_exists_tile_in_radius_with_type(x, y, 3, 4, TERRAIN_ELEVATION))
                //                    image_id += image_id_from_group(GROUP_TERRAIN_ELEVATION_ROCK);
                //                else
                image_id += image_id_from_group(GROUP_TERRAIN_ORE_ROCK);
                map_building_tiles_add(0, x, y, 3, image_id, TERRAIN_ORE);
            } else if (map_terrain_all_tiles_in_area_are(x, y, 2, TERRAIN_ORE)
                       && terrain_no_image_at(grid_offset, 2)) { // 2-tile large rock
                int image_id = 8 + (map_random_get(grid_offset) & 3);
                //                if (map_terrain_exists_tile_in_radius_with_type(x, y, 2, 4, TERRAIN_ELEVATION))
                //                    image_id += image_id_from_group(GROUP_TERRAIN_ELEVATION_ROCK);
                //                else
                image_id += image_id_from_group(GROUP_TERRAIN_ORE_ROCK);
                map_building_tiles_add(0, x, y, 2, image_id, TERRAIN_ORE);
            } else if (map_terrain_is(grid_offset, TERRAIN_ORE)) { // 1-tile large rock
                int image_id = map_random_get(grid_offset) & 7;
                //                if (map_terrain_exists_tile_in_radius_with_type(x, y, 1, 4, TERRAIN_ELEVATION))
                //                    image_id += image_id_from_group(GROUP_TERRAIN_ELEVATION_ROCK);
                //                else
                image_id += image_id_from_group(GROUP_TERRAIN_ORE_ROCK);
                map_image_set(grid_offset, image_id);
            }
        }
    }
}
void map_tiles_update_all_rocks(void) {
    foreach_map_tile(clear_rock_image);
    foreach_map_tile(set_ore_rock_image);
    foreach_map_tile(set_rock_image);
}

static void update_tree_image(int grid_offset) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    if (map_terrain_is(grid_offset, TERRAIN_TREE)
        && !map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP)) {
        int image_id = image_id_from_group(GROUP_TERRAIN_TREE) + (map_random_get(grid_offset) & 7);

        int grasslevel = map_grasslevel_get(grid_offset);
        if (map_get_vegetation_growth(grid_offset) == 255) {
            if (map_terrain_has_only_rocks_trees_in_ring(x, y, 3))
                image_id += 56;
            else if (map_terrain_has_only_rocks_trees_in_ring(x, y, 2))
                image_id += 48;
            else {
                if (grasslevel > 8)
                    image_id += 32;
                else if (grasslevel > 4)
                    image_id += 16;
                if (map_terrain_has_only_rocks_trees_in_ring(x, y, 1))
                    image_id += 8;
            }
        } else {
            image_id += 64;
            if (grasslevel > 8)
                image_id += 16;
            else if (grasslevel > 4)
                image_id += 8;
            //            if (map_terrain_has_only_rocks_trees_in_ring(x, y, 1))
            //                image_id += 8;
        }
        map_image_set(grid_offset, image_id);

        //        if (map_terrain_has_only_rocks_trees_in_ring(x, y, 3))
        //            map_image_set(grid_offset, image_id + 24);
        //        else if (map_terrain_has_only_rocks_trees_in_ring(x, y, 2))
        //            map_image_set(grid_offset, image_id + 16);
        //        if (map_terrain_has_only_rocks_trees_in_ring(x, y, 1))
        //            map_image_set(grid_offset, image_id + 8);
        //        else
        //            map_image_set(grid_offset, image_id);

        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
        map_aqueduct_set(grid_offset, 0);
    }
}
static void update_tree_image_3x3(int grid_offset) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    if (map_terrain_is(grid_offset, TERRAIN_TREE)
        && !map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP)) {
        foreach_region_tile(x - 1, y - 1, x + 1, y + 1, update_tree_image);
    }
}
void map_tiles_update_region_trees(int x_min, int y_min, int x_max, int y_max) {
    foreach_region_tile(x_min, y_min, x_max, y_max, update_tree_image_3x3);
}
static void set_shrub_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_SHRUB)
        && !map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP)) {
        map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_SHRUB) + (map_random_get(grid_offset) & 7));
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
}
void map_tiles_update_region_shrub(int x_min, int y_min, int x_max, int y_max) {
    foreach_region_tile(x_min, y_min, x_max, y_max, set_shrub_image);
}

static void clear_garden_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_GARDEN)
        && !map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP)) {
        map_image_set(grid_offset, 0);
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
}
static void set_garden_image(int grid_offset) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    if (map_terrain_is(grid_offset, TERRAIN_GARDEN)
        && !map_terrain_is(grid_offset, TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP)) {
        if (!map_image_at(grid_offset)) {
            int image_id = image_id_from_group(GROUP_TERRAIN_GARDEN);
            if (map_terrain_all_tiles_in_area_are(x, y, 2, TERRAIN_GARDEN)) {
                switch (map_random_get(grid_offset) & 3) {
                case 0:
                case 1:
                    image_id += 6;
                    break;
                case 2:
                    image_id += 5;
                    break;
                case 3:
                    image_id += 4;
                    break;
                }
                map_building_tiles_add(0, x, y, 2, image_id, TERRAIN_GARDEN);
            } else {
                if (y & 1) {
                    switch (x & 3) {
                    case 0:
                    case 2:
                        image_id += 2;
                        break;
                    case 1:
                    case 3:
                        image_id += 3;
                        break;
                    }
                } else {
                    switch (x & 3) {
                    case 1:
                    case 3:
                        image_id += 1;
                        break;
                    }
                }
                map_image_set(grid_offset, image_id);
            }
        }
    }
}
void map_tiles_update_all_gardens(void) {
    foreach_map_tile(clear_garden_image);
    foreach_map_tile(set_garden_image);
}
static void determine_garden_tile(int grid_offset) {
    int base_image = image_id_from_group(GROUP_TERRAIN_GARDEN);
    int image_id = map_image_at(grid_offset);
    if (image_id >= base_image && image_id <= base_image + 6) {
        map_terrain_add(grid_offset, TERRAIN_GARDEN);
        map_property_clear_constructing(grid_offset);
        map_aqueduct_set(grid_offset, 0);
    }
}
void map_tiles_determine_gardens(void) {
    foreach_map_tile(determine_garden_tile);
}

static void remove_plaza_below_building(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_ROAD) && map_property_is_plaza_or_earthquake(grid_offset)) {
        if (map_terrain_is(grid_offset, TERRAIN_BUILDING))
            map_property_clear_plaza_or_earthquake(grid_offset);
    }
}
static void clear_plaza_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_ROAD) && map_property_is_plaza_or_earthquake(grid_offset)) {
        map_image_set(grid_offset, 0);
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
}
static int is_tile_plaza(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_ROAD) && map_property_is_plaza_or_earthquake(grid_offset)
        && !map_terrain_is(grid_offset, TERRAIN_WATER | TERRAIN_BUILDING) && !map_image_at(grid_offset)) {
        return 1;
    }
    return 0;
}
static int is_two_tile_square_plaza(int grid_offset) {
    return is_tile_plaza(grid_offset + GRID_OFFSET(1, 0)) && is_tile_plaza(grid_offset + GRID_OFFSET(0, 1))
           && is_tile_plaza(grid_offset + GRID_OFFSET(1, 1));
}
static void set_plaza_image(int grid_offset) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    if (map_terrain_is(grid_offset, TERRAIN_ROAD) && map_property_is_plaza_or_earthquake(grid_offset)
        && !map_image_at(grid_offset)) {
        int image_id = image_id_from_group(GROUP_TERRAIN_PLAZA);
        if (is_two_tile_square_plaza(grid_offset)) {
            if (map_random_get(grid_offset) & 1)
                image_id += 7;
            else {
                image_id += 6;
            }
            map_building_tiles_add(0, x, y, 2, image_id, TERRAIN_ROAD);
        } else {
            // single tile plaza
            switch ((x & 1) + (y & 1)) {
            case 2:
                image_id += 1;
                break;
            case 1:
                image_id += 2;
                break;
            }
            map_image_set(grid_offset, image_id);
        }
    }
}
void map_tiles_update_all_plazas(void) {
    foreach_map_tile(remove_plaza_below_building);
    foreach_map_tile(clear_plaza_image);
    foreach_map_tile(set_plaza_image);
}

static int get_gatehouse_building_id(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_GATEHOUSE))
        return map_building_at(grid_offset);

    return 0;
}
static int get_gatehouse_position(int grid_offset, int direction, int building_id) {
    int result = 0;
    if (direction == DIR_0_TOP_RIGHT) {
        if (map_terrain_is(grid_offset + GRID_OFFSET(1, -1), TERRAIN_GATEHOUSE)
            && map_building_at(grid_offset + GRID_OFFSET(1, -1)) == building_id) {
            result = 1;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(-1, 1), TERRAIN_WALL)) {
                result = 2;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, 1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

        } else if (map_terrain_is(grid_offset + GRID_OFFSET(-1, -1), TERRAIN_GATEHOUSE)
                   && map_building_at(grid_offset + GRID_OFFSET(-1, -1)) == building_id) {
            result = 3;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(1, 1), TERRAIN_WALL)) {
                result = 4;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, 1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;
        }
    } else if (direction == DIR_6_TOP_LEFT) {
        if (map_terrain_is(grid_offset + GRID_OFFSET(-1, 1), TERRAIN_GATEHOUSE)
            && map_building_at(grid_offset + GRID_OFFSET(-1, 1)) == building_id) {
            result = 1;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(1, -1), TERRAIN_WALL)) {
                result = 2;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, 1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

        } else if (map_terrain_is(grid_offset + GRID_OFFSET(-1, -1), TERRAIN_GATEHOUSE)
                   && map_building_at(grid_offset + GRID_OFFSET(-1, -1)) == building_id) {
            result = 3;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(1, 1), TERRAIN_WALL)) {
                result = 4;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, -1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;
        }
    } else if (direction == DIR_4_BOTTOM_LEFT) {
        if (map_terrain_is(grid_offset + GRID_OFFSET(1, 1), TERRAIN_GATEHOUSE)
            && map_building_at(grid_offset + GRID_OFFSET(1, 1)) == building_id) {
            result = 1;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(-1, -1), TERRAIN_WALL)) {
                result = 2;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(1, -1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

        } else if (map_terrain_is(grid_offset + GRID_OFFSET(-1, 1), TERRAIN_GATEHOUSE)
                   && map_building_at(grid_offset + GRID_OFFSET(-1, 1)) == building_id) {
            result = 3;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(1, -1), TERRAIN_WALL)) {
                result = 4;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, -1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;
        }
    } else if (direction == DIR_2_BOTTOM_RIGHT) {
        if (map_terrain_is(grid_offset + GRID_OFFSET(1, 1), TERRAIN_GATEHOUSE)
            && map_building_at(grid_offset + GRID_OFFSET(1, 1)) == building_id) {
            result = 1;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(-1, -1), TERRAIN_WALL)) {
                result = 2;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, 1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

        } else if (map_terrain_is(grid_offset + GRID_OFFSET(1, -1), TERRAIN_GATEHOUSE)
                   && map_building_at(grid_offset + GRID_OFFSET(1, -1)) == building_id) {
            result = 3;
            if (!map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_WALL))
                result = 0;

            if (map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_WALL)
                && map_terrain_is(grid_offset + GRID_OFFSET(-1, 1), TERRAIN_WALL)) {
                result = 4;
            }
            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;

            if (!map_terrain_is(grid_offset + GRID_OFFSET(-1, -1), TERRAIN_WALL_OR_GATEHOUSE))
                result = 0;
        }
    }
    return result;
}
static void set_wall_gatehouse_image_manually(int grid_offset) {
    int gatehouse_up = get_gatehouse_building_id(grid_offset + GRID_OFFSET(0, -1));
    int gatehouse_left = get_gatehouse_building_id(grid_offset + GRID_OFFSET(-1, 0));
    int gatehouse_down = get_gatehouse_building_id(grid_offset + GRID_OFFSET(0, 1));
    int gatehouse_right = get_gatehouse_building_id(grid_offset + GRID_OFFSET(1, 0));
    int image_offset = 0;
    int map_orientation = city_view_orientation();
    if (map_orientation == DIR_0_TOP_RIGHT) {
        if (gatehouse_up && !gatehouse_left) {
            int pos = get_gatehouse_position(grid_offset, DIR_0_TOP_RIGHT, gatehouse_up);
            if (pos > 0) {
                if (pos <= 2)
                    image_offset = 29;
                else if (pos == 3)
                    image_offset = 31;
                else {
                    image_offset = 33;
                }
            }
        } else if (gatehouse_left && !gatehouse_up) {
            int pos = get_gatehouse_position(grid_offset, DIR_6_TOP_LEFT, gatehouse_left);
            if (pos > 0) {
                if (pos <= 2)
                    image_offset = 30;
                else if (pos == 3)
                    image_offset = 32;
                else {
                    image_offset = 33;
                }
            }
        }
    } else if (map_orientation == DIR_2_BOTTOM_RIGHT) {
        if (gatehouse_up && !gatehouse_right) {
            int pos = get_gatehouse_position(grid_offset, DIR_0_TOP_RIGHT, gatehouse_up);
            if (pos > 0) {
                if (pos == 1)
                    image_offset = 32;
                else if (pos == 2)
                    image_offset = 33;
                else {
                    image_offset = 30;
                }
            }
        } else if (gatehouse_right && !gatehouse_up) {
            int pos = get_gatehouse_position(grid_offset, DIR_2_BOTTOM_RIGHT, gatehouse_right);
            if (pos > 0) {
                if (pos <= 2)
                    image_offset = 29;
                else if (pos == 3)
                    image_offset = 31;
                else {
                    image_offset = 33;
                }
            }
        }
    } else if (map_orientation == DIR_4_BOTTOM_LEFT) {
        if (gatehouse_down && !gatehouse_right) {
            int pos = get_gatehouse_position(grid_offset, DIR_4_BOTTOM_LEFT, gatehouse_down);
            if (pos > 0) {
                if (pos == 1)
                    image_offset = 31;
                else if (pos == 2)
                    image_offset = 33;
                else {
                    image_offset = 29;
                }
            }
        } else if (gatehouse_right && !gatehouse_down) {
            int pos = get_gatehouse_position(grid_offset, DIR_2_BOTTOM_RIGHT, gatehouse_right);
            if (pos > 0) {
                if (pos == 1)
                    image_offset = 32;
                else if (pos == 2)
                    image_offset = 33;
                else {
                    image_offset = 30;
                }
            }
        }
    } else if (map_orientation == DIR_6_TOP_LEFT) {
        if (gatehouse_down && !gatehouse_left) {
            int pos = get_gatehouse_position(grid_offset, DIR_4_BOTTOM_LEFT, gatehouse_down);
            if (pos > 0) {
                if (pos <= 2)
                    image_offset = 30;
                else if (pos == 3)
                    image_offset = 32;
                else {
                    image_offset = 33;
                }
            }
        } else if (gatehouse_left && !gatehouse_down) {
            int pos = get_gatehouse_position(grid_offset, DIR_6_TOP_LEFT, gatehouse_left);
            if (pos > 0) {
                if (pos == 1)
                    image_offset = 31;
                else if (pos == 2)
                    image_offset = 33;
                else {
                    image_offset = 29;
                }
            }
        }
    }
    if (image_offset)
        map_image_set(grid_offset, image_id_from_group(GROUP_BUILDING_WALL) + image_offset);
}

static void set_wall_image(int grid_offset) {
    if (!map_terrain_is(grid_offset, TERRAIN_WALL) || map_terrain_is(grid_offset, TERRAIN_BUILDING))
        return;
    const terrain_image* img = map_image_context_get_wall(grid_offset);
    map_image_set(grid_offset, image_id_from_group(GROUP_BUILDING_WALL) + img->group_offset + img->item_offset);
    map_property_set_multi_tile_size(grid_offset, 1);
    map_property_mark_draw_tile(grid_offset);
    if (map_terrain_count_directly_adjacent_with_type(grid_offset, TERRAIN_GATEHOUSE) > 0) {
        img = map_image_context_get_wall_gatehouse(grid_offset);
        if (img->is_valid) {
            map_image_set(grid_offset, image_id_from_group(GROUP_BUILDING_WALL) + img->group_offset + img->item_offset);
        } else {
            set_wall_gatehouse_image_manually(grid_offset);
        }
    }
}
void map_tiles_update_all_walls(void) {
    foreach_map_tile(set_wall_image);
}
void map_tiles_update_area_walls(int x, int y, int size) {
    foreach_region_tile(x - 1, y - 1, x + size - 2, y + size - 2, set_wall_image);
}
int map_tiles_set_wall(int x, int y) {
    int grid_offset = MAP_OFFSET(x, y);
    int tile_set = 0;
    if (!map_terrain_is(grid_offset, TERRAIN_WALL))
        tile_set = 1;

    map_terrain_add(grid_offset, TERRAIN_WALL);
    map_property_clear_constructing(grid_offset);

    foreach_region_tile(x - 1, y - 1, x + 1, y + 1, set_wall_image);
    return tile_set;
}

int get_aqueduct_image(int grid_offset, bool is_road, int terrain, const terrain_image* img) {
    if (map_terrain_is(grid_offset, TERRAIN_WATER))
        return 0;

    int image_aqueduct = image_id_from_group(GROUP_BUILDING_AQUEDUCT); // 119 C3
    int water_offset = 0;
    int terrain_image = map_image_at(grid_offset);
    if (terrain_image >= image_aqueduct && terrain_image < image_aqueduct + IMAGE_CANAL_FULL_OFFSET)
        water_offset = 0; // has water
    else                  // has no water
        water_offset = IMAGE_CANAL_FULL_OFFSET;

    // floodplains
    int floodplains_offset = 0;
    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN))
        floodplains_offset = IMAGE_CANAL_FLOODPLAIN_OFFSET;

    // curve/connection offset
    int image_offset = img->group_offset;
    // TODO: some edge cases with roads don't perfectly match up with original game (not really a priority?)
    if (is_road) {
        bool road_dir_right = false;
        if (map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_ROAD))
            road_dir_right = true;
        if (map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_ROAD))
            road_dir_right = true;
        road_dir_right = city_view_relative_orientation(road_dir_right) % 2;
        bool is_paved = map_tiles_is_paved_road(grid_offset);

        switch (GAME_ENV) {
        case ENGINE_ENV_PHARAOH:
            if (road_dir_right) // left/right offset is opposite from C3
                image_offset = 0;
            else
                image_offset = 1;
            if (is_paved) {
                floodplains_offset = 0; // no floodplains version for paved roads
                image_offset += 42;
            } else
                image_offset += 15;
        }
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        if (image_offset <= 3)
            image_offset = !(image_offset - 2);
        else if (image_offset <= 7)
            image_offset -= 2;
    }
    // TODO: canals disappearing into the Nile river --- good luck with that!
    return image_id_from_group(GROUP_BUILDING_AQUEDUCT) + water_offset + floodplains_offset + image_offset;
}
static void set_aqueduct_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_AQUEDUCT) && !map_terrain_is(grid_offset, TERRAIN_WATER)) {
        const terrain_image* img = map_image_context_get_aqueduct(grid_offset);
        bool is_road = map_terrain_is(grid_offset, TERRAIN_ROAD);
        if (is_road)
            map_property_clear_plaza_or_earthquake(grid_offset);

        int image_id = get_aqueduct_image(grid_offset, is_road, 0, img);
        if (image_id) {
            map_image_set(grid_offset, image_id);
            map_property_set_multi_tile_size(grid_offset, 1);
            map_property_mark_draw_tile(grid_offset);
        }

        map_aqueduct_set(grid_offset, img->aqueduct_offset);
    }
}
void map_tiles_update_all_aqueducts(int include_construction) {
    aqueduct_include_construction = include_construction;
    foreach_map_tile(set_aqueduct_image);
    aqueduct_include_construction = 0;
}
void map_tiles_update_region_aqueducts(int x_min, int y_min, int x_max, int y_max) {
    foreach_region_tile(x_min, y_min, x_max, y_max, set_aqueduct_image);
}
int map_tiles_set_aqueduct(int x, int y) {
    int grid_offset = MAP_OFFSET(x, y);
    int tile_set = 0;
    if (!map_terrain_is(grid_offset, TERRAIN_AQUEDUCT))
        tile_set = 1;
    map_terrain_add(grid_offset, TERRAIN_AQUEDUCT);
    map_property_clear_constructing(grid_offset);

    foreach_region_tile(x - 1, y - 1, x + 1, y + 1, set_aqueduct_image);
    return tile_set;
}

int map_tiles_is_paved_road(int grid_offset) {
    int desirability = map_desirability_get(grid_offset);
    if (desirability > 4)
        return 1;

    if (desirability > 0 && map_terrain_is(grid_offset, TERRAIN_FOUNTAIN_RANGE))
        return 1;

    return 0;
}
static void set_road_image(int grid_offset) {
    if (!map_terrain_is(grid_offset, TERRAIN_ROAD)
        || map_terrain_is(grid_offset, TERRAIN_WATER)
        || map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
        return;
    }

    if (map_terrain_is(grid_offset, TERRAIN_AQUEDUCT)) {
        set_aqueduct_image(grid_offset);
        return;
    }

    if (map_property_is_plaza_or_earthquake(grid_offset)) {
        return;
    }

    if (map_tiles_is_paved_road(grid_offset)) {
        const terrain_image* img = map_image_context_get_paved_road(grid_offset);
        map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_ROAD) + img->group_offset + img->item_offset);
    } else {
        const terrain_image* img = map_image_context_get_dirt_road(grid_offset);
        if (!map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
            if (map_terrain_is(grid_offset + GRID_OFFSET(0, -1), TERRAIN_FLOODPLAIN)) {
                map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_FLOODPLAIN) + 84);
            } else if (map_terrain_is(grid_offset + GRID_OFFSET(1, 0), TERRAIN_FLOODPLAIN)) {
                map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_FLOODPLAIN) + 85);
            } else if (map_terrain_is(grid_offset + GRID_OFFSET(0, 1), TERRAIN_FLOODPLAIN)) {
                map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_FLOODPLAIN) + 86);
            } else if (map_terrain_is(grid_offset + GRID_OFFSET(-1, 0), TERRAIN_FLOODPLAIN)) {
                map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_FLOODPLAIN) + 87);
            } else {
                map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_ROAD) + img->group_offset + img->item_offset + 49);
            }
        } else {
            map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_ROAD) + img->group_offset + img->item_offset + 49 + 344);
        }
    }
    map_property_set_multi_tile_size(grid_offset, 1);
    map_property_mark_draw_tile(grid_offset);
}
void map_tiles_update_all_roads(void) {
    foreach_map_tile(set_road_image);
}
void map_tiles_update_area_roads(int x, int y, int size) {
    foreach_region_tile(x - 1, y - 1, x + size - 2, y + size - 2, set_road_image);
}
int map_tiles_set_road(int x, int y) {
    int grid_offset = MAP_OFFSET(x, y);
    int tile_set = 0;
    if (!map_terrain_is(grid_offset, TERRAIN_ROAD))
        tile_set = 1;

    map_terrain_add(grid_offset, TERRAIN_ROAD);
    map_property_clear_constructing(grid_offset);

    foreach_region_tile(x - 1, y - 1, x + 1, y + 1, set_road_image);
    return tile_set;
}

static void set_meadow_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_MEADOW) && !map_terrain_is(grid_offset, FORBIDDEN_TERRAIN_MEADOW)) {
        int ph_grass = map_grasslevel_get(grid_offset);
        int meadow_density = 0;
        if (map_get_fertility(grid_offset, FERT_WITH_MALUS) > 70)
            meadow_density = 2;
        else if (map_get_fertility(grid_offset, FERT_WITH_MALUS) > 40)
            meadow_density = 1;

        int random = map_random_get(grid_offset) % 8;
        if (ph_grass == 0) { // for no grass at all
            if (meadow_density == 2)
                map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_MEADOW_STATIC_INNER) + random);
            else if (meadow_density == 0)
                map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_MEADOW_STATIC_OUTER) + random);
            else
                map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_MEADOW_WITH_GRASS) + 12);
        } else if (ph_grass == 12) { // for fully grown grass
            if (meadow_density == 2)
                map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_MEADOW_STATIC_TALLGRASS) + random);
            else
                map_image_set(grid_offset,
                              image_id_from_group(GROUP_TERRAIN_MEADOW_WITH_GRASS) + 12 * meadow_density + ph_grass
                                - 1);
        } else // for grass transitions
            map_image_set(grid_offset,
                          image_id_from_group(GROUP_TERRAIN_MEADOW_WITH_GRASS) + 12 * meadow_density + ph_grass - 1);

        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
        map_aqueduct_set(grid_offset, 0);
    }
}
void map_tiles_update_all_meadow(void) {
    foreach_map_tile(set_meadow_image);
}
void map_tiles_update_region_meadow(int x_min, int y_min, int x_max, int y_max) {
    foreach_region_tile(x_min, y_min, x_max, y_max, set_meadow_image);
}

static void update_marshland_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_MARSHLAND)) { // there's no way to build anything on reed tiles, so... it's fine?
        const terrain_image* img = map_image_context_get_reeds_transition(grid_offset);
        int image_id = image_id_from_group(GROUP_TERRAIN_REEDS) + 8 + img->group_offset + img->item_offset;

        if (!img->is_valid) { // if not edge, then it's a full reeds tile
            if (map_get_vegetation_growth(grid_offset) == 255)
                image_id = image_id_from_group(GROUP_TERRAIN_REEDS_GROWN) + (map_random_get(grid_offset) & 7);
            else
                image_id = image_id_from_group(GROUP_TERRAIN_REEDS) + (map_random_get(grid_offset) & 7);
        }
        return map_image_set(grid_offset, image_id);
    }
}
void map_tiles_update_vegetation(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_MARSHLAND)) {
        return update_marshland_image(grid_offset);
    } else if (map_terrain_is(grid_offset, TERRAIN_TREE)) {
        return update_tree_image(grid_offset);
    }
}
void map_tiles_update_all_vegetation_tiles() {
    foreach_marshland_tile(update_marshland_image);
    foreach_tree_tile(update_tree_image);
}

#include "game/time.h"
#include "water.h"

// the x and y are all GRID COORDS, not PIXEL COORDS
static void set_water_image(int grid_offset) {
    const terrain_image* img = map_image_context_get_shore(grid_offset);
    int image_id = image_id_from_group(GROUP_TERRAIN_WATER) + img->group_offset + img->item_offset;
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    if (GAME_ENV == ENGINE_ENV_C3 && map_terrain_exists_tile_in_radius_with_type(x, y, 1, 2, TERRAIN_BUILDING)) {
        // fortified shore
        int base = image_id_from_group(GROUP_TERRAIN_WATER_SHORE);
        switch (img->group_offset) {
        case 8:
            image_id = base + 10;
            break;
        case 12:
            image_id = base + 11;
            break;
        case 16:
            image_id = base + 9;
            break;
        case 20:
            image_id = base + 8;
            break;
        case 24:
            image_id = base + 18;
            break;
        case 28:
            image_id = base + 16;
            break;
        case 32:
            image_id = base + 19;
            break;
        case 36:
            image_id = base + 17;
            break;
        case 50:
            image_id = base + 12;
            break;
        case 51:
            image_id = base + 14;
            break;
        case 52:
            image_id = base + 13;
            break;
        case 53:
            image_id = base + 15;
            break;
        }
    }
    if (map_terrain_exists_tile_in_radius_with_type(x, y, 1, 1, TERRAIN_FLOODPLAIN)
        && map_terrain_exists_tile_in_radius_with_exact(x, y, 1, 1, TERRAIN_GROUNDWATER)) {
        return;
    }
    map_image_set(grid_offset, image_id);
    map_property_set_multi_tile_size(grid_offset, 1);
    map_property_mark_draw_tile(grid_offset);
}
static void set_deepwater_image(int grid_offset) {
    const terrain_image* img = map_image_context_get_river(grid_offset);
    int image_id = image_id_from_group(GROUP_TERRAIN_DEEPWATER) + img->group_offset + img->item_offset;
    map_image_set(grid_offset, image_id);
    map_property_set_multi_tile_size(grid_offset, 1);
    map_property_mark_draw_tile(grid_offset);
}
static void set_river_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_WATER) && !map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
        set_water_image(grid_offset);
    }

    if (map_terrain_is(grid_offset, TERRAIN_DEEPWATER)) {
        set_deepwater_image(grid_offset);
    }
}
static void set_floodplain_edges_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_BUILDING)
        || (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN) && !map_terrain_is(grid_offset, TERRAIN_WATER))) { // non-flooded floodplain, skip
        return;
    }

    int image_id = 0;
    if (!map_terrain_is(grid_offset, TERRAIN_WATER)) { // NOT floodplain, but not water either -- dry land shoreline
        if (map_terrain_is(grid_offset, TERRAIN_ROAD))
            return;
        const terrain_image* img
          = map_image_context_get_floodplain_shore(grid_offset); // this checks against FLOODPLAIN tiles
        image_id = image_id_from_group(GROUP_TERRAIN_FLOODPLAIN) + 48 + img->group_offset + img->item_offset;
    } else { // floodplain which is ALSO flooded --  this is a waterline
        const terrain_image* img
          = map_image_context_get_floodplain_waterline(grid_offset); // this checks against WATER tiles
        image_id = image_id_from_group(GROUP_TERRAIN_FLOODSYSTEM) + 209 + img->group_offset + img->item_offset;
        if (!img->is_valid) // else, normal water tile
            image_id = 0;
        //            image_id = image_id_from_group(GROUP_TERRAIN_BLACK); // temp

        //        if (map_terrain_is(grid_offset, TERRAIN_GROUNDWATER)) {
        //            if (map_terrain_get(grid_offset - 1) == TERRAIN_GROUNDWATER ||
        //                map_terrain_get(grid_offset + 1) == TERRAIN_GROUNDWATER ||
        //                map_terrain_get(grid_offset - 228) == TERRAIN_GROUNDWATER ||
        //                map_terrain_get(grid_offset + 228) == TERRAIN_GROUNDWATER)
        //            image_id = 0;
        //        }
    }
    if (image_id) {
        map_image_set(grid_offset, image_id);
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
}
static void set_floodplain_land_tiles_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN) && !map_terrain_is(grid_offset, TERRAIN_WATER)
        && !map_terrain_is(grid_offset, TERRAIN_BUILDING) && !map_terrain_is(grid_offset, TERRAIN_ROAD)
        && !map_terrain_is(grid_offset, TERRAIN_AQUEDUCT)) {
        int growth = map_get_floodplain_growth(grid_offset);
        int image_id = image_id_from_group(GROUP_TERRAIN_FLOODPLAIN) + growth;
        int fertility_index = 0;

        int fertility_value = map_get_fertility(grid_offset, FERT_WITH_MALUS); // todo
        if (true) {
            if (fertility_value < 25)
                fertility_index = 0;
            else if (fertility_value < 50)
                fertility_index = 1;
            else if (fertility_value < 75)
                fertility_index = 2;
            else
                fertility_index = 3;
            image_id += 12 * fertility_index;
            if (map_property_is_alternate_terrain(grid_offset) && fertility_index < 7)
                image_id += 6;
        } else {
            // smoother transition...?
        }
        map_image_set(grid_offset, image_id);
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
}

static void set_river_3x3_tiles(int grid_offset) {
    map_point point = map_point(grid_offset);
    int x = point.x();
    int y = point.y();
    foreach_region_tile(x - 1, y - 1, x + 1, y + 1, set_river_image);
}
static void set_floodplain_edge_3x3_tiles(int grid_offset) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN))
        foreach_region_tile(x - 1, y - 1, x + 1, y + 1, set_floodplain_edges_image);
}

void map_refresh_river_image_at(int grid_offset) {
    set_river_3x3_tiles(grid_offset);
    set_floodplain_edge_3x3_tiles(grid_offset);
    set_floodplain_land_tiles_image(grid_offset);
    set_road_image(grid_offset);
    set_aqueduct_image(grid_offset);
}
void map_tiles_river_refresh_entire(void) {
    //    return;
    foreach_river_tile(set_river_3x3_tiles);
    foreach_river_tile(set_floodplain_edge_3x3_tiles);
    foreach_river_tile(set_floodplain_land_tiles_image);
}
void map_tiles_river_refresh_region(int x_min, int y_min, int x_max, int y_max) {
    foreach_region_tile(x_min, y_min, x_max, y_max, set_river_3x3_tiles);
    foreach_region_tile(x_min, y_min, x_max, y_max, set_floodplain_edge_3x3_tiles);
    foreach_region_tile(x_min, y_min, x_max, y_max, set_floodplain_land_tiles_image);
}
void map_tiles_set_water(int grid_offset) { // todo: broken
    map_terrain_add(grid_offset, TERRAIN_WATER);
    map_refresh_river_image_at(grid_offset);
    //    set_water_image(x, y, map_grid_offset(x, y));
    //    foreach_region_tile(x - 1, y - 1, x + 1, y + 1, set_water_image);
}

#define PH_FLOODPLAIN_GROWTH_MAX 6
int floodplain_growth_advance = 0;
static void advance_floodplain_growth_tile(int grid_offset, int order) {
    if (map_terrain_is(grid_offset, TERRAIN_WATER) || map_terrain_is(grid_offset, TERRAIN_BUILDING)
        || map_terrain_is(grid_offset, TERRAIN_ROAD) || map_terrain_is(grid_offset, TERRAIN_AQUEDUCT)) {
        map_set_floodplain_growth(grid_offset, 0);
        set_floodplain_land_tiles_image(grid_offset);
        map_refresh_river_image_at(grid_offset);
        return;
    }
    int growth_current = map_get_floodplain_growth(grid_offset);
    if (growth_current < PH_FLOODPLAIN_GROWTH_MAX - 1) {
        map_set_floodplain_growth(grid_offset, growth_current + 1);
        set_floodplain_land_tiles_image(grid_offset);
        map_refresh_river_image_at(grid_offset);
    }
}
void map_advance_floodplain_growth() {
    // do groups of 12 rows at a time. every 12 cycle, do another pass over them.
    foreach_floodplain_row(0 + floodplain_growth_advance, advance_floodplain_growth_tile);
    foreach_floodplain_row(12 + floodplain_growth_advance, advance_floodplain_growth_tile);
    foreach_floodplain_row(24 + floodplain_growth_advance, advance_floodplain_growth_tile);

    floodplain_growth_advance++;
    if (floodplain_growth_advance >= 12) {
        floodplain_growth_advance = 0;
    }
}

int floodplain_is_flooding = 0;
static void floodplain_update_inundation_row(int grid_offset, int order) {
    // TODO: I can not find the way the OG game determines which tile to update.
    //  I know it's deterministic, so I just used the random grid for now.
    int randm = map_random_get(grid_offset);
    int ticks = floods_fticks();
    int local_tick_bound = calc_bound(ticks - order * 25, 0, 25);
    bool flooded = randm % 25 < local_tick_bound;

    int b_id = map_building_at(grid_offset);
    building* b = building_get(b_id);

    // tile is updating!
    if (flooded != map_terrain_is(grid_offset, TERRAIN_WATER)) {
        // tile is FLOODING
        if (floodplain_is_flooding == 1) {
            map_terrain_add(grid_offset, TERRAIN_WATER);

            map_soil_set_depletion(grid_offset, 0);

            // hide / destroy farm
            if (b_id && b->state == BUILDING_STATE_VALID && map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
                if (city_data.religion.osiris_flood_will_destroy_active > 0) { // destroy farm
                    building* b = building_get(b_id);
                    building_farm_deplete_soil(b);
                    building_destroy_by_poof(b, true);
                    city_data.religion.osiris_flood_will_destroy_active = 2;
                    for (int _y = b->tile.y(); _y < b->tile.y() + b->size; _y++)
                        for (int _x = b->tile.x(); _x < b->tile.x() + b->size; _x++) {
                            int _offset = MAP_OFFSET(_x, _y);
                            map_soil_set_depletion(_offset, -65);
                            map_terrain_remove(_offset, TERRAIN_BUILDING);
                            //                            map_property_set_multi_tile_size(_offset, 1);
                            map_refresh_river_image_at(_offset);
                        }
                } else { // hide building by unsetting the TERRAIN_BUILDING bitflag
                    b->data.industry.progress = 0;
                    b->data.industry.labor_state = LABOR_STATE_NONE;
                    b->data.industry.labor_days_left = 0;
                    for (int _y = b->tile.y(); _y < b->tile.y() + b->size; _y++)
                        for (int _x = b->tile.x(); _x < b->tile.x() + b->size; _x++) {
                            int _offset = MAP_OFFSET(_x, _y);
                            map_terrain_remove(_offset, TERRAIN_BUILDING);
                            map_property_set_multi_tile_size(_offset, 1);
                            map_refresh_river_image_at(_offset);
                        }
                }
            }

            // flood roads
            if (map_terrain_is(grid_offset, TERRAIN_ROAD)) {
                map_terrain_remove(grid_offset, TERRAIN_ROAD);
                map_terrain_add(grid_offset, TERRAIN_SUBMERGED_ROAD);
            }
        }
        // tile is RESURFACING
        else if (floodplain_is_flooding == -1) {
            map_terrain_remove(grid_offset, TERRAIN_WATER);

            // bring back flooded buildings
            if (b_id && b->state == BUILDING_STATE_VALID && !map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
                // check if any other tile of the farm is still submerged
                bool still_flooded = false;
                for (int _y = b->tile.y(); _y < b->tile.y() + b->size; _y++) {
                    for (int _x = b->tile.x(); _x < b->tile.x() + b->size; _x++) {
                        if (map_terrain_is(MAP_OFFSET(_x, _y), TERRAIN_WATER)) {
                            still_flooded = true;
                        }
                    }
                }

                if (!still_flooded) {
                    map_building_tiles_add_farm(b_id, b->tile.x(), b->tile.y(), 0, 0);
                }
            }

            // resurface roads
            if (map_terrain_is(grid_offset, TERRAIN_SUBMERGED_ROAD)) {
                map_terrain_remove(grid_offset, TERRAIN_SUBMERGED_ROAD);
                map_terrain_add(grid_offset, TERRAIN_ROAD);
            }
        }
        map_refresh_river_image_at(grid_offset);
    }
}
void map_update_floodplain_inundation(int leading_row, int is_flooding, int flooding_ticks) {
    floodplain_is_flooding = is_flooding;
    if (floodplain_is_flooding == 0)
        return;
    // no need to update every single row -- only update the "leading" shore
    foreach_floodplain_row(29 - leading_row, floodplain_update_inundation_row);
}

static void set_earthquake_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_ROCK) && map_property_is_plaza_or_earthquake(grid_offset)) {
        const terrain_image* img = map_image_context_get_earthquake(grid_offset);
        if (img->is_valid) {
            map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_EARTHQUAKE) + img->group_offset + img->item_offset);
        } else {
            map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_EARTHQUAKE));
        }
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
}
static void update_earthquake_tile(int grid_offset) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    if (map_terrain_is(grid_offset, TERRAIN_ROCK) && map_property_is_plaza_or_earthquake(grid_offset)) {
        map_terrain_add(grid_offset, TERRAIN_ROCK);
        map_property_mark_plaza_or_earthquake(grid_offset);
        foreach_region_tile(x - 1, y - 1, x + 1, y + 1, set_earthquake_image);
    }
}
void map_tiles_update_all_earthquake(void) {
    foreach_map_tile(update_earthquake_tile);
}
void map_tiles_set_earthquake(int x, int y) {
    int grid_offset = MAP_OFFSET(x, y);
    // earthquake: terrain = rock && bitfields = plaza
    map_terrain_add(grid_offset, TERRAIN_ROCK);
    map_property_mark_plaza_or_earthquake(grid_offset);

    foreach_region_tile(x - 1, y - 1, x + 1, y + 1, set_earthquake_image);
}

static void set_rubble_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_RUBBLE) && !map_terrain_is(grid_offset, FORBIDDEN_TERRAIN_RUBBLE)) {
        map_image_set(grid_offset, image_id_from_group(GROUP_TERRAIN_RUBBLE) + (map_random_get(grid_offset) & 7));
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
        map_aqueduct_set(grid_offset, 0);
    }
}
void map_tiles_update_all_rubble(void) {
    foreach_map_tile(set_rubble_image);
}
void map_tiles_update_region_rubble(int x_min, int y_min, int x_max, int y_max) {
    foreach_region_tile(x_min, y_min, x_max, y_max, set_rubble_image);
}

static void clear_access_ramp_image(int grid_offset) {
    if (map_terrain_is(grid_offset, TERRAIN_ACCESS_RAMP))
        map_image_set(grid_offset, 0);
}

static const int offsets_PH[4][6] = {
  {GRID_OFFSET(0, 1), GRID_OFFSET(1, 1), GRID_OFFSET(0, 0), GRID_OFFSET(1, 0), GRID_OFFSET(0, 2), GRID_OFFSET(1, 2)},
  {GRID_OFFSET(0, 0), GRID_OFFSET(0, 1), GRID_OFFSET(1, 0), GRID_OFFSET(1, 1), GRID_OFFSET(-1, 0), GRID_OFFSET(-1, 1)},
  {GRID_OFFSET(0, 0), GRID_OFFSET(1, 0), GRID_OFFSET(0, 1), GRID_OFFSET(1, 1), GRID_OFFSET(0, -1), GRID_OFFSET(1, -1)},
  {GRID_OFFSET(1, 0), GRID_OFFSET(1, 1), GRID_OFFSET(0, 0), GRID_OFFSET(0, 1), GRID_OFFSET(2, 0), GRID_OFFSET(2, 1)},
};

static int get_access_ramp_image_offset(int x, int y) {
    if (!map_grid_is_inside(x, y, 1))
        return -1;

    int base_offset = MAP_OFFSET(x, y);
    int image_offset = -1;
    for (int dir = 0; dir < 4; dir++) {
        int right_tiles = 0;
        int height = -1;
        for (int i = 0; i < 6; i++) {
            int grid_offset = base_offset;

            switch (GAME_ENV) {
            case ENGINE_ENV_PHARAOH:
                grid_offset += offsets_PH[dir][i];
                break;
            }

            if (i < 2) { // 2nd row
                if (map_terrain_is(grid_offset, TERRAIN_ELEVATION))
                    right_tiles++;

                height = map_elevation_at(grid_offset);
            } else if (i < 4) { // 1st row
                if (map_terrain_is(grid_offset, TERRAIN_ACCESS_RAMP) && map_elevation_at(grid_offset) < height) {
                    right_tiles++;
                }
            } else { // higher row beyond access ramp
                if (map_terrain_is(grid_offset, TERRAIN_ELEVATION)) {
                    if (map_elevation_at(grid_offset) != height)
                        right_tiles++;

                } else if (map_elevation_at(grid_offset) >= height)
                    right_tiles++;
            }
        }
        if (right_tiles == 6) {
            image_offset = dir;
            break;
        }
    }
    if (image_offset < 0)
        return -1;

    switch (city_view_orientation()) {
    case DIR_0_TOP_RIGHT:
        break;
    case DIR_6_TOP_LEFT:
        image_offset += 1;
        break;
    case DIR_4_BOTTOM_LEFT:
        image_offset += 2;
        break;
    case DIR_2_BOTTOM_RIGHT:
        image_offset += 3;
        break;
    }
    if (image_offset >= 4)
        image_offset -= 4;

    return image_offset;
}
// static void set_elevation_aqueduct_image(int grid_offset) {
//     if (map_aqueduct_at(grid_offset) <= 15 && !map_terrain_is(grid_offset, TERRAIN_BUILDING))
//         set_aqueduct_image(grid_offset);
// }
static void set_elevation_image(int grid_offset) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    if (map_terrain_is(grid_offset, TERRAIN_ACCESS_RAMP) && !map_image_at(grid_offset)) {
        int image_offset = get_access_ramp_image_offset(x, y);
        if (image_offset < 0) {
            // invalid map: remove access ramp
            map_terrain_remove(grid_offset, TERRAIN_ACCESS_RAMP);
            map_property_set_multi_tile_size(grid_offset, 1);
            map_property_mark_draw_tile(grid_offset);
            if (map_elevation_at(grid_offset))
                map_terrain_add(grid_offset, TERRAIN_ELEVATION);
            else {
                map_terrain_remove(grid_offset, TERRAIN_ELEVATION);
                map_image_set(grid_offset,
                              image_id_from_group(GROUP_TERRAIN_EMPTY_LAND) + (map_random_get(grid_offset) & 7));
            }
        } else {
            map_building_tiles_add(
              0, x, y, 2, image_id_from_group(GROUP_TERRAIN_ACCESS_RAMP) + image_offset, TERRAIN_ACCESS_RAMP);
        }
    }
    if (map_elevation_at(grid_offset) && !map_terrain_is(grid_offset, TERRAIN_ACCESS_RAMP)) {
        const terrain_image* img = map_image_context_get_elevation(grid_offset, map_elevation_at(grid_offset));
        if (img->group_offset == 44) {
            map_terrain_remove(grid_offset, TERRAIN_ELEVATION);
            int terrain = map_terrain_get(grid_offset);
            if (!(terrain & TERRAIN_BUILDING)) {
                map_property_set_multi_tile_xy(grid_offset, 0, 0, 1);
                if (terrain & TERRAIN_SHRUB) {
                    map_image_set(grid_offset,
                                  image_id_from_group(GROUP_TERRAIN_SHRUB) + (map_random_get(grid_offset) & 7));
                } else if (terrain & TERRAIN_TREE) {
                    map_image_set(grid_offset,
                                  image_id_from_group(GROUP_TERRAIN_TREE) + (map_random_get(grid_offset) & 7));
                } else if (terrain & TERRAIN_ROAD)
                    map_tiles_set_road(x, y);
                //                else if (terrain & TERRAIN_AQUEDUCT)
                //                    set_elevation_aqueduct_image(grid_offset);
                else if (terrain & TERRAIN_MEADOW)
                    map_image_set(grid_offset,
                                  image_id_from_group(GROUP_TERRAIN_MEADOW_STATIC_OUTER)
                                    + (map_random_get(grid_offset) & 3));
                else
                    map_image_set(grid_offset,
                                  image_id_from_group(GROUP_TERRAIN_EMPTY_LAND) + (map_random_get(grid_offset) & 7));
            }
        } else {
            map_property_set_multi_tile_xy(grid_offset, 0, 0, 1);
            map_terrain_add(grid_offset, TERRAIN_ELEVATION);
            map_image_set(grid_offset,
                          image_id_from_group(GROUP_TERRAIN_ELEVATION) + img->group_offset + img->item_offset);
        }
    }
}
void map_tiles_update_all_elevation(void) {
    int width = scenario_map_data()->width - 2;
    int height = scenario_map_data()->height - 2;
    foreach_region_tile(0, 0, width, height, clear_access_ramp_image);
    foreach_region_tile(0, 0, width, height, set_elevation_image);
}

void map_tiles_add_entry_exit_flags(void) {
    int entry_orientation;
    map_point entry_point = scenario_map_entry();
    if (entry_point.x() == 0)
        entry_orientation = DIR_2_BOTTOM_RIGHT;
    else if (entry_point.x() == scenario_map_data()->width - 1)
        entry_orientation = DIR_6_TOP_LEFT;
    else if (entry_point.y() == 0)
        entry_orientation = DIR_0_TOP_RIGHT;
    else if (entry_point.y() == scenario_map_data()->height - 1)
        entry_orientation = DIR_4_BOTTOM_LEFT;
    else
        entry_orientation = -1;
    int exit_orientation;
    map_point exit_point = scenario_map_exit();
    if (exit_point.x() == 0)
        exit_orientation = DIR_2_BOTTOM_RIGHT;
    else if (exit_point.x() == scenario_map_data()->width - 1)
        exit_orientation = DIR_6_TOP_LEFT;
    else if (exit_point.y() == 0)
        exit_orientation = DIR_0_TOP_RIGHT;
    else if (exit_point.y() == scenario_map_data()->height - 1)
        exit_orientation = DIR_4_BOTTOM_LEFT;
    else
        exit_orientation = -1;
    if (entry_orientation >= 0) {
        int grid_offset = MAP_OFFSET(entry_point.x(), entry_point.y());
        int x_tile, y_tile;
        for (int i = 1; i < 10; i++) {
            if (map_terrain_exists_clear_tile_in_radius(
                  entry_point.x(), entry_point.y(), 1, i, grid_offset, &x_tile, &y_tile)) {
                break;
            }
        }
        int grid_offset_flag = city_map_set_entry_flag(x_tile, y_tile);
        map_terrain_add(grid_offset_flag, TERRAIN_ROCK);
        int orientation = (city_view_orientation() + entry_orientation) % 8;
        map_image_set(grid_offset_flag, image_id_from_group(GROUP_TERRAIN_ENTRY_EXIT_FLAGS) + orientation / 2);
    }
    if (exit_orientation >= 0) {
        int grid_offset = MAP_OFFSET(exit_point.x(), exit_point.y());
        int x_tile, y_tile;
        for (int i = 1; i < 10; i++) {
            if (map_terrain_exists_clear_tile_in_radius(
                  exit_point.x(), exit_point.y(), 1, i, grid_offset, &x_tile, &y_tile)) {
                break;
            }
        }
        int grid_offset_flag = city_map_set_exit_flag(x_tile, y_tile);
        map_terrain_add(grid_offset_flag, TERRAIN_ROCK);
        int orientation = (city_view_orientation() + exit_orientation) % 8;
        map_image_set(grid_offset_flag, image_id_from_group(GROUP_TERRAIN_ENTRY_EXIT_FLAGS) + 4 + orientation / 2);
    }
}
static void remove_entry_exit_flag(map_point& tile) {
    // re-calculate grid_offset_figure because the stored offset might be invalid
    map_terrain_remove(MAP_OFFSET(tile.x(), tile.y()), TERRAIN_ROCK);
}
void map_tiles_remove_entry_exit_flags(void) {
    remove_entry_exit_flag(city_map_entry_flag());
    remove_entry_exit_flag(city_map_exit_flag());
}

static bool map_has_nonfull_grassland_in_radius(int x, int y, int size, int radius, int terrain) {
    int x_min, y_min, x_max, y_max;
    map_grid_get_area(x, y, size, radius, &x_min, &y_min, &x_max, &y_max);

    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            if (map_grasslevel_get(MAP_OFFSET(xx, yy)) < 12)
                return true;
        }
    }
    return false;
}

static void clear_empty_land_image(int grid_offset) {
    if (!map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR)) {
        map_image_set(grid_offset, 0);
        map_property_set_multi_tile_size(grid_offset, 1);
        map_property_mark_draw_tile(grid_offset);
    }
    if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN) && !map_terrain_is(grid_offset, TERRAIN_WATER))
        set_floodplain_land_tiles_image(grid_offset);
    else if (map_terrain_exists_tile_in_radius_with_type(
               MAP_X(grid_offset), MAP_Y(grid_offset), 1, 1, TERRAIN_FLOODPLAIN))
        set_floodplain_edges_image(grid_offset);
}
static void set_empty_land_image(int grid_offset, int size, int image_id) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    if (!map_grid_is_inside(x, y, size))
        return;
    int index = 0;
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = MAP_OFFSET(x + dx, y + dy);
            map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
            map_building_set(grid_offset, 0);
            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, 1);
            map_property_mark_draw_tile(grid_offset);
            map_image_set(grid_offset, image_id + index);
            index++;
        }
    }
}
static void set_empty_land_pass1(int grid_offset) {
    // first pass: clear land with no grass
    if (!map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR) && !map_image_at(grid_offset)) {
        int image_id;
        if (map_property_is_alternate_terrain(grid_offset))
            image_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND_ALT);
        else
            image_id = image_id_from_group(GROUP_TERRAIN_EMPTY_LAND);
        if (is_clear(grid_offset, 4, TERRAIN_ALL, 1))
            set_empty_land_image(grid_offset, 4, image_id + 42);
        else if (is_clear(grid_offset, 3, TERRAIN_ALL, 1))
            set_empty_land_image(grid_offset, 3, image_id + 24 + 9 * (map_random_get(grid_offset) & 1));
        else if (is_clear(grid_offset, 2, TERRAIN_ALL, 1))
            set_empty_land_image(grid_offset, 2, image_id + 8 + 4 * (map_random_get(grid_offset) & 3));
        else
            set_empty_land_image(grid_offset, 1, image_id + (map_random_get(grid_offset) & 7));
    }
}
static void set_empty_land_pass2(int grid_offset) {
    int x = MAP_X(grid_offset);
    int y = MAP_Y(grid_offset);
    // second pass:
    int ph_grass = map_grasslevel_get(grid_offset);
    if (!map_terrain_is(grid_offset, TERRAIN_NOT_CLEAR + TERRAIN_MEADOW) && ph_grass >= 0) {
        int image_base = image_id_from_group(GROUP_TERRAIN_GRASS_PH);
        if (ph_grass && ph_grass <= 11)
            return set_empty_land_image(grid_offset,
                                        1,
                                        image_base + ph_grass - 1 + 12 * (map_random_get(grid_offset) % 3));
        else if (ph_grass == 12) {
            // check for non-clear terrain tiles in a radius around it
            int closest_radius_not_fullgrass = 3;
            if (map_terrain_exists_tile_in_radius_with_type(x, y, 1, 1, TERRAIN_NOT_CLEAR + TERRAIN_MEADOW))
                closest_radius_not_fullgrass = 1;
            else if (map_terrain_exists_tile_in_radius_with_type(x, y, 1, 2, TERRAIN_NOT_CLEAR + TERRAIN_MEADOW)
                     || map_has_nonfull_grassland_in_radius(
                       x, y, 1, 1, TERRAIN_NOT_CLEAR + TERRAIN_MEADOW)) // for lower grass level transition
                closest_radius_not_fullgrass = 2;

            switch (closest_radius_not_fullgrass) {
            case 1: // one tile of distance
                return set_empty_land_image(grid_offset, 1, image_base + 36 + (map_random_get(grid_offset) % 12));
            case 2: // two tiles of distance
                return set_empty_land_image(grid_offset, 1, image_base + 60 + (map_random_get(grid_offset) % 12));
            default: // any other distance
                return set_empty_land_image(grid_offset,
                                            1,
                                            image_base + 48 + (map_random_get(grid_offset) % 12)); // flat tiles
            }

        } else if (ph_grass >= 16) { // edges have special ids

            // todo: this doesn't work yet.....
            //            const terrain_image *img = map_image_context_get_grass_corners(grid_offset);
            //            if (img->is_valid) {
            //                int image_id = image_id_from_group(GROUP_TERRAIN_GRASS_PH_EDGES) + img->group_offset +
            //                img->item_offset; return set_empty_land_image(grid_offset, 1, image_id);
            //            }
            //            else
            //                return set_empty_land_image(grid_offset, 1, image_id_from_group(GROUP_TERRAIN_BLACK));

            // correct for city orientation the janky, hardcoded, but at least working way
            int tr_offset = ph_grass - 16;
            int orientation = city_view_orientation();
            if (tr_offset < 8) {
                if (tr_offset % 2 == 0) {
                    tr_offset -= orientation;
                    if (tr_offset < 0)
                        tr_offset += 8;
                } else {
                    tr_offset -= orientation;
                    if (tr_offset < 1)
                        tr_offset += 8;
                }
            } else {
                tr_offset -= orientation / 2;
                if (tr_offset < 8)
                    tr_offset += 4;
            }
            return set_empty_land_image(grid_offset, 1, image_id_from_group(GROUP_TERRAIN_GRASS_PH_EDGES) + tr_offset);
        }
    }
}

void map_tiles_update_all_cleared_land() {
    foreach_map_tile(clear_empty_land_image);
}

void map_tiles_update_all_empty_land() {
    // foreach_map_tile(clear_empty_land_image);
    foreach_map_tile(set_empty_land_pass1);
    foreach_map_tile(set_empty_land_pass2);
    foreach_map_tile(set_floodplain_edge_3x3_tiles);
}
void map_tiles_update_region_empty_land(bool clear, int x_min, int y_min, int x_max, int y_max) {
    if (clear)
        foreach_region_tile(x_min, y_min, x_max, y_max, clear_empty_land_image);
    foreach_region_tile(x_min, y_min, x_max, y_max, set_empty_land_pass1);
    foreach_region_tile(x_min, y_min, x_max, y_max, set_empty_land_pass2);
    foreach_region_tile(x_min - 1, y_min - 1, x_max + 1, y_max + 1, set_floodplain_edge_3x3_tiles);
}

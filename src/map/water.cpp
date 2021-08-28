#include "water.h"

#include "building/building.h"
#include "city/view.h"
#include "map/building.h"
#include "map/figure.h"
#include "map/grid.h"
#include "map/image.h"
#include "map/point.h"
#include "map/property.h"
#include "map/terrain.h"

void map_water_add_building(int building_id, int x, int y, int size, int image_id) {
    if (!map_grid_is_inside(x, y, size))
        return;
    map_point leftmost;
    switch (city_view_orientation()) {
        case DIR_0_TOP_RIGHT:
            leftmost.x = 0;
            leftmost.y = size - 1;
            break;
        case DIR_2_BOTTOM_RIGHT:
            leftmost.x = leftmost.y = 0;
            break;
        case DIR_4_BOTTOM_LEFT:
            leftmost.x = size - 1;
            leftmost.y = 0;
            break;
        case DIR_6_TOP_LEFT:
            leftmost.x = leftmost.y = size - 1;
            break;
        default:
            return;
    }
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = map_grid_offset(x + dx, y + dy);
            map_terrain_add(grid_offset, TERRAIN_BUILDING);
            if (!map_terrain_is(grid_offset, TERRAIN_WATER)) {
                map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
                map_terrain_add(grid_offset, TERRAIN_BUILDING);
            }
            map_building_set(grid_offset, building_id);
            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, size);
            map_image_set(grid_offset, image_id);
            map_property_set_multi_tile_xy(grid_offset, dx, dy,
                                           dx == leftmost.x && dy == leftmost.y);
        }
    }
}

static int blocked_land_terrain(void) {
    return
            TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER |
            TERRAIN_BUILDING | TERRAIN_SHRUB | TERRAIN_GARDEN |
            TERRAIN_ROAD | TERRAIN_ELEVATION | TERRAIN_RUBBLE;
}

bool map_water_determine_orientation_generic(int x, int y, int size, bool adjust_xy, int *orientation_absolute) {
    if (adjust_xy) {
        switch (city_view_orientation()) {
            case DIR_0_TOP_RIGHT:
                break;
            case DIR_2_BOTTOM_RIGHT:
                x -= size - 1;
                break;
            case DIR_6_TOP_LEFT:
                y -= size - 1;
                break;
            case DIR_4_BOTTOM_LEFT:
                x -= size - 1;
                y -= size - 1;
                break;
        }
    }
    if (!map_grid_is_inside(x, y, size))
        return false;

    // actually... check also the bordering blocks on each side.
    size += 2;
    x--;
    y--;

    // fill in tile cache first
    int water_tiles[size][size];
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            water_tiles[row][column] = map_terrain_is(map_grid_offset(x + column, y + row), TERRAIN_WATER);
        }
    }

    // check -- north
    bool matches = true;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if ((water_tiles[row][column] == true && row > 1 && (column > 0 && column < size - 1 && row < size - 1)) ||
                (water_tiles[row][column] == false && row <= 1))
                matches = false;
        }
    }
    if (matches && orientation_absolute) {
        *orientation_absolute = 0;
        return true;
    }

    // check -- east
    matches = true;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if ((water_tiles[row][column] == true && column < size - 2 && (row > 0 && row < size - 1 && column > 0)) ||
                (water_tiles[row][column] == false && column >= size - 2))
                matches = false;
        }
    }
    if (matches && orientation_absolute) {
        *orientation_absolute = 1;
        return true;
    }

    // check -- south
    matches = true;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if ((water_tiles[row][column] == true && row < size - 2 && (column > 0 && column < size - 1 && row > 0)) ||
                (water_tiles[row][column] == false && row >= size - 2))
                matches = false;
        }
    }
    if (matches && orientation_absolute) {
        *orientation_absolute = 2;
        return true;
    }

    // check -- west
    matches = true;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if ((water_tiles[row][column] == true && column > 1 && (row > 0 && row < size - 1 && column < size - 1)) ||
                (water_tiles[row][column] == false && column <= 1))
                matches = false;
        }
    }
    if (matches && orientation_absolute) {
        *orientation_absolute = 3;
        return true;
    }

    // no match.
    return false;
}

int map_water_get_wharf_for_new_fishing_boat(figure *boat, map_point *tile) {
    building *wharf = 0;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_FISHING_WHARF) {
            int wharf_boat_id = b->data.industry.fishing_boat_id;
            if (!wharf_boat_id || wharf_boat_id == boat->id) {
                wharf = b;
                break;
            }
        }
    }
    if (!wharf)
        return 0;

    int dx, dy;
    switch (wharf->data.industry.orientation) {
        case 0:
            dx = 1;
            dy = -1;
            break;
        case 1:
            dx = 2;
            dy = 1;
            break;
        case 2:
            dx = 1;
            dy = 2;
            break;
        default:
            dx = -1;
            dy = 1;
            break;
    }
    map_point_store_result(wharf->x + dx, wharf->y + dy, tile);
    return wharf->id;
}
int map_water_find_alternative_fishing_boat_tile(figure *boat, map_point *tile) {
    if (map_figure_at(boat->grid_offset_figure) == boat->id)
        return 0;

    for (int radius = 1; radius <= 5; radius++) {
        int x_min, y_min, x_max, y_max;
        map_grid_get_area(boat->tile_x, boat->tile_y, 1, radius, &x_min, &y_min, &x_max, &y_max);

        for (int yy = y_min; yy <= y_max; yy++) {
            for (int xx = x_min; xx <= x_max; xx++) {
                int grid_offset = map_grid_offset(xx, yy);
                if (!map_has_figure_at(grid_offset) && map_terrain_is(grid_offset, TERRAIN_WATER)) {
                    map_point_store_result(xx, yy, tile);
                    return 1;
                }
            }
        }
    }
    return 0;
}
int map_water_find_shipwreck_tile(figure *wreck, map_point *tile) {
    if (map_terrain_is(wreck->grid_offset_figure, TERRAIN_WATER) && map_figure_at(wreck->grid_offset_figure) == wreck->id)
        return 0;

    for (int radius = 1; radius <= 5; radius++) {
        int x_min, y_min, x_max, y_max;
        map_grid_get_area(wreck->tile_x, wreck->tile_y, 1, radius, &x_min, &y_min, &x_max, &y_max);

        for (int yy = y_min; yy <= y_max; yy++) {
            for (int xx = x_min; xx <= x_max; xx++) {
                int grid_offset = map_grid_offset(xx, yy);
                if (!map_has_figure_at(grid_offset) || map_figure_at(grid_offset) == wreck->id) {
                    if (map_terrain_is(grid_offset, TERRAIN_WATER) &&
                        map_terrain_is(map_grid_offset(xx, yy - 2), TERRAIN_WATER) &&
                        map_terrain_is(map_grid_offset(xx, yy + 2), TERRAIN_WATER) &&
                        map_terrain_is(map_grid_offset(xx - 2, yy), TERRAIN_WATER) &&
                        map_terrain_is(map_grid_offset(xx + 2, yy), TERRAIN_WATER)) {
                        map_point_store_result(xx, yy, tile);
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

static int num_surrounding_water_tiles(int grid_offset) {
    int amount = 0;
    for (int i = 0; i < DIR_8_NONE; i++) {
        if (map_terrain_is(grid_offset + map_grid_direction_delta(i), TERRAIN_WATER))
            amount++;

    }
    return amount;
}

int map_water_can_spawn_fishing_boat(int x, int y, int size, map_point *tile) {
    int base_offset = map_grid_offset(x, y);
    for (const int *tile_delta = map_grid_adjacent_offsets(size); *tile_delta; tile_delta++) {
        int grid_offset = base_offset + *tile_delta;
        if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
            if (!map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
                if (num_surrounding_water_tiles(grid_offset) >= 8) {
                    map_point_store_result(map_grid_offset_to_x(grid_offset), map_grid_offset_to_y(grid_offset), tile);
                    return 1;
                }
            }
        }
    }
    return 0;
}

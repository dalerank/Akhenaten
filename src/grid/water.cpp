#include "water.h"

#include "building/building.h"
#include "graphics/view/view.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/point.h"
#include "grid/property.h"
#include "grid/terrain.h"

#include <array>

tile_cache river_tiles_cache;
tile_cache river_shoreline_tiles_cache;

void foreach_river_tile(void (*callback)(int grid_offset)) {
    for (const auto &tile: river_tiles_cache) {
        callback(tile);
    }
}

void map_water_add_building(int building_id, int x, int y, int size, int image_id) {
    if (!map_grid_is_inside(x, y, size))
        return;
    map_point leftmost;
    switch (city_view_orientation()) {
    case DIR_0_TOP_RIGHT:
        leftmost.set(0, size - 1);
        break;
    case DIR_2_BOTTOM_RIGHT:
        leftmost.set(0, 0);
        break;
    case DIR_4_BOTTOM_LEFT:
        leftmost.set(size - 1, 0);
        break;
    case DIR_6_TOP_LEFT:
        leftmost.set(size - 1, size - 1);
        break;
    default:
        return;
    }
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            int grid_offset = MAP_OFFSET(x + dx, y + dy);
            map_terrain_add(grid_offset, TERRAIN_BUILDING);
            if (!map_terrain_is(grid_offset, TERRAIN_WATER)) {
                map_terrain_remove(grid_offset, TERRAIN_CLEARABLE);
                map_terrain_add(grid_offset, TERRAIN_BUILDING);
            }
            map_building_set(grid_offset, building_id);
            map_property_clear_constructing(grid_offset);
            map_property_set_multi_tile_size(grid_offset, size);
            map_image_set(grid_offset, image_id);
            map_property_set_multi_tile_xy(grid_offset, dx, dy, dx == leftmost.x() && dy == leftmost.y());
        }
    }
}

static int blocked_land_terrain(void) {
    return TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_WATER | TERRAIN_BUILDING | TERRAIN_SHRUB | TERRAIN_GARDEN
           | TERRAIN_ROAD | TERRAIN_ELEVATION | TERRAIN_RUBBLE;
}

bool map_shore_determine_orientation(int x,
                                     int y,
                                     int size,
                                     bool adjust_xy,
                                     int* orientation_absolute,
                                     bool adjacent,
                                     int shore_terrain) {
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
    struct water_tiles_t {
        int *_data;
        int _size;
        water_tiles_t(int size) : _size(size) { _data = (int*)_alloca(size * size * sizeof(int)); }
        int &at(int row, int column) { return _data[row * _size + column]; }
    } water_tiles(size);

    auto water_tile = [water_tiles] (int row, int column) { };
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            water_tiles.at(row, column) = map_terrain_is(MAP_OFFSET(x + column, y + row), shore_terrain);
        }
    }

    // check -- north
    bool matches = true;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if ((water_tiles.at(row, column) == true && row > (!adjacent) && (column > 0 && column < size - 1 && row < size - 1))
                || (water_tiles.at(row, column) == false && row <= (!adjacent) && (column >= adjacent && column <= size - (1 + adjacent))))
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
            if ((water_tiles.at(row, column) == true && column < size - (1 + !adjacent) && (row > 0 && row < size - 1 && column > 0))
                || (water_tiles.at(row, column) == false && column >= size - (1 + !adjacent) && (row >= adjacent && row <= size - (1 + adjacent))))
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
            if ((water_tiles.at(row, column) == true && row < size - (1 + !adjacent) && (column > 0 && column < size - 1 && row > 0))
                || (water_tiles.at(row, column) == false && row >= size - (1 + !adjacent) && (column >= adjacent && column <= size - (1 + adjacent))))
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
            if ((water_tiles.at(row, column) == true && column > (!adjacent) && (row > 0 && row < size - 1 && column < size - 1))
                || (water_tiles.at(row, column) == false && column <= (!adjacent) && (row >= adjacent && row <= size - (1 + adjacent))))
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

int map_water_get_wharf_for_new_fishing_boat(figure* boat, map_point* tile) {
    building* wharf = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
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
    map_point_store_result(wharf->tile.x() + dx, wharf->tile.y() + dy, tile);
    return wharf->id;
}
int map_water_find_alternative_fishing_boat_tile(figure* boat, map_point* tile) {
    if (map_figure_at(boat->tile.grid_offset()) == boat->id)
        return 0;

    for (int radius = 1; radius <= 5; radius++) {
        int x_min, y_min, x_max, y_max;
        map_grid_get_area(boat->tile.x(), boat->tile.y(), 1, radius, &x_min, &y_min, &x_max, &y_max);

        for (int yy = y_min; yy <= y_max; yy++) {
            for (int xx = x_min; xx <= x_max; xx++) {
                int grid_offset = MAP_OFFSET(xx, yy);
                if (!map_has_figure_at(grid_offset) && map_terrain_is(grid_offset, TERRAIN_WATER)) {
                    map_point_store_result(xx, yy, tile);
                    return 1;
                }
            }
        }
    }
    return 0;
}
int map_water_find_shipwreck_tile(figure* wreck, map_point* tile) {
    if (map_terrain_is(wreck->tile.grid_offset(), TERRAIN_WATER)
        && map_figure_at(wreck->tile.grid_offset()) == wreck->id)
        return 0;

    for (int radius = 1; radius <= 5; radius++) {
        int x_min, y_min, x_max, y_max;
        map_grid_get_area(wreck->tile.x(), wreck->tile.y(), 1, radius, &x_min, &y_min, &x_max, &y_max);

        for (int yy = y_min; yy <= y_max; yy++) {
            for (int xx = x_min; xx <= x_max; xx++) {
                int grid_offset = MAP_OFFSET(xx, yy);
                if (!map_has_figure_at(grid_offset) || map_figure_at(grid_offset) == wreck->id) {
                    if (map_terrain_is(grid_offset, TERRAIN_WATER)
                        && map_terrain_is(MAP_OFFSET(xx, yy - 2), TERRAIN_WATER)
                        && map_terrain_is(MAP_OFFSET(xx, yy + 2), TERRAIN_WATER)
                        && map_terrain_is(MAP_OFFSET(xx - 2, yy), TERRAIN_WATER)
                        && map_terrain_is(MAP_OFFSET(xx + 2, yy), TERRAIN_WATER)) {
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

int map_water_can_spawn_fishing_boat(int x, int y, int size, map_point* tile) {
    int base_offset = MAP_OFFSET(x, y);
    for (const int* tile_delta = map_grid_adjacent_offsets(size); *tile_delta; tile_delta++) {
        int grid_offset = base_offset + *tile_delta;
        if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
            if (!map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
                if (num_surrounding_water_tiles(grid_offset) >= 8) {
                    map_point_store_result(MAP_X(grid_offset), MAP_Y(grid_offset), tile);
                    return 1;
                }
            }
        }
    }
    return 0;
}

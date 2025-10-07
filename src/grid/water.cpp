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
#include "grid/routing/routing.h"

#include <array>

tile_cache river_tiles_cache;
tile_cache g_river_shore;
tile_cache &river_tiles() { return river_tiles_cache; }

bool map_water_is_point_inside(tile2i tile) {
    int map_height = scenario_map_data()->height;
    int map_width = scenario_map_data()->width;
    return tile.x() < map_width && tile.y() < map_height;
}

void map_water_cache_river_tiles() {
    river_tiles_cache.clear();

    int grid_offset = scenario_map_data()->start_offset;
    int map_height = scenario_map_data()->height;
    int border_size = scenario_map_data()->border_size;
    int map_width = scenario_map_data()->width;
    for (int y = 0; y < map_height; y++, grid_offset += border_size) {
        for (int x = 0; x < map_width; x++, grid_offset++) {
            if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN + TERRAIN_WATER)) {
                river_tiles_cache.push_back(grid_offset);
            }
        }
    }
}

void map_water_update_docking_points(building &b, int orientation, int offset) {
    tile2i river_entry = scenario_map_river_entry();
    if (!river_entry.valid()) {
        b.has_water_access = false;
        b.has_open_water_access = false;
        return;
    }

    map_routing_calculate_distances_water_boat(river_entry);

    bool found = map_terrain_is_adjacent_to_open_water(b.tile, b.size);
    b.has_water_access |= found;
    b.has_open_water_access = found;

    water_access_tiles ppoints;
    if (found) {
        ppoints = map_water_get_access_points(b, b.dcast()->get_orientation(), offset);
    } 
    b.dcast()->set_water_access_tiles(ppoints);
}

water_access_tiles map_water_get_access_points(building &b, int orientation, int offset) {
    const auto &params = building_impl::params(b.type);
    if (!params.needs.water_access) {
        return {{-1, -1},{-1, -1}};
    }

    water_access_tiles result;
    const int bsize = params.building_size;
    switch (orientation) {
    case 0:
        result.point_a = b.tile.shifted(1, -offset);
        result.point_b = b.tile.shifted(0, -offset);
        break;
    case 1:
        result.point_a = b.tile.shifted(bsize + (offset - 1), 0);
        result.point_b = b.tile.shifted(bsize + (offset - 1), 1);
        break;
    case 2:
        result.point_a = b.tile.shifted(0, bsize + (offset - 1));
        result.point_b = b.tile.shifted(1, bsize + (offset - 1));
        break;
    case 3:
        result.point_a = b.tile.shifted(-offset, 0);
        result.point_b = b.tile.shifted(-offset, 1);
        break;
    }

    return result;
}

void map_water_add_building(int building_id, tile2i tile, int size, int image_id, int ext_terrain_flags) {
    if (!map_grid_is_inside(tile, size)) {
        return;
    }

    tile2i leftmost;
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
            int grid_offset = MAP_OFFSET(tile.x() + dx, tile.y() + dy);
            map_terrain_add(grid_offset, TERRAIN_BUILDING|ext_terrain_flags);
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

void map_water_rebuild_shores() {
    foreach_river_tile([&] (int tile_offset) {
        tile2i tile(tile_offset);
        grid_area area = map_grid_get_area(tile, 1, 1);

        bool ground_aside = false;
        int ground_tiles_num = 0;
        int water_tiles_num = 0;
        map_grid_area_foreach(area.tmin, area.tmax, [&] (tile2i t) {
            if (map_terrain_is(t, TERRAIN_WATER|TERRAIN_FLOODPLAIN)) {
                water_tiles_num++;
            } else {
                ground_aside = true;
                ground_tiles_num++;
            }
        });

        if (ground_aside) {
            map_terrain_add(tile_offset, TERRAIN_SHORE);
        }
    });
}

shore_orientation map_shore_determine_orientation(tile2i tile, int size, bool adjust_xy, bool adjacent, int shore_terrain) {
    int x = tile.x();
    int y = tile.y();

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

    if (!map_grid_is_inside(tile2i(x, y), size)) {
        return { false, 0 };
    }

    // actually... check also the bordering blocks on each side.
    size += 2;
    x--;
    y--;

    // fill in tile cache first
    struct water_tiles_t {
        int _size;
        std::array<int, 32> _data = { 0 };
        water_tiles_t(int size) : _size(size) {}
        int &at(int row, int column) { return _data[row * _size + column]; }
    } water_tiles(size);
    assert((size *size) < 36);

    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            water_tiles.at(row, column) = map_terrain_is(MAP_OFFSET(x + column, y + row), shore_terrain);
        }
    }

    // check -- north
    bool matches = true;
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            if ((water_tiles.at(row, column) && row > (!adjacent) && (column > 0 && column < size - 1 && row < size - 1))
                || (!water_tiles.at(row, column) && row <= (!adjacent) && (column >= adjacent && column <= size - (1 + adjacent))))
                matches = false;
        }
    }

    if (matches) {
        return {true, 0};
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

    if (matches) {
        return {true, 1};
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

    if (matches) {
        return {true, 2};
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

    if (matches) {
        return {true, 3};
    }

    // no match.
    return {false, 0};
}

water_dest map_water_find_alternative_fishing_boat_tile(figure &boat) {
    if (map_figure_id_get(boat.tile) == boat.id) {
        return {false};
    }

    grid_area area = map_grid_get_area(boat.tile, 1, 1);

    svector<tile2i, 16> tiles;
    area.for_each([&] (tile2i tt) {
        if (!map_has_figure_at(tt) && map_terrain_is(tt, TERRAIN_WATER)) {
            tiles.push_back(tt);
        }
    });

    tile2i result = tiles.empty() ? tile2i::invalid : tiles[rand() % tiles.size()];
    return { result.valid(), 0, result };
}

water_dest map_water_find_shipwreck_tile(figure &wreck) {
    if (map_terrain_is(wreck.tile, TERRAIN_WATER) && map_figure_id_get(wreck.tile) == wreck.id) {
        return {false};
    }

    tile2i tile;
    for (int radius = 1; radius <= 5; radius++) {
        grid_area area = map_grid_get_area(wreck.tile, 1, radius);

        for (int yy = area.tmin.y(), endy = area.tmax.y(); yy <= endy; yy++) {
            for (int xx = area.tmin.x(), endx = area.tmax.x(); xx <= endx; xx++) {
                int grid_offset = MAP_OFFSET(xx, yy);
                if (!map_has_figure_at(grid_offset) || map_figure_id_get(grid_offset) == wreck.id) {
                    if (map_terrain_is(grid_offset, TERRAIN_WATER)
                        && map_terrain_is(MAP_OFFSET(xx, yy - 2), TERRAIN_WATER)
                        && map_terrain_is(MAP_OFFSET(xx, yy + 2), TERRAIN_WATER)
                        && map_terrain_is(MAP_OFFSET(xx - 2, yy), TERRAIN_WATER)
                        && map_terrain_is(MAP_OFFSET(xx + 2, yy), TERRAIN_WATER)) {
                        map_point_store_result(tile2i(xx, yy), tile);
                        return {true, 0, tile};
                    }
                }
            }
        }
    }
    return {false};
}

static int num_surrounding_water_tiles(int grid_offset) {
    int amount = 0;
    for (int i = 0; i < DIR_8_NONE; i++) {
        if (map_terrain_is(grid_offset + map_grid_direction_delta(i), TERRAIN_WATER))
            amount++;
    }
    return amount;
}

bool map_water_can_spawn_boat(tile2i tile, int size, tile2i &boat_tile) {
    int base_offset = tile.grid_offset();
    offsets_array offsets;
    map_grid_adjacent_offsets(size, offsets);
    for (const int& tile_delta: offsets) {
        int grid_offset = base_offset + tile_delta;
        if (map_terrain_is(grid_offset, TERRAIN_WATER|TERRAIN_DEEPWATER)) {
            if (!map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
                if (num_surrounding_water_tiles(grid_offset) >= 8) {
                    map_point_store_result(tile2i(grid_offset), boat_tile);
                    return true;
                }
            }
        }
    }
    return false;
}

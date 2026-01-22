#include "road_access.h"

#include "building/building.h"
#include "building/building_roadblock.h"
#include "building/rotation.h"
#include "city/city.h"
#include "core/profiler.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/property.h"
#include "grid/road_network.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "grid/terrain.h"
#include "game/game_config.h"

bool road_tile_valid_access(int grid_offset) {
    if (!map_terrain_is(grid_offset, TERRAIN_ROAD)) {
        return false;
    }

    if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
        return false;
    }

    if (map_terrain_is(grid_offset, TERRAIN_DEEPWATER)) {
        return false;
    }

    if (map_terrain_is(grid_offset, TERRAIN_BUILDING)) {// general case -- no buildings over road!
        e_building_type btype = building_at(grid_offset)->type; // exceptions: vvv
        if (building_type_any_of(btype, { BUILDING_MUD_GATEHOUSE, BUILDING_BOOTH, BUILDING_BANDSTAND, BUILDING_PAVILLION, BUILDING_FESTIVAL_SQUARE })) {
            return true;
        }
    }

    return true;
}

bool map_road_find_minimum_tile_xy(tile2i tile, int sizex, int sizey, int *min_value, int *min_grid_offset) {
    bool found = false;
    if (!!game_features::gameplay_change_enter_point_on_nearest_tile) {
        found = map_road_find_minimum_tile_xy_nearest(tile, sizex, sizey, min_value, min_grid_offset);
    }

    if (!found) {
        found = map_road_find_minimum_tile_xy_classic(tile, sizex, sizey, min_value, min_grid_offset);
    }

    return found;
}

bool map_road_find_minimum_tile_xy_nearest(tile2i tile, int sizex, int sizey, int* min_value, int* min_grid_offset) {
    int base_offset = tile.grid_offset();
    offsets_array offsets;
    map_grid_adjacent_offsets_xy(sizex, sizey, offsets);
    float f_min_value = *min_value;
    bool found = false;
    for (const auto &tile_delta: offsets) {
        int grid_offset = base_offset + tile_delta;

        if (!road_tile_valid_access(grid_offset)) {
            continue;
        }

        float road_dist = tile2i(grid_offset).dist(tile);
        if (road_dist < f_min_value) {
            f_min_value = road_dist;
            *min_value = f_min_value;
            *min_grid_offset = grid_offset;
            found = true;
        }
    }

    return found;
}

bool map_road_find_minimum_tile_xy_classic(tile2i tile, int sizex, int sizey, int* min_value, int* min_grid_offset) {
    int base_offset = tile.grid_offset();
    offsets_array offsets;
    map_grid_adjacent_offsets_xy(sizex, sizey, offsets);
    bool found = false;
    for (const auto &tile_delta: offsets) {
        int grid_offset = base_offset + tile_delta;

        if (!road_tile_valid_access(grid_offset)) {
            continue;
        }

        int road_index = g_city.map.road_network_index(map_road_network_get(grid_offset));
        if (road_index < *min_value) {
            *min_value = road_index;
            *min_grid_offset = grid_offset;
            found = false;
        }
    }

    return false;
}

bool map_has_road_access(tile2i tile, int size) {
    tile2i result = map_has_road_access_rotation(0, tile, size);
    return result.valid();
}

tile2i map_get_road_access_tile(tile2i tile, int size) {
    return map_has_road_access_rotation(0, tile, size);
}

tile2i map_has_road_access_rotation(int rotation, tile2i tile, int size) {
    switch (rotation) {
    case 1:
        tile.shift(-size + 1, 0);
        break;
    case 2:
        tile.shift(-size + 1, -size + 1);
        break;
    case 3:
        tile.shift(0, -size + 1);
        break;
    default:
        break;
    }

    int min_value = 12;
    int min_grid_offset = tile.grid_offset();
    map_road_find_minimum_tile_xy(tile, size, size, &min_value, &min_grid_offset);
    if (min_value < 12) {
        tile2i result(min_grid_offset);
        tile2i _;
        map_point_store_result(result, _);
        return result;
    }

    return tile2i::invalid;
}

// int map_has_road_access_hippodrome_rotation(int x, int y, map_point *road, int rotation) {
//     int min_value = 12;
//     int min_grid_offset = map_grid_offset(x, y);
//     int x_offset, y_offset;
//     building_rotation_get_offset_with_rotation(5, rotation, &x_offset, &y_offset);
//     find_minimum_road_tile(x, y, 5, &min_value, &min_grid_offset);
//     find_minimum_road_tile(x + x_offset, y + y_offset, 5, &min_value, &min_grid_offset);
//     building_rotation_get_offset_with_rotation(10, rotation, &x_offset, &y_offset);
//     find_minimum_road_tile(x + x_offset, y + y_offset, 5, &min_value, &min_grid_offset);
//     if (min_value < 12) {
//         if (road)
//             map_point_store_result(map_grid_offset_to_x(min_grid_offset), map_grid_offset_to_y(min_grid_offset),
//             road);
//         return 1;
//     }
//     return 0;
// }

// int map_has_road_access_hippodrome(int x, int y, map_point *road) {
//     return map_has_road_access_hippodrome_rotation(x, y, road, building_rotation_get_rotation());
// }

// TODO: fix getting road access for temple complex
bool map_has_road_access_temple_complex(tile2i tile, int orientation, bool from_corner, tile2i* road) {
    int sizex = 7;
    int sizey = 13;

    // correct size for orientation
    switch (orientation) {
    case 1:
    case 3:
        sizex = 13;
        sizey = 7;
        break;
    }

    // correct offset if coords are from the main building part
    if (!from_corner) {
        switch (orientation) {
        case 0:
            tile.shift(-2, -11);
            break;
        case 1:
            tile.shift(0, -2);
            break;
        case 2:
            tile.shift(-2, 0);
            break;
        case 3:
            tile.shift(-11, -2);
            break;
        }
    }

    int min_value = 12;
    int min_grid_offset = tile.grid_offset();
    map_road_find_minimum_tile_xy(tile, sizex, sizey, &min_value, &min_grid_offset);
    if (min_value < 12) {
        if (road) {
            map_point_store_result(tile2i(min_grid_offset), *road);
        }
        return true;
    }
    return false;
}

bool map_road_within_radius(tile2i tile, int size, int radius, tile2i &road_tile, bool avoid_center) {
    OZZY_PROFILER_FUNCTION();
    grid_area area = map_grid_get_area(tile, size, radius);
    uint32_t center_offset = tile.grid_offset();

    for (int yy = area.tmin.y(), endy = area.tmax.y(); yy <= endy; yy++) {
        for (int xx = area.tmin.x(), endx = area.tmax.x(); xx <= endx; xx++) {
            uint32_t grid_offset = MAP_OFFSET(xx, yy);
            if (grid_offset == center_offset) {
                continue;
            }

            if (!map_terrain_is(grid_offset, TERRAIN_ROAD)) {
                continue;
            }
            // Don't spawn walkers on roadblocks
            if (building_at(grid_offset)->type == BUILDING_ROADBLOCK) {
                continue;
            }

            road_tile.set(xx, yy);
            return true;
        }
    }
    return false;
}

tile2i map_closest_road_within_radius(building &b, int radius) {
    return map_closest_road_within_radius(b.tile, b.size, radius);
}

tile2i map_closest_road_within_radius(tile2i tile, int size, int radius, bool avoid_center) {
    OZZY_PROFILER_FUNCTION();
    tile2i result;
    for (int r = 1; r <= radius; r++) {
        if (map_road_within_radius(tile, size, r, result, avoid_center)) {
            return result;
        }
    }
    return tile2i::invalid;
}

bool map_reachable_road_within_radius(tile2i tile, int size, int radius, tile2i &road_tile) {
    OZZY_PROFILER_FUNCTION();
    grid_area area = map_grid_get_area(tile, size, radius);

    for (int yy = area.tmin.y(), endy = area.tmax.y(); yy <= endy; yy++) {
        for (int xx = area.tmin.x(), endx = area.tmax.x(); xx <= endx; xx++) {
            int grid_offset = MAP_OFFSET(xx, yy);
            if (map_terrain_is(grid_offset, TERRAIN_ROAD)) {
                if (map_routing_distance(grid_offset) > 0) {
                    road_tile = {xx, yy};
                    return true;
                }
            }
        }
    }
    return false;
}

bool map_closest_reachable_road_within_radius(tile2i tile, int size, int radius, tile2i &road_tile) {
    OZZY_PROFILER_FUNCTION();
    for (int r = 1; r <= radius; r++) {
        if (map_reachable_road_within_radius(tile, size, r, road_tile))
            return true;
    }
    return false;
}

tile2i map_road_to_largest_network_rotation(int rotation, tile2i tile, int size, bool closest) {
    int x = tile.x();
    int y = tile.y();
    switch (rotation) {
    case 1:
        x = x - size + 1;
        break;
    case 2:
        x = x - size + 1;
        y = y - size + 1;
        break;
    case 3:
        y = y - size + 1;
        break;
    default:
        break;
    }

    int min_index = 12;
    int min_grid_offset = -1;
    int base_offset = MAP_OFFSET(x, y);
    offsets_array offsets;
    map_grid_adjacent_offsets(size, offsets);
    if (closest) {
        std::erase_if(offsets, [base_offset] (auto &it) {
            return map_terrain_is(base_offset + it, TERRAIN_WATER | TERRAIN_DEEPWATER)
                     || (map_building_at(base_offset + it) > 0);
        });

        std::sort(offsets.begin(), offsets.end(), [base_offset] (auto &lhs, auto &rhs) {
            int lhs_network_id = map_road_network_get(base_offset + lhs);
            int rhs_network_id = map_road_network_get(base_offset + rhs);
            return (lhs_network_id > rhs_network_id);
        });
        
        tile2i base_tile(base_offset);
        tile2i current_tile(base_offset + offsets.front());
        tile2i best_road_tile = current_tile;
        float min_dist = base_tile.dist(best_road_tile);
        int greatest_road_id = map_road_network_get(best_road_tile);
        for (int i = 1, size = offsets.size(); i < size; ++i) {
            current_tile = tile2i(base_offset + offsets[i]);
            int cur_road_id = map_road_network_get(current_tile);
            if (map_terrain_is(current_tile, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
                continue;
            }

            if (!map_terrain_is(current_tile, TERRAIN_ROAD)) {
                continue;
            }

            if (cur_road_id != greatest_road_id) {
                break;
            }

            float cur_dist = base_tile.dist(current_tile);
            if (cur_dist < min_dist) {
                min_dist = cur_dist;
                best_road_tile = current_tile;
            }
        }

        const bool is_road = map_terrain_is(best_road_tile, TERRAIN_ROAD);
        return is_road ? best_road_tile : tile2i::invalid;
    } else {
        for (const auto &tile_delta: offsets) {
            int grid_offset = base_offset + tile_delta;
            if (map_terrain_is(grid_offset, TERRAIN_ROAD) && map_routing_distance(grid_offset) > 0) {
                int index = g_city.map.road_network_index(map_road_network_get(grid_offset));
                if (index < min_index) {
                    min_index = index;
                    min_grid_offset = grid_offset;
                }
            }
        }

        if (min_index < 12) {
            return tile2i(min_grid_offset);
        }
    }
   
    int min_dist = 100000;
    min_grid_offset = -1;
    offsets.clear();
    map_grid_adjacent_offsets(size, offsets);
    for (const auto &tile_delta : offsets) {
        int grid_offset = base_offset + tile_delta;
        int dist = map_routing_distance(grid_offset);
        if (dist > 0 && dist < min_dist) {
            min_dist = dist;
            min_grid_offset = grid_offset;
        }
    }
    
    if (min_grid_offset >= 0) {
        return tile2i(min_grid_offset);
    }

    return tile2i{-1, -1};
}

tile2i map_road_to_largest_network(tile2i tile, int size, bool closest) {
    return map_road_to_largest_network_rotation(0, tile, size, closest);
}

static void check_road_to_largest_network_hippodrome(int x, int y, int* min_index, int* min_grid_offset) {
    int base_offset = MAP_OFFSET(x, y);
    offsets_array offsets;
    map_grid_adjacent_offsets(5, offsets);
    for (const int &tile_delta: offsets) {
        int grid_offset = base_offset + tile_delta;
        if (map_terrain_is(grid_offset, TERRAIN_ROAD) && map_routing_distance(grid_offset) > 0) {
            int index = g_city.map.road_network_index(map_road_network_get(grid_offset));
            if (index < *min_index) {
                *min_index = index;
                *min_grid_offset = grid_offset;
            }
        }
    }
}

static void check_min_dist_hippodrome(int base_offset, int x_offset, int* min_dist, int* min_grid_offset, int* min_x_offset) {
    offsets_array offsets;
    map_grid_adjacent_offsets(5, offsets);
    for (const int &tile_delta: offsets) {
        int grid_offset = base_offset + tile_delta;
        int dist = map_routing_distance(grid_offset);
        if (dist > 0 && dist < *min_dist) {
            *min_dist = dist;
            *min_grid_offset = grid_offset;
            *min_x_offset = x_offset;
        }
    }
}

int map_road_to_largest_network_hippodrome(int x, int y, int* x_road, int* y_road) {
    int min_index = 12;
    int min_grid_offset = -1;
    check_road_to_largest_network_hippodrome(x, y, &min_index, &min_grid_offset);
    check_road_to_largest_network_hippodrome(x + 5, y, &min_index, &min_grid_offset);
    check_road_to_largest_network_hippodrome(x + 10, y, &min_index, &min_grid_offset);

    if (min_index < 12) {
        *x_road = MAP_X(min_grid_offset);
        *y_road = MAP_Y(min_grid_offset);
        return min_grid_offset;
    }

    int min_dist = 100000;
    min_grid_offset = -1;
    int min_x_offset = -1;
    check_min_dist_hippodrome(MAP_OFFSET(x, y), 0, &min_dist, &min_grid_offset, &min_x_offset);
    check_min_dist_hippodrome(MAP_OFFSET(x + 5, y), 5, &min_dist, &min_grid_offset, &min_x_offset);
    check_min_dist_hippodrome(MAP_OFFSET(x + 10, y), 10, &min_dist, &min_grid_offset, &min_x_offset);

    if (min_grid_offset >= 0) {
        *x_road = MAP_X(min_grid_offset) + min_x_offset;
        *y_road = MAP_Y(min_grid_offset);
        return min_grid_offset + min_x_offset;
    }
    return -1;
}

static int terrain_is_road_like(int grid_offset) {
    return map_terrain_is(grid_offset, TERRAIN_ROAD | TERRAIN_ACCESS_RAMP) ? 1 : 0;
}

static bool is_adjacent_road_tile_for_roaming(int grid_offset, e_permission perm) {
    if (map_terrain_is(grid_offset, TERRAIN_WATER) && map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
        return 0;
    }

    int is_road = terrain_is_road_like(grid_offset);
    if (!map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
        return is_road;
    }

    building* b = building_at(grid_offset);
    if (b->type == BUILDING_MUD_GATEHOUSE) {
        return false;
    } 
        
    building_routeblock *roadblock = b->dcast_roadblock();
    if (roadblock && !roadblock->get_permission(perm)) {
        return false;
    } 
        
    if (b->type == BUILDING_GRANARY) {
        if (map_routing_citizen_is_road(grid_offset)) {
            if (!!game_features::gameplay_dynamic_granaries) {
                if (map_property_multi_tile_xy(grid_offset) == EDGE_X1Y1 || map_has_adjacent_road_tiles(grid_offset)
                    || map_has_adjacent_granary_road(grid_offset))
                    is_road = 1;

            } else {
                is_road = 1;
            }
        }
        return is_road;
    } 
        
    if (b->type == BUILDING_RESERVED_TRIUMPHAL_ARCH_56) {
        if (map_routing_citizen_is_road(grid_offset)) {
            is_road = 1;
        }

        return is_road;
    }

    return is_road;
}

int map_get_adjacent_road_tiles_for_roaming(int grid_offset, int* road_tiles, e_permission perm) {
    road_tiles[1] = road_tiles[3] = road_tiles[5] = road_tiles[7] = 0;

    road_tiles[0] = is_adjacent_road_tile_for_roaming(grid_offset + GRID_OFFSET(0, -1), perm);
    road_tiles[2] = is_adjacent_road_tile_for_roaming(grid_offset + GRID_OFFSET(1, 0), perm);
    road_tiles[4] = is_adjacent_road_tile_for_roaming(grid_offset + GRID_OFFSET(0, 1), perm);
    road_tiles[6] = is_adjacent_road_tile_for_roaming(grid_offset + GRID_OFFSET(-1, 0), perm);

    return road_tiles[0] + road_tiles[2] + road_tiles[4] + road_tiles[6];
}

int map_get_diagonal_road_tiles_for_roaming(int grid_offset, int* road_tiles) {
    road_tiles[1] = terrain_is_road_like(grid_offset + GRID_OFFSET(1, -1));
    road_tiles[3] = terrain_is_road_like(grid_offset + GRID_OFFSET(1, 1));
    road_tiles[5] = terrain_is_road_like(grid_offset + GRID_OFFSET(-1, 1));
    road_tiles[7] = terrain_is_road_like(grid_offset + GRID_OFFSET(-1, -1));

    int max_stretch = 0;
    int stretch = 0;
    for (int i = 0; i < 16; i++) {
        if (road_tiles[i % 8]) {
            stretch++;
            if (stretch > max_stretch)
                max_stretch = stretch;

        } else {
            stretch = 0;
        }
    }
    return max_stretch;
}

int map_has_adjacent_road_tiles(int grid_offset) {
    int adjacent_roads = terrain_is_road_like(grid_offset + GRID_OFFSET(0, -1))
                         + terrain_is_road_like(grid_offset + GRID_OFFSET(1, 0))
                         + terrain_is_road_like(grid_offset + GRID_OFFSET(0, 1))
                         + terrain_is_road_like(grid_offset + GRID_OFFSET(-1, 0));
    return adjacent_roads;
}

int map_has_adjacent_granary_road(int grid_offset) {
    int tiles[4];
    tiles[0] = grid_offset + GRID_OFFSET(0, -1);
    tiles[1] = grid_offset + GRID_OFFSET(1, 0);
    tiles[2] = grid_offset + GRID_OFFSET(0, 1);
    tiles[3] = grid_offset + GRID_OFFSET(-1, 0);
    for (int i = 0; i < 4; i++) {
        if (building_at(tiles[i])->type != BUILDING_GRANARY)
            continue;
        switch (map_property_multi_tile_xy(tiles[i])) {
        case EDGE_X1Y0:
        case EDGE_X0Y1:
        case EDGE_X2Y1:
        case EDGE_X1Y2:
            return 1;
        }
    }
    return 0;
}

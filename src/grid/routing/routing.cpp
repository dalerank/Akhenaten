#include "routing.h"

#include "city/city_animals.h"
#include "figure/route.h"
#include "grid/vegetation.h"
#include "building/building.h"
#include "city/city_buildings.h"
#include "routing_terrain.h"
#include "core/profiler.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/road_canal.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "queue.h"
#include "routing_grids.h"

#include <cmath>

struct routing_stats_t {
    uint32_t enemy_routes_calculated;
    uint32_t noncitizen_routes_calculated;
    uint32_t amphibia_routes_calculated;
    uint32_t total_routes_calculated;
};

routing_stats_t g_routing_stats = {0, 0};

struct routing_state_data_t {
    int through_building_id;
};

routing_state_data_t g_routing_state_data;

static bool can_place_on_crossing_no_neighboring(int grid_offset, int terrain_underneath, int terrain_to_avoid, int d_x, int d_y, bool adjacent) {
    // this is similar to the way Pharaoh does it... it only allows to build in alternating rows/columns
    // after starting the road placement. not perfect, but it works.
    d_x++;
    d_y++;
    if (adjacent) {
        if (map_terrain_has_adjacent_y_with_type(grid_offset, terrain_underneath)) {
            if (map_terrain_has_adjacent_x_with_type(grid_offset, terrain_to_avoid))
                return false;

            if (d_x % 2 == 0)
                return false;
        }

        if (map_terrain_has_adjacent_x_with_type(grid_offset, terrain_underneath)) {
            if (map_terrain_has_adjacent_y_with_type(grid_offset, terrain_to_avoid))
                return false;

            if (d_y % 2 == 0)
                return false;
        }
    } else {
        if (!map_terrain_is(grid_offset, terrain_underneath))
            return true;

        if (map_terrain_has_adjacent_x_with_type(grid_offset, terrain_underneath)) {
            if (map_terrain_has_adjacent_x_with_type(grid_offset, terrain_to_avoid))
                return false;

            if (d_x % 2 == 0)
                return false;
        }

        if (map_terrain_has_adjacent_y_with_type(grid_offset, terrain_underneath)) {
            if (map_terrain_has_adjacent_y_with_type(grid_offset, terrain_to_avoid))
                return false;
            if (d_y % 2 == 0)
                return false;
        }
    }
    return true;
}

void callback_calc_distance(int next_offset, int dist) {
    OZZY_PROFILER_FUNCTION();
    if (map_grid_get(routing_land_citizen, next_offset) >= CITIZEN_0_ROAD)
        enqueue(next_offset, dist);
}

void map_routing_calculate_distances(tile2i tile) {
    ++g_routing_stats.total_routes_calculated;
    route_queue(tile.grid_offset(), -1, callback_calc_distance);
}

static void callback_calc_distance_water_boat(int next_offset, int dist) {
    if (map_grid_get(routing_tiles_water, next_offset) != WATER_N1_BLOCKED
        && map_grid_get(routing_tiles_water, next_offset) != WATER_N3_LOW_BRIDGE) {
        enqueue(next_offset, dist);
        if (map_grid_get(routing_tiles_water, next_offset) == WATER_N2_MAP_EDGE) {
            int v = map_grid_get(routing_distance, next_offset);
            //            safe_i16(routing_distance)->items[next_offset] += 4;
            map_grid_set(routing_distance, next_offset, v + 4);
        }
    }
}

void map_routing_calculate_distances_water_boat(tile2i tile) {
    assert(tile.valid());
    int grid_offset = tile.grid_offset();
    if (map_grid_get(routing_tiles_water, grid_offset) == WATER_N1_BLOCKED) {
        clear_distances();
    } else {
        route_queue_boat(grid_offset, callback_calc_distance_water_boat);
    }
}

static void callback_calc_distance_deepwater(int next_offset, int dist) {
    if (map_grid_get(routing_tiles_water, next_offset) != WATER_N1_BLOCKED) {
        if (map_terrain_is(next_offset, TERRAIN_DEEPWATER)) {
            enqueue(next_offset, dist);
        }
    }
}
void map_routing_calculate_distances_deepwater(tile2i tile) {
    int grid_offset = tile.grid_offset();
    if (map_grid_get(routing_tiles_water, grid_offset) == WATER_N1_BLOCKED) {
        clear_distances();
    } else {
        route_queue_dir8(grid_offset, callback_calc_distance_deepwater);
    }
}
static void callback_calc_distance_build_wall(int next_offset, int dist) {
    if (map_grid_get(routing_land_citizen, next_offset) == CITIZEN_4_CLEAR_TERRAIN) {
        enqueue(next_offset, dist);
    }
}
static void callback_calc_distance_build_road(int next_offset, int dist) {
    bool blocked = false;
    int d_x = MAP_X(next_offset) - MAP_X(queue_get(0));
    int d_y = MAP_Y(next_offset) - MAP_Y(queue_get(0));
    switch (map_grid_get(routing_land_citizen, next_offset)) {
    case CITIZEN_N3_CANAL:
        if (!map_can_place_road_under_canal(tile2i(next_offset)))
            blocked = true;
        if (!can_place_on_crossing_no_neighboring(next_offset, TERRAIN_CANAL, TERRAIN_ROAD, d_x, d_y, false))
            blocked = true;
        break;

    case CITIZEN_2_PASSABLE_TERRAIN: // rubble, garden, access ramp
    case CITIZEN_N1_BLOCKED:         // non-empty land
        if (!map_terrain_is(next_offset, TERRAIN_FLOODPLAIN) || map_terrain_is(next_offset, TERRAIN_WATER)
            || map_terrain_is(next_offset, TERRAIN_BUILDING))
            blocked = true;
        break;

    default:
        if (!map_terrain_is(next_offset, TERRAIN_FLOODPLAIN)
            && map_terrain_has_adjecent_with_type(next_offset, TERRAIN_FLOODPLAIN)) { // on the EDGE of floodplains
            if (map_terrain_count_directly_adjacent_with_type(next_offset, TERRAIN_FLOODPLAIN) != 1)
                blocked = true;
            else if (!can_place_on_crossing_no_neighboring(
                       next_offset, TERRAIN_FLOODPLAIN, TERRAIN_ROAD, d_x, d_y, true))
                blocked = true;
        }
        break;
    }
    if (!blocked)
        enqueue(next_offset, dist);
}

static void callback_calc_distance_build_aqueduct(int next_offset, int dist) {
    bool blocked = false;
    int d_x = MAP_X(next_offset) - MAP_X(queue_get(0));
    int d_y = MAP_Y(next_offset) - MAP_Y(queue_get(0));
    switch (map_grid_get(routing_land_citizen, next_offset)) {
    case CITIZEN_0_ROAD: // rubble, garden, access ramp
        if (!map_can_place_canal_on_road(tile2i(next_offset)))
            blocked = true;
        if (!can_place_on_crossing_no_neighboring(next_offset, TERRAIN_ROAD, TERRAIN_CANAL, d_x, d_y, false))
            blocked = true;
        break;

    case CITIZEN_2_PASSABLE_TERRAIN: // rubble, garden, access ramp
    case CITIZEN_N1_BLOCKED:         // non-empty land
        if (!map_terrain_is(next_offset, TERRAIN_FLOODPLAIN) || map_terrain_is(next_offset, TERRAIN_WATER)
            || map_terrain_is(next_offset, TERRAIN_BUILDING))
            blocked = true;
        break;

    default:
        if (!map_terrain_is(next_offset, TERRAIN_FLOODPLAIN)
            && map_terrain_has_adjecent_with_type(next_offset, TERRAIN_FLOODPLAIN)) { // on the EDGE of floodplains
            blocked = true; // CAN NOT place canals on floodplain edges directly in Pharaoh
        }
        break;
    }
    if (!blocked)
        enqueue(next_offset, dist);
}

bool map_can_place_initial_road_or_canal(int grid_offset, int is_aqueduct) {
    switch (map_grid_get(routing_land_citizen, grid_offset)) {
    case CITIZEN_N1_BLOCKED:
        // not open land, can only if:
        // - aqueduct should be placed, and:
        // - land is a reservoir building OR an aqueduct
        if (!map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN) || map_terrain_is(grid_offset, TERRAIN_WATER)) {
            return false;
        }
        break;

    case CITIZEN_2_PASSABLE_TERRAIN:
        return false;
        break;

    case CITIZEN_0_ROAD:
        if (is_aqueduct) {
            if (!map_can_place_canal_on_road(tile2i(grid_offset)))
                return false;

            if (!can_place_on_crossing_no_neighboring(grid_offset, TERRAIN_ROAD, TERRAIN_CANAL, 0, 0, false))
                return false;
        }
        break;

    case CITIZEN_N3_CANAL:
        if (!is_aqueduct) {
            if (!map_can_place_road_under_canal(tile2i(grid_offset)))
                return false;
            if (!can_place_on_crossing_no_neighboring(grid_offset, TERRAIN_CANAL, TERRAIN_ROAD, 0, 0, false))
                return false;
        }
        break;

    default:
        if (!map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)
            && map_terrain_has_adjecent_with_type(grid_offset, TERRAIN_FLOODPLAIN)) { // on the EDGE of floodplains
            if (map_terrain_count_directly_adjacent_with_type(grid_offset, TERRAIN_FLOODPLAIN)
                != 1) // floodplain CORNER
                return false;
            else { // floodplain EDGES
                if (is_aqueduct)
                    return false; // CAN NOT place canals on floodplain edges directly in Pharaoh
                else if (!can_place_on_crossing_no_neighboring(grid_offset, TERRAIN_FLOODPLAIN, TERRAIN_ROAD, 0, 0, true))
                    return false;
            }
        }
        break;
    }

    // herd spawn points
    if (g_city_animals.breeding_ground_at(tile2i(grid_offset), 1)) {
        return false;
    }
    return true;
}

bool map_routing_ferry_has_routes(building *b) {
    svector<building *, 64> ferries;
    buildings_get(ferries, BUILDING_FERRY);

    for (const auto &it : ferries) {
        water_access_tiles fpoints_begin = map_water_get_access_points(*it, it->dcast()->get_orientation(), 1);
        water_access_tiles fpoints_end = map_water_get_access_points(*b, b->dcast()->get_orientation(), 1);

        std::array<uint8_t, 500> path_data;
        map_routing_calculate_distances_water_boat(fpoints_begin.point_a);
        int path_length = map_routing_get_path_on_water(path_data.data(), fpoints_end.point_a, false);

        if (path_length > 0) {
            return true;
        }
    }
    return false;
}

bool map_routing_calculate_distances_for_building(e_routed_mode type, tile2i tile) {
    clear_distances();
    int source_offset = tile.grid_offset();

    switch (type) {
    case ROUTED_BUILDING_ROAD:
        if (!map_can_place_initial_road_or_canal(source_offset, false))
            return false;

        if (map_terrain_is(source_offset, TERRAIN_CANAL) && !map_can_place_road_under_canal(tile))
            return false;

        route_queue(source_offset, -1, callback_calc_distance_build_road);
        break;

    case ROUTED_BUILDING_CANALS:
        if (!map_can_place_initial_road_or_canal(source_offset, true))
            return false;

        if (map_terrain_is(source_offset, TERRAIN_ROAD) && !map_can_place_canal_on_road(tile))
            return false;

        route_queue(source_offset, -1, callback_calc_distance_build_aqueduct);
        break;

    case ROUTED_BUILDING_WALL:
        route_queue(tile.grid_offset(), -1, callback_calc_distance_build_wall);
        break;

    default:
        assert(false);
    }
    ++g_routing_stats.total_routes_calculated;
    return true;
}

static bool callback_delete_wall_canal(int next_offset, int dist) {
    if (map_grid_get(routing_land_citizen, next_offset) < CITIZEN_0_ROAD) {
        if (map_terrain_is(next_offset, TERRAIN_CANAL | TERRAIN_WALL)) {
            map_terrain_remove(next_offset, TERRAIN_CLEARABLE);
            return true;
        }
    } else {
        enqueue(next_offset, dist);
    }
    return false;
}

void map_routing_delete_first_wall_or_aqueduct(int x, int y) {
    ++g_routing_stats.total_routes_calculated;
    route_queue_until(MAP_OFFSET(x, y), callback_delete_wall_canal);
}

bool figure::is_fighting_friendly() {
    return is_friendly() && in_attack();
}

bool figure::is_fighting_enemy() {
    return !is_friendly() && in_attack();
}

static int has_fighting_friendly(int grid_offset) {
    return map_figure_foreach_until(grid_offset, TEST_SEARCH_FIGHTING_FRIENDLY);
}

static int has_fighting_enemy(int grid_offset) {
    return map_figure_foreach_until(grid_offset, TEST_SEARCH_FIGHTING_ENEMY);
}

static bool callback_travel_found_terrain(int next_offset, int dist, int terrain_type) {
    if (map_grid_get(routing_land_citizen, next_offset) >= CITIZEN_0_ROAD && !has_fighting_friendly(next_offset)) {
        enqueue(next_offset, dist);
        if (map_terrain_is(next_offset, terrain_type)) {
            return true;
        }
    }
    return false;
}

bool map_routing_citizen_found_terrain(tile2i src, tile2i *dst, int terrain_type) {
    int src_offset = src.grid_offset();
    ++g_routing_stats.total_routes_calculated;
    return route_queue_until_terrain(src_offset, terrain_type, dst, callback_travel_found_terrain);
}

resource_tile map_routing_citizen_found_reeds(tile2i src) {
    auto callback_travel_found_reeds = [] (int next_offset, int dist) {
        if (map_grid_get(routing_land_citizen, next_offset) >= CITIZEN_0_ROAD && !has_fighting_friendly(next_offset)) {
            enqueue(next_offset, dist);
            if (map_terrain_is(next_offset, TERRAIN_MARSHLAND)) {
                // requires tile to be fully within a 3x3 marshland area
                if (map_terrain_all_tiles_in_radius_are(tile2i(next_offset), 1, 1, TERRAIN_MARSHLAND)) {
                    if (can_harvest_point(next_offset))
                        return true;
                }
            }
        }
        return false;
    };

    int src_offset = src.grid_offset();
    ++g_routing_stats.total_routes_calculated;
    tile2i dst;
    const bool found = route_queue_until_found(src_offset, dst, callback_travel_found_reeds);

    return { found ? RESOURCE_REEDS : RESOURCE_NONE, dst };
}

resource_tile map_routing_citizen_found_timber(tile2i src) {
    auto callback_travel_found_timber = [] (int next_offset, int dist) {
        if ((map_grid_get(routing_land_citizen, next_offset) >= CITIZEN_0_ROAD || map_terrain_is(next_offset, TERRAIN_TREE))
            && !has_fighting_friendly(next_offset)) {
            enqueue(next_offset, dist);
            if (map_terrain_is(next_offset, TERRAIN_TREE)) {
                if (can_harvest_point(next_offset))
                    return true;
            }
        }
        return false;
        };

    int src_offset = src.grid_offset();
    ++g_routing_stats.total_routes_calculated;
    tile2i dst;
    const bool found = route_queue_until_found(src_offset, dst, callback_travel_found_timber);
    return { found ? RESOURCE_TIMBER : RESOURCE_NONE, dst };
}

static void callback_travel_citizen_land(int next_offset, int dist) {
    if (map_grid_get(routing_land_citizen, next_offset) >= CITIZEN_0_ROAD 
        && !has_fighting_friendly(next_offset)
        && (!map_terrain_is(next_offset, TERRAIN_WATER) || map_terrain_is(next_offset, TERRAIN_FERRY_ROUTE))) {
        enqueue(next_offset, dist);
    }
}

bool map_routing_citizen_can_travel_over_land(tile2i src, tile2i dst) {
    int src_offset = src.grid_offset();
    int dst_offset = dst.grid_offset();
    ++g_routing_stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_citizen_land);
    return map_grid_get(routing_distance, dst_offset) != 0;
}

static void callback_travel_citizen_road(int next_offset, int dist) {
    if (map_grid_get(routing_land_citizen, next_offset) >= CITIZEN_0_ROAD
        && map_grid_get(routing_land_citizen, next_offset) < CITIZEN_2_PASSABLE_TERRAIN) {
        enqueue(next_offset, dist);
    }
}
bool map_routing_citizen_can_travel_over_road(tile2i src, tile2i dst) {
    int src_offset = src.grid_offset();
    int dst_offset = dst.grid_offset();
    ++g_routing_stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_citizen_road);
    return map_grid_get(routing_distance, dst_offset) != 0;
}

static void callback_travel_citizen_road_garden(int next_offset, int dist) {
    if (map_grid_get(routing_land_citizen, next_offset) >= CITIZEN_0_ROAD
        && map_grid_get(routing_land_citizen, next_offset) <= CITIZEN_2_PASSABLE_TERRAIN) {
        enqueue(next_offset, dist);
    }
}

bool map_routing_citizen_can_travel_over_road_garden(int src_x, int src_y, int dst_x, int dst_y) {
    int src_offset = MAP_OFFSET(src_x, src_y);
    int dst_offset = MAP_OFFSET(dst_x, dst_y);
    ++g_routing_stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_citizen_road_garden);
    return map_grid_get(routing_distance, dst_offset) != 0;
}
static void callback_travel_walls(int next_offset, int dist) {
    if (map_grid_get(routing_tiles_walls, next_offset) >= WALL_0_PASSABLE
        && map_grid_get(routing_tiles_walls, next_offset) <= 2) {
        enqueue(next_offset, dist);
    }
}

bool map_routing_can_travel_over_walls(int src_x, int src_y, int dst_x, int dst_y) {
    int src_offset = MAP_OFFSET(src_x, src_y);
    int dst_offset = MAP_OFFSET(dst_x, dst_y);
    ++g_routing_stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_walls);
    return map_grid_get(routing_distance, dst_offset) != 0;
}

static void callback_travel_noncitizen_land_through_building(int next_offset, int dist) {
    if (has_fighting_enemy(next_offset)) {
        return;
    }

    if (map_grid_get(routing_land_noncitizen, next_offset) == NONCITIZEN_0_PASSABLE) {
        return enqueue(next_offset, dist);
    }
       
    if (map_grid_get(routing_land_noncitizen, next_offset) == NONCITIZEN_2_CLEARABLE) {
        return enqueue(next_offset, dist);
    }
        
    if (g_routing_state_data.through_building_id > 0 && map_building_at(next_offset) == g_routing_state_data.through_building_id) {
        return enqueue(next_offset, dist);
    }
}

static void callback_travel_amphibia_land_water_through_building(int next_offset, int dist) {
    if (has_fighting_enemy(next_offset)) {
        return;
    }

    const int32_t pas = map_grid_get(routing_land_amphibia, next_offset);
    if (map_grid_get(routing_land_amphibia, next_offset) == AMPHIBIA_0_PASSABLE) {
        return enqueue(next_offset, dist);
    }

    if (g_routing_state_data.through_building_id > 0 
        && map_grid_get(routing_land_amphibia, next_offset) == AMPHIBIA_1_BUILDING
        && map_building_at(next_offset) == g_routing_state_data.through_building_id) {
        return enqueue(next_offset, dist);
    }
}

static void callback_travel_amphibia_land_water(int next_offset, int dist) {
    if (has_fighting_enemy(next_offset)) {
        return;
    }

    const int32_t pas = map_grid_get(routing_land_amphibia, next_offset);
    if (pas == AMPHIBIA_0_PASSABLE
        || (map_grid_get(routing_land_amphibia, next_offset) == AMPHIBIA_1_BUILDING
            && map_routing_tile_check(TERRAIN_USAGE_AMPHIBIA, next_offset) >= 0)) {
        enqueue(next_offset, dist);
    }
}

static void callback_travel_noncitizen_land(int next_offset, int dist) {
    if (has_fighting_enemy(next_offset)) {
        return;
    }

    const int32_t pas = map_grid_get(routing_land_noncitizen, next_offset);
    if (pas >= NONCITIZEN_0_PASSABLE && pas < NONCITIZEN_5_FORT) {
        enqueue(next_offset, dist);
    }
}

bool map_routing_amphibia_can_travel_over_land_water(tile2i src, tile2i dst, int only_through_building_id, int max_tiles) {
    int src_offset = src.grid_offset();
    int dst_offset = dst.grid_offset();

    ++g_routing_stats.total_routes_calculated;
    ++g_routing_stats.enemy_routes_calculated;
    
    if (only_through_building_id > 0) {
        g_routing_state_data.through_building_id = only_through_building_id;
        route_queue(src_offset, dst_offset, callback_travel_amphibia_land_water_through_building);
    } else {
        route_queue_max(src_offset, dst_offset, max_tiles, callback_travel_amphibia_land_water);
    }

    return map_grid_get(routing_distance, dst_offset) != 0;
}

bool map_routing_enemy_can_travel_over_land(tile2i src, tile2i dst, int only_through_building_id, int max_tiles) {
    int src_offset = src.grid_offset();
    int dst_offset = dst.grid_offset();

    ++g_routing_stats.total_routes_calculated;
    ++g_routing_stats.enemy_routes_calculated;

    if (only_through_building_id > 0) {
        g_routing_state_data.through_building_id = only_through_building_id;
        route_queue(src_offset, dst_offset, callback_travel_noncitizen_land_through_building);
    } else {
        route_queue_max(src_offset, dst_offset, max_tiles, callback_travel_noncitizen_land);
    }

    return map_grid_get(routing_distance, dst_offset) != 0;
}

static void callback_travel_enemy_through_everything(int next_offset, int dist) {
    if (map_grid_get(routing_land_noncitizen, next_offset) >= NONCITIZEN_0_PASSABLE)
        enqueue(next_offset, dist);
}

bool map_routing_enemy_can_travel_through_everything(tile2i src, tile2i dst) {
    int src_offset = src.grid_offset();
    int dst_offset = dst.grid_offset();

    ++g_routing_stats.total_routes_calculated;
    ++g_routing_stats.enemy_routes_calculated;
    
    route_queue(src_offset, dst_offset, callback_travel_enemy_through_everything);
    return map_grid_get(routing_distance, dst_offset) != 0;
}

bool map_routing_noncitizen_can_travel_over_land(tile2i src, tile2i dst, int only_through_building_id, int max_tiles) {
    int src_offset = src.grid_offset();
    int dst_offset = dst.grid_offset();

    ++g_routing_stats.total_routes_calculated;
    ++g_routing_stats.noncitizen_routes_calculated;

    if (only_through_building_id > 0) {
        g_routing_state_data.through_building_id = only_through_building_id;
        route_queue(src_offset, dst_offset, callback_travel_noncitizen_land_through_building);
    } else {
        route_queue_max(src_offset, dst_offset, max_tiles, callback_travel_noncitizen_land);
    }

    return map_grid_get(routing_distance, dst_offset) != 0;
}

static void callback_travel_noncitizen_through_everything(int next_offset, int dist) {
    if (map_grid_get(routing_land_noncitizen, next_offset) >= NONCITIZEN_0_PASSABLE)
        enqueue(next_offset, dist);
}

bool map_routing_noncitizen_can_travel_through_everything(tile2i src, tile2i dst) {
    int src_offset = src.grid_offset();
    int dst_offset = dst.grid_offset();
    ++g_routing_stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_noncitizen_through_everything);
    return map_grid_get(routing_distance, dst_offset) != 0;
}

void map_routing_block(int x, int y, int size) {
    if (!map_grid_is_inside(tile2i(x, y), size))
        return;

    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            map_grid_set(routing_distance, MAP_OFFSET(x + dx, y + dy), 0);
        }
    }
}

int map_routing_distance(int grid_offset) {
    return map_grid_get(routing_distance, grid_offset);
}

int map_citizen_grid(int grid_offset) {
    return map_grid_get(routing_land_citizen, grid_offset);
}

int map_noncitizen_grid(int grid_offset) {
    return map_grid_get(routing_land_noncitizen, grid_offset);
}

bool map_noncitizen_is_passable(int grid_offset) {
    return map_noncitizen_grid(grid_offset) == NONCITIZEN_0_PASSABLE;
}

int map_amphibia_grid(int grid_offset) {
    return map_grid_get(routing_land_amphibia, grid_offset);
}

int map_water_grid(int grid_offset) {
    return map_grid_get(routing_tiles_water, grid_offset);
}

io_buffer* iob_routing_stats = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind____skip(4);
    iob->bind____skip(4); // resets to zero at the start of a new scenario
    iob->bind____skip(4); // unused counter
    iob->bind_u32(g_routing_stats.total_routes_calculated);
    iob->bind_u32(g_routing_stats.enemy_routes_calculated);
    iob->bind_u32(g_routing_stats.noncitizen_routes_calculated);
    iob->bind_u32(g_routing_stats.amphibia_routes_calculated);
    iob->bind____skip(4); // ??? coords?
    iob->bind____skip(8); // ??? coords?
    iob->bind____skip(2); // ??? something empire map related?
    iob->bind____skip(8); // ??? something storage related?
});
#include "routing.h"
#include <cmath>
#include <figure/formation_herd.h>
#include <grid/vegetation.h>

#include "building/building.h"
#include "core/game_environment.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/road_aqueduct.h"
#include "grid/terrain.h"
#include "queue.h"
#include "routing_grids.h"

static struct {
    int total_routes_calculated;
    int enemy_routes_calculated;
} stats = {0, 0};
static struct {
    int through_building_id;
} state;

static bool can_place_on_crossing_no_neighboring(int grid_offset, int terrain_underneath, int terrain_to_avoid, int d_x,
                                                 int d_y, bool adjacent) {
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

static void callback_calc_distance(int next_offset, int dist) {
    if (map_grid_get(&terrain_land_citizen, next_offset) >= CITIZEN_0_ROAD)
        enqueue(next_offset, dist);
}
void map_routing_calculate_distances(int x, int y) {
    ++stats.total_routes_calculated;
    route_queue(MAP_OFFSET(x, y), -1, callback_calc_distance);
}
static void callback_calc_distance_water_boat(int next_offset, int dist) {
    if (map_grid_get(&terrain_water, next_offset) != WATER_N1_BLOCKED
        && map_grid_get(&terrain_water, next_offset) != WATER_N3_LOW_BRIDGE) {
        enqueue(next_offset, dist);
        if (map_grid_get(&terrain_water, next_offset) == WATER_N2_MAP_EDGE) {
            int v = map_grid_get(&routing_distance, next_offset);
            //            safe_i16(&routing_distance)->items[next_offset] += 4;
            map_grid_set(&routing_distance, next_offset, v + 4);
        }
    }
}
void map_routing_calculate_distances_water_boat(int x, int y) {
    int grid_offset = MAP_OFFSET(x, y);
    if (map_grid_get(&terrain_water, grid_offset) == WATER_N1_BLOCKED)
        clear_distances();
    else
        route_queue_boat(grid_offset, callback_calc_distance_water_boat);
}
static void callback_calc_distance_water_flotsam(int next_offset, int dist) {
    if (map_grid_get(&terrain_water, next_offset) != WATER_N1_BLOCKED)
        enqueue(next_offset, dist);
}
void map_routing_calculate_distances_water_flotsam(int x, int y) {
    int grid_offset = MAP_OFFSET(x, y);
    if (map_grid_get(&terrain_water, grid_offset) == WATER_N1_BLOCKED)
        clear_distances();
    else
        route_queue_dir8(grid_offset, callback_calc_distance_water_flotsam);
}
static void callback_calc_distance_build_wall(int next_offset, int dist) {
    if (map_grid_get(&terrain_land_citizen, next_offset) == CITIZEN_4_CLEAR_TERRAIN)
        enqueue(next_offset, dist);
}
static void callback_calc_distance_build_road(int next_offset, int dist) {
    bool blocked = false;
    int d_x = MAP_X(next_offset) - MAP_X(queue_get(0));
    int d_y = MAP_Y(next_offset) - MAP_Y(queue_get(0));
    switch (map_grid_get(&terrain_land_citizen, next_offset)) {
    case CITIZEN_N3_AQUEDUCT:
        if (!map_can_place_road_under_aqueduct(next_offset))
            blocked = true;
        if (!can_place_on_crossing_no_neighboring(next_offset, TERRAIN_AQUEDUCT, TERRAIN_ROAD, d_x, d_y, false))
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
    switch (map_grid_get(&terrain_land_citizen, next_offset)) {
    case CITIZEN_0_ROAD: // rubble, garden, access ramp
        if (!map_can_place_aqueduct_on_road(next_offset))
            blocked = true;
        if (!can_place_on_crossing_no_neighboring(next_offset, TERRAIN_ROAD, TERRAIN_AQUEDUCT, d_x, d_y, false))
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
            blocked = true;                                                           // CAN NOT place canals on floodplain edges directly in Pharaoh
        }
        break;
    }
    if (!blocked)
        enqueue(next_offset, dist);
}
bool map_can_place_initial_road_or_aqueduct(int grid_offset, int is_aqueduct) {
    switch (map_grid_get(&terrain_land_citizen, grid_offset)) {
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
            if (!map_can_place_aqueduct_on_road(grid_offset))
                return false;
            if (!can_place_on_crossing_no_neighboring(grid_offset, TERRAIN_ROAD, TERRAIN_AQUEDUCT, 0, 0, false))
                return false;
        }
        break;
    case CITIZEN_N3_AQUEDUCT:
        if (!is_aqueduct) {
            if (!map_can_place_road_under_aqueduct(grid_offset))
                return false;
            if (!can_place_on_crossing_no_neighboring(grid_offset, TERRAIN_AQUEDUCT, TERRAIN_ROAD, 0, 0, false))
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
                else if (!can_place_on_crossing_no_neighboring(
                           grid_offset, TERRAIN_FLOODPLAIN, TERRAIN_ROAD, 0, 0, true))
                    return false;
            }
        }
        break;
    }

    // herd spawn points
    if (formation_herd_breeding_ground_at(MAP_X(grid_offset), MAP_Y(grid_offset), 1))
        return false;
    return true;
}
bool map_routing_calculate_distances_for_building(routed_int type, int x, int y) {
    clear_distances();
    int source_offset = MAP_OFFSET(x, y);

    switch (type) {
    case ROUTED_BUILDING_ROAD:
        if (!map_can_place_initial_road_or_aqueduct(source_offset, false))
            return false;
        if (map_terrain_is(source_offset, TERRAIN_AQUEDUCT) && !map_can_place_road_under_aqueduct(source_offset))
            return false;
        route_queue(source_offset, -1, callback_calc_distance_build_road);
        break;
    case ROUTED_BUILDING_AQUEDUCT:
        if (!map_can_place_initial_road_or_aqueduct(source_offset, true))
            return false;
        if (map_terrain_is(source_offset, TERRAIN_ROAD) && !map_can_place_aqueduct_on_road(source_offset))
            return false;
        route_queue(source_offset, -1, callback_calc_distance_build_aqueduct);
        break;
    case ROUTED_BUILDING_WALL:
        route_queue(MAP_OFFSET(x, y), -1, callback_calc_distance_build_wall);
        break;
    }
    ++stats.total_routes_calculated;
    return true;
}
static bool callback_delete_wall_aqueduct(int next_offset, int dist) {
    if (map_grid_get(&terrain_land_citizen, next_offset) < CITIZEN_0_ROAD) {
        if (map_terrain_is(next_offset, TERRAIN_AQUEDUCT | TERRAIN_WALL)) {
            map_terrain_remove(next_offset, TERRAIN_CLEARABLE);
            return true;
        }
    } else
        enqueue(next_offset, dist);
    return false;
}
void map_routing_delete_first_wall_or_aqueduct(int x, int y) {
    ++stats.total_routes_calculated;
    route_queue_until(MAP_OFFSET(x, y), callback_delete_wall_aqueduct);
}

bool figure::is_fighting_friendly() {
    return is_friendly && action_state == FIGURE_ACTION_150_ATTACK;
}
bool figure::is_fighting_enemy() {
    return !is_friendly && action_state == FIGURE_ACTION_150_ATTACK;
}

static int has_fighting_friendly(int grid_offset) {
    return map_figure_foreach_until(grid_offset, TEST_SEARCH_FIGHTING_FRIENDLY);
}
static int has_fighting_enemy(int grid_offset) {
    return map_figure_foreach_until(grid_offset, TEST_SEARCH_FIGHTING_ENEMY);
}

static bool callback_travel_found_terrain(int next_offset, int dist, int terrain_type) {
    if (map_grid_get(&terrain_land_citizen, next_offset) >= CITIZEN_0_ROAD && !has_fighting_friendly(next_offset)) {
        enqueue(next_offset, dist);
        if (map_terrain_is(next_offset, terrain_type))
            return true;
    }
    return false;
}
bool map_routing_citizen_found_terrain(int src_x, int src_y, int* dst_x, int* dst_y, int terrain_type) {
    int src_offset = MAP_OFFSET(src_x, src_y);
    ++stats.total_routes_calculated;
    bool found = route_queue_until_terrain(src_offset, terrain_type, dst_x, dst_y, callback_travel_found_terrain);
    return found;
}
static bool callback_travel_found_reeds(int next_offset, int dist) {
    if (map_grid_get(&terrain_land_citizen, next_offset) >= CITIZEN_0_ROAD && !has_fighting_friendly(next_offset)) {
        enqueue(next_offset, dist);
        if (map_terrain_is(next_offset, TERRAIN_MARSHLAND)) {
            int t_x = MAP_X(next_offset);
            int t_y = MAP_Y(next_offset);
            // requires tile to be fully within a 3x3 marshland area
            if (map_terrain_all_tiles_in_radius_are(t_x, t_y, 1, 1, TERRAIN_MARSHLAND))
                if (can_harvest_point(next_offset))
                    return true;
        }
    }
    return false;
}
bool map_routing_citizen_found_reeds(int src_x, int src_y, int* dst_x, int* dst_y) {
    int src_offset = MAP_OFFSET(src_x, src_y);
    ++stats.total_routes_calculated;
    bool found = route_queue_until_found(src_offset, dst_x, dst_y, callback_travel_found_reeds);
    return found;
}
static bool callback_travel_found_timber(int next_offset, int dist) {
    if ((map_grid_get(&terrain_land_citizen, next_offset) >= CITIZEN_0_ROAD
         || map_terrain_is(next_offset, TERRAIN_TREE))
        && !has_fighting_friendly(next_offset)) {
        enqueue(next_offset, dist);
        if (map_terrain_is(next_offset, TERRAIN_TREE))
            if (can_harvest_point(next_offset))
                return true;
    }
    return false;
}
bool map_routing_citizen_found_timber(int src_x, int src_y, int* dst_x, int* dst_y) {
    int src_offset = MAP_OFFSET(src_x, src_y);
    ++stats.total_routes_calculated;
    bool found = route_queue_until_found(src_offset, dst_x, dst_y, callback_travel_found_timber);
    return found;
}

static void callback_travel_citizen_land(int next_offset, int dist) {
    if (map_grid_get(&terrain_land_citizen, next_offset) >= CITIZEN_0_ROAD && !has_fighting_friendly(next_offset))
        enqueue(next_offset, dist);
}
bool map_routing_citizen_can_travel_over_land(int src_x, int src_y, int dst_x, int dst_y) {
    int src_offset = MAP_OFFSET(src_x, src_y);
    int dst_offset = MAP_OFFSET(dst_x, dst_y);
    ++stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_citizen_land);
    return map_grid_get(&routing_distance, dst_offset) != 0;
}
static void callback_travel_citizen_road(int next_offset, int dist) {
    if (map_grid_get(&terrain_land_citizen, next_offset) >= CITIZEN_0_ROAD
        && map_grid_get(&terrain_land_citizen, next_offset) < CITIZEN_2_PASSABLE_TERRAIN) {
        enqueue(next_offset, dist);
    }
}
bool map_routing_citizen_can_travel_over_road(int src_x, int src_y, int dst_x, int dst_y) {
    int src_offset = MAP_OFFSET(src_x, src_y);
    int dst_offset = MAP_OFFSET(dst_x, dst_y);
    ++stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_citizen_road);
    return map_grid_get(&routing_distance, dst_offset) != 0;
}
static void callback_travel_citizen_road_garden(int next_offset, int dist) {
    if (map_grid_get(&terrain_land_citizen, next_offset) >= CITIZEN_0_ROAD
        && map_grid_get(&terrain_land_citizen, next_offset) <= CITIZEN_2_PASSABLE_TERRAIN) {
        enqueue(next_offset, dist);
    }
}
bool map_routing_citizen_can_travel_over_road_garden(int src_x, int src_y, int dst_x, int dst_y) {
    int src_offset = MAP_OFFSET(src_x, src_y);
    int dst_offset = MAP_OFFSET(dst_x, dst_y);
    ++stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_citizen_road_garden);
    return map_grid_get(&routing_distance, dst_offset) != 0;
}
static void callback_travel_walls(int next_offset, int dist) {
    if (map_grid_get(&terrain_walls, next_offset) >= WALL_0_PASSABLE
        && map_grid_get(&terrain_walls, next_offset) <= 2) {
        enqueue(next_offset, dist);
    }
}
bool map_routing_can_travel_over_walls(int src_x, int src_y, int dst_x, int dst_y) {
    int src_offset = MAP_OFFSET(src_x, src_y);
    int dst_offset = MAP_OFFSET(dst_x, dst_y);
    ++stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_walls);
    return map_grid_get(&routing_distance, dst_offset) != 0;
}
static void callback_travel_noncitizen_land_through_building(int next_offset, int dist) {
    if (!has_fighting_enemy(next_offset)) {
        if (map_grid_get(&terrain_land_noncitizen, next_offset) == NONCITIZEN_0_PASSABLE
            || map_grid_get(&terrain_land_noncitizen, next_offset) == NONCITIZEN_2_CLEARABLE
            || (map_grid_get(&terrain_land_noncitizen, next_offset) == NONCITIZEN_1_BUILDING
                && map_building_at(next_offset) == state.through_building_id)) {
            enqueue(next_offset, dist);
        }
    }
}
static void callback_travel_noncitizen_land(int next_offset, int dist) {
    if (!has_fighting_enemy(next_offset)) {
        if (map_grid_get(&terrain_land_noncitizen, next_offset) >= NONCITIZEN_0_PASSABLE
            && map_grid_get(&terrain_land_noncitizen, next_offset) < NONCITIZEN_5_FORT) {
            enqueue(next_offset, dist);
        }
    }
}
bool map_routing_noncitizen_can_travel_over_land(int src_x, int src_y, int dst_x, int dst_y,
                                                 int only_through_building_id, int max_tiles) {
    int src_offset = MAP_OFFSET(src_x, src_y);
    int dst_offset = MAP_OFFSET(dst_x, dst_y);
    ++stats.total_routes_calculated;
    ++stats.enemy_routes_calculated;
    if (only_through_building_id) {
        state.through_building_id = only_through_building_id;
        route_queue(src_offset, dst_offset, callback_travel_noncitizen_land_through_building);
    } else
        route_queue_max(src_offset, dst_offset, max_tiles, callback_travel_noncitizen_land);
    return map_grid_get(&routing_distance, dst_offset) != 0;
}
static void callback_travel_noncitizen_through_everything(int next_offset, int dist) {
    if (map_grid_get(&terrain_land_noncitizen, next_offset) >= NONCITIZEN_0_PASSABLE)
        enqueue(next_offset, dist);
}
bool map_routing_noncitizen_can_travel_through_everything(int src_x, int src_y, int dst_x, int dst_y) {
    int src_offset = MAP_OFFSET(src_x, src_y);
    int dst_offset = MAP_OFFSET(dst_x, dst_y);
    ++stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_noncitizen_through_everything);
    return map_grid_get(&routing_distance, dst_offset) != 0;
}

void map_routing_block(int x, int y, int size) {
    if (!map_grid_is_inside(x, y, size))
        return;
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            map_grid_set(&routing_distance, MAP_OFFSET(x + dx, y + dy), 0);
        }
    }
}
int map_routing_distance(int grid_offset) {
    return map_grid_get(&routing_distance, grid_offset);
}
int map_citizen_grid(int grid_offset) {
    return map_grid_get(&terrain_land_citizen, grid_offset);
}

io_buffer* iob_routing_stats = new io_buffer([](io_buffer* iob) {
    iob->bind____skip(4);
    iob->bind____skip(4); // resets to zero at the start of a new scenario
    iob->bind____skip(4); // unused counter
    iob->bind(BIND_SIGNATURE_UINT32, &stats.enemy_routes_calculated);
    iob->bind(BIND_SIGNATURE_UINT32, &stats.total_routes_calculated);
    iob->bind____skip(4); // unused counter
    iob->bind____skip(8); // ??? coords?
    iob->bind____skip(8); // ??? coords?
    iob->bind____skip(2); // ??? something empire map related?
    iob->bind____skip(8); // ??? something storage related?
});
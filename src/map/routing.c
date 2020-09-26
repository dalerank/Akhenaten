#include "routing.h"

#include "building/building.h"
#include "map/building.h"
#include "map/figure.h"
#include "map/grid.h"
#include "map/road_aqueduct.h"
#include "map/routing_data.h"
#include "map/terrain.h"
#include "core/game_environment.h"

#define MAX_QUEUE 162 * 162//grid_total_size[GAME_ENV]
#define GUARD 50000

static const int ROUTE_OFFSETS[2][8] = {
    {-162, 1, 162, -1, -161, 163, 161, -163},
    {-228, 1, 228, -1, -227, 229, 227, -229}
};

static grid_xx routing_distance = {0, {FS_INT16, FS_INT16}};

static struct {
    int total_routes_calculated;
    int enemy_routes_calculated;
} stats = {0, 0};

static struct {
    int head;
    int tail;
    int items[MAX_QUEUE];
} queue;

static grid_xx water_drag = {0, {FS_UINT8, FS_UINT8}};

static struct {
    int through_building_id;
} state;

static void clear_distances(void)
{
    map_grid_clear(&routing_distance);
}
static int valid_offset(int grid_offset)
{
    return map_grid_is_valid_offset(grid_offset) && map_grid_get(&routing_distance, grid_offset) == 0;
}

static void enqueue(int offset, int dist)
{
    map_grid_set(&routing_distance, offset, dist);
    queue.items[queue.tail++] = offset;
    if (queue.tail >= MAX_QUEUE)
        queue.tail = 0;
}
static void route_queue(int source, int dest, void (*callback)(int next_offset, int dist))
{
//    clear_distances();
    queue.head = queue.tail = 0;
    enqueue(source, 1);
    while (queue.head != queue.tail) {
        int offset = queue.items[queue.head];
        if (offset == dest)
            break;
        int dist = 1 + map_grid_get(&routing_distance, offset);
        for (int i = 0; i < 4; i++) {
            if (valid_offset(offset + ROUTE_OFFSETS[GAME_ENV][i]))
                callback(offset + ROUTE_OFFSETS[GAME_ENV][i], dist);
        }
        if (++queue.head >= MAX_QUEUE)
            queue.head = 0;
    }
}
static void route_queue_until(int source, int (*callback)(int next_offset, int dist))
{
    clear_distances();
    queue.head = queue.tail = 0;
    enqueue(source, 1);
    while (queue.head != queue.tail) {
        int offset = queue.items[queue.head];
        int dist = 1 + map_grid_get(&routing_distance, offset);
        for (int i = 0; i < 4; i++) {
            if (valid_offset(offset + ROUTE_OFFSETS[GAME_ENV][i])) {
                if (!callback(offset + ROUTE_OFFSETS[GAME_ENV][i], dist))
                    break;

            }
        }
        if (++queue.head >= MAX_QUEUE)
            queue.head = 0;

    }
}
static void route_queue_max(int source, int dest, int max_tiles, void (*callback)(int, int))
{
    clear_distances();
    queue.head = queue.tail = 0;
    enqueue(source, 1);
    int tiles = 0;
    while (queue.head != queue.tail) {
        int offset = queue.items[queue.head];
        if (offset == dest) break;
        if (++tiles > max_tiles) break;
        int dist = 1 + map_grid_get(&routing_distance, offset);
        for (int i = 0; i < 4; i++) {
            if (valid_offset(offset + ROUTE_OFFSETS[GAME_ENV][i]))
                callback(offset + ROUTE_OFFSETS[GAME_ENV][i], dist);
        }
        if (++queue.head >= MAX_QUEUE)
            queue.head = 0;
    }
}
static void route_queue_boat(int source, void (*callback)(int, int))
{
    clear_distances();
    map_grid_clear(&water_drag);
    queue.head = queue.tail = 0;
    enqueue(source, 1);
    int tiles = 0;
    while (queue.head != queue.tail) {
        int offset = queue.items[queue.head];
        if (++tiles > GUARD)
            break;

        int drag = map_grid_get(&terrain_water, offset) == WATER_N2_MAP_EDGE ? 4 : 0;
        int v = map_grid_get(&water_drag, offset);
        if (drag && v < drag) {
            queue.items[queue.tail++] = offset;
            if (queue.tail >= MAX_QUEUE)
                queue.tail = 0;
        } else {
            int dist = 1 + map_grid_get(&routing_distance, offset);
            for (int i = 0; i < 4; i++) {
                if (valid_offset(offset + ROUTE_OFFSETS[GAME_ENV][i]))
                    callback(offset + ROUTE_OFFSETS[GAME_ENV][i], dist);
            }
        }
        map_grid_set(&water_drag, offset, v + 1);
        if (++queue.head >= MAX_QUEUE)
            queue.head = 0;
    }
}
static void route_queue_dir8(int source, void (*callback)(int, int))
{
    clear_distances();
    queue.head = queue.tail = 0;
    enqueue(source, 1);
    int tiles = 0;
    while (queue.head != queue.tail) {
        if (++tiles > GUARD)
            break;
        int offset = queue.items[queue.head];
        int dist = 1 + map_grid_get(&routing_distance, offset);
        for (int i = 0; i < 8; i++) {
            if (valid_offset(offset + ROUTE_OFFSETS[GAME_ENV][i]))
                callback(offset + ROUTE_OFFSETS[GAME_ENV][i], dist);
        }
        if (++queue.head >= MAX_QUEUE)
            queue.head = 0;
    }
}

static void callback_calc_distance(int next_offset, int dist)
{
    if (map_grid_get(&terrain_land_citizen, next_offset) >= CITIZEN_0_ROAD)
        enqueue(next_offset, dist);
}
void map_routing_calculate_distances(int x, int y)
{
    ++stats.total_routes_calculated;
    route_queue(map_grid_offset(x, y), -1, callback_calc_distance);
}
static void callback_calc_distance_water_boat(int next_offset, int dist)
{
    if (map_grid_get(&terrain_water, next_offset) != WATER_N1_BLOCKED &&
        map_grid_get(&terrain_water, next_offset) != WATER_N3_LOW_BRIDGE) {
        enqueue(next_offset, dist);
        if (map_grid_get(&terrain_water, next_offset) == WATER_N2_MAP_EDGE) {
            int v = map_grid_get(&routing_distance, next_offset);
//            safe_i16(&routing_distance)->items[next_offset] += 4;
            map_grid_set(&routing_distance, next_offset, v + 4);
        }
    }
}
void map_routing_calculate_distances_water_boat(int x, int y)
{
    int grid_offset = map_grid_offset(x, y);
    if (map_grid_get(&terrain_water, grid_offset) == WATER_N1_BLOCKED)
        clear_distances();
    else
        route_queue_boat(grid_offset, callback_calc_distance_water_boat);
}
static void callback_calc_distance_water_flotsam(int next_offset, int dist)
{
    if (map_grid_get(&terrain_water, next_offset) != WATER_N1_BLOCKED)
        enqueue(next_offset, dist);
}
void map_routing_calculate_distances_water_flotsam(int x, int y)
{
    int grid_offset = map_grid_offset(x, y);
    if (map_grid_get(&terrain_water, grid_offset) == WATER_N1_BLOCKED)
        clear_distances();
    else
        route_queue_dir8(grid_offset, callback_calc_distance_water_flotsam);
}
static void callback_calc_distance_build_wall(int next_offset, int dist)
{
    if (map_grid_get(&terrain_land_citizen, next_offset) == CITIZEN_4_CLEAR_TERRAIN)
        enqueue(next_offset, dist);
}
static void callback_calc_distance_build_road(int next_offset, int dist)
{
    int blocked = 0;
    switch (map_grid_get(&terrain_land_citizen, next_offset)) {
        case CITIZEN_N3_AQUEDUCT:
            if (!map_can_place_road_under_aqueduct(next_offset)) {
                map_grid_set(&routing_distance, next_offset, -1);
                blocked = 1;
            }
            break;
        case CITIZEN_2_PASSABLE_TERRAIN: // rubble, garden, access ramp
        case CITIZEN_N1_BLOCKED: // non-empty land
            blocked = 1;
            break;
        default:
            if (map_terrain_is(next_offset, TERRAIN_BUILDING))
                blocked = 1;
            break;
    }
    if (!blocked)
        enqueue(next_offset, dist);
}
static void callback_calc_distance_build_aqueduct(int next_offset, int dist)
{
    int blocked = 0;
    switch (map_grid_get(&terrain_land_citizen, next_offset)) {
        case CITIZEN_N3_AQUEDUCT:
        case CITIZEN_2_PASSABLE_TERRAIN: // rubble, garden, access ramp
        case CITIZEN_N1_BLOCKED: // non-empty land
            blocked = 1;
            break;
        default:
            if (map_terrain_is(next_offset, TERRAIN_BUILDING)) {
                if (map_grid_get(&terrain_land_citizen, next_offset) != CITIZEN_N4_RESERVOIR_CONNECTOR)
                    blocked = 1;
            }
            break;
    }
    if (map_terrain_is(next_offset, TERRAIN_ROAD) && !map_can_place_aqueduct_on_road(next_offset)) {
        map_grid_set(&routing_distance, next_offset, -1);
        blocked = 1;
    }
    if (!blocked)
        enqueue(next_offset, dist);
}
static int map_can_place_initial_road_or_aqueduct(int grid_offset, int is_aqueduct)
{
    if (map_grid_get(&terrain_land_citizen, grid_offset) == CITIZEN_N1_BLOCKED) {
        // not open land, can only if:
        // - aqueduct should be placed, and:
        // - land is a reservoir building OR an aqueduct
        if (!is_aqueduct)
            return 0;
        if (map_terrain_is(grid_offset, TERRAIN_AQUEDUCT))
            return 1;
        if (map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
            if (building_get(map_building_at(grid_offset))->type == BUILDING_RESERVOIR)
                return 1;
        }
        return 0;
    } else if (map_grid_get(&terrain_land_citizen, grid_offset) == CITIZEN_2_PASSABLE_TERRAIN) {
        // rubble, access ramp, garden
        return 0;
    } else if (map_grid_get(&terrain_land_citizen, grid_offset) == CITIZEN_N3_AQUEDUCT) {
        if (is_aqueduct)
            return 0;
        if (map_can_place_road_under_aqueduct(grid_offset))
            return 1;
        return 0;
    } else
        return 1;
}
int map_routing_calculate_distances_for_building(routed_int type, int x, int y)
{
    if (type == ROUTED_BUILDING_WALL) {
        route_queue(map_grid_offset(x, y), -1, callback_calc_distance_build_wall);
        return 1;
    }
    clear_distances();
    int source_offset = map_grid_offset(x, y);
    if (!map_can_place_initial_road_or_aqueduct(source_offset, type != ROUTED_BUILDING_ROAD))
        return 0;
    if (map_terrain_is(source_offset, TERRAIN_ROAD) &&
        type != ROUTED_BUILDING_ROAD && !map_can_place_aqueduct_on_road(source_offset))
        return 0;
    ++stats.total_routes_calculated;
    if (type == ROUTED_BUILDING_ROAD)
        route_queue(source_offset, -1, callback_calc_distance_build_road);
    else
        route_queue(source_offset, -1, callback_calc_distance_build_aqueduct);
    return 1;
}
static int callback_delete_wall_aqueduct(int next_offset, int dist)
{
    if (map_grid_get(&terrain_land_citizen, next_offset) < CITIZEN_0_ROAD) {
        if (map_terrain_is(next_offset, TERRAIN_AQUEDUCT | TERRAIN_WALL)) {
            map_terrain_remove(next_offset, TERRAIN_CLEARABLE);
            return 1;
        }
    } else
        enqueue(next_offset, dist);
    return 0;
}
void map_routing_delete_first_wall_or_aqueduct(int x, int y)
{
    ++stats.total_routes_calculated;
    route_queue_until(map_grid_offset(x, y), callback_delete_wall_aqueduct);
}

static int is_fighting_friendly(figure *f)
{
    return f->is_friendly && f->action_state == FIGURE_ACTION_150_ATTACK;
}
static int has_fighting_friendly(int grid_offset)
{
    return map_figure_foreach_until(grid_offset, is_fighting_friendly);
}
static int is_fighting_enemy(figure *f)
{
    return !f->is_friendly && f->action_state == FIGURE_ACTION_150_ATTACK;
}
static int has_fighting_enemy(int grid_offset)
{
    return map_figure_foreach_until(grid_offset, is_fighting_enemy);
}

static void callback_travel_citizen_land(int next_offset, int dist)
{
    if (map_grid_get(&terrain_land_citizen, next_offset) >= 0 && !has_fighting_friendly(next_offset))
        enqueue(next_offset, dist);
}
int map_routing_citizen_can_travel_over_land(int src_x, int src_y, int dst_x, int dst_y)
{
    int src_offset = map_grid_offset(src_x, src_y);
    int dst_offset = map_grid_offset(dst_x, dst_y);
    ++stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_citizen_land);
    return map_grid_get(&routing_distance, dst_offset) != 0;
}
static void callback_travel_citizen_road_garden(int next_offset, int dist)
{
    if (map_grid_get(&terrain_land_citizen, next_offset) >= CITIZEN_0_ROAD &&
        map_grid_get(&terrain_land_citizen, next_offset) <= CITIZEN_2_PASSABLE_TERRAIN) {
        enqueue(next_offset, dist);
    }
}
int map_routing_citizen_can_travel_over_road_garden(int src_x, int src_y, int dst_x, int dst_y)
{
    int src_offset = map_grid_offset(src_x, src_y);
    int dst_offset = map_grid_offset(dst_x, dst_y);
    ++stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_citizen_road_garden);
    return map_grid_get(&routing_distance, dst_offset) != 0;
}
static void callback_travel_walls(int next_offset, int dist)
{
    if (map_grid_get(&terrain_walls, next_offset) >= WALL_0_PASSABLE &&
        map_grid_get(&terrain_walls, next_offset) <= 2) {
        enqueue(next_offset, dist);
    }
}
int map_routing_can_travel_over_walls(int src_x, int src_y, int dst_x, int dst_y)
{
    int src_offset = map_grid_offset(src_x, src_y);
    int dst_offset = map_grid_offset(dst_x, dst_y);
    ++stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_walls);
    return map_grid_get(&routing_distance, dst_offset) != 0;
}
static void callback_travel_noncitizen_land_through_building(int next_offset, int dist)
{
    if (!has_fighting_enemy(next_offset)) {
        if (map_grid_get(&terrain_land_noncitizen, next_offset) == NONCITIZEN_0_PASSABLE ||
                map_grid_get(&terrain_land_noncitizen, next_offset) == NONCITIZEN_2_CLEARABLE ||
            (map_grid_get(&terrain_land_noncitizen, next_offset) == NONCITIZEN_1_BUILDING &&
                map_building_at(next_offset) == state.through_building_id)) {
            enqueue(next_offset, dist);
        }
    }
}
static void callback_travel_noncitizen_land(int next_offset, int dist)
{
    if (!has_fighting_enemy(next_offset)) {
        if (map_grid_get(&terrain_land_noncitizen, next_offset) >= NONCITIZEN_0_PASSABLE &&
            map_grid_get(&terrain_land_noncitizen, next_offset) < NONCITIZEN_5_FORT) {
            enqueue(next_offset, dist);
        }
    }
}
int map_routing_noncitizen_can_travel_over_land(int src_x, int src_y, int dst_x, int dst_y, int only_through_building_id, int max_tiles)
{
    int src_offset = map_grid_offset(src_x, src_y);
    int dst_offset = map_grid_offset(dst_x, dst_y);
    ++stats.total_routes_calculated;
    ++stats.enemy_routes_calculated;
    if (only_through_building_id) {
        state.through_building_id = only_through_building_id;
        route_queue(src_offset, dst_offset, callback_travel_noncitizen_land_through_building);
    } else {
        route_queue_max(src_offset, dst_offset, max_tiles, callback_travel_noncitizen_land);
    }
    return map_grid_get(&routing_distance, dst_offset) != 0;
}
static void callback_travel_noncitizen_through_everything(int next_offset, int dist)
{
    if (map_grid_get(&terrain_land_noncitizen, next_offset) >= NONCITIZEN_0_PASSABLE)
        enqueue(next_offset, dist);

}
int map_routing_noncitizen_can_travel_through_everything(int src_x, int src_y, int dst_x, int dst_y)
{
    int src_offset = map_grid_offset(src_x, src_y);
    int dst_offset = map_grid_offset(dst_x, dst_y);
    ++stats.total_routes_calculated;
    route_queue(src_offset, dst_offset, callback_travel_noncitizen_through_everything);
    return map_grid_get(&routing_distance, dst_offset) != 0;
}

void map_routing_block(int x, int y, int size)
{
    if (!map_grid_is_inside(x, y, size))
            return;
    for (int dy = 0; dy < size; dy++) {
        for (int dx = 0; dx < size; dx++) {
            map_grid_set(&routing_distance, map_grid_offset(x + dx, y + dy), 0);
        }
    }
}
int map_routing_distance(int grid_offset)
{
    return map_grid_get(&routing_distance, grid_offset);
}

void map_routing_save_state(buffer *buf)
{
    buf->write_i32(0); // unused counter
    buf->write_i32(stats.enemy_routes_calculated);
    buf->write_i32(stats.total_routes_calculated);
    buf->write_i32(0); // unused counter
}
void map_routing_load_state(buffer *buf)
{
    buf->skip(4); // unused counter
    stats.enemy_routes_calculated = buf->read_i32();
    stats.total_routes_calculated = buf->read_i32();
    buf->skip(4); // unused counter
}

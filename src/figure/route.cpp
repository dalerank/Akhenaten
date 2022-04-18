#include "route.h"

#include "map/routing.h"
#include "map/routing_path.h"
#include "core/game_environment.h"

#define MAX_PATH_LENGTH 500
#define MAX_ROUTES 3000

static struct {
    int figure_ids[MAX_ROUTES];
    uint8_t direction_paths[MAX_ROUTES][MAX_PATH_LENGTH];
} data;

void figure_route_clear_all(void) {
    for (int i = 0; i < MAX_ROUTES; i++) {
        data.figure_ids[i] = 0;
        for (int j = 0; j < MAX_PATH_LENGTH; j++) {
            data.direction_paths[i][j] = 0;
        }
    }
}
void figure_route_clean(void) {
    for (int i = 0; i < MAX_ROUTES; i++) {
        int figure_id = data.figure_ids[i];
        if (figure_id > 0 && figure_id < MAX_FIGURES[GAME_ENV]) {
            const figure *f = figure_get(figure_id);
            if (f->state != FIGURE_STATE_ALIVE || f->routing_path_id != i)
                data.figure_ids[i] = 0;
        }
    }
}
static int get_first_available(void) {
    for (int i = 1; i < MAX_ROUTES; i++) {
        if (data.figure_ids[i] == 0)
            return i;
    }
    return 0;
}

void figure::figure_route_add() {
    routing_path_id = 0;
    routing_path_current_tile = 0;
    routing_path_length = 0;
    int path_id = get_first_available();
    if (!path_id)
        return;
    int path_length;
    if (is_boat) {
        if (is_boat == 2) { // flotsam
            map_routing_calculate_distances_water_flotsam(tile_x, tile_y);
            path_length = map_routing_get_path_on_water(data.direction_paths[path_id], destination_x, destination_y, 1);
        } else {
            map_routing_calculate_distances_water_boat(tile_x, tile_y);
            path_length = map_routing_get_path_on_water(data.direction_paths[path_id], destination_x, destination_y, 0);
        }
    } else {
        // land figure
        int can_travel;
        switch (terrain_usage) {
            case TERRAIN_USAGE_ENEMY:
                can_travel = map_routing_noncitizen_can_travel_over_land(tile_x, tile_y, destination_x, destination_y, destinationID(), 5000);
                if (!can_travel) {
                    can_travel = map_routing_noncitizen_can_travel_over_land(tile_x, tile_y, destination_x, destination_y, 0, 25000);
                    if (!can_travel)
                        can_travel = map_routing_noncitizen_can_travel_through_everything(tile_x, tile_y, destination_x, destination_y);
                }
                break;
            case TERRAIN_USAGE_WALLS:
                can_travel = map_routing_can_travel_over_walls(tile_x, tile_y, destination_x, destination_y);
                break;
            case TERRAIN_USAGE_ANIMAL:
                can_travel = map_routing_noncitizen_can_travel_over_land(tile_x, tile_y, destination_x, destination_y, -1, 5000);
                break;
            case TERRAIN_USAGE_PREFER_ROADS:
                can_travel = map_routing_citizen_can_travel_over_road(tile_x, tile_y, destination_x, destination_y);
                if (!can_travel)
                    can_travel = map_routing_citizen_can_travel_over_land(tile_x, tile_y, destination_x, destination_y);
                break;
            case TERRAIN_USAGE_ROADS:
                can_travel = map_routing_citizen_can_travel_over_road(tile_x, tile_y, destination_x, destination_y);
                break;
            default:
                can_travel = map_routing_citizen_can_travel_over_land(tile_x, tile_y, destination_x, destination_y);
                break;
        }
        if (can_travel) {
            if (terrain_usage == TERRAIN_USAGE_WALLS) {
                path_length = map_routing_get_path(data.direction_paths[path_id], tile_x, tile_y, destination_x, destination_y, 4);
                if (path_length <= 0)
                    path_length = map_routing_get_path(data.direction_paths[path_id], tile_x, tile_y, destination_x, destination_y, 8);
            } else if (terrain_usage == TERRAIN_USAGE_ROADS)
                path_length = map_routing_get_path(data.direction_paths[path_id], tile_x, tile_y, destination_x, destination_y, 4);
            else
                path_length = map_routing_get_path(data.direction_paths[path_id], tile_x, tile_y, destination_x, destination_y, 8);
        } else // cannot travel
            path_length = 0;
    }
    if (path_length) {
        data.figure_ids[path_id] = id;
        routing_path_id = path_id;
        routing_path_length = path_length;
    }
}
void figure::route_remove() {
    if (routing_path_id > 0) {
        if (data.figure_ids[routing_path_id] == id)
            data.figure_ids[routing_path_id] = 0;
        routing_path_id = 0;
    }
}
int figure_route_get_direction(int path_id, int index) {
    return data.direction_paths[path_id][index];
}

io_buffer *iob_route_figures = new io_buffer([](io_buffer *iob) {
    for (int i = 0; i < MAX_ROUTES; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &data.figure_ids[i]);
    }
});
io_buffer *iob_route_paths = new io_buffer([](io_buffer *iob) {
    for (int i = 0; i < MAX_ROUTES; i++) {
        iob->bind(BIND_SIGNATURE_RAW, &data.direction_paths[i], MAX_PATH_LENGTH);
    }
});

#include "core/calc.h"
#include "core/random.h"
#include "map/grid.h"
#include "map/random.h"
#include "map/routing.h"

static int direction_path[MAX_PATH_LENGTH];

static void adjust_tile_in_direction(int direction, int *x, int *y, int *grid_offset) {
    switch (direction) {
        case DIR_0_TOP_RIGHT:
            --*y;
            break;
        case DIR_1_RIGHT:
            ++*x;
            --*y;
            break;
        case DIR_2_BOTTOM_RIGHT:
            ++*x;
            break;
        case DIR_3_BOTTOM:
            ++*x;
            ++*y;
            break;
        case DIR_4_BOTTOM_LEFT:
            ++*y;
            break;
        case DIR_5_LEFT:
            --*x;
            ++*y;
            break;
        case DIR_6_TOP_LEFT:
            --*x;
            break;
        case DIR_7_TOP:
            --*x;
            --*y;
            break;
    }
    *grid_offset += map_grid_direction_delta(direction);
}

int map_routing_get_path(uint8_t *path, int src_x, int src_y, int dst_x, int dst_y, int num_directions) {
    int dst_grid_offset = map_grid_offset(dst_x, dst_y);
    int distance = map_routing_distance(dst_grid_offset);
    if (distance <= 0 || distance >= 998)
        return 0;

    int num_tiles = 0;
    int last_direction = -1;
    int x = dst_x;
    int y = dst_y;
    int grid_offset = dst_grid_offset;
    int step = num_directions == 8 ? 1 : 2;

    while (distance > 1) {
        distance = map_routing_distance(grid_offset);
        int direction = -1;
        int general_direction = calc_general_direction(x, y, src_x, src_y);
        for (int d = 0; d < 8; d += step) {
            if (d != last_direction) {
                int next_offset = grid_offset + map_grid_direction_delta(d);
                int next_distance = map_routing_distance(next_offset);
                if (next_distance) {
                    if (next_distance < distance) {
                        distance = next_distance;
                        direction = d;
                    } else if (next_distance == distance && (d == general_direction || direction == -1)) {
                        distance = next_distance;
                        direction = d;
                    }
                }
            }
        }
        if (direction == -1)
            return 0;
        adjust_tile_in_direction(direction, &x, &y, &grid_offset);
        int forward_direction = (direction + 4) % 8;
        direction_path[num_tiles++] = forward_direction;
        last_direction = forward_direction;
        if (num_tiles >= MAX_PATH_LENGTH)
            return 0;
    }
    for (int i = 0; i < num_tiles; i++)
        path[i] = direction_path[num_tiles - i - 1];
    return num_tiles;
}
int map_routing_get_closest_tile_within_range(int src_x, int src_y, int dst_x, int dst_y, int num_directions, int range, int *out_x, int *out_y) {
    int dst_grid_offset = map_grid_offset(dst_x, dst_y);
    int distance = map_routing_distance(dst_grid_offset);
    if (distance <= 0 || distance >= 998)
        return 0;

    int num_tiles = 0;
    int last_direction = -1;
    int x = dst_x;
    int y = dst_y;
    int grid_offset = dst_grid_offset;
    int step = num_directions == 8 ? 1 : 2;

    while (distance > 1) {
        distance = map_routing_distance(grid_offset);
        *out_x = x;
        *out_y = y;
        if (distance <= range)
            return 1;
        int direction = -1;
        int general_direction = calc_general_direction(x, y, src_x, src_y);
        for (int d = 0; d < 8; d += step) {
            if (d != last_direction) {
                int next_offset = grid_offset + map_grid_direction_delta(d);
                int next_distance = map_routing_distance(next_offset);
                if (next_distance) {
                    if (next_distance < distance) {
                        distance = next_distance;
                        direction = d;
                    } else if (next_distance == distance && (d == general_direction || direction == -1)) {
                        distance = next_distance;
                        direction = d;
                    }
                }
            }
        }
        if (direction == -1)
            return 0;
        adjust_tile_in_direction(direction, &x, &y, &grid_offset);
        int forward_direction = (direction + 4) % 8;
        direction_path[num_tiles++] = forward_direction;
        last_direction = forward_direction;
        if (num_tiles >= MAX_PATH_LENGTH)
            return 0;
    }
    return 0;
}
int map_routing_get_path_on_water(uint8_t *path, int dst_x, int dst_y, int is_flotsam) {
    int rand = random_byte() & 3;
    int dst_grid_offset = map_grid_offset(dst_x, dst_y);
    int distance = map_routing_distance(dst_grid_offset);
    if (distance <= 0 || distance >= 998)
        return 0;


    int num_tiles = 0;
    int last_direction = -1;
    int x = dst_x;
    int y = dst_y;
    int grid_offset = dst_grid_offset;
    while (distance > 1) {
        int current_rand = rand;
        distance = map_routing_distance(grid_offset);
        if (is_flotsam)
            current_rand = map_random_get(grid_offset) & 3;

        int direction = -1;
        for (int d = 0; d < 8; d++) {
            if (d != last_direction) {
                int next_offset = grid_offset + map_grid_direction_delta(d);
                int next_distance = map_routing_distance(next_offset);
                if (next_distance) {
                    if (next_distance < distance) {
                        distance = next_distance;
                        direction = d;
                    } else if (next_distance == distance && rand == current_rand) {
                        // allow flotsam to wander
                        distance = next_distance;
                        direction = d;
                    }
                }
            }
        }
        if (direction == -1)
            return 0;

        adjust_tile_in_direction(direction, &x, &y, &grid_offset);
        int forward_direction = (direction + 4) % 8;
        direction_path[num_tiles++] = forward_direction;
        last_direction = forward_direction;
        if (num_tiles >= MAX_PATH_LENGTH)
            return 0;

    }
    for (int i = 0; i < num_tiles; i++) {
        path[i] = direction_path[num_tiles - i - 1];
    }
    return num_tiles;
}

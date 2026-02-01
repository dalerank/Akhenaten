#include "route.h"

#include "city/city_figures.h"
#include "grid/routing/queue.h"
#include "grid/routing/routing.h"

#include "core/calc.h"
#include "core/random.h"
#include "grid/grid.h"
#include "grid/figure.h"
#include "grid/random.h"
#include "grid/terrain.h"

#include <assert.h>

#define MAX_ROUTES 3000

struct figure_route_data_t {
    int figure_ids[MAX_ROUTES];
    uint8_t direction_paths[MAX_ROUTES][MAX_PATH_LENGTH];
};

figure_route_data_t g_figure_route_data;

void figure_route_clear_all(void) {
    auto &data = g_figure_route_data;
    for (int i = 0; i < MAX_ROUTES; i++) {
        data.figure_ids[i] = 0;
        for (int j = 0; j < MAX_PATH_LENGTH; j++) {
            data.direction_paths[i][j] = 0;
        }
    }
}

void figure_route_clean(void) {
    auto &data = g_figure_route_data;
    for (int i = 0; i < MAX_ROUTES; i++) {
        int figure_id = data.figure_ids[i];
        if (figure_id > 0 && figure_id < MAX_FIGURES) {
            const figure* f = figure_get(figure_id);
            if (f->state != FIGURE_STATE_ALIVE || f->routing_path_id != i)
                data.figure_ids[i] = 0;
        }
    }
}
int map_routing_get_first_available_id() {
    auto &data = g_figure_route_data;
    for (int i = 1; i < MAX_ROUTES; i++) {
        if (data.figure_ids[i] == 0)
            return i;
    }
    return 0;
}

void figure::map_figure_add() {
    if (!map_grid_is_valid_offset(tile)) {
        return;
    }

    // check for figures on new tile, update "next_figure" pointers accordingly
    next_figure = 0;
    int on_tile = map_figure_id_get(tile);
    if (on_tile) {
        figure* checking = figure_get(on_tile); // get first figure (head) on the new tile, if any is present
                                                //        assert(checking->id != f->id); // hmmmm that'd be wrong

                                                // traverse through chain
        while (checking->next_figure) {
            if (checking->next_figure == id) { // this figure is already in the chain on this tile!!
                return;
            }

            if (checking->next_figure == checking->id) { // this figure next_id looped!!
                checking->next_figure = 0;
                return;
            }
            checking = figure_get(checking->next_figure); // else, traverse chain of figures as normal...
        }

        // last figure in the chain!
        checking->next_figure = id;
    } else {
        map_figure_set(tile, id);
    }
}

void figure::map_figure_update() { // useless - but used temporarily for checking if figures are correct!
    if (!map_grid_is_valid_offset(tile.grid_offset())) {
        return;
    }

    // traverse through chain of figures on this tile
    int on_tile = map_figure_id_get(tile);
    figure* checking = figure_get(on_tile);
    while (checking->id) {
        assert(checking->tile.grid_offset() == tile.grid_offset());
        checking = figure_get(checking->next_figure);
    }
}

void figure::map_figure_remove() {
    if (!map_has_figure_at(tile)) {
        next_figure = 0;
        return;
    }

    // check for figures on new tile, update "next_figure" pointers accordingly
    int on_tile = map_figure_id_get(tile);
    if (on_tile == id) { // figure is the first (head) on its tile!
        map_figure_set(tile, next_figure); // remove from chain, set the head as the next one in chain (0 is fine)
    } else {
        figure* checking = figure_get(on_tile); // traverse through the chain to find this figure...
        while (checking->id && checking->next_figure != id) {
            checking = figure_get(checking->next_figure);
            if (checking->id == checking->next_figure) {
                checking->next_figure = 0;
            }
        }
        checking->next_figure = next_figure; // remove from chain, set previous figure to point "next" to the next one
                                             // in chain (0 is fine)
    }
    next_figure = 0;
}

void figure::figure_route_add() {
    auto &data = g_figure_route_data;
    routing_path_id = 0;
    routing_path_current_tile = 0;
    routing_path_length = 0;
    int path_id = map_routing_get_first_available_id();
    if (!path_id) {
        return;
    }

    int path_length;
    if (can_move_by_water() && is_boat()) {
        if (allow_move_type == EMOVE_DEEPWATER) { // flotsam
            map_routing_calculate_distances_deepwater(tile);
            path_length = map_routing_get_path_on_water(data.direction_paths[path_id], destination_tile, true);
        } else {
            map_routing_calculate_distances_water_boat(tile);
            path_length = map_routing_get_path_on_water(data.direction_paths[path_id], destination_tile, false);
        }
    } else {
        // land figure
        int can_travel;
        switch (terrain_usage) {
        case TERRAIN_USAGE_ENEMY:
            can_travel = map_routing_enemy_can_travel_over_land(tile, destination_tile, destinationID(), 5000);
            if (!can_travel) {
                can_travel = map_routing_enemy_can_travel_over_land(tile, destination_tile, 0, 25000);
                if (!can_travel) {
                    can_travel = map_routing_enemy_can_travel_through_everything(tile, destination_tile);
                }
            }
            break;

        case TERRAIN_USAGE_WALLS:
            can_travel = map_routing_can_travel_over_walls(tile.x(), tile.y(), destination_tile.x(), destination_tile.y());
            break;

        case TERRAIN_USAGE_ANIMAL:
            can_travel = map_routing_noncitizen_can_travel_over_land(tile, destination_tile, -1, 5000);
            break;

        case TERRAIN_USAGE_AMPHIBIA:
            can_travel = map_routing_amphibia_can_travel_over_land_water(tile, destination_tile, -1, 5000);
            break;

        case TERRAIN_USAGE_PREFER_ROADS:
            can_travel = map_routing_citizen_can_travel_over_road(tile, destination_tile);
            if (!can_travel) {
                can_travel = map_routing_citizen_can_travel_over_land(tile, destination_tile);
            }
            break;

        case TERRAIN_USAGE_ROADS:
            can_travel = map_routing_citizen_can_travel_over_road(tile, destination_tile);
            break;

        default:
            can_travel = map_routing_citizen_can_travel_over_land(tile, destination_tile);
            break;
        }

        if (can_travel) {
            if (terrain_usage == TERRAIN_USAGE_WALLS) {
                path_length = map_routing_get_path(data.direction_paths[path_id], tile, destination_tile, 4);
                if (path_length <= 0) {
                    path_length = map_routing_get_path(data.direction_paths[path_id], tile, destination_tile, 8);
                }
            } else if (terrain_usage == TERRAIN_USAGE_ROADS) {
                path_length = map_routing_get_path(data.direction_paths[path_id], tile, destination_tile, 4);
            } else {
                path_length = map_routing_get_path(data.direction_paths[path_id], tile, destination_tile, 8);
            }
        } else { // cannot travel
            path_length = 0;
        }
    }

    if (path_length) {
        data.figure_ids[path_id] = id;
        routing_path_id = path_id;
        routing_path_length = path_length;
    }
}

void figure::route_remove() {
    auto &data = g_figure_route_data;
    if (routing_path_id > 0) {
        if (data.figure_ids[routing_path_id] == id) {
            data.figure_ids[routing_path_id] = 0;
        }
        routing_path_id = 0;
    }
}

int figure_route_get_direction(int path_id, int index) {
    auto &data = g_figure_route_data;
    return data.direction_paths[path_id][index];
}

int figure_find_best_road_direction(tile2i spawn_tile, tile2i target_tile) {
    // Calculate target direction
    int target_direction = calc_general_direction(spawn_tile, target_tile);

    // Check neib tiles (8 dirs) that find better available for start
    int best_direction = DIR_4_BOTTOM_LEFT;
    int min_direction_diff = 8;

    // (dx, dy) -> direction
    struct {
        int dx, dy;
        int dir;
    } neighbors[] = {
        {0, -1, DIR_7_TOP},           // 0: top
        {1, -1, DIR_0_TOP_RIGHT},     // 1: top-right
        {1, 0, DIR_1_RIGHT},          // 2: right
        {1, 1, DIR_2_BOTTOM_RIGHT},   // 3: down-right
        {0, 1, DIR_3_BOTTOM},         // 4: down
        {-1, 1, DIR_4_BOTTOM_LEFT},   // 5: down-left
        {-1, 0, DIR_5_LEFT},          // 6: left
        {-1, -1, DIR_6_TOP_LEFT}       // 7: top-left
    };

    for (int i = 0; i < 8; i++) {
        tile2i neighbor_tile = spawn_tile.shifted(neighbors[i].dx, neighbors[i].dy);

        if (map_terrain_is(neighbor_tile.grid_offset(), TERRAIN_ROAD | TERRAIN_ACCESS_RAMP)) {
            int dir_diff = std::abs(target_direction - neighbors[i].dir);
            int circular_diff = std::min(dir_diff, 8 - dir_diff);

            if (circular_diff < min_direction_diff) {
                min_direction_diff = circular_diff;
                best_direction = neighbors[i].dir;
            }
        }
    }

    return best_direction;
}

io_buffer* iob_route_figures = new io_buffer([](io_buffer* iob, size_t version) {
    auto &data = g_figure_route_data;
    for (int i = 0; i < MAX_ROUTES; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &data.figure_ids[i]);
    }
});

io_buffer* iob_route_paths = new io_buffer([](io_buffer* iob, size_t version) {
    auto &data = g_figure_route_data;
    for (int i = 0; i < MAX_ROUTES; i++) {
        iob->bind(BIND_SIGNATURE_RAW, &data.direction_paths[i], MAX_PATH_LENGTH);
    }
});

int g_direction_path[MAX_PATH_LENGTH];

void map_routing_adjust_tile_in_direction(int direction, tile2i &tile, int &grid_offset) {
    switch (direction) {
    case DIR_0_TOP_RIGHT: tile.shift(0, -1); break;
    case DIR_1_RIGHT: tile.shift(1, -1); break;
    case DIR_2_BOTTOM_RIGHT: tile.shift(1, 0); break;
    case DIR_3_BOTTOM: tile.shift(1, 1); break;
    case DIR_4_BOTTOM_LEFT: tile.shift(0, 1); break;
    case DIR_5_LEFT: tile.shift(-1, 1); break;
    case DIR_6_TOP_LEFT: tile.shift(-1, 0); break;
    case DIR_7_TOP: tile.shift(-1, -1); break;
    }
    grid_offset += map_grid_direction_delta(direction);
}

int map_routing_get_path(uint8_t* path, tile2i src, tile2i dst, int num_directions) {
    int dst_grid_offset = dst.grid_offset();
    int distance = map_routing_distance(dst_grid_offset);
    if (distance <= 0 || distance >= 998)
        return 0;

    int num_tiles = 0;
    int last_direction = -1;
    int grid_offset = dst_grid_offset;
    int step = num_directions == 8 ? 1 : 2;

    while (distance > 1) {
        distance = map_routing_distance(grid_offset);
        int direction = -1;
        int general_direction = calc_general_direction(dst, src);
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

        if (direction == -1) {
            return 0;
        }

        map_routing_adjust_tile_in_direction(direction, dst, grid_offset);
        int forward_direction = (direction + 4) % 8;
        g_direction_path[num_tiles++] = forward_direction;
        last_direction = forward_direction;
        if (num_tiles >= MAX_PATH_LENGTH) {
            return 0;
        }
    }

    for (int i = 0; i < num_tiles; i++) {
        path[i] = g_direction_path[num_tiles - i - 1];
    }

    return num_tiles;
}
int map_routing_get_closest_tile_within_range(tile2i src, tile2i dst, int num_directions, int range, tile2i &out) {
    int dst_grid_offset = dst.grid_offset();
    int distance = map_routing_distance(dst_grid_offset);
    if (distance <= 0 || distance >= 998)
        return 0;

    int num_tiles = 0;
    int last_direction = -1;
    int grid_offset = dst_grid_offset;
    int step = num_directions == 8 ? 1 : 2;

    while (distance > 1) {
        distance = map_routing_distance(grid_offset);
        out = dst;
        if (distance <= range) {
            return 1;
        }
        int direction = -1;
        int general_direction = calc_general_direction(dst, src);
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

        map_routing_adjust_tile_in_direction(direction, dst, grid_offset);
        int forward_direction = (direction + 4) % 8;
        g_direction_path[num_tiles++] = forward_direction;
        last_direction = forward_direction;
        if (num_tiles >= MAX_PATH_LENGTH)
            return 0;
    }
    return 0;
}

int map_routing_get_path_on_water(uint8_t* path, tile2i dst, bool is_flotsam) {
    int rand = random_byte() & 3;
    int dst_grid_offset = dst.grid_offset();
    int distance = map_routing_distance(dst_grid_offset);
    if (distance <= 0 || distance >= 998)
        return 0;

    int num_tiles = 0;
    int last_direction = -1;
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

        map_routing_adjust_tile_in_direction(direction, dst, grid_offset);
        int forward_direction = (direction + 4) % 8;
        g_direction_path[num_tiles++] = forward_direction;
        last_direction = forward_direction;
        if (num_tiles >= MAX_PATH_LENGTH) {
            return 0;
        }
    }
    for (int i = 0; i < num_tiles; i++) {
        path[i] = g_direction_path[num_tiles - i - 1];
    }
    return num_tiles;
}

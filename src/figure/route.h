#pragma once

#include "core/buffer.h"
#include "grid/point.h"

constexpr uint32_t MAX_PATH_LENGTH = 500;

void figure_route_clear_all();
void figure_route_clean();
int figure_route_get_direction(int path_id, int index);
int figure_find_best_road_direction(tile2i spawn_tile, tile2i target_tile);

void map_routing_adjust_tile_in_direction(int direction, tile2i &tile, int &grid_offset);
int map_routing_get_first_available_id();
int map_routing_get_path(uint8_t* path, tile2i src, tile2i dst, int num_directions);
int map_routing_get_path_on_water(uint8_t* path, tile2i dst, bool is_flotsam);
int map_routing_get_closest_tile_within_range(tile2i src, tile2i dst, int num_directions, int range, tile2i &out);

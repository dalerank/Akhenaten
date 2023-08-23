#pragma once

#include "core/buffer.h"
#include "core/span.hpp"
#include "figure/figure.h"

constexpr uint32_t MAX_PATH_LENGTH = 500;

void figure_route_clear_all(void);
void figure_route_clean(void);
// void figure_route_add();
// void route_remove();
int figure_route_get_direction(int path_id, int index);

void map_routing_adjust_tile_in_direction(int direction, int *x, int *y, int *grid_offset);
int map_routing_get_first_available_id();
int map_routing_get_path(uint8_t* path, int src_x, int src_y, int dst_x, int dst_y, int num_directions);
int map_routing_get_path_on_water(uint8_t* path, int dst_x, int dst_y, bool is_flotsam);
int map_routing_get_closest_tile_within_range(int src_x,
                                              int src_y,
                                              int dst_x,
                                              int dst_y,
                                              int num_directions,
                                              int range,
                                              int* out_x,
                                              int* out_y);

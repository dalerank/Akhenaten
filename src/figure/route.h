#ifndef FIGURE_ROUTE_H
#define FIGURE_ROUTE_H

#include "core/buffer.h"
#include "figure/figure.h"

void figure_route_clear_all(void);
void figure_route_clean(void);
//void figure_route_add();
//void route_remove();
int figure_route_get_direction(int path_id, int index);

void figure_route_save_state(buffer *figures, buffer *paths);
void figure_route_load_state(buffer *figures, buffer *paths);

int map_routing_get_path(uint8_t *path, int src_x, int src_y, int dst_x, int dst_y, int num_directions);
int map_routing_get_path_on_water(uint8_t *path, int dst_x, int dst_y, int is_flotsam);
int map_routing_get_closest_tile_within_range(int src_x, int src_y, int dst_x, int dst_y, int num_directions, int range, int *out_x, int *out_y);

#endif // FIGURE_ROUTE_H

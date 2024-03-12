#pragma once

#include "grid/point.h"

tile2i& city_map_entry_point();
tile2i& city_map_exit_point();

tile2i& city_map_entry_flag();
tile2i& city_map_exit_flag();

void city_map_set_entry_point(tile2i tile);
void city_map_set_exit_point(tile2i tile);

int city_map_set_entry_flag(tile2i tile);
int city_map_set_exit_flag(tile2i tile);

int city_map_road_network_index(int network_id);

void city_map_clear_largest_road_networks(void);

void city_map_add_to_largest_road_networks(int network_id, int size);

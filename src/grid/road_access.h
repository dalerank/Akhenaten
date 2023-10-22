#pragma once

#include "building/roadblock.h"
#include "grid/point.h"

bool map_has_road_access(tile2i tile, int size);
bool map_get_road_access_tile(tile2i tile, int size, tile2i &road);
bool burning_ruin_can_be_accessed(int x, int y, tile2i *point);
bool map_has_road_access_rotation(int rotation, tile2i tile, int size, tile2i *road);
bool map_has_road_access_temple_complex(tile2i tile, int orientation, bool from_corner, tile2i* road);
bool map_closest_road_within_radius(tile2i tile, int size, int radius, tile2i &road_tile);
bool map_closest_reachable_road_within_radius(int x, int y, int size, int radius, tile2i &road_tile);
bool map_reachable_road_within_radius(int x, int y, int size, int radius, tile2i &road_tile);
int map_road_to_largest_network_rotation(int rotation, int x, int y, int size, int* x_road, int* y_road);
int map_road_to_largest_network(int x, int y, int size, int* x_road, int* y_road);
int map_road_to_largest_network_hippodrome(int x, int y, int* x_road, int* y_road);
int map_get_adjacent_road_tiles_for_roaming(int grid_offset, int* road_tiles, int p);
int map_get_diagonal_road_tiles_for_roaming(int grid_offset, int* road_tiles);
int map_has_adjacent_road_tiles(int grid_offset);
int map_has_adjacent_granary_road(int grid_offset);
void map_road_find_minimum_tile_xy(tile2i tile, int sizex, int sizey, int *min_value, int *min_grid_offset);
bool map_road_within_radius(int x, int y, int size, int radius, tile2i &road_tile);
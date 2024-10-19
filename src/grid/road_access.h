#pragma once

#include "grid/point.h"
#include "city/constants.h"
class building;

bool map_has_road_access(tile2i tile, int size);
tile2i map_get_road_access_tile(tile2i tile, int size);
bool road_tile_valid_access(int grid_offset);
tile2i map_has_road_access_rotation(int rotation, tile2i tile, int size);
bool map_has_road_access_temple_complex(tile2i tile, int orientation, bool from_corner, tile2i* road);
tile2i map_closest_road_within_radius(tile2i tile, int size, int radius, bool avoid_center = false);
tile2i map_closest_road_within_radius(building &b, int radius);
bool map_closest_reachable_road_within_radius(tile2i tile, int size, int radius, tile2i &road_tile);
bool map_reachable_road_within_radius(tile2i tile, int size, int radius, tile2i &road_tile);
tile2i map_road_to_largest_network_rotation(int rotation, tile2i tile, int size,  bool closest);
tile2i map_road_to_largest_network(tile2i tile, int size, bool closest);
int map_road_to_largest_network_hippodrome(int x, int y, int* x_road, int* y_road);
int map_get_adjacent_road_tiles_for_roaming(int grid_offset, int* road_tiles, e_permission permission);
int map_get_diagonal_road_tiles_for_roaming(int grid_offset, int* road_tiles);
inline int map_get_diagonal_road_tiles_for_roaming(tile2i tile, int *road_tiles) { return map_get_diagonal_road_tiles_for_roaming(tile.grid_offset(), road_tiles); }
int map_has_adjacent_road_tiles(int grid_offset);
int map_has_adjacent_granary_road(int grid_offset);
bool map_road_find_minimum_tile_xy(tile2i tile, int sizex, int sizey, int *min_value, int *min_grid_offset);
bool map_road_find_minimum_tile_xy_nearest(tile2i tile, int sizex, int sizey, int *min_value, int *min_grid_offset);
bool map_road_find_minimum_tile_xy_classic(tile2i tile, int sizex, int sizey, int *min_value, int *min_grid_offset);
bool map_road_within_radius(tile2i tile, int size, int radius, tile2i &road_tile, bool avoid_center);
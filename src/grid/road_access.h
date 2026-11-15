#pragma once

#include "grid/point.h"
#include "city/constants.h"
#include "building/building_type.h"
class building;

enum class road_access_resolve_mode {
    Preview, // UI: last-tick distances; optional assume_footprint_occupied
    Commit   // caller already ran calculate_distances; resolve does not BFS again
};

struct building_road_access_result {
    tile2i tile = tile2i::invalid;
    bool valid = false;
};

struct building_road_ports {
    tile2i tile = tile2i::invalid;  // v1 access (== spawn == ret)
    tile2i spawn = tile2i::invalid;
    tile2i ret = tile2i::invalid;
    bool valid = false;
};

building_road_access_result resolve_building_road_access(tile2i tile, e_building_type type, int size,
    int orientation, int variant, road_access_resolve_mode mode, bool assume_footprint_occupied = false);

void apply_building_road_access(building &b, building_road_access_result r);
void apply_building_road_access_from_main(building &part);

building_road_ports building_road_ports_stored(const building &b);
building_road_ports building_road_ports_preview(tile2i tile, e_building_type type, int size, int orientation,
    int variant, bool assume_footprint_occupied = false);

bool building_type_hover_road_access(e_building_type type);
bool building_type_ghost_road_access(e_building_type type);
// On-road venues: preview must erase footprint like post-place (EE1b).
bool building_type_ghost_assume_occupied(e_building_type type);

bool map_has_road_access(tile2i tile, int size);
bool map_has_road_access_nearby(tile2i tile, int distance);
tile2i map_get_road_access_tile(tile2i tile, int size);
bool road_tile_valid_access(int grid_offset);
tile2i map_has_road_access_rotation(int rotation, tile2i tile, int size);
bool map_has_road_access_temple_complex(tile2i tile, int orientation, bool from_corner, tile2i* road);
tile2i map_closest_road_within_radius(tile2i tile, int size, int radius, bool avoid_center = false);
tile2i map_closest_road_within_radius(building &b, int radius);
bool map_closest_reachable_road_within_radius(tile2i tile, int size, int radius, tile2i &road_tile);
bool map_reachable_road_within_radius(tile2i tile, int size, int radius, tile2i &road_tile);
tile2i map_road_to_largest_network_rotation(int rotation, tile2i tile, int size, bool closest,
    bool assume_footprint_occupied = false);
tile2i map_road_to_largest_network(tile2i tile, int size, bool closest,
    bool assume_footprint_occupied = false);
int map_road_to_largest_network_hippodrome(int x, int y, int* x_road, int* y_road);
int map_get_adjacent_road_tiles_for_roaming(int grid_offset, int* road_tiles, e_permission permission, bool ignore_roadblocks = false);
int map_get_diagonal_road_tiles_for_roaming(int grid_offset, int* road_tiles);
inline int map_get_diagonal_road_tiles_for_roaming(tile2i tile, int *road_tiles) { return map_get_diagonal_road_tiles_for_roaming(tile.grid_offset(), road_tiles); }
int map_has_adjacent_road_tiles(int grid_offset);
int map_has_adjacent_granary_road(int grid_offset);
bool map_road_find_minimum_tile_xy(tile2i tile, int sizex, int sizey, int *min_value, int *min_grid_offset);
bool map_road_find_minimum_tile_xy_nearest(tile2i tile, int sizex, int sizey, int *min_value, int *min_grid_offset);
bool map_road_find_minimum_tile_xy_classic(tile2i tile, int sizex, int sizey, int *min_value, int *min_grid_offset);
bool map_road_within_radius(tile2i tile, int size, int radius, tile2i &road_tile, bool avoid_center);
#pragma once

#include "routing_fwd.h"

class building;

enum e_routed_mode {
    ROUTED_BUILDING_ROAD = 0,
    ROUTED_BUILDING_WALL = 1,
    ROUTED_BUILDING_CANALS = 2,
    ROUTED_BUILDING_CANALS_WITHOUT_GRAPHIC = 4,
};

void map_routing_calculate_distances(tile2i tile);
void map_routing_calculate_distances_water_boat(tile2i tile);
void map_routing_calculate_distances_deepwater(tile2i tile);

bool map_can_place_initial_road_or_canal(int grid_offset, int is_canal);
bool map_routing_calculate_distances_for_building(e_routed_mode type, tile2i start);
bool map_routing_ferry_has_routes(building *b);

void map_routing_delete_first_wall_or_aqueduct(int x, int y);

int map_routing_distance(int grid_offset);
inline int map_routing_distance(tile2i tile) { return map_routing_distance(tile.grid_offset()); }
int map_citizen_grid(int grid_offset);
int map_noncitizen_grid(int grid_offset);
bool map_noncitizen_is_passable(int grid_offset);
int map_amphibia_grid(int grid_offset);
int map_water_grid(int grid_offset);

bool map_routing_citizen_found_terrain(tile2i src, tile2i *dst, int terrain_type);
resource_tile map_routing_citizen_found_reeds(tile2i src);
resource_tile map_routing_citizen_found_timber(tile2i src);

bool map_routing_citizen_can_travel_over_land(tile2i src, tile2i dst);
bool map_routing_citizen_can_travel_over_road(tile2i src, tile2i dst);
bool map_routing_citizen_can_travel_over_road_garden(int src_x, int src_y, int dst_x, int dst_y);
bool map_routing_can_travel_over_walls(int src_x, int src_y, int dst_x, int dst_y);

bool map_routing_noncitizen_can_travel_over_land(tile2i src, tile2i dst, int only_through_building_id, int max_tiles);
bool map_routing_noncitizen_can_travel_through_everything(tile2i src, tile2i dst);
bool map_routing_amphibia_can_travel_over_land_water(tile2i src, tile2i dst, int only_through_building_id, int max_tiles);
bool map_routing_enemy_can_travel_over_land(tile2i src, tile2i dst, int only_through_building_id, int max_tiles);
bool map_routing_enemy_can_travel_through_everything(tile2i src, tile2i dst);

void map_routing_block(int x, int y, int size);
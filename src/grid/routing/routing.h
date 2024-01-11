#pragma once

#include "core/buffer.h"
#include "grid/point.h"

class building;

enum routed_int {
    ROUTED_BUILDING_ROAD = 0,
    ROUTED_BUILDING_WALL = 1,
    ROUTED_BUILDING_AQUEDUCT = 2,
    ROUTED_BUILDING_AQUEDUCT_WITHOUT_GRAPHIC = 4,
};

void map_routing_calculate_distances(tile2i tile);
void map_routing_calculate_distances_water_boat(tile2i tile);
void map_routing_calculate_distances_water_flotsam(tile2i tile);

bool map_can_place_initial_road_or_aqueduct(int grid_offset, int is_aqueduct);
bool map_routing_calculate_distances_for_building(routed_int type, int x, int y);
bool map_routing_ferry_has_routes(building *b);

void map_routing_delete_first_wall_or_aqueduct(int x, int y);

int map_routing_distance(int grid_offset);
int map_citizen_grid(int grid_offset);

bool map_routing_citizen_found_terrain(tile2i src, tile2i *dst, int terrain_type);
bool map_routing_citizen_found_reeds(tile2i src, tile2i &dst);
bool map_routing_citizen_found_timber(tile2i src, tile2i &dst);

bool map_routing_citizen_can_travel_over_land(tile2i src, tile2i dst);
bool map_routing_citizen_can_travel_over_road(int src_x, int src_y, int dst_x, int dst_y);
bool map_routing_citizen_can_travel_over_road_garden(int src_x, int src_y, int dst_x, int dst_y);
bool map_routing_can_travel_over_walls(int src_x, int src_y, int dst_x, int dst_y);

bool map_routing_noncitizen_can_travel_over_land(tile2i src, tile2i dst, int only_through_building_id, int max_tiles);
bool map_routing_noncitizen_can_travel_through_everything(tile2i src, tile2i dst);

void map_routing_block(int x, int y, int size);
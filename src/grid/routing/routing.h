#pragma once

#include "core/buffer.h"

enum routed_int {
    ROUTED_BUILDING_ROAD = 0,
    ROUTED_BUILDING_WALL = 1,
    ROUTED_BUILDING_AQUEDUCT = 2,
    ROUTED_BUILDING_AQUEDUCT_WITHOUT_GRAPHIC = 4,
};

void map_routing_calculate_distances(int x, int y);
void map_routing_calculate_distances_water_boat(int x, int y);
void map_routing_calculate_distances_water_flotsam(int x, int y);

bool map_can_place_initial_road_or_aqueduct(int grid_offset, int is_aqueduct);
bool map_routing_calculate_distances_for_building(routed_int type, int x, int y);

void map_routing_delete_first_wall_or_aqueduct(int x, int y);

int map_routing_distance(int grid_offset);
int map_citizen_grid(int grid_offset);

bool map_routing_citizen_found_terrain(int src_x, int src_y, int* dst_x, int* dst_y, int terrain_type);
bool map_routing_citizen_found_reeds(int src_x, int src_y, int* dst_x, int* dst_y);
bool map_routing_citizen_found_timber(int src_x, int src_y, int* dst_x, int* dst_y);

bool map_routing_citizen_can_travel_over_land(int src_x, int src_y, int dst_x, int dst_y);
bool map_routing_citizen_can_travel_over_road(int src_x, int src_y, int dst_x, int dst_y);
bool map_routing_citizen_can_travel_over_road_garden(int src_x, int src_y, int dst_x, int dst_y);
bool map_routing_can_travel_over_walls(int src_x, int src_y, int dst_x, int dst_y);

bool map_routing_noncitizen_can_travel_over_land(int src_x, int src_y, int dst_x, int dst_y, int only_through_building_id, int max_tiles);
bool map_routing_noncitizen_can_travel_through_everything(int src_x, int src_y, int dst_x, int dst_y);

void map_routing_block(int x, int y, int size);
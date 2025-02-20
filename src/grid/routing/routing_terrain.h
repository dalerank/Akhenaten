#pragma once

#include "grid/point.h"

enum {
    ROUTING_TYPE_CITIZEN,
    ROUTING_TYPE_NONCITIZEN,
    ROUTING_TYPE_WATER,
    ROUTING_TYPE_WALLS,
};

void map_routing_update_all(void);
void map_routing_update_land();
void map_routing_update_land_citizen(void);
void map_routing_update_water(void);
void map_routing_update_walls(void);
void map_routing_update_ferry_routes();

bool map_routing_passable_by_usage(int terrain_usage, int grid_offset);

int map_routing_citizen_is_passable(int grid_offset);
int map_routing_citizen_is_road(int grid_offset);
inline int map_routing_citizen_is_road(tile2i tile) { return map_routing_citizen_is_road(tile.grid_offset()); }
int map_routing_citizen_is_passable_terrain(int grid_offset);

int map_routing_noncitizen_is_passable(int grid_offset);
int map_routing_is_destroyable(int grid_offset);

int map_routing_is_wall_passable(int grid_offset);
int map_routing_wall_tile_in_radius(int x, int y, int radius, int* x_wall, int* y_wall);

enum { DESTROYABLE_BUILDING, DESTROYABLE_AQUEDUCT_GARDEN, DESTROYABLE_WALL, DESTROYABLE_GATEHOUSE, DESTROYABLE_NONE };
int map_routing_get_destroyable(int grid_offset);

#ifndef MAP_WATER_H
#define MAP_WATER_H

#include "figure/figure.h"
#include "map/point.h"
#include "terrain.h"
#include "tile_cache.h"

extern tile_cache river_tiles_cache;
void foreach_river_tile(void (*callback)(int grid_offset));

void map_water_add_building(int building_id, int x, int y, int size, int image_id);

bool map_shore_determine_orientation(int x, int y, int size, bool adjust_xy, int *orientation_absolute, bool adjacent = false, int shore_terrain = TERRAIN_WATER);

int map_water_get_wharf_for_new_fishing_boat(figure *boat, map_point *tile);
int map_water_find_alternative_fishing_boat_tile(figure *boat, map_point *tile);
int map_water_find_shipwreck_tile(figure *wreck, map_point *tile);
int map_water_can_spawn_fishing_boat(int x, int y, int size, map_point *tile);

#endif // MAP_WATER_H

#pragma once

#include "figure/figure.h"
#include "grid/point.h"
#include "terrain.h"
#include "tile_cache.h"

tile_cache &river_tiles();

template<typename T>
void foreach_river_tile(T callback) {
    for (const auto grid_offset : river_tiles()) {
        callback(grid_offset);
    }
}

template<typename T>
void foreach_river_tile_ex(T callback) {
    for (const auto grid_offset : river_tiles()) {
        callback(tile2i(grid_offset));
    }
}

struct water_access_tiles {
    tile2i point_a = {-1, -1};
    tile2i point_b = {-1, -1};
};

void map_water_update_docking_points(building &b, int orientation, int offset);
water_access_tiles map_water_get_access_points(const building &b, int orientation, int offset);
bool map_water_is_point_inside(tile2i tile);

void map_water_add_building(int building_id, tile2i tile, int size, int image_id, int ext_terrain_flags = 0);

void map_water_cache_river_tiles();

struct shore_orientation {
    bool match;
    int orientation_absolute;
};

struct water_dest {
    bool found;
    int bid = 0;
    tile2i tile = tile2i::invalid;
};

shore_orientation map_shore_determine_orientation(tile2i tile, int size, bool adjust_xy, bool adjacent = false, int shore_terrain = TERRAIN_WATER);

water_dest map_water_find_shipwreck_tile(figure &wreck);

bool map_water_find_alternative_fishing_boat_tile(figure &boat, tile2i &tile);
void map_water_rebuild_shores();
bool map_water_can_spawn_boat(tile2i tile, int size, tile2i &boat_tile);

int map_water_landing_point(tile2i landing, tile2i ship, tile2i &out);
bool map_find_nearest_free_land_tile(tile2i &tile);

bool map_water_tile_next_to(tile2i building_tile, int size, tile2i &out);
int map_water_farthest_on_line(tile2i from, tile2i to, tile2i &out);
void map_water_recompute_depth_region(tile2i tmin, tile2i tmax);

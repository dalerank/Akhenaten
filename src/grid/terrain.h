#pragma once

#include "core/buffer.h"
#include "grid/point.h"

#include <vector>

enum e_terrain : uint32_t {
    TERRAIN_NONE = 0x0,

    TERRAIN_TREE = 0x1,
    TERRAIN_ROCK = 0x2,
    TERRAIN_WATER = 0x4,
    TERRAIN_BUILDING = 0x8,
    TERRAIN_SHRUB = 0x10,
    TERRAIN_GARDEN = 0x20,
    TERRAIN_ROAD = 0x40,
    TERRAIN_GROUNDWATER = 0x80,
    TERRAIN_CANAL = 0x100,
    TERRAIN_ELEVATION = 0x200,
    TERRAIN_ACCESS_RAMP = 0x400,
    TERRAIN_MEADOW = 0x800,
    TERRAIN_RUBBLE = 0x1000,
    TERRAIN_FOUNTAIN_RANGE = 0x2000,
    TERRAIN_WALL = 0x4000,
    TERRAIN_GATEHOUSE = 0x8000,

    // pharaoh
    TERRAIN_FLOODPLAIN = 0x10000,
    TERRAIN_FERRY_ROUTE = 0x20000,
    TERRAIN_MARSHLAND = 0x40000,
    TERRAIN_UNK_01 = 0x80000,
    TERRAIN_ORE = 0x100000,
    TERRAIN_UNK_02 = 0x200000,
    TERRAIN_UNK_03 = 0x400000,
    TERRAIN_UNK_04 = 0x800000,
    TERRAIN_IRRIGATION_RANGE = 0x1000000,
    TERRAIN_DUNE = 0x2000000,
    TERRAIN_DEEPWATER = 0x4000000,
    TERRAIN_SUBMERGED_ROAD = 0x8000000,
    TERRAIN_PLANER_FUTURE = 0x10000000,
    TERRAIN_UNK_08 = 0x20000000,
    TERRAIN_UNK_09 = 0x40000000,
    TERRAIN_SHORE = 0x80000000,

    // combined
    TERRAIN_ALL = 0xffffffff,
    TERRAIN_WALL_OR_GATEHOUSE = TERRAIN_WALL | TERRAIN_GATEHOUSE,
    TERRAIN_NOT_CLEAR = TERRAIN_TREE + TERRAIN_ROCK + TERRAIN_WATER + TERRAIN_BUILDING + TERRAIN_SHRUB + TERRAIN_GARDEN
                        + TERRAIN_ROAD
                        // ... //
                        + TERRAIN_CANAL + TERRAIN_ELEVATION
                        + TERRAIN_ACCESS_RAMP
                        // ... //
                        + TERRAIN_RUBBLE
                        // ... //
                        + TERRAIN_WALL + TERRAIN_GATEHOUSE
                        + TERRAIN_FLOODPLAIN
                        // ... //
                        + TERRAIN_MARSHLAND
                        // ... //
                        + TERRAIN_ORE
                        // ... //
                        + TERRAIN_DUNE + TERRAIN_DEEPWATER + TERRAIN_SUBMERGED_ROAD,

    TERRAIN_CLEARABLE = TERRAIN_NOT_CLEAR - TERRAIN_ROCK - TERRAIN_WATER - TERRAIN_ELEVATION - TERRAIN_FLOODPLAIN
                        - TERRAIN_MARSHLAND - TERRAIN_ORE - TERRAIN_DUNE - TERRAIN_DEEPWATER - TERRAIN_SUBMERGED_ROAD,
    //    TERRAIN_NOT_REMOVABLE = TERRAIN_ROCK | TERRAIN_FLOODPLAIN | TERRAIN_DUNE,

    TERRAIN_IMPASSABLE = TERRAIN_NOT_CLEAR - TERRAIN_ROAD - TERRAIN_GATEHOUSE - TERRAIN_DEEPWATER - TERRAIN_SUBMERGED_ROAD,

    TERRAIN_IMPASSABLE_ENEMY = TERRAIN_IMPASSABLE + TERRAIN_GATEHOUSE - TERRAIN_BUILDING - TERRAIN_FLOODPLAIN,

    TERRAIN_IMPASSABLE_WOLF = TERRAIN_IMPASSABLE + TERRAIN_GARDEN + TERRAIN_GATEHOUSE - TERRAIN_FLOODPLAIN,
    TERRAIN_IMPASSABLE_HIPPO = TERRAIN_IMPASSABLE + TERRAIN_GARDEN + TERRAIN_GATEHOUSE - TERRAIN_FLOODPLAIN - TERRAIN_MARSHLAND - TERRAIN_WATER - TERRAIN_DEEPWATER,

    TERRAIN_IMPASSABLE_OSTRICH = TERRAIN_IMPASSABLE + TERRAIN_GARDEN + TERRAIN_GATEHOUSE - TERRAIN_FLOODPLAIN,
    TERRAIN_IMPASSABLE_ANTELOPE = TERRAIN_IMPASSABLE + TERRAIN_GARDEN + TERRAIN_GATEHOUSE - TERRAIN_FLOODPLAIN - TERRAIN_MARSHLAND,
};

bool map_terrain_is(int grid_offset, int terrain_mask);
inline bool map_terrain_is(tile2i tile, int terrain_mask) { return map_terrain_is(tile.grid_offset(), terrain_mask); }

int map_terrain_get(int grid_offset);
inline int map_terrain_get(tile2i tile) { return map_terrain_get(tile.grid_offset()); }

void map_terrain_set(int grid_offset, int terrain);

void map_terrain_add(int grid_offset, int terrain);
inline void map_terrain_add(tile2i tile, int terrain) { map_terrain_add(tile.grid_offset(), terrain); }

void map_terrain_remove(int grid_offset, int terrain);
inline void map_terrain_remove(tile2i tile, int terrain) { map_terrain_remove(tile.grid_offset(), terrain); }

void map_terrain_add_in_area(tile2i pmin, tile2i pmax, int terrain);

void map_terrain_add_with_radius(tile2i tile, int size, int radius, int terrain);

void map_terrain_remove_with_radius(tile2i center, int size, int radius, int terrain);

void map_terrain_remove_all(int terrain);

int map_terrain_count_directly_adjacent_with_type(int grid_offset, int terrain);
inline int map_terrain_count_directly_adjacent_with_type(tile2i tile, int terrain) { return map_terrain_count_directly_adjacent_with_type(tile.grid_offset(), terrain); }

int map_terrain_count_diagonally_adjacent_with_type(int grid_offset, int terrain);
inline int map_terrain_count_diagonally_adjacent_with_type(tile2i tile, int terrain) { return map_terrain_count_diagonally_adjacent_with_type(tile.grid_offset(), terrain); }

bool map_terrain_has_adjecent_with_type(int grid_offset, int terrain);
inline bool map_terrain_has_adjecent_with_type(tile2i tile, int terrain) { return map_terrain_has_adjecent_with_type(tile.grid_offset(), terrain); }
bool map_terrain_has_adjacent_x_with_type(int grid_offset, int terrain);
bool map_terrain_has_adjacent_y_with_type(int grid_offset, int terrain);

bool map_terrain_exists_tile_in_area_with_type(tile2i tile, int size, int terrain);

bool map_terrain_exists_tile_in_radius_with_type(tile2i tile, int size, int radius, int terrain);
bool map_terrain_exists_tile_in_radius_with_exact(int x, int y, int size, int radius, int terrain);

bool map_terrain_exists_clear_tile_in_radius(tile2i tile, int size, int radius, int except_grid_offset, tile2i &result);

bool map_terrain_all_tiles_in_area_are(tile2i tile, int size, int terrain);

bool map_terrain_all_tiles_in_radius_are(tile2i c, int size, int radius, int terrain);

bool map_terrain_has_only_rocks_trees_in_ring(int x, int y, int distance);

bool map_terrain_has_only_meadow_in_ring(int x, int y, int distance);

bool map_terrain_is_adjacent_to_wall(int x, int y, int size);

bool map_terrain_is_adjacent_to_water(tile2i tile, int size);

bool map_terrain_is_adjacent_to_open_water(tile2i tile, int size);
bool map_terrain_adjacent_open_water_tiles(tile2i tile, int size, std::vector<tile2i> &water_tiles);

bool map_terrain_get_adjacent_road_or_clear_land(int x, int y, int size, int* x_tile, int* y_tile);

void map_terrain_add_roadblock_road(int x, int y, int orientation);
void map_terrain_add_triumphal_arch_roads(int x, int y, int orientation);

void map_terrain_backup();
void map_terrain_restore();
void map_terrain_clear();
void map_terrain_init_outside_map();

bool map_terrain_is_near_ferry_route(int base_offset, int radius);

void build_terrain_caches();

int map_get_UNK03(int grid_offset);

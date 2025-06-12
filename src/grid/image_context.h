#pragma once

#include <cstdint>
#include <array>
#include "grid/point.h"

constexpr uint8_t MAP_IMAGE_MAX_TILES = 8;

enum e_terrain_image_context {
    CONTEXT_WATER,
    CONTEXT_WALL,
    CONTEXT_WALL_GATEHOUSE,
    CONTEXT_ELEVATION,
    CONTEXT_EARTHQUAKE,
    CONTEXT_DIRT_ROAD,
    CONTEXT_PAVED_ROAD,
    CONTEXT_CANAL,
    CONTEXT_DEEPWATER,
    CONTEXT_FLOODSYSTEM,
    CONTEXT_GRASSCORNERS,

    CONTEXT_MAX_ITEMS
};

using image_tiles_vec = std::array<int, MAP_IMAGE_MAX_TILES>;

struct terrain_image {
    int is_valid;
    int group_offset;
    int item_offset;
    int canal_offset;
};

void map_image_context_init(void);
void map_image_context_reset_water(void);
void map_image_context_reset_elevation(void);

terrain_image map_image_context_get_terrain_image(e_terrain_image_context group, const image_tiles_vec& tiles);
terrain_image map_image_context_get_elevation(int grid_offset, int elevation);
terrain_image map_image_context_get_earthquake(int grid_offset);
terrain_image map_image_context_get_shore(tile2i tile);
terrain_image map_image_context_get_river(tile2i tile);
terrain_image map_image_context_get_floodplain_shore(tile2i tile);
terrain_image map_image_context_get_floodplain_waterline(tile2i tile);
terrain_image map_image_context_get_reeds_transition(tile2i tile);
terrain_image map_image_context_get_grass_corners(tile2i tile);
terrain_image map_image_context_get_wall_gatehouse(tile2i tile);
terrain_image map_image_context_get_dirt_road(tile2i tile);
terrain_image map_image_context_get_paved_road(tile2i tile);

struct match_option {
    int match;
    int nomatch;
};
void map_image_context_fill_matches(tile2i tile, int terrain, match_option match, image_tiles_vec &tiles);


#pragma once

struct terrain_image {
    int is_valid;
    int group_offset;
    int item_offset;
    int aqueduct_offset;
};

void map_image_context_init(void);
void map_image_context_reset_water(void);
void map_image_context_reset_elevation(void);

const terrain_image* map_image_context_get_elevation(int grid_offset, int elevation);
const terrain_image* map_image_context_get_earthquake(int grid_offset);
const terrain_image* map_image_context_get_shore(int grid_offset);
const terrain_image* map_image_context_get_river(int grid_offset);
const terrain_image* map_image_context_get_floodplain_shore(int grid_offset);
const terrain_image* map_image_context_get_floodplain_waterline(int grid_offset);
const terrain_image* map_image_context_get_reeds_transition(int grid_offseet);
const terrain_image* map_image_context_get_grass_corners(int grid_offset);
const terrain_image* map_image_context_get_wall(int grid_offset);
const terrain_image* map_image_context_get_wall_gatehouse(int grid_offset);
const terrain_image* map_image_context_get_dirt_road(int grid_offset);
const terrain_image* map_image_context_get_paved_road(int grid_offset);
const terrain_image* map_image_context_get_canal(int grid_offset);

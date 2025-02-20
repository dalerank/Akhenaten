#pragma once

#define IMAGE_CANAL_FULL_OFFSET 48
#define IMAGE_CANAL_FLOODPLAIN_OFFSET 21

#include "grid/image_context.h"

int map_canal_at(int grid_offset);

void map_canal_set(int grid_offset, int value);

void map_canal_remove(int grid_offset);
void map_canal_clear(void);

void map_canal_backup(void);
void map_canal_restore(void);

void map_update_canals(void);
void map_canal_fill_from_offset(int grid_offset);
void map_canal_update_all_tiles(int include_construction);
void map_tiles_set_canal_image(int grid_offset);

int get_canal_image(int grid_offset, bool is_road, int terrain, const terrain_image *img);
const terrain_image *map_image_context_get_canal(int grid_offset);
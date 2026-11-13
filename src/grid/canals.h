#pragma once

#define IMAGE_CANAL_FLOODPLAIN_OFFSET 21

#include "grid/image_context.h"
#include "grid/point.h"

int map_canal_at(int grid_offset);
inline int map_canal_at(tile2i tile) { return map_canal_at(tile.grid_offset()); }

void map_canal_set(int grid_offset, int value);
inline void map_canal_set(tile2i tile, int value) { map_canal_set(tile.grid_offset(), value); }

void map_canal_remove(int grid_offset);
void map_canal_clear(void);

void map_canal_backup(void);
void map_canal_restore(void);

// OG map_water_supply_set_all_canals_to_no_water, plus the IRRIGATION_RANGE clear that precedes it.
void map_canals_reset_water_supply();
void map_canal_fill_from_offset(tile2i tile);
// Basin-aware IRRIGATION_RANGE stamp (plain radius when flood basins off).
void map_add_irrigation_range(tile2i tile, int size, int radius);
// Clear IRRIGATION_RANGE and re-stamp from wet canals (no water decay). Flag toggle.
void map_irrigation_restamp_from_wet_canals(void);
void map_canal_update_all_tiles(int include_construction);
void map_tiles_set_canal_image(int grid_offset);

int get_canal_image(int grid_offset, bool is_road, int terrain, const terrain_image img);
terrain_image map_image_context_get_canal(int grid_offset);
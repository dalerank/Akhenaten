#pragma once

#include "tile_cache.h"
#include <stdint.h>

#define MAX_FLOODPLAIN_ROWS 30

enum e_fert_type { 
    FERT_NO_MALUS = 0,
    FERT_WITH_MALUS = 1,
    FERT_ONLY_MALUS = 2
};

extern tile_cache floodplain_tiles_cache;

void foreach_floodplain_row(int is_flooding, int row, void (*callback)(int flooding, int grid_offset, int order));
int map_floodplain_rebuild_rows();
void map_floodplain_rebuild_shores();
int map_get_floodplain_edge(tile2i tile);
int8_t map_get_floodplain_row(int grid_offset);

uint8_t map_get_floodplain_growth(int grid_offset);
void map_set_floodplain_growth(int grid_offset, int growth);
void map_clear_floodplain_growth();
void map_tiles_update_floodplain_images();
int map_get_fertility(int grid_offset, int tally_type);
uint8_t map_get_fertility_for_farm(int grid_offset);
inline uint8_t map_get_fertility_for_farm(tile2i tile) { return map_get_fertility_for_farm(tile.grid_offset()); }
void map_soil_set_depletion(int grid_offset, int malus);
void map_update_tile_fertility(int grid_offset, int delta);
void map_update_area_fertility(int x, int y, int size, int delta);
void set_floodplain_land_tiles_image(int grid_offset, bool force);
void map_floodplain_adv_growth_tile(int _, int grid_offset, int order);
void map_floodplain_sub_growth_tile(int grid_offset, int order);
void map_image_set_road_floodplain(int grid_offset);
void set_floodplain_edges_image(int grid_offset);
void map_floodplain_advance_growth();
void map_floodplain_sub_growth();
void map_floodplain_update_inundation(int leading_row, int is_flooding, int flooding_ticks);

int map_get_UNK04(int grid_offset);

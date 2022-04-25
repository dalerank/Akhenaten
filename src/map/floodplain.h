#ifndef OZYMANDIAS_FLOODPLAIN_H
#define OZYMANDIAS_FLOODPLAIN_H

#include <stdint.h>

#define MAX_FLOODPLAIN_ORDER_RANGE 30

enum {
    FERT_NO_MALUS = 0,
    FERT_WITH_MALUS = 1,
    FERT_ONLY_MALUS = 2
};

void tile_cache_floodplain_clear();
void tile_cache_floodplain_add(int grid_offset);
int tile_cache_floodplain_total();

void foreach_floodplain_order(int order, void (*callback)(int grid_offset, int order));
int map_floodplain_rebuild_shoreorder();
int8_t map_get_floodplain_shoreorder(int grid_offset);

uint8_t map_get_floodplain_growth(int grid_offset);
int map_get_fertility(int grid_offset, int tally_type);
uint8_t map_get_fertility_for_farm(int grid_offset);
void map_set_floodplain_growth(int grid_offset, int growth);
void map_soil_set_depletion(int grid_offset, int malus);

int map_get_UNK04(int grid_offset);

#endif //OZYMANDIAS_FLOODPLAIN_H

#pragma once

#include "building/building_type.h"

enum e_house_level {
    HOUSE_SMALL_HUT = 0,
    HOUSE_LARGE_HUT = 1,
    HOUSE_SMALL_SHACK = 2,
    HOUSE_LARGE_SHACK = 3,
    HOUSE_SMALL_HOVEL = 4,
    HOUSE_LARGE_HOVEL = 5,
    HOUSE_SMALL_CASA = 6,
    HOUSE_LARGE_CASA = 7,
    HOUSE_SMALL_INSULA = 8,
    HOUSE_MEDIUM_INSULA = 9,
    HOUSE_LARGE_INSULA = 10,
    HOUSE_GRAND_INSULA = 11,
    HOUSE_SMALL_VILLA = 12,
    HOUSE_MEDIUM_VILLA = 13,
    HOUSE_LARGE_VILLA = 14,
    HOUSE_GRAND_VILLA = 15,
    HOUSE_SMALL_PALACE = 16,
    HOUSE_MEDIUM_PALACE = 17,
    HOUSE_LARGE_PALACE = 18,
    HOUSE_LUXURY_PALACE = 19,
};

class building;

void building_house_change_to(building* house, e_building_type type);
void building_house_change_to_vacant_lot(building* house);

void building_house_merge(building* house);

int building_house_can_expand(building* house, int num_tiles);

void building_house_expand_to_large_insula(building* house);
void building_house_expand_to_large_villa(building* house);
void building_house_expand_to_large_palace(building* house);

void building_house_devolve_from_large_insula(building* house);
void building_house_devolve_from_large_villa(building* house);
void building_house_devolve_from_large_palace(building* house);

void building_house_check_for_corruption(building* house);

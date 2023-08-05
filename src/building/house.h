#pragma once

#include "building/type.h"

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

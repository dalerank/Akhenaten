#pragma once

#include "building/building_type.h"
#include "grid/point.h"

void building_construction_warning_reset(void);
void building_construction_warning_check_food_stocks(int type);
void building_construction_warning_check_reservoir(int type);
void building_construction_warning_generic_checks(int type, tile2i tile, int size, int orientation);
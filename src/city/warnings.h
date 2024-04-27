#pragma once

#include "building/building.h"
#include "city/warning.h"

void building_construction_warning_show(int);
void building_construction_warning_reset();
void building_construction_warning_check_food_stocks(int type);
void building_construction_warning_check_reservoir(int type);
void building_construction_warning_generic_checks(building *b, tile2i tile, int size, int orientation);
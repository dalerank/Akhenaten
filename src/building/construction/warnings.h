#ifndef BUILDING_PLACEMENT_WARNING_H
#define BUILDING_PLACEMENT_WARNING_H

#include "building/type.h"

void building_construction_warning_reset(void);
void building_construction_warning_check_food_stocks(int type);
void building_construction_warning_check_reservoir(int type);
void building_construction_warning_generic_checks(int type, int x, int y, int size);

#endif // BUILDING_PLACEMENT_WARNING_H

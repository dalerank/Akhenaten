#pragma once

#include "building/building_type.h"
#include "game/resource.h"

void building_count_update();
int building_count_active(e_building_type type);
int building_count_total(e_building_type type);
int building_count_industry_active(e_resource resource);
int building_count_industry_total(e_resource resource);
void building_increase_type_count(int type, bool active);
void building_increase_industry_count(int resource, bool active);
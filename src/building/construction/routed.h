#pragma once

#include "grid/routing/routing.h"

int place_routed_building(tile2i start, tile2i end, e_routed_mode type, int *items);
int building_construction_place_wall(bool measure_only, tile2i start, tile2i end);
int building_construction_place_canal(bool measure_only, tile2i start, tile2i end);
int building_construction_place_canal_for_reservoir(bool measure_only, tile2i start, tile2i end, int* items);

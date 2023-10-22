#pragma once

#include "grid/point.h"
#include "scenario_data.h"


const map_data_t* scenario_map_data();

int scenario_map_size();

void scenario_map_init_entry_exit();

tile2i scenario_map_entry();

tile2i scenario_map_exit();

int scenario_map_has_river_entry();

tile2i scenario_map_river_entry();

int scenario_map_has_river_exit();

tile2i scenario_map_river_exit();

void scenario_map_foreach_herd_point(void (*callback)(int x, int y));

void scenario_map_foreach_fishing_point(void (*callback)(int x, int y));

int scenario_map_closest_fishing_point(tile2i tile, tile2i &fish);

int scenario_map_has_flotsam();

#pragma once

#include "grid/point.h"
#include "scenario.h"

const map_data_t* scenario_map_data();

int scenario_map_size();

void scenario_map_init_entry_exit();

tile2i scenario_map_entry();

tile2i scenario_map_exit();

bool scenario_map_has_river_entry();
bool scenario_map_has_river_exit();

tile2i scenario_map_river_entry();
tile2i scenario_map_river_exit();

void scenario_map_foreach_herd_point(std::function<void(tile2i)> callback);
void scenario_map_foreach_fishing_point(void (*callback)(tile2i));

bool scenario_map_has_flotsam();
bool scenario_map_has_animals();
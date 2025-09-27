#ifndef SCENARIO_EDITOR_MAP_H
#define SCENARIO_EDITOR_MAP_H

#include "grid/point.h"

void scenario_editor_set_entry_point(int x, int y);

void scenario_editor_set_exit_point(int x, int y);

void scenario_editor_set_river_entry_point(int x, int y);

void scenario_editor_set_river_exit_point(int x, int y);

void scenario_editor_clear_predator_herd_points(void);

tile2i scenario_editor_predator_herd_point(int id);

void scenario_editor_set_predator_herd_point(int id, int x, int y);

void scenario_editor_clear_fishing_points(void);

tile2i scenario_editor_fishing_point(int id);

void scenario_editor_set_fishing_point(int id, int x, int y);

int scenario_editor_count_invasion_points(void);

void scenario_editor_clear_invasion_points(void);

tile2i scenario_editor_land_invasion_point(int id);

void scenario_editor_set_land_invasion_point(int id, int x, int y);

tile2i scenario_editor_earthquake_point(void);

void scenario_editor_set_earthquake_point(int x, int y);

void scenario_editor_updated_terrain(void);

#endif // SCENARIO_EDITOR_MAP_H

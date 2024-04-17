#pragma once

#include "building/building.h"

int game_can_undo();
void game_undo_disable();
void game_undo_add_building(building* b);
void game_undo_adjust_building(building* b);
int game_undo_contains_building(int building_id);
void game_undo_restore_building_state();
void game_undo_restore_map(int include_properties);
int game_undo_start_build(int type);
void game_undo_finish_build(int cost);
void game_undo_perform();
void game_undo_reduce_time_available();

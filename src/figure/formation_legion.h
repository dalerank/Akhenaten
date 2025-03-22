#pragma once

#include "building/building.h"
#include "figure/formation.h"

int formation_legion_create_for_fort(building* fort);

void formation_legion_delete_for_fort(building* fort);

int formation_legion_recruits_needed();

void formation_legion_update_recruit_status(building* fort);

void formation_legion_change_layout(formation* m, formation_layout new_layout);

void formation_legion_restore_layout(formation* m);

void formation_legion_move_to(formation* m, tile2i tile);

void formation_legion_return_home(formation* m);

void formation_legions_dispatch_to_distant_battle();

void formation_legions_kill_in_distant_battle(int kill_percentage);

void formation_legions_return_from_distant_battle();

int formation_legion_curse();

int formation_legion_at(tile2i tile);

int formation_legion_at_building(int grid_offset);

void formation_legion_update();

void formation_legion_decrease_damage();
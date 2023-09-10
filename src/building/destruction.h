#pragma once

#include "building/building.h"

void building_destroy_by_collapse(building* b);

void building_destroy_by_poof(building* b, bool clouds);

void building_destroy_by_fire(building* b);

void building_destroy_by_plague(building* b);

void building_destroy_by_rioter(building* b);

int building_destroy_first_of_type(e_building_type type);

void building_destroy_last_placed(void);

void building_destroy_increase_enemy_damage(int grid_offset, int max_damage);

void building_destroy_by_enemy(map_point point);

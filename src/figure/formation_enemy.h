#pragma once

#include "figure/formation.h"

int formation_rioter_get_target_building(int* x_tile, int* y_tile);
bool formation_enemy_move_formation_to(const formation* m, tile2i tile, tile2i &outtile);
void formation_enemy_update(void);

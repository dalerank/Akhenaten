#pragma once

#include "figure/formation.h"

bool formation_enemy_move_formation_to(const formation* m, tile2i tile, tile2i &outtile);
void formation_enemy_update(void);

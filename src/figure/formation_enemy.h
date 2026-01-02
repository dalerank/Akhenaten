#pragma once

#include "figure/formation.h"

struct formation_destination {
    bool valid;
    tile2i tile;
};

formation_destination formation_enemy_move_formation_to(const formation* m, tile2i tile);

void formation_seth_kill_enemies();

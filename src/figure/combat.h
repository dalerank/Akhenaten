#pragma once
//
#include "figure/figure.h"
#include "grid/point.h"

int figure_combat_get_target_for_soldier(tile2i tile, int max_distance);
int figure_combat_get_target_for_enemy(tile2i tile);

int figure_combat_get_missile_target_for_soldier(figure* shooter, int max_distance, tile2i* tile);

struct target_figure {
    figure_id fid = 0;
    tile2i tile = tile2i::invalid;
};
target_figure figure_combat_get_missile_target_for_enemy(figure* enemy, int max_distance, int attack_citizens);



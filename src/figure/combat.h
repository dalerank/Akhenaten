#pragma once
//
#include "figure/figure.h"
#include "grid/point.h"
//
////void figure_combat_handle_corpse();
////void figure_combat_handle_attack();
////
int figure_combat_get_target_for_soldier(tile2i tile, int max_distance);
int figure_combat_get_target_for_enemy(tile2i tile);
////
int figure_combat_get_missile_target_for_soldier(figure* shooter, int max_distance, tile2i* tile);
int figure_combat_get_missile_target_for_enemy(figure* enemy, int max_distance, int attack_citizens, tile2i* tile);
////
////void figure_combat_attack_figure_at(int grid_offset_figure);
//


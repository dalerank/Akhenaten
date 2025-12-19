#include "destruction.h"

#include "building/building.h"
#include "grid/building.h"

void building_destroy_increase_enemy_damage(int grid_offset, int delta_damage) {
    building *b = building_get(grid_offset);
    if (b->id) {
        b->force_damage(e_damage_enemy, delta_damage);
    }
}
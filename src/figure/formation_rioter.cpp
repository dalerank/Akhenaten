#include "figure/formation.h"

#include "building/building.h"

static const int RIOTER_ATTACK_PRIORITY[100] = {
    79,  78,  77,  29, 28,  27,  26,  25,  85,  84,  32, 33, 98, 65, 66,  67,  68,  69,  87,  86, 30,
    31,  47,  52,  46, 48,  53,  51,  24,  23,  22,  21, 20, 46, 48, 114, 113, 112, 111, 110, 71, 72,
    70,  74,  75,  76, 60,  61,  62,  63,  64,  34,  36, 37, 35, 94, 19,  18,  17,  16,  15,  49, 106,
    107, 109, 108, 90, 100, 101, 102, 103, 104, 105, 55, 81, 91, 92, 14,  13,  12,  11,  10,  0
};

int formation_rioter_get_target_building(int* x_tile, int* y_tile) {
    int best_type_index = 100;
    building* best_building = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID)
            continue;

        for (int t = 0; t < 100 && t <= best_type_index && RIOTER_ATTACK_PRIORITY[t]; t++) {
            if (b->type == RIOTER_ATTACK_PRIORITY[t]) {
                if (t < best_type_index) {
                    best_type_index = t;
                    best_building = b;
                }
                break;
            }
        }
    }
    if (!best_building)
        return 0;

    if (best_building->type == BUILDING_STORAGE_YARD) {
        *x_tile = best_building->tile.x() + 1;
        *y_tile = best_building->tile.y();
        return best_building->id + 1;
    } else {
        *x_tile = best_building->tile.x();
        *y_tile = best_building->tile.y();
        return best_building->id;
    }
}
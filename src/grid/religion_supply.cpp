#include "religion_supply.h"

#include "building/building.h"
#include "core/svector.h"
#include "grid/building.h"
#include "grid/grid.h"

static void mark_shrine_access(building* shrine, int radius) {
    int x_min, y_min, x_max, y_max;
    map_grid_get_area(shrine->tile.x(), shrine->tile.y(), 1, radius, &x_min, &y_min, &x_max, &y_max);

    for (int yy = y_min; yy <= y_max; yy++) {
        for (int xx = x_min; xx <= x_max; xx++) {
            int building_id = map_building_at(MAP_OFFSET(xx, yy));

            building* b = building_get(building_id);
            if (b->house_size) {
                b->data.house.shrine_access = true;
            }
        }
    }
}


void map_religion_supply_update_houses() {
    svector<building*, 512> shrines;
    for (auto& b : city_buildings()) {
        if (b.state != BUILDING_STATE_VALID)
            continue;

        if (b.is_shrine()) {
            shrines.push_back(&b);
        } else if (b.house_size) {
            b.data.house.shrine_access = false;
        }
    }

    for (auto& s : shrines) {
        mark_shrine_access(s, 3);
    }
}
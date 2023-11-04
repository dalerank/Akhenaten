#include "religion_supply.h"

#include "building/building.h"
#include "core/svector.h"
#include "core/profiler.h"
#include "grid/building.h"
#include "grid/grid.h"

static void mark_shrine_access(building* shrine, int radius) {
    tile2i tmin, tmax;
    map_grid_get_area(shrine->tile, 1, radius, tmin, tmax);

    for (int yy = tmin.y(), endy = tmax.y(); yy <= endy; yy++) {
        for (int xx = tmin.x(), endx = tmax.x(); xx <= endx; xx++) {
            int building_id = map_building_at(MAP_OFFSET(xx, yy));

            building* b = building_get(building_id);
            if (b->house_size) {
                b->data.house.shrine_access = true;
            }
        }
    }
}


void map_religion_supply_update_houses() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Religion Supply Update");
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
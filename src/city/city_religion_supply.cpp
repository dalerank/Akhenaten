#include "city_religion_supply.h"

#include "building/building.h"
#include "building/count.h"
#include "core/svector.h"
#include "core/profiler.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "city/city.h"

static void mark_shrine_access(building* shrine, int radius) {
    grid_area area = map_grid_get_area(shrine->tile, 1, radius);

    for (int yy = area.tmin.y(), endy = area.tmax.y(); yy <= endy; yy++) {
        for (int xx = area.tmin.x(), endx = area.tmax.x(); xx <= endx; xx++) {
            int building_id = map_building_at(MAP_OFFSET(xx, yy));

            building* b = building_get(building_id);
            if (b->house_size) {
                b->data.house.shrine_access = true;
            }
        }
    }
}

void city_buildings_t::update_religion_supply_houses() {
    OZZY_PROFILER_SECTION("Game/Update/Religion Supply Update");
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
#include "city_desirability.h"

#include "core/profiler.h"
#include "building/building.h"
#include "grid/elevation.h"
#include "city/city_buildings.h"
#include "grid/desirability.h"

void building_update_desirability(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Building Update Desirability");
    buildings_valid_do([] (building &b) {
        b.desirability = g_desirability.get_max(b.tile, b.size);
        if (b.is_adjacent_to_water) {
            b.desirability += 10;
        }

        const int elevation = map_elevation_at(b.tile.grid_offset());
        switch (elevation) {
        case 0:
            break;
        case 1:
            b.desirability += 10;
            break;
        case 2:
            b.desirability += 12;
            break;
        case 3:
            b.desirability += 14;
            break;
        case 4:
            b.desirability += 16;
            break;
        default:
            b.desirability += 18;
            break;
        }
    });
}
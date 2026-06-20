#include "building/building_well.h"

#include "grid/water_supply.h"
#include "js/js_game.h"
#include "core/profiler.h"

int __building_well_necessity_status(int bid, int radius) {
    building_well *well = building_get(bid)->dcast_well();
    if (!well) {
        return WELL_UNNECESSARY_NO_HOUSES;
    }
    return map_water_supply_is_well_unnecessary(bid, radius);
}
ANK_FUNCTION_2(__building_well_necessity_status)

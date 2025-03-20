#include "water_supply.h"

#include "building/building.h"
#include "building/building_well.h"
#include "core/game_environment.h"
#include "building/building_house.h"
#include "core/svector.h"
#include "core/profiler.h"
#include "config/config.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/canals.h"
#include "grid/building.h"
#include "grid/moisture.h"
#include "grid/building_tiles.h"
#include "grid/desirability.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/terrain.h"
#include "scenario/map.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "tiles.h"

#include <string.h>

e_well_status map_water_supply_is_well_unnecessary(int well_id, int radius) {
    building* well = building_get(well_id);
    int num_houses = 0;
    grid_area area = map_grid_get_area(well->tile, 1, radius);

    for (int yy = area.tmin.y(), endy = area.tmax.y(); yy <= endy; yy++) {
        for (int xx = area.tmin.x(), endx = area.tmax.x(); xx <= endx; xx++) {
            int grid_offset = MAP_OFFSET(xx, yy);
            int building_id = map_building_at(grid_offset);

            auto house = building_get(building_id)->dcast_house();
            if (house && house->hsize() && !house->runtime_data().water_supply) {
                num_houses++;
                //                if (!building_get(building_id)->has_water_access) //todo: water carrier access
                return WELL_NECESSARY;
            }
        }
    }
    return num_houses ? WELL_UNNECESSARY_FOUNTAIN : WELL_UNNECESSARY_NO_HOUSES;
}

#include "building/building_house.h"

#include "building/building_house_model.h"
#include "city/city.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "game/resource.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "grid/routing/routing_terrain.h"
#include "grid/tiles.h"

#include <numeric>

void building_house::determine_worst_desirability_building() {
    auto &housed = runtime_data();
    housed.worst_desirability_building_id = 0;

    grid_area area = map_grid_get_area(tile(), 1, 6);

    const e_house_level my_level = house_level();
    if (!my_level) {
        return;
    }

    int lowest_desirability = 0;
    int lowest_building_id = 0;

    for (int y = area.tmin.y(), endy = area.tmax.y(); y <= endy; y++) {
        for (int x = area.tmin.x(), endx = area.tmax.x(); x <= endx; x++) {
            int building_id = map_building_at(tile2i(x, y));
            if (building_id <= 0)
                continue;

            auto b = building_get(building_id);
            if (!b->is_valid() || building_id == id()) {
                continue;
            }

            int8_t des = b->des_influence.value;
            if (des >= 0) {
                continue;
            }

            auto other_house = b->dcast_house();
            if (other_house && other_house->house_level() >= my_level) {
                continue;
            }

            // simplified desirability calculation
            int step_size = b->des_influence.step_size;
            int range = b->des_influence.range;
            int dist = calc_maximum_distance(vec2i(x, y), tile());
            if (dist <= range) {
                while (--dist > 1) {
                    des += step_size;
                }

                if (des < lowest_desirability) {
                    lowest_desirability = des;
                    lowest_building_id = building_id;
                }
            }
        }
    }

    housed.worst_desirability_building_id = lowest_building_id;
}

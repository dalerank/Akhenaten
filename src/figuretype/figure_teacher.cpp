#include "figure_teacher.h"

#include "building/building_house.h"
#include "figure/service.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_teacher)

int figure_teacher::provide_service() {
    int houses = 0;
    map_grid_area_foreach(map_grid_get_area(tile(), 1, 2), [&] (tile2i t) {
        const int bid = map_building_at(t.grid_offset());
        auto house = bid ? building_get(bid)->dcast_house() : nullptr;
        if (house && house->house_population() > 0) {
            house->runtime_data().school = MAX_COVERAGE;
            houses++;
        }
    });
    return houses;
}

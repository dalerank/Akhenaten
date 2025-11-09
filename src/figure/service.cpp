#include "service.h"

#include "figuretype/figure_market_buyer.h"
#include "building/building_house.h"
#include "game/resource.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "game/tutorial.h"
#include "game/game_config.h"

static int provide_missionary_coverage(int x, int y) {
    grid_area area = map_grid_get_area(tile2i(x, y), 1, 4);

    map_grid_area_foreach(area.tmin, area.tmax, [] (tile2i tile) {
        int building_id = map_building_at(tile.grid_offset());
        if (building_id) {
            building *b = building_get(building_id);
            if (b->type == BUILDING_UNUSED_NATIVE_HUT_88 || b->type == BUILDING_UNUSED_NATIVE_MEETING_89)
                b->sentiment.native_anger = 0;
        }
    });
    return 1;
}

int figure::figure_service_provide_coverage() {
    int houses_serviced = 0;
    int none_service = 0;
    building* b;
    switch (type) {
    case FIGURE_NOBLES:
        return 0;

    case FIGURE_EMBALMER:
        houses_serviced = figure_provide_culture(tile, this, [] (building * b, figure * f) {
            auto house = ((building *)b)->dcast_house();

            if (house) {
                auto &housed = house->runtime_data();
                housed.mortuary = MAX_COVERAGE;
            }
        });
        break;

    case FIGURE_MISSIONARY:
        houses_serviced = provide_missionary_coverage(tile.x(), tile.y());
        break;

    case FIGURE_CHARIOR_RACER:
        houses_serviced = figure_provide_culture(tile, this, [] (building *b, figure *f) {
            auto house = ((building *)b)->dcast_house();

            if (house) {
                auto &housed = house->runtime_data();
                housed.bullfighter = MAX_COVERAGE;
            }
        });
        break;
 
    //case FIGURE_TOMB_ROBER:
    //    if (figure_rioter_collapse_building() == 1) {
    //        return 1;
    //    }
    //    break;

    default:
        houses_serviced = dcast()->provide_service();
        break;
    }

    if (has_home()) {
        b = home()->main();
        b->houses_covered += houses_serviced;
        if (b->houses_covered >= 300)
            b->houses_covered = 300;
    }

    return 0;
}

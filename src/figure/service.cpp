#include "service.h"

#include "figuretype/figure_market_buyer.h"
#include "building/building_house.h"
#include "building/model.h"
#include "figuretype/crime.h"
#include "game/resource.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "game/tutorial.h"
#include "config/config.h"

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

static void hippodrome_coverage(building* b, figure *f, int&) {
    b->data.house.hippodrome = MAX_COVERAGE;
}

static void mortuary_coverage(building* b, figure *f, int&) {
    b->data.house.mortuary = MAX_COVERAGE;
}

static void policeman_coverage(building* b, figure *f, int &max_anger_seen) {
    b->house_criminal_active -= 1;
    b->house_criminal_active = std::max<int>(0, b->house_criminal_active);

    if (b->house_criminal_active > max_anger_seen) {
        max_anger_seen = b->house_criminal_active;
    }
}

int figure::figure_service_provide_coverage() {
    int houses_serviced = 0;
    int none_service = 0;
    building* b;
    switch (type) {
    case FIGURE_NOBLES:
        return 0;

    case FIGURE_EMBALMER:
        houses_serviced = figure_provide_culture(tile, this, mortuary_coverage);
        break;

    case FIGURE_MISSIONARY:
        houses_serviced = provide_missionary_coverage(tile.x(), tile.y());
        break;

    case FIGURE_CHARIOR_RACER:
    case FIGURE_SENET_PLAYER:
        houses_serviced = figure_provide_culture(tile, this, hippodrome_coverage);
        break;
 
    case FIGURE_TOMB_ROBER:
        if (figure_rioter_collapse_building() == 1) {
            return 1;
        }
        break;

    case FIGURE_CONSTABLE: {
            int max_criminal_active = 0;
            houses_serviced = figure_provide_service(tile, this, max_criminal_active, policeman_coverage);
            if (max_criminal_active > min_max_seen)
                min_max_seen = max_criminal_active;
            else if (min_max_seen <= 10)
                min_max_seen = 0;
            else
                min_max_seen -= 10;
        }
        break;

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

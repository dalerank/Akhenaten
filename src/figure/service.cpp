#include "service.h"

#include "figuretype/figure_market_buyer.h"
#include "building/building_house.h"
#include "game/resource.h"
#include "grid/building.h"
#include "grid/grid.h"
#include "game/game_config.h"

#include <algorithm>

static int provide_missionary_coverage(int x, int y) {
    grid_area area = map_grid_get_area(tile2i(x, y), 1, 4);

    map_grid_area_foreach(area, [] (tile2i tile) {
        int building_id = map_building_at(tile.grid_offset());
        if (building_id) {
            building *b = building_get(building_id);
            if (b->type == BUILDING_UNUSED_NATIVE_HUT_88 || b->type == BUILDING_UNUSED_NATIVE_MEETING_89)
                b->sentiment.native_anger = 0;
        }
    });
    return 1;
}

int figure_provide_crime_coverage(tile2i tile, int reduction) {
    int crime_seen = 0;
    figure_provide_service(tile, nullptr, [&](building* b, figure*) {
        auto house = b->dcast_house();
        if (!house) {
            return;
        }

        // TODO: crime is the remake house criminal_active until the OG crime_risk lands (og-diff item 8).
        auto& housed = house->runtime_data();
        crime_seen = std::max<int>(crime_seen, housed.criminal_active);
        housed.criminal_active = (uint8_t)std::max(0, housed.criminal_active - reduction);
    });
    return crime_seen;
}

int figure::figure_service_provide_coverage() {
    int houses_serviced = 0;
    int none_service = 0;
    building* b;
    switch (type) {
    case FIGURE_NOBLES:
        return 0;

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

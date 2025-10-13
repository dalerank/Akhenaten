#include "figure_governor.h"

#include "city/buildings.h"
#include "grid/road_access.h"
#include "building/building_house.h"
#include "graphics/image.h"
#include "js/js_game.h"
#include "city/city.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_governor);

void figure_governor::figure_action() {
    switch (action_state()) {
    case FIGURE_ACTION_120_GOVERNOR_CREATED:
    {
        // if city has palace, all mugger will go there
        base.wait_ticks = 0;
        int senate_id = g_city.buildings.get_palace_id();
        building* b_dst = building_get(senate_id);
        tile2i road_tile = map_closest_road_within_radius(b_dst->tile, b_dst->size, 2);
        if (road_tile.valid()) {
            base.destination_tile = road_tile;
            set_destination(senate_id);
            advance_action(FIGURE_ACTION_121_GOVERNOR_MOVING);
            route_remove();
        } else {
            poof();
        }
    }
    break;

    case FIGURE_ACTION_121_GOVERNOR_MOVING:
        base.move_ticks(1);
        base.wait_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            poof();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(FIGURE_ACTION_120_GOVERNOR_CREATED);
            route_remove();
        }
    break;

    }

    base.wait_ticks++;
    if (base.wait_ticks > 200) {
        poof();
        base.animctx.frame = 0;
    }
}

sound_key figure_governor::phrase_key() const {
    int nobles_in_city = 0;
    buildings_house_do([&] (auto house) {
        if (house->house_population() <= 0) {
            return;
        }

        if (house->house_level() < HOUSE_COMMON_MANOR) {
            return;
        }

        nobles_in_city += house->house_population();
    });

    int nolbes_leave_city_pct = calc_percentage<int>(g_city.migration.nobles_leave_city_this_year, nobles_in_city);
    if (nolbes_leave_city_pct > 10) {
        return "governor_city_left_much_nobles";
    }

    if (g_city.festival.months_since_festival < 6) {
        return "governor_festival_was_near";
    }

    return {};
}
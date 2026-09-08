#include "figure_labor_seeker.h"

#include "core/profiler.h"
#include "city/city.h"
#include "figure/service.h"
#include "building/building_house.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_labor_seeker);

void figure_labor_seeker::figure_action() {
    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_125_ROAMER_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_126_ROAMER_RETURNING);
        break;

    case ACTION_126_ROAMER_RETURNING:
        do_returnhome(TERRAIN_USAGE_ROADS);
        break;
    }
}

void figure_labor_seeker::figure_before_action() {
    building *b = home();
    if (!b->is_valid()) {
        poof();
    }
}

int figure_labor_seeker::provide_service() {
    int houses_serviced = 0;
    figure_provide_service(tile(), &base, [&] (building *b, figure *f) {
        auto house = b->dcast_house();
        if (!house) {
            return;
        }

        if (house->house_population() <= 0) {
            return;
        }

        if (house->is_nobles()) {
            return;
        }

        houses_serviced++;
    });
    return houses_serviced;
}

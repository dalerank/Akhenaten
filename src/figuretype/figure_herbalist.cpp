#include "figure_herbalist.h"

#include "core/profiler.h"
#include "figure/service.h"
#include "building/building_house.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_herbalist);

void figure_herbalist::figure_before_action() {
    building* b = home();
    if (!b->is_valid() || !b->has_figure(0, id())) {
        poof();
    }
}

void figure_herbalist::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Herbalist");
    //    building *b = building_get(building_id);
    switch (action_state()) {
    default:
        advance_action(ACTION_11_RETURNING_FROM_PATROL);
        break;

    case FIGURE_ACTION_149_CORPSE:
        break;

    case ACTION_60_HERBALIST_CREATED:
        advance_action(ACTION_10_GOING);
        break;

    case ACTION_61_HERBALIST_ENTERING_EXITING:
    case 9:
        do_enterbuilding(true, home());
        break;

    case ACTION_10_GOING:
    case ACTION_62_HERBALIST_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_11_RETURNING_FROM_PATROL);
        break;

    case ACTION_11_RETURNING_FROM_PATROL:
    case ACTION_63_HERBALIST_RETURNING:
        do_returnhome(TERRAIN_USAGE_ROADS, ACTION_61_HERBALIST_ENTERING_EXITING);
        break;
    }
}

figure_sound_t figure_herbalist::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

sound_key figure_herbalist::phrase_key() const {
    if (runtime_data().see_low_health > 0) {
        return "have_malaria_risk_here";
    } else {
        return "no_threat_malaria_here";
    }

    return {};
}

int figure_herbalist::provide_service() {
    int minmax = 0;
    int houses_serviced = figure_provide_service(tile(), &base, [&] (building *b, figure*) {
        runtime_data().see_low_health += (b->common_health < 20) ? 1 : 0;
        b->common_health = std::max<uint8_t>(b->common_health, 50);

        auto house = b->dcast_house();
        if (house) {
            auto &housed = house->runtime_data();
            housed.apothecary = MAX_COVERAGE;
        }
    });

    return houses_serviced;
}

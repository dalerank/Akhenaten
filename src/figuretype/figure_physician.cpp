#include "figure_physician.h"

#include "core/profiler.h"
#include "building/building_house.h"
#include "city/city_health.h"
#include "city/city.h"
#include "figure/service.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_physician);

void figure_physician::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Physician");
    //    building *b = building_get(building_id);
    switch (action_state()) {
    case ACTION_60_PHYSICIAN_CREATED:
        advance_action(ACTION_10_GOING);
        break;

    case ACTION_61_PHYSICIAN_ENTERING_EXITING:
    case 9:
        do_enterbuilding(true, home());
        break;

    case ACTION_10_GOING:
    case ACTION_62_PHYSICIAN_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_11_RETURNING_FROM_PATROL);
        break;

    case ACTION_11_RETURNING_FROM_PATROL:
    case ACTION_63_PHYSICIAN_RETURNING:
        do_returnhome(TERRAIN_USAGE_ROADS, FIGURE_ACTION_61_ENGINEER_ENTERING_EXITING);
        break;
    }
}

void figure_physician::figure_before_action() {
    building* b = home();
    if (!b->is_valid() || !b->has_figure(0, id())) {
        poof();
    }
}

sound_key figure_physician::phrase_key() const {
    svector<sound_key, 10> keys;
    if (g_city.health.value < 40) {
        keys.push_back(g_city.health.value < 20
                       ? "desease_can_start_at_any_moment"
                       : "city_has_low_health");
    } else if (g_city.health.value > 80) {
        keys.push_back("city_very_healthy");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("city_have_no_army");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("no_food_in_city");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS) {
        keys.push_back("no_job_in_city");
    }

    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("need_workers");
    }

    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("gods_are_angry");
    } else { // gods are good
        keys.push_back("gods_are_pleasures");
    }

    if (g_city.festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("low_entertainment");
    }

    if (keys.empty()) {
        return "all_good_in_city";
    }

    int index = rand() % keys.size();
    return xstring().printf("doctor_", keys[index].c_str());
}

int figure_physician::provide_service() {
    int houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
        auto house = b->dcast_house();

        if (house && house->house_population() > 0) {
            house->runtime_data().physician = MAX_COVERAGE;
            b->common_health = std::min(b->common_health + 1, 100);
        }
    });
    return houses_serviced;
}

figure_sound_t figure_physician::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

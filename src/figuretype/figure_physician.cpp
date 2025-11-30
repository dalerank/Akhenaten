#include "figure_physician.h"

#include "core/profiler.h"
#include "building/building_house.h"
#include "building/building_physician.h"
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
        advance_action(ACTION_10_PHYSICIAN_GOING);
        break;

    case ACTION_10_PHYSICIAN_GOING:
        advance_action(ACTION_62_PHYSICIAN_ROAMING);
        break;

    case ACTION_61_PHYSICIAN_ENTERING_EXITING:
    case 9:
        do_enterbuilding(true, home());
        break;

    case ACTION_62_PHYSICIAN_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_63_PHYSICIAN_RETURNING);
        break;

    case ACTION_63_PHYSICIAN_RETURNING:
        do_returnhome(TERRAIN_USAGE_ROADS, ACTION_61_PHYSICIAN_ENTERING_EXITING);
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
    return xstring().printf("doctor_%s", keys[index].c_str());
}

int figure_physician::provide_service() {
    building *physician_building = home();
    if (!physician_building) {
        return 0;
    }

    auto physician = physician_building->dcast_physician();
    if (!physician) {
        return 0;
    }

    auto &physician_data = physician->runtime_data();
    const auto &params = physician->current_params();

    // Check if already served 1000 residents this month
    if (physician_data.residents_served_this_month >= params.max_serve_clients) {
        return 0;
    }

    int heal_amount = current_params().health_heal_amount;
    int houses_serviced = figure_provide_service(tile(), &base, [&] (building *b, figure *f) {
        auto house = b->dcast_house();
        if (!house || house->house_population() <= 0) {
            return;
        }

        auto &housed = house->runtime_data();        
        if (housed.physician < MAX_COVERAGE / 2) {
            int house_population = house->house_population();
            physician_data.residents_served_this_month += house_population;
            housed.physician = MAX_COVERAGE;
        }

        b->common_health = std::min(b->common_health + heal_amount, 100);
    });
    return houses_serviced;
}

figure_sound_t figure_physician::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

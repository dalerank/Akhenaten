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

sound_key figure_labor_seeker::phrase_key() const {
    svector<sound_key, 10> keys;
    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS) {
        keys.push_back("no_jobs");
    }

    if (g_city.labor.workers_needed >= 0) {
        keys.push_back("no_some_workers");
    }

    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("need_workers");
    }

    if (g_city.labor.workers_needed >= 20) {
        keys.push_back("need_more_workers");
    }

    int houses_in_disease = 0;
    buildings_house_do([&] (auto house) {
        if (house->house_population() <= 0) {
            return;
        }
        houses_in_disease = (house->base.disease_days > 0) ? 1 : 0;
    });

    if (houses_in_disease > 0) {
        keys.push_back("disease_in_city");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("city_not_safety");
    }

    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("gods_are_angry");
    } else { // gods are good
        keys.push_back("city_is_amazing");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("no_food_in_city");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_LOW_WAGES) {
        keys.push_back("i_want_to_leave_city");
    }

    if (g_city.labor.unemployment_percentage >= 15) {
        keys.push_back("much_unemployments");
    }

    keys.push_back("i_looking_for_the_workers");
    int index = rand() % keys.size();
    return xstring().printf("recruiter_%s", keys[index].c_str());
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

figure_sound_t figure_labor_seeker::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

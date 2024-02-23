#include "figure_architector.h"

#include "core/profiler.h"
#include "city/sentiment.h"
#include "city/labor.h"
#include "city/gods.h"
#include "city/data_private.h"
#include "figure/service.h"

#include "js/js_game.h"

struct architector_model : public figures::model_t<FIGURE_ARCHITECT, figure_architector> {};
architector_model architector_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_architector);
void config_load_figure_architector() {
    g_config_arch.r_section("figure_architect", [] (archive arch) {
        architector_m.anim.load(arch);
    });
}

void figure_architector::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Architector");
    //    building *b = building_get(building_id);
    switch (action_state()) {
    case FIGURE_ACTION_60_ENGINEER_CREATED:
        advance_action(ACTION_10_GOING);
        break;

    case FIGURE_ACTION_61_ENGINEER_ENTERING_EXITING:
    case 9:
        do_enterbuilding(true, home());
        break;

    case ACTION_10_GOING:
    case FIGURE_ACTION_62_ENGINEER_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_11_RETURNING_FROM_PATROL);
        break;

    case ACTION_11_RETURNING_FROM_PATROL:
    case FIGURE_ACTION_63_ENGINEER_RETURNING:
        do_returnhome(TERRAIN_USAGE_ROADS, FIGURE_ACTION_61_ENGINEER_ENTERING_EXITING);
        break;
    }
}

sound_key figure_architector::phrase_key() const {
    svector<sound_key, 10> keys;

    int houses_damage_risk = 0;
    int hoeses_damage_high = 0;
    buildings_valid_do([&] (building &b) {
        houses_damage_risk += (b.damage_risk > 70) ? 1 : 0;
        hoeses_damage_high += (b.damage_risk > 50) ? 1 : 0;
    });

    if (houses_damage_risk > 0) {
        keys.push_back("engineer_extreme_damage_level");
    }

    if (formation_get_num_forts() < 0) {
        keys.push_back("engineer_city_not_safety");
    }

    if (hoeses_damage_high > 0) {
        keys.push_back("engineer_high_damage_level");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("engineer_no_food_in_city");
    }

    if (city_labor_workers_needed() >= 20) {
        keys.push_back("engineer_need_more_workers");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("engineer_gods_are_angry");
    }

    if (city_sentiment() < 30) {
        keys.push_back("engineer_city_has_bad_reputation");
    }

    if (city_sentiment() > 50) {
        keys.push_back("engineer_city_is_good");
    }

    if (city_sentiment() >= 30) {
        keys.push_back("engineer_city_is_bad");
    }

    if (city_data_struct()->festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("engineer_low_entertainment");
    }

    if (city_sentiment() > 90) {
        keys.push_back("engineer_city_is_amazing");
    }

    keys.push_back("engineer_i_am_works");

    int index = rand() % keys.size();
    return keys[index];
}

static void engineer_coverage(building* b, figure *f, int &max_damage_seen) {
    if (b->type == BUILDING_SENET_HOUSE || b->type == BUILDING_STORAGE_YARD_SPACE)
        b = b->main();

    if (b->damage_risk > max_damage_seen)
        max_damage_seen = b->damage_risk;

    b->damage_risk = 0;
} 

int figure_architector::provide_service() {
    int max_damage = 0;
    int houses_serviced = figure_provide_service(tile(), &base, max_damage, engineer_coverage);
    if (max_damage > base.min_max_seen) {
        base.min_max_seen = max_damage;
    } else if (base.min_max_seen <= 10) {
        base.min_max_seen = 0;
    } else {
        base.min_max_seen -= 10;
    }
    return houses_serviced;
}

#include "figure_architector.h"

#include "core/profiler.h"
#include "core/log.h"
#include "city/city.h"
#include "figure/service.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_architector);

void figure_architector::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Architector");
    //    building *b = building_get(building_id);
    switch (action_state()) {
    default:
        advance_action(ACTION_11_RETURNING_FROM_PATROL);
        break;

    case FIGURE_ACTION_149_CORPSE:
        break;

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

void figure_architector::figure_before_action() {
    building* b = home();
    if (!b->is_valid() || !b->has_figure(0, id())) {
        poof();
    }
}

sound_key figure_architector::phrase_key() const {
    int houses_damage_risk = 0;
    int hoeses_damage_high = 0;
    buildings_valid_do([&] (building &b) {
        houses_damage_risk += (b.damage_risk > 70) ? 1 : 0;
        hoeses_damage_high += (b.damage_risk > 50) ? 1 : 0;
    });

    const int sentiment = g_city.sentiment.value;
    svector<sound_key_state, 16> keys = {
        {"extreme_damage_level", houses_damage_risk > 0},
        {"city_not_safety", formation_get_num_forts() < 0},
        {"high_damage_level", hoeses_damage_high > 0},
        {"no_food_in_city", g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD},
        {"need_more_workers", g_city.labor.workers_needed >= 20},
        {"gods_are_angry", g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT},
        {"city_has_bad_reputation", sentiment < 30},
        {"city_is_good", sentiment > 50},
        {"city_is_bad", sentiment >= 30},
        {"low_entertainment", g_city.festival.months_since_festival > 6},
        {"city_is_amazing", sentiment > 90},
        {"i_am_works", true}
    };

    std::erase_if(keys, [] (auto &it) { return !it.valid; });

    int index = rand() % keys.size();
    return xstring().printf("engineer_%s", keys[index].prefix);
}

void figure_architector::on_action_changed(int saved_action) {
    if (action_state() == ACTION_8_RECALCULATE) {
        logs::info("test");
    }
}

figure_sound_t figure_architector::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

int figure_architector::provide_service() {
    int max_damage = 0;
    int houses_serviced = figure_provide_service(tile(), &base, [&] (building *b, figure *f) {
        b = b->main();
        max_damage = std::max<short>(b->damage_risk, max_damage);
        b->damage_risk = 0;
    });

    if (max_damage > base.min_max_seen) {
        base.min_max_seen = max_damage;
    } else if (base.min_max_seen <= 10) {
        base.min_max_seen = 0;
    } else {
        base.min_max_seen -= 10;
    }
    return houses_serviced;
}

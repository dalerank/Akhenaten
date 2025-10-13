#include "figure_water_carrier.h"

#include "city/city_health.h"
#include "city/ratings.h"
#include "city/city.h"
#include "figure/service.h"
#include "grid/building.h"
#include "graphics/animation.h"
#include "building/building_house.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_water_carrier);

void figure_water_carrier::figure_before_action() {
    building* b = home();
    if (!b->is_valid() || !b->has_figure(0, id())) {
        poof();
    }
}

void figure_water_carrier::figure_action() {
    // TODO
    //    if (config_get(CONFIG_GP_CH_WATER_CARRIER_FIREFIGHT))
    //        if (fight_fire())
    //            image_set_animation(GROUP_FIGURE_PREFECT);

    building* b = home();
    switch (action_state()) {
    case ACTION_10_GOING:
    case FIGURE_ACTION_72_FIREMAN_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_2_ROAMERS_RETURNING);
        break;

    case ACTION_11_RETURNING_FROM_PATROL:
    case FIGURE_ACTION_73_FIREMAN_RETURNING:
        do_returnhome(TERRAIN_USAGE_PREFER_ROADS);
        break;
    //        case FIGURE_ACTION_74_PREFECT_GOING_TO_FIRE:
    //            if (do_goto(destination_x, destination_y, TERRAIN_USAGE_ENEMY, FIGURE_ACTION_75_PREFECT_AT_FIRE))
    //                wait_ticks = 50;
    //            break;
    //        case FIGURE_ACTION_75_PREFECT_AT_FIRE:
    //            extinguish_fire();
    //            direction = attack_direction;
    //            image_set_animation(GROUP_FIGURE_PREFECT, 104, 36);
    //            break;
    }
}

sound_key figure_water_carrier::phrase_key() const {
    svector<sound_key, 10> keys;
    if (g_city.health.value < 30) {
        keys.push_back("desease_can_start_at_any_moment");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("no_food_in_city");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("city_have_no_army");
    }

    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("need_workers");
    }

    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("gods_are_angry");
    }

    if (g_city.kingdome.rating < 30) {
        keys.push_back("city_is_bad");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS) {
        keys.push_back("much_unemployments");
    }

    if (g_city.festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("low_entertainment");
    }

    const int sentiment = g_city.sentiment.value;
    if (sentiment > 50) {
        keys.push_back("city_is_good");
    }

    if (sentiment > 90) {
        keys.push_back("city_is_amazing");
    }

    int index = rand() % keys.size();
    return keys[index];
}

int figure_water_carrier::provide_service() {
    int houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
        auto house = ((building *)b)->dcast_house();

        if (house) {
            auto &housed = house->runtime_data();
            housed.water_supply = MAX_COVERAGE;
        }
    });

    return houses_serviced;
}

figure_sound_t figure_water_carrier::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

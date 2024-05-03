#include "figure_water_carrier.h"

#include "city/health.h"
#include "city/sentiment.h"
#include "city/labor.h"
#include "city/gods.h"
#include "city/ratings.h"
#include "city/city.h"
#include "figure/service.h"
#include "grid/building.h"
#include "graphics/animation.h"

#include "js/js_game.h"

struct water_carrier_model : public figures::model_t<FIGURE_WATER_CARRIER, figure_water_carrier> {};
water_carrier_model water_carrier_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_water_carrier);
void config_load_figure_water_carrier() {
    g_config_arch.r_section("figure_water_carrier", [] (archive arch) {
        water_carrier_m.anim.load(arch);
        water_carrier_m.sounds.load(arch);
    });
}

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

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("no_food_in_city");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("city_have_no_army");
    }

    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("need_workers");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("gods_are_angry");
    }

    if (city_rating_kingdom() < 30) {
        keys.push_back("city_is_bad");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_JOBS) {
        keys.push_back("much_unemployments");
    }

    if (g_city.festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("low_entertainment");
    }

    if (city_sentiment() > 50) {
        keys.push_back("city_is_good");
    }

    if (city_sentiment() > 90) {
        keys.push_back("city_is_amazing");
    }

    int index = rand() % keys.size();
    return keys[index];
}

void water_supply_coverage(building* b, figure *f, int&) {
    b->data.house.water_supply = MAX_COVERAGE;
}

int figure_water_carrier::provide_service() {
    int none_service;
    return figure_provide_service(tile(), &base, none_service, water_supply_coverage);
}

figure_sound_t figure_water_carrier::get_sound_reaction(pcstr key) const {
    return water_carrier_m.sounds[key];
}

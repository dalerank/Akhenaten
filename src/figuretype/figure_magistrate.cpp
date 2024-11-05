#include "figure_magistrate.h"

#include "city/sentiment.h"
#include "city/city.h"
#include "city/labor.h"
#include "city/ratings.h"
#include "city/houses.h"
#include "figure/service.h"

#include "js/js_game.h"

figures::model_t<figure_magistrate> magistrate_m;

void figure_magistrate::figure_action() {
    switch (action_state()) {
    case FIGURE_ACTION_70_POLICEMAN_CREATED:
        advance_action(ACTION_10_GOING);
        break;

    case FIGURE_ACTION_71_POLICEMAN_ENTERING_EXITING:
        do_enterbuilding(true, home());
        break;

    case FIGURE_ACTION_72_POLICEMAN_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_11_RETURNING_FROM_PATROL);
        break;

    case FIGURE_ACTION_73_POLICEMAN_RETURNING:
        do_returnhome(TERRAIN_USAGE_ROADS, FIGURE_ACTION_61_ENGINEER_ENTERING_EXITING);
        break;
    }
}

void figure_magistrate::figure_before_action() {
    building* b = home();
    if (b->state != BUILDING_STATE_VALID || !b->has_figure(0, id())) {
        poof();
    }
}

sound_key figure_magistrate::phrase_key() const {
    int houses_in_disease = 0;
    buildings_valid_do([&] (building &b) {
        if (!b.house_size || !b.house_population) {
            return;
        }
        houses_in_disease = (b.disease_days > 0) ? 1 : 0;
    });

    if (houses_in_disease > 0) {
        return "disease_in_city";
    }

    svector<sound_key, 10> keys;
    int criminals = city_sentiment_criminals();
    if (criminals <= 0) {
        keys.push_back("no_criminals_in_city");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("city_not_safety");
    }

    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("need_workers");
    }

    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("gods_are_angry");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("no_food_in_city");
    }

    if (g_city.ratings.kingdom < 10) {
        keys.push_back("city_bad_reputation");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_JOBS) {
        keys.push_back("much_unemployments");
    }

    const house_demands &demands = g_city.houses;
    if (demands.missing.more_entertainment > 0) {
        keys.push_back("no_entertainment_need");
    }

    if (city_sentiment() > 90) {
        keys.push_back("city_is_amazing");
    } else if (city_sentiment() > 30) {
        keys.push_back("city_not_bad");
    }

    if (base.min_max_seen > 60) {
        keys.push_back("all_good_in_city");
    } else {
        keys.push_back("streets_still_arent_safety");
    }

    keys.push_back("i_hope_we_are_ready");

    int index = rand() % keys.size();
    return keys[index];
}

int figure_magistrate::provide_service() {
    int max_criminal_active = 0;
    int houses_serviced = figure_provide_service(tile(), &base, max_criminal_active, [] (building *b, figure *f, int &) {
        b->data.house.magistrate = MAX_COVERAGE;
    });

    if (max_criminal_active > base.min_max_seen)
        base.min_max_seen = max_criminal_active;
    else if (base.min_max_seen <= 10)
        base.min_max_seen = 0;
    else
        base.min_max_seen -= 10;

    return houses_serviced;
}

figure_sound_t figure_magistrate::get_sound_reaction(xstring key) const {
    return magistrate_m.sounds[key];
}

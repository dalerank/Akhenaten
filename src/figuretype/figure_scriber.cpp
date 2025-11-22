#include "figuretype/figure_scriber.h"

#include "figure/service.h"
#include "building/building_house.h"
#include "city/city.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_scriber);

void figure_scriber::figure_action() {
    switch (action_state()) {
    case ACTION_125_ROAMER_ROAMING:
        base.roam_length++;
        if (base.roam_length >= base.max_roam_length) {
            advance_action(ACTION_126_ROAMER_RETURNING);
        }

        break;

    case ACTION_126_ROAMER_RETURNING:
        ; // nothing here
        break;

    }
}

sound_key figure_scriber::phrase_key() const {
    svector<sound_key, 10> keys;
    
    if (g_city.festival.months_since_festival > 6) {
        keys.push_back("scriber_these_festivals");
    }
    
    if (g_city.health.value < 40) {
        keys.push_back(g_city.health.value < 20 
                       ? "scriber_plague_could_break_out" 
                       : "scriber_plague_could_break_out");
    }
    
    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("scriber_no_food_in_city");
    }
    
    if (formation_get_num_forts() < 1) {
        keys.push_back("scriber_defenses_are_weak");
    }
    
    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("scriber_need_more_workers");
    }
    
    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) {
        keys.push_back("scriber_gods_are_angry");
    }
    
    if (g_city.kingdome.rating < 30) {
        keys.push_back("scriber_reputation_is_low");
    }
    
    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS) {
        keys.push_back("scriber_high_unemployment");
    }
    
    if (g_city.festival.months_since_festival > 6) {
        keys.push_back("scriber_low_entertainment");
    }
    
    const int sentiment = g_city.sentiment.value;
    if (sentiment > 90) {
        keys.push_back("scriber_city_is_amazing");
    } else if (sentiment > 50) {
        keys.push_back("scriber_city_is_ok");
    }
    
    if (keys.empty()) {
        keys.push_back("scriber_city_is_ok");
    }
    
    int index = rand() % keys.size();
    return keys[index];
}

int figure_scriber::provide_service() {
    int houses_serviced = figure_provide_culture(tile(), &base, [] (building *b, figure *f) {
        auto house = ((building *)b)->dcast_house();

        if (house) {
            auto &housed = house->runtime_data();
            housed.academy = MAX_COVERAGE;
        }
    });
    return houses_serviced;
}

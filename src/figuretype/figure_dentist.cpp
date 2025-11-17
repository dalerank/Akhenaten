#include "figuretype/figure_dentist.h"

#include "figure/service.h"
#include "building/building_house.h"
#include "city/city.h"
#include "city/constants.h"
#include "figure/formation.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_dentist);

void figure_dentist::figure_action() {
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

sound_key figure_dentist::phrase_key() const {
    svector<sound_key, 10> keys;
    
    if (g_city.health.value < 40) {
        keys.push_back(g_city.health.value < 20
                       ? "dentist_concerned_about_plague"
                       : "dentist_concerned_about_plague");
    }
    
    if (formation_get_num_forts() < 1) {
        keys.push_back("dentist_defenses_weak");
    }
    
    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("dentist_no_food_in_city");
    }
    
    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("dentist_need_more_workers");
    }
    
    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) {
        keys.push_back("dentist_gods_are_angry");
    }
    
    if (g_city.kingdome.rating < 30) {
        keys.push_back("dentist_reputation_is_low");
    }
    
    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS) {
        keys.push_back("dentist_unemployment_is_high");
    }
    
    if (g_city.festival.months_since_festival > 6) {
        keys.push_back("dentist_low_entertainment");
    }
    
    const int sentiment = g_city.sentiment.value;
    if (sentiment > 90) {
        keys.push_back("dentist_city_is_the_best");
    } else if (sentiment > 50) {
        keys.push_back("dentist_city_is_ok");
    }
    
    if (keys.empty()) {
        keys.push_back("dentist_city_is_ok");
    }
    
    int index = rand() % keys.size();
    return keys[index];
}

void figure_dentist::figure_before_action() {
    auto b = home();
    if (b->state != BUILDING_STATE_VALID || !b->has_figure(0, id())) {
        poof();
    }
}

int figure_dentist::provide_service() {
    int houses_serviced = figure_provide_culture(tile(), &base, [] (building* b, figure *f) {
        auto house = b->dcast_house();
        if (!house) {
            return;
        }
        house->runtime_data().dentist = MAX_COVERAGE;
    });
    return 0;
}

#include "figuretype/figure_embalmer.h"

#include "figure/service.h"
#include "building/building_house.h"
#include "building/building_mortuary.h"
#include "city/city.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_embalmer);

void figure_embalmer::figure_action() {
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

void figure_embalmer::figure_before_action() {
    auto b = home();
    if (b->state != BUILDING_STATE_VALID || !b->has_figure(0, id())) {
        poof();
    }
}

int figure_embalmer::provide_service() {
    building *mortuary_building = home();
    if (!mortuary_building) {
        return 0;
    }
    
    auto mortuary = mortuary_building->dcast_mortuary();
    if (!mortuary) {
        return 0;
    }
    
    auto &mortuary_data = mortuary->runtime_data();
    const auto &params = mortuary->current_params();
    
    // Check if already served max_serve_clients residents this month
    if (mortuary_data.residents_served_this_month >= params.max_serve_clients) {
        return 0;
    }
    
    int houses_serviced = figure_provide_culture(tile(), &base, [&] (building *b, figure *f) {
        auto house = b->dcast_house();
        if (!house || house->house_population() <= 0) {
            return;
        }
        
        auto &housed = house->runtime_data();
        
        if (housed.mortuary < MAX_COVERAGE / 2) {
            int house_population = house->house_population();
            mortuary_data.residents_served_this_month += house_population;
            housed.mortuary = MAX_COVERAGE;
        }
    });
    return houses_serviced;
}

sound_key figure_embalmer::phrase_key() const {
    svector<sound_key, 10> keys;
    
    if (g_city.health.value < 40) {
        keys.push_back(g_city.health.value < 20
                       ? "embalmer_concerned_about_plague"
                       : "embalmer_health_worsening");
    }
    
    if (formation_get_num_forts() < 1) {
        keys.push_back("embalmer_defenses_weak");
    }
    
    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("embalmer_no_food_in_city");
    }
    
    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("embalmer_need_more_workers");
    }
    
    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) {
        keys.push_back("embalmer_gods_are_angry");
    }
    
    if (g_city.kingdome.rating < 30) {
        keys.push_back("embalmer_reputation_is_low");
    }
    
    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS) {
        keys.push_back("embalmer_unemployment_is_high");
    }
    
    if (g_city.festival.months_since_festival > 6) {
        keys.push_back("embalmer_low_entertainment");
    }
    
    const int sentiment = g_city.sentiment.value;
    if (sentiment > 90) {
        keys.push_back("embalmer_city_is_the_best");
    } else if (sentiment > 50) {
        keys.push_back("embalmer_city_is_ok");
    }
    
    if (keys.empty()) {
        keys.push_back("embalmer_city_is_ok");
    }
    
    int index = rand() % keys.size();
    return keys[index];
}
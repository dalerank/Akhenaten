#include "figuretype/figure_dentist.h"

#include "figure/service.h"
#include "building/building_house.h"
#include "building/building_dentist.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/constants.h"
#include "figure/formation.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_dentist);

void figure_dentist::figure_action() {
    switch (action_state()) {
    case ACTION_125_DENTIST_ROAMING:
        {
            building_id noble_house_id = find_noble_house_with_bad_teeth();
            if (noble_house_id > 0) {
                set_destination(noble_house_id);
                advance_action(ACTION_64_DENTIST_GOING_TO_NOBLE_HOUSE);
                break;
            }
        }
        
        base.roam_length++;
        if (base.roam_length >= base.max_roam_length) {
            advance_action(ACTION_126_ROAMER_RETURNING);
        }
        break;

    case ACTION_64_DENTIST_GOING_TO_NOBLE_HOUSE:
        {
            building *dest = destination();
            if (!dest || !dest->is_valid()) {
                advance_action(ACTION_125_ROAMER_ROAMING);
                break;
            }
            
            auto house = dest->dcast_house();
            if (!house || !house->is_nobles() || house->runtime_data().nobles_with_bad_teeth == 0) {
                advance_action(ACTION_125_ROAMER_ROAMING);
                break;
            }
            
            if (do_gotobuilding(dest, true, TERRAIN_USAGE_ROADS, ACTION_65_DENTIST_TREATING_NOBLES)) {
                // threating
            }
        }
        break;

    case ACTION_65_DENTIST_TREATING_NOBLES:
        {
            building *dest = destination();
            if (!dest || !dest->is_valid()) {
                advance_action(ACTION_125_ROAMER_ROAMING);
                break;
            }
            
            auto house = dest->dcast_house();
            if (house && house->is_nobles()) {
                treat_nobles_in_house(house);
            }
            
            advance_action(ACTION_125_ROAMER_ROAMING);
        }
        break;

    case ACTION_126_DENTIST_RETURNING:
        do_returnhome(TERRAIN_USAGE_ROADS);
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

building_id figure_dentist::find_noble_house_with_bad_teeth() {
    building *home_building = home();
    if (!home_building || !home_building->is_valid()) {
        return 0;
    }
    
    return building_closest_route(*home_building,
        [] (building &b) {
            auto house = b.dcast_house();
            if (!house || !house->is_nobles() || house->house_population() <= 0) {
                return false;
            }
            return house->runtime_data().nobles_with_bad_teeth > 0;
        },
        [] (building &b) {
            auto house = b.dcast_house();
            if (!house) {
                return 0;
            }
            return 100 - (house->runtime_data().nobles_with_bad_teeth * 10);
        });
}

void figure_dentist::treat_nobles_in_house(building_house *house) {
    if (!house || !house->is_nobles() || house->house_population() <= 0) {
        return;
    }
    
    building *dentist_building = home();
    if (!dentist_building) {
        return;
    }
    
    auto dentist = dentist_building->dcast_dentist();
    if (!dentist) {
        return;
    }
    
    auto &dentist_data = dentist->runtime_data();
    const auto &params = dentist->current_params();
    
    if (dentist_data.residents_served_this_month >= params.max_serve_clients) {
        return;
    }
    
    int house_population = house->house_population();
   
    auto &housed = house->runtime_data();
    housed.dentist = MAX_COVERAGE;
    dentist_data.residents_served_this_month += house_population;

    if (housed.nobles_with_bad_teeth > 0) {
        housed.nobles_with_bad_teeth--;
    }
}

int figure_dentist::provide_service() {
    building *dentist_building = home();
    if (!dentist_building) {
        return 0;
    }
    
    auto dentist = dentist_building->dcast_dentist();
    if (!dentist) {
        return 0;
    }
    
    auto &dentist_data = dentist->runtime_data();
    const auto &params = dentist->current_params();
    
    // Check if already served max_serve_clients residents this month
    if (dentist_data.residents_served_this_month >= params.max_serve_clients) {
        return 0;
    }
    
    int houses_serviced = figure_provide_culture(tile(), &base, [&] (building* b, figure *f) {
        auto house = b->dcast_house();
        if (!house || house->house_population() <= 0) {
            return;
        }
        
        auto &housed = house->runtime_data();

        if (housed.dentist < MAX_COVERAGE / 2) {
            int house_population = house->house_population();
            dentist_data.residents_served_this_month += house_population;
            housed.dentist = MAX_COVERAGE;
        }            
    });
    return houses_serviced;
}

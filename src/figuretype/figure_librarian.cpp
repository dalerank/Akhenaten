#include "figure_librarian.h"

#include "figure/service.h"
#include "city/city.h"
#include "figure/service.h"
#include "building/building_house.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_librarian);

int figure_librarian::provide_service() {
    int houses_serviced = figure_provide_culture(tile(), &base, [] (building* b, figure *f) {
        auto house = ((building *)b)->dcast_house();

        if (house) {
            auto &housed = house->runtime_data();
            housed.library = MAX_COVERAGE;
        }
    });
    return houses_serviced;
}

sound_key figure_librarian::phrase_key() const {
    svector<sound_key, 10> keys;
    
    if (g_city.festival.months_since_festival > 6) {
        keys.push_back("library_read_about_festivals");
    }
    
    if (g_city.health.value < 40) {
        keys.push_back("library_people_are_sick");
    }
    
    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("library_no_food_in_city");
    }
    
    if (formation_get_num_forts() < 1) {
        keys.push_back("library_defenses_are_weak");
    }
    
    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("library_need_more_workers");
    }
    
    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) {
        keys.push_back("library_gods_are_angry");
    }
    
    if (g_city.kingdome.rating < 30) {
        keys.push_back("library_reputation_is_low");
    }
    
    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS) {
        keys.push_back("library_high_unemployment");
    }
    
    if (g_city.festival.months_since_festival > 6) {
        keys.push_back("library_low_entertainment");
    }
    
    const int sentiment = g_city.sentiment.value;
    if (sentiment > 90) {
        keys.push_back("library_city_is_amazing");
    } else if (sentiment > 50) {
        keys.push_back("library_city_is_ok");
    }
    
    if (keys.empty()) {
        keys.push_back("library_city_is_ok");
    }
    
    int index = rand() % keys.size();
    return keys[index];
}
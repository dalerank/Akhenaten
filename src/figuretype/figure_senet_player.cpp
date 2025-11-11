#include "figure_senet_player.h"

#include "figure/service.h"
#include "city/city.h"
#include "figure/service.h"
#include "building/building_house.h"
#include "building/building_entertainment.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_senet_player);

void figure_senet_player::update_shows() {
    building_entertainment *entertainment = destination()->dcast_entertainment();
    auto &d = entertainment->runtime_data();
    d.juggler_visited = 32;
}

sound_key figure_senet_player::phrase_key() const {
    int enemies = g_city.figures.enemies;
    if (enemies > 0) {
        return "city_not_safety_workers_leaving";
    }

    svector<sound_key, 10> keys;
    uint32_t months_since_last_festival = g_city.religion.months_since_last_festival();
    if (months_since_last_festival < 6) {
        keys.push_back("i_like_festivals");
    }

    int houses_in_disease = 0;
    buildings_house_do([&] (auto house) {
        if (house->house_population() <= 0) {
            return;
        }

        houses_in_disease = (house->base.disease_days > 0) ? 1 : 0;
    });

    if (houses_in_disease > 0) {
        return "disease_in_city";
    }

    const int sentiment = g_city.sentiment.value;
    if (sentiment < 30) {
        if (sentiment < 20) {
            keys.push_back("city_verylow_sentiment");
        }
        keys.push_back("city_low_sentiment");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS) {
        keys.push_back("much_unemployments");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_LOW_WAGES) {
        keys.push_back("salary_too_low");
    }

    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("gods_are_angry");
    } else {
        keys.push_back("gods_are_pleasures");
    }

    if (g_city.festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("low_entertainment");
    }

    if (sentiment > 40) {
        keys.push_back("city_is_good");
    }

    if (sentiment > 90) {
        keys.push_back("city_is_amazing");
    }

    int index = rand() % keys.size();
    return xstring().printf( "senet_%s", keys[index].c_str());
}

int figure_senet_player::provide_service() {
    int houses_serviced = 0;
    houses_serviced = figure_provide_culture(tile(), &base, [] (building *b, figure *f) {
        auto house = ((building *)b)->dcast_house();

        if (house) {
            auto &housed = house->runtime_data();
            housed.senet_player = MAX_COVERAGE;
        }
    });
    return houses_serviced;
}

figure_sound_t figure_senet_player::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}
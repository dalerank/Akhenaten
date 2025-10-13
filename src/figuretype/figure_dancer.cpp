#include "figure_dancer.h"

#include "figure/service.h"
#include "city/city_health.h"
#include "city/city.h"
#include "city/ratings.h"
#include "sound/sound.h"
#include "building/building_entertainment.h"
#include "building/building_house.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_dancer);

void figure_dancer::update_shows() {
    auto ent = destination()->dcast_entertainment();
    ent->runtime_data().dancer_visited = 32;
}

sound_key figure_dancer::phrase_key() const {
    svector<sound_key, 10> keys;
    uint32_t months_since_last_festival = g_city.religion.months_since_last_festival();
    if (months_since_last_festival < 6) {
        keys.push_back("i_like_festivals");
    }

    if (g_city.health.value < 20) {
        keys.push_back("desease_can_start_at_any_moment");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("city_not_safety_workers_leaving");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("no_food_in_city");
    }

    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("need_workers");
    }

    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("gods_are_angry");
    } else {
        keys.push_back("gods_are_pleasures");
    }

    if (g_city.kingdome.rating < 30) {
        keys.push_back("city_is_bad");
    }

    const int sentiment = g_city.sentiment.value;
    if (sentiment > 50) {
        keys.push_back("city_is_good");
    }

    if (sentiment > 90) {
        keys.push_back("city_is_amazing");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_LOW_WAGES) {
        keys.push_back("salary_too_low");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS) {
        keys.push_back("much_unemployments");
    }

    int index = rand() % keys.size();
    return keys[index];
}

bool figure_dancer::play_die_sound() {
    g_sound.play_effect(SOUND_EFFECT_DANCER_DIE);
    return true;
}

int figure_dancer::provide_service() {
    building *b = current_destination();
    int houses_serviced = provide_entertainment(0, [] (building *b, int shows) {
        auto house = ((building *)b)->dcast_house();

        if (house) {
            auto &housed = house->runtime_data();
            housed.pavillion_dancer = MAX_COVERAGE;
        }
    });
    return houses_serviced;
}

figure_sound_t figure_dancer::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

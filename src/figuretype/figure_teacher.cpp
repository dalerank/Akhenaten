#include "figure_teacher.h"

#include "city/city_health.h"
#include "city/city.h"
#include "city/ratings.h"
#include "building/building_house.h"
#include "figure/service.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_teacher)

void figure_teacher::figure_action() {
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

sound_key figure_teacher::phrase_key() const {
    svector<sound_key, 10> keys;

    if (g_city.health.value < 20) {
        keys.push_back("teacher_desease_can_start_at_any_moment");
    }

    if (g_city.festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("teacher_low_entertainment");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("teacher_no_food_in_city");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("teacher_city_not_safety");
    }

    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("teacher_gods_are_angry");
    }

    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("teacher_need_workers");
    }

    if (g_city.kingdome.rating < 30) {
        keys.push_back("teacher_low_rating");
    }

    if (g_city.labor.unemployment_percentage >= 15) {
        keys.push_back("teacher_much_unemployments");
    }

    const int sentiment = g_city.sentiment.value;
    if (sentiment > 90) {
        keys.push_back("teacher_city_is_amazing");
    } else if (sentiment > 70) {
        keys.push_back("teacher_city_much_better");
    } else if (sentiment > 40) {
        keys.push_back("teacher_city_is_good");
    } 

    keys.push_back("teacher_festival_info");

    int index = rand() % keys.size();
    return keys[index];
}

int figure_teacher::provide_service() {
    int houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
        auto house = b->dcast_house();
        if (!house) {
            return;
        }

        if (f->home()->stored_amount(RESOURCE_PAPYRUS) <= 0) {
            return;
        }

        const uint8_t delta_allow_papyrus = MAX_COVERAGE / 4;
        auto &housed = house->runtime_data();
        if ((MAX_COVERAGE - housed.school) > delta_allow_papyrus) {
            f->home()->consume_resource(RESOURCE_PAPYRUS, 1);
        }
        housed.school = MAX_COVERAGE;
    });
    return houses_serviced;
}
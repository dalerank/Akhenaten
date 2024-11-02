#include "figure_teacher.h"

#include "city/city_health.h"
#include "city/city.h"
#include "city/sentiment.h"
#include "city/ratings.h"

#include "figure/service.h"
#include "js/js_game.h"

figures::model_t<figure_teacher> teacher_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_teacher);
void config_load_figure_teacher() {
    teacher_m.load();
}

void figure_teacher::figure_action() {
    switch (action_state()) {
    case FIGURE_ACTION_125_ROAMING:
        base.roam_length++;
        if (base.roam_length >= base.max_roam_length) {
            advance_action(FIGURE_ACTION_126_ROAMER_RETURNING);
        }

        break;

    case FIGURE_ACTION_126_ROAMER_RETURNING:
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

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
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

    if (g_city.ratings.kingdom < 30) {
        keys.push_back("teacher_low_rating");
    }

    if (g_city.labor.unemployment_percentage >= 15) {
        keys.push_back("teacher_much_unemployments");
    }

    if (city_sentiment() > 90) {
        keys.push_back("teacher_city_is_amazing");
    } else if (city_sentiment() > 70) {
        keys.push_back("teacher_city_much_better");
    } else if (city_sentiment() > 40) {
        keys.push_back("teacher_city_is_good");
    } 

    keys.push_back("teacher_festival_info");

    int index = rand() % keys.size();
    return keys[index];
}

void school_coverage(building* b, figure *f, int&) {
    if (f->home()->stored_amount_first <= 0 ) {
        return;
    }

    const uint8_t delta_allow_papyrus = MAX_COVERAGE / 4;
    if ((MAX_COVERAGE - b->data.house.school) > delta_allow_papyrus) {
        f->home()->stored_amount_first--;
    }
    b->data.house.school = MAX_COVERAGE;
}

int figure_teacher::provide_service() {
    int none_value;
    int houses_serviced = figure_provide_service(tile(), &base, none_value, school_coverage);
    return houses_serviced;
}

const animations_t &figure_teacher::anim() const {
    return teacher_m.anim;
}

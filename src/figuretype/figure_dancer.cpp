#include "figure_dancer.h"

#include "figure/service.h"
#include "city/gods.h"
#include "city/health.h"
#include "city/sentiment.h"
#include "city/city.h"
#include "city/ratings.h"
#include "sound/effect.h"

#include "js/js_game.h"

struct dancer_model : public figures::model_t<FIGURE_DANCER, figure_dancer> {};
dancer_model dancer_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_dancer);
void config_load_figure_dancer() {
    g_config_arch.r_section("figure_dancer", [] (archive arch) {
        dancer_m.anim.load(arch);
        dancer_m.sounds.load(arch);
    });
}

void figure_dancer::update_shows() {
    building* b = destination();
    b->data.entertainment.days3_or_play = 32;
}

sound_key figure_dancer::phrase_key() const {
    svector<sound_key, 10> keys;
    uint32_t months_since_last_festival = city_months_since_last_festival();
    if (months_since_last_festival < 6) {
        keys.push_back("i_like_festivals");
    }

    if (g_city.health.value < 20) {
        keys.push_back("desease_can_start_at_any_moment");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("city_not_safety_workers_leaving");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("no_food_in_city");
    }

    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("need_workers");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("gods_are_angry");
    } else {
        keys.push_back("gods_are_pleasures");
    }

    if (g_city.ratings.kingdom < 30) {
        keys.push_back("city_is_bad");
    }

    if (city_sentiment() > 50) {
        keys.push_back("city_is_good");
    }

    if (city_sentiment() > 90) {
        keys.push_back("city_is_amazing");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_LOW_WAGES) {
        keys.push_back("salary_too_low");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_JOBS) {
        keys.push_back("much_unemployments");
    }

    int index = rand() % keys.size();
    return keys[index];
}

bool figure_dancer::play_die_sound() {
    sound_effect_play(SOUND_EFFECT_DANCER_DIE);
    return true;
}

int figure_dancer::provide_service() {
    building *b = current_destination();
    int houses_serviced = provide_entertainment(b->data.entertainment.days2 ? 2 : 1, senet_coverage);
    return houses_serviced;
}

figure_sound_t figure_dancer::get_sound_reaction(pcstr key) const {
    return dancer_m.sounds[key];
}

#include "figure_priest.h"

#include "game/tutorial.h"
#include "city/labor.h"
#include "city/city.h"
#include "city/sentiment.h"
#include "city/houses.h"
#include "city/city_health.h"
#include "city/ratings.h"
#include "figure/service.h"
#include "graphics/image_groups.h"
#include "graphics/image.h"
#include "graphics/animation.h"

#include "js/js_game.h"

figures::model_t<figure_priest> priest_m;
figures::model_t<figure_festival_priest> festival_priest_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_priest);
void config_load_figure_priest() {
    priest_m.load();
    festival_priest_m.load();
}

void figure_priest::figure_before_action() {
    building* b = home();
    if (!b->is_valid() || !b->has_figure(0, id())) {
        poof();
    }
}

void figure_priest::figure_action() {

}

sound_key figure_priest::phrase_key() const {
    pcstr god_prefix = "unk";
    e_god god;
    switch (home()->type) {
    case BUILDING_TEMPLE_OSIRIS: case BUILDING_TEMPLE_COMPLEX_OSIRIS: god = GOD_OSIRIS; god_prefix = "osiris"; break;
    case BUILDING_TEMPLE_RA: case BUILDING_TEMPLE_COMPLEX_RA: god = GOD_RA; god_prefix = "ra"; break;
    case BUILDING_TEMPLE_PTAH: case BUILDING_TEMPLE_COMPLEX_PTAH: god = GOD_PTAH;  god_prefix = "ptah"; break;
    case BUILDING_TEMPLE_SETH: case BUILDING_TEMPLE_COMPLEX_SETH: god = GOD_SETH;  god_prefix = "seth"; break;
    case BUILDING_TEMPLE_BAST: case BUILDING_TEMPLE_COMPLEX_BAST: god = GOD_BAST;  god_prefix = "bast"; break;

    default:
        assert(false);
    }

    svector<sound_key, 10> keys;
    auto create_key = [&] (pcstr fmt) { return sound_key().printf("%s_%s", god_prefix, fmt); };

    if (formation_get_num_forts() < 1) {
        keys.push_back(create_key("city_not_safety"));
    }

    if (g_city.religion.months_since_festival(god) < 6) {
        keys.push_back(create_key("god_love_festival"));
    }

    if (g_city.labor.workers_needed >= 10) {
        keys.push_back(create_key("need_workers"));
    }

    if (city_sentiment() < 30) {
        keys.push_back(create_key("city_low_mood"));
    }

    const house_demands &demands = g_city.houses;
    if (demands.missing.more_entertainment > 1) {  // low entertainment
        keys.push_back(create_key("low_entertainment"));
    } else {
        keys.push_back(create_key("need_entertainment"));
    }

    int houses_in_disease = 0;
    buildings_valid_do([&] (building &b) {
        if (!b.house_size || b.house_population <= 0) {
            return;
        }
        houses_in_disease = (b.disease_days > 0) ? 1 : 0;
    });

    if (houses_in_disease > 0) {
        keys.push_back(create_key("disease_in_city"));
    }

    if (g_city.health.value < 30) {
        keys.push_back(create_key("city_low_health"));
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back(create_key("no_food_in_city"));
    }

    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back(create_key("gods_are_angry"));
    }

    if (g_city.ratings.kingdom < 30) {
        keys.push_back(create_key("low_sentiment"));
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_JOBS) {
        keys.push_back(create_key("much_unemployments"));
    }

    if (city_sentiment() > 90) {
        keys.push_back(create_key("city_is_amazing"));
    } else  if (city_sentiment() > 40) {
        keys.push_back(create_key("city_is_good"));
    }

    int index = rand() % keys.size();
    return keys[index];
}

int figure_priest::provide_service() {
    int houses_serviced = 0;
    int none_service = 0;
    switch (home()->type) {
    case BUILDING_TEMPLE_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        houses_serviced = figure_provide_service(tile(), &base, none_service, [] (building *b, figure *f, int &) {
            if (b->house_size > 0 && b->house_population > 0) {
                b->data.house.temple_osiris = MAX_COVERAGE;
            }
        });
        break;

    case BUILDING_TEMPLE_RA:
    case BUILDING_TEMPLE_COMPLEX_RA:
        houses_serviced = figure_provide_service(tile(), &base, none_service, [] (building *b, figure *f, int &) {
            if (b->house_size > 0 && b->house_population > 0) {
                b->data.house.temple_ra = MAX_COVERAGE;
            }
        });
        break;

    case BUILDING_TEMPLE_PTAH:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
        houses_serviced = figure_provide_service(tile(), &base, none_service, [] (building *b, figure *f, int &) {
            if (b->house_size > 0 && b->house_population > 0) {
                b->data.house.temple_ptah = MAX_COVERAGE;
            }
        });
        break;

    case BUILDING_TEMPLE_SETH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
        houses_serviced = figure_provide_service(tile(), &base, none_service, [] (building *b, figure *f, int &) {
            if (b->house_size > 0 && b->house_population > 0) {
                b->data.house.temple_seth = MAX_COVERAGE;
            }
        });
        break;

    case BUILDING_TEMPLE_BAST:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        houses_serviced = figure_provide_service(tile(), &base, none_service, [] (building *b, figure *f, int &) {
            if (b->house_size > 0 && b->house_population > 0) {
                b->data.house.temple_bast = MAX_COVERAGE;
            }
        });
        break;
    default:
        break;
    }

    return houses_serviced;
}

e_overlay figure_priest::get_overlay() const {
    switch (home()->type) {
    case BUILDING_SHRINE_OSIRIS: case BUILDING_TEMPLE_OSIRIS: case BUILDING_TEMPLE_COMPLEX_OSIRIS: return OVERLAY_RELIGION_OSIRIS;
    case BUILDING_SHRINE_RA: case BUILDING_TEMPLE_RA: case BUILDING_TEMPLE_COMPLEX_RA: return OVERLAY_RELIGION_RA;
    case BUILDING_SHRINE_PTAH: case BUILDING_TEMPLE_PTAH: case BUILDING_TEMPLE_COMPLEX_PTAH: return OVERLAY_RELIGION_PTAH;
    case BUILDING_SHRINE_SETH: case BUILDING_TEMPLE_SETH: case BUILDING_TEMPLE_COMPLEX_SETH: return OVERLAY_RELIGION_SETH;
    case BUILDING_SHRINE_BAST: case BUILDING_TEMPLE_BAST: case BUILDING_TEMPLE_COMPLEX_BAST: return OVERLAY_RELIGION_BAST;

    default:
        assert(false);
    }

    return OVERLAY_NONE;
}

const animations_t &figure_priest::anim() const {
    return priest_m.anim;
}

void figure_priest::update_animation() {
    building* temple = home();
    xstring animkey = {};
    switch (temple->type) {
    case BUILDING_TEMPLE_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        animkey = "osiris_walk";
        break;

    case BUILDING_TEMPLE_RA:
    case BUILDING_TEMPLE_COMPLEX_RA:
        animkey = "ra_walk";
        break;

    case BUILDING_TEMPLE_PTAH:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
        animkey = "ptah_walk";
        break;

    case BUILDING_TEMPLE_SETH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
        animkey = "seth_walk";
        break;

    case BUILDING_TEMPLE_BAST:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        animkey = "bast_walk";
        break;

    default:
        assert(false);
    }

    image_set_animation(animkey);
}

figure_sound_t figure_priest::get_sound_reaction(xstring key) const {
    return priest_m.sounds[key];
}

void figure_festival_priest::figure_action() {
    switch (action_state()) {
    case FIGURE_ACTION_10_FESTIVAL_PRIEST_CREATED:
        base.anim.frame = 0;
        if (--wait_ticks <= 0) {
            advance_action(FIGURE_ACTION_11_FESTIVAL_PRIEST_GOTO_SQUARE);
        }
        break;

    case FIGURE_ACTION_11_FESTIVAL_PRIEST_GOTO_SQUARE:
        if (do_goto(destination_tile, TERRAIN_USAGE_ANY, FIGURE_ACTION_12_FESTIVAL_PRIEST_DANCE)) {
            wait_ticks = rand() % 20;
        }
        break;

    case FIGURE_ACTION_12_FESTIVAL_PRIEST_DANCE:
        if (--wait_ticks <= 0) {
            advance_action(FIGURE_ACTION_13_FESTIVAL_PRIEST_GOTO_HOME);
        }
        break;

    case FIGURE_ACTION_13_FESTIVAL_PRIEST_GOTO_HOME:
        do_gotobuilding(home());
        break;
    }
}

void figure_festival_priest::before_poof() {
    ; //
}

const animations_t &figure_festival_priest::anim() const {
    return festival_priest_m.anim;
}

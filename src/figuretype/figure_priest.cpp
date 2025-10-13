#include "figure_priest.h"

#include "game/tutorial.h"
#include "city/city.h"
#include "city/city_health.h"
#include "city/ratings.h"
#include "figure/service.h"
#include "graphics/image_groups.h"
#include "graphics/image.h"
#include "graphics/animation.h"
#include "building/building_house.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_priest);

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

    const int sentiment = g_city.sentiment.value;
    if (sentiment < 30) {
        keys.push_back(create_key("city_low_mood"));
    }

    const house_demands &demands = g_city.houses;
    if (demands.missing.more_entertainment > 1) {  // low entertainment
        keys.push_back(create_key("low_entertainment"));
    } else {
        keys.push_back(create_key("need_entertainment"));
    }

    int houses_in_disease = 0;
    buildings_house_do([&] (auto house) {
        if (house->house_population() <= 0) {
            return;
        }
        houses_in_disease = (house->base.disease_days > 0) ? 1 : 0;
    });

    if (houses_in_disease > 0) {
        keys.push_back(create_key("disease_in_city"));
    }

    if (g_city.health.value < 30) {
        keys.push_back(create_key("city_low_health"));
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back(create_key("no_food_in_city"));
    }

    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back(create_key("gods_are_angry"));
    }

    if (g_city.kingdome.rating < 30) {
        keys.push_back(create_key("low_sentiment"));
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS) {
        keys.push_back(create_key("much_unemployments"));
    }

    if (sentiment > 90) {
        keys.push_back(create_key("city_is_amazing"));
    } else  if (sentiment > 40) {
        keys.push_back(create_key("city_is_good"));
    }

    int index = rand() % keys.size();
    return keys[index];
}

int figure_priest::provide_service() {
    int houses_serviced = 0;
    switch (home()->type) {
    case BUILDING_TEMPLE_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
            auto house = b->dcast_house();
            if (house && house->house_population() > 0) {
                house->runtime_data().temple_osiris = MAX_COVERAGE;
            }
        });
        break;

    case BUILDING_TEMPLE_RA:
    case BUILDING_TEMPLE_COMPLEX_RA:
        houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
            auto house = b->dcast_house();
            if (house && house->house_population() > 0) {
                house->runtime_data().temple_ra = MAX_COVERAGE;
            }
        });
        break;

    case BUILDING_TEMPLE_PTAH:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
        houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
            auto house = b->dcast_house();
            if (house && house->house_population() > 0) {
                house->runtime_data().temple_ptah = MAX_COVERAGE;
            }
        });
        break;

    case BUILDING_TEMPLE_SETH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
        houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
            auto house = b->dcast_house();
            if (house && house->house_population() > 0) {
                house->runtime_data().temple_seth = MAX_COVERAGE;
            }
        });
        break;

    case BUILDING_TEMPLE_BAST:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
            auto house = b->dcast_house();
            if (house && house->house_population() > 0) {
                house->runtime_data().temple_bast = MAX_COVERAGE;
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
    return current_params().sounds[key];
}



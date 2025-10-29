#include "figure_phrase.h"

#include "building/building.h"
#include "building/building_bazaar.h"
#include "city/city_floods.h"
#include "city/constants.h"
#include "city/city_health.h"
#include "city/ratings.h"
#include "city/city.h"
#include "city/coverage.h"
#include "city/city_labor.h"
#include "city/city_population.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "core/bstring.h"
#include "empire/trader_handler.h"
#include "figure/formation.h"
#include "figure/figure.h"
#include "sound/sound.h"
#include "sound/sound_walker.h"

#include <string.h>

static figure_phrase_t g_figure_sounds[] = {
    {FIGURE_NONE, "artisan"},
    {FIGURE_NONE, "carpenter"},
    {FIGURE_NONE, "desease"},
    {FIGURE_EMBALMER, "embalmer"},
    {FIGURE_NONE, "governor"},
    {FIGURE_NONE, "guard"},
    {FIGURE_NONE, "pharaoh"},
    {FIGURE_ROBBER, "robber"},
    {FIGURE_NONE, "senet"},
    {FIGURE_NONE, "thief"},
    {FIGURE_NONE, "transport"},
    {FIGURE_NONE, "vagrant"},
    {FIGURE_NONE, "warship"},
    {FIGURE_NONE, "zookeeper"}
};

static int citizen_phrase() {
    //    if (++f->phrase_sequence_exact >= 3)
    //        f->phrase_sequence_exact = 0;
    //
    //    return 7 + f->phrase_sequence_exact;
    return 0;
}

static int tower_sentry_phrase() {
    //    if (++f->phrase_sequence_exact >= 2)
    //        f->phrase_sequence_exact = 0;
    //
    //    int enemies = city_figures_enemies();
    //    if (!enemies)
    //        return 7 + f->phrase_sequence_exact;
    //    else if (enemies <= 10)
    //        return 9;
    //    else if (enemies <= 30)
    //        return 10;
    //    else {
    //        return 11;
    //    }
    return 0;
}

static int soldier_phrase() {
    int enemies = g_city.figures.enemies;
    if (enemies >= 40) {
        return 11;
    } else if (enemies > 20) {
        return 10;
    } else if (enemies) {
        return 9;
    }

    return 0;
}

static sound_key phrase_based_on_figure_state(figure *f) {
    switch (f->type) {
    //        case FIGURE_PROTESTER:
    //        case FIGURE_CRIMINAL:
    //        case FIGURE_RIOTER:
    //        case FIGURE_MISSIONARY:
    //            return citizen_phrase(f);
    //        case FIGURE_TOWER_SENTRY:
    //            return tower_sentry_phrase(f);
    //        case FIGURE_FORT_JAVELIN:
    //        case FIGURE_FORT_MOUNTED:
    //        case FIGURE_FORT_LEGIONARY:
    //            return soldier_phrase();
    default:
        return f->dcast()->phrase_key();
    }
    return {};
}

static sound_key phrase_based_on_city_state() {
    //    f->phrase_sequence_city = 0;
    //    int god_state = city_god_state();
    //    int unemployment_pct = city_labor_unemployment_percentage();
    //
    //    if (city_resource_food_supply_months() <= 0)
    //        return 0;
    //    else if (unemployment_pct >= 17)
    //        return 1;
    //    else if (city_labor_workers_needed() >= 10)
    //        return 2;
    //    else if (city_culture_average_entertainment() == 0)
    //        return 3;
    //    else if (god_state == GOD_STATE_VERY_ANGRY)
    //        return 4;
    //    else if (city_culture_average_entertainment() <= 10)
    //        return 3;
    //    else if (god_state == GOD_STATE_ANGRY)
    //        return 4;
    //    else if (city_culture_average_entertainment() <= 20)
    //        return 3;
    //    else if (city_resource_food_supply_months() >= 4 &&
    //             unemployment_pct <= 5 &&
    //             city_culture_average_health() > 0 &&
    //             city_culture_average_education() > 0) {
    //        if (city_population() < 500)
    //            return 5;
    //        else {
    //            return 6;
    //        }
    //    } else if (unemployment_pct >= 10)
    //        return 1;
    //    else {
    //        return 5;
    //    }
    return sound_key();
}

void figure::figure_phrase_determine() {
    if (id <= 0) {
        return;
    }

    if (!phrase_key.empty()) {
        figure_sound_t reaction = dcast()->get_sound_reaction(phrase_key);
        phrase = { reaction.group, reaction.text };
        return;
    }

    phrase = { 0, 0 };
    phrase_key = "";
    
    if (is_enemy() || type == FIGURE_INDIGENOUS_NATIVE || type == FIGURE_NATIVE_TRADER) {
        phrase.id = -1;
        phrase_key = "unknown";
        return;
    }
    
    xstring key = phrase_based_on_figure_state(this);
    if (!key.empty()) {
        phrase_key = key;
    } else {
        phrase_key = phrase_based_on_city_state();
    }

    if (!phrase_key.empty()) {
        figure_sound_t reaction = dcast()->get_sound_reaction(phrase_key.c_str());
        phrase = { reaction.group, reaction.text };
    }
}

static int figure_play_phrase_file(figure *f, e_figure_type type, xstring key) {
    if (type >= 0) {
        auto type_it = std::find_if(std::begin(g_figure_sounds), std::end(g_figure_sounds), [type] (auto &t) { return t.type == type; });

        figure_phrase_t phrase = (type_it == std::end(g_figure_sounds))
                                   ? figure_phrase_t{FIGURE_NONE, ""}
                                   : *type_it;

        if (phrase.type == FIGURE_NONE) {
            phrase = f->dcast()->phrase();
        }

        if (phrase.type == FIGURE_NONE) {
            return -1;
        }

        xstring path;
        if (key.empty()) {
            if (f->phrase.id == 0) {
                f->phrase.id = rand() % 10;
            }
            path.printf("Voice/Walker/%s_random_%02u.wav", type_it->prefix.c_str(), key.c_str(), f->phrase.id);

            if (!g_sound.speech_file_exist(path)) {
                // fallback to standart phrase
                path.printf("Voice/Walker/%s_random_01.wav", type_it->prefix.c_str(), key.c_str());
            }
        } else {
            auto reaction = f->dcast()->get_sound_reaction(key);
            path.printf("Voice/Walker/%s", reaction.sound.c_str());
        }

        g_sound.speech_play_file(path, 255);
    }

    return -1;
}

int figure::figure_phrase_play() {
    if (id <= 0) {
        return 0;
    }
    figure_phrase_determine();
    return figure_play_phrase_file(this, type, phrase_key);
}
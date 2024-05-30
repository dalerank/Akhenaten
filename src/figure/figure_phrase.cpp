#include "figure_phrase.h"

#include "building/building.h"
#include "building/building_bazaar.h"
#include "city/floods.h"
#include "city/constants.h"
#include "city/health.h"
#include "city/ratings.h"
#include "city/houses.h"
#include "city/city.h"
#include "city/coverage.h"
#include "city/gods.h"
#include "city/labor.h"
#include "city/population.h"
#include "city/resource.h"
#include "city/sentiment.h"
#include "core/calc.h"
#include "core/bstring.h"
#include "core/game_environment.h"
#include "figure/trader.h"
#include "figure/formation.h"
#include "figure/figure.h"
#include "sound/speech.h"
#include "sound/sound_walker.h"

#include <string.h>

static e_figure_sound g_figure_sounds[] = {
    {FIGURE_NONE, "artisan"},
    {FIGURE_NONE, "barge"},
    {FIGURE_NONE, "carpenter"},
    {FIGURE_NONE, "desease"},
    {FIGURE_EMBALMER, "embalmer"},
    {FIGURE_NONE, "governor"},
    {FIGURE_NONE, "guard"},
    {FIGURE_LIBRARIAN, "library"},
    {FIGURE_NONE, "pharaoh"},
    {FIGURE_CONSTABLE, "police"},
    {FIGURE_CRIMINAL, "robber"},
    {FIGURE_NONE, "senet"},
    {FIGURE_NONE, "thief"},
    {FIGURE_NONE, "transport"},
    {FIGURE_NONE, "vagrant"},
    {FIGURE_NONE, "warship"},
    {FIGURE_NONE, "woodcutter"},
    {FIGURE_NONE, "zookeeper"}
};

static int lion_tamer_phrase() {
    //    if (action_state == FIGURE_ACTION_150_ATTACK) {
    //        if (++phrase_sequence_exact >= 3)
    //            phrase_sequence_exact = 0;
    //
    //        return 7 + phrase_sequence_exact;
    //    }
    return 0;
}

static sound_key policeman_phrase(figure *f) {
    svector<sound_key, 10> keys;

    if (f->min_max_seen < 10) {
        keys.push_back("policeman_very_low_crime_level");
    } else if (f->min_max_seen < 30) {
        keys.push_back("policeman_low_crime_level");
    } else {
        keys.push_back("policeman_usual_crime_level");
    }

    if (formation_get_num_forts() < 0) {
        keys.push_back("policeman_city_not_safety");
        keys.push_back("policeman_enemies_are_coming");
        keys.push_back("policeman_no_army");
        keys.push_back("policeman_no_army_2");
    }

    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("policeman_need_workers");
    }

    if (g_city.labor.workers_needed >= 20) {
        keys.push_back("policeman_need_more_workers");
    }

    if (g_city.health.value < 20) {
        keys.push_back("policeman_desease_can_start_at_any_moment");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("policeman_no_food_in_city");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("policeman_gods_are_angry");
    }

    if (g_city.labor.unemployment_percentage >= 15) {
        keys.push_back("policeman_much_unemployments");
    }

    if (g_city.festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("policeman_low_entertainment");
    }

    if (city_sentiment() > 90) {
        keys.push_back("policeman_city_is_amazing");
    } else  if (city_sentiment() > 40) {
        keys.push_back("policeman_city_is_good");
    }

    keys.push_back("policeman_iam_too_busy_that_talk");
    keys.push_back("policeman_i_hope_my_work_is_need");

    int index = rand() % keys.size();
    return keys[index];
}

static int citizen_phrase() {
    //    if (++f->phrase_sequence_exact >= 3)
    //        f->phrase_sequence_exact = 0;
    //
    //    return 7 + f->phrase_sequence_exact;
    return 0;
}

static sound_key governor_phrase(figure *f) {
    int nobles_in_city = 0;
    buildings_valid_do([&] (building &b) {
        if (!b.house_size || !b.house_population || b.subtype.house_level < BUILDING_HOUSE_COMMON_MANOR) {
            return;
        }
        nobles_in_city += b.house_population;
    });

    int nolbes_leave_city_pct = calc_percentage<int>(g_city.migration.nobles_leave_city_this_year, nobles_in_city);
    if (nolbes_leave_city_pct > 10) {
        return "governor_city_left_much_nobles";
    }

    if (g_city.festival.months_since_festival < 6) {
        return "governor_festival_was_near";
    }

    return {};
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
    int enemies = g_city.figure.enemies;
    if (enemies >= 40) {
        return 11;
    } else if (enemies > 20) {
        return 10;
    } else if (enemies) {
        return 9;
    }

    return 0;
}

static int trade_ship_phrase() {
    //    if (f->action_state == FIGURE_ACTION_115_TRADE_SHIP_LEAVING) {
    //        if (!trader_has_traded(f->trader_id))
    //            return 9; // no trade
    //        else {
    //            return 11; // good trade
    //        }
    //    } else if (f->action_state == FIGURE_ACTION_112_TRADE_SHIP_MOORED) {
    //        int state = figure_trade_ship_is_trading(f);
    //        if (state == TRADE_SHIP_BUYING)
    //            return 8; // buying goods
    //        else if (state == TRADE_SHIP_SELLING)
    //            return 7; // selling goods
    //        else {
    //            return 9; // no trade
    //        }
    //    } else {
    //        return 10; // can't wait to trade
    //    }
    return 0;
}

static sound_key phrase_based_on_figure_state(figure *f) {
    switch (f->type) {
    case FIGURE_CONSTABLE: return policeman_phrase(f);
    //        case FIGURE_PROTESTER:
    //        case FIGURE_CRIMINAL:
    //        case FIGURE_RIOTER:
    //        case FIGURE_MISSIONARY:
    //            return citizen_phrase(f);
    case FIGURE_GOVERNOR: return governor_phrase(f);
    //        case FIGURE_TOWER_SENTRY:
    //            return tower_sentry_phrase(f);
    //        case FIGURE_FORT_JAVELIN:
    //        case FIGURE_FORT_MOUNTED:
    //        case FIGURE_FORT_LEGIONARY:
    //            return soldier_phrase();
    //        case FIGURE_TRADE_SHIP:
    //            return trade_ship_phrase(f);
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
        figure_sound_t reaction = dcast()->get_sound_reaction(phrase_key.c_str());
        phrase_group = reaction.group;
        phrase_id = reaction.text;
        return;
    }

    phrase_id = 0;
    phrase_key = "";
    
    if (is_enemy() || type == FIGURE_INDIGENOUS_NATIVE || type == FIGURE_NATIVE_TRADER) {
        phrase_id = -1;
        phrase_key = "unknown";
        return;
    }
    
    bstring64 key = phrase_based_on_figure_state(this);
    if (!key.empty()) {
        phrase_key = key;
    } else {
        phrase_key = phrase_based_on_city_state();
    }

    if (!phrase_key.empty()) {
        figure_sound_t reaction = dcast()->get_sound_reaction(phrase_key.c_str());
        phrase_group = reaction.group;
        phrase_id = reaction.text;
    }
}

static int figure_play_phrase_file(figure *f, e_figure_type type, bstring64 key) {
    if (type >= 0) {
        auto type_it = std::find_if(std::begin(g_figure_sounds), std::end(g_figure_sounds), [type] (auto &t) { return t.type == type; });

        e_figure_sound phrase = (type_it == std::end(g_figure_sounds))
                                   ? e_figure_sound{FIGURE_NONE, ""}
                                   : *type_it;

        if (phrase.type == FIGURE_NONE) {
            phrase = f->dcast()->phrase();
        }

        if (phrase.type == FIGURE_NONE) {
            return -1;
        }

        vfs::path path;
        if (key.empty()) {
            if (f->phrase_id == 0) {
                f->phrase_id = rand() % 10;
            }
            path.printf("Voice/Walker/%s_random_%02u.wav", type_it->prefix.c_str(), key.c_str(), f->phrase_id);

            if (!sound_speech_file_exist(path)) {
                // fallback to standart phrase
                path.printf("Voice/Walker/%s_random_01.wav", type_it->prefix.c_str(), key.c_str());
            }
        } else {
            auto reaction = f->dcast()->get_sound_reaction(key);
            path.printf("Voice/Walker/%s", reaction.fname.c_str());
        }

        sound_speech_play_file(path);
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
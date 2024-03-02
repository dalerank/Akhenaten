#include "figure_phrase.h"

#include "building/building.h"
#include "building/building_bazaar.h"
#include "city/floods.h"
#include "city/constants.h"
#include "city/health.h"
#include "city/ratings.h"
#include "city/houses.h"
#include "city/data_private.h"
#include "city/coverage.h"
#include "city/figures.h"
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
    {FIGURE_NONE, "brick"},
    {FIGURE_TRADE_CARAVAN, "caravan"},
    {FIGURE_NONE, "carpenter"},
    {FIGURE_DANCER, "dancer"},
    {FIGURE_DENTIST, "dentist"},
    {FIGURE_NONE, "desease"},
    {FIGURE_DOCKER, "dock_pusher"},
    {FIGURE_EMBALMER, "embalmer"},
    {FIGURE_FISHING_BOAT, "fishing"},
    {FIGURE_LABOR_SEEKER, "laborseeker"},
    {FIGURE_NONE, "governor"},
    {FIGURE_NONE, "guard"},
    {FIGURE_JUGGLER, "juggler"},
    {FIGURE_NONE, "labor"},
    {FIGURE_LIBRARIAN, "library"},
    {FIGURE_MAGISTRATE, "magistrate"},
    {FIGURE_MUSICIAN, "musician"},
    {FIGURE_NONE, "pharaoh"},
    {FIGURE_CONSTABLE, "police"},
    {FIGURE_REED_GATHERER, "reed"},
    {FIGURE_CRIMINAL, "robber"},
    {FIGURE_SCRIBER, "scribe"},
    {FIGURE_NONE, "senet"},
    {FIGURE_TEACHER,"teacher"},
    {FIGURE_NONE, "thief"},
    {FIGURE_NONE, "transport"},
    {FIGURE_NONE, "vagrant"},
    {FIGURE_NONE, "warship"},
    {FIGURE_NONE, "woodcutter"},
    {FIGURE_WORKER, "worker"},
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

static sound_key hunter_ostric_phrase(figure *f) {
    if (f->action_state == ACTION_16_HUNTER_INVESTIGATE || f->action_state == ACTION_9_CHASE_PREY || f->action_state == ACTION_15_HUNTER_HUNT) {
        return "hunterostrich_hunting";
    } else {
        return "hunterostrich_back";
    }
}

static sound_key dancer_phrase(figure *f) {
    svector<sound_key, 10> keys;
    uint32_t months_since_last_festival = city_months_since_last_festival();
    if (months_since_last_festival < 6) {
        keys.push_back("dancer_i_like_festivals");
    }

    if (city_health() < 20) {
        keys.push_back("dancer_desease_can_start_at_any_moment");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("dancer_city_not_safety_workers_leaving");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("dancer_no_food_in_city");
    }

    if (city_labor_workers_needed() >= 10) {
        keys.push_back("dancer_need_workers");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("dancer_gods_are_angry");
    } else {
        keys.push_back("dancer_gods_are_pleasures");
    }

    if (city_rating_kingdom() < 30) {
        keys.push_back("dancer_city_is_bad");
    }

    if (city_sentiment() > 50) {
        keys.push_back("dancer_city_is_good");
    }

    if (city_sentiment() > 90) {
        keys.push_back("dancer_city_is_amazing");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_LOW_WAGES) {
        keys.push_back("dancer_salary_too_low");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_JOBS) {
        keys.push_back("dancer_much_unemployments");
    }

    int index = rand() % keys.size();
    return keys[index];
}

static sound_key magistrate_phrase(figure *f) {
    int houses_in_disease = 0;
    buildings_valid_do([&] (building &b) {
        if (!b.house_size || !b.house_population) {
            return;
        }
        houses_in_disease = (b.disease_days > 0) ? 1 : 0;
    });

    if (houses_in_disease > 0) {
        return "magistrate_disease_in_city";
    }

    svector<sound_key, 10> keys;
    int criminals = city_sentiment_criminals();
    if (criminals <= 0) {
        keys.push_back("magistrate_no_criminals_in_city");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("magistrate_city_not_safety");
    }

    if (city_labor_workers_needed() >= 10) {
        keys.push_back("magistrate_need_workers");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("magistrate_gods_are_angry");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("magistrate_no_food_in_city");
    }

    if (city_rating_kingdom() < 10) {
        keys.push_back("magistrate_city_bad_reputation");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_JOBS) {
        keys.push_back("magistrate_much_unemployments");
    }

    const house_demands *demands = city_houses_demands();
    if (demands->missing.more_entertainment > 0) {
        keys.push_back("magistrate_no_entertainment_need");
    }

    if (city_sentiment() > 90) {
        keys.push_back("magistrate_city_is_amazing");
    } else if (city_sentiment() > 30) {
        keys.push_back("magistrate_city_not_bad");
    }

    if (f->min_max_seen > 60) {
        keys.push_back("magistrate_all_good_in_city");
    } else {
        keys.push_back("magistrate_streets_still_arent_safety");
    }

    keys.push_back("magistrate_i_hope_we_are_ready");

    int index = rand() % keys.size();
    return keys[index];
}

static sound_key musician_phrase(figure *f) {
    svector<sound_key, 10> keys;
    uint32_t months_since_last_festival = city_months_since_last_festival();
    if (months_since_last_festival < 6) {
        keys.push_back("musician_i_like_festivals");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("musician_city_not_safety_workers_leaving");
    }

    if (city_health() < 40) {
        keys.push_back("musician_city_heath_too_low");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("musician_no_food_in_city");
    }

    if (city_labor_workers_needed() >= 10) {
        keys.push_back("musician_need_workers");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("musician_gods_are_angry");
    } else {
        keys.push_back("musician_gods_are_pleasures");
    }

    if (city_sentiment() < 30) {
        keys.push_back("musician_city_is_bad_reputation");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_JOBS) {
        keys.push_back("musician_much_unemployments");
    }

    const house_demands *demands = city_houses_demands();
    if (demands->missing.more_entertainment == 0) {
        keys.push_back("musician_no_entertainment_need");
    }

    if (city_sentiment() < 50) {
        keys.push_back("musician_city_not_bad");
    } else {
        keys.push_back("musician_city_is_good");
    }

    int index = rand() % keys.size();
    return keys[index];
}

static sound_key juggler_phrase(figure *f) {
    int enemies = city_figures_enemies();
    if (enemies > 0) {
       return "juggler_city_not_safety_workers_leaving";
    }

    svector<sound_key, 10> keys;
    uint32_t months_since_last_festival = city_months_since_last_festival();
    if (months_since_last_festival < 6) {
        keys.push_back("juggler_i_like_festivals");
    }

    int houses_in_disease = 0;
    buildings_valid_do([&] (building &b) {
        if (!b.house_size || !b.house_population) {
            return;
        }
        houses_in_disease = (b.disease_days > 0) ? 1 : 0;
    });

    if (houses_in_disease > 0) {
        return "juggler_disease_in_city";
    }

    if (city_sentiment() < 30) {
        if (city_sentiment() < 20) {
            keys.push_back("juggler_city_verylow_sentiment");
        }
        keys.push_back("juggler_city_low_sentiment");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_JOBS) {
        keys.push_back("juggler_much_unemployments");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_LOW_WAGES) {
        keys.push_back("juggler_salary_too_low");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("juggler_gods_are_angry");
    } else {
        keys.push_back("juggler_gods_are_pleasures");
    }

    if (city_data_struct()->festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("juggler_low_entertainment");
    }

    if (city_sentiment() > 40) {
        keys.push_back("juggler_city_is_good");
    }

    if (city_sentiment() > 90) {
        keys.push_back("juggler_city_is_amazing");
    }

    int index = rand() % keys.size();
    return keys[index];
}

static sound_key teacher_phrase(figure *f) {
    svector<sound_key, 10> keys;

    if (city_health() < 20) {
        keys.push_back("teacher_desease_can_start_at_any_moment");
    }

    if (city_data_struct()->festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("teacher_low_entertainment");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("teacher_no_food_in_city");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("teacher_city_not_safety");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("teacher_gods_are_angry");
    }

    if (city_labor_workers_needed() >= 10) {
        keys.push_back("teacher_need_workers");
    }

    if (city_rating_kingdom() < 30) {
        keys.push_back("teacher_low_rating");
    }

    if (city_labor_unemployment_percentage() >= 15) {
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

    if (city_labor_workers_needed() >= 10) {
        keys.push_back("policeman_need_workers");
    }

    if (city_labor_workers_needed() >= 20) {
        keys.push_back("policeman_need_more_workers");
    }

    if (city_health() < 20) {
        keys.push_back("policeman_desease_can_start_at_any_moment");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("policeman_no_food_in_city");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("policeman_gods_are_angry");
    }

    if (city_labor_unemployment_percentage() >= 15) {
        keys.push_back("policeman_much_unemployments");
    }

    if (city_data_struct()->festival.months_since_festival > 6) {  // low entertainment
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

    int nolbes_leave_city_pct = calc_percentage<int>(city_data_struct()->migration.nobles_leave_city_this_year, nobles_in_city);
    if (nolbes_leave_city_pct > 10) {
        return "governor_city_left_much_nobles";
    }

    if (city_data_struct()->festival.months_since_festival < 6) {
        return "governor_festival_was_near";
    }

    return {};
}

static sound_key labor_seeker_phrase(figure *f) {
    svector<sound_key, 10> keys;
    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_JOBS) {
        keys.push_back("laborseeker_no_jobs");
    }

    if (city_labor_workers_needed() >= 0) {
        keys.push_back("laborseeker_no_some_workers");
    }

    if (city_labor_workers_needed() >= 10) {
        keys.push_back("laborseeker_need_workers");
    }

    if (city_labor_workers_needed() >= 20) {
        keys.push_back("laborseeker_need_more_workers");
    }

    int houses_in_disease = 0;
    buildings_valid_do([&] (building &b) {
        if (!b.house_size || !b.house_population) {
            return;
        }
        houses_in_disease = (b.disease_days > 0) ? 1 : 0;
    });

    if (houses_in_disease > 0) {
        keys.push_back("laborseeker_disease_in_city");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("laborseeker_city_not_safety_workers_leaving");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("laborseeker_gods_are_angry");
    } else { // gods are good
        keys.push_back("laborseeker_city_is_amazing");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("laborseeker_no_food_in_city");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_LOW_WAGES) {
        keys.push_back("laborseeker_i_want_to_leave_city");
    }

    if (city_labor_unemployment_percentage() >= 15) {
        keys.push_back("laborseeker_much_unemployments");
    }

    keys.push_back("laborseeker_i_looking_for_the_workers");
    int index = rand() % keys.size();
    return keys[index];
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
    int enemies = city_figures_enemies();
    if (enemies >= 40) {
        return 11;
    } else if (enemies > 20) {
        return 10;
    } else if (enemies) {
        return 9;
    }

    return 0;
}

static int docker_phrase() {
    //    if (f->action_state == FIGURE_ACTION_135_DOCKER_IMPORT_GOING_TO_WAREHOUSE ||
    //        f->action_state == FIGURE_ACTION_136_DOCKER_EXPORT_GOING_TO_WAREHOUSE) {
    //        if (calc_maximum_distance(
    //                f->destination_x, f->destination_y, f->source_x, f->source_y) >= 25) {
    //            return 9; // too far
    //        }
    //    }
    return 0;
}

static int trade_caravan_phrase() {
    //    if (++f->phrase_sequence_exact >= 2)
    //        f->phrase_sequence_exact = 0;
    //
    //    if (f->action_state == FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING) {
    //        if (!trader_has_traded(f->trader_id))
    //            return 7; // no trade
    //
    //    } else if (f->action_state == FIGURE_ACTION_102_TRADE_CARAVAN_TRADING) {
    //        if (figure_trade_caravan_can_buy(f, f->destination_building_id, f->empire_city_id))
    //            return 11; // buying goods
    //        else if (figure_trade_caravan_can_sell(f, f->destination_building_id, f->empire_city_id))
    //            return 10; // selling goods
    //
    //    }
    //    return 8 + f->phrase_sequence_exact;
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

    case FIGURE_DANCER: return dancer_phrase(f);
    case FIGURE_OSTRICH_HUNTER: return hunter_ostric_phrase(f);
    case FIGURE_MAGISTRATE: return magistrate_phrase(f);
    case FIGURE_CONSTABLE: return policeman_phrase(f);
    case FIGURE_TEACHER: return teacher_phrase(f);
    //        case FIGURE_PROTESTER:
    //        case FIGURE_CRIMINAL:
    //        case FIGURE_RIOTER:
    //        case FIGURE_MISSIONARY:
    //            return citizen_phrase(f);
    //        case FIGURE_HOMELESS:
    case FIGURE_MUSICIAN: return musician_phrase(f);
    case FIGURE_JUGGLER: return juggler_phrase(f);
    case FIGURE_LABOR_SEEKER: return labor_seeker_phrase(f);
    case FIGURE_GOVERNOR: return governor_phrase(f);
    //        case FIGURE_TOWER_SENTRY:
    //            return tower_sentry_phrase(f);
    //        case FIGURE_FORT_JAVELIN:
    //        case FIGURE_FORT_MOUNTED:
    //        case FIGURE_FORT_LEGIONARY:
    //            return soldier_phrase();
    //        case FIGURE_DOCKER:
    //            return docker_phrase(f);
    //        case FIGURE_TRADE_CARAVAN:
    //            return trade_caravan_phrase(f);
    //        case FIGURE_TRADE_CARAVAN_DONKEY:
    //            while (f->type == FIGURE_TRADE_CARAVAN_DONKEY && f->leading_figure_id) {
    //                f = figure_get(f->leading_figure_id);
    //            }
    //            return f->type == FIGURE_TRADE_CARAVAN ? trade_caravan_phrase(f) : 0;
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
#include "figure_phrase.h"

#include "building/building.h"
#include "building/market.h"
#include "city/constants.h"
#include "city/health.h"
#include "city/houses.h"
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
#include "figuretype/trader.h"
#include "sound/speech.h"
#include "sound/sound_walker.h"

#include <string.h>

static e_figure_sound g_figure_sounds[] = {
    {FIGURE_HERBALIST, "apothecary"},
    {FIGURE_NONE, "artisan"},
    {FIGURE_NONE, "barge"},
    {FIGURE_NONE, "brick"},
    {FIGURE_TRADE_CARAVAN, "caravan"},
    {FIGURE_NONE, "carpenter"},
    {FIGURE_CART_PUSHER, "cartpusher"},
    {FIGURE_DANCER, "dancer"},
    {FIGURE_DENTIST, "dentist"},
    {FIGURE_NONE, "desease"},
    {FIGURE_DOCKER, "dock_pusher"},
    {FIGURE_PHYSICIAN, "doctor"},
    {FIGURE_EMBALMER, "embalmer"},
    {FIGURE_EMIGRANT, "emigrant"},
    {FIGURE_ENGINEER, "engineer"},
    {FIGURE_FIREMAN, "fireman"},
    {FIGURE_FISHING_BOAT, "fishing"},
    {FIGURE_LABOR_SEEKER, "laborseeker"},
    {FIGURE_NONE, "governor"},
    {FIGURE_NONE, "guard"},
    {FIGURE_OSTRICH_HUNTER, "hunt_ant"},
    {FIGURE_IMMIGRANT, "immigrant"},
    {FIGURE_JUGGLER, "juggler"},
    {FIGURE_NONE, "labor"},
    {FIGURE_LIBRARIAN, "library"},
    {FIGURE_MAGISTRATE, "magistrate"},
    {FIGURE_DELIVERY_BOY, "marketboy"},
    {FIGURE_MARKET_BUYER, "mkt_buyer"},
    {FIGURE_MARKET_TRADER, "mkt_seller"},
    {FIGURE_MUSICIAN, "musician"},
    {FIGURE_NONE, "pharaoh"},
    {FIGURE_POLICEMAN, "plice"},
    {FIGURE_PRIEST, "priest_bast"},
    {FIGURE_PRIEST, "priest_osiris"},
    {FIGURE_PRIEST, "priest_ptah"},
    {FIGURE_PRIEST, "priest_ra"},
    {FIGURE_PRIEST, "priest_seth"},
    {FIGURE_REED_GATHERER, "reed"},
    {FIGURE_CRIMINAL, "robber"},
    {FIGURE_NONE, "scribe"},
    {FIGURE_NONE, "senet"},
    {FIGURE_TAX_COLLECTOR, "taxman"},
    {FIGURE_TEACHER,"teacher"},
    {FIGURE_NONE, "thief"},
    {FIGURE_NONE, "transport"},
    {FIGURE_NONE, "vagrant"},
    {FIGURE_NONE, "warship"},
    {FIGURE_WATER_CARRIER, "water"},
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

static int gladiator_phrase() {
    //    return action_state == FIGURE_ACTION_150_ATTACK ? 7 : 0;
    return 0;
}

static int tax_collector_phrase() {
    //    if (min_max_seen >= HOUSE_LARGE_CASA)
    //        return 7;
    //    else if (min_max_seen >= HOUSE_SMALL_HOVEL)
    //        return 8;
    //    else if (min_max_seen >= HOUSE_LARGE_TENT)
    //        return 9;
    //    else {
    //        return 0;
    //    }
    return 0;
}

static int market_trader_phrase() {
    //    if (action_state == FIGURE_ACTION_126_ROAMER_RETURNING) {
    //        if (building_market_get_max_food_stock(building_get(building_id)) <= 0)
    //            return 9; // run out of goods
    //
    //    }
    return 0;
}

static sound_key market_buyer_phrase(figure *f) {
    if (f->action_state == FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE) {
        return "market_buyer_goto_store";
    } else if (f->action_state == FIGURE_ACTION_146_MARKET_BUYER_RETURNING) {
        return "market_buyer_back_to_market";
    } 

    return {};
}

static sound_key physician_phrase(figure *f) {
    int enemies = city_figures_enemies();
    if (enemies > 10) {
        return "physician_enemies_in_city";
    }

    svector<sound_key, 10> keys;
    if (city_health() < 40) {
        keys.push_back(city_health() < 20
                       ? "physician_desease_can_start_at_any_moment"
                       : "physician_city_has_low_health");
    } else if (city_health() > 80) {
        keys.push_back("physician_city_very_healthy");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("physician_no_food_in_city");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_JOBS) {
        keys.push_back("physician_no_job_in_city");
    }

    if (city_labor_workers_needed() >= 10) {
        keys.push_back("physician_need_workers");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("physician_gods_are_angry");
    } else { // gods are good
        keys.push_back("physician_gods_are_pleasures");
    }

    const house_demands *demands = city_houses_demands();
    if (demands->missing.more_entertainment > 0) {  // low entertainment
        keys.push_back("physician_low_entertainment");
    }

    if (keys.empty()) {
        return "physician_all_good_in_city";
    }

    int index = rand() % keys.size();
    return keys[index];
}

static sound_key immigrant_phrase(figure *f) {
    svector<sound_key, 10> keys;
    keys.push_back("immigrant_i_hope_i_need_here");
    keys.push_back("immigrant_i_heard_city_have_work_for_all");
    keys.push_back("immigrant_i_heard_city_have_cheap_food");

    int index = rand() % keys.size();
    return keys[index];
}

static sound_key apothecary_phrase(figure *f) {
    if (f->service_values.apothecary_see_low_health > 0) {
        return "apothecary_have_malaria_risk_here";
    } else {
        return "apothecary_no_threat_malaria_here";
    }

    return {};
}

static sound_key cart_pusher_phrase(figure *f) {
    if (f->action_state == FIGURE_ACTION_20_CARTPUSHER_INITIAL) {
        return "cartpusher_i_have_no_destination";
    }

    if (f->action_state == FIGURE_ACTION_27_CARTPUSHER_RETURNING) {
        return "cartpusher_back_to_home";
    }

    if (f->action_state == FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE ||
        f->action_state == FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY ||
        f->action_state == FIGURE_ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP) {
        return "cartpusher_delivering_items";
    }

    return {};
}

static int warehouseman_phrase() {
    //    if (action_state == FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE) {
    //        if (calc_maximum_distance(
    //                destination_x, destination_y, source_x, f->source_y) >= 25) {
    //            return 9; // too far
    //        }
    //    }
    return 0;
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

    const house_demands *demands = city_houses_demands();
    if (demands->missing.more_entertainment > 0) {  // low entertainment
        keys.push_back("juggler_low_entertainment");
    }

    if (city_sentiment() > 50) {
        keys.push_back("juggler_city_is_good");
    }

    if (city_sentiment() > 90) {
        keys.push_back("juggler_city_is_amazing");
    }

    int index = rand() % keys.size();
    return keys[index];
}

static sound_key fireman_phrase(figure *f) {
    if (f->action_state == FIGURE_ACTION_74_FIREMAN_GOING_TO_FIRE) {
        return "fireman_going_to_fire";
    }
    
    svector<sound_key, 10> keys;
    if (f->action_state == FIGURE_ACTION_75_FIREMAN_AT_FIRE) {
        keys.push_back("fireman_fighting_fire_also");
        keys.push_back("fireman_fighting_fire");

        int index = rand() % keys.size();
        return keys[index];
    }

    if (city_health() < 20) {
        keys.push_back("fireman_desease_can_start_at_any_moment");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("fireman_no_food_in_city");
    }

    int enemies = city_figures_enemies();
    if (enemies > 0) {
        keys.push_back("fireman_city_not_safety_workers_leaving");
    }

    if (city_labor_workers_needed() >= 10) {
        keys.push_back("fireman_need_workers");
    }

    if (city_labor_workers_needed() >= 20) {
        keys.push_back("fireman_need_more_workers");
    }

    int houses_risk_fire = 0;
    buildings_valid_do([&] (building &b) {
        houses_risk_fire = (b.fire_risk > 70) ? 1 : 0;
    });

    if (houses_risk_fire > 0) {
        keys.push_back("fireman_hight_fire_level");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("fireman_gods_are_angry");
    } else {
        keys.push_back("fireman_gods_are_pleasures");
    }

    const house_demands *demands = city_houses_demands();
    if (demands->missing.more_entertainment > 0) {  // low entertainment
        keys.push_back("fireman_low_entertainment");
    }

    if (city_sentiment() > 90) {
        keys.push_back("fireman_city_is_amazing");
    }

    int index = rand() % keys.size();
    return keys[index];
}

static int engineer_phrase() {
    //    if (f->min_max_seen >= 60)
    //        return 7;
    //    else if (f->min_max_seen >= 10)
    //        return 8;
    //    else {
    //        return 0;
    //    }
    return 0;
}

static int citizen_phrase() {
    //    if (++f->phrase_sequence_exact >= 3)
    //        f->phrase_sequence_exact = 0;
    //
    //    return 7 + f->phrase_sequence_exact;
    return 0;
}

static int house_seeker_phrase() {
    //    if (++f->phrase_sequence_exact >= 2)
    //        f->phrase_sequence_exact = 0;
    //
    //    return 7 + f->phrase_sequence_exact;
    return 0;
}

static sound_key emigrant_phrase(figure *f) {
    switch (city_sentiment_low_mood_cause()) {
    case LOW_MOOD_NO_JOBS: return "emigrant_no_job_in_city";
    case LOW_MOOD_NO_FOOD: return "emigrant_no_food_in_city";
    case LOW_MOOD_HIGH_TAXES: return "emigrant_tax_too_high";
    case LOW_MOOD_LOW_WAGES: return "emigrant_salary_too_low";
    }

    building *b = f->destination();
    if (!b || !b->id) {
        return "emigrant_no_house_for_me";
    }

    return  "emigrant_all_good_in_city";
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

    int enemies = city_figures_enemies();
    if (enemies > 0) {
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
    //        case FIGURE_LION_TAMER:
    //            return lion_tamer_phrase(f);
    //        case FIGURE_GLADIATOR:
    //            return gladiator_phrase(f);
    //        case FIGURE_TAX_COLLECTOR:
    //            return tax_collector_phrase(f);
    //        case FIGURE_MARKET_TRADER:
    //            return market_trader_phrase(f);
    case FIGURE_IMMIGRANT: return immigrant_phrase(f);
    case FIGURE_HERBALIST: return apothecary_phrase(f);
    case FIGURE_MARKET_BUYER: return market_buyer_phrase(f);
    case FIGURE_PHYSICIAN: return physician_phrase(f);
    case FIGURE_CART_PUSHER: return cart_pusher_phrase(f);
    //        case FIGURE_WAREHOUSEMAN:
    //            return warehouseman_phrase(f);
    case FIGURE_FIREMAN: return fireman_phrase(f);
    //        case FIGURE_ENGINEER:
    //            return engineer_phrase(f);
    //        case FIGURE_PROTESTER:
    //        case FIGURE_CRIMINAL:
    //        case FIGURE_RIOTER:
    //        case FIGURE_DELIVERY_BOY:
    //        case FIGURE_MISSIONARY:
    //            return citizen_phrase(f);
    //        case FIGURE_HOMELESS:
    case FIGURE_JUGGLER: return juggler_phrase(f);
    case FIGURE_LABOR_SEEKER: return labor_seeker_phrase(f);
    case FIGURE_EMIGRANT: return emigrant_phrase(f);
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
}

static int figure_play_phrase_file(figure *f, e_figure_type type, bstring64 key) {
    if (type >= 0) {
        auto type_it = std::find_if(std::begin(g_figure_sounds), std::end(g_figure_sounds), [type] (auto &t) { return t.type == type; });

        if (type_it == std::end(g_figure_sounds)) {
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
            auto reaction = snd::get_walker_reaction(key);
            path.printf("Voice/Walker/%s", reaction.c_str());
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
#include "phrase.h"

#include "building/building.h"
#include "building/market.h"
#include "city/constants.h"
#include "city/culture.h"
#include "city/figures.h"
#include "city/gods.h"
#include "city/labor.h"
#include "city/population.h"
#include "city/resource.h"
#include "city/sentiment.h"
#include "core/calc.h"
#include "core/game_environment.h"
#include "figure/trader.h"
#include "figuretype/trader.h"
#include "sound/speech.h"

#include <string.h>

#define SOUND_FILENAME_MAX 32

static const char FIGURE_SOUNDS[2][50][SOUND_FILENAME_MAX] = {
    {
        "vigils",
        "wallguard",
        "engine",
        "taxman",
        "market",
        "crtpsh",
        "donkey",
        "boats",
        "priest",
        "teach",
        "pupils",
        "bather",
        "doctor",
        "barber",
        "actors",
        "gladtr",
        "liontr",
        "charot",
        "patric",
        "pleb",
        "rioter",
        "homeless",
        "unemploy",
        "emigrate",
        "immigrant",
        "enemy",
        "local",
        "libary",
        "srgeon",
        "docker",
        "missionary",
        "granboy"
    },
    {
        //
    }
};
static const char FIGURE_PHRASE_VARIANTS[2][20][SOUND_FILENAME_MAX] = {
    {
        "_starv1.wav", "_nojob1.wav", "_needjob1.wav", "_nofun1.wav",
        "_relig1.wav", "_great1.wav", "_great2.wav", "_exact1.wav",
        "_exact2.wav", "_exact3.wav", "_exact4.wav", "_exact5.wav",
        "_exact6.wav", "_exact7.wav", "_exact8.wav", "_exact9.wav",
        "_exact0.wav", "_free1.wav", "_free2.wav", "_free3.wav"
    },
    {
        "_g01.wav", "_g02.wav", "_g03.wav", "_g04.wav",
        "_g05.wav", "_g06.wav", "_g07.wav", "_g08.wav",
        "_g09.wav", "_g10.wav", "_e01.wav", "_e02.wav",
        "_e03.wav", "_e04.wav", "_e05.wav", "_e06.wav",
        "_e07.wav", "_e08.wav", "_e09.wav", "_e10.wav"
    }
};
static const int int_TO_SOUND_TYPE[2][200] = {
    {
        -1, 24, 23, 21, 5, 19, -1, 3, 2, 5, // 0-9
        0, 1, 1, 1, -1, 14, 15, 16, 17, 6, // 10-19
        7, 6, 20, 20, 20, -1, 4, 8, 10, 9, // 20-29
        9, 13, 11, 12, 12, 19, -1, -1, 5, 4, // 30-39
        18, -1, 1, 25, 25, 25, 25, 25, 25, 25, // 40-49
        25, 25, 25, 25, 25, 25, 25, 25, -1, -1, // 50-59
        -1, -1, -1, -1, 30, -1, 31, -1, -1, -1, // 60-69
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 // 70-79
    },
    {
        //
    }
};

enum {
    GOD_STATE_NONE = 0,
    GOD_STATE_VERY_ANGRY = 1,
    GOD_STATE_ANGRY = 2
};

static int lion_tamer_phrase(figure *f)
{
    if (f->action_state == FIGURE_ACTION_150_ATTACK) {
        if (++f->phrase_sequence_exact >= 3)
            f->phrase_sequence_exact = 0;

        return 7 + f->phrase_sequence_exact;
    }
    return 0;
}
static int gladiator_phrase(figure *f)
{
    return f->action_state == FIGURE_ACTION_150_ATTACK ? 7 : 0;
}
static int tax_collector_phrase(figure *f)
{
    if (f->min_max_seen >= HOUSE_LARGE_CASA)
        return 7;
 else if (f->min_max_seen >= HOUSE_SMALL_HOVEL)
        return 8;
 else if (f->min_max_seen >= HOUSE_LARGE_TENT)
        return 9;
 else {
        return 0;
    }
}
static int market_trader_phrase(figure *f)
{
    if (f->action_state == FIGURE_ACTION_126_ROAMER_RETURNING) {
        if (building_market_get_max_food_stock(building_get(f->building_id)) <= 0)
            return 9; // run out of goods

    }
    return 0;
}
static int market_buyer_phrase(figure *f)
{
    if (f->action_state == FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE)
        return 7;
 else if (f->action_state == FIGURE_ACTION_146_MARKET_BUYER_RETURNING)
        return 8;
 else {
        return 0;
    }
}
static int cart_pusher_phrase(figure *f)
{
    if (f->action_state == FIGURE_ACTION_20_CARTPUSHER_INITIAL) {
        if (f->min_max_seen == 2)
            return 7;
 else if (f->min_max_seen == 1)
            return 8;

    } else if (f->action_state == FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE ||
            f->action_state == FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY ||
            f->action_state == FIGURE_ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP) {
        if (calc_maximum_distance(
            f->destination_x, f->destination_y, f->source_x, f->source_y) >= 25) {
            return 9; // too far
        }
    }
    return 0;
}
static int warehouseman_phrase(figure *f)
{
    if (f->action_state == FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE) {
        if (calc_maximum_distance(
            f->destination_x, f->destination_y, f->source_x, f->source_y) >= 25) {
            return 9; // too far
        }
    }
    return 0;
}
static int prefect_phrase(figure *f)
{
    if (++f->phrase_sequence_exact >= 4)
        f->phrase_sequence_exact = 0;

    if (f->action_state == FIGURE_ACTION_74_PREFECT_GOING_TO_FIRE)
        return 10;
 else if (f->action_state == FIGURE_ACTION_75_PREFECT_AT_FIRE)
        return 11 + (f->phrase_sequence_exact % 2);
 else if (f->action_state == FIGURE_ACTION_150_ATTACK)
        return 13 + f->phrase_sequence_exact;
 else if (f->min_max_seen >= 50) {
        // alternate between "no sign of crime around here" and the regular city phrases
        if (f->phrase_sequence_exact % 2)
            return 7;
 else {
            return 0;
        }
    } else if (f->min_max_seen >= 10)
        return 8;
 else {
        return 9;
    }
}
static int engineer_phrase(figure *f)
{
    if (f->min_max_seen >= 60)
        return 7;
 else if (f->min_max_seen >= 10)
        return 8;
 else {
        return 0;
    }
}
static int citizen_phrase(figure *f)
{
    if (++f->phrase_sequence_exact >= 3)
        f->phrase_sequence_exact = 0;

    return 7 + f->phrase_sequence_exact;
}
static int house_seeker_phrase(figure *f)
{
    if (++f->phrase_sequence_exact >= 2)
        f->phrase_sequence_exact = 0;

    return 7 + f->phrase_sequence_exact;
}
static int emigrant_phrase(void)
{
    switch (city_sentiment_int()) {
        case int_NO_JOBS:
            return 7;
        case int_NO_FOOD:
            return 8;
        case int_HIGH_TAXES:
            return 9;
        case int_LOW_WAGES:
            return 10;
        default:
            return 11;
    }
}
static int tower_sentry_phrase(figure *f)
{
    if (++f->phrase_sequence_exact >= 2)
        f->phrase_sequence_exact = 0;

    int enemies = city_figures_enemies();
    if (!enemies)
        return 7 + f->phrase_sequence_exact;
 else if (enemies <= 10)
        return 9;
 else if (enemies <= 30)
        return 10;
 else {
        return 11;
    }
}
static int soldier_phrase(void)
{
    int enemies = city_figures_enemies();
    if (enemies >= 40)
        return 11;
 else if (enemies > 20)
        return 10;
 else if (enemies)
        return 9;

    return 0;
}
static int docker_phrase(figure *f)
{
    if (f->action_state == FIGURE_ACTION_135_DOCKER_IMPORT_GOING_TO_WAREHOUSE ||
        f->action_state == FIGURE_ACTION_136_DOCKER_EXPORT_GOING_TO_WAREHOUSE) {
        if (calc_maximum_distance(
            f->destination_x, f->destination_y, f->source_x, f->source_y) >= 25) {
            return 9; // too far
        }
    }
    return 0;
}
static int trade_caravan_phrase(figure *f)
{
    if (++f->phrase_sequence_exact >= 2)
        f->phrase_sequence_exact = 0;

    if (f->action_state == FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING) {
        if (!trader_has_traded(f->trader_id))
            return 7; // no trade

    } else if (f->action_state == FIGURE_ACTION_102_TRADE_CARAVAN_TRADING) {
        if (figure_trade_caravan_can_buy(f, f->destination_building_id, f->empire_city_id))
            return 11; // buying goods
 else if (figure_trade_caravan_can_sell(f, f->destination_building_id, f->empire_city_id))
            return 10; // selling goods

    }
    return 8 + f->phrase_sequence_exact;
}
static int trade_ship_phrase(figure *f)
{
    if (f->action_state == FIGURE_ACTION_115_TRADE_SHIP_LEAVING) {
        if (!trader_has_traded(f->trader_id))
            return 9; // no trade
 else {
            return 11; // good trade
        }
    } else if (f->action_state == FIGURE_ACTION_112_TRADE_SHIP_MOORED) {
        int state = figure_trade_ship_is_trading(f);
        if (state == TRADE_SHIP_BUYING)
            return 8; // buying goods
 else if (state == TRADE_SHIP_SELLING)
            return 7; // selling goods
 else {
            return 9; // no trade
        }
    } else {
        return 10; // can't wait to trade
    }
}

static int city_god_state(void)
{
    int least_god_happiness = 100;
    for (int i = 0; i < MAX_GODS; i++) {
        int happiness = city_god_happiness(i);
        if (happiness < least_god_happiness)
            least_god_happiness = happiness;

    }
    if (least_god_happiness < 20)
        return GOD_STATE_VERY_ANGRY;
 else if (least_god_happiness < 40)
        return GOD_STATE_ANGRY;
 else {
        return GOD_STATE_NONE;
    }
}
static int phrase_based_on_figure_state(figure *f)
{
    switch (f->type) {
        case FIGURE_LION_TAMER:
            return lion_tamer_phrase(f);
        case FIGURE_GLADIATOR:
            return gladiator_phrase(f);
        case FIGURE_TAX_COLLECTOR:
            return tax_collector_phrase(f);
        case FIGURE_MARKET_TRADER:
            return market_trader_phrase(f);
        case FIGURE_MARKET_BUYER:
            return market_buyer_phrase(f);
        case FIGURE_CART_PUSHER:
            return cart_pusher_phrase(f);
        case FIGURE_WAREHOUSEMAN:
            return warehouseman_phrase(f);
        case FIGURE_PREFECT:
            return prefect_phrase(f);
        case FIGURE_ENGINEER:
            return engineer_phrase(f);
        case FIGURE_PROTESTER:
        case FIGURE_CRIMINAL:
        case FIGURE_RIOTER:
        case FIGURE_DELIVERY_BOY:
        case FIGURE_MISSIONARY:
            return citizen_phrase(f);
        case FIGURE_HOMELESS:
        case FIGURE_IMMIGRANT:
            return house_seeker_phrase(f);
        case FIGURE_EMIGRANT:
            return emigrant_phrase();
        case FIGURE_TOWER_SENTRY:
            return tower_sentry_phrase(f);
        case FIGURE_FORT_JAVELIN:
        case FIGURE_FORT_MOUNTED:
        case FIGURE_FORT_LEGIONARY:
            return soldier_phrase();
        case FIGURE_DOCKER:
            return docker_phrase(f);
        case FIGURE_TRADE_CARAVAN:
            return trade_caravan_phrase(f);
        case FIGURE_TRADE_CARAVAN_DONKEY:
            while (f->type == FIGURE_TRADE_CARAVAN_DONKEY && f->leading_figure_id) {
                f = figure_get(f->leading_figure_id);
            }
            return f->type == FIGURE_TRADE_CARAVAN ? trade_caravan_phrase(f) : 0;
        case FIGURE_TRADE_SHIP:
            return trade_ship_phrase(f);
    }
    return 0;
}
static int phrase_based_on_city_state(figure *f)
{
    f->phrase_sequence_city = 0;
    int god_state = city_god_state();
    int unemployment_pct = city_labor_unemployment_percentage();

    if (city_resource_food_supply_months() <= 0)
        return 0;
 else if (unemployment_pct >= 17)
        return 1;
 else if (city_labor_workers_needed() >= 10)
        return 2;
 else if (city_culture_average_entertainment() == 0)
        return 3;
 else if (god_state == GOD_STATE_VERY_ANGRY)
        return 4;
 else if (city_culture_average_entertainment() <= 10)
        return 3;
 else if (god_state == GOD_STATE_ANGRY)
        return 4;
 else if (city_culture_average_entertainment() <= 20)
        return 3;
 else if (city_resource_food_supply_months() >= 4 &&
            unemployment_pct <= 5 &&
            city_culture_average_health() > 0 &&
            city_culture_average_education() > 0) {
        if (city_population() < 500)
            return 5;
 else {
            return 6;
        }
    } else if (unemployment_pct >= 10)
        return 1;
 else {
        return 5;
    }
}
void figure_phrase_determine(figure *f)
{
    if (f->id <= 0)
            return;
    f->phrase_id = 0;

    if (figure_is_enemy(f) || f->type == FIGURE_INDIGENOUS_NATIVE || f->type == FIGURE_NATIVE_TRADER) {
        f->phrase_id = -1;
        return;
    }

    int phrase_id = phrase_based_on_figure_state(f);
    if (phrase_id)
        f->phrase_id = phrase_id;
    else
        f->phrase_id = phrase_based_on_city_state(f);
}
static void play_sound_file(int sound_id, int phrase_id)
{
    if (sound_id >= 0 && phrase_id >= 0) {
        char path[SOUND_FILENAME_MAX];
        strcpy(path, "wavs/");

        strcat(path, FIGURE_SOUNDS[GAME_ENV][sound_id]);
        strcat(path, FIGURE_PHRASE_VARIANTS[GAME_ENV][phrase_id]);
        sound_speech_play_file(path);
    }
}
int figure_phrase_play(figure *f)
{
    if (f->id <= 0)
        return 0;
    int sound_id = int_TO_SOUND_TYPE[GAME_ENV][f->type];
    play_sound_file(sound_id, f->phrase_id);
    return sound_id;
}
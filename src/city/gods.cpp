#include "gods.h"

#include "building/count.h"
#include "building/granary.h"
#include "building/industry.h"
#include "city/culture.h"
#include "city/data_private.h"
#include "city/health.h"
#include "city/message.h"
#include "city/sentiment.h"
#include "city/trade.h"
#include "core/calc.h"
#include "core/config.h"
#include "core/random.h"
#include "figure/formation_legion.h"
#include "figuretype/water.h"
#include "game/settings.h"
#include "game/time.h"
#include "scenario/property.h"
#include "scenario/invasion.h"

#define TIE 10

void city_gods_reset(void) {
    for (int i = 0; i < MAX_GODS; i++) {
        if (is_god_known(i) == GOD_STATUS_UNKNOWN)
            break;
        god_status *god = &city_data.religion.gods[i];
        god->target_mood = 50;
        god->mood = 50;
        god->wrath_bolts = 0;
        god->blessing_done = 0;
        god->small_curse_done = 0;
        god->unused1 = 0;
        god->unused2 = 0;
        god->unused3 = 0;
        god->months_since_festival = 0;
    }
    city_data.religion.angry_message_delay = 0;
}

void city_gods_reset_neptune_blessing(void) {
    city_data.religion.neptune_double_trade_active = 0;
}

static void perform_small_blessing(int god) {
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        switch (god) {
            case GOD_OSIRIS:
                // slightly better flood
                city_message_post(true, MESSAGE_SMALL_BLESSING_OSIRIS, 0, 0);
                building_bless_farms();
                break;
            case GOD_RA:
                // slightly increased reputation
                city_message_post(true, MESSAGE_SMALL_BLESSING_RA_1, 0, 0);
                return;

                // slightly increased trading
                city_message_post(true, MESSAGE_SMALL_BLESSING_RA_2, 0, 0);
                city_data.religion.neptune_double_trade_active = 1;
                break;
            case GOD_PTAH:
                // restocks shipwrights, weavers and jewelers
                city_message_post(true, MESSAGE_SMALL_BLESSING_PTAH, 0, 0);
//                building_granary_bless();
                break;
            case GOD_SETH:
                // protects soldiers far away
                city_message_post(true, MESSAGE_SMALL_BLESSING_SETH, 0, 0);
                city_data.religion.mars_spirit_power = 10;
                break;
            case GOD_BAST:
                // throws a festival (?) in your honor
                city_message_post(true, MESSAGE_SMALL_BLESSING_BAST, 0, 0);
                city_sentiment_change_happiness(25);
                break;
        }
}
static void perform_blessing(int god) {
    if (GAME_ENV == ENGINE_ENV_C3)
        switch (god) {
            case GOD_OSIRIS:
                city_message_post(true, MESSAGE_BLESSING_FROM_CERES, 0, 0);
                building_bless_farms();
                break;
            case GOD_RA:
                city_message_post(true, MESSAGE_BLESSING_FROM_NEPTUNE, 0, 0);
                city_data.religion.neptune_double_trade_active = 1;
                break;
            case GOD_PTAH:
                city_message_post(true, MESSAGE_BLESSING_FROM_MERCURY, 0, 0);
                building_granary_bless();
                break;
            case GOD_SETH:
                city_message_post(true, MESSAGE_BLESSING_FROM_MARS, 0, 0);
                city_data.religion.mars_spirit_power = 10;
                break;
            case GOD_BAST:
                city_message_post(true, MESSAGE_BLESSING_FROM_VENUS, 0, 0);
                city_sentiment_change_happiness(25);
                break;
        }
    else if (GAME_ENV == ENGINE_ENV_PHARAOH)
        switch (god) {
            case GOD_OSIRIS:
                city_message_post(true, MESSAGE_BLESSING_OSIRIS, 0, 0);
                building_bless_farms();
                break;
            case GOD_RA:
                city_message_post(true, MESSAGE_BLESSING_RA, 0, 0);
                city_data.religion.neptune_double_trade_active = 1;
                break;
            case GOD_PTAH:
                city_message_post(true, MESSAGE_BLESSING_PTAH, 0, 0);
                building_granary_bless();
                break;
            case GOD_SETH:

                city_message_post(true, MESSAGE_BLESSING_SETH, 0, 0);
                city_data.religion.mars_spirit_power = 10;
                break;
            case GOD_BAST:
                // fills houses and bazaars
                city_message_post(true, MESSAGE_BLESSING_BAST, 0, 0);
                city_sentiment_change_happiness(25);
                break;
        }
}
static void perform_small_curse(int god) {
    if (GAME_ENV == ENGINE_ENV_C3)
        switch (god) {
            case GOD_OSIRIS:
                city_message_post(true, MESSAGE_CERES_IS_UPSET, 0, 0);
                building_curse_farms(0);
                break;
            case GOD_RA:
                city_message_post(true, MESSAGE_NEPTUNE_IS_UPSET, 0, 0);
                figure_sink_all_ships();
                city_data.religion.neptune_sank_ships = 1;
                break;
            case GOD_PTAH:
                city_message_post(true, MESSAGE_MERCURY_IS_UPSET, 0, 0);
                building_granary_warehouse_curse(0);
                break;
            case GOD_SETH:
                if (scenario_invasion_start_from_mars())
                    city_message_post(true, MESSAGE_MARS_IS_UPSET, 0, 0);
                else
                    city_message_post(true, MESSAGE_WRATH_OF_MARS_NO_MILITARY, 0, 0);
                break;
            case GOD_BAST:
                city_message_post(true, MESSAGE_VENUS_IS_UPSET, 0, 0);
                city_sentiment_set_max_happiness(50);
                city_sentiment_change_happiness(-5);
                city_health_change(-10);
                city_sentiment_update();
                break;
        }
    else if (GAME_ENV == ENGINE_ENV_PHARAOH)
        switch (god) {
            case GOD_OSIRIS:
                // flood destroys farms
                city_message_post(true, MESSAGE_SMALL_CURSE_OSIRIS, 0, 0);
                building_curse_farms(0);
                break;
            case GOD_RA:
                // lowers reputation
                city_message_post(true, MESSAGE_SMALL_CURSE_RA_1, 0, 0);
                return;

                // lowers amount of traded goods
                city_message_post(true, MESSAGE_SMALL_CURSE_RA_2, 0, 0);

                break;
            case GOD_PTAH:
                // destroys random storage yard
                city_message_post(true, MESSAGE_SMALL_CURSE_PTAH, 0, 0);
                building_granary_warehouse_curse(0);
                break;
            case GOD_SETH:
                // destroys a fort
                if (formation_legion_curse())
                    city_message_post(true, MESSAGE_SMALL_CURSE_SETH, 0, 0);
                else
                    city_message_post(true, MESSAGE_CURSE_SETH_NOEFFECT, 0, 0);
                break;
            case GOD_BAST:
                // plague
                city_message_post(true, MESSAGE_SMALL_CURSE_BAST, 0, 0);
                city_sentiment_set_max_happiness(50);
                city_sentiment_change_happiness(-5);
                city_health_change(-10);
                city_sentiment_update();
                break;
        }
}
static int perform_large_curse(int god) {
    if (GAME_ENV == ENGINE_ENV_C3)
        switch (god) {
            case GOD_OSIRIS:
                city_message_post(true, MESSAGE_WRATH_OF_CERES, 0, 0);
                building_curse_farms(1);
                break;
            case GOD_RA:
                if (city_data.trade.num_sea_routes <= 0) {
                    city_message_post(true, MESSAGE_WRATH_OF_NEPTUNE_NO_SEA_TRADE, 0, 0);
                    return 0;
                } else {
                    city_message_post(true, MESSAGE_WRATH_OF_NEPTUNE, 0, 0);
                    figure_sink_all_ships();
                    city_data.religion.neptune_sank_ships = 1;
                    city_trade_start_sea_trade_problems(80);
                }
                break;
            case GOD_PTAH:
                city_message_post(true, MESSAGE_WRATH_OF_MERCURY, 0, 0);
                building_granary_warehouse_curse(1);
                break;
            case GOD_SETH:
                if (formation_legion_curse()) {
                    city_message_post(true, MESSAGE_WRATH_OF_MARS, 0, 0);
                    scenario_invasion_start_from_mars();
                } else {
                    city_message_post(true, MESSAGE_WRATH_OF_MARS_NO_MILITARY, 0, 0);
                }
                break;
            case GOD_BAST:
                city_message_post(true, MESSAGE_WRATH_OF_VENUS, 0, 0);
                city_sentiment_set_max_happiness(40);
                city_sentiment_change_happiness(-10);
                if (city_data.health.value >= 80)
                    city_health_change(-50);
                else if (city_data.health.value >= 60)
                    city_health_change(-40);
                else {
                    city_health_change(-20);
                }
                city_data.religion.venus_curse_active = 1;
                city_sentiment_update();
                break;
        }
    else if (GAME_ENV == ENGINE_ENV_PHARAOH)
        switch (god) {
            case GOD_OSIRIS:

                // bad floods wawrning if not corrected
                city_message_post(true, MESSAGE_CURSE_OSIRIS_1, 0, 0);
                return 0;

                // locusts
                city_message_post(true, MESSAGE_CURSE_OSIRIS_2, 0, 0);
                building_curse_farms(1);
                break;
            case GOD_RA:

                // lowers reputation
                city_message_post(true, MESSAGE_CURSE_RA_1, 0, 0);
                return 0;

                // lowers commerce prices
                city_message_post(true, MESSAGE_CURSE_RA_2, 0, 0);

                // no trading ships/caravans for one year
                city_message_post(true, MESSAGE_CURSE_RA_3, 0, 0);

//                if (city_data.trade.num_sea_routes <= 0) {
//                    city_message_post(true, MESSAGE_WRATH_OF_NEPTUNE_NO_SEA_TRADE, 0, 0);
//                    return 0;
//                } else {
//                    city_message_post(true, MESSAGE_CURSE_RA_3, 0, 0);
//                    figure_sink_all_ships();
//                    city_data.religion.neptune_sank_ships = 1;
//                    city_trade_start_sea_trade_problems(80);
//                }
                break;
            case GOD_PTAH:
                city_message_post(true, MESSAGE_CURSE_PTAH_1, 0, 0);
                building_granary_warehouse_curse(1);
                break;
            case GOD_SETH:

                // destroys all ships
                city_message_post(true, MESSAGE_CURSE_SETH_1, 0, 0);
//                figure_sink_all_ships();
//                city_data.religion.neptune_sank_ships = 1;
                return 0;

                // hailstorm (random killing?)
                city_message_post(true, MESSAGE_CURSE_SETH_2, 0, 0);

//                if (formation_legion_curse()) {
//                    city_message_post(true, MESSAGE_CURSE_SETH_1, 0, 0);
//                    scenario_invasion_start_from_mars();
//                } else {
//                    city_message_post(true, MESSAGE_CURSE_SETH_NOEFFECT, 0, 0);
//                    return 0;
//                }
                break;
            case GOD_BAST:
                city_message_post(true, MESSAGE_CURSE_BAST_1, 0, 0);
                city_sentiment_set_max_happiness(40);
                city_sentiment_change_happiness(-10);
                if (city_data.health.value >= 80)
                    city_health_change(-50);
                else if (city_data.health.value >= 60)
                    city_health_change(-40);
                else
                    city_health_change(-20);
                city_data.religion.venus_curse_active = 1;
                city_sentiment_update();
                break;
        }
    return 1;
}

static void update_god_moods(void) {
    for (int i = 0; i < MAX_GODS; i++) {
        if (is_god_known(i) != GOD_STATUS_UNKNOWN) {
            god_status *god = &city_data.religion.gods[i];
            if (god->mood < god->target_mood)
                god->mood++;
            else if (god->mood > god->target_mood)
                god->mood--;
            if (scenario_is_mission_rank(1)) {
                if (god->mood < 50)
                    god->mood = 50;
            }
            if (god->mood > 50)
                god->small_curse_done = 0;
            if (god->mood < 50)
                god->blessing_done = 0;
        }
    }

    // update anger/happiness/bolt icons/etc.
    int difficulty = setting_difficulty();
    int randm_god = anti_scum_random_uint16() % 5;
    if (is_god_known(randm_god) != GOD_STATUS_UNKNOWN) { // OG code checks "randm_god < MAX_GODS" which is redundant.
        god_status *god = &city_data.religion.gods[randm_god];
        if (god->mood > 50)
            god->wrath_bolts = 0;

        if (god->mood <= 10)
            god->wrath_bolts += ((int[]){1, 1, 2, 4, 5})[difficulty];
        if (god->mood <= 20)
            god->wrath_bolts += ((int[]){0, 1, 1, 2, 3})[difficulty];;
        if (god->mood <= 30)
            god->wrath_bolts += ((int[]){0, 0, 0, 1, 2})[difficulty];;

        if (god->wrath_bolts > 50)
            god->wrath_bolts = 50;

        if (god->mood < 50)
            god->happy_ankhs = 0;

        if (god->mood >= 70)
            god->happy_ankhs += ((int[]){6, 4, 2, 1, 1})[difficulty];;
        if (god->mood >= 80)
            god->happy_ankhs += ((int[]){3, 2, 1, 1, 0})[difficulty];;
        if (god->mood >= 90)
            god->happy_ankhs += ((int[]){2, 1, 0, 0, 0})[difficulty];;

        if (god->happy_ankhs > 50)
            god->happy_ankhs = 50;
    }
    if (game_time_day() != 0)
        return;

    // handle blessings, curses, etc every month
    for (int i = 0; i < MAX_GODS; i++) {
        if (is_god_known(i) != GOD_STATUS_UNKNOWN)
            city_data.religion.gods[i].months_since_festival++;
    }
    if (randm_god >= MAX_GODS) {
        if (city_gods_calculate_least_happy())
            randm_god = city_data.religion.least_happy_god - 1;
    }
    if (!setting_gods_enabled())
        return;
    if (randm_god < MAX_GODS) {
        god_status *god = &city_data.religion.gods[randm_god];
        if (god->mood >= 100 && !god->blessing_done) {
            god->blessing_done = 1;
            perform_blessing(randm_god);
        } else if (god->wrath_bolts >= 20 && !god->small_curse_done && god->months_since_festival > 3) {
            god->small_curse_done = 1;
            god->wrath_bolts = 0;
            god->mood += 12;
            perform_small_curse(randm_god);
        } else if (god->wrath_bolts >= 50 && god->months_since_festival > 3) {
            if (scenario_campaign_rank() < 4 && !scenario_is_custom()) {
                // no large curses in early scenarios
                god->small_curse_done = 0;
                return;
            }
            god->wrath_bolts = 0;
            god->mood += 30;
            if (!perform_large_curse(randm_god))
                return;
        }
    }

    int min_happiness = 100;
    for (int i = 0; i < MAX_GODS; i++) {
        if (is_god_known(i) != GOD_STATUS_UNKNOWN) {
            if (city_data.religion.gods[i].mood < min_happiness)
                min_happiness = city_data.religion.gods[i].mood;
        }
    }
    if (city_data.religion.angry_message_delay)
        city_data.religion.angry_message_delay--;
    else if (min_happiness < 30) {
        city_data.religion.angry_message_delay = 20;
        if (min_happiness < 10)
            city_message_post(false, MESSAGE_GODS_WRATHFUL, 0, 0);
        else if (GAME_ENV == ENGINE_ENV_C3)
            city_message_post(false, MESSAGE_GODS_UNHAPPY, 0, 0);
    }
}

int is_god_known(int god) {
    return city_data.religion.gods[god].is_known;
}

void city_gods_calculate_moods(bool update_moods) {
    // base happiness: percentage of houses covered
    for (int i = 0; i < MAX_GODS; i++)
        city_data.religion.gods[i].target_mood = city_culture_coverage_religion(i);

    int max_temples = 0;
    int max_god = TIE;
    int min_temples = 100000;
    int min_god = TIE;
    for (int i = 0; i < MAX_GODS; i++) {
        if (is_god_known(i) == GOD_STATUS_UNKNOWN)
            break;
        int num_temples = 0;
        switch (i) {
            case GOD_OSIRIS:
                num_temples = building_count_total(BUILDING_TEMPLE_OSIRIS) +
                              building_count_total(BUILDING_TEMPLE_COMPLEX_OSIRIS);
                break;
            case GOD_RA:
                num_temples = building_count_total(BUILDING_TEMPLE_RA) +
                              building_count_total(BUILDING_TEMPLE_COMPLEX_RA);
                break;
            case GOD_PTAH:
                num_temples = building_count_total(BUILDING_TEMPLE_PTAH) +
                              building_count_total(BUILDING_TEMPLE_COMPLEX_PTAH);
                break;
            case GOD_SETH:
                num_temples = building_count_total(BUILDING_TEMPLE_SETH) +
                              building_count_total(BUILDING_TEMPLE_COMPLEX_SETH);
                break;
            case GOD_BAST:
                num_temples = building_count_total(BUILDING_TEMPLE_BAST) +
                              building_count_total(BUILDING_TEMPLE_COMPLEX_BAST);
                break;
        }
        if (num_temples == max_temples)
            max_god = TIE;
        else if (num_temples > max_temples) {
            max_temples = num_temples;
            max_god = i;
        }
        if (num_temples == min_temples)
            min_god = TIE;
        else if (num_temples < min_temples) {
            min_temples = num_temples;
            min_god = i;
        }
    }
    // happiness factor based on months since festival (max 40)
    for (int i = 0; i < MAX_GODS; i++) {
        if (is_god_known(i) == GOD_STATUS_UNKNOWN)
            break;
        int festival_penalty = city_data.religion.gods[i].months_since_festival;
        if (festival_penalty > 40)
            festival_penalty = 40;

        city_data.religion.gods[i].target_mood = calc_bound(city_data.religion.gods[i].target_mood + 12 - festival_penalty, 0, 100);
    }

//    if (!(config_get(CONFIG_GP_CH_JEALOUS_GODS))) {
//        if (max_god < MAX_GODS) {
//            if (city_data.religion.gods[max_god].target_mood >= 50)
//                city_data.religion.gods[max_god].target_mood = 100;
//            else
//                city_data.religion.gods[max_god].target_mood += 50;
//        }
//        if (min_god < MAX_GODS)
//            city_data.religion.gods[min_god].target_mood -= 25;
//    }

    int points = calc_bound((city_data.population.population - 350) / 50, 0, 5);
    int min_mood = 50 - 10 * points;
    int max_mood = 50 + 10 * points;

    for (int i = 0; i < MAX_GODS; i++)
        city_data.religion.gods[i].target_mood = calc_bound(city_data.religion.gods[i].target_mood, min_mood, max_mood);
    if (update_moods)
        update_god_moods();
}
int city_gods_calculate_least_happy(void) {
    int max_god = 0;
    int max_wrath = 0;
    // first, check who's the most enraged (number of bolts)
    for (int i = 0; i < MAX_GODS; i++) {
        if (is_god_known(i) == GOD_STATUS_UNKNOWN)
            break;
        if (city_data.religion.gods[i].wrath_bolts > max_wrath) {
            max_god = i + 1;
            max_wrath = city_data.religion.gods[i].wrath_bolts;
        }
    }
    if (max_god > 0) {
        city_data.religion.least_happy_god = max_god;
        return 1;
    }
    int min_happiness = 40;
    // lastly, check who's the least happy
    for (int i = 0; i < MAX_GODS; i++) {
        if (is_god_known(i) == GOD_STATUS_UNKNOWN)
            break;
        if (city_data.religion.gods[i].mood < min_happiness) {
            max_god = i + 1;
            min_happiness = city_data.religion.gods[i].mood;
        }
    }
    city_data.religion.least_happy_god = max_god;
    return max_god > 0;
}
int city_god_happiness(int god_id) {
    return city_data.religion.gods[god_id].mood;
}
int city_god_wrath_bolts(int god_id) {
    return city_data.religion.gods[god_id].wrath_bolts;
}
int city_god_happy_angels(int god_id) {
    return city_data.religion.gods[god_id].happy_ankhs;
}
int city_god_months_since_festival(int god_id) {
    return city_data.religion.gods[god_id].months_since_festival;
}
int city_god_least_happy(void) {
    return city_data.religion.least_happy_god - 1;
}

int city_god_spirit_of_mars_power(void) {
    return city_data.religion.mars_spirit_power;
}
void city_god_spirit_of_mars_mark_used(void) {
    city_data.religion.mars_spirit_power = 0;
}
int city_god_neptune_create_shipwreck_flotsam(void) {
    if (city_data.religion.neptune_sank_ships) {
        city_data.religion.neptune_sank_ships = 0;
        return 1;
    } else {
        return 0;
    }
}

void city_god_blessing_cheat(int god_id) {
    perform_blessing(god_id);
}
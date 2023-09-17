#include "gods.h"

#include "building/count.h"
#include "building/destruction.h"
#include "building/granary.h"
#include "building/industry.h"
#include "building/storage_yard.h"
#include "city/coverage.h"
#include "city/data_private.h"
#include "city/health.h"
#include "city/message.h"
#include "city/sentiment.h"
#include "city/trade.h"
#include "core/profiler.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/formation_legion.h"
#include "figuretype/water.h"
#include "floods.h"
#include "game/settings.h"
#include "game/tutorial.h"
#include "game/time.h"
#include "grid/routing/routing_terrain.h"
#include "config/config.h"
#include "ratings.h"
#include "scenario/invasion.h"
#include "scenario/property.h"
#include "sound/effect.h"

#include <algorithm>
#include <array>

void city_gods_reset() {
    for (auto &god: city_data.religion.gods) {
        god.type = e_god(std::distance(city_data.religion.gods, &god));
        god.target_mood = 50;
        god.mood = 50;
        god.wrath_bolts = 0;
        god.blessing_done = false;
        god.curse_done = false;
        god.unused1 = 0;
        god.unused2 = 0;
        god.unused3 = 0;
        god.months_since_festival = 0;
        god.is_known = GOD_STATUS_UNKNOWN;
    }

    city_data.religion.angry_message_delay = 0;
}

svector<god_state*, MAX_GODS> city_gods_knowns() {
    svector<god_state*, MAX_GODS> gods;
    for (int i = 0; i < MAX_GODS; i++) {
        if (city_gods_is_known((e_god)i) != GOD_STATUS_UNKNOWN) {
            gods.push_back(&city_data.religion.gods[i]);
        }
    }
    return gods;
}

e_god_status city_gods_is_known(e_god god) {
    return city_data.religion.gods[god].is_known;
}

static bool OSIRIS_locusts() {
    // TODO
    return 0;
}

static bool PTAH_warehouse_restock() {
    // fill warehouses with gems, clay, pottery, flax, linen, or jewelry
    e_resource resources[6] = {RESOURCE_GEMS, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS};

    building* chosen_yard = nullptr;
    int lowest_stock_found = 10000;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID) {
            continue;
        }
        
        if (b->type != BUILDING_STORAGE_YARD && b->type != 193) {
            continue;
        }
        
        int total_stored = 0;
        for (int j = 0; j < 6; ++j)
            total_stored += building_storageyard_get_amount(b, resources[j]);
        if (total_stored > 0 && total_stored < lowest_stock_found) {
            lowest_stock_found = total_stored;
            chosen_yard = b;
        }
    }

    e_resource chosen_resource = RESOURCE_NONE;
    int lowest_resource_found = 10000;
    if (lowest_stock_found > 0 && chosen_yard != nullptr) {
        for (int i = 0; i < 6; ++i) {
            int stored = building_storageyard_get_amount(chosen_yard, resources[i]);
            if (stored > 0 && stored < lowest_resource_found) {
                lowest_resource_found = stored;
                chosen_resource = resources[i];
            }
        }
        if (chosen_resource > 0) {
            building_storageyard_add_resource(chosen_yard, chosen_resource, 999999); // because I'm lazy.
            if (building_storageyard_get_amount(chosen_yard, chosen_resource) == lowest_resource_found)
                return false;
            else
                return true;
        }
    }

    return false;
}

static bool PTAH_industry_restock() {
    // restocks shipwrights, weavers and jewelers
    int industries[3] = {BUILDING_SHIPYARD, BUILDING_LINEN_WORKSHOP, BUILDING_JEWELS_WORKSHOP};
    int industry_resource[3] = {-1, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS};

    // search for industries
    int industries_found = 0;
    for (int i = 0; i < 6; ++i) {
        if (building_count_total(industries[i]) > 0
            || (industry_resource[i] != -1 && building_count_industry_active(industry_resource[i]) > 0)) {
            industries_found++;
        } else {
            industries[i] = 0;
        }
    }
    if (industries_found == 0)
        return false;

    int randm = anti_scum_random_15bit() % industries_found;
    int industry = 0;

    for (int i = 0; i < 3; ++i) {
        if (industries[i] > 0) {
            if (industry++ == randm) {
                for (int j = 1; j < MAX_BUILDINGS; j++) {
                    building* b = building_get(j);
                    if (b->state != BUILDING_STATE_VALID || b->type != industries[i])
                        continue;

                    b->stored_full_amount = std::clamp<short>(b->stored_full_amount, 200, 9999);
                }
                return true;
            }
        }
    }
    return false;
}
static bool PTAH_warehouse_destruction() {
    // destroy the "best" warehouse found (most stocked up)
    int max_stored = 0;
    building* max_building = nullptr;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_STORAGE_YARD)
            continue;

        int total_stored = 0;
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; r = (e_resource)(r + 1))
            total_stored += building_storageyard_get_amount(b, r);

        if (total_stored > max_stored) {
            max_stored = total_stored;
            max_building = b;
        }
    }
    if (max_building == nullptr)
        return false;
    //    city_message_disable_sound_for_next_message();
    //    city_message_post(false, MESSAGE_FIRE, max_building->type, max_building->tile.grid_offset());
    building_destroy_by_fire(max_building);
    map_routing_update_land();
    return true;
}

static bool PTAH_industry_destruction() {
    // destroys random industry, if found
    int industries[6] = {BUILDING_GOLD_MINE, BUILDING_GEMSTONE_MINE, BUILDING_CLAY_PIT, BUILDING_SHIPYARD, BUILDING_LINEN_WORKSHOP, BUILDING_JEWELS_WORKSHOP};
    int industry_resource[6] = {RESOURCE_GOLD, RESOURCE_GEMS, RESOURCE_CLAY, -1, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS};

    // search for industries
    int industries_found = 0;
    for (int i = 0; i < 6; ++i) {
        if (building_count_total(industries[i]) > 0
            || (industry_resource[i] != -1 && building_count_industry_active(industry_resource[i]) > 0)) {
            industries_found++;
        } else {
            industries[i] = 0;
        }
    }

    if (industries_found == 0) {
        return false;
    }

    int randm = anti_scum_random_15bit() % industries_found;
    int industry = 0;
    for (int i = 0; i < 6; ++i) {
        if (industries[i] > 0) {
            if (industry++ == randm) {
                for (int j = 1; j < MAX_BUILDINGS; j++) {
                    building* b = building_get(j);
                    if (b->state != BUILDING_STATE_VALID)
                        continue;

                    if (b->type == industries[i]) {
                        building_destroy_by_fire(b);
                        //                        FUN_0046cf10((int)building_id,0);
                        //                        FUN_004693e0(building_id,1);
                    }
                }
                //                FUN_0053adb0(0x11);
                //                FUN_00517090();
                //                FUN_00517380();
                map_routing_update_land();
                return true;
            }
        }
    }
    return false;
}

static bool SETH_fort_destruction() {
    // TODO
    //            formation_legion_curse();
    return 0;
}
static bool SETH_ships_destruction() {
    // TODO
    //                figure_sink_all_ships();
    //                city_data.religion.neptune_sank_ships = 1;
    return 0;
}
static bool SETH_hailstorm() {
    // TODO
    //                if (formation_legion_curse()) {
    //                    city_message_post(true, MESSAGE_CURSE_SETH_1, 0, 0);
    //                    scenario_invasion_start_from_mars();
    //                } else {
    //                    city_message_post(true, MESSAGE_CURSE_SETH_NOEFFECT, 0, 0);
    //                    return 0;
    //                }
    return 0;
}

static bool PTAH_frogs() {
    // TODO
    return 0;
}

static bool BAST_refill_houses_and_bazaar() {
    // TODO
    //            city_sentiment_change_happiness(25);
    // TODO
    //            city_sentiment_set_max_happiness(40);
    //            city_sentiment_change_happiness(-10);
    //            if (city_data.health.value >= 80)
    //                city_health_change(-50);
    //            else if (city_data.health.value >= 60)
    //                city_health_change(-40);
    //            else
    //                city_health_change(-20);
    //            city_data.religion.venus_curse_active = true;
    //            city_sentiment_update();
    return 0;
}

static int compare(int A, int B) {
    auto hA = building_get(A)->subtype.house_level;
    auto hB = building_get(B)->subtype.house_level;

    if (hA < hB)
        return -1;
    else if (hA > hB)
        return 1;

    return 0;
}
static void rearrange_CHILD(int arr[20], int first, int last) {
    if (first >= last)
        return;

    int A, B;
    while (first < last) {
        A = first;
        B = first + 1;

        while (B <= last) {
            if (compare(arr[B], arr[A]) > 0) // A is more evolved
                A = B;
            B++;
        }
        std::swap(arr[A], arr[last]);
        last--;
    }
}

static void rearrange_dark_magic(int arr[20]) {
    auto DBG = (int(*)[20])arr;

    int cache_first[30];
    int cache_last[30];
    int j = 0;

    int first = 0;
    int last = 19;

    int A, B;
    int size;

REDO:
    size = last - first + 1; // starts with 20
    if (size > 8) {
        std::swap(arr[first], arr[size / 2]);

        A = first;
        B = last + 1;

        while (true) {
            // finds the first house better than than the one at the top!
            do {
                A++;
                if (A > last)
                    break;
            } while (compare(arr[A], arr[first]) < 1);

            // finds the last house worse than the one at the top!
            do {
                B--;
                if (B <= first)
                    break;
            } while (compare(arr[B], arr[first]) > -1);

            if (A > B)
                break;
            else // continue the loop
                std::swap(arr[A], arr[B]);
        }

        std::swap(arr[first], arr[B]);
        if (B - 1 - first < last - A) {
            if (A < last) {
                cache_first[j] = A;
                cache_last[j] = last;
                j++;
            }
            if (first + 1 < B) {
                last = B - 1;
                goto REDO;
            }
        } else {
            if (first + 1 < B) {
                cache_first[j] = first;
                cache_last[j] = B - 1;
                j++;
            }

            if (A < last) {
                first = A;
                goto REDO;
            }
        }
    } else {
        rearrange_CHILD(arr, first, last);
    }

    j--;
    if (j < 0)
        return;
    first = cache_first[j];
    last = cache_last[j];
    goto REDO;
}

static bool BAST_houses_destruction() {
    int houses[20] = {0};
    int houses_found = 0;
    // first, find the first 20 houses
    for (int i = 1; i < MAX_BUILDINGS; ++i) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || !building_is_house(b->type))
            continue;
        if (houses_found < 20)
            houses[houses_found++] = i; // add to the list
        else
            break; // found 20 houses, job done!
    }

    if (houses_found > 19) {
        rearrange_dark_magic(houses); // ???????????????
                                      //        FUN_00561c09(houses_array,20,4,&LAB_004c42d0);
        for (int i = 20; i < MAX_BUILDINGS; ++i) {
            building* b = building_get(i);
            if (b->state != BUILDING_STATE_VALID || !building_is_house(b->type))
                continue;
            int this_house_level = b->subtype.house_level;
            int last_house_level = building_get(houses[19])->subtype.house_level;
            if (this_house_level > last_house_level) { // found house more evolved than the initial 20 houses

                // where to stuff this new house? find the appropriate spot index
                for (int j = 0; j < 20; ++j) {
                    if (building_get(houses[j])->subtype.house_level < this_house_level) {
                        // found a spot! the next in the list is an inferior house -- shift all the
                        // items in the list from this point onward down ONE SLOT, and insert here.
                        for (int k = 19; k > j; --k)
                            houses[k] = houses[k - 1]; // copy from above slot
                        houses[j] = i;                 // assign the new building to the original slot
                        break;
                    }
                }
            }
            // didn't find any better houses, OR we filled the 20 houses completely AGAIN
        }
    }

    if (houses_found > 0) {
        for (int i = 0; i < houses_found; ++i) {
            if (houses[i] != 0)
                building_destroy_by_fire(building_get(houses[i]));
        }
        map_routing_update_land();
        return true;
    }
    return false;
}

static bool BAST_malaria_plague() {
    // TODO
    //            city_sentiment_set_max_happiness(50);
    //            city_sentiment_change_happiness(-5);
    //            city_health_change(-10);
    //            city_sentiment_update();
    return 0;
}

static void perform_major_blessing(e_god god) {
    bool success = false;
    switch (god) {
    case GOD_OSIRIS:
        if (anti_scum_random_bool()) {
            // double farm yields
            city_data.religion.osiris_double_farm_yield = true;
            city_message_god_post(GOD_OSIRIS, true, MESSAGE_BLESSING_OSIRIS_FARMS, 0, 0);
            return;
        } else {
            // better next flood quality
            floodplains_adjust_next_quality((anti_scum_random_15bit() % 3 * 5 + 10) * 2);
            city_message_god_post(GOD_OSIRIS, true, MESSAGE_BLESSING_OSIRIS_FLOOD, 0, 0);
            return;
        }
        break;

    case GOD_RA:
        if (anti_scum_random_bool()) {
            // exports sell for 150% profits for the next 12 months
            city_data.religion.ra_150_export_profits_months_left = 12;
            city_message_god_post(GOD_RA, true, MESSAGE_BLESSING_RA_EXPORTS, 0, 0);
            return;
        } else {
            // increased kingdom by 15
            city_ratings_change_kingdom(15);
            city_message_god_post(GOD_RA, true, MESSAGE_BLESSING_RA_KINGDOM, 0, 0);
            return;
        }
        break;

    case GOD_PTAH:
        // gems, clay, pottery, flax, linen, or jewelry in storage yards
        success = PTAH_warehouse_restock();
        if (success)
            city_message_god_post(GOD_PTAH, true, MESSAGE_BLESSING_PTAH, 0, 0);
        else // no yard with such goods (and space) found
            city_message_god_post(GOD_PTAH, true, MESSAGE_BLESSING_PTAH_NOEFFECT, 0, 0);
        return;

    case GOD_SETH:
        city_data.religion.seth_crush_enemy_troops = 10;
        city_message_god_post(GOD_SETH, true, MESSAGE_BLESSING_SETH, 0, 0);
        return;

    case GOD_BAST:
        // fills houses and bazaars
        BAST_refill_houses_and_bazaar();
        city_message_god_post(GOD_BAST, true, MESSAGE_BLESSING_BAST, 0, 0);
        return;
    }
}

static void perform_minor_blessing(int god) {
    int randm = 0;
    switch (god) {
    case GOD_OSIRIS:
        // slightly better flood
        randm = anti_scum_random_15bit();
        randm = randm & 0x80000003;
        if ((int)randm < 0)
            randm = (randm - 1 | 0xfffffffc) + 1;
        floodplains_adjust_next_quality(randm * 5 + 5);
        city_message_post(true, MESSAGE_SMALL_BLESSING_OSIRIS, 0, 0);
        break;

    case GOD_RA:
        if (anti_scum_random_bool()) {
            // slightly increased trading
            city_data.religion.ra_slightly_increased_trading_months_left = 12;
            city_message_post(true, MESSAGE_SMALL_BLESSING_RA_2, 0, 0);
            return;
        } else {
            // slightly increased reputation
            city_message_post(true, MESSAGE_SMALL_BLESSING_RA_1, 0, 0);
            city_ratings_change_kingdom(5);
            return;
        }
        break;

    case GOD_PTAH:
        // restocks shipwrights, weavers and jewelers
        PTAH_industry_restock(); // <-- there is no message for when this fails.
        city_message_post(true, MESSAGE_SMALL_BLESSING_PTAH, 0, 0);
        return;

    case GOD_SETH:
        // protects soldiers far away
        city_data.religion.seth_protect_player_troops = 10;
        city_message_post(true, MESSAGE_SMALL_BLESSING_SETH, 0, 0);
        return;

    case GOD_BAST:
        // throws a festival for the other gods
        city_data.festival.planned.god = GOD_OSIRIS;
        city_data.festival.planned.size = FESTIVAL_BAST_SPECIAL;
        city_data.festival.planned.months_to_go = 1;
        city_data.festival.first_festival_effect_months = 1;

        city_data.religion.gods[GOD_RA].months_since_festival = 0;
        city_data.religion.gods[GOD_PTAH].months_since_festival = 0;
        city_data.religion.gods[GOD_SETH].months_since_festival = 0;
        city_message_post(true, MESSAGE_SMALL_BLESSING_BAST, 0, 0);
        return;
    }
}

static void perform_major_curse(int god) {
    bool success = false;
    switch (god) {
    case GOD_OSIRIS:
        if (anti_scum_random_bool()) {
            // worse flood quality
            floodplains_adjust_next_quality((-2 - anti_scum_random_15bit() % 3) * 10);
            city_message_post(true, MESSAGE_CURSE_OSIRIS_1, 0, 0);
            return;
        } else {
            // locusts
            OSIRIS_locusts();
            city_message_post(true, MESSAGE_CURSE_OSIRIS_2, 0, 0);
            return;
        }
        break;

    case GOD_RA:
        if (anti_scum_random_15bit() % 3 == 0) {
            // lowers commerce prices
            city_data.religion.ra_harshly_reduced_trading_months_left = 12;
            city_message_post(true, MESSAGE_CURSE_RA_2, 0, 0);
            return;
        }

        if (anti_scum_random_15bit() % 3 == 1) {
            // lowers reputation
            city_ratings_change_kingdom(-15);
            city_message_post(true, MESSAGE_CURSE_RA_1, 0, 0);
            return;
        }
        // no trading ships/caravans for one year
        city_data.religion.ra_no_traders_months_left = 12;
        city_message_post(true, MESSAGE_CURSE_RA_3, 0, 0);
        return;

    case GOD_PTAH:
        if (anti_scum_random_bool()) {
            // destroys some industrial buildings
            success = PTAH_industry_destruction();
            if (success)
                city_message_post(true, MESSAGE_CURSE_PTAH_1, 0, 0);
            else // no yard found
                city_message_post(true, MESSAGE_CURSE_PTAH_NOEFFECT, 0, 0);
            return;
        } else {
            // frogs
            PTAH_frogs();
            city_message_post(true, MESSAGE_CURSE_PTAH_2, 0, 0);
            return;
        }
        break;

    case GOD_SETH:
        if (anti_scum_random_bool()) {
            // destroys all ships
            SETH_ships_destruction();
            city_message_post(true, MESSAGE_CURSE_SETH_1, 0, 0);
            return;
        } else {
            SETH_hailstorm();
            city_message_post(true, MESSAGE_CURSE_SETH_2, 0, 0);
            return;
        }
        break;

    case GOD_BAST:
        // destroy some of the best houses
        BAST_houses_destruction();
        city_message_post(true, MESSAGE_CURSE_BAST_1, 0, 0);
        return;
    }
}

static void perform_minor_curse(e_god god) {
    bool success = false;
    switch (god) {
    case GOD_OSIRIS:
        if (anti_scum_random_bool()) {
            // next flood will destroys farms
            city_data.religion.osiris_flood_will_destroy_active = 1;
            city_message_god_post(GOD_OSIRIS, true, MESSAGE_SMALL_CURSE_OSIRIS, 0, 0);
            return;
        } else {
            // lower quality flood
            int randm = anti_scum_random_15bit();
            randm = randm & 0x80000003;
            if ((int)randm < 0) {
                randm = (randm - 1 | 0xfffffffc) + 1;
            }
            floodplains_adjust_next_quality((-1 - randm) * 5);
            city_message_god_post(GOD_OSIRIS, true, MESSAGE_SMALL_CURSE_OSIRIS, 0, 0);
            return;
        }
        break;

    case GOD_RA:
        if (anti_scum_random_bool()) {
            // lowers amount of traded goods
            city_data.religion.ra_slightly_reduced_trading_months_left = 12;
            city_message_god_post(GOD_RA, true, MESSAGE_SMALL_CURSE_RA_2, 0, 0);
            return;
        } else {
            // lowers reputation
            city_ratings_change_kingdom(-5);
            city_message_god_post(GOD_RA, true, MESSAGE_SMALL_CURSE_RA_1, 0, 0);
            return;
        }
        break;

    case GOD_PTAH:
        // destroys random storage yard
        success = PTAH_warehouse_destruction();
        if (success) {
            city_message_god_post(GOD_PTAH, true, MESSAGE_SMALL_CURSE_PTAH, 0, 0);
        } else { // no yard found 
            city_message_god_post(GOD_PTAH, true, MESSAGE_CURSE_PTAH_NOEFFECT, 0, 0);
        }
        return;

    case GOD_SETH:
        // destroys the best fort
        success = SETH_fort_destruction();
        if (success) {
            city_message_god_post(GOD_SETH, true, MESSAGE_SMALL_CURSE_SETH, 0, 0);
        } else {
            city_message_god_post(GOD_SETH, true, MESSAGE_CURSE_SETH_NOEFFECT, 0, 0);
        }
        break;

    case GOD_BAST:
        // plague
        BAST_malaria_plague();
        city_message_god_post(GOD_BAST, true, MESSAGE_SMALL_CURSE_BAST, 0, 0);
        break;
    }
}

void city_gods_update_curses_and_blessings(int randm_god, int FORCE_EVENT) {
    if (randm_god >= MAX_GODS) {
        if (city_gods_calculate_least_happy())
            randm_god = city_data.religion.least_happy_god - 1;
    }

    // perform curses/blessings
    if (randm_god < MAX_GODS) {
        god_state* god = &city_data.religion.gods[randm_god];

        if (FORCE_EVENT == GOD_EVENT_MAJOR_BLESSING
            || (FORCE_EVENT == -1 && god->happy_ankhs == 50 && god->months_since_festival < 15)) {
            /* ***** MAJOR BLESSINGS ***** */
            perform_major_blessing((e_god)randm_god);
            god->happy_ankhs = 0;
            god->mood = calc_bound(god->mood - 30, 0, 100);
        } else if (FORCE_EVENT == GOD_EVENT_MINOR_BLESSING
                   || (FORCE_EVENT == -1 && god->happy_ankhs > 19 && god->months_since_festival < 15)) {
            /* ***** MINOR BLESSINGS ***** */
            perform_minor_blessing(randm_god);
            god->happy_ankhs = 0;
            god->mood = calc_bound(god->mood - 12, 0, 100);
        } else if (FORCE_EVENT == GOD_EVENT_MAJOR_CURSE
                   || (FORCE_EVENT == -1 && god->wrath_bolts == 50 && god->months_since_festival > 3)) {
            /* ***** MAJOR CURSES ***** */
            perform_major_curse(randm_god);
            god->wrath_bolts = 0;
            god->mood = calc_bound(god->mood + 30, 0, 100);
        } else if (FORCE_EVENT == GOD_EVENT_MINOR_CURSE
                   || (FORCE_EVENT == -1 && god->wrath_bolts > 19 && god->months_since_festival > 3)) {
            /* ***** MINOR CURSES ***** */
            perform_minor_curse((e_god)randm_god);
            god->wrath_bolts = 0;
            god->mood = calc_bound(god->mood + 12, 0, 100);
        }
    }
}

static void calculate_mood_targets() {
    // fix god moods to 30 if campaign has not unlocked them yet
    // TODO: move this option to city_data.gods_available
    if (scenario_campaign_scenario_id() < 4) {
        for (auto *god: city_gods_knowns()) {
            god->target_mood = 30;
            god->mood = 30;
        }
        return;
    }

    // base happiness: percentage of houses covered
    for (auto *god: city_gods_knowns()) {
        god->target_mood = city_culture_coverage_religion(god->type);
    }

    int max_temples = 0;
    e_god max_god = GOD_UNKNOWN;
    int min_temples = 100000;
    e_god min_god = GOD_UNKNOWN;

    for (auto *god: city_gods_knowns()) {
        int num_temples = 0;
        switch (god->type) {
        case GOD_OSIRIS: num_temples = building_count_total(BUILDING_TEMPLE_OSIRIS) + building_count_total(BUILDING_TEMPLE_COMPLEX_OSIRIS); break;
        case GOD_RA: num_temples = building_count_total(BUILDING_TEMPLE_RA) + building_count_total(BUILDING_TEMPLE_COMPLEX_RA); break;
        case GOD_PTAH: num_temples = building_count_total(BUILDING_TEMPLE_PTAH) + building_count_total(BUILDING_TEMPLE_COMPLEX_PTAH); break;
        case GOD_SETH: num_temples = building_count_total(BUILDING_TEMPLE_SETH) + building_count_total(BUILDING_TEMPLE_COMPLEX_SETH); break;
        case GOD_BAST: num_temples = building_count_total(BUILDING_TEMPLE_BAST) + building_count_total(BUILDING_TEMPLE_COMPLEX_BAST); break;
        }

        if (num_temples == max_temples) {
            max_god = GOD_UNKNOWN;
        } else if (num_temples > max_temples) {
            max_temples = num_temples;
            max_god = god->type;
        }

        if (num_temples == min_temples) {
            min_god = GOD_UNKNOWN;
        } else if (num_temples < min_temples) {
            min_temples = num_temples;
            min_god = god->type;
        }
    }

    // happiness factor based on months since festival (max 40)
    for (auto *god: city_gods_knowns()) {
        int festival_penalty = god->months_since_festival;
        if (festival_penalty > 40)
            festival_penalty = 40;

        god->target_mood = calc_bound(god->target_mood + 12 - festival_penalty, 0, 100);
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

    for (auto *god: city_gods_knowns()) {
        god->target_mood = calc_bound(god->target_mood, min_mood, max_mood);
    }
}
static void update_moods(e_god randm_god) {

    for (auto *god: city_gods_knowns()) {
        if (god->mood < god->target_mood) {
            god->mood++;
        } else if (god->mood > god->target_mood) {
            god->mood--;
        }

        if (scenario_is_mission_rank(1)) {
            if (god->mood < 50)
                god->mood = 50;
        }

        if (god->mood > 50)
            god->curse_done = false;

        if (god->mood < 50)
            god->blessing_done = false;
    }

    // update anger/happiness/bolt icons/etc.
    int difficulty = setting_difficulty();
    if (city_gods_is_known(randm_god) != GOD_STATUS_UNKNOWN) { // OG code checks "randm_god < MAX_GODS" which is redundant.
        god_state* god = &city_data.religion.gods[randm_god];
        if (god->mood > 50)
            god->wrath_bolts = 0;

        if (god->mood <= 10) {
            int difficultyLevels[] = {1, 1, 2, 4, 5};
            god->wrath_bolts += difficultyLevels[difficulty];
        }
        if (god->mood <= 20) {
            int difficultyLevels[] = {0, 1, 1, 2, 3};
            god->wrath_bolts += difficultyLevels[difficulty];
            ;
        }
        if (god->mood <= 30) {
            int difficultyLevels[] = {0, 0, 0, 1, 2};
            god->wrath_bolts += difficultyLevels[difficulty];
            ;
        }

        if (god->wrath_bolts > 50)
            god->wrath_bolts = 50;

        if (god->mood < 50)
            god->happy_ankhs = 0;

        if (god->mood >= 70) {
            int difficultyLevels[] = {6, 4, 2, 1, 1};
            god->happy_ankhs += difficultyLevels[difficulty];
        }
        if (god->mood >= 80) {
            int difficultyLevels[] = {3, 2, 1, 1, 0};
            god->happy_ankhs += difficultyLevels[difficulty];
        }
        if (god->mood >= 90) {
            int difficultyLevels[] = {2, 1, 0, 0, 0};
            god->happy_ankhs += difficultyLevels[difficulty];
            ;
        }

        if (god->happy_ankhs > 50)
            god->happy_ankhs = 50;
    }
}

static void update_monthly_data(int randm_god) {
    // update festival counter
    for (auto *god: city_gods_knowns()) {
        god->months_since_festival++;
    }

    // handle blessings, curses, etc every month
    city_gods_update_curses_and_blessings(randm_god);

    // post city message about the gods being angery
    int min_happiness = 100;
    for (auto *god: city_gods_knowns()) {
        if (god->mood < min_happiness) {
           min_happiness = god->mood;
        }
    }

    if (city_data.religion.angry_message_delay > 0) {
        city_data.religion.angry_message_delay--;
    } else if (min_happiness < 30) { // message delay = 0 and there's a god with mood < 30
        city_data.religion.angry_message_delay = 20;
        if (min_happiness < 10)
            city_message_post(false, MESSAGE_GODS_WRATHFUL, 0, 0);

        //else if (GAME_ENV == ENGINE_ENV_C3)
        //    city_message_post(false, MESSAGE_GODS_UNHAPPY, 0, 0);
    }

    // update status effects with limited durations
    if (city_data.religion.ra_slightly_increased_trading_months_left != -1)
        city_data.religion.ra_slightly_increased_trading_months_left--;

    if (city_data.religion.ra_harshly_reduced_trading_months_left != -1)
        city_data.religion.ra_harshly_reduced_trading_months_left--;

    if (city_data.religion.ra_slightly_reduced_trading_months_left != -1)
        city_data.religion.ra_slightly_reduced_trading_months_left--;

    if (city_data.religion.ra_150_export_profits_months_left != -1)
        city_data.religion.ra_150_export_profits_months_left--;

    if (city_data.religion.ra_no_traders_months_left != -1)
        city_data.religion.ra_no_traders_months_left--;
}

void city_gods_update(bool mood_calc_only) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Gods Update");
    calculate_mood_targets();

    if (!mood_calc_only && setting_gods_enabled()) {
        e_god randm_god = e_god(anti_scum_random_15bit() % MAX_GODS);
        update_moods(randm_god);

        //        perform_minor_blessing(GOD_PTAH); // TODO: DEBUGGING
        //        BAST_houses_destruction();

        // at the start of every month
        if (game_time_day() == 0) {
            update_monthly_data(randm_god);
        }
    }
}

bool city_gods_calculate_least_happy(void) {
    e_god max_god = GOD_UNKNOWN;
    int max_wrath = 0;
    // first, check who's the most enraged (number of bolts)
    for (auto *god: city_gods_knowns()) {
        if (god->wrath_bolts > max_wrath) {
            max_god = god->type;
            max_wrath = god->wrath_bolts;
        }
    }

    if (max_god != GOD_UNKNOWN) {
        city_data.religion.least_happy_god = max_god;
        return true;
    }

    int min_happiness = 40;
    // lastly, check who's the least happy
    for (auto *god: city_gods_knowns()) {
        if (god->mood < min_happiness) {
            max_god = god->type;
            min_happiness = god->mood;
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

int city_god_spirit_of_seth_power(void) {
    return city_data.religion.seth_crush_enemy_troops;
}

void city_god_spirit_of_seth_mark_used(void) {
    city_data.religion.seth_crush_enemy_troops = 0;
}

int city_god_osiris_create_shipwreck_flotsam(void) {
    if (city_data.religion.osiris_sank_ships) {
        city_data.religion.osiris_sank_ships = 0;
        return 1;
    } else {
        return 0;
    }
}

void city_god_blessing_cheat(e_god god_id) {
    perform_major_blessing(god_id);
}

void city_god_upset_cheat(e_god god_id) {
    perform_minor_curse(god_id);
}
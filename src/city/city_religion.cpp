#include "city_religion.h"

#include "building/destruction.h"
#include "building/building_granary.h"
#include "building/building_storage_yard.h"
#include "building/building_house.h"
#include "city/coverage.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_health.h"
#include "city/city_message.h"
#include "core/profiler.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/formation_batalion.h"
#include "city_floods.h"
#include "game/settings.h"
#include "game/tutorial.h"
#include "grid/routing/routing_terrain.h"
#include "ratings.h"
#include "scenario/scenario_invasion.h"
#include "scenario/scenario.h"
#include "sound/effect.h"
#include "dev/debug.h"
#include "city/city_warnings.h"
#include "game/game.h"
#include "core/stable_array.h"
#include "js/js_game.h"

#include <algorithm>
#include <array>

e_god_tokens_t ANK_CONFIG_ENUM(e_god_tokens);

e_god find_god_id_from_name(const std::string& god_name) {    
    if (god_name == "osiris") return GOD_OSIRIS;
    if (god_name == "ra") return GOD_RA;
    if (god_name == "seth") return GOD_SETH;
    if (god_name == "bast") return GOD_BAST;
    if (god_name == "ptah") return GOD_PTAH;
    return GOD_UNKNOWN;
}

declare_console_command_p(god_minor_blessing) {
    std::string god_name; is >> god_name;
    e_god god = find_god_id_from_name(god_name);
    if (god != GOD_UNKNOWN) {
        g_city.religion.perform_minor_blessing(god);
        events::emit(event_city_warning{ "Cheated minor blessing" });
    }
}

declare_console_command_p(god_major_blessing) {
    std::string args; is >> args;
    int god_id = atoi(args.empty() ? (pcstr)"0" : args.c_str());
    g_city.religion.perform_major_blessing((e_god)god_id);

    events::emit(event_city_warning{ "Casted major upset" });
}

declare_console_command_p(god_minor_curse) {
    std::string args; is >> args;
    int god_id = atoi(args.empty() ? (pcstr)"0" : args.c_str());
    g_city.religion.perform_minor_curse((e_god)god_id);

    events::emit(event_city_warning{ "Casted major upset" });
}

declare_console_command_p(god_major_curse) {
    std::string args; is >> args;
    int god_id = atoi(args.empty() ? (pcstr)"0" : args.c_str());
    g_city.religion.perform_major_curse((e_god)god_id);

    events::emit(event_city_warning{ "Casted upset" });
}

declare_console_command_p(ra_no_trade) {
    std::string args; is >> args;
    int nomonth = atoi(args.empty() ? (pcstr)"0" : args.c_str());

    g_city.religion.ra_no_traders_months_left = nomonth;
    g_city.religion.ra_harshly_reduced_trading_months_left = nomonth;
    g_warning_manager.show_console_var("Ra no month trade %d", nomonth);
}

stable_array<god_state::static_params_t> ANK_VARIABLE_N(gods_static_data, "gods");

void city_religion_t::reset() {
    for (auto &god: gods) {
        god.type = e_god(std::distance(gods, &god));
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

    angry_message_delay = 0;
}

int city_religion_t::coverage_avg(e_god god) {
    return coverage[god];
}

int city_religion_t::god_coverage_total(e_god god, e_building_type shrine, e_building_type temple, e_building_type complex) {
    switch (is_god_known(god)) {
    default: return 0;

    case GOD_STATUS_KNOWN: {
            const int shrine_cov = 150 * g_city.buildings.count_total(shrine);
            const int temple_cov = 375 * g_city.buildings.count_active(temple);
            const int complex_cov = 8000 * g_city.buildings.count_active(complex);
            const int total_cov = shrine_cov + temple_cov + complex_cov;
            return total_cov;
        }

    case GOD_STATUS_PATRON:{ 
            const int shrine_cov = 300 * g_city.buildings.count_total(shrine);
            const int temple_cov = 750 * g_city.buildings.count_active(temple);
            const int complex_cov = 8000 * g_city.buildings.count_active(complex);
            const int total_cov = shrine_cov + temple_cov + complex_cov;
            return total_cov;
        }
    }
}

void city_religion_t::calc_coverage() {
    int pop = g_city.population.current;

    int known_gods_num = 0;
    for (e_god i = GOD_OSIRIS; i < MAX_GODS; ++i) {
        if (is_god_known((e_god)i) != GOD_STATUS_UNKNOWN) {
            known_gods_num++;
        }
    }

    if (known_gods_num <= 0) {
        return;
    }

    coverage[GOD_OSIRIS] = std::min(calc_percentage(pop, god_coverage_total(GOD_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS)), 100);
    coverage[GOD_RA] = std::min(calc_percentage(pop, god_coverage_total(GOD_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA)), 100);
    coverage[GOD_PTAH] = std::min(calc_percentage(pop, god_coverage_total(GOD_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_COMPLEX_PTAH)), 100);
    coverage[GOD_SETH] = std::min(calc_percentage(pop, god_coverage_total(GOD_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_COMPLEX_SETH)), 100);
    coverage[GOD_BAST] = std::min(calc_percentage(pop, god_coverage_total(GOD_BAST, BUILDING_SHRINE_BAST, BUILDING_TEMPLE_BAST, BUILDING_TEMPLE_COMPLEX_BAST)), 100);

    int result = coverage[GOD_OSIRIS] + coverage[GOD_RA]
                        + coverage[GOD_PTAH] + coverage[GOD_SETH]
                        + coverage[GOD_BAST];

    coverage_common = (result / known_gods_num);
}

city_religion_t::god_states city_religion_t::known_gods() {
    god_states r;
    for (e_god i = GOD_OSIRIS; i < MAX_GODS; ++i) {
        if (is_god_known((e_god)i) != GOD_STATUS_UNKNOWN) {
            r.push_back(&gods[i]);
        }
    }

    return r;
}

e_god_status city_religion_t::is_god_known(e_god god) {
    return gods[god].is_known;
}

void city_religion_t::set_god_known(e_god god, e_god_status v) {
   gods[god].is_known = v;
}

static bool OSIRIS_locusts() {
    // TODO
    return 0;
}

bool city_religion_t::PTAH_warehouse_restock() {
    // fill warehouses with gems, clay, pottery, flax, linen, or jewelry
    e_resource resources[6] = {RESOURCE_GEMS, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS};

    building_storage_yard* chosen_yard = nullptr;
    int lowest_stock_found = 10000;
    buildings_valid_do<building_storage_yard>([&] (building_storage_yard *warehouse) {
        int total_stored = 0;
        for (int j = 0; j < 6; ++j) {
            total_stored += warehouse->amount(resources[j]);
        }

        if (total_stored > 0 && total_stored < lowest_stock_found) {
            lowest_stock_found = total_stored;
            chosen_yard = warehouse;
        }
    });

    e_resource chosen_resource = RESOURCE_NONE;
    int lowest_resource_found = 10000;
    if (lowest_stock_found > 0 && chosen_yard != nullptr) {
        for (int i = 0; i < 6; ++i) {
            int stored = chosen_yard->amount(resources[i]);
            if (stored > 0 && stored < lowest_resource_found) {
                lowest_resource_found = stored;
                chosen_resource = resources[i];
            }
        }

        if (chosen_resource > 0) {
            chosen_yard->add_resource(chosen_resource, 999999, /*force*/true); // because I'm lazy.
            bool was_added = (chosen_yard->amount(chosen_resource) == lowest_resource_found);
            return !was_added;
        }
    }

    return false;
}

bool city_religion_t::PTAH_industry_restock() {
    if (!is_god_known(GOD_PTAH)) {
        return false;
    }

    // restocks shipwrights, weavers and jewelers
    e_building_type industries[3] = {BUILDING_SHIPWRIGHT, BUILDING_WEAVER_WORKSHOP, BUILDING_JEWELS_WORKSHOP};
    e_resource industry_resource[3] = {RESOURCE_NONE, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS};

    // search for industries
    int industries_found = 0;
    for (int i = 0; i < 3; ++i) {
        if (g_city.buildings.count_total(industries[i]) > 0
            || (industry_resource[i] != RESOURCE_NONE && g_city.buildings.count_industry_active(industry_resource[i]) > 0)) {
            industries_found++;
        } else {
            industries[i] = BUILDING_NONE;
        }
    }

    if (industries_found == 0) {
        return false;
    }

    int randm = anti_scum_random_15bit() % industries_found;
    int industry = 0;

    for (int i = 0; i < 3; ++i) {
        if (industries[i] > 0) {
            if (industry++ == randm) {
                for (int j = 1; j < MAX_BUILDINGS; j++) {
                    building* b = building_get(j);
                    if (b->state != BUILDING_STATE_VALID || b->type != industries[i])
                        continue;

                    b->stored_amount_first = std::clamp<short>(b->stored_amount_first, 200, 9999);
                }
                return true;
            }
        }
    }
    return false;
}

bool city_religion_t::PTAH_warehouse_destruction() {
    if (!is_god_known(GOD_PTAH)) {
        return false;
    }

    // destroy the "best" warehouse found (most stocked up)
    int max_stored = 0;
    building_storage_yard* max_building = nullptr;

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_storage_yard *warehouse = building_get(i)->dcast_storage_yard();
        if (!warehouse || !warehouse->is_valid())
            continue;

        int total_stored = 0;
        for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
            total_stored += warehouse->amount(r);
        }

        if (total_stored > max_stored) {
            max_stored = total_stored;
            max_building = warehouse;
        }
    }

    if (max_building == nullptr) {
        return false;
    }
    //    city_message_disable_sound_for_next_message();
    //    city_message_post(false, MESSAGE_FIRE, max_building->type, max_building->tile.grid_offset());
    max_building->base.destroy_by_fire();
    map_routing_update_land();
    return true;
}

bool city_religion_t::PTAH_industry_destruction() {
    // destroys random industry, if found
    e_building_type industries[6] = {BUILDING_GOLD_MINE, BUILDING_GEMSTONE_MINE, BUILDING_CLAY_PIT, BUILDING_SHIPWRIGHT, BUILDING_WEAVER_WORKSHOP, BUILDING_JEWELS_WORKSHOP};
    e_resource industry_resource[6] = {RESOURCE_GOLD, RESOURCE_GEMS, RESOURCE_CLAY, RESOURCE_NONE, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS};

    // search for industries
    int industries_found = 0;
    for (int i = 0; i < 6; ++i) {
        if (g_city.buildings.count_total(industries[i]) > 0
            || (industry_resource[i] != RESOURCE_NONE && g_city.buildings.count_industry_active(industry_resource[i]) > 0)) {
            industries_found++;
        } else {
            industries[i] = BUILDING_NONE;
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
                        b->destroy_by_fire();
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

static int compare_house_level(int A, int B) {
    auto housea = building_get(A)->dcast_house();
    auto houseb = building_get(B)->dcast_house();

    const e_house_level hA = housea->house_level();
    const e_house_level hB = houseb->house_level();

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
            if (compare_house_level(arr[B], arr[A]) > 0) // A is more evolved
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
            } while (compare_house_level(arr[A], arr[first]) < 1);

            // finds the last house worse than the one at the top!
            do {
                B--;
                if (B <= first)
                    break;
            } while (compare_house_level(arr[B], arr[first]) > -1);

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

bool city_religion_t::BAST_houses_destruction() {
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
            auto house = building_get(i)->dcast_house();
            if (!house || house->state() != BUILDING_STATE_VALID) {
                continue;
            }

            int this_house_level = house->house_level();
            int last_house_level = building_get(houses[19])->dcast_house()->house_level();
            if (this_house_level > last_house_level) { // found house more evolved than the initial 20 houses

                // where to stuff this new house? find the appropriate spot index
                for (int j = 0; j < 20; ++j) {
                    if (building_get(houses[j])->dcast_house()->house_level() < this_house_level) {
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
            if (houses[i] != 0) {
                building_get(houses[i])->destroy_by_fire();
            }
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

void city_religion_t::perform_major_blessing(e_god god) {
    bool success = false;
    switch (god) {
    case GOD_OSIRIS:
        if (anti_scum_random_bool()) {
            // double farm yields
            osiris_double_farm_yield_days = 100 + rand() % 50;
            messages::god(GOD_OSIRIS, "message_blessing_from_osiris" );
            return;
        } else {
            // better next flood quality
            g_floods.adjust_next_quality((anti_scum_random_15bit() % 3 * 5 + 10) * 2);
            messages::god(GOD_OSIRIS, "message_blessing_inundation_from_osiris" );
            return;
        }
        break;

    case GOD_RA:
        if (anti_scum_random_bool()) {
            // exports sell for 150% profits for the next 12 months
            ra_150_export_profits_months_left = 12;
            messages::god(GOD_RA, "message_blessing_trade_from_ra" );
            return;
        } else {
            // increased kingdom by 15
            g_city.kingdome.change(15);
            messages::god(GOD_RA, "message_blessing_ra_kingdom" );
            return;
        }
        break;

    case GOD_PTAH:
        // gems, clay, pottery, flax, linen, or jewelry in storage yards
        success = PTAH_warehouse_restock();
        messages::god( GOD_PTAH, success ? "message_blessing_ptah" : "message_blessing_ptah_noeffect" );
        return;

    case GOD_SETH:
        seth_crush_enemy_troops = 10;
        messages::god( GOD_SETH, "message_blessing_seth" );
        return;

    case GOD_BAST:
        // fills houses and bazaars
        BAST_refill_houses_and_bazaar();
        messages::god( GOD_BAST, "message_blessing_bast" );
        return;
    }
}

void city_religion_t::perform_minor_blessing(e_god god) {
    int randm = 0;
    switch (god) {
    default:
        break;

    case GOD_OSIRIS:
        // slightly better flood
        randm = anti_scum_random_15bit();
        randm = randm & 0x80000003;
        if ((int)randm < 0) {
            randm = (randm - 1 | 0xfffffffc) + 1;
        }
        g_floods.adjust_next_quality(randm * 5 + 5);
        messages::popup("message_small_blessing_from_osiris", 0, 0);
        break;

    case GOD_RA:
        if (anti_scum_random_bool()) {
            // slightly increased trading
            ra_slightly_increased_trading_months_left = 12;
            messages::popup("message_minor_blessing_from_ra", 0, 0);
            return;
        } else {
            // slightly increased reputation
            messages::popup("message_minor_blessing_from_ra_2", 0, 0);
            g_city.kingdome.increase_blessing_god(5);
            return;
        }
        break;

    case GOD_PTAH:
        // restocks shipwrights, weavers and jewelers
        PTAH_industry_restock(); // <-- there is no message for when this fails.
        messages::popup("message_minor_blessing_from_ptah", 0, 0);
        return;

    case GOD_SETH:
        // protects soldiers far away
        seth_protect_player_troops_months = 10;
        messages::popup("message_minor_blessing_from_seth", 0, 0);
        return;

    case GOD_BAST: {
        // throws a festival for the other gods
        static auto &city_data = g_city;
        city_data.festival.planned.god = GOD_OSIRIS;
        city_data.festival.planned.size = FESTIVAL_BAST_SPECIAL;
        city_data.festival.planned.months_to_go = 1;
        city_data.festival.first_festival_effect_months = 1;

        city_data.religion.gods[GOD_RA].months_since_festival = 0;
        city_data.religion.gods[GOD_PTAH].months_since_festival = 0;
        city_data.religion.gods[GOD_SETH].months_since_festival = 0;
        messages::popup("message_small_blessing_from_bast", 0, 0);
        }
        return;
    }
}

void city_religion_t::perform_major_curse(e_god god) {
    bool success = false;
    switch (god) {
    case GOD_OSIRIS:
        if (anti_scum_random_bool()) {
            // worse flood quality
            g_floods.adjust_next_quality((-2 - anti_scum_random_15bit() % 3) * 10);
            messages::popup("message_wrath_of_osiris", 0, 0);
            return;
        } else {
            // locusts
            OSIRIS_locusts();
            messages::popup("message_wrath_of_osiris_2", 0, 0);
            return;
        }
        break;

    case GOD_RA:
        if (anti_scum_random_15bit() % 3 == 0) {
            // lowers commerce prices
            ra_harshly_reduced_trading_months_left = 12;
            messages::popup("message_wrath_of_ra", 0, 0);
            return;
        }

        if (anti_scum_random_15bit() % 3 == 1) {
            // lowers reputation
            g_city.kingdome.reduce_god_wrath(15);
            messages::popup("message_wrath_of_ra_2", 0, 0);
            return;
        }
        // no trading ships/caravans for one year
        ra_no_traders_months_left = 12;
        messages::popup("message_wrath_of_ra_3", 0, 0);
        return;

    case GOD_PTAH:
        if (anti_scum_random_bool()) {
            // destroys some industrial buildings
            success = PTAH_industry_destruction();
            if (success)
                messages::popup("message_wrath_of_ptah", 0, 0);
            else // no yard found
                messages::popup("message_wrath_of_ptah_no_effect", 0, 0);
            return;
        } else {
            // frogs
            PTAH_frogs();
            messages::popup("message_wrath_of_ptah_2", 0, 0);
            return;
        }
        break;

    case GOD_SETH:
        if (anti_scum_random_bool()) {
            // destroys all ships
            SETH_ships_destruction();
            messages::popup("message_wrath_of_seth", 0, 0);
            return;
        } else {
            SETH_hailstorm();
            messages::popup("message_wrath_of_seth_2", 0, 0);
            return;
        }
        break;

    case GOD_BAST:
        // destroy some of the best houses
        BAST_houses_destruction();
        messages::popup("message_wrath_of_bast", 0, 0);
        return;

    default:
        break;
    }
}

void city_religion_t::perform_minor_curse(e_god god) {
    bool success = false;
    switch (god) {
    case GOD_OSIRIS:
        if (anti_scum_random_bool()) {
            // next flood will destroys farms
            osiris_flood_will_destroy_active = 1;
            events::emit(event_message_god{ GOD_OSIRIS, "message_small_curse_osiris" });
            return;
        } else {
            // lower quality flood
            int randm = anti_scum_random_15bit();
            randm = randm & 0x80000003;
            if ((int)randm < 0) {
                randm = (randm - 1 | 0xfffffffc) + 1;
            }
            g_floods.adjust_next_quality((-1 - randm) * 5);
            events::emit(event_message_god{ GOD_OSIRIS, "message_small_curse_osiris" });
            return;
        }
        break;

    case GOD_RA:
        if (anti_scum_random_bool()) {
            // lowers amount of traded goods
            ra_slightly_reduced_trading_months_left = 12;
            events::emit(event_message_god{ GOD_RA, "message_ra_is_upset" });
            return;
        } else {
            // lowers reputation
            g_city.kingdome.reduce_god_wrath(5);
            events::emit(event_message_god{ GOD_RA, "message_ra_is_upset_2" });
            return;
        }
        break;

    case GOD_PTAH:
        // destroys random storage yard
        success = PTAH_warehouse_destruction();
        if (success) {
            events::emit(event_message_god{ GOD_PTAH, "message_ptah_is_upset" });
        } else { // no yard found 
            events::emit(event_message_god{ GOD_PTAH, "message_curse_ptah_noeffect" });
        }
        return;

    case GOD_SETH:
        // destroys the best fort
        success = SETH_fort_destruction();
        if (success) {
            events::emit(event_message_god{ GOD_SETH, "message_seth_is_upset" });
        } else {
            events::emit(event_message_god{ GOD_SETH, "message_seth_is_upset_noeffect" });
        }
        break;

    case GOD_BAST:
        // plague
        BAST_malaria_plague();
        events::emit(event_message_god{ GOD_BAST, "message_bast_is_upset" });
        break;

    default:
        break;
    }
}

void city_religion_t::update_curses_and_blessings(e_god randm_god, e_god_event force) {
    if (randm_god >= MAX_GODS) {
        if (calculate_least_happy_god()) {
            randm_god = (e_god)(least_happy_god - 1);
        }
    }

    // perform curses/blessings
    if (randm_god < MAX_GODS) {
        god_state* god = &gods[randm_god];

        if (force == GOD_EVENT_MAJOR_BLESSING
            || (force == GED_EVENT_UNKNOWN && god->happy_ankhs == 50 && god->months_since_festival < 15)) {
            /* ***** MAJOR BLESSINGS ***** */
            perform_major_blessing((e_god)randm_god);
            god->happy_ankhs = 0;
            god->mood = calc_bound(god->mood - 30, 0, 100);
        } else if (force == GOD_EVENT_MINOR_BLESSING
                   || (force == -1 && god->happy_ankhs > 19 && god->months_since_festival < 15)) {
            /* ***** MINOR BLESSINGS ***** */
            perform_minor_blessing(randm_god);
            god->happy_ankhs = 0;
            god->mood = calc_bound(god->mood - 12, 0, 100);
        } else if (force == GOD_EVENT_MAJOR_CURSE
                   || (force == -1 && god->wrath_bolts == 50 && god->months_since_festival > 3)) {
            /* ***** MAJOR CURSES ***** */
            perform_major_curse(randm_god);
            god->wrath_bolts = 0;
            god->mood = calc_bound(god->mood + 30, 0, 100);
        } else if (force == GOD_EVENT_MINOR_CURSE
                   || (force == -1 && god->wrath_bolts > 19 && god->months_since_festival > 3)) {
            /* ***** MINOR CURSES ***** */
            perform_minor_curse(randm_god);
            god->wrath_bolts = 0;
            god->mood = calc_bound(god->mood + 12, 0, 100);
        }
    }
}

void city_religion_t::calculate_gods_mood_targets() {
    const auto &known_gods = this->known_gods();
    if (g_scenario.env.gods_least_mood > 0) {
        for (auto *god: known_gods) {
            god->target_mood = g_scenario.env.gods_least_mood;
            god->mood = g_scenario.env.gods_least_mood;
        }
        return;
    }

    // base happiness: percentage of houses covered
    for (auto *god: known_gods) {
        god->target_mood = coverage_avg(god->type);
    }

    int max_temples = 0;
    e_god max_god = GOD_UNKNOWN;

    int min_temples = 100000;
    e_god min_god = GOD_UNKNOWN;

    for (auto *god: known_gods) {
        int num_temples = 0;
        switch (god->type) {
        case GOD_OSIRIS: num_temples = g_city.buildings.count_total({ BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS }); break;
        case GOD_RA: num_temples = g_city.buildings.count_total({ BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA }); break;
        case GOD_PTAH: num_temples = g_city.buildings.count_total({ BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_COMPLEX_PTAH }); break;
        case GOD_SETH: num_temples = g_city.buildings.count_total({ BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_COMPLEX_SETH }); break;
        case GOD_BAST: num_temples = g_city.buildings.count_total({ BUILDING_TEMPLE_BAST, BUILDING_TEMPLE_COMPLEX_BAST }); break;

        default:
            assert(false);
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
    for (auto *god: known_gods) {
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

    int points = calc_bound((g_city.population.current - 350) / 50, 0, 5);
    int min_mood = 50 - 10 * points;
    int max_mood = 50 + 10 * points;

    for (auto *god: known_gods) {
        god->target_mood = calc_bound(god->target_mood, min_mood, max_mood);
    }
}

void city_religion_t::update_mood(e_god randm_god) {
    const auto &known_gods = this->known_gods();
    for (auto *god: known_gods) {
        if (god->mood < god->target_mood) {
            god->mood++;
        } else if (god->mood > god->target_mood) {
            god->mood--;
        }

        god->mood = std::max(god->mood, g_scenario.env.gods_least_mood);

        if (god->mood > 50) 
            god->curse_done = false;

        if (god->mood < 50)
            god->blessing_done = false;
    }

    // update anger/happiness/bolt icons/etc.
    const int difficulty = g_settings.difficulty();
    if (is_god_known(randm_god) != GOD_STATUS_UNKNOWN) { // OG code checks "randm_god < MAX_GODS" which is redundant.
        god_state* god = &gods[randm_god];
        if (god->mood > 50)
            god->wrath_bolts = 0;

        if (god->mood <= 10) {
            int difficultyLevels[] = {1, 1, 2, 4, 5};
            god->wrath_bolts += difficultyLevels[difficulty];
        }

        if (god->mood <= 20) {
            int difficultyLevels[] = {0, 1, 1, 2, 3};
            god->wrath_bolts += difficultyLevels[difficulty];
        }

        if (god->mood <= 30) {
            int difficultyLevels[] = {0, 0, 0, 1, 2};
            god->wrath_bolts += difficultyLevels[difficulty];
        }

        god->wrath_bolts = std::min<uint8_t>(god->wrath_bolts, 50);

        if (god->mood < 50) {
            god->happy_ankhs = 0;
        }

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
        }

        god->happy_ankhs = std::min<uint8_t>(god->wrath_bolts, 50);
    }
}

template<typename T>
void reduce_month(T &m) { if (m > 0) { m--; }};

void city_religion_t::update_monthly_data(e_god randm_god) {
    // update festival counter
    const auto &known_gods = this->known_gods();
    for (auto *god: known_gods) {
        god->months_since_festival++;
    }

    // handle blessings, curses, etc every month
    update_curses_and_blessings(randm_god, (e_god_event)-1);

    // post city message about the gods being angery
    int min_happiness = 100;
    for (auto *god: known_gods) {
        if (god->mood < min_happiness) {
           min_happiness = god->mood;
        }
    }

    if (angry_message_delay > 0) {
        angry_message_delay--;
    } else if (min_happiness < 30) { // message delay = 0 and there's a god with mood < 30
        angry_message_delay = 20;
        if (min_happiness < 10) {
            messages::popup("message_gods_wrathful", 0, 0);
        }
    }

    // update status effects with limited durations
    reduce_month(ra_slightly_increased_trading_months_left);
    reduce_month(ra_harshly_reduced_trading_months_left);
    reduce_month(ra_slightly_reduced_trading_months_left);
    reduce_month(ra_150_export_profits_months_left);
    reduce_month(ra_no_traders_months_left);
}

void city_religion_t::update() {
    OZZY_PROFILER_SECTION("Game/Religion/Update");
    calc_coverage();
    calculate_gods_mood_targets();

    if (!g_settings.gods_enabled) {
        return;
    }

    e_god randm_god = e_god(anti_scum_random_15bit() % MAX_GODS);
    update_mood(randm_god);

    //        perform_minor_blessing(GOD_PTAH); // TODO: DEBUGGING
    //        BAST_houses_destruction();
    if (osiris_double_farm_yield_days > 0) {
        osiris_double_farm_yield_days--;
    }

    // at the start of every month
    if (game.simtime.day == 0) {
        update_monthly_data(randm_god);
    }
}

bool city_religion_t::calculate_least_happy_god() {
    e_god max_god = GOD_UNKNOWN;
    int max_wrath = 0;
    // first, check who's the most enraged (number of bolts)
    const auto &known_gods = this->known_gods();
    for (auto *god: known_gods) {
        if (god->wrath_bolts > max_wrath) {
            max_god = god->type;
            max_wrath = god->wrath_bolts;
        }
    }

    if (max_god != GOD_UNKNOWN) {
        least_happy_god = max_god;
        return true;
    }

    int min_happiness = 40;
    // lastly, check who's the least happy
    for (auto *god: known_gods) {
        if (god->mood < min_happiness) {
            max_god = god->type;
            min_happiness = god->mood;
        }
    }

    least_happy_god = max_god;
    return max_god > 0;
}

int city_religion_t::god_happiness(e_god god_id) {
    return gods[god_id].mood;
}

int city_religion_t::god_wrath_bolts(e_god god_id) {
    return gods[god_id].wrath_bolts;
}

int city_religion_t::god_happy_angels(e_god god_id) {
    return gods[god_id].happy_ankhs;
}

e_god_mood city_religion_t::least_mood() {
    int least_god_happiness = 100;
    const auto &known_gods = this->known_gods();
    for (auto *god: known_gods) {
        int happiness = god_happiness(god->type);
        if (happiness < least_god_happiness) {
            least_god_happiness = happiness;
        }
    }

    if (least_god_happiness < 10) {
        return GOD_MOOD_WRATHFUL;
    } else if (least_god_happiness < 20) {
        return GOD_MOOD_VERY_ANGRY;
    } else if (least_god_happiness < 40) {
        return GOD_MOOD_ANGRY;
    } else if (least_god_happiness < 51) {
        return GOD_MOOD_INDIFIRENT;
    } else if (least_god_happiness < 65) {
        return GOD_MOOD_FINE;
    } else if (least_god_happiness < 80) {
        return GOD_MOOD_PLEASURE;
    } else {
        return GOD_MOOD_EXALTED;
    }
}

int city_religion_t::months_since_festival(e_god god_id) {
    return gods[god_id].months_since_festival;
}

int city_religion_t::months_since_last_festival() {
    uint32_t since_last_festival_months = 999;
    for (auto &g : gods) {
        since_last_festival_months = std::min<int>(since_last_festival_months, g.months_since_festival);
    }

    return since_last_festival_months;
}

e_god city_religion_t::get_least_happy_god() {
    return (e_god)(this->least_happy_god - 1);
}

int city_religion_t::spirit_of_seth_power() {
    return seth_crush_enemy_troops;
}

void city_religion_t::spirit_of_seth_mark_used() {
   seth_crush_enemy_troops = 0;
}

bool city_religion_t::osiris_create_shipwreck_flotsam() {
    if (osiris_sank_ships) {
        osiris_sank_ships = 0;
        return true;
    } else {
        return false;
    }
}

const god_state::static_params_t &god_state::static_params() const {
    return gods_static_data[type];
}

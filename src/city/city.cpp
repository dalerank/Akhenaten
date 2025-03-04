#include "city.h"

#include "city/constants.h"
#include "city/city.h"
#include "city/trade.h"
#include "city/buildings.h"
#include "city/population.h"
#include "core/object_property.h"
#include "grid/water.h"
#include "core/profiler.h"
#include "core/calc.h"
#include "game/difficulty.h"
#include "scenario/scenario.h"
#include "core/game_environment.h"
#include "empire/empire_city.h"
#include "empire/empire.h"
#include "io/io_buffer.h"
#include "empire/trade_route.h"
#include "building/count.h"
#include "building/building_granary.h"
#include "figure/figure.h"
#include "figuretype/figure_fishing_point.h"
#include "figuretype/figure_kingdome_trader.h"
#include "figuretype/figure_trader_ship.h"
#include "empire/empire_object.h"

#include <core/string.h>
#include <string.h>
#include <time.h>

city_t g_city;
events::typed_queue g_city_events;

void city_t::init() {
    buildings.shutdown();
    g_city_events.removeListeners();

    memset(this, 0, sizeof(struct city_t));

    unused.faction_bytes[0] = 0;
    unused.faction_bytes[1] = 0;

    sentiment.value = 60;
    health.target_value = 50;
    health.value = 50;
    unused.unknown_00c0 = 3;
    labor.wages_kingdome = 30;
    labor.wages = 30;
    finance.tax_percentage = 7;
    trade.caravan_import_resource = RESOURCE_MIN;
    trade.caravan_backup_import_resource = RESOURCE_MIN;
    population.monthly.next_index = 0;
    population.monthly.count = 0;
    festival.months_since_festival = 1;
    festival.selected.size = FESTIVAL_SMALL;
    kingdome.reset_gifts();
    religion.reset();
    buildings.init();
    figure_clear_all();
}

void city_t::init_custom_map() {
    unused.faction_id = 1;
    unused.unknown_00a2 = 1;
    unused.unknown_00a3 = 1;
    finance.treasury = difficulty_adjust_money(scenario_initial_funds());
    finance.last_year.balance = finance.treasury;
}

bool city_t::has_made_money() {
    const int treasury_this_year = finance.last_year.expenses.construction + finance.treasury;
    const int treasury_last_year = ratings.prosperity_treasury_last_year;
    return (treasury_this_year > treasury_last_year);
}

void city_t::ratings_update_explanations() {
    ratings.update_culture_explanation();
    update_prosperity_explanation();
    ratings.update_monument_explanation();
    ratings.update_kingdom_explanation();
}

void city_t::ratings_update(bool is_yearly_update) {
    ratings.update_culture_rating();
    ratings.update_kingdom_rating(is_yearly_update);
    calculate_max_prosperity();

    if (is_yearly_update) {
        update_prosperity_rating();
        ratings.update_monument_rating();
    }
}

void city_t::init_campaign_mission() {
    finance.treasury = difficulty_adjust_money(finance.treasury);
}

void city_t::init_mission_resources(const std::vector<resource_allow>& resources) {
    auto fobj = const_cast<full_empire_object*>(ourcity().get_full_empire_object());
    for (const auto &r: resources) {
        fobj->add_sell_resource(r.type);
    }
}

e_resource city_t::allowed_foods(int i) {
    return resource.food_types_allowed[i];
}

bool city_t::generate_trader_from(empire_city &city) {
    if (g_city.religion.ra_no_traders_months_left > 0) {
        return false;
    }

    int max_traders = 0;
    int num_resources = 0;
    auto &trade_route = city.get_route();
    for (const auto &r: resource_list::all) {
        if (city.buys_resource[r.type] || city.sells_resource[r.type]) {
            ++num_resources;
            int trade_limit = trade_route.limit(r.type);
            if (trade_limit >= 1500 && trade_limit < 2500) {
                max_traders += 1;
            } else if (trade_limit >= 2500 && trade_limit < 4000) {
                max_traders += 2;
            } else if (trade_limit >= 4000) {
                max_traders += 3;
            }
        }
    }

    if (num_resources > 1) {
        if (max_traders % num_resources)
            max_traders = max_traders / num_resources + 1;
        else
            max_traders = max_traders / num_resources;
    }

    if (max_traders <= 0) {
        return false;
    }

    int index;
    if (max_traders == 1) {
        if (!city.trader_figure_ids[0])
            index = 0;
        else
            return false;
    } else if (max_traders == 2) {
        if (!city.trader_figure_ids[0])
            index = 0;
        else if (!city.trader_figure_ids[1])
            index = 1;
        else
            return false;
    } else { // 3
        if (!city.trader_figure_ids[0])
            index = 0;
        else if (!city.trader_figure_ids[1])
            index = 1;
        else if (!city.trader_figure_ids[2])
            index = 2;
        else
            return false;
    }

    if (city.trader_entry_delay > 0) {
        city.trader_entry_delay--;
        return false;
    }

    city.trader_entry_delay = city.is_sea_trade ? 30 : 4;

    if (city.is_sea_trade) {
        // generate ship
        if (g_city.buildings.has_working_dock() && scenario_map_has_river_entry()
            && !city_trade_has_sea_trade_problems()) {
            tile2i river_entry = scenario_map_river_entry();
            city.trader_figure_ids[index] = figure_trade_ship::create(river_entry, city);
            return true;
        }
    } else {
        // generate caravan and donkeys
        if (!city_trade_has_land_trade_problems()) {
            // caravan head
            tile2i entry = g_city.map.entry_point;
            city.trader_figure_ids[index] = figure_trade_caravan::create(entry, city);
            return true;
        }
    }
    return false;
}

bool city_t::is_food_allowed(e_resource resource) {
    bool result = false;
    for (int i = 0; i < 4; i++) {
        if (g_city.allowed_foods(i) == resource) {
            result = true;
        }
    }
    // for etc etc todo: other resources?
    return result;
}

void city_t::set_allowed_food(int i, e_resource r) {
    resource.food_types_allowed[i] = r;
}

void city_t::coverage_update() {
    OZZY_PROFILER_SECTION("Game/Update/Avg Coverage Update");
    auto &coverage = g_coverage;
    int pop = population.population;

    // entertainment
    coverage.booth = std::min(calc_percentage(400 * building_count_active(BUILDING_BOOTH), pop), 100);
    coverage.bandstand = std::min(calc_percentage(700 * building_count_active(BUILDING_BANDSTAND), pop), 100);
    coverage.pavilion = std::min(calc_percentage(1200 * building_count_active(BUILDING_PAVILLION), pop), 100);
    coverage.senet_house = building_count_active(BUILDING_SENET_HOUSE) <= 0 ? 0 : 100;

    // education
    city_population_calculate_educational_age();

    coverage.school = std::min(calc_percentage(75 * building_count_active(BUILDING_SCRIBAL_SCHOOL), city_population_school_age()), 100);
    coverage.library = std::min(calc_percentage(800 * building_count_active(BUILDING_LIBRARY), pop), 100);
    coverage.academy = std::min(calc_percentage(100 * building_count_active(BUILDING_ACADEMY), city_population_academy_age()), 100);
}

int stack_units_by_resource(int resource) {
    switch (resource) {
    default:
        return RESOURCE_UNIT_PILE;

    case RESOURCE_GOLD:
    case RESOURCE_STONE:
    case RESOURCE_LIMESTONE:
    case RESOURCE_GRANITE:
    case RESOURCE_SANDSTONE:
    case RESOURCE_MARBLE:
        return RESOURCE_UNIT_BLOCK;

    case RESOURCE_WEAPONS:
        return RESOURCE_UNIT_WEAPON;

    case RESOURCE_CHARIOTS:
        return RESOURCE_UNIT_CHARIOT;
    }
}

int stack_proper_quantity(int full, int resource) {
    switch (stack_units_by_resource(resource)) {
    default: // all other goods are 100 worth of, per pile
        return full;

    case RESOURCE_UNIT_BLOCK:
    case RESOURCE_UNIT_WEAPON:
    case RESOURCE_UNIT_CHARIOT:
    case RESOURCE_WEAPONS:
        return full / 100;
    }
}

empire_city &city_t::ourcity() {
    auto const &cities = g_empire.get_cities();
    auto it = std::find_if(cities.begin(), cities.end(), [] (auto &city) { return (city.in_use && (city.type == EMPIRE_CITY_OURS)); });

    assert(it != cities.end());
    return *it;
}

bool city_t::can_produce_resource(e_resource resource) {
    auto &c = ourcity();
    return c.sells_resource[resource];
}

void city_t::set_produce_resource(e_resource resource, bool v) {
    auto &c = ourcity();
    c.sells_resource[resource] = v;
}

void city_t::update_allowed_foods() {
    int food_index = 0;

    std::fill_n(std::begin(resource.food_types_allowed), RESOURCES_FOODS_MAX, RESOURCE_NONE);

    for (e_resource resource = RESOURCE_MIN; resource < RESOURCES_FOODS_MAX; ++resource) {
        bool can_import_food = g_empire.can_import_resource(resource, false);
        bool can_produce_food = can_produce_resource(resource);
        if (can_import_food || can_produce_food) {
            set_allowed_food(food_index, resource);
            food_index++;
        }
    }
}

bool city_t::available_resource(e_resource resource) {
    e_resource raw_resource = get_raw_resource(resource);
    // finished goods: check imports of raw materials
    if (raw_resource != resource && g_empire.can_import_resource(raw_resource, false)) {
        return true;
    }

    // check if we can produce the raw materials
    return can_produce_resource(raw_resource);
}

void city_t::buildings_generate_figure() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure Generate");
    buildings_valid_do([] (building &b) {
        b.figure_generate();
    });
}


io_buffer* iob_city_data = new io_buffer([](io_buffer* iob, size_t version) {
    auto &data = g_city;
    iob->bind(BIND_SIGNATURE_RAW, &data.unused.other_player, 18904);
    iob->bind(BIND_SIGNATURE_INT8, &data.unused.unknown_00a0);
    iob->bind(BIND_SIGNATURE_INT8, &data.unused.unknown_00a1);
    iob->bind(BIND_SIGNATURE_INT8, &data.unused.unknown_00a2);
    iob->bind(BIND_SIGNATURE_INT8, &data.unused.unknown_00a3);
    iob->bind(BIND_SIGNATURE_INT8, &data.unused.unknown_00a4);
    iob->bind(BIND_SIGNATURE_INT8, &data.buildings.unknown_value);
    iob->bind(BIND_SIGNATURE_INT8, &data.unused.unknown_00a7);
    iob->bind(BIND_SIGNATURE_INT8, &data.unused.unknown_00a6);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.tax_percentage);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.treasury);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.value);
    iob->bind(BIND_SIGNATURE_INT32, &data.health.target_value);
    iob->bind(BIND_SIGNATURE_INT32, &data.health.value);
    iob->bind(BIND_SIGNATURE_INT32, &data.health.num_mortuary_workers);
    iob->bind(BIND_SIGNATURE_INT32, &data.unused.unknown_00c0);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.population);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.population_last_year);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.school_age);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.academy_age);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.total_capacity);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.room_in_houses);
    for (int i = 0; i < 2400; i++)
        iob->bind(BIND_SIGNATURE_INT32, &data.population.monthly.values[i]);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.monthly.next_index);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.monthly.count);
    for (int i = 0; i < 100; i++)
        iob->bind(BIND_SIGNATURE_INT16, &data.population.at_age[i]);
    for (int i = 0; i < 20; i++)
        iob->bind(BIND_SIGNATURE_INT32, &data.population.at_level[i]);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.yearly_births);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.yearly_deaths);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.lost_removal);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.immigration_amount_per_batch);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.emigration_amount_per_batch);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.emigration_queue_size);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.immigration_queue_size);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.lost_homeless);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.last_change);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.average_per_year);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.total_all_years);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.people_in_shanties);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.people_in_manors);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.total_years);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.yearly_update_requested);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.last_used_house_add);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.last_used_house_remove);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.immigrated_today);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.emigrated_today);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.refused_immigrants_today);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.percentage);
    iob->bind(BIND_SIGNATURE_INT32, &data.unused.unused_27d0);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.immigration_duration);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.emigration_duration);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.newcomers);
    iob->bind(BIND_SIGNATURE_UINT16, &data.migration.nobles_leave_city_this_year);
    iob->bind(BIND_SIGNATURE_UINT16, &data.unused.unused_27d0_short);

    for (int i = 0; i < 3; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.unused.unknown_27e0[i]);
    }

    iob->bind(BIND_SIGNATURE_INT16, &data.unused.unknown_27f0);
    iob->bind(BIND_SIGNATURE_INT16, &data.resource.last_used_warehouse);
    for (int i = 0; i < 18; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &data.unused.unknown_27f4[i]);
    }
    iob->bind(BIND_SIGNATURE_INT32, data.map.entry_point);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, data.map.exit_point);
    iob->bind____skip(4);
    iob->bind____skip(4);  // iob->bind(BIND_SIGNATURE_INT32, data.buildings.palace_point);
    iob->bind____skip(4);
    iob->bind____skip(4);  // iob->bind(BIND_SIGNATURE_INT32, &data.buildings.palace_building_id);
    iob->bind(BIND_SIGNATURE_INT16, &data.unused.unknown_2828);
    iob->bind____skip(2);
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &data.resource.space_in_warehouses[i + 1]);
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &data.resource.stored_in_warehouses[i + 1]);

    int tmp;
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.resource.trade_status[i + 1]);
        iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    }

    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &data.resource.trading_amount[i + 1]);

    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &data.resource.mothballed[i + 1]);

    iob->bind(BIND_SIGNATURE_INT16, &data.unused.unused_28ca);

    //    iob->bind____skip(20);
    //    for (int i = 0; i < RESOURCES_MAX; i++)
    //        iob->bind(BIND_SIGNATURE_INT16, &city_data.resource.unk_00[i + 1]);
    //    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
    //        iob->bind(BIND_SIGNATURE_INT16, &city_data.resource.granary_food_stored[i]);
    //    iob->bind____skip(28); // temp

    iob->bind____skip(20);
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &data.resource.unk_00[i]);
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &data.resource.granary_food_stored[i]);
    iob->bind____skip(28); // temp

    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT8, &data.resource.food_types_available_arr[i]);

    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT8, &data.resource.food_types_eaten_arr[i]);

    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT8, &data.resource.food_types_arr_unk_00[i]);

    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT8, &data.resource.food_types_arr_unk_01[i]);

    iob->bind____skip(216);

    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT32, &data.resource.stockpiled[i]);

    // TODO: TEMP!!!!
    data.resource.food_types_available_num = 0;
    data.resource.food_types_eaten_num = 0;

    iob->bind(BIND_SIGNATURE_INT32, &data.resource.food_supply_months);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.granaries.operating);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.percentage_plebs);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.working_age);
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.workers_available);
    for (int i = 0; i < 10; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.labor.categories[i].workers_needed);
        iob->bind(BIND_SIGNATURE_INT32, &data.labor.categories[i].workers_allocated);
        iob->bind(BIND_SIGNATURE_INT32, &data.labor.categories[i].total_houses_covered);
        iob->bind(BIND_SIGNATURE_INT32, &data.labor.categories[i].buildings);
        iob->bind(BIND_SIGNATURE_INT32, &data.labor.categories[i].priority);
    }
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.workers_employed);
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.workers_unemployed);
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.unemployment_percentage);
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.unemployment_percentage_for_goverment);
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.workers_needed);
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.wages);
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.wages_kingdome);
    iob->bind(BIND_SIGNATURE_INT32, &data.unused.unknown_2b6c);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.wages_so_far);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.expenses.wages);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.expenses.wages);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.taxed_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.taxed_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.untaxed_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.untaxed_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.percentage_taxed_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.percentage_taxed_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.percentage_taxed_people);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.yearly.collected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.yearly.collected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.yearly.uncollected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.yearly.uncollected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.income.taxes);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.income.taxes);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.monthly.collected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.monthly.uncollected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.monthly.collected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.monthly.uncollected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.income.exports);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.income.exports);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.expenses.imports);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.expenses.imports);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.interest_so_far);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.expenses.interest);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.expenses.interest);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.expenses.stolen);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.expenses.stolen);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.expenses.construction);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.expenses.construction);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.expenses.salary);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.expenses.salary);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.salary_amount);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.salary_rank);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.salary_so_far);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.income.total);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.income.total);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.expenses.total);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.expenses.total);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.net_in_out);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.net_in_out);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.balance);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.balance);
    for (int i = 0; i < 1400; i++)
        iob->bind(BIND_SIGNATURE_INT32, &data.unused.unknown_2c20[i]);
    for (int i = 0; i < 8; i++)
        iob->bind(BIND_SIGNATURE_INT32, &data.unused.houses_requiring_unknown_to_evolve[i]); // ????
    iob->bind(BIND_SIGNATURE_INT32, &data.trade.caravan_import_resource);
    iob->bind(BIND_SIGNATURE_INT32, &data.trade.caravan_backup_import_resource);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.culture);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.prosperity);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.monument);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.kingdom);
    iob->bind____skip(8);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.prosperity_treasury_last_year);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.culture_points.entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.culture_points.religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.culture_points.school);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.culture_points.library);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.culture_points.academy);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.monument_num_criminals);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.monument_num_rioters);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.fountain);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.well);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.more_entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.more_education);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.education);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.school);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.library);
    iob->bind(BIND_SIGNATURE_INT32, &data.unused.unknown_4284);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.apothecary);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.dentist);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.food);

    for (int i = 0; i < 2; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.unused.unknown_4294[i]);
    }

    iob->bind(BIND_SIGNATURE_INT32, &data.buildings.senet_house_placed);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.mortuary);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.physician);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.dentist);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.water_supply);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.physician);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.second_religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.third_religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.booth_shows);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.booth_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.bandstand_shows);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.bandstand_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.pavilion_shows);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.pavilion_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.senet_house_plays);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.senet_house_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &data.entertainment.venue_needing_shows);
    iob->bind(BIND_SIGNATURE_INT32, &data.avg_coverage.average_entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.entertainment);
    iob->bind(BIND_SIGNATURE_INT8, &data.festival.months_since_festival); // ok
    iob->bind____skip(3);

    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.religion.gods[i].target_mood);
    }

    iob->bind____skip(5);
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.religion.gods[i].mood);
    }

    iob->bind____skip(5);
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.religion.gods[i].wrath_bolts);
    }

    iob->bind____skip(20);
    iob->bind____skip(35);
    //    for (int i = 0; i < MAX_GODS; i++)
    //        city_data.religion.gods[i].unused1 = main->read_i8();
    //    for (int i = 0; i < MAX_GODS; i++)
    //        city_data.religion.gods[i].unused2 = main->read_i8();
    //    for (int i = 0; i < MAX_GODS; i++)
    //        city_data.religion.gods[i].unused3 = main->read_i8();
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.religion.gods[i].months_since_festival);
        iob->bind____skip(3);
    }

    iob->bind(BIND_SIGNATURE_INT32, &data.religion.least_happy_god);
    iob->bind(BIND_SIGNATURE_INT32, &data.unused.unknown_4334);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.no_immigration_cause);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.protesters);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.criminals);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.health);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.education);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &data.figures.rioters);
    iob->bind____skip(20);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.selected);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.culture_explanation);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.prosperity_explanation);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.monument_explanation);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.kingdom_explanation);
    iob->bind____skip(8);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.player_rank);
    iob->bind(BIND_SIGNATURE_UINT16, &data.kingdome.personal_savings); // ok
    iob->bind____skip(2);
                                                                          //    for (int i = 0; i < 2; i++)
    //        iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_4374[i]);
    //    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.income.donated);
    //    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.income.donated);
    //        for (int i = 0; i < 2; i++)
    //            iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_4374[i]);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.income.donated);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.income.donated);

    for (int i = 0; i < 2; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.unused.unknown_4374[i]);
    }

    tmp = 0;
    for (int i = 0; i < 10; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &tmp); // dock id
    }

    iob->bind____skip(2); // (BIND_SIGNATURE_INT16, &data.buildings.temple_complex_placed);
    iob->bind(BIND_SIGNATURE_UINT8, &data.figures.fish_number);
    iob->bind(BIND_SIGNATURE_UINT8, &data.figures.animals_number);

    for (int i = 0; i < 3; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &data.unused.unknown_439c[i]);
    }

    iob->bind____skip(2);
    iob->bind____skip(2);
    iob->bind____skip(2);  // iob->bind(BIND_SIGNATURE_INT16, &data.buildings.palace_placed);
    iob->bind____skip(2);
    iob->bind____skip(2);
    iob->bind____skip(2);
    iob->bind____skip(2);
    iob->bind____skip(2);
    //        iob->bind(BIND_SIGNATURE_INT16, &city_data.trade.num_sea_routes);
    //        iob->bind(BIND_SIGNATURE_INT16, &city_data.trade.num_land_routes);
    //        iob->bind(BIND_SIGNATURE_INT16, &city_data.trade.sea_trade_problem_duration);
    //        iob->bind(BIND_SIGNATURE_INT16, &city_data.trade.land_trade_problem_duration);
    //        iob->bind(BIND_SIGNATURE_INT16, &city_data.building.working_docks);
    //        iob->bind(BIND_SIGNATURE_INT16, &city_data.building.senate_placed);
    //        iob->bind(BIND_SIGNATURE_INT16, &city_data.building.working_wharfs);

    for (int i = 0; i < 2; i++) {
        iob->bind(BIND_SIGNATURE_INT8, &data.unused.padding_43b2[i]);
    }
    iob->bind(BIND_SIGNATURE_INT16, &data.finance.stolen_this_year);
    iob->bind(BIND_SIGNATURE_INT16, &data.finance.stolen_last_year);
    iob->bind(BIND_SIGNATURE_INT32, &data.trade.docker_import_resource);
    iob->bind(BIND_SIGNATURE_INT32, &data.trade.docker_export_resource);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.debt_state);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.months_in_debt);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.cheated_money);
    iob->bind____skip(4); // BIND_SIGNATURE_UINT32, data.buildings.recruiter.tile);
    iob->bind____skip(4); // (BIND_SIGNATURE_INT32, &data.buildings.recruiter.building_id);
    iob->bind____skip(4); // (BIND_SIGNATURE_INT32, &data.buildings.recruiter.placed);
    iob->bind(BIND_SIGNATURE_UINT32, data.buildings.festival_square);

    for (int i = 0; i < 4; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.unused.unknown_43d8[i]);
    }

    iob->bind(BIND_SIGNATURE_INT32, &data.population.lost_troop_request);
    iob->bind(BIND_SIGNATURE_INT32, &data.unused.unknown_43f0);
    iob->bind(BIND_SIGNATURE_INT32, &data.mission.has_won);
    iob->bind(BIND_SIGNATURE_INT32, &data.mission.continue_months_left);
    iob->bind(BIND_SIGNATURE_INT32, &data.mission.continue_months_chosen); // wrong? hmm... 300 became 120? is it the wages?
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.wage_rate_paid_this_year);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.expenses.tribute); // ok
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.expenses.tribute);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.tribute_not_paid_last_year);
    iob->bind(BIND_SIGNATURE_UINT8, &data.festival.selected.god);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.festival.selected.size); // ????
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.festival.planned.size);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT8, &data.festival.planned.months_to_go);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.festival.planned.god);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT16, &data.festival.small_cost); // 23 --> 22 ??????
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.festival.large_cost); // 46 --> 45
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.festival.grand_cost); // 93 --> 90
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.festival.grand_alcohol);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT8, &data.festival.not_enough_alcohol);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.avg_coverage.average_religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.avg_coverage.average_education);
    iob->bind(BIND_SIGNATURE_INT32, &data.avg_coverage.average_health);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_UINT8, &data.festival.first_festival_effect_months);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.festival.second_festival_effect_months);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.unused.unused_4454);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.unemployment);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.previous_value); // ok
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.message_delay);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.low_mood_cause);
    iob->bind(BIND_SIGNATURE_INT32, &data.figures.security_breach_duration);
    for (int i = 0; i < 4; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.unused.unknown_446c[i]);
    }
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.selected_gift_size);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.months_since_gift); // ok
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.gift_overdose_penalty);
    iob->bind(BIND_SIGNATURE_INT32, &data.unused.unused_4488);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.gifts[GIFT_MODEST].id);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.gifts[GIFT_GENEROUS].id);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.gifts[GIFT_LAVISH].id);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.gifts[GIFT_MODEST].cost);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.gifts[GIFT_GENEROUS].cost);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.gifts[GIFT_LAVISH].cost);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.kingdom_salary_penalty);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.kingdom_milestone_penalty);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.kingdom_ignored_request_penalty);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.kingdom_last_year);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.kingdom_change);
    iob->bind(BIND_SIGNATURE_INT32, &data.military.native_attack_duration);
    iob->bind(BIND_SIGNATURE_INT32, &data.unused.unused_native_force_attack);
    iob->bind(BIND_SIGNATURE_INT32, &data.buildings.mission_post_operational);
    iob->bind(BIND_SIGNATURE_UINT32, data.buildings.main_native_meeting);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.wage_rate_paid_last_year);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.food_needed_per_month); // 62
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.granaries.understaffed);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.granaries.not_operating);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.granaries.not_operating_with_food);

    for (int i = 0; i < 2; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.unused.unused_44e0[i]);
    }

    iob->bind(BIND_SIGNATURE_INT32, &data.religion.bast_curse_active);
    iob->bind(BIND_SIGNATURE_INT32, &data.unused.unused_44ec);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.ra_150_export_profits_months_left);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.religion.seth_crush_enemy_troops);
    iob->bind(BIND_SIGNATURE_INT32, &data.unused.unused_44f8);
    iob->bind(BIND_SIGNATURE_INT32, &data.religion.angry_message_delay);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.food_consumed_last_month);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.food_produced_last_month);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.food_produced_this_month);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.monument_riot_cause);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.estimated_tax_income);
    iob->bind(BIND_SIGNATURE_INT32, &data.mission.tutorial_senate_built); // ok
    iob->bind(BIND_SIGNATURE_UINT32, data.buildings.distribution_center);
    iob->bind(BIND_SIGNATURE_INT32, &data.buildings.distribution_center_building_id);
    iob->bind(BIND_SIGNATURE_INT32, &data.buildings.distribution_center_placed);

    for (int i = 0; i < 11; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.unused.unused_4524[i]);
    }

    iob->bind(BIND_SIGNATURE_INT8, &data.buildings.fishing_boats_requested);
    iob->bind(BIND_SIGNATURE_INT8, &data.buildings.warships_requested);
    iob->bind(BIND_SIGNATURE_INT8, &data.buildings.transport_ships_requested);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_INT16, &data.figures.enemies);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT8, &data.sentiment.wages);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT16, &data.population.people_in_huts);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.population.people_in_residences);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.figures.kingdome_soldiers);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.kingdome.invasion.duration_day_countdown);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT8, &data.kingdome.invasion.warnings_given);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.invasion.days_until_invasion);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.invasion.retreat_message_shown);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.ratings.monument_destroyed_buildings);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT16, &data.ratings.monument_years_of_monument);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT8, &data.distant_battle.city);
    iob->bind(BIND_SIGNATURE_UINT8, &data.distant_battle.enemy_strength);
    iob->bind(BIND_SIGNATURE_UINT8, &data.distant_battle.roman_strength);
    iob->bind(BIND_SIGNATURE_INT8, &data.distant_battle.months_until_battle);
    iob->bind(BIND_SIGNATURE_INT8, &data.distant_battle.roman_months_to_travel_back);
    iob->bind(BIND_SIGNATURE_INT8, &data.distant_battle.roman_months_to_travel_forth);
    iob->bind(BIND_SIGNATURE_INT8, &data.distant_battle.city_foreign_months_left);
    iob->bind(BIND_SIGNATURE_INT8, &data.buildings.triumphal_arches_available);
    iob->bind(BIND_SIGNATURE_INT8, &data.distant_battle.total_count);
    iob->bind(BIND_SIGNATURE_INT8, &data.distant_battle.won_count);
    iob->bind(BIND_SIGNATURE_INT8, &data.distant_battle.enemy_months_traveled);
    iob->bind(BIND_SIGNATURE_INT8, &data.distant_battle.roman_months_traveled);
    iob->bind(BIND_SIGNATURE_UINT8, &data.military.total_batalions);
    iob->bind(BIND_SIGNATURE_UINT8, &data.military.kingdome_service_batalions);
    iob->bind(BIND_SIGNATURE_UINT8, &data.unused.unknown_458e);
    iob->bind(BIND_SIGNATURE_UINT8, &data.military.total_soldiers);
    iob->bind(BIND_SIGNATURE_INT8, &data.buildings.triumphal_arches_placed);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.die_citizen);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.die_soldier);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.shoot_arrow);
    iob->bind(BIND_SIGNATURE_INT32, &data.buildings.trade_center_building_id);
    iob->bind(BIND_SIGNATURE_INT32, &data.figures.soldiers);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.hit_soldier);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.hit_spear);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.hit_club);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.march_enemy);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.march_horse);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.hit_elephant);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.hit_axe);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.hit_wolf);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.march_wolf);
    iob->bind____skip(10);
    iob->bind(BIND_SIGNATURE_INT8, &data.sentiment.include_huts);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.invasion.count);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.invasion.size);
    iob->bind(BIND_SIGNATURE_UINT16, &data.kingdome.invasion.soldiers_killed);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT8, &data.military.infantry_batalions);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.highest_ever);
    iob->bind(BIND_SIGNATURE_UINT8, &data.finance.estimated_wages);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.resource.wine_types_available);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.ratings.prosperity_max);
    iob->bind____skip(3);
    for (int i = 0; i < 10; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.map.largest_road_networks[i].id); // ????
        iob->bind(BIND_SIGNATURE_INT32, &data.map.largest_road_networks[i].size);
    }
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.second_wine);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.osiris_sank_ships);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.senet_house_has_plays);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.senet_house_message_shown);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.entertainment.pavilion_message_shown);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.emigration_message_shown);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.mission.fired_message_shown);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.mission.victory_message_shown);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.mission.start_saved_game_written);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.mission.tutorial_fire_message_shown);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.mission.tutorial_disease_message_shown);
    iob->bind(BIND_SIGNATURE_INT32, &data.figures.attacking_natives);

    iob->bind____skip(4); // (BIND_SIGNATURE_INT32, &data.buildings.temple_complex_id);
    iob->bind____skip(36);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.expenses.requests_and_festivals);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.expenses.requests_and_festivals);
    iob->bind____skip(64);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.estimated_tax_uncollected);
    iob->bind(BIND_SIGNATURE_UINT32, data.buildings.festival_square);
    iob->bind____skip(4);
    iob->bind____skip(8);
    iob->bind(BIND_SIGNATURE_UINT32, &data.finance.this_year.income.gold_extracted);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.ra_no_traders_months_left);
    iob->bind____skip(3);
    iob->bind____skip(92);
    int reserved;
    iob->bind(BIND_SIGNATURE_INT16, &reserved);

    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.religion.gods[i].happy_ankhs);
    }

    iob->bind____skip(33);
    iob->bind____skip(2); // 2800 --> 0     granary space?
    iob->bind____skip(30);
    iob->bind____skip(2); // 400 --> 0      granary used (game meat)?
    iob->bind____skip(288);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.coverage_common);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.coverage[GOD_OSIRIS]);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.coverage[GOD_RA]);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.coverage[GOD_PTAH]);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.coverage[GOD_SETH]);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.coverage[GOD_BAST]);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.ra_slightly_increased_trading_months_left);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.ra_harshly_reduced_trading_months_left);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.ra_slightly_reduced_trading_months_left);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT16, &data.religion.seth_protect_player_troops);
    iob->bind____skip(6);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.osiris_double_farm_yield_days);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.religion.osiris_flood_will_destroy_active);
    iob->bind____skip(3);
    iob->bind____skip(60);
});

io_buffer* iob_city_data_extra = new io_buffer([](io_buffer* iob, size_t version) {
    auto &data = g_city;
    iob->bind(BIND_SIGNATURE_INT16, &data.unused.faction_bytes[0]);
    iob->bind(BIND_SIGNATURE_INT16, &data.unused.faction_bytes[1]);
    iob->bind(BIND_SIGNATURE_RAW, &data.kingdome.player_name_adversary, MAX_PLAYER_NAME);
    iob->bind(BIND_SIGNATURE_RAW, &data.kingdome.player_name, MAX_PLAYER_NAME);
    iob->bind(BIND_SIGNATURE_INT32, &data.unused.faction_id);
});

io_buffer* iob_city_graph_order = new io_buffer([](io_buffer* iob, size_t version) {
    auto &data = g_city;
    iob->bind(BIND_SIGNATURE_INT32, &data.population.graph_order);
    iob->bind(BIND_SIGNATURE_INT32, &data.unused.unknown_order);
});

const uint8_t* city_player_name() {
    auto &data = g_city;
    return data.kingdome.player_name;
}
void city_set_player_name(const uint8_t* name) {
    auto &data = g_city;
    string_copy(name, data.kingdome.player_name, MAX_PLAYER_NAME);
}
void city_save_campaign_player_name() {
    auto &data = g_city;
    string_copy(data.kingdome.player_name, data.kingdome.campaign_player_name, MAX_PLAYER_NAME);
}
void city_restore_campaign_player_name() {
    auto &data = g_city;
    string_copy(data.kingdome.campaign_player_name, data.kingdome.player_name, MAX_PLAYER_NAME);
}

struct cproperty {
    xstring domain;
    xstring name;

    std::function<bvariant(const xstring &)> handler;
};

bvariant city_get_property(const xstring &domain, const xstring &name) {
    static cproperty cproperties[] = {
        { tags().city, tags().tax_percentage, [] (const xstring &) { return bvariant(g_city.finance.tax_percentage); }},
        { tags().city, tags().population, [] (const xstring &) { return bvariant(g_city.population.population); }},
        { tags().city, tags().treasury, [] (const xstring &) { return bvariant(g_city.finance.treasury); }},
        { tags().rating, tags().culture, [] (const xstring &) { return bvariant(g_city.ratings.culture); }},
        { tags().rating, tags().prosperity, [] (const xstring &) { return bvariant(g_city.ratings.prosperity); }},
        { tags().rating, tags().monument, [] (const xstring &) { return bvariant(g_city.ratings.monument); }},
        { tags().rating, tags().kingdom, [] (const xstring &) { return bvariant(g_city.ratings.kingdom); }},
        { tags().player, tags().rank_name, [] (const xstring &) { return bvariant(ui::str(52, g_city.kingdome.salary_rank + 4)); }},
        { tags().player, tags().salary_amount, [] (const xstring &) { return bvariant(g_city.kingdome.salary_amount); }},
        { tags().city, tags().months_since_festival, [] (const xstring &) { return bvariant(g_city.festival.months_since_festival); }},
    };

    for (const auto &prop : cproperties) {
        if (prop.domain != domain) {
            continue;
        }

        if (prop.name == name) {
            return prop.handler(name);
        }
    }

    return bvariant();
}

bvariant city_t::get_property(const xstring &domain, const xstring &name) const {
    return city_get_property(domain, name);
}

void city_t::environment_t::river_update_flotsam() {
    constexpr int FLOTSAM_RESOURCE_IDS[] = {3, 1, 3, 2, 1, 3, 2, 3, 2, 1, 3, 3, 2, 3, 3, 3, 1, 2, 0, 1};
    constexpr int FLOTSAM_WAIT_TICKS[]  = {10, 50, 100, 130, 200, 250, 400, 430, 500, 600, 70, 750, 820, 830, 900, 980, 1010, 1030, 1200, 1300};

    if (!scenario_map_has_river_entry() || !scenario_map_has_river_exit() || !scenario_map_has_flotsam()) {
        return;
    }

    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (f->state == FIGURE_STATE_ALIVE && f->type == FIGURE_FLOTSAM) {
            return;
        }
    }

    tile2i river_entry = scenario_map_river_entry();
    for (int i = 0; i < 1; i++) {
        figure* f = figure_create(FIGURE_FLOTSAM, river_entry, DIR_0_TOP_RIGHT);
        f->action_state = FIGURE_ACTION_128_FLOTSAM_CREATED;
        f->set_resource((e_resource)FLOTSAM_RESOURCE_IDS[i]);
        f->wait_ticks = FLOTSAM_WAIT_TICKS[i];
        f->allow_move_type = EMOVE_DEEPWATER;
    }
}

void city_t::figures_update_day() {
    figure_valid_do([] (figure &f) {
        f.dcast()->update_day();
    });
}

bool city_t::determine_granary_get_foods(resource_list &foods, int road_network) {
    if (scenario_property_kingdom_supplies_grain()) {
        return false;
    }

    foods.clear();
    buildings_valid_do([&] (building &b) {
        building_granary *granary = b.dcast_granary();
        assert(granary);
        if (!granary->has_road_access()) {
            return;
        }

        if (road_network != granary->road_network()) {
            return;
        }

        int pct_workers = calc_percentage<int>(granary->num_workers(), model_get_building(granary->type())->laborers);
        if (pct_workers < 100 || granary->amount(RESOURCE_NONE) < 100) {
            return;
        }

        if (!granary->is_empty_all()) {
            return;
        }

        for (const auto &r: resource_list::foods) {
            if (granary->is_getting(r.type)) {
                foods[r.type] = 1;
            }
        }
    }, BUILDING_GRANARY);

    return foods.any();
}

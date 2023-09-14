#include "city_data.h"

#include "city/constants.h"
#include "city/data_private.h"
#include "city/gods.h"
#include "game/difficulty.h"
#include "scenario/property.h"
#include "core/game_environment.h"
#include "empire/city.h"
#include "io/io_buffer.h"

#include <core/string.h>
#include <string.h>

const city_data_t* city_data_struct() {
    return &city_data;
}

void city_data_init(void) {
    memset(&city_data, 0, sizeof(struct city_data_t));

    city_data.unused.faction_bytes[0] = 0;
    city_data.unused.faction_bytes[1] = 0;

    city_data.sentiment.value = 60;
    city_data.health.target_value = 50;
    city_data.health.value = 50;
    city_data.unused.unknown_00c0 = 3;
    city_data.labor.wages_kingdome = 30;
    city_data.labor.wages = 30;
    city_data.finance.tax_percentage = 7;
    city_data.trade.caravan_import_resource = RESOURCE_MIN;
    city_data.trade.caravan_backup_import_resource = RESOURCE_MIN;
    city_data.population.monthly.next_index = 0;
    city_data.population.monthly.count = 0;
    city_data.festival.months_since_festival = 1;
    city_data.festival.selected.size = FESTIVAL_SMALL;
    city_data.emperor.gifts[GIFT_MODEST].cost = 0;
    city_data.emperor.gifts[GIFT_GENEROUS].cost = 0;
    city_data.emperor.gifts[GIFT_LAVISH].cost = 0;

    city_gods_reset();
}
void city_data_init_custom_map(void) {
    city_data.unused.faction_id = 1;
    city_data.unused.unknown_00a2 = 1;
    city_data.unused.unknown_00a3 = 1;
    city_data.finance.treasury = difficulty_adjust_money(scenario_initial_funds());
    city_data.finance.last_year.balance = city_data.finance.treasury;
}
void city_data_init_campaign_mission(void) {
    city_data.finance.treasury = difficulty_adjust_money(city_data.finance.treasury);
}

int ALLOWED_FOODS(int i) {
    return city_data.resource.food_types_allowed[i];
}
bool is_food_allowed(int resource) {
    bool result = false;
    for (int i = 0; i < 4; i++) {
        if (ALLOWED_FOODS(i) == resource) {
            result = true;
        }
    }
    // for etc etc todo: other resources?
    return result;
}
void set_allowed_food(int i, int resource) {
    city_data.resource.food_types_allowed[i] = resource;
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
        return full / 100;
    }
}

io_buffer* iob_city_data = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_RAW, &city_data.unused.other_player, 18904);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.unused.unknown_00a0);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.unused.unknown_00a1);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.unused.unknown_00a2);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.unused.unknown_00a3);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.unused.unknown_00a4);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.building.unknown_value);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.unused.unknown_00a7);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.unused.unknown_00a6);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.tax_percentage);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.treasury);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.sentiment.value);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.health.target_value);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.health.value);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.health.num_hospital_workers);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_00c0);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.population);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.population_last_year);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.school_age);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.academy_age);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.total_capacity);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.room_in_houses);
    for (int i = 0; i < 2400; i++)
        iob->bind(BIND_SIGNATURE_INT32, &city_data.population.monthly.values[i]);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.monthly.next_index);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.monthly.count);
    for (int i = 0; i < 100; i++)
        iob->bind(BIND_SIGNATURE_INT16, &city_data.population.at_age[i]);
    for (int i = 0; i < 20; i++)
        iob->bind(BIND_SIGNATURE_INT32, &city_data.population.at_level[i]);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.yearly_births);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.yearly_deaths);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.lost_removal);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.migration.immigration_amount_per_batch);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.migration.emigration_amount_per_batch);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.migration.emigration_queue_size);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.migration.immigration_queue_size);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.lost_homeless);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.last_change);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.average_per_year);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.total_all_years);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.people_in_tents_shacks);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.people_in_villas_palaces);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.total_years);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.yearly_update_requested);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.last_used_house_add);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.last_used_house_remove);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.migration.immigrated_today);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.migration.emigrated_today);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.migration.refused_immigrants_today);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.migration.percentage);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unused_27d0);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.migration.immigration_duration);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.migration.emigration_duration);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.migration.newcomers);
    for (int i = 0; i < 4; i++)
        iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_27e0[i]);
    iob->bind(BIND_SIGNATURE_INT16, &city_data.unused.unknown_27f0);
    iob->bind(BIND_SIGNATURE_INT16, &city_data.resource.last_used_warehouse);
    for (int i = 0; i < 18; i++)
        iob->bind(BIND_SIGNATURE_INT16, &city_data.unused.unknown_27f4[i]);
    iob->bind(BIND_SIGNATURE_UINT16, city_data.map.entry_point.private_access(_X));
    iob->bind(BIND_SIGNATURE_UINT16, city_data.map.entry_point.private_access(_Y));
    iob->bind(BIND_SIGNATURE_INT32, city_data.map.entry_point.private_access(_GRID_OFFSET));
    iob->bind(BIND_SIGNATURE_UINT16, city_data.map.exit_point.private_access(_X));
    iob->bind(BIND_SIGNATURE_UINT16, city_data.map.exit_point.private_access(_Y));
    iob->bind(BIND_SIGNATURE_INT32, city_data.map.exit_point.private_access(_GRID_OFFSET));
    iob->bind(BIND_SIGNATURE_UINT16, city_data.building.palace_point.private_access(_X));
    iob->bind(BIND_SIGNATURE_UINT16, city_data.building.palace_point.private_access(_Y));
    iob->bind(BIND_SIGNATURE_INT32, city_data.building.palace_point.private_access(_GRID_OFFSET));
    iob->bind(BIND_SIGNATURE_INT32, &city_data.building.palace_building_id);
    iob->bind(BIND_SIGNATURE_INT16, &city_data.unused.unknown_2828);
    iob->bind____skip(2);
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &city_data.resource.space_in_warehouses[i + 1]);
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &city_data.resource.stored_in_warehouses[i + 1]);
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &city_data.resource.trade_status[i + 1]);
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &city_data.resource.trading_amount[i + 1]);
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &city_data.resource.mothballed[i + 1]);
    iob->bind(BIND_SIGNATURE_INT16, &city_data.unused.unused_28ca);

    //    iob->bind____skip(20);
    //    for (int i = 0; i < RESOURCES_MAX; i++)
    //        iob->bind(BIND_SIGNATURE_INT16, &city_data.resource.unk_00[i + 1]);
    //    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
    //        iob->bind(BIND_SIGNATURE_INT16, &city_data.resource.granary_food_stored[i]);
    //    iob->bind____skip(28); // temp

    iob->bind____skip(20);
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &city_data.resource.unk_00[i]);
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &city_data.resource.granary_food_stored[i]);
    iob->bind____skip(28); // temp

    int food_index = 0;
    for (int i = 0; i < 4; i++) // reset available foods quick array
        city_data.resource.food_types_allowed[i] = 0;
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &city_data.resource.food_types_available_arr[i]);
        if (city_data.resource.food_types_available_arr[i]) {
            city_data.resource.food_types_allowed[food_index] = i;
            food_index++;
        }
    }
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT8, &city_data.resource.food_types_eaten_arr[i]);

    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT8, &city_data.resource.food_types_arr_unk_00[i]);
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT8, &city_data.resource.food_types_arr_unk_01[i]);

    iob->bind____skip(216);

    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT32, &city_data.resource.stockpiled[i]);

    // TODO: TEMP!!!!
    city_data.resource.food_types_available_num = 0;
    city_data.resource.food_types_eaten_num = 0;

    iob->bind(BIND_SIGNATURE_INT32, &city_data.resource.food_supply_months);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.resource.granaries.operating);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.percentage_plebs);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.working_age);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.labor.workers_available);
    for (int i = 0; i < 10; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &city_data.labor.categories[i].workers_needed);
        iob->bind(BIND_SIGNATURE_INT32, &city_data.labor.categories[i].workers_allocated);
        iob->bind(BIND_SIGNATURE_INT32, &city_data.labor.categories[i].total_houses_covered);
        iob->bind(BIND_SIGNATURE_INT32, &city_data.labor.categories[i].buildings);
        iob->bind(BIND_SIGNATURE_INT32, &city_data.labor.categories[i].priority);
    }
    iob->bind(BIND_SIGNATURE_INT32, &city_data.labor.workers_employed);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.labor.workers_unemployed);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.labor.unemployment_percentage);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.labor.unemployment_percentage_for_senate);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.labor.workers_needed);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.labor.wages);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.labor.wages_kingdome);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_2b6c);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.wages_so_far);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.expenses.wages);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.expenses.wages);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.taxed_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.taxed_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.untaxed_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.untaxed_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.percentage_taxed_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.percentage_taxed_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.percentage_taxed_people);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.yearly.collected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.yearly.collected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.yearly.uncollected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.yearly.uncollected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.income.taxes);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.income.taxes);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.monthly.collected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.monthly.uncollected_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.monthly.collected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.taxes.monthly.uncollected_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.income.exports);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.income.exports);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.expenses.imports);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.expenses.imports);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.interest_so_far);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.expenses.interest);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.expenses.interest);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.expenses.stolen);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.expenses.stolen);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.expenses.construction);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.expenses.construction);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.expenses.salary);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.expenses.salary);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.salary_amount);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.salary_rank);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.salary_so_far);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.income.total);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.income.total);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.expenses.total);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.expenses.total);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.net_in_out);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.net_in_out);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.balance);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.balance);
    for (int i = 0; i < 1400; i++)
        iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_2c20[i]);
    for (int i = 0; i < 8; i++)
        iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.houses_requiring_unknown_to_evolve[i]); // ????
    iob->bind(BIND_SIGNATURE_INT32, &city_data.trade.caravan_import_resource);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.trade.caravan_backup_import_resource);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.culture);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.prosperity);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.monument);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.kingdom);
    iob->bind____skip(8);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.prosperity_treasury_last_year);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.culture_points.entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.culture_points.religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.culture_points.school);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.culture_points.library);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.culture_points.academy);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.monument_num_criminals);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.monument_num_rioters);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.fountain);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.well);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.more_entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.more_education);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.education);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.requiring.school);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.requiring.library);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_4284);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.apothecary);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.dentist);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.food);

    for (int i = 0; i < 2; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_4294[i]);
    }

    iob->bind(BIND_SIGNATURE_INT32, &city_data.building.hippodrome_placed);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.mortuary);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.physician);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.requiring.dentist);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.requiring.water_supply);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.requiring.physician);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.second_religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.third_religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.requiring.religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.entertainment.theater_shows);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.entertainment.theater_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.entertainment.amphitheater_shows);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.entertainment.amphitheater_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.entertainment.colosseum_shows);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.entertainment.colosseum_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.entertainment.hippodrome_shows);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.entertainment.hippodrome_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.entertainment.venue_needing_shows);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.culture.average_entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.festival.months_since_festival); // ok
    for (int i = 0; i < MAX_GODS; i++)
        iob->bind(BIND_SIGNATURE_UINT8, &city_data.religion.gods[i].target_mood);
    iob->bind____skip(5);
    for (int i = 0; i < MAX_GODS; i++)
        iob->bind(BIND_SIGNATURE_UINT8, &city_data.religion.gods[i].mood);
    iob->bind____skip(5);
    for (int i = 0; i < MAX_GODS; i++)
        iob->bind(BIND_SIGNATURE_UINT8, &city_data.religion.gods[i].wrath_bolts);
    iob->bind____skip(5);
    iob->bind____skip(15);
    iob->bind____skip(35);
    //    for (int i = 0; i < MAX_GODS; i++)
    //        city_data.religion.gods[i].unused1 = main->read_i8();
    //    for (int i = 0; i < MAX_GODS; i++)
    //        city_data.religion.gods[i].unused2 = main->read_i8();
    //    for (int i = 0; i < MAX_GODS; i++)
    //        city_data.religion.gods[i].unused3 = main->read_i8();
    for (int i = 0; i < MAX_GODS; i++)
        iob->bind(BIND_SIGNATURE_UINT32, &city_data.religion.gods[i].months_since_festival);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.religion.least_happy_god);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_4334);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.migration.no_immigration_cause);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.sentiment.protesters);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.sentiment.criminals);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.health);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.education);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.figure.rioters);
    iob->bind____skip(20);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.selected);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.culture_explanation);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.prosperity_explanation);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.monument_explanation);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.kingdom_explanation);
    iob->bind____skip(8);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.player_rank);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.personal_savings); // ok
                                                                          //    for (int i = 0; i < 2; i++)
    //        iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_4374[i]);
    //    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.income.donated);
    //    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.income.donated);
    //        for (int i = 0; i < 2; i++)
    //            iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_4374[i]);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.income.donated);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.income.donated);
    
    for (int i = 0; i < 2; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_4374[i]);
    }
    
    for (int i = 0; i < 10; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &city_data.building.working_dock_ids[i]);
    }

    iob->bind(BIND_SIGNATURE_INT16, &city_data.building.temple_complex_placed);
    iob->bind(BIND_SIGNATURE_UINT8, &city_data.env.has_animals);
    iob->bind(BIND_SIGNATURE_UINT8, &city_data.figure.animals_number);

    for (int i = 0; i < 3; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &city_data.unused.unknown_439c[i]);
    }

    iob->bind____skip(2);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT16, &city_data.building.palace_placed);
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

    for (int i = 0; i < 2; i++)
        iob->bind(BIND_SIGNATURE_INT8, &city_data.unused.padding_43b2[i]);
    iob->bind(BIND_SIGNATURE_INT16, &city_data.finance.stolen_this_year);
    iob->bind(BIND_SIGNATURE_INT16, &city_data.finance.stolen_last_year);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.trade.docker_import_resource);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.trade.docker_export_resource);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.debt_state);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.months_in_debt);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.cheated_money);
    iob->bind(BIND_SIGNATURE_INT8, city_data.building.barracks.private_access(_X));
    iob->bind(BIND_SIGNATURE_INT8, city_data.building.barracks.private_access(_Y));
    iob->bind(BIND_SIGNATURE_INT16, city_data.building.barracks.private_access(_GRID_OFFSET));
    iob->bind(BIND_SIGNATURE_INT32, &city_data.building.barracks_building_id);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.building.barracks_placed);
    for (int i = 0; i < 5; i++)
        iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_43d8[i]);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.lost_troop_request);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_43f0);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.mission.has_won);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.mission.continue_months_left);
    iob->bind(BIND_SIGNATURE_INT32,
              &city_data.mission.continue_months_chosen); // wrong? hmm... 300 became 120? is it the wages?
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.wage_rate_paid_this_year);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.expenses.tribute); // ok
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.expenses.tribute);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.tribute_not_paid_last_year);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.festival.selected.god);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.festival.selected.size); // ????
    iob->bind(BIND_SIGNATURE_INT32, &city_data.festival.planned.size);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.festival.planned.months_to_go);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.festival.planned.god);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.festival.small_cost); // 23 --> 22 ??????
    iob->bind(BIND_SIGNATURE_INT32, &city_data.festival.large_cost); // 46 --> 45
    iob->bind(BIND_SIGNATURE_INT32, &city_data.festival.grand_cost); // 93 --> 90
    iob->bind(BIND_SIGNATURE_INT32, &city_data.festival.grand_alcohol);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.festival.not_enough_alcohol);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.culture.average_religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.culture.average_education);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.culture.average_health);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.culture.religion_coverage);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.festival.first_festival_effect_months);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.festival.second_festival_effect_months);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unused_4454);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.sentiment.unemployment);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.sentiment.previous_value); // ok
    iob->bind(BIND_SIGNATURE_INT32, &city_data.sentiment.message_delay);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.sentiment.low_mood_cause);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.figure.security_breach_duration);
    for (int i = 0; i < 4; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_446c[i]);
    }
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.selected_gift_size);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.months_since_gift); // ok
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.gift_overdose_penalty);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unused_4488);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.gifts[GIFT_MODEST].id);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.gifts[GIFT_GENEROUS].id);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.gifts[GIFT_LAVISH].id);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.gifts[GIFT_MODEST].cost);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.gifts[GIFT_GENEROUS].cost);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.gifts[GIFT_LAVISH].cost);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.kingdom_salary_penalty);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.kingdom_milestone_penalty);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.kingdom_ignored_request_penalty);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.kingdom_last_year);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.kingdom_change);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.military.native_attack_duration);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unused_native_force_attack);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.building.mission_post_operational);
    iob->bind(BIND_SIGNATURE_INT32, city_data.building.main_native_meeting.private_access(_X));
    iob->bind(BIND_SIGNATURE_INT32, city_data.building.main_native_meeting.private_access(_Y));
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.wage_rate_paid_last_year);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.resource.food_needed_per_month); // 62
    iob->bind(BIND_SIGNATURE_INT32, &city_data.resource.granaries.understaffed);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.resource.granaries.not_operating);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.resource.granaries.not_operating_with_food);
    for (int i = 0; i < 2; i++)
        iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unused_44e0[i]);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.religion.bast_curse_active);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unused_44ec);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.religion.ra_150_export_profits_months_left);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.religion.seth_crush_enemy_troops);
    city_data.religion.osiris_double_farm_yield = false; // todo
    iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unused_44f8);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.religion.angry_message_delay);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.resource.food_consumed_last_month);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.resource.food_produced_last_month);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.resource.food_produced_this_month);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.monument_riot_cause);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.estimated_tax_income);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.mission.tutorial_senate_built); // ok
    iob->bind(BIND_SIGNATURE_INT8, city_data.building.distribution_center.private_access(_X));
    iob->bind(BIND_SIGNATURE_INT8, city_data.building.distribution_center.private_access(_Y));
    iob->bind(BIND_SIGNATURE_INT16, city_data.building.distribution_center.private_access(_GRID_OFFSET));
    iob->bind(BIND_SIGNATURE_INT32, &city_data.building.distribution_center_building_id);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.building.distribution_center_placed);
    for (int i = 0; i < 11; i++)
        iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unused_4524[i]);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.building.shipyard_boats_requested);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.figure.enemies);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.sentiment.wages);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.people_in_tents);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.people_in_large_insula_and_above);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.figure.imperial_soldiers);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.invasion.duration_day_countdown);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.invasion.warnings_given);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.invasion.days_until_invasion);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.invasion.retreat_message_shown);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.monument_destroyed_buildings);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.monument_years_of_monument);
    iob->bind(BIND_SIGNATURE_UINT8, &city_data.distant_battle.city);
    iob->bind(BIND_SIGNATURE_UINT8, &city_data.distant_battle.enemy_strength);
    iob->bind(BIND_SIGNATURE_UINT8, &city_data.distant_battle.roman_strength);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.distant_battle.months_until_battle);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.distant_battle.roman_months_to_travel_back);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.distant_battle.roman_months_to_travel_forth);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.distant_battle.city_foreign_months_left);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.building.triumphal_arches_available);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.distant_battle.total_count);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.distant_battle.won_count);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.distant_battle.enemy_months_traveled);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.distant_battle.roman_months_traveled);
    iob->bind(BIND_SIGNATURE_UINT8, &city_data.military.total_legions);
    iob->bind(BIND_SIGNATURE_UINT8, &city_data.military.empire_service_legions);
    iob->bind(BIND_SIGNATURE_UINT8, &city_data.unused.unknown_458e);
    iob->bind(BIND_SIGNATURE_UINT8, &city_data.military.total_soldiers);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.building.triumphal_arches_placed);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.sound.die_citizen);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.sound.die_soldier);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.sound.shoot_arrow);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.building.trade_center_building_id);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.figure.soldiers);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.sound.hit_soldier);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.sound.hit_spear);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.sound.hit_club);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.sound.march_enemy);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.sound.march_horse);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.sound.hit_elephant);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.sound.hit_axe);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.sound.hit_wolf);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.sound.march_wolf);
    iob->bind____skip(10);
    iob->bind(BIND_SIGNATURE_INT8, &city_data.sentiment.include_tents);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.invasion.count);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.invasion.size);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.emperor.invasion.soldiers_killed);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.military.legionary_legions);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.highest_ever);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.estimated_wages);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.resource.wine_types_available);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.ratings.prosperity_max);
    for (int i = 0; i < 10; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &city_data.map.largest_road_networks[i].id); // ????
        iob->bind(BIND_SIGNATURE_INT32, &city_data.map.largest_road_networks[i].size);
    }
    iob->bind(BIND_SIGNATURE_INT32, &city_data.houses.missing.second_wine);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.religion.osiris_sank_ships);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.entertainment.hippodrome_has_race);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.entertainment.hippodrome_message_shown);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.entertainment.colosseum_message_shown);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.migration.emigration_message_shown);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.mission.fired_message_shown);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.mission.victory_message_shown);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.mission.start_saved_game_written);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.mission.tutorial_fire_message_shown);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.mission.tutorial_disease_message_shown);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.figure.attacking_natives);

    iob->bind(BIND_SIGNATURE_INT32, &city_data.building.temple_complex_id);
    iob->bind____skip(36);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.last_year.expenses.requests_and_festivals);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.expenses.requests_and_festivals);
    iob->bind____skip(64);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.estimated_tax_uncollected);
    iob->bind(BIND_SIGNATURE_INT32, city_data.building.festival_square.private_access(_X));
    iob->bind(BIND_SIGNATURE_INT32, city_data.building.festival_square.private_access(_Y));
    iob->bind____skip(8);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.finance.this_year.income.gold_extracted);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.religion.ra_no_traders_months_left);
    iob->bind____skip(92);
    iob->bind(BIND_SIGNATURE_INT16, &city_data.building.festival_square_placed);
    for (int i = 0; i < MAX_GODS; i++)
        iob->bind(BIND_SIGNATURE_UINT8, &city_data.religion.gods[i].happy_ankhs);
    iob->bind____skip(33);
    iob->bind____skip(2); // 2800 --> 0     granary space?
    iob->bind____skip(30);
    iob->bind____skip(2); // 400 --> 0      granary used (game meat)?
    iob->bind____skip(290);
    iob->bind____skip(4); // something related to Bast plague (minor curse)
    iob->bind(BIND_SIGNATURE_INT16, &city_data.religion.ra_slightly_increased_trading_months_left);
    iob->bind(BIND_SIGNATURE_INT16, &city_data.religion.ra_harshly_reduced_trading_months_left);
    iob->bind(BIND_SIGNATURE_INT16, &city_data.religion.ra_slightly_reduced_trading_months_left);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT16, &city_data.religion.seth_protect_player_troops);
    iob->bind____skip(6);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.religion.osiris_double_farm_yield);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.religion.osiris_flood_will_destroy_active);
    iob->bind____skip(60);
    //    iob->bind____skip(378);
});
io_buffer* iob_city_data_extra = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT16, &city_data.unused.faction_bytes[0]);
    iob->bind(BIND_SIGNATURE_INT16, &city_data.unused.faction_bytes[1]);
    iob->bind(BIND_SIGNATURE_RAW, &city_data.emperor.player_name_adversary, MAX_PLAYER_NAME);
    iob->bind(BIND_SIGNATURE_RAW, &city_data.emperor.player_name, MAX_PLAYER_NAME);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.faction_id);
});
io_buffer* iob_city_graph_order = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT32, &city_data.population.graph_order);
    iob->bind(BIND_SIGNATURE_INT32, &city_data.unused.unknown_order);
});

const uint8_t* city_player_name(void) {
    return city_data.emperor.player_name;
}
void city_set_player_name(const uint8_t* name) {
    string_copy(name, city_data.emperor.player_name, MAX_PLAYER_NAME);
}
void city_save_campaign_player_name(void) {
    string_copy(city_data.emperor.player_name, city_data.emperor.campaign_player_name, MAX_PLAYER_NAME);
}
void city_restore_campaign_player_name(void) {
    string_copy(city_data.emperor.campaign_player_name, city_data.emperor.player_name, MAX_PLAYER_NAME);
}
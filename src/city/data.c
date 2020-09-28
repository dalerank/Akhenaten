#include "data.h"

#include "city/constants.h"
#include "city/data_private.h"
#include "city/gods.h"
#include "game/difficulty.h"
#include "scenario/property.h"

#include <string.h>

void city_data_init(void)
{
    memset(&city_data, 0, sizeof(struct city_data_t));

    city_data.unused.faction_bytes[0] = 0;
    city_data.unused.faction_bytes[1] = 0;

    city_data.sentiment.value = 60;
    city_data.health.target_value = 50;
    city_data.health.value = 50;
    city_data.unused.unknown_00c0 = 3;
    city_data.labor.wages_rome = 30;
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

void city_data_init_scenario(void)
{
    city_data.unused.faction_id = 1;
    city_data.unused.unknown_00a2 = 1;
    city_data.unused.unknown_00a3 = 1;
    city_data.finance.treasury = difficulty_adjust_money(scenario_initial_funds());
    city_data.finance.last_year.balance = city_data.finance.treasury;
}

void city_data_init_campaign_mission(void)
{
    city_data.finance.treasury = difficulty_adjust_money(city_data.finance.treasury);
}

static void save_main_data(buffer *main)
{
    main->write_raw(city_data.unused.other_player, 18068);
    main->write_i8(city_data.unused.unknown_00a0);
    main->write_i8(city_data.unused.unknown_00a1);
    main->write_i8(city_data.unused.unknown_00a2);
    main->write_i8(city_data.unused.unknown_00a3);
    main->write_i8(city_data.unused.unknown_00a4);
    main->write_i8(city_data.building.unknown_value);
    main->write_i8(city_data.unused.unknown_00a6);
    main->write_i8(city_data.unused.unknown_00a7);
    main->write_i32(city_data.finance.tax_percentage);
    main->write_i32(city_data.finance.treasury);
    main->write_i32(city_data.sentiment.value);
    main->write_i32(city_data.health.target_value);
    main->write_i32(city_data.health.value);
    main->write_i32(city_data.health.num_hospital_workers);
    main->write_i32(city_data.unused.unknown_00c0);
    main->write_i32(city_data.population.population);
    main->write_i32(city_data.population.population_last_year);
    main->write_i32(city_data.population.school_age);
    main->write_i32(city_data.population.academy_age);
    main->write_i32(city_data.population.total_capacity);
    main->write_i32(city_data.population.room_in_houses);
    for (int i = 0; i < 2400; i++) {
        main->write_i32(city_data.population.monthly.values[i]);
    }
    main->write_i32(city_data.population.monthly.next_index);
    main->write_i32(city_data.population.monthly.count);
    for (int i = 0; i < 100; i++) {
        main->write_i16(city_data.population.at_age[i]);
    }
    for (int i = 0; i < 20; i++) {
        main->write_i32(city_data.population.at_level[i]);
    }
    main->write_i32(city_data.population.yearly_births);
    main->write_i32(city_data.population.yearly_deaths);
    main->write_i32(city_data.population.lost_removal);
    main->write_i32(city_data.migration.immigration_amount_per_batch);
    main->write_i32(city_data.migration.emigration_amount_per_batch);
    main->write_i32(city_data.migration.emigration_queue_size);
    main->write_i32(city_data.migration.immigration_queue_size);
    main->write_i32(city_data.population.lost_homeless);
    main->write_i32(city_data.population.last_change);
    main->write_i32(city_data.population.average_per_year);
    main->write_i32(city_data.population.total_all_years);
    main->write_i32(city_data.population.people_in_tents_shacks);
    main->write_i32(city_data.population.people_in_villas_palaces);
    main->write_i32(city_data.population.total_years);
    main->write_i32(city_data.population.yearly_update_requested);
    main->write_i32(city_data.population.last_used_house_add);
    main->write_i32(city_data.population.last_used_house_remove);
    main->write_i32(city_data.migration.immigrated_today);
    main->write_i32(city_data.migration.emigrated_today);
    main->write_i32(city_data.migration.refused_immigrants_today);
    main->write_i32(city_data.migration.percentage);
    main->write_i32(city_data.unused.unused_27d0);
    main->write_i32(city_data.migration.immigration_duration);
    main->write_i32(city_data.migration.emigration_duration);
    main->write_i32(city_data.migration.newcomers);
    for (int i = 0; i < 4; i++) {
        main->write_i32(city_data.unused.unknown_27e0[i]);
    }
    main->write_i16(city_data.unused.unknown_27f0);
    main->write_i16(city_data.resource.last_used_warehouse);
    for (int i = 0; i < 18; i++) {
        main->write_i16(city_data.unused.unknown_27f4[i]);
    }
    main->write_u8(city_data.map.entry_point.x);
    main->write_u8(city_data.map.entry_point.y);
    main->write_i16(city_data.map.entry_point.grid_offset);
    main->write_u8(city_data.map.exit_point.x);
    main->write_u8(city_data.map.exit_point.y);
    main->write_i16(city_data.map.exit_point.grid_offset);
    main->write_u8(city_data.building.senate_x);
    main->write_u8(city_data.building.senate_y);
    main->write_i16(city_data.building.senate_grid_offset);
    main->write_i32(city_data.building.senate_building_id);
    main->write_i16(city_data.unused.unknown_2828);
    for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++) {
        main->write_i16(city_data.resource.space_in_warehouses[i]);
    }
    for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++) {
        main->write_i16(city_data.resource.stored_in_warehouses[i]);
    }
    for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++) {
        main->write_i16(city_data.resource.trade_status[i]);
    }
    for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++) {
        main->write_i16(city_data.resource.export_over[i]);
    }
    for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++) {
        main->write_i16(city_data.resource.mothballed[i]);
    }
    main->write_i16(city_data.unused.unused_28ca);
    for (int i = 0; i < RESOURCE_MAX_FOOD[GAME_ENV]; i++) {
        main->write_i32(city_data.resource.granary_food_stored[i]);
    }
    for (int i = 0; i < 6; i++) {
        main->write_i32(city_data.resource.stored_in_workshops[i]);
    }
    for (int i = 0; i < 6; i++) {
        main->write_i32(city_data.resource.space_in_workshops[i]);
    }
    main->write_i32(city_data.resource.granary_total_stored);
    main->write_i32(city_data.resource.food_types_available);
    main->write_i32(city_data.resource.food_types_eaten);
    for (int i = 0; i < 272; i++) {
        main->write_i8(city_data.unused.unknown_2924[i]);
    }
    for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++) {
        main->write_i32(city_data.resource.stockpiled[i]);
    }
    main->write_i32(city_data.resource.food_supply_months);
    main->write_i32(city_data.resource.granaries.operating);
    main->write_i32(city_data.population.percentage_plebs);
    main->write_i32(city_data.population.working_age);
    main->write_i32(city_data.labor.workers_available);
    for (int i = 0; i < 10; i++) {
        main->write_i32(city_data.labor.categories[i].workers_needed);
        main->write_i32(city_data.labor.categories[i].workers_allocated);
        main->write_i32(city_data.labor.categories[i].total_houses_covered);
        main->write_i32(city_data.labor.categories[i].buildings);
        main->write_i32(city_data.labor.categories[i].priority);
    }
    main->write_i32(city_data.labor.workers_employed);
    main->write_i32(city_data.labor.workers_unemployed);
    main->write_i32(city_data.labor.unemployment_percentage);
    main->write_i32(city_data.labor.unemployment_percentage_for_senate);
    main->write_i32(city_data.labor.workers_needed);
    main->write_i32(city_data.labor.wages);
    main->write_i32(city_data.labor.wages_rome);
    main->write_i32(city_data.unused.unknown_2b6c);
    main->write_i32(city_data.finance.wages_so_far);
    main->write_i32(city_data.finance.this_year.expenses.wages);
    main->write_i32(city_data.finance.last_year.expenses.wages);
    main->write_i32(city_data.taxes.taxed_plebs);
    main->write_i32(city_data.taxes.taxed_patricians);
    main->write_i32(city_data.taxes.untaxed_plebs);
    main->write_i32(city_data.taxes.untaxed_patricians);
    main->write_i32(city_data.taxes.percentage_taxed_plebs);
    main->write_i32(city_data.taxes.percentage_taxed_patricians);
    main->write_i32(city_data.taxes.percentage_taxed_people);
    main->write_i32(city_data.taxes.yearly.collected_plebs);
    main->write_i32(city_data.taxes.yearly.collected_patricians);
    main->write_i32(city_data.taxes.yearly.uncollected_plebs);
    main->write_i32(city_data.taxes.yearly.uncollected_patricians);
    main->write_i32(city_data.finance.this_year.income.taxes);
    main->write_i32(city_data.finance.last_year.income.taxes);
    main->write_i32(city_data.taxes.monthly.collected_plebs);
    main->write_i32(city_data.taxes.monthly.uncollected_plebs);
    main->write_i32(city_data.taxes.monthly.collected_patricians);
    main->write_i32(city_data.taxes.monthly.uncollected_patricians);
    main->write_i32(city_data.finance.this_year.income.exports);
    main->write_i32(city_data.finance.last_year.income.exports);
    main->write_i32(city_data.finance.this_year.expenses.imports);
    main->write_i32(city_data.finance.last_year.expenses.imports);
    main->write_i32(city_data.finance.interest_so_far);
    main->write_i32(city_data.finance.last_year.expenses.interest);
    main->write_i32(city_data.finance.this_year.expenses.interest);
    main->write_i32(city_data.finance.last_year.expenses.sundries);
    main->write_i32(city_data.finance.this_year.expenses.sundries);
    main->write_i32(city_data.finance.last_year.expenses.construction);
    main->write_i32(city_data.finance.this_year.expenses.construction);
    main->write_i32(city_data.finance.last_year.expenses.salary);
    main->write_i32(city_data.finance.this_year.expenses.salary);
    main->write_i32(city_data.emperor.salary_amount);
    main->write_i32(city_data.emperor.salary_rank);
    main->write_i32(city_data.finance.salary_so_far);
    main->write_i32(city_data.finance.last_year.income.total);
    main->write_i32(city_data.finance.this_year.income.total);
    main->write_i32(city_data.finance.last_year.expenses.total);
    main->write_i32(city_data.finance.this_year.expenses.total);
    main->write_i32(city_data.finance.last_year.net_in_out);
    main->write_i32(city_data.finance.this_year.net_in_out);
    main->write_i32(city_data.finance.last_year.balance);
    main->write_i32(city_data.finance.this_year.balance);
    for (int i = 0; i < 1400; i++) {
        main->write_i32(city_data.unused.unknown_2c20[i]);
    }
    for (int i = 0; i < 8; i++) {
        main->write_i32(city_data.unused.houses_requiring_unknown_to_evolve[i]);
    }
    main->write_i32(city_data.trade.caravan_import_resource);
    main->write_i32(city_data.trade.caravan_backup_import_resource);
    main->write_i32(city_data.ratings.culture);
    main->write_i32(city_data.ratings.prosperity);
    main->write_i32(city_data.ratings.peace);
    main->write_i32(city_data.ratings.favor);
    for (int i = 0; i < 4; i++) {
        main->write_i32(city_data.unused.unknown_4238[i]);
    }
    main->write_i32(city_data.ratings.prosperity_treasury_last_year);
    main->write_i32(city_data.ratings.culture_points.theater);
    main->write_i32(city_data.ratings.culture_points.religion);
    main->write_i32(city_data.ratings.culture_points.school);
    main->write_i32(city_data.ratings.culture_points.library);
    main->write_i32(city_data.ratings.culture_points.academy);
    main->write_i32(city_data.ratings.peace_num_criminals);
    main->write_i32(city_data.ratings.peace_num_rioters);
    main->write_i32(city_data.houses.missing.fountain);
    main->write_i32(city_data.houses.missing.well);
    main->write_i32(city_data.houses.missing.more_entertainment);
    main->write_i32(city_data.houses.missing.more_education);
    main->write_i32(city_data.houses.missing.education);
    main->write_i32(city_data.houses.requiring.school);
    main->write_i32(city_data.houses.requiring.library);
    main->write_i32(city_data.unused.unknown_4284);
    main->write_i32(city_data.houses.missing.barber);
    main->write_i32(city_data.houses.missing.bathhouse);
    main->write_i32(city_data.houses.missing.food);
    for (int i = 0; i < 2; i++) {
        main->write_i32(city_data.unused.unknown_4294[i]);
    }
    main->write_i32(city_data.building.hippodrome_placed);
    main->write_i32(city_data.houses.missing.clinic);
    main->write_i32(city_data.houses.missing.hospital);
    main->write_i32(city_data.houses.requiring.barber);
    main->write_i32(city_data.houses.requiring.bathhouse);
    main->write_i32(city_data.houses.requiring.clinic);
    main->write_i32(city_data.houses.missing.religion);
    main->write_i32(city_data.houses.missing.second_religion);
    main->write_i32(city_data.houses.missing.third_religion);
    main->write_i32(city_data.houses.requiring.religion);
    main->write_i32(city_data.entertainment.theater_shows);
    main->write_i32(city_data.entertainment.theater_no_shows_weighted);
    main->write_i32(city_data.entertainment.amphitheater_shows);
    main->write_i32(city_data.entertainment.amphitheater_no_shows_weighted);
    main->write_i32(city_data.entertainment.colosseum_shows);
    main->write_i32(city_data.entertainment.colosseum_no_shows_weighted);
    main->write_i32(city_data.entertainment.hippodrome_shows);
    main->write_i32(city_data.entertainment.hippodrome_no_shows_weighted);
    main->write_i32(city_data.entertainment.venue_needing_shows);
    main->write_i32(city_data.culture.average_entertainment);
    main->write_i32(city_data.houses.missing.entertainment);
    main->write_i32(city_data.festival.months_since_festival);
    for (int i = 0; i < MAX_GODS; i++) {
        main->write_i8(city_data.religion.gods[i].target_happiness);
    }
    for (int i = 0; i < MAX_GODS; i++) {
        main->write_i8(city_data.religion.gods[i].happiness);
    }
    for (int i = 0; i < MAX_GODS; i++) {
        main->write_i8(city_data.religion.gods[i].wrath_bolts);
    }
    for (int i = 0; i < MAX_GODS; i++) {
        main->write_i8(city_data.religion.gods[i].blessing_done);
    }
    for (int i = 0; i < MAX_GODS; i++) {
        main->write_i8(city_data.religion.gods[i].small_curse_done);
    }
    for (int i = 0; i < MAX_GODS; i++) {
        main->write_i8(city_data.religion.gods[i].unused1);
    }
    for (int i = 0; i < MAX_GODS; i++) {
        main->write_i8(city_data.religion.gods[i].unused2);
    }
    for (int i = 0; i < MAX_GODS; i++) {
        main->write_i8(city_data.religion.gods[i].unused3);
    }
    for (int i = 0; i < MAX_GODS; i++) {
        main->write_i32(city_data.religion.gods[i].months_since_festival);
    }
    main->write_i32(city_data.religion.least_happy_god);
    main->write_i32(city_data.unused.unknown_4334);
    main->write_i32(city_data.migration.no_immigration_cause);
    main->write_i32(city_data.sentiment.protesters);
    main->write_i32(city_data.sentiment.criminals);
    main->write_i32(city_data.houses.health);
    main->write_i32(city_data.houses.religion);
    main->write_i32(city_data.houses.education);
    main->write_i32(city_data.houses.entertainment);
    main->write_i32(city_data.figure.rioters);
    main->write_i32(city_data.ratings.selected);
    main->write_i32(city_data.ratings.culture_explanation);
    main->write_i32(city_data.ratings.prosperity_explanation);
    main->write_i32(city_data.ratings.peace_explanation);
    main->write_i32(city_data.ratings.favor_explanation);
    main->write_i32(city_data.emperor.player_rank);
    main->write_i32(city_data.emperor.personal_savings);
    for (int i = 0; i < 2; i++) {
        main->write_i32(city_data.unused.unknown_4374[i]);
    }
    main->write_i32(city_data.finance.last_year.income.donated);
    main->write_i32(city_data.finance.this_year.income.donated);
    main->write_i32(city_data.emperor.donate_amount);
    for (int i = 0; i < 10; i++) {
        main->write_i16(city_data.building.working_dock_ids[i]);
    }
    for (int i = 0; i < 3; i++) {
        main->write_i16(city_data.unused.unknown_439c[i]);
    }
    main->write_i16(city_data.figure.animals);
    main->write_i16(city_data.trade.num_sea_routes);
    main->write_i16(city_data.trade.num_land_routes);
    main->write_i16(city_data.trade.sea_trade_problem_duration);
    main->write_i16(city_data.trade.land_trade_problem_duration);
    main->write_i16(city_data.building.working_docks);
    main->write_i16(city_data.building.senate_placed);
    main->write_i16(city_data.building.working_wharfs);
    for (int i = 0; i < 2; i++) {
        main->write_i8(city_data.unused.padding_43b2[i]);
    }
    main->write_i16(city_data.finance.stolen_this_year);
    main->write_i16(city_data.finance.stolen_last_year);
    main->write_i32(city_data.trade.docker_import_resource);
    main->write_i32(city_data.trade.docker_export_resource);
    main->write_i32(city_data.emperor.debt_state);
    main->write_i32(city_data.emperor.months_in_debt);
    main->write_i32(city_data.finance.cheated_money);
    main->write_i8(city_data.building.barracks_x);
    main->write_i8(city_data.building.barracks_y);
    main->write_i16(city_data.building.barracks_grid_offset);
    main->write_i32(city_data.building.barracks_building_id);
    main->write_i32(city_data.building.barracks_placed);
    for (int i = 0; i < 5; i++) {
        main->write_i32(city_data.unused.unknown_43d8[i]);
    }
    main->write_i32(city_data.population.lost_troop_request);
    main->write_i32(city_data.unused.unknown_43f0);
    main->write_i32(city_data.mission.has_won);
    main->write_i32(city_data.mission.continue_months_left);
    main->write_i32(city_data.mission.continue_months_chosen);
    main->write_i32(city_data.finance.wage_rate_paid_this_year);
    main->write_i32(city_data.finance.this_year.expenses.tribute);
    main->write_i32(city_data.finance.last_year.expenses.tribute);
    main->write_i32(city_data.finance.tribute_not_paid_last_year);
    main->write_i32(city_data.finance.tribute_not_paid_total_years);
    main->write_i32(city_data.festival.selected.god);
    main->write_i32(city_data.festival.selected.size);
    main->write_i32(city_data.festival.planned.size);
    main->write_i32(city_data.festival.planned.months_to_go);
    main->write_i32(city_data.festival.planned.god);
    main->write_i32(city_data.festival.small_cost);
    main->write_i32(city_data.festival.large_cost);
    main->write_i32(city_data.festival.grand_cost);
    main->write_i32(city_data.festival.grand_wine);
    main->write_i32(city_data.festival.not_enough_wine);
    main->write_i32(city_data.culture.average_religion);
    main->write_i32(city_data.culture.average_education);
    main->write_i32(city_data.culture.average_health);
    main->write_i32(city_data.culture.religion_coverage);
    main->write_i32(city_data.festival.first_festival_effect_months);
    main->write_i32(city_data.festival.second_festival_effect_months);
    main->write_i32(city_data.unused.unused_4454);
    main->write_i32(city_data.sentiment.unemployment);
    main->write_i32(city_data.sentiment.previous_value);
    main->write_i32(city_data.sentiment.message_delay);
    main->write_i32(city_data.sentiment.low_mood_cause);
    main->write_i32(city_data.figure.security_breach_duration);
    for (int i = 0; i < 4; i++) {
        main->write_i32(city_data.unused.unknown_446c[i]);
    }
    main->write_i32(city_data.emperor.selected_gift_size);
    main->write_i32(city_data.emperor.months_since_gift);
    main->write_i32(city_data.emperor.gift_overdose_penalty);
    main->write_i32(city_data.unused.unused_4488);
    main->write_i32(city_data.emperor.gifts[GIFT_MODEST].id);
    main->write_i32(city_data.emperor.gifts[GIFT_GENEROUS].id);
    main->write_i32(city_data.emperor.gifts[GIFT_LAVISH].id);
    main->write_i32(city_data.emperor.gifts[GIFT_MODEST].cost);
    main->write_i32(city_data.emperor.gifts[GIFT_GENEROUS].cost);
    main->write_i32(city_data.emperor.gifts[GIFT_LAVISH].cost);
    main->write_i32(city_data.ratings.favor_salary_penalty);
    main->write_i32(city_data.ratings.favor_milestone_penalty);
    main->write_i32(city_data.ratings.favor_ignored_request_penalty);
    main->write_i32(city_data.ratings.favor_last_year);
    main->write_i32(city_data.ratings.favor_change);
    main->write_i32(city_data.military.native_attack_duration);
    main->write_i32(city_data.unused.unused_native_force_attack);
    main->write_i32(city_data.building.mission_post_operational);
    main->write_i32(city_data.building.main_native_meeting.x);
    main->write_i32(city_data.building.main_native_meeting.y);
    main->write_i32(city_data.finance.wage_rate_paid_last_year);
    main->write_i32(city_data.resource.food_needed_per_month);
    main->write_i32(city_data.resource.granaries.understaffed);
    main->write_i32(city_data.resource.granaries.not_operating);
    main->write_i32(city_data.resource.granaries.not_operating_with_food);
    for (int i = 0; i < 2; i++) {
        main->write_i32(city_data.unused.unused_44e0[i]);
    }
    main->write_i32(city_data.religion.venus_curse_active);
    main->write_i32(city_data.unused.unused_44ec);
    main->write_i32(city_data.religion.neptune_double_trade_active);
    main->write_i32(city_data.religion.mars_spirit_power);
    main->write_i32(city_data.unused.unused_44f8);
    main->write_i32(city_data.religion.angry_message_delay);
    main->write_i32(city_data.resource.food_consumed_last_month);
    main->write_i32(city_data.resource.food_produced_last_month);
    main->write_i32(city_data.resource.food_produced_this_month);
    main->write_i32(city_data.ratings.peace_riot_cause);
    main->write_i32(city_data.finance.estimated_tax_income);
    main->write_i32(city_data.mission.tutorial_senate_built);
    main->write_i8(city_data.building.distribution_center_x);
    main->write_i8(city_data.building.distribution_center_y);
    main->write_i16(city_data.building.distribution_center_grid_offset);
    main->write_i32(city_data.building.distribution_center_building_id);
    main->write_i32(city_data.building.distribution_center_placed);
    for (int i = 0; i < 11; i++) {
        main->write_i32(city_data.unused.unused_4524[i]);
    }
    main->write_i32(city_data.building.shipyard_boats_requested);
    main->write_i32(city_data.figure.enemies);
    main->write_i32(city_data.sentiment.wages);
    main->write_i32(city_data.population.people_in_tents);
    main->write_i32(city_data.population.people_in_large_insula_and_above);
    main->write_i32(city_data.figure.imperial_soldiers);
    main->write_i32(city_data.emperor.invasion.duration_day_countdown);
    main->write_i32(city_data.emperor.invasion.warnings_given);
    main->write_i32(city_data.emperor.invasion.days_until_invasion);
    main->write_i32(city_data.emperor.invasion.retreat_message_shown);
    main->write_i32(city_data.ratings.peace_destroyed_buildings);
    main->write_i32(city_data.ratings.peace_years_of_peace);
    main->write_u8(city_data.distant_battle.city);
    main->write_u8(city_data.distant_battle.enemy_strength);
    main->write_u8(city_data.distant_battle.roman_strength);
    main->write_i8(city_data.distant_battle.months_until_battle);
    main->write_i8(city_data.distant_battle.roman_months_to_travel_back);
    main->write_i8(city_data.distant_battle.roman_months_to_travel_forth);
    main->write_i8(city_data.distant_battle.city_foreign_months_left);
    main->write_i8(city_data.building.triumphal_arches_available);
    main->write_i8(city_data.distant_battle.total_count);
    main->write_i8(city_data.distant_battle.won_count);
    main->write_i8(city_data.distant_battle.enemy_months_traveled);
    main->write_i8(city_data.distant_battle.roman_months_traveled);
    main->write_u8(city_data.military.total_legions);
    main->write_u8(city_data.military.empire_service_legions);
    main->write_u8(city_data.unused.unknown_458e);
    main->write_u8(city_data.military.total_soldiers);
    main->write_i8(city_data.building.triumphal_arches_placed);
    main->write_i8(city_data.sound.die_citizen);
    main->write_i8(city_data.sound.die_soldier);
    main->write_i8(city_data.sound.shoot_arrow);
    main->write_i32(city_data.building.trade_center_building_id);
    main->write_i32(city_data.figure.soldiers);
    main->write_i8(city_data.sound.hit_soldier);
    main->write_i8(city_data.sound.hit_spear);
    main->write_i8(city_data.sound.hit_club);
    main->write_i8(city_data.sound.march_enemy);
    main->write_i8(city_data.sound.march_horse);
    main->write_i8(city_data.sound.hit_elephant);
    main->write_i8(city_data.sound.hit_axe);
    main->write_i8(city_data.sound.hit_wolf);
    main->write_i8(city_data.sound.march_wolf);
    for (int i = 0; i < 6; i++) {
        main->write_i8(city_data.unused.unused_45a5[i]);
    }
    main->write_i8(city_data.sentiment.include_tents);
    main->write_i32(city_data.emperor.invasion.count);
    main->write_i32(city_data.emperor.invasion.size);
    main->write_i32(city_data.emperor.invasion.soldiers_killed);
    main->write_i32(city_data.military.legionary_legions);
    main->write_i32(city_data.population.highest_ever);
    main->write_i32(city_data.finance.estimated_wages);
    main->write_i32(city_data.resource.wine_types_available);
    main->write_i32(city_data.ratings.prosperity_max);
    for (int i = 0; i < 10; i++) {
        main->write_i32(city_data.map.largest_road_networks[i].id);
        main->write_i32(city_data.map.largest_road_networks[i].size);
    }
    main->write_i32(city_data.houses.missing.second_wine);
    main->write_i32(city_data.religion.neptune_sank_ships);
    main->write_i32(city_data.entertainment.hippodrome_has_race);
    main->write_i32(city_data.entertainment.hippodrome_message_shown);
    main->write_i32(city_data.entertainment.colosseum_message_shown);
    main->write_i32(city_data.migration.emigration_message_shown);
    main->write_i32(city_data.mission.fired_message_shown);
    main->write_i32(city_data.mission.victory_message_shown);
    main->write_i32(city_data.mission.start_saved_game_written);
    main->write_i32(city_data.mission.tutorial_fire_message_shown);
    main->write_i32(city_data.mission.tutorial_disease_message_shown);
    main->write_i32(city_data.figure.attacking_natives);
    for (int i = 0; i < 232; i++) {
        main->write_i8(city_data.unused.unknown_464c[i]);
    }
}

#include "core/game_environment.h"

static void load_main_data(buffer *main)
{
    if (GAME_ENV == ENGINE_ENV_C3)
        main->read_raw(city_data.unused.other_player, 18068);
    else
        main->read_raw(city_data.unused.other_player, 18068+836);
    city_data.unused.unknown_00a0 = main->read_i8();
    city_data.unused.unknown_00a1 = main->read_i8();
    city_data.unused.unknown_00a2 = main->read_i8();
    city_data.unused.unknown_00a3 = main->read_i8();
    city_data.unused.unknown_00a4 = main->read_i8();
    city_data.building.unknown_value = main->read_i8();
    city_data.unused.unknown_00a7 = main->read_i8();
    city_data.unused.unknown_00a6 = main->read_i8();
    city_data.finance.tax_percentage = main->read_i32();
    city_data.finance.treasury = main->read_i32();
    city_data.sentiment.value = main->read_i32();
    city_data.health.target_value = main->read_i32();
    city_data.health.value = main->read_i32();
    city_data.health.num_hospital_workers = main->read_i32();
    city_data.unused.unknown_00c0 = main->read_i32();
    city_data.population.population = main->read_i32();
    city_data.population.population_last_year = main->read_i32();
    city_data.population.school_age = main->read_i32();
    city_data.population.academy_age = main->read_i32();
    city_data.population.total_capacity = main->read_i32();
    city_data.population.room_in_houses = main->read_i32();
    for (int i = 0; i < 2400; i++)
        city_data.population.monthly.values[i] = main->read_i32();
    city_data.population.monthly.next_index = main->read_i32();
    city_data.population.monthly.count = main->read_i32();
    for (int i = 0; i < 100; i++)
        city_data.population.at_age[i] = main->read_i16();
    for (int i = 0; i < 20; i++)
        city_data.population.at_level[i] = main->read_i32();
    city_data.population.yearly_births = main->read_i32();
    city_data.population.yearly_deaths = main->read_i32();
    city_data.population.lost_removal = main->read_i32();
    city_data.migration.immigration_amount_per_batch = main->read_i32();
    city_data.migration.emigration_amount_per_batch = main->read_i32();
    city_data.migration.emigration_queue_size = main->read_i32();
    city_data.migration.immigration_queue_size = main->read_i32();
    city_data.population.lost_homeless = main->read_i32();
    city_data.population.last_change = main->read_i32();
    city_data.population.average_per_year = main->read_i32();
    city_data.population.total_all_years = main->read_i32();
    city_data.population.people_in_tents_shacks = main->read_i32();
    city_data.population.people_in_villas_palaces = main->read_i32();
    city_data.population.total_years = main->read_i32();
    city_data.population.yearly_update_requested = main->read_i32();
    city_data.population.last_used_house_add = main->read_i32();
    city_data.population.last_used_house_remove = main->read_i32();
    city_data.migration.immigrated_today = main->read_i32();
    city_data.migration.emigrated_today = main->read_i32();
    city_data.migration.refused_immigrants_today = main->read_i32();
    city_data.migration.percentage = main->read_i32();
    city_data.unused.unused_27d0 = main->read_i32();
    city_data.migration.immigration_duration = main->read_i32();
    city_data.migration.emigration_duration = main->read_i32();
    city_data.migration.newcomers = main->read_i32();
    for (int i = 0; i < 4; i++)
        city_data.unused.unknown_27e0[i] = main->read_i32();
    city_data.unused.unknown_27f0 = main->read_i16();
    city_data.resource.last_used_warehouse = main->read_i16();
    for (int i = 0; i < 18; i++)
        city_data.unused.unknown_27f4[i] = main->read_i16();
    if (GAME_ENV == ENGINE_ENV_C3) {
        city_data.map.entry_point.x = main->read_u8();
        city_data.map.entry_point.y = main->read_u8();
        city_data.map.entry_point.grid_offset = main->read_i16();
        city_data.map.exit_point.x = main->read_u8();
        city_data.map.exit_point.y = main->read_u8();
        city_data.map.exit_point.grid_offset = main->read_i16();
        city_data.building.senate_x = main->read_u8();
        city_data.building.senate_y = main->read_u8();
        city_data.building.senate_grid_offset = main->read_i16();
    } else  {
        city_data.map.entry_point.x = main->read_u16();
        city_data.map.entry_point.y = main->read_u16();
        city_data.map.entry_point.grid_offset = main->read_i32();
        city_data.map.exit_point.x = main->read_u16();
        city_data.map.exit_point.y = main->read_u16();
        city_data.map.exit_point.grid_offset = main->read_i32();
        city_data.building.senate_x = main->read_u16();
        city_data.building.senate_y = main->read_u16();
        city_data.building.senate_grid_offset = main->read_i32();
    }
    city_data.building.senate_building_id = main->read_i32();
    city_data.unused.unknown_2828 = main->read_i16();
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        main->skip(2);
    for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++)
        city_data.resource.space_in_warehouses[i] = main->read_i16();
    for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++)
        city_data.resource.stored_in_warehouses[i] = main->read_i16();
    for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++)
        city_data.resource.trade_status[i] = main->read_i16();
    for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++)
        city_data.resource.export_over[i] = main->read_i16();
    for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++)
        city_data.resource.mothballed[i] = main->read_i16();
    city_data.unused.unused_28ca = main->read_i16();
    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        main->skip(22);
        for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++)
            main->skip(2);
        for (int i = 0; i < RESOURCE_MAX_FOOD[GAME_ENV]; i++)
            city_data.resource.granary_food_stored[i] = main->read_i16();
        main->skip(424); // temp
    } else {
        for (int i = 0; i < RESOURCE_MAX_FOOD[GAME_ENV]; i++)
            city_data.resource.granary_food_stored[i] = main->read_i32();
        for (int i = 0; i < 6; i++)
            city_data.resource.stored_in_workshops[i] = main->read_i32();
        for (int i = 0; i < 6; i++)
            city_data.resource.space_in_workshops[i] = main->read_i32();
        city_data.resource.granary_total_stored = main->read_i32();
        city_data.resource.food_types_available = main->read_i32();
        city_data.resource.food_types_eaten = main->read_i32();
        for (int i = 0; i < 272; i++)
            city_data.unused.unknown_2924[i] = main->read_i8();
        for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++)
            city_data.resource.stockpiled[i] = main->read_i32();
    }
    city_data.resource.food_supply_months = main->read_i32();
    city_data.resource.granaries.operating = main->read_i32();
    city_data.population.percentage_plebs = main->read_i32();
    city_data.population.working_age = main->read_i32();
    city_data.labor.workers_available = main->read_i32();
    for (int i = 0; i < 10; i++) {
        city_data.labor.categories[i].workers_needed = main->read_i32();
        city_data.labor.categories[i].workers_allocated = main->read_i32();
        city_data.labor.categories[i].total_houses_covered = main->read_i32();
        city_data.labor.categories[i].buildings = main->read_i32();
        city_data.labor.categories[i].priority = main->read_i32();
    }
    city_data.labor.workers_employed = main->read_i32();
    city_data.labor.workers_unemployed = main->read_i32();
    city_data.labor.unemployment_percentage = main->read_i32();
    city_data.labor.unemployment_percentage_for_senate = main->read_i32();
    city_data.labor.workers_needed = main->read_i32();
    city_data.labor.wages = main->read_i32();
    city_data.labor.wages_rome = main->read_i32();
    city_data.unused.unknown_2b6c = main->read_i32();
    city_data.finance.wages_so_far = main->read_i32();
    city_data.finance.this_year.expenses.wages = main->read_i32();
    city_data.finance.last_year.expenses.wages = main->read_i32();
    city_data.taxes.taxed_plebs = main->read_i32();
    city_data.taxes.taxed_patricians = main->read_i32();
    city_data.taxes.untaxed_plebs = main->read_i32();
    city_data.taxes.untaxed_patricians = main->read_i32();
    city_data.taxes.percentage_taxed_plebs = main->read_i32();
    city_data.taxes.percentage_taxed_patricians = main->read_i32();
    city_data.taxes.percentage_taxed_people = main->read_i32();
    city_data.taxes.yearly.collected_plebs = main->read_i32();
    city_data.taxes.yearly.collected_patricians = main->read_i32();
    city_data.taxes.yearly.uncollected_plebs = main->read_i32();
    city_data.taxes.yearly.uncollected_patricians = main->read_i32();
    city_data.finance.this_year.income.taxes = main->read_i32();
    city_data.finance.last_year.income.taxes = main->read_i32();
    city_data.taxes.monthly.collected_plebs = main->read_i32();
    city_data.taxes.monthly.uncollected_plebs = main->read_i32();
    city_data.taxes.monthly.collected_patricians = main->read_i32();
    city_data.taxes.monthly.uncollected_patricians = main->read_i32();
    city_data.finance.this_year.income.exports = main->read_i32();
    city_data.finance.last_year.income.exports = main->read_i32();
    city_data.finance.this_year.expenses.imports = main->read_i32();
    city_data.finance.last_year.expenses.imports = main->read_i32();
    city_data.finance.interest_so_far = main->read_i32();
    city_data.finance.last_year.expenses.interest = main->read_i32();
    city_data.finance.this_year.expenses.interest = main->read_i32();
    city_data.finance.last_year.expenses.sundries = main->read_i32();
    city_data.finance.this_year.expenses.sundries = main->read_i32();
    city_data.finance.last_year.expenses.construction = main->read_i32();
    city_data.finance.this_year.expenses.construction = main->read_i32();
    city_data.finance.last_year.expenses.salary = main->read_i32();
    city_data.finance.this_year.expenses.salary = main->read_i32();
    city_data.emperor.salary_amount = main->read_i32();
    city_data.emperor.salary_rank = main->read_i32();
    city_data.finance.salary_so_far = main->read_i32();
    city_data.finance.last_year.income.total = main->read_i32();
    city_data.finance.this_year.income.total = main->read_i32();
    city_data.finance.last_year.expenses.total = main->read_i32();
    city_data.finance.this_year.expenses.total = main->read_i32();
    city_data.finance.last_year.net_in_out = main->read_i32();
    city_data.finance.this_year.net_in_out = main->read_i32();
    city_data.finance.last_year.balance = main->read_i32();
    city_data.finance.this_year.balance = main->read_i32();
    for (int i = 0; i < 1400; i++)
        city_data.unused.unknown_2c20[i] = main->read_i32();
    for (int i = 0; i < 8; i++)
        city_data.unused.houses_requiring_unknown_to_evolve[i] = main->read_i32();
    city_data.trade.caravan_import_resource = main->read_i32();
    city_data.trade.caravan_backup_import_resource = main->read_i32();
    city_data.ratings.culture = main->read_i32();
    city_data.ratings.prosperity = main->read_i32();
    city_data.ratings.peace = main->read_i32();
    city_data.ratings.favor = main->read_i32();
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        main->skip(8);
    else for (int i = 0; i < 4; i++)
        city_data.unused.unknown_4238[i] = main->read_i32();
    city_data.ratings.prosperity_treasury_last_year = main->read_i32();
    city_data.ratings.culture_points.theater = main->read_i32();
    city_data.ratings.culture_points.religion = main->read_i32();
    city_data.ratings.culture_points.school = main->read_i32();
    city_data.ratings.culture_points.library = main->read_i32();
    city_data.ratings.culture_points.academy = main->read_i32();
    city_data.ratings.peace_num_criminals = main->read_i32();
    city_data.ratings.peace_num_rioters = main->read_i32();
    city_data.houses.missing.fountain = main->read_i32();
    city_data.houses.missing.well = main->read_i32();
    city_data.houses.missing.more_entertainment = main->read_i32();
    city_data.houses.missing.more_education = main->read_i32();
    city_data.houses.missing.education = main->read_i32();
    city_data.houses.requiring.school = main->read_i32();
    city_data.houses.requiring.library = main->read_i32();
    city_data.unused.unknown_4284 = main->read_i32();
    city_data.houses.missing.barber = main->read_i32();
    city_data.houses.missing.bathhouse = main->read_i32();
    city_data.houses.missing.food = main->read_i32();
    for (int i = 0; i < 2; i++)
        city_data.unused.unknown_4294[i] = main->read_i32();
    city_data.building.hippodrome_placed = main->read_i32();
    city_data.houses.missing.clinic = main->read_i32();
    city_data.houses.missing.hospital = main->read_i32();
    city_data.houses.requiring.barber = main->read_i32();
    city_data.houses.requiring.bathhouse = main->read_i32();
    city_data.houses.requiring.clinic = main->read_i32();
    city_data.houses.missing.religion = main->read_i32();
    city_data.houses.missing.second_religion = main->read_i32();
    city_data.houses.missing.third_religion = main->read_i32();
    city_data.houses.requiring.religion = main->read_i32();
    city_data.entertainment.theater_shows = main->read_i32();
    city_data.entertainment.theater_no_shows_weighted = main->read_i32();
    city_data.entertainment.amphitheater_shows = main->read_i32();
    city_data.entertainment.amphitheater_no_shows_weighted = main->read_i32();
    city_data.entertainment.colosseum_shows = main->read_i32();
    city_data.entertainment.colosseum_no_shows_weighted = main->read_i32();
    city_data.entertainment.hippodrome_shows = main->read_i32();
    city_data.entertainment.hippodrome_no_shows_weighted = main->read_i32();
    city_data.entertainment.venue_needing_shows = main->read_i32();
    city_data.culture.average_entertainment = main->read_i32();
    city_data.houses.missing.entertainment = main->read_i32();
    city_data.festival.months_since_festival = main->read_i32(); // ok
    for (int i = 0; i < MAX_GODS; i++)
        city_data.religion.gods[i].target_happiness = main->read_i8();
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        main->skip(5);
    for (int i = 0; i < MAX_GODS; i++)
        city_data.religion.gods[i].happiness = main->read_i8();
    for (int i = 0; i < MAX_GODS; i++)
        city_data.religion.gods[i].wrath_bolts = main->read_i8();
    for (int i = 0; i < MAX_GODS; i++)
        city_data.religion.gods[i].blessing_done = main->read_i8();
    for (int i = 0; i < MAX_GODS; i++)
        city_data.religion.gods[i].small_curse_done = main->read_i8();
    main->skip(15);
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        main->skip(35);
//    for (int i = 0; i < MAX_GODS; i++)
//        city_data.religion.gods[i].unused1 = main->read_i8();
//    for (int i = 0; i < MAX_GODS; i++)
//        city_data.religion.gods[i].unused2 = main->read_i8();
//    for (int i = 0; i < MAX_GODS; i++)
//        city_data.religion.gods[i].unused3 = main->read_i8();
    for (int i = 0; i < MAX_GODS; i++)
        city_data.religion.gods[i].months_since_festival = main->read_i32();
    city_data.religion.least_happy_god = main->read_i32();
    city_data.unused.unknown_4334 = main->read_i32();
    city_data.migration.no_immigration_cause = main->read_i32();
    city_data.sentiment.protesters = main->read_i32();
    city_data.sentiment.criminals = main->read_i32();
    city_data.houses.health = main->read_i32();
    city_data.houses.religion = main->read_i32();
    city_data.houses.education = main->read_i32();
    city_data.houses.entertainment = main->read_i32();
    city_data.figure.rioters = main->read_i32();
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        main->skip(20);
    city_data.ratings.selected = main->read_i32();
    city_data.ratings.culture_explanation = main->read_i32();
    city_data.ratings.prosperity_explanation = main->read_i32();
    city_data.ratings.peace_explanation = main->read_i32();
    city_data.ratings.favor_explanation = main->read_i32();
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        main->skip(8);
    city_data.emperor.player_rank = main->read_i32();
    city_data.emperor.personal_savings = main->read_i32(); // ok
    for (int i = 0; i < 2; i++)
        city_data.unused.unknown_4374[i] = main->read_i32();
    city_data.finance.last_year.income.donated = main->read_i32();
    city_data.finance.this_year.income.donated = main->read_i32();
    city_data.emperor.donate_amount = main->read_i32();
    for (int i = 0; i < 10; i++)
        city_data.building.working_dock_ids[i] = main->read_i16();
    for (int i = 0; i < 3; i++)
        city_data.unused.unknown_439c[i] = main->read_i16();
    city_data.figure.animals = main->read_i16();
    city_data.trade.num_sea_routes = main->read_i16();
    city_data.trade.num_land_routes = main->read_i16();
    city_data.trade.sea_trade_problem_duration = main->read_i16();
    city_data.trade.land_trade_problem_duration = main->read_i16();
    city_data.building.working_docks = main->read_i16();
    city_data.building.senate_placed = main->read_i16();
    city_data.building.working_wharfs = main->read_i16();
    for (int i = 0; i < 2; i++)
        city_data.unused.padding_43b2[i] = main->read_i8();
    city_data.finance.stolen_this_year = main->read_i16();
    city_data.finance.stolen_last_year = main->read_i16();
    city_data.trade.docker_import_resource = main->read_i32();
    city_data.trade.docker_export_resource = main->read_i32();
    city_data.emperor.debt_state = main->read_i32();
    city_data.emperor.months_in_debt = main->read_i32();
    city_data.finance.cheated_money = main->read_i32();
    city_data.building.barracks_x = main->read_i8();
    city_data.building.barracks_y = main->read_i8();
    city_data.building.barracks_grid_offset = main->read_i16();
    city_data.building.barracks_building_id = main->read_i32();
    city_data.building.barracks_placed = main->read_i32();
    for (int i = 0; i < 5; i++)
        city_data.unused.unknown_43d8[i] = main->read_i32();
    city_data.population.lost_troop_request = main->read_i32();
    city_data.unused.unknown_43f0 = main->read_i32();
    city_data.mission.has_won = main->read_i32();
    city_data.mission.continue_months_left = main->read_i32();
    city_data.mission.continue_months_chosen = main->read_i32();
    city_data.finance.wage_rate_paid_this_year = main->read_i32();
    city_data.finance.this_year.expenses.tribute = main->read_i32(); // ok
    city_data.finance.last_year.expenses.tribute = main->read_i32();
    city_data.finance.tribute_not_paid_last_year = main->read_i32();
    if (GAME_ENV == ENGINE_ENV_C3)
        city_data.finance.tribute_not_paid_total_years = main->read_i32();
    city_data.festival.selected.god = main->read_i32();
    city_data.festival.selected.size = main->read_i32();
    city_data.festival.planned.size = main->read_i32();
    city_data.festival.planned.months_to_go = main->read_i32();
    city_data.festival.planned.god = main->read_i32();
    city_data.festival.small_cost = main->read_i32();
    city_data.festival.large_cost = main->read_i32();
    city_data.festival.grand_cost = main->read_i32();
    city_data.festival.grand_wine = main->read_i32();
    city_data.festival.not_enough_wine = main->read_i32();
    city_data.culture.average_religion = main->read_i32();
    city_data.culture.average_education = main->read_i32();
    city_data.culture.average_health = main->read_i32();
    city_data.culture.religion_coverage = main->read_i32();
    city_data.festival.first_festival_effect_months = main->read_i32();
    city_data.festival.second_festival_effect_months = main->read_i32();
    city_data.unused.unused_4454 = main->read_i32();
    city_data.sentiment.unemployment = main->read_i32();
    city_data.sentiment.previous_value = main->read_i32();
    city_data.sentiment.message_delay = main->read_i32();
    city_data.sentiment.low_mood_cause = main->read_i32();
    city_data.figure.security_breach_duration = main->read_i32();
    for (int i = 0; i < 4; i++)
        city_data.unused.unknown_446c[i] = main->read_i32();
    city_data.emperor.selected_gift_size = main->read_i32();
    city_data.emperor.months_since_gift = main->read_i32(); // ok
    city_data.emperor.gift_overdose_penalty = main->read_i32();
    city_data.unused.unused_4488 = main->read_i32();
    city_data.emperor.gifts[GIFT_MODEST].id = main->read_i32();
    city_data.emperor.gifts[GIFT_GENEROUS].id = main->read_i32();
    city_data.emperor.gifts[GIFT_LAVISH].id = main->read_i32();
    city_data.emperor.gifts[GIFT_MODEST].cost = main->read_i32();
    city_data.emperor.gifts[GIFT_GENEROUS].cost = main->read_i32();
    city_data.emperor.gifts[GIFT_LAVISH].cost = main->read_i32();
    city_data.ratings.favor_salary_penalty = main->read_i32();
    city_data.ratings.favor_milestone_penalty = main->read_i32();
    city_data.ratings.favor_ignored_request_penalty = main->read_i32();
    city_data.ratings.favor_last_year = main->read_i32();
    city_data.ratings.favor_change = main->read_i32();
    city_data.military.native_attack_duration = main->read_i32();
    city_data.unused.unused_native_force_attack = main->read_i32();
    city_data.building.mission_post_operational = main->read_i32();
    city_data.building.main_native_meeting.x = main->read_i32();
    city_data.building.main_native_meeting.y = main->read_i32();
    city_data.finance.wage_rate_paid_last_year = main->read_i32();
    city_data.resource.food_needed_per_month = main->read_i32();
    city_data.resource.granaries.understaffed = main->read_i32();
    city_data.resource.granaries.not_operating = main->read_i32();
    city_data.resource.granaries.not_operating_with_food = main->read_i32();
    for (int i = 0; i < 2; i++)
        city_data.unused.unused_44e0[i] = main->read_i32();
    city_data.religion.venus_curse_active = main->read_i32();
    city_data.unused.unused_44ec = main->read_i32();
    city_data.religion.neptune_double_trade_active = main->read_i32();
    city_data.religion.mars_spirit_power = main->read_i32();
    city_data.unused.unused_44f8 = main->read_i32();
    city_data.religion.angry_message_delay = main->read_i32();
    city_data.resource.food_consumed_last_month = main->read_i32();
    city_data.resource.food_produced_last_month = main->read_i32();
    city_data.resource.food_produced_this_month = main->read_i32();
    city_data.ratings.peace_riot_cause = main->read_i32();
    city_data.finance.estimated_tax_income = main->read_i32();
    city_data.mission.tutorial_senate_built = main->read_i32(); // ok
    city_data.building.distribution_center_x = main->read_i8();
    city_data.building.distribution_center_y = main->read_i8();
    city_data.building.distribution_center_grid_offset = main->read_i16();
    city_data.building.distribution_center_building_id = main->read_i32();
    city_data.building.distribution_center_placed = main->read_i32();
    for (int i = 0; i < 11; i++)
        city_data.unused.unused_4524[i] = main->read_i32();
    city_data.building.shipyard_boats_requested = main->read_i32();
    city_data.figure.enemies = main->read_i32();
    city_data.sentiment.wages = main->read_i32();
    city_data.population.people_in_tents = main->read_i32();
    city_data.population.people_in_large_insula_and_above = main->read_i32();
    city_data.figure.imperial_soldiers = main->read_i32();
    city_data.emperor.invasion.duration_day_countdown = main->read_i32();
    city_data.emperor.invasion.warnings_given = main->read_i32();
    city_data.emperor.invasion.days_until_invasion = main->read_i32();
    city_data.emperor.invasion.retreat_message_shown = main->read_i32();
    city_data.ratings.peace_destroyed_buildings = main->read_i32();
    city_data.ratings.peace_years_of_peace = main->read_i32();
    city_data.distant_battle.city = main->read_u8();
    city_data.distant_battle.enemy_strength = main->read_u8();
    city_data.distant_battle.roman_strength = main->read_u8();
    city_data.distant_battle.months_until_battle = main->read_i8();
    city_data.distant_battle.roman_months_to_travel_back = main->read_i8();
    city_data.distant_battle.roman_months_to_travel_forth = main->read_i8();
    city_data.distant_battle.city_foreign_months_left = main->read_i8();
    city_data.building.triumphal_arches_available = main->read_i8();
    city_data.distant_battle.total_count = main->read_i8();
    city_data.distant_battle.won_count = main->read_i8();
    city_data.distant_battle.enemy_months_traveled = main->read_i8();
    city_data.distant_battle.roman_months_traveled = main->read_i8();
    city_data.military.total_legions = main->read_u8();
    city_data.military.empire_service_legions = main->read_u8();
    city_data.unused.unknown_458e = main->read_u8();
    city_data.military.total_soldiers = main->read_u8();
    city_data.building.triumphal_arches_placed = main->read_i8();
    city_data.sound.die_citizen = main->read_i8();
    city_data.sound.die_soldier = main->read_i8();
    city_data.sound.shoot_arrow = main->read_i8();
    city_data.building.trade_center_building_id = main->read_i32();
    city_data.figure.soldiers = main->read_i32();
    city_data.sound.hit_soldier = main->read_i8();
    city_data.sound.hit_spear = main->read_i8();
    city_data.sound.hit_club = main->read_i8();
    city_data.sound.march_enemy = main->read_i8();
    city_data.sound.march_horse = main->read_i8();
    city_data.sound.hit_elephant = main->read_i8();
    city_data.sound.hit_axe = main->read_i8();
    city_data.sound.hit_wolf = main->read_i8();
    city_data.sound.march_wolf = main->read_i8();
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        main->skip(10);
    else
        for (int i = 0; i < 6; i++)
            city_data.unused.unused_45a5[i] = main->read_i8();
    city_data.sentiment.include_tents = main->read_i8();
    city_data.emperor.invasion.count = main->read_i32();
    city_data.emperor.invasion.size = main->read_i32();
    city_data.emperor.invasion.soldiers_killed = main->read_i32();
    city_data.military.legionary_legions = main->read_i32();
    city_data.population.highest_ever = main->read_i32();
    city_data.finance.estimated_wages = main->read_i32();
    city_data.resource.wine_types_available = main->read_i32();
    city_data.ratings.prosperity_max = main->read_i32();
    for (int i = 0; i < 10; i++) {
        city_data.map.largest_road_networks[i].id = main->read_i32();
        city_data.map.largest_road_networks[i].size = main->read_i32();
    }
    city_data.houses.missing.second_wine = main->read_i32();
    city_data.religion.neptune_sank_ships = main->read_i32();
    city_data.entertainment.hippodrome_has_race = main->read_i32();
    city_data.entertainment.hippodrome_message_shown = main->read_i32();
    city_data.entertainment.colosseum_message_shown = main->read_i32();
    city_data.migration.emigration_message_shown = main->read_i32();
    city_data.mission.fired_message_shown = main->read_i32();
    city_data.mission.victory_message_shown = main->read_i32();
    city_data.mission.start_saved_game_written = main->read_i32();
    city_data.mission.tutorial_fire_message_shown = main->read_i32();
    city_data.mission.tutorial_disease_message_shown = main->read_i32();
    city_data.figure.attacking_natives = main->read_i32();
    for (int i = 0; i < 232; i++)
        city_data.unused.unknown_464c[i] = main->read_i8();
    if (GAME_ENV == ENGINE_ENV_PHARAOH) // todo: fill in missing data?
        main->skip(452); // unknown bytes ??????
}

static void save_entry_exit(buffer *entry_exit_xy, buffer *entry_exit_grid_offset)
{
    entry_exit_xy->write_i32(city_data.map.entry_flag.x);
    entry_exit_xy->write_i32(city_data.map.entry_flag.y);
    entry_exit_xy->write_i32(city_data.map.exit_flag.x);
    entry_exit_xy->write_i32(city_data.map.exit_flag.y);

    entry_exit_grid_offset->write_i32(city_data.map.entry_flag.grid_offset);
    entry_exit_grid_offset->write_i32(city_data.map.exit_flag.grid_offset);
}

#include "core/game_environment.h"

static void load_entry_exit(buffer *entry_exit_xy, buffer *entry_exit_grid_offset)
{
    if (GAME_ENV == ENGINE_ENV_C3) {
        city_data.map.entry_flag.x = entry_exit_xy->read_i32();
        city_data.map.entry_flag.y = entry_exit_xy->read_i32();
        city_data.map.exit_flag.x = entry_exit_xy->read_i32();
        city_data.map.exit_flag.y = entry_exit_xy->read_i32();
    }
    else {
        city_data.map.entry_flag.x = entry_exit_xy->read_i16();
        city_data.map.entry_flag.y = entry_exit_xy->read_i16();
        city_data.map.exit_flag.x = entry_exit_xy->read_i16();
        city_data.map.exit_flag.y = entry_exit_xy->read_i16();
    }
//    city_data.map.entry_flag.grid_offset = entry_exit_grid_offset->read_i32();
//    city_data.map.exit_flag.grid_offset = entry_exit_grid_offset->read_i32();
    city_data.map.entry_flag.grid_offset = 0;
    city_data.map.exit_flag.grid_offset = 0;
}

void city_data_save_state(buffer *main, buffer *faction, buffer *faction_unknown, buffer *graph_order,
                          buffer *entry_exit_xy, buffer *entry_exit_grid_offset)
{
    save_main_data(main);

    faction->write_i32(city_data.unused.faction_id);
    faction_unknown->write_i8(city_data.unused.faction_bytes[0]);
    faction_unknown->write_i8(city_data.unused.faction_bytes[1]);
    graph_order->write_i32(city_data.population.graph_order);
    graph_order->write_i32(city_data.unused.unknown_order);

    save_entry_exit(entry_exit_xy, entry_exit_grid_offset);
}

void city_data_load_state(buffer *main, buffer *faction, buffer *faction_unknown, buffer *graph_order,
                          buffer *entry_exit_xy, buffer *entry_exit_grid_offset)
{
    load_main_data(main);

    city_data.unused.faction_id = faction->read_i32();
    city_data.unused.faction_bytes[0] = faction_unknown->read_i8();
    city_data.unused.faction_bytes[1] = faction_unknown->read_i8();
    city_data.population.graph_order = graph_order->read_i32();
    city_data.unused.unknown_order = graph_order->read_i32();

    load_entry_exit(entry_exit_xy, entry_exit_grid_offset);
}

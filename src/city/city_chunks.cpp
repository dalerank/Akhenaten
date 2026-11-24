#include "city/city_chunks.h"

#include "city/city.h"
#include "city/entertainment.h"
#include "city/city_festival.h"
#include "city/city_religion_osiris.h"
#include "io/io_buffer.h"
#include "io/chunk_serializer.h"
#include "scenario/distant_battle.h"
#include "scenario/scenario.h"

// Save version 199+ (and OG .sav files): the city_player record exactly as OG city_player_types.h lays it out
// (offsets checked against its offsetof asserts). Our fields without an OG field live in OG reserved bytes:
// in place where they already sat in a reserved range, otherwise packed from 0x2D14 inside OG reserved_13.
static void city_data_bind_og_layout(io_buffer* iob) {
    auto& data = g_city;
    int tmp = 0;
    iob->bind____skip(18904);
    iob->bind____skip(1);
    iob->bind____skip(1);
    iob->bind____skip(1);
    iob->bind____skip(1);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_INT8, &data.buildings.unknown_value);
    iob->bind____skip(1);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_INT8, &data.finance.tax_percentage);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.treasury.value);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.value);
    iob->bind(BIND_SIGNATURE_INT32, &data.health.target_value);
    iob->bind(BIND_SIGNATURE_INT32, &data.health.value);
    iob->bind(BIND_SIGNATURE_INT32, &data.health.num_mortuary_workers);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.current);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.last_year);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.school_age);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.academy_age);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.total_capacity);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.room_in_houses);
    for (int i = 0; i < 2400; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.population.monthly.values[i]);
    }
    iob->bind(BIND_SIGNATURE_INT32, &data.population.monthly.next_index);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.monthly.count);
    for (int i = 0; i < 100; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &data.population.at_age[i]);
    }
    for (int i = 0; i < 20; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &data.population.at_level[i]);
        iob->bind____skip(2);
    }
    iob->bind(BIND_SIGNATURE_INT32, &data.population.yearly_births);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.yearly_deaths);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.lost_removal);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.immigration_amount_per_batch);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.emigration_amount_per_batch);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.emigration_queue_size);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.immigration_queue_size);
    iob->bind____skip(3);
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
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.immigrated_today);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.emigrated_today);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.refused_immigrants_today);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT8, &data.migration.percentage);
    iob->bind____skip(3);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_UINT16, &data.migration.emigration_duration);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.migration.immigration_duration);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.migration.newcomers);
    iob->bind____skip(6);
    iob->bind____skip(12);
    iob->bind____skip(2);
    iob->bind____skip(2);
    iob->bind____skip(36);
    iob->bind(BIND_SIGNATURE_INT32, data.map.entry_point);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, data.map.exit_point);
    iob->bind____skip(16);
    iob->bind____skip(2);
    iob->bind____skip(2);
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &data.resource.space_in_storages[i + 1]);
    }
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT16, &data.resource.stored_in_storages[i + 1]);
    }
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.resource.trade_status[i + 1]);
        iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    }
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &data.resource.trading_amount[i + 1]);
    for (int i = 0; i < RESOURCES_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.resource.mothballed[i + 1]);
        iob->bind____skip(1);
    }
    iob->bind____skip(2);
    iob->bind____skip(20);
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT16, &data.resource.unk_00[i]);
    iob->bind____skip(298);
    for (int i = 0; i < RESOURCES_MAX; i++)
        iob->bind(BIND_SIGNATURE_INT32, &data.resource.stockpiled[i]);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.food_supply_months);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.granaries.operating);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.percentage_plebs);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.working_age);
    iob->bind(BIND_SIGNATURE_INT32, &data.labor.workers_available);
    for (int i = 0; i < LABOR_CATEGORY_SAVE_SLOTS; i++) {
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
    iob->bind(BIND_SIGNATURE_INT8, &data.finance.wages);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT8, &data.finance.wages_kingdome);
    iob->bind____skip(3);
    iob->bind____skip(4);
    iob->bind____skip(12);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.taxed_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.taxed_nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.untaxed_citizens);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.untaxed_nobles);
    iob->bind(BIND_SIGNATURE_INT8, &data.taxes.percentage_taxed_citizens);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT8, &data.taxes.percentage_taxed_nobles);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT8, &data.taxes.percentage_taxed_people);
    iob->bind____skip(3);
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
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.this_year.income.exports);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.last_year.income.exports);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.this_year.expenses.imports);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.last_year.expenses.imports);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT16, &data.finance.interest_so_far);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.last_year.expenses.interest);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.this_year.expenses.interest);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.last_year.expenses.stolen);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.this_year.expenses.stolen);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.last_year.expenses.construction);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.this_year.expenses.construction);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.last_year.expenses.accountant_salary);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.this_year.expenses.accountant_salary);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.salary_amount);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.salary_rank);
    iob->bind____skip(3);
    iob->bind_u16(data.finance.this_year.expenses.mayour_salary);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.income.total);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.income.total);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.expenses.total);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.expenses.total);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.net_in_out);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.net_in_out);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.balance);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.balance);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.cheated_money);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.estimated_uncollected);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.last_year.expenses.festivals);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.this_year.expenses.festivals);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.last_year.expenses.kingdome);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.this_year.expenses.kingdome);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.this_year.expenses.tribute);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.last_year.expenses.tribute);
    iob->bind____skip(18);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.wages_so_far);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.this_year.expenses.wages);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.last_year.expenses.wages);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.this_year.income.gold_delivered);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.last_year.income.gold_delivered);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.this_year.expenses.disasters);
    iob->bind(BIND_SIGNATURE_UINT16, &data.finance.last_year.expenses.disasters);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.last_day_current);
    iob->bind(BIND_SIGNATURE_UINT16, &data.migration.nobles_leave_city_this_year);
    iob->bind____skip(2);
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &data.resource.food_types_available[i]);
    iob->bind____skip(2);
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++)
        iob->bind(BIND_SIGNATURE_UINT16, &data.resource.food_types_eaten[i]);
    iob->bind_u16(data.kingdome.campaign_carry_personal_savings); // savings carried over to next mission
    iob->bind(BIND_SIGNATURE_UINT8, &data.figures.fish_number);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.debt_state);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.months_in_debt);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.lost_troop_request);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.message_delay);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.rating_cap);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.military.native_attack_duration);
    iob->bind(BIND_SIGNATURE_INT32, &data.gods.bast_curse_active);
    iob->bind(BIND_SIGNATURE_INT32, &data.gods.seth_crush_enemy_troops);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.monument_riot_cause);
    iob->bind(BIND_SIGNATURE_UINT16, &data.kingdome.invasion.duration_day_countdown);
    iob->bind(BIND_SIGNATURE_INT8, &data.kingdome.invasion.warnings_given);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.invasion.days_until_invasion);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.invasion.retreat_message_shown);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.invasion.favour_only);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.invasion.cheated);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT16, &data.ratings.monument_years_of_monument);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.egyptian_months_to_travel_forth);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.city_foreign_months_left);
    iob->bind(BIND_SIGNATURE_INT8, &data.buildings.triumphal_obelisk_available);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.won_count);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.enemy_months_traveled);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.egyptian_months_traveled);
    iob->bind(BIND_SIGNATURE_INT8, &data.buildings.triumphal_obelisk_placed);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.invasion.count);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.invasion.size);
    iob->bind(BIND_SIGNATURE_UINT16, &data.kingdome.invasion.soldiers_killed);
    iob->bind(BIND_SIGNATURE_UINT8, &data.military.infantry_batalions);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_INT8, &god_osiris.sank_ships);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.percentage_by_sentiment);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.population_cap);
    iob->bind_u8((uint8_t&)g_distant_battle.dispatched_army.state);
    iob->bind_u8(g_distant_battle.dispatched_army.await_soldiers);
    iob->bind_u8(g_distant_battle.dispatched_army.position_index);
    iob->bind____skip(1);
    iob->bind_i16(g_distant_battle.source_request_event_id);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.coverage_common);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.coverage[GOD_OSIRIS]);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.coverage[GOD_RA]);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.coverage[GOD_PTAH]);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.coverage[GOD_SETH]);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.coverage[GOD_BAST]);
    iob->bind____skip(5376);
    iob->bind____skip(32);
    iob->bind(BIND_SIGNATURE_INT32, &data.trade.caravan_import_resource);
    iob->bind(BIND_SIGNATURE_INT32, &data.trade.caravan_backup_import_resource);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.culture);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.prosperity);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.monument);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.rating);
    iob->bind____skip(8);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.prosperity_trend);
    iob->bind____skip(20);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.monument_num_criminals);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.monument_num_rioters);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.fountain);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.well);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.more_entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.more_education);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.education);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.school);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.library);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.dentist);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.courthouse);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.food);
    iob->bind____skip(8);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.health);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.more_health);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.dentist);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.courthouse);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.health);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.second_religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.third_religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.religion);
    iob->bind(BIND_SIGNATURE_INT32, &city_entertainment().booth_shows);
    iob->bind(BIND_SIGNATURE_INT32, &city_entertainment().booth_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &city_entertainment().bandstand_shows);
    iob->bind(BIND_SIGNATURE_INT32, &city_entertainment().bandstand_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &city_entertainment().pavilion_shows);
    iob->bind(BIND_SIGNATURE_INT32, &city_entertainment().pavilion_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &city_entertainment().senet_house_plays);
    iob->bind(BIND_SIGNATURE_INT32, &city_entertainment().senet_house_no_shows_weighted);
    iob->bind(BIND_SIGNATURE_INT32, &city_entertainment().venue_needing_shows);
    iob->bind(BIND_SIGNATURE_INT32, &data.avg_coverage.average_entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.entertainment);
    iob->bind(BIND_SIGNATURE_INT8, &city_festival().months_since_festival); // ok
    iob->bind____skip(3);
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.gods.gods[i].target_mood);
    }
    iob->bind____skip(5);
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.gods.gods[i].mood);
    }
    iob->bind____skip(5);
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.gods.gods[i].wrath_bolts);
    }
    iob->bind____skip(55);
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.gods.gods[i].months_since_festival);
        iob->bind____skip(3);
    }
    iob->bind____skip(20);
    iob->bind(BIND_SIGNATURE_INT32, &data.gods.least_happy_god);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT8, &data.migration.no_immigration_cause);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.protesters);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.criminals);
    iob->bind(BIND_SIGNATURE_UINT8, &data.houses.health);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.education);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.entertainment);
    iob->bind(BIND_SIGNATURE_INT32, &data.figures.rioters);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.culture_explanation);
    iob->bind(BIND_SIGNATURE_INT32, &data.ratings.prosperity_explanation);
    iob->bind____skip(16);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.player_rank);
    iob->bind____skip(3);
    iob->bind_u16(data.kingdome.personal_savings); // ok
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.last_year.income.donated);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.this_year.income.donated);
    iob->bind____skip(30);
    iob->bind(BIND_SIGNATURE_UINT8, &data.figures.animals_number);
    iob->bind____skip(21);
    iob->bind(BIND_SIGNATURE_INT32, &data.trade.docker_import_resource);
    iob->bind(BIND_SIGNATURE_INT32, &data.trade.docker_export_resource);
    iob->bind____skip(56);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.has_won);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.continue_months_left);
    iob->bind(BIND_SIGNATURE_INT32, &g_scenario.continue_months_chosen);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.wage_rate_paid_this_year);
    iob->bind____skip(8);
    iob->bind(BIND_SIGNATURE_UINT8, &data.finance.tribute_not_paid_last_year);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.finance.tribute_not_paid_total_years);
    iob->bind____skip(11);
    iob->bind(BIND_SIGNATURE_UINT8, &city_festival().planned_size);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT8, &city_festival().months_till_next);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &city_festival().planned_god);
    iob->bind____skip(23);
    iob->bind(BIND_SIGNATURE_INT32, &data.avg_coverage.average_religion);
    iob->bind(BIND_SIGNATURE_INT32, &data.avg_coverage.average_education);
    iob->bind(BIND_SIGNATURE_INT32, &data.avg_coverage.average_health);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_UINT8, &city_festival().first_festival_effect_months);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &city_festival().second_festival_effect_months);
    iob->bind____skip(7);
    iob->bind(BIND_SIGNATURE_UINT8, &data.sentiment.unemployment_pct);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.previous_value); // ok
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, &data.sentiment.low_mood_cause);
    iob->bind(BIND_SIGNATURE_INT32, &data.figures.security_breach_duration);
    iob->bind____skip(20);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.months_since_gift); // ok
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.gift_overdose_penalty);
    iob->bind____skip(28);
    iob->bind(BIND_SIGNATURE_INT8, &data.kingdome.kingdom_salary_penalty);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT8, &data.kingdome.kingdom_milestone_penalty);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT8, &data.kingdome.kingdom_ignored_request_penalty);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.rating_last_year);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.kingdom_change);
    iob->bind____skip(11);
    iob->bind(BIND_SIGNATURE_INT32, &data.buildings.mission_post_operational);
    iob->bind(BIND_SIGNATURE_UINT32, data.buildings.main_native_meeting);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.wage_rate_paid_last_year);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.food_needed_per_month); // 62
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.granaries.understaffed);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.granaries.not_operating);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.granaries.not_operating_with_food);
    iob->bind____skip(16);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.ra_150_export_profits_months_left);
    iob->bind____skip(11);
    iob->bind(BIND_SIGNATURE_INT32, &data.gods.angry_message_delay);
    iob->bind____skip(16);
    iob->bind(BIND_SIGNATURE_INT32, &data.taxes.estimated_income);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_UINT32, data.buildings.distribution_center);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, &data.buildings.distribution_center_building_id);
    iob->bind(BIND_SIGNATURE_INT32, &data.buildings.distribution_center_placed);
    iob->bind____skip(43);
    iob->bind(BIND_SIGNATURE_INT8, &data.buildings.fishing_boats_requested);
    iob->bind(BIND_SIGNATURE_INT8, &data.buildings.warships_requested);
    iob->bind(BIND_SIGNATURE_INT8, &data.buildings.transport_ships_requested);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT16, &data.figures.enemies);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT8, &data.sentiment.wages);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT16, &data.population.people_in_huts);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.population.people_in_residences);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_UINT16, &data.figures.kingdome_soldiers);
    iob->bind____skip(18);
    iob->bind(BIND_SIGNATURE_UINT8, &data.ratings.monument_destroyed_buildings);
    iob->bind____skip(6);
    iob->bind(BIND_SIGNATURE_UINT8, &g_distant_battle.battle.city);
    iob->bind(BIND_SIGNATURE_UINT8, &g_distant_battle.battle.enemy_strength);
    iob->bind(BIND_SIGNATURE_UINT8, &g_distant_battle.battle.egyptian_strength);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.months_until_battle);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.egyptian_months_to_travel_back);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.total_count);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_UINT8, &data.military.total_batalions);
    iob->bind(BIND_SIGNATURE_UINT8, &data.military.kingdome_service_batalions);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &data.military.total_soldiers);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, &data.buildings.trade_center_building_id);
    iob->bind(BIND_SIGNATURE_INT32, &data.figures.soldiers);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.march_enemy);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.march_horse);
    iob->bind____skip(10);
    iob->bind(BIND_SIGNATURE_INT8, &data.sentiment.include_huts);
    iob->bind____skip(16);
    iob->bind(BIND_SIGNATURE_INT32, &data.population.highest_ever);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.estimated_wages);
    iob->bind(BIND_SIGNATURE_INT32, &data.resource.luxury_goods_kinds);
    iob->bind(BIND_SIGNATURE_UINT8, &data.ratings.prosperity_max);
    iob->bind____skip(3);
    for (int i = 0; i < 10; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &data.map.largest_road_networks[i].id); // ????
        iob->bind(BIND_SIGNATURE_INT32, &data.map.largest_road_networks[i].size);
    }
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.second_luxury);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_UINT8, &city_entertainment().senet_house_has_plays);
    iob->bind____skip(6);
    iob->bind(BIND_SIGNATURE_UINT8, &city_entertainment().senet_house_message_shown);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &city_entertainment().pavilion_message_shown);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.emigration_message_shown);
    iob->bind(BIND_SIGNATURE_UINT8, &data.mission.fired_message_shown);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.mission.victory_message_shown);
    iob->bind____skip(15);
    iob->bind(BIND_SIGNATURE_INT32, &data.figures.attacking_natives);
    iob->bind____skip(28);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.requiring.more_courthouse);
    iob->bind(BIND_SIGNATURE_INT32, &data.houses.missing.any_courthouse);
    iob->bind____skip(16);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.crimes_this_month);
    iob->bind(BIND_SIGNATURE_INT32, &data.finance.gold_stolen_this_month);
    iob->bind____skip(4);
    iob->bind(BIND_SIGNATURE_INT32, &data.food_supply.hunting_lodges_working);
    iob->bind(BIND_SIGNATURE_INT32, &data.food_supply.game_meat_last_month);
    iob->bind(BIND_SIGNATURE_INT32, &data.food_supply.game_meat_this_month);
    iob->bind(BIND_SIGNATURE_INT32, &data.food_supply.fishing_wharfs_working);
    iob->bind(BIND_SIGNATURE_INT32, &data.food_supply.fish_last_month);
    iob->bind(BIND_SIGNATURE_INT32, &data.food_supply.fish_this_month);
    iob->bind____skip(28);
    iob->bind(BIND_SIGNATURE_UINT32, data.buildings.festival_square);
    iob->bind____skip(16);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.ra_no_traders_months_left);
    iob->bind____skip(97);
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &data.gods.gods[i].happy_ankhs);
    }
    iob->bind____skip(33);
    for (int i = 0; i < RESOURCES_FOODS_MAX; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &data.resource.granary_food_stored[i]);
        iob->bind____skip(2);
    }
    iob->bind____skip(292);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.ra_slightly_increased_trading_months_left);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.ra_harshly_reduced_trading_months_left);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.ra_slightly_reduced_trading_months_left);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.seth_protect_player_troops_months);
    iob->bind____skip(7);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.osiris_double_farm_yield_days);
    iob->bind____skip(3);
    iob->bind(BIND_SIGNATURE_UINT8, &data.gods.osiris_flood_will_destroy_active);
    iob->bind____skip(63);
    verify_no_crash(iob->get_offset() == 37808);
}

void city_data_chunk::bind_data(io_buffer* iob, size_t version) {
    city_data_bind_og_layout(iob);
}

void city_data_extra_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind____skip(2);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_XSTR, data.kingdome.player_name_adversary, MAX_PLAYER_NAME);
    iob->bind(BIND_SIGNATURE_XSTR, data.kingdome.player_name, MAX_PLAYER_NAME);
    iob->bind____skip(4);
}

void labor_storage_priority_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT32, &g_city.labor.categories[LABOR_CATEGORY_STORAGE].priority);
}

void labor_storage_priority_chunk::load_defaults(size_t version) {
    // before the labor split, STORAGE had no priority of its own
    g_city.labor.categories[LABOR_CATEGORY_STORAGE].priority = 0;
}

void city_graph_order_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind____skip(8);
}

// The first 64 bytes held the 16 cloud positions; they live in the "clouds" chunk now (v200) and
// these bytes are written as zero.
void building_list_small_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind____skip(64);
    iob->bind____skip(36);
    iob->bind____skip(900);
}

void building_list_large_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind____skip(6000);
    g_scenario.bind_data(iob, version, 2000);
}

void city_mission_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_UINT8, &data.mission.fired_message_shown);
    iob->bind(BIND_SIGNATURE_UINT8, &data.mission.victory_message_shown);
    verify_no_crash(iob->get_offset() == city_mission_chunk::size);
}

void city_sound_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.march_enemy);
    iob->bind(BIND_SIGNATURE_INT8, &data.sound.march_horse);
    verify_no_crash(iob->get_offset() == city_sound_chunk::size);
}

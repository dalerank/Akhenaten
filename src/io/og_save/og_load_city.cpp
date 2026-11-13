#include "io/og_save/og_load.h"

#include "city/city.h"
#include "scenario/scenario.h"

#include <cstring>
#include <type_traits>

// City state of the human player (OG city_players[1], tutankhamun city_player_types.h). Field order follows our
// city_data_bind_og_layout so a field missing here is easy to spot; widths are converted, not copied.
// OG fields with no home in our model are listed in tmp/og-save-converter.md.
namespace og {

    namespace {

        template <typename D, typename S>
        void assign(D& dst, S src) {
            dst = static_cast<std::remove_reference_t<D>>(src);
        }

    } // namespace

    void load_city_state(const savegame& s) {
        const city_player& p = s.player();
        std::memcpy(g_city.unused.other_player, &s.players[0], sizeof(city_player));

        assign(g_city.buildings.unknown_value, p.building_reserved_id);
        assign(g_city.finance.tax_percentage, p.tax_percentage);
        assign(g_city.finance.treasury.value, p.treasury);
        assign(g_city.sentiment.value, p.sentiment);
        assign(g_city.health.target_value, p.health_target);
        assign(g_city.health.value, p.health);
        assign(g_city.health.num_mortuary_workers, p.mortuary_workers);
        assign(g_city.population.current, p.population);
        assign(g_city.population.last_year, p.population_last_year);
        assign(g_city.population.school_age, p.school_age);
        assign(g_city.population.academy_age, p.academy_age);
        assign(g_city.population.total_capacity, p.total_capacity);
        assign(g_city.population.room_in_houses, p.room_in_houses);
        for (int i = 0; i < 2400; i++) {
            assign(g_city.population.monthly.values[i], p.monthly_population[i]);
        }
        assign(g_city.population.monthly.next_index, p.monthly_population_next_index);
        assign(g_city.population.monthly.count, p.monthly_population_count);
        for (int i = 0; i < 100; i++) {
            assign(g_city.population.at_age[i], p.population_at_age[i]);
        }
        for (int i = 0; i < 20; i++) {
            assign(g_city.population.at_level[i], p.population_per_level[i]);
        }
        assign(g_city.population.yearly_births, p.yearly_births);
        assign(g_city.population.yearly_deaths, p.yearly_deaths);
        assign(g_city.population.lost_removal, p.lost_removal);
        assign(g_city.migration.immigration_amount_per_batch, p.immigration_amount_per_batch);
        assign(g_city.migration.emigration_amount_per_batch, p.emigration_amount_per_batch);
        assign(g_city.migration.emigration_queue_size, p.emigration_queue_size);
        assign(g_city.migration.immigration_queue_size, p.immigration_queue_size);
        assign(g_city.population.lost_homeless, p.lost_homeless);
        assign(g_city.population.last_change, p.last_change);
        assign(g_city.population.average_per_year, p.average_per_year);
        assign(g_city.population.total_all_years, p.total_all_years);
        assign(g_city.population.people_in_shanties, p.people_in_huts_and_shanties);
        assign(g_city.population.people_in_manors, p.people_in_manors_and_up);
        assign(g_city.population.total_years, p.total_years);
        assign(g_city.population.yearly_update_requested, p.yearly_update_requested);
        assign(g_city.population.last_used_house_add, p.last_used_house_add);
        assign(g_city.population.last_used_house_remove, p.last_used_house_remove);
        assign(g_city.migration.immigrated_today, p.immigrated_today);
        assign(g_city.migration.emigrated_today, p.emigrated_today);
        assign(g_city.migration.refused_immigrants_today, p.refused_immigrants_today);
        assign(g_city.migration.percentage, p.migration_percentage);
        assign(g_city.migration.emigration_duration, p.emigration_duration);
        assign(g_city.migration.immigration_duration, p.immigration_duration);
        assign(g_city.migration.newcomers, p.migration_newcomers);
        g_city.map.entry_point = tile2i(p.entry_point_x, p.entry_point_y);
        g_city.map.exit_point = tile2i(p.exit_point_x, p.exit_point_y);
        for (int i = 0; i < 36; i++) {
            assign(g_city.resource.trade_status[i + 1], p.trade_status[1 + i]);
        }
        for (int i = 0; i < 36; i++) {
            assign(g_city.resource.trading_amount[i + 1], p.trading_amount[1 + i]);
        }
        for (int i = 0; i < 36; i++) {
            assign(g_city.resource.mothballed[i + 1], p.mothballed[1 + i]);
        }
        for (int i = 0; i < 36; i++) {
            assign(g_city.resource.stockpiled[i], p.stockpiled[i]);
        }
        assign(g_city.resource.food_supply_months, p.food_supply_months);
        assign(g_city.resource.granaries.operating, p.granaries_operating);
        assign(g_city.population.percentage_plebs, p.percentage_plebs);
        assign(g_city.population.working_age, p.working_age);
        assign(g_city.labor.workers_available, p.workers_available);
        for (int i = 0; i < 10; i++) {
            assign(g_city.labor.categories[i].workers_needed, p.labor_categories[i].workers_needed);
            assign(g_city.labor.categories[i].workers_allocated, p.labor_categories[i].workers_allocated);
            assign(g_city.labor.categories[i].total_houses_covered, p.labor_categories[i].total_houses_covered);
            assign(g_city.labor.categories[i].buildings, p.labor_categories[i].buildings);
            assign(g_city.labor.categories[i].priority, p.labor_categories[i].priority);
        }
        assign(g_city.labor.workers_employed, p.workers_employed);
        assign(g_city.labor.workers_unemployed, p.workers_unemployed);
        assign(g_city.labor.unemployment_percentage, p.unemployment_percentage);
        assign(g_city.labor.unemployment_percentage_for_goverment, p.unemployment_percentage_for_senate);
        assign(g_city.labor.workers_needed, p.workers_needed);
        assign(g_city.finance.wages, p.wages);
        assign(g_city.finance.wages_kingdome, p.wages_kingdom);
        assign(g_city.taxes.taxed_citizens, p.taxed_plebs);
        assign(g_city.taxes.taxed_nobles, p.taxed_nobles);
        assign(g_city.taxes.untaxed_citizens, p.untaxed_plebs);
        assign(g_city.taxes.untaxed_nobles, p.untaxed_nobles);
        assign(g_city.taxes.percentage_taxed_citizens, p.percentage_taxed_plebs);
        assign(g_city.taxes.percentage_taxed_nobles, p.percentage_taxed_nobles);
        assign(g_city.taxes.percentage_taxed_people, p.percentage_taxed_people);
        assign(g_city.taxes.yearly.collected_citizens, p.yearly_collected_plebs);
        assign(g_city.taxes.yearly.collected_nobles, p.yearly_collected_nobles);
        assign(g_city.taxes.yearly.uncollected_citizens, p.yearly_uncollected_plebs);
        assign(g_city.taxes.yearly.uncollected_nobles, p.yearly_uncollected_nobles);
        assign(g_city.finance.this_year.income.taxes, p.taxes_this_year);
        assign(g_city.finance.last_year.income.taxes, p.taxes_last_year);
        assign(g_city.taxes.monthly.collected_citizens, p.monthly_collected_plebs);
        assign(g_city.taxes.monthly.uncollected_citizens, p.monthly_uncollected_plebs);
        assign(g_city.taxes.monthly.collected_nobles, p.monthly_collected_nobles);
        assign(g_city.taxes.monthly.uncollected_nobles, p.monthly_uncollected_nobles);
        assign(g_city.finance.this_year.income.exports, p.exports_this_year);
        assign(g_city.finance.last_year.income.exports, p.exports_last_year);
        assign(g_city.finance.this_year.expenses.imports, p.imports_this_year);
        assign(g_city.finance.last_year.expenses.imports, p.imports_last_year);
        assign(g_city.finance.interest_so_far, p.interest_so_far);
        assign(g_city.finance.last_year.expenses.interest, p.interest_last_year);
        assign(g_city.finance.this_year.expenses.interest, p.interest_this_year);
        assign(g_city.finance.last_year.expenses.stolen, p.stolen_last_year);
        assign(g_city.finance.this_year.expenses.stolen, p.stolen_this_year);
        assign(g_city.finance.last_year.expenses.construction, p.construction_last_year);
        assign(g_city.finance.this_year.expenses.construction, p.construction_this_year);
        assign(g_city.finance.last_year.expenses.accountant_salary, p.salary_last_year);
        assign(g_city.finance.this_year.expenses.accountant_salary, p.salary_this_year);
        assign(g_city.kingdome.salary_amount, p.salary_amount);
        assign(g_city.kingdome.salary_rank, p.salary_rank);
        assign(g_city.finance.this_year.expenses.mayour_salary, p.salary_so_far);
        assign(g_city.finance.last_year.income.total, p.income_last_year);
        assign(g_city.finance.this_year.income.total, p.income_this_year);
        assign(g_city.finance.last_year.expenses.total, p.expenses_last_year);
        assign(g_city.finance.this_year.expenses.total, p.expenses_this_year);
        assign(g_city.finance.last_year.net_in_out, p.net_in_out_last_year);
        assign(g_city.finance.this_year.net_in_out, p.net_in_out_this_year);
        assign(g_city.finance.last_year.balance, p.balance_last_year);
        assign(g_city.finance.this_year.balance, p.balance_this_year);
        assign(g_city.finance.wages_so_far, p.wages_so_far);
        assign(g_city.finance.this_year.expenses.wages, p.wages_this_year);
        assign(g_city.finance.last_year.expenses.wages, p.wages_last_year);
        assign(g_city.finance.this_year.income.gold_delivered, p.gold_this_year);
        assign(g_city.finance.last_year.income.gold_delivered, p.gold_last_year);
        assign(g_city.kingdome.months_in_debt, p.months_in_debt);
        assign(g_city.trade.caravan_import_resource, p.caravan_import_resource);
        assign(g_city.trade.caravan_backup_import_resource, p.caravan_backup_import_resource);
        assign(g_city.ratings.culture, p.rating_culture);
        assign(g_city.ratings.prosperity, p.rating_prosperity);
        assign(g_city.ratings.monument, p.rating_monument);
        assign(g_city.kingdome.rating, p.rating_kingdom);
        assign(g_city.ratings.prosperity_trend, p.prosperity_trend);
        assign(g_city.ratings.monument_num_criminals, p.monument_num_criminals);
        assign(g_city.ratings.monument_num_rioters, p.monument_num_rioters);
        assign(g_city.houses.missing.fountain, p.houses_missing_water_supply);
        assign(g_city.houses.missing.well, p.houses_missing_well);
        assign(g_city.houses.missing.more_entertainment, p.houses_missing_more_entertainment);
        assign(g_city.houses.missing.more_education, p.houses_missing_more_education);
        assign(g_city.houses.missing.education, p.houses_missing_education);
        assign(g_city.houses.requiring.school, p.houses_requiring_school);
        assign(g_city.houses.requiring.library, p.houses_requiring_library);
        assign(g_city.houses.missing.apothecary, p.houses_missing_dentist);
        assign(g_city.houses.missing.dentist, p.houses_missing_courthouse);
        assign(g_city.houses.missing.food, p.houses_missing_food);
        assign(g_city.houses.missing.mortuary, p.houses_missing_health);
        assign(g_city.houses.missing.physician, p.houses_missing_more_health);
        assign(g_city.houses.requiring.dentist, p.houses_requiring_dentist);
        assign(g_city.houses.requiring.water_supply, p.houses_requiring_courthouse);
        assign(g_city.houses.requiring.physician, p.houses_requiring_health);
        assign(g_city.houses.missing.religion, p.houses_missing_religion);
        assign(g_city.houses.missing.second_religion, p.houses_missing_second_religion);
        assign(g_city.houses.missing.third_religion, p.houses_missing_third_religion);
        assign(g_city.houses.requiring.religion, p.houses_requiring_religion);
        assign(g_city.entertainment.booth_shows, p.juggler_shows);
        assign(g_city.entertainment.booth_no_shows_weighted, p.juggler_no_shows_weighted);
        assign(g_city.entertainment.bandstand_shows, p.musician_shows);
        assign(g_city.entertainment.bandstand_no_shows_weighted, p.musician_no_shows_weighted);
        assign(g_city.entertainment.pavilion_shows, p.dancer_shows);
        assign(g_city.entertainment.pavilion_no_shows_weighted, p.dancer_no_shows_weighted);
        assign(g_city.entertainment.senet_house_plays, p.senet_shows);
        assign(g_city.entertainment.senet_house_no_shows_weighted, p.senet_no_shows_weighted);
        assign(g_city.entertainment.venue_needing_shows, p.venue_needing_shows);
        assign(g_city.avg_coverage.average_entertainment, p.average_entertainment);
        assign(g_city.houses.missing.entertainment, p.houses_missing_entertainment);
        assign(g_city.festival.months_since_festival, p.months_since_festival);
        for (int i = 0; i < 5; i++) {
            assign(g_city.religion.gods[i].target_mood, p.god_target_mood[i]);
        }
        for (int i = 0; i < 5; i++) {
            assign(g_city.religion.gods[i].mood, p.god_mood[i]);
        }
        for (int i = 0; i < 5; i++) {
            assign(g_city.religion.gods[i].wrath_bolts, p.god_wrath_bolts[i]);
        }
        for (int i = 0; i < 5; i++) {
            assign(g_city.religion.gods[i].months_since_festival, p.god_months_since_festival[i]);
        }
        assign(g_city.religion.least_happy_god, p.least_happy_god);
        assign(g_city.migration.no_immigration_cause, p.no_immigration_cause);
        assign(g_city.sentiment.protesters, p.protesters);
        assign(g_city.sentiment.criminals, p.thefts);
        assign(g_city.houses.health, p.health_demand);
        assign(g_city.houses.religion, p.religion_demand);
        assign(g_city.houses.education, p.education_demand);
        assign(g_city.houses.entertainment, p.entertainment_demand);
        assign(g_city.figures.rioters, p.rioters);
        assign(g_city.ratings.culture_explanation, p.culture_explanation);
        assign(g_city.ratings.prosperity_explanation, p.prosperity_explanation);
        assign(g_city.kingdome.player_rank, p.player_rank);
        assign(g_city.kingdome.personal_savings, p.personal_savings);
        assign(g_city.finance.last_year.income.donated, p.donated_last_year);
        assign(g_city.finance.this_year.income.donated, p.donated_this_year);
        assign(g_city.figures.animals_number, p.animals);
        assign(g_city.trade.docker_import_resource, p.docker_import_resource);
        assign(g_city.trade.docker_export_resource, p.docker_export_resource);
        assign(g_scenario.has_won, p.mission_has_won);
        assign(g_scenario.continue_months_left, p.mission_continue_months_left);
        assign(g_scenario.continue_months_chosen, p.mission_continue_months_chosen);
        assign(g_city.finance.wage_rate_paid_this_year, p.wage_rate_paid_this_year);
        assign(g_city.finance.tribute_not_paid_last_year, p.tribute_not_paid_last_year);
        assign(g_city.finance.tribute_not_paid_total_years, p.tribute_not_paid_total_years);
        assign(g_city.festival.planned_size, p.festival_planned_size);
        assign(g_city.festival.months_till_next, p.festival_planned_months_to_go);
        assign(g_city.festival.planned_god, p.festival_planned_god);
        assign(g_city.avg_coverage.average_religion, p.average_religion);
        assign(g_city.avg_coverage.average_education, p.average_education);
        assign(g_city.avg_coverage.average_health, p.average_health);
        assign(g_city.festival.first_festival_effect_months, p.first_festival_effect_months);
        assign(g_city.festival.second_festival_effect_months, p.second_festival_effect_months);
        assign(g_city.sentiment.unemployment_pct, p.sentiment_unemployment);
        assign(g_city.sentiment.previous_value, p.sentiment_previous_value);
        assign(g_city.sentiment.low_mood_cause, p.sentiment_low_mood_cause);
        assign(g_city.figures.security_breach_duration, p.security_breach_duration);
        assign(g_city.kingdome.months_since_gift, p.months_since_gift);
        assign(g_city.kingdome.gift_overdose_penalty, p.gift_overdose_penalty);
        assign(g_city.kingdome.kingdom_salary_penalty, p.kingdom_salary_penalty);
        assign(g_city.kingdome.kingdom_milestone_penalty, p.kingdom_milestone_penalty);
        assign(g_city.kingdome.kingdom_ignored_request_penalty, p.kingdom_ignored_request_penalty);
        assign(g_city.kingdome.rating_last_year, p.kingdom_last_year);
        assign(g_city.kingdome.kingdom_change, p.kingdom_change);
        assign(g_city.buildings.mission_post_operational, p.mission_post_operational);
        g_city.buildings.main_native_meeting = tile2i(p.main_native_meeting_x, p.main_native_meeting_y);
        assign(g_city.finance.wage_rate_paid_last_year, p.wage_rate_paid_last_year);
        assign(g_city.resource.food_needed_per_month, p.food_needed_per_month);
        assign(g_city.resource.granaries.understaffed, p.granaries_understaffed);
        assign(g_city.resource.granaries.not_operating, p.granaries_not_operating);
        assign(g_city.resource.granaries.not_operating_with_food, p.granaries_not_operating_with_food);
        assign(g_city.religion.ra_150_export_profits_months_left, p.ra_exports_bonus_months);
        assign(g_city.religion.angry_message_delay, p.gods_angry_message_delay);
        assign(g_city.taxes.estimated_income, p.estimated_tax_income);
        g_city.buildings.distribution_center = tile2i(p.distribution_center_x, p.distribution_center_y);
        assign(g_city.buildings.distribution_center_building_id, p.distribution_center_building_id);
        assign(g_city.buildings.distribution_center_placed, p.distribution_center_placed);
        assign(g_city.buildings.warships_requested, p.shipyard_boats_requested);
        assign(g_city.figures.enemies, p.enemies);
        assign(g_city.sentiment.wages, p.sentiment_wages);
        assign(g_city.population.people_in_huts, p.people_in_huts);
        assign(g_city.population.people_in_residences, p.people_in_residences_and_up);
        assign(g_city.figures.kingdome_soldiers, p.kingdom_soldiers);
        assign(g_city.ratings.monument_destroyed_buildings, p.destroyed_buildings);
        assign(g_city.military.total_batalions, p.total_legions);
        assign(g_city.military.kingdome_service_batalions, p.empire_service_legions);
        assign(g_city.military.total_soldiers, p.total_soldiers);
        assign(g_city.buildings.trade_center_building_id, p.trade_center_building_id);
        assign(g_city.figures.soldiers, p.soldiers);
        assign(g_city.sound.march_enemy, p.sound_march_enemy);
        assign(g_city.sound.march_horse, p.sound_march_horse);
        assign(g_city.sentiment.include_huts, p.sentiment_food_toggle);
        assign(g_city.population.highest_ever, p.population_highest_ever);
        assign(g_city.finance.estimated_wages, p.estimated_wages);
        assign(g_city.ratings.prosperity_max, p.prosperity_max);
        for (int i = 0; i < 10; i++) {
            assign(g_city.map.largest_road_networks[i].id, p.largest_road_networks[i].id);
            assign(g_city.map.largest_road_networks[i].size, p.largest_road_networks[i].size);
        }
        assign(g_city.houses.missing.second_wine, p.houses_missing_second_luxury);
        assign(g_city.entertainment.senet_house_has_plays, p.senet_house_has_plays);
        assign(g_city.mission.fired_message_shown, p.fired_message_shown);
        assign(g_city.mission.victory_message_shown, p.victory_message_shown);
        assign(g_city.figures.attacking_natives, p.attacking_natives);
        g_city.buildings.festival_square = tile2i(p.festival_square_x, p.festival_square_y);
        assign(g_city.religion.ra_no_traders_months_left, p.ra_no_traders_months);
        for (int i = 0; i < 5; i++) {
            assign(g_city.religion.gods[i].happy_ankhs, p.god_happy_bolts[i]);
        }
        for (int i = 0; i < 9; i++) {
            assign(g_city.resource.granary_food_stored[i], p.granary_food_stored[i]);
        }
        assign(g_city.religion.ra_slightly_increased_trading_months_left, p.ra_trade_bonus_months);
        assign(g_city.religion.ra_harshly_reduced_trading_months_left, p.ra_trade_penalty_months);
        assign(g_city.religion.ra_slightly_reduced_trading_months_left, p.ra_trade_minor_penalty_months);
        assign(g_city.religion.seth_protect_player_troops_months, p.seth_minor_blessing_months);
        assign(g_city.religion.osiris_double_farm_yield_days, p.osiris_double_farm_yield);
        assign(g_city.religion.osiris_flood_will_destroy_active, p.osiris_flood_destroys_farms);
    }

} // namespace og

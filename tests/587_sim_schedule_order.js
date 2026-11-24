// The simulation schedule (e_sim_step in game/sim_schedule.h) is the one place that orders what runs each tick slot,
// day, week, month and year. This test pins that order: a step moved, added or removed fails here until the expected
// list is updated on purpose.

var __test587_ok = false

var T587_EXPECTED = [
    'SIM_PHASE_TICK_BEGIN:-1:sim_step_housing_type_counts',
    'SIM_PHASE_TICK_BEGIN:-1:sim_step_random',
    'SIM_PHASE_TICK_BEGIN:-1:sim_step_undo_time',
    'SIM_PHASE_TICK_BEGIN:-1:sim_step_floods',
    'SIM_PHASE_TICK_BEGIN:-1:sim_step_buildings_tick',
    'SIM_PHASE_TICK_SLOT:1:sim_step_religion',
    'SIM_PHASE_TICK_SLOT:1:sim_step_coverage',
    'SIM_PHASE_TICK_SLOT:2:sim_step_tree_growth',
    'SIM_PHASE_TICK_SLOT:4:sim_step_kingdome',
    'SIM_PHASE_TICK_SLOT:5:sim_step_irrigation_value',
    'SIM_PHASE_TICK_SLOT:5:sim_step_formations',
    'SIM_PHASE_TICK_SLOT:6:sim_step_natives_land',
    'SIM_PHASE_TICK_SLOT:7:sim_step_road_network',
    'SIM_PHASE_TICK_SLOT:8:sim_step_stocks',
    'SIM_PHASE_TICK_SLOT:9:sim_step_house_service_decay',
    'SIM_PHASE_TICK_SLOT:10:sim_step_desirability',
    'SIM_PHASE_TICK_SLOT:11:sim_step_trade_export_keep',
    'SIM_PHASE_TICK_SLOT:12:sim_step_houses_covered_decay',
    'SIM_PHASE_TICK_SLOT:16:sim_step_storageyard_stocks',
    'SIM_PHASE_TICK_SLOT:17:sim_step_food_stocks',
    'SIM_PHASE_TICK_SLOT:18:sim_step_vegetation_growth',
    'SIM_PHASE_TICK_SLOT:19:sim_step_open_water_access',
    'SIM_PHASE_TICK_SLOT:20:sim_step_industry_production',
    'SIM_PHASE_TICK_SLOT:21:sim_step_kingdome_access',
    'SIM_PHASE_TICK_SLOT:22:sim_step_population_room',
    'SIM_PHASE_TICK_SLOT:23:sim_step_migration',
    'SIM_PHASE_TICK_SLOT:23:sim_step_population_migration',
    'SIM_PHASE_TICK_SLOT:24:sim_step_evict_overcrowded',
    'SIM_PHASE_TICK_SLOT:25:sim_step_labor',
    'SIM_PHASE_TICK_SLOT:27:sim_step_water_supply',
    'SIM_PHASE_TICK_SLOT:28:sim_step_religion_supply',
    'SIM_PHASE_TICK_SLOT:29:sim_step_formations_skip_morale',
    'SIM_PHASE_TICK_SLOT:30:sim_step_crime',
    'SIM_PHASE_TICK_SLOT:31:sim_step_tower_sentry_decay',
    'SIM_PHASE_TICK_SLOT:31:sim_step_generate_figures',
    'SIM_PHASE_TICK_SLOT:32:sim_step_empire_traders',
    'SIM_PHASE_TICK_SLOT:32:sim_step_trade',
    'SIM_PHASE_TICK_SLOT:33:sim_step_building_counters',
    'SIM_PHASE_TICK_SLOT:33:sim_step_avg_coverage_33',
    'SIM_PHASE_TICK_SLOT:33:sim_step_health_coverage',
    'SIM_PHASE_TICK_SLOT:33:sim_step_farms',
    'SIM_PHASE_TICK_SLOT:34:sim_step_distribute_treasury',
    'SIM_PHASE_TICK_SLOT:35:sim_step_house_health',
    'SIM_PHASE_TICK_SLOT:36:sim_step_culture_aggregates',
    'SIM_PHASE_TICK_SLOT:37:sim_step_malaria_risk',
    'SIM_PHASE_TICK_SLOT:38:sim_step_building_desirability',
    'SIM_PHASE_TICK_SLOT:39:sim_step_house_evolve',
    'SIM_PHASE_TICK_SLOT:40:sim_step_building_state',
    'SIM_PHASE_TICK_SLOT:43:sim_step_burning_ruins',
    'SIM_PHASE_TICK_SLOT:44:sim_step_building_destroying',
    'SIM_PHASE_TICK_SLOT:44:sim_step_reset_protesters',
    'SIM_PHASE_TICK_SLOT:45:sim_step_criminals',
    'SIM_PHASE_TICK_SLOT:46:sim_step_building_malaria_risk',
    'SIM_PHASE_TICK_SLOT:48:sim_step_house_tax_coverage_decay',
    'SIM_PHASE_TICK_SLOT:49:sim_step_avg_coverage_49',
    'SIM_PHASE_TICK_CITY_END:-1:sim_step_plagues',
    'SIM_PHASE_TICK_END:-1:sim_step_figures',
    'SIM_PHASE_TICK_END:-1:sim_step_scenario',
    'SIM_PHASE_DAY:-1:sim_step_distant_battle',
    'SIM_PHASE_DAY:-1:sim_step_invasion_auto_resolve',
    'SIM_PHASE_DAY:-1:sim_step_sentiment',
    'SIM_PHASE_DAY:-1:sim_step_criminals_day',
    'SIM_PHASE_DAY:-1:sim_step_funeral_walkers',
    'SIM_PHASE_DAY:-1:sim_step_plague_day',
    'SIM_PHASE_DAY:-1:sim_step_flotsam',
    'SIM_PHASE_DAY:-1:sim_step_buildings_day',
    'SIM_PHASE_DAY:-1:sim_step_figures_day',
    'SIM_PHASE_DAY:-1:sim_step_population_day',
    'SIM_PHASE_DAY:-1:sim_step_victory',
    'SIM_PHASE_DAY:-1:sim_step_avg_coverage_day',
    'SIM_PHASE_DAY:-1:sim_step_event_advance_day',
    'SIM_PHASE_WEEK:-1:sim_step_food_weekly',
    'SIM_PHASE_WEEK:-1:sim_step_industry_nearby_houses',
    'SIM_PHASE_WEEK:-1:sim_step_event_advance_week',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_migration_month',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_health_month',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_population_at_levels',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_taxes_month',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_finance_month',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_food_monthly',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_resource_month',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_food_supply_month',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_allowed_foods',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_population_record',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_local_cults',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_festival',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_buildings_month',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_fishing_points',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_kingdome_month',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_tomb_robbers_month',
    'SIM_PHASE_MONTH:-1:sim_step_distant_battle_month',
    'SIM_PHASE_MONTH:-1:sim_step_random_month',
    'SIM_PHASE_MONTH:-1:sim_step_empire_month',
    'SIM_PHASE_MONTH:-1:sim_step_random_events',
    'SIM_PHASE_MONTH:-1:sim_step_invasions',
    'SIM_PHASE_MONTH:-1:sim_step_scenario_events',
    'SIM_PHASE_MONTH:-1:sim_step_invasion_bind_resolutions',
    'SIM_PHASE_MONTH:-1:sim_step_invasion_process',
    'SIM_PHASE_MONTH:-1:sim_step_morale_at_rest',
    'SIM_PHASE_MONTH:-1:sim_step_messages',
    'SIM_PHASE_MONTH:-1:sim_step_roads_images',
    'SIM_PHASE_MONTH:-1:sim_step_land_citizen_routing',
    'SIM_PHASE_MONTH:-1:sim_step_locusts_month',
    'SIM_PHASE_MONTH_END:-1:sim_step_estimate_taxes',
    'SIM_PHASE_MONTH_END:-1:sim_step_event_advance_month',
    'SIM_PHASE_YEAR:-1:sim_step_empire_expansion',
    'SIM_PHASE_YEAR:-1:sim_step_undo_disable',
    'SIM_PHASE_YEAR:-1:sim_step_simtime_year',
    'SIM_PHASE_YEAR:-1:sim_step_population_yearly_request',
    'SIM_PHASE_YEAR:-1:sim_step_taxes_year',
    'SIM_PHASE_YEAR:-1:sim_step_finance_year',
    'SIM_PHASE_YEAR:-1:sim_step_migration_year',
    'SIM_PHASE_YEAR:-1:sim_step_monuments_year',
    'SIM_PHASE_YEAR:-1:sim_step_yearly_trade_amounts',
    'SIM_PHASE_YEAR:-1:sim_step_ratings_year',
    'SIM_PHASE_YEAR:-1:sim_step_temple_complexes',
    'SIM_PHASE_YEAR:-1:sim_step_buildings_year',
]

function t587_fail(msg) {
    __log_info_native('[test:587] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    var steps = __test_sim_schedule().split(';').filter(function (s) { return s.length > 0 })
    if (steps.length != T587_EXPECTED.length) {
        return t587_fail('schedule has ' + steps.length + ' steps, expected ' + T587_EXPECTED.length)
    }
    for (var i = 0; i < steps.length; i++) {
        if (steps[i] != T587_EXPECTED[i]) {
            return t587_fail('step ' + i + ' is ' + steps[i] + ', expected ' + T587_EXPECTED[i])
        }
    }

    __log_marker('sim_schedule_ok')
    __test587_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test587_ok && __test_find_inlog('[test-marker] sim_schedule_ok')
}

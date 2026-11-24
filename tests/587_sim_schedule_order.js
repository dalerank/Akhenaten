// The simulation schedule (e_sim_step in game/sim_schedule.h) is the one place that orders what runs each tick slot,
// day, week, month and year, and what each step writes. This test pins that order: a step moved, added, removed or given new
// writes fails here until the expected list is updated on purpose. It also pins the places where two steps write the
// same area in the same tick slot and the steps that run more than once a day, so new ones do not appear silently.

var __test587_ok = false

var T587_EXPECTED = [
    'SIM_PHASE_TICK_BEGIN:-1:sim_step_housing_type_counts:1',
    'SIM_PHASE_TICK_BEGIN:-1:sim_step_random:33554432',
    'SIM_PHASE_TICK_BEGIN:-1:sim_step_undo_time:67108864',
    'SIM_PHASE_TICK_BEGIN:-1:sim_step_floods:4210688',
    'SIM_PHASE_TICK_BEGIN:-1:sim_step_buildings_tick:4',
    'SIM_PHASE_TICK_SLOT:1:sim_step_religion:64',
    'SIM_PHASE_TICK_SLOT:1:sim_step_coverage:128',
    'SIM_PHASE_TICK_SLOT:2:sim_step_tree_growth:16384',
    'SIM_PHASE_TICK_SLOT:4:sim_step_kingdome:2048',
    'SIM_PHASE_TICK_SLOT:5:sim_step_irrigation_value:16384',
    'SIM_PHASE_TICK_SLOT:5:sim_step_formations:32768',
    'SIM_PHASE_TICK_SLOT:6:sim_step_natives_land:16384',
    'SIM_PHASE_TICK_SLOT:7:sim_step_road_network:16384',
    'SIM_PHASE_TICK_SLOT:8:sim_step_stocks:32',
    'SIM_PHASE_TICK_SLOT:9:sim_step_house_service_decay:2',
    'SIM_PHASE_TICK_SLOT:10:sim_step_desirability:16384',
    'SIM_PHASE_TICK_SLOT:11:sim_step_trade_export_keep:1024',
    'SIM_PHASE_TICK_SLOT:12:sim_step_houses_covered_decay:4',
    'SIM_PHASE_TICK_SLOT:16:sim_step_storageyard_stocks:32',
    'SIM_PHASE_TICK_SLOT:17:sim_step_food_stocks:32',
    'SIM_PHASE_TICK_SLOT:18:sim_step_vegetation_growth:16384',
    'SIM_PHASE_TICK_SLOT:19:sim_step_open_water_access:4',
    'SIM_PHASE_TICK_SLOT:20:sim_step_industry_production:4',
    'SIM_PHASE_TICK_SLOT:21:sim_step_kingdome_access:4',
    'SIM_PHASE_TICK_SLOT:22:sim_step_population_room:1',
    'SIM_PHASE_TICK_SLOT:23:sim_step_migration:65536',
    'SIM_PHASE_TICK_SLOT:23:sim_step_population_migration:1',
    'SIM_PHASE_TICK_SLOT:24:sim_step_evict_overcrowded:9',
    'SIM_PHASE_TICK_SLOT:25:sim_step_labor:512',
    'SIM_PHASE_TICK_SLOT:27:sim_step_water_supply:4',
    'SIM_PHASE_TICK_SLOT:28:sim_step_religion_supply:2',
    'SIM_PHASE_TICK_SLOT:29:sim_step_formations_skip_morale:32768',
    'SIM_PHASE_TICK_SLOT:30:sim_step_crime:8192',
    'SIM_PHASE_TICK_SLOT:31:sim_step_tower_sentry_decay:32768',
    'SIM_PHASE_TICK_SLOT:31:sim_step_generate_figures:8',
    'SIM_PHASE_TICK_SLOT:32:sim_step_empire_traders:1032',
    'SIM_PHASE_TICK_SLOT:32:sim_step_trade:1032',
    'SIM_PHASE_TICK_SLOT:33:sim_step_building_counters:4',
    'SIM_PHASE_TICK_SLOT:33:sim_step_avg_coverage_33:128',
    'SIM_PHASE_TICK_SLOT:33:sim_step_health_coverage:384',
    'SIM_PHASE_TICK_SLOT:33:sim_step_farms:4',
    'SIM_PHASE_TICK_SLOT:34:sim_step_distribute_treasury:20',
    'SIM_PHASE_TICK_SLOT:35:sim_step_house_health:2',
    'SIM_PHASE_TICK_SLOT:36:sim_step_culture_aggregates:2',
    'SIM_PHASE_TICK_SLOT:37:sim_step_malaria_risk:16384',
    'SIM_PHASE_TICK_SLOT:38:sim_step_building_desirability:4',
    'SIM_PHASE_TICK_SLOT:39:sim_step_house_evolve:16390',
    'SIM_PHASE_TICK_SLOT:40:sim_step_building_state:4',
    'SIM_PHASE_TICK_SLOT:43:sim_step_burning_ruins:4',
    'SIM_PHASE_TICK_SLOT:44:sim_step_building_destroying:4',
    'SIM_PHASE_TICK_SLOT:44:sim_step_reset_protesters:4096',
    'SIM_PHASE_TICK_SLOT:45:sim_step_criminals:8200',
    'SIM_PHASE_TICK_SLOT:46:sim_step_building_malaria_risk:4',
    'SIM_PHASE_TICK_SLOT:48:sim_step_house_tax_coverage_decay:2',
    'SIM_PHASE_TICK_SLOT:49:sim_step_avg_coverage_49:128',
    'SIM_PHASE_TICK_CITY_END:-1:sim_step_plagues:256',
    'SIM_PHASE_TICK_END:-1:sim_step_figures:8',
    'SIM_PHASE_TICK_END:-1:sim_step_scenario:1048576',
    'SIM_PHASE_DAY:-1:sim_step_distant_battle:32768',
    'SIM_PHASE_DAY:-1:sim_step_invasion_auto_resolve:32768',
    'SIM_PHASE_DAY:-1:sim_step_sentiment:4096',
    'SIM_PHASE_DAY:-1:sim_step_criminals_day:8194',
    'SIM_PHASE_DAY:-1:sim_step_funeral_walkers:8',
    'SIM_PHASE_DAY:-1:sim_step_plague_day:258',
    'SIM_PHASE_DAY:-1:sim_step_flotsam:8',
    'SIM_PHASE_DAY:-1:sim_step_buildings_day:4',
    'SIM_PHASE_DAY:-1:sim_step_figures_day:8',
    'SIM_PHASE_DAY:-1:sim_step_population_day:1',
    'SIM_PHASE_DAY:-1:sim_step_victory:134217728',
    'SIM_PHASE_DAY:-1:sim_step_avg_coverage_day:128',
    'SIM_PHASE_DAY:-1:sim_step_event_advance_day:268435456',
    'SIM_PHASE_WEEK:-1:sim_step_food_weekly:34',
    'SIM_PHASE_WEEK:-1:sim_step_industry_nearby_houses:4',
    'SIM_PHASE_WEEK:-1:sim_step_event_advance_week:268435456',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_migration_month:65536',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_health_month:256',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_population_at_levels:1',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_taxes_month:536870928',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_finance_month:16',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_food_monthly:34',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_resource_month:32',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_food_supply_month:32',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_allowed_foods:32',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_population_record:1',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_local_cults:64',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_festival:8388608',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_buildings_month:4',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_fishing_points:8',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_kingdome_month:2048',
    'SIM_PHASE_MONTH_CITY:-1:sim_step_tomb_robbers_month:8',
    'SIM_PHASE_MONTH:-1:sim_step_distant_battle_month:32768',
    'SIM_PHASE_MONTH:-1:sim_step_random_month:33554432',
    'SIM_PHASE_MONTH:-1:sim_step_empire_month:524288',
    'SIM_PHASE_MONTH:-1:sim_step_random_events:1048576',
    'SIM_PHASE_MONTH:-1:sim_step_invasions:1081344',
    'SIM_PHASE_MONTH:-1:sim_step_scenario_events:1048576',
    'SIM_PHASE_MONTH:-1:sim_step_invasion_bind_resolutions:32768',
    'SIM_PHASE_MONTH:-1:sim_step_invasion_process:1081344',
    'SIM_PHASE_MONTH:-1:sim_step_morale_at_rest:32768',
    'SIM_PHASE_MONTH:-1:sim_step_messages:262144',
    'SIM_PHASE_MONTH:-1:sim_step_roads_images:16384',
    'SIM_PHASE_MONTH:-1:sim_step_land_citizen_routing:16384',
    'SIM_PHASE_MONTH:-1:sim_step_locusts_month:8',
    'SIM_PHASE_MONTH_END:-1:sim_step_estimate_taxes:536870928',
    'SIM_PHASE_MONTH_END:-1:sim_step_event_advance_month:268435456',
    'SIM_PHASE_YEAR:-1:sim_step_empire_expansion:524288',
    'SIM_PHASE_YEAR:-1:sim_step_undo_disable:67108864',
    'SIM_PHASE_YEAR:-1:sim_step_simtime_year:16777216',
    'SIM_PHASE_YEAR:-1:sim_step_population_yearly_request:1',
    'SIM_PHASE_YEAR:-1:sim_step_taxes_year:536870930',
    'SIM_PHASE_YEAR:-1:sim_step_finance_year:16',
    'SIM_PHASE_YEAR:-1:sim_step_migration_year:65536',
    'SIM_PHASE_YEAR:-1:sim_step_monuments_year:2097152',
    'SIM_PHASE_YEAR:-1:sim_step_yearly_trade_amounts:525312',
    'SIM_PHASE_YEAR:-1:sim_step_ratings_year:131072',
    'SIM_PHASE_YEAR:-1:sim_step_temple_complexes:64',
    'SIM_PHASE_YEAR:-1:sim_step_buildings_year:4',
]

var T587_SAME_SLOT_WRITERS = ['SIM_PHASE_TICK_SLOT:32:trade:1024', 'SIM_PHASE_TICK_SLOT:32:figures:8',
    'SIM_PHASE_TICK_SLOT:33:buildings:4', 'SIM_PHASE_TICK_SLOT:33:coverage:128']
var T587_REPEATED = []

function t587_fail(msg) {
    __log_info_native('[test:587] FAIL: ' + msg)
    __test_signal_ready()
}

function t587_area_names(mask) {
    var names = {1: 'population', 2: 'houses', 4: 'buildings', 8: 'figures', 16: 'finance', 32: 'resources',
        64: 'religion', 128: 'coverage', 256: 'health', 512: 'labor', 1024: 'trade', 2048: 'kingdom', 536870912: 'taxes'}
    return names[mask] || ('' + mask)
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

    var by_slot = {}
    var per_day = {}
    for (var j = 0; j < steps.length; j++) {
        var p = steps[j].split(':')
        var phase = p[0], slot = p[1], name = p[2], writes = parseInt(p[3])
        if (phase == 'SIM_PHASE_TICK_SLOT' || phase == 'SIM_PHASE_DAY') {
            per_day[name] = (per_day[name] || 0) + 1
        }
        if (phase != 'SIM_PHASE_TICK_SLOT') {
            continue
        }
        for (var bit = 1; bit <= (1 << 28); bit *= 2) {
            if (writes & bit) {
                var key = 'SIM_PHASE_TICK_SLOT:' + slot + ':' + bit
                by_slot[key] = (by_slot[key] || 0) + 1
            }
        }
    }
    var same = []
    for (var k in by_slot) {
        if (by_slot[k] > 1) {
            var q = k.split(':')
            same.push(q[0] + ':' + q[1] + ':' + t587_area_names(parseInt(q[2])) + ':' + q[2])
        }
    }
    same.sort()
    var expected_same = T587_SAME_SLOT_WRITERS.slice().sort()
    if (same.join(',') != expected_same.join(',')) {
        return t587_fail('same-slot writers ' + same.join(',') + ', expected ' + expected_same.join(','))
    }
    var repeated = []
    for (var n in per_day) {
        if (per_day[n] > 1) {
            repeated.push(n + ':' + per_day[n])
        }
    }
    repeated.sort()
    if (repeated.join(',') != T587_REPEATED.join(',')) {
        return t587_fail('steps run more than once a day ' + repeated.join(',') + ', expected ' + T587_REPEATED.join(','))
    }

    __log_marker('sim_schedule_ok')
    __test587_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test587_ok && __test_find_inlog('[test-marker] sim_schedule_ok')
}

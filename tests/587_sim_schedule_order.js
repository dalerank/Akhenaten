// The simulation schedule (game/sim_schedule.cpp) is the one place that orders what runs each tick slot, day, week,
// month and year, and what each step writes. This test pins that order: a step moved, added, removed or given new
// writes fails here until the expected list is updated on purpose. It also pins the places where two steps write the
// same area in the same tick slot and the steps that run more than once a day, so new ones do not appear silently.

var __test587_ok = false

var T587_EXPECTED = [
    'tick_begin:-1:housing_type_counts:1',
    'tick_begin:-1:random:33554432',
    'tick_begin:-1:undo_time:67108864',
    'tick_begin:-1:floods:4210688',
    'tick_begin:-1:buildings_tick:4',
    'tick_slot:1:religion:64',
    'tick_slot:1:coverage:128',
    'tick_slot:2:tree_growth:16384',
    'tick_slot:4:kingdome:2048',
    'tick_slot:5:irrigation_value:16384',
    'tick_slot:5:formations:32768',
    'tick_slot:6:natives_land:16384',
    'tick_slot:7:road_network:16384',
    'tick_slot:8:stocks:32',
    'tick_slot:9:house_service_decay:2',
    'tick_slot:10:desirability:16384',
    'tick_slot:11:trade_export_keep:1024',
    'tick_slot:12:houses_covered_decay:4',
    'tick_slot:16:storageyard_stocks:32',
    'tick_slot:17:food_stocks:32',
    'tick_slot:18:vegetation_growth:16384',
    'tick_slot:19:open_water_access:4',
    'tick_slot:20:industry_production:4',
    'tick_slot:21:kingdome_access:4',
    'tick_slot:22:population_room:1',
    'tick_slot:23:migration:65536',
    'tick_slot:23:population_migration:1',
    'tick_slot:24:evict_overcrowded:9',
    'tick_slot:25:labor:512',
    'tick_slot:27:water_supply:4',
    'tick_slot:28:religion_supply:2',
    'tick_slot:29:formations_skip_morale:32768',
    'tick_slot:30:crime:8192',
    'tick_slot:31:tower_sentry_decay:32768',
    'tick_slot:31:generate_figures:8',
    'tick_slot:32:empire_traders:1032',
    'tick_slot:32:trade:1032',
    'tick_slot:33:building_counters:4',
    'tick_slot:33:avg_coverage:128',
    'tick_slot:33:health_coverage:384',
    'tick_slot:33:farms:4',
    'tick_slot:34:distribute_treasury:20',
    'tick_slot:35:house_health:2',
    'tick_slot:36:culture_aggregates:2',
    'tick_slot:37:malaria_risk:16384',
    'tick_slot:38:building_desirability:4',
    'tick_slot:39:house_evolve:16390',
    'tick_slot:40:building_state:4',
    'tick_slot:43:burning_ruins:4',
    'tick_slot:44:building_destroying:4',
    'tick_slot:44:reset_protesters:4096',
    'tick_slot:45:criminals:8200',
    'tick_slot:46:building_malaria_risk:4',
    'tick_slot:48:house_tax_coverage_decay:2',
    'tick_slot:49:avg_coverage:128',
    'tick_city_end:-1:plague_countdowns:256',
    'tick_end:-1:figures:8',
    'tick_end:-1:scenario:1048576',
    'day:-1:distant_battle:32768',
    'day:-1:invasion_auto_resolve:32768',
    'day:-1:sentiment:4096',
    'day:-1:criminals_day:8194',
    'day:-1:funeral_walkers:8',
    'day:-1:plague_day:258',
    'day:-1:flotsam:8',
    'day:-1:buildings_day:4',
    'day:-1:figures_day:8',
    'day:-1:population_day:1',
    'day:-1:victory_check:134217728',
    'day:-1:avg_coverage:128',
    'day:-1:event_advance_day:268435456',
    'week:-1:food_weekly:34',
    'week:-1:industry_nearby_houses:4',
    'week:-1:event_advance_week:268435456',
    'month_city:-1:migration_month:65536',
    'month_city:-1:health_month:256',
    'month_city:-1:finance_month:16',
    'month_city:-1:food_monthly:34',
    'month_city:-1:resource_month:32',
    'month_city:-1:food_supply_month:32',
    'month_city:-1:allowed_foods:32',
    'month_city:-1:population_record:1',
    'month_city:-1:local_cults_month:64',
    'month_city:-1:festival_month:8388608',
    'month_city:-1:buildings_month:4',
    'month_city:-1:fishing_points_month:8',
    'month_city:-1:kingdome_month:2048',
    'month_city:-1:tomb_robbers_month:8',
    'month:-1:distant_battle_month:32768',
    'month:-1:random_month:33554432',
    'month:-1:empire_month:524288',
    'month:-1:random_events:1048576',
    'month:-1:invasions:1081344',
    'month:-1:scenario_events:1048576',
    'month:-1:invasion_bind_resolutions:32768',
    'month:-1:invasion_process:1081344',
    'month:-1:morale_at_rest:32768',
    'month:-1:message_delays:262144',
    'month:-1:roads_images:16384',
    'month:-1:land_citizen_routing:16384',
    'month:-1:locusts_month:8',
    'month_end:-1:estimate_taxes:16',
    'month_end:-1:event_advance_month:268435456',
    'year:-1:empire_expansion:524288',
    'year:-1:undo_disable:67108864',
    'year:-1:simtime_year:16777216',
    'year:-1:population_yearly_request:1',
    'year:-1:finance_year:16',
    'year:-1:migration_year:65536',
    'year:-1:monuments_year:2097152',
    'year:-1:yearly_trade_amounts:525312',
    'year:-1:ratings_year:131072',
    'year:-1:ra_yearly_favour:64',
    'year:-1:buildings_year:4',
]

var T587_SAME_SLOT_WRITERS = ['tick_slot:32:trade:1024', 'tick_slot:32:figures:8', 'tick_slot:33:buildings:4',
    'tick_slot:33:coverage:128']
var T587_REPEATED = ['avg_coverage:3']

function t587_fail(msg) {
    __log_info_native('[test:587] FAIL: ' + msg)
    __test_signal_ready()
}

function t587_area_names(mask) {
    var names = {1: 'population', 2: 'houses', 4: 'buildings', 8: 'figures', 16: 'finance', 32: 'resources',
        64: 'religion', 128: 'coverage', 256: 'health', 512: 'labor', 1024: 'trade', 2048: 'kingdom'}
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
        if (phase == 'tick_slot' || phase == 'day') {
            per_day[name] = (per_day[name] || 0) + 1
        }
        if (phase != 'tick_slot') {
            continue
        }
        for (var bit = 1; bit <= (1 << 28); bit *= 2) {
            if (writes & bit) {
                var key = 'tick_slot:' + slot + ':' + bit
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

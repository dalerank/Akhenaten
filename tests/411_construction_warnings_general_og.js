// OG construction_warnings.c, general part: road access with the OG exempt list, venues that only get the
// venue-school hints (208-210), granary and recruiter requirements, and the house plot warnings
// (population 300+: eating more than produced, low food levels).
// Markers:
//   [test-marker] t411_road_access_ok
//   [test-marker] t411_statue_exempt_ok
//   [test-marker] t411_booth_ok
//   [test-marker] t411_pavilion_ok
//   [test-marker] t411_granary_ok
//   [test-marker] t411_recruiter_ok
//   [test-marker] t411_house_plots_ok

var __t411_ok = false

var T540_KEYS = ['#needs_road_access', '#city_needs_more_workers', '#no_troops_for_defense',
    '#build_juggling_school', '#build_conservatory', '#build_dance_school',
    '#build_jugglers_school', '#venue_build_conservatory', '#venue_build_dance_school',
    '#build_bazaars_to_distribute_food', '#soldiers_need_supplies_of_weapons',
    '#people_eating_more_than_produced', '#people_eat_more_than_produce', '#too_few_jobs_for_population',
    '#low_food_levels']

function t411_shown() {
    var shown = []
    for (var i = 0; i < T540_KEYS.length; i++) {
        var n = __test_construction_warning_count(T540_KEYS[i])
        for (var k = 0; k < n; k++) {
            shown.push(T540_KEYS[i])
        }
    }
    return shown.join(',')
}

function t411_expect(label, expected) {
    var shown = t411_shown()
    if (shown != expected.join(',')) {
        __log_info_native('[test:411] FAIL ' + label + ': shown [' + shown + '] want [' + expected.join(',') + ']')
        return false
    }
    return true
}

function t411_clear_roads(cx, cy, radius) {
    for (var y = cy - radius; y <= cy + radius; y++) {
        for (var x = cx - radius; x <= cx + radius; x++) {
            terrain.remove({ x: x, y: y }, TERRAIN_ROAD)
        }
    }
    __test_update_road_network()
}

function t411_place(type, x, y) {
    __test_construction_warnings_reset()
    var bid = test_building_place(type, x, y)
    __test_process_events()
    return bid
}

function t411_place_venue(type, roads, extra, x, y) {
    for (var dy = 0; dy < roads.length; dy++) {
        for (var dx = 0; dx < roads[dy].length; dx++) {
            if (roads[dy][dx]) {
                terrain.add({ x: x + dx, y: y + dy }, TERRAIN_ROAD)
            }
        }
    }
    for (var i = 0; i < extra.length; i++) {
        terrain.add({ x: x + extra[i][0], y: y + extra[i][1] }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    return t411_place(type, x, y)
}

function t411_place_plots(x, y) {
    __test_construction_warnings_reset()
    if (!test_planner_enter_build_mode(BUILDING_HOUSE_VACANT_LOT)) {
        return false
    }
    city_planner.update(x, y)
    city_planner.construction_start(x, y)
    city_planner.construction_update(x + 1, y + 1)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()
    __test_process_events()
    return true
}

function t411_run() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000000)
    __camera_rotate_north()

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    t411_clear_roads(cx, cy, 14)
    if (!t411_place(BUILDING_FIREHOUSE, cx, cy)) {
        __log_info_native('[test:411] FAIL firehouse placement')
        return false
    }
    if (!t411_expect('firehouse without road', ['#needs_road_access'])) {
        return false
    }
    __log_marker('t411_road_access_ok')

    if (!t411_place(BUILDING_SMALL_STATUE, cx + 6, cy)) {
        __log_info_native('[test:411] FAIL statue placement')
        return false
    }
    if (!t411_expect('statue without road', [])) {
        return false
    }
    __log_marker('t411_statue_exempt_ok')

    if (!t411_place_venue(BUILDING_BOOTH, [[0, 1], [1, 1]], [[1, 2], [2, 1]], cx - 30, cy - 20)) {
        __log_info_native('[test:411] FAIL booth placement')
        return false
    }
    if (!t411_expect('booth', ['#build_jugglers_school'])) {
        return false
    }
    __log_marker('t411_booth_ok')

    var pavilion_roads = [[0, 0, 1, 0], [0, 0, 1, 0], [0, 0, 1, 0], [1, 1, 1, 1]]
    if (!t411_place_venue(BUILDING_PAVILLION, pavilion_roads, [], cx - 10, cy - 20)) {
        __log_info_native('[test:411] FAIL pavilion placement')
        return false
    }
    if (!t411_expect('pavilion', ['#build_jugglers_school', '#venue_build_conservatory', '#venue_build_dance_school'])) {
        return false
    }
    __log_marker('t411_pavilion_ok')

    // Nothing has been staffed yet, so no workers are needed and the gated hints show.
    var workers_needed = city.labor.workers_needed
    if (workers_needed >= 10) {
        __log_info_native('[test:411] FAIL workers needed ' + workers_needed + ' before any staffing')
        return false
    }
    if (!t411_place(BUILDING_GRANARY, -1, -1)) {
        __log_info_native('[test:411] FAIL granary placement')
        return false
    }
    if (__test_construction_warning_count('#build_bazaars_to_distribute_food') != 1) {
        __log_info_native('[test:411] FAIL granary without bazaar: [' + t411_shown() + ']')
        return false
    }
    __log_marker('t411_granary_ok')

    if (!t411_place(BUILDING_RECRUITER, -1, -1)) {
        __log_info_native('[test:411] FAIL recruiter placement')
        return false
    }
    if (__test_construction_warning_count('#soldiers_need_supplies_of_weapons') != 1) {
        __log_info_native('[test:411] FAIL recruiter without weapons: [' + t411_shown() + ']')
        return false
    }
    __log_marker('t411_recruiter_ok')

    __test_set_city_population(0)
    if (!t411_place_plots(cx + 20, cy + 20) || !t411_expect('plots, no population', [])) {
        return false
    }
    __test_set_city_population(400)
    if (!t411_place_plots(cx + 24, cy + 20)) {
        return false
    }
    var eating = __test_construction_warning_count('#people_eating_more_than_produced')
    var low_food = __test_construction_warning_count('#low_food_levels')
    var old_key = __test_construction_warning_count('#people_eat_more_than_produce')
    if (low_food != 1 || old_key != 0 || eating > 1
        || __test_construction_warning_count('#too_few_jobs_for_population') != 0) {
        __log_info_native('[test:411] FAIL plots at population 400: [' + t411_shown() + ']')
        return false
    }
    __log_marker('t411_house_plots_ok')
    return true
}

function run_test() {
    __log_info_native('[test:411] construction warnings, general part')
    __t411_ok = t411_run()
    __test_signal_ready()
}

function check_valid() {
    var markers = ['t411_road_access_ok', 't411_statue_exempt_ok', 't411_booth_ok', 't411_pavilion_ok',
        't411_granary_ok', 't411_recruiter_ok', 't411_house_plots_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:411] missing marker: ' + markers[i])
            return false
        }
    }
    return __t411_ok
}

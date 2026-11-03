// FIG_PATRICIAN / FIGURE_NOBLES: OG roam length 128, citizen category, manor spawn every 41 days
// with at most one new walker per generate pass (no population gate, no labor spawn timer).
// Markers:
//   [test-marker] patrician_params_ok
//   [test-marker] patrician_spawn_ok
//   [test-marker] patrician_one_per_tick_ok
//   [test-marker] patrician_no_pop_gate_ok

var __test235_ok = false

function test235_fail(msg) {
    __log_info_native('[test:235] ' + msg)
    __test_signal_ready()
}

function test235_setup_manor(x, y, delay) {
    var bid = __test_building_create(BUILDING_HOUSE_COMMON_MANOR, x, y)
    if (!bid) {
        return 0
    }
    __test_building_force_road_access(bid)
    __test_house_set_population(bid, 5)
    city.get_building(bid).figure_spawn_delay = delay
    return bid
}

function run_test() {
    __log_info_native('[test:235] patrician OG')

    if (__test_figure_type_max_roam(FIGURE_NOBLES) != 128) {
        return test235_fail('max_roam want 128 got ' + __test_figure_type_max_roam(FIGURE_NOBLES))
    }
    // figure_category_citizen = 1
    if (__test_figure_type_category(FIGURE_NOBLES) != 1) {
        return test235_fail('category want citizen(1) got ' + __test_figure_type_category(FIGURE_NOBLES))
    }
    __log_marker('patrician_params_ok')

    test_reload_city_session('data/default.map')
    city.figures.remove_figures(FIGURE_NOBLES)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var a = test235_setup_manor(cx, cy, 40)
    var b = test235_setup_manor(cx + 10, cy, 40)
    if (!a || !b) {
        return test235_fail('manor create failed a=' + a + ' b=' + b)
    }

    var before = __test_count_figures(FIGURE_NOBLES)
    __test_buildings_generate_figures()
    var after_one = __test_count_figures(FIGURE_NOBLES)
    if (after_one != before + 1) {
        return test235_fail('one-per-tick want +1 got ' + before + ' -> ' + after_one)
    }
    if (city.get_building(a).figure_spawn_delay != 0 && city.get_building(b).figure_spawn_delay != 0) {
        return test235_fail('spawning manor should reset delay')
    }
    __log_marker('patrician_spawn_ok')
    __log_marker('patrician_one_per_tick_ok')

    // Low population still spawns (OG has no pop>20 gate). Second generate: remaining due manor.
    __test_buildings_generate_figures()
    var after_two = __test_count_figures(FIGURE_NOBLES)
    if (after_two != after_one + 1) {
        return test235_fail('second manor want +1 got ' + after_one + ' -> ' + after_two)
    }
    __log_marker('patrician_no_pop_gate_ok')

    __test235_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test235_ok
        && __test_find_inlog('[test-marker] patrician_params_ok')
        && __test_find_inlog('[test-marker] patrician_spawn_ok')
        && __test_find_inlog('[test-marker] patrician_one_per_tick_ok')
        && __test_find_inlog('[test-marker] patrician_no_pop_gate_ok')
}

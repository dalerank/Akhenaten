// FIG_ENEMY_CAMEL / figure_egyptian_camel: OG enemy_rider_action(0, 1) —
// FIGURE_SPEAR only in INITIAL, no drown on flooded floodplain, speed factor 1.
// Markers:
//   [test-marker] enemy_camel_params_ok
//   [test-marker] enemy_camel_initial_spear_ok
//   [test-marker] enemy_camel_no_drown_ok

var __test241_ok = false

function test241_fail(msg) {
    __log_info_native('[test:241] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:241] FIG_ENEMY_CAMEL / egyptian camel OG')

    test_ensure_city_session('data/default.map')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_CAMEL)) {
        return test241_fail('egyptian camel not registered')
    }
    __log_marker('enemy_camel_params_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var soldier = test_figure_create(FIGURE_INFANTRY, cx + 2, cy)
    if (!soldier) {
        return test241_fail('infantry bait failed')
    }

    var camel = test_figure_create(FIGURE_ENEMY_EGYPTIAN_CAMEL, cx, cy)
    if (!camel) {
        return test241_fail('egyptian camel create failed')
    }
    if (!__test_enemy_archer_fire_initial_missile(camel)) {
        return test241_fail('INITIAL should fire FIGURE_SPEAR and set missile_fired; ACTION_3 must not fire')
    }
    __log_marker('enemy_camel_initial_spear_ok')

    city.figures.remove_figures(FIGURE_ENEMY_EGYPTIAN_CAMEL)
    city.figures.remove_figures(FIGURE_SPEAR)
    var dry = test_figure_create(FIGURE_ENEMY_EGYPTIAN_CAMEL, cx + 4, cy + 4)
    if (!dry) {
        return test241_fail('no-drown create failed')
    }
    var dt = __figure_get_tile(dry)
    __test_make_floodplain_water(dt.x, dt.y)
    __test_figure_action_perform(dry)
    if (__test_figure_is_alive(dry) != 1) {
        return test241_fail('camel must not drown on flooded floodplain')
    }
    __log_marker('enemy_camel_no_drown_ok')

    __test241_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test241_ok
        && __test_find_inlog('[test-marker] enemy_camel_params_ok')
        && __test_find_inlog('[test-marker] enemy_camel_initial_spear_ok')
        && __test_find_inlog('[test-marker] enemy_camel_no_drown_ok')
}

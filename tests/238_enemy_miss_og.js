// FIG_ENEMY_MISS / figure_enemy_archer: OG shoots FIGURE_SPEAR only in INITIAL,
// records formation missile_fired, ACTION_3 is melee (no missiles), drown on
// flooded floodplain.
// Markers:
//   [test-marker] enemy_miss_params_ok
//   [test-marker] enemy_miss_initial_spear_ok
//   [test-marker] enemy_miss_drown_ok

var __test238_ok = false

function test238_fail(msg) {
    __log_info_native('[test:238] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:238] FIG_ENEMY_MISS / enemy archer OG')

    test_ensure_city_session('data/default.map')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_ARCHER)) {
        return test238_fail('egyptian archer not registered')
    }
    __log_marker('enemy_miss_params_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var soldier = test_figure_create(FIGURE_INFANTRY, cx + 2, cy)
    if (!soldier) {
        return test238_fail('infantry bait failed')
    }

    var archer = test_figure_create(FIGURE_ENEMY_EGYPTIAN_ARCHER, cx, cy)
    if (!archer) {
        return test238_fail('egyptian archer create failed')
    }
    if (!__test_enemy_archer_fire_initial_missile(archer)) {
        return test238_fail('INITIAL should fire FIGURE_SPEAR and set missile_fired; ACTION_3 must not fire')
    }
    __log_marker('enemy_miss_initial_spear_ok')

    city.figures.remove_figures(FIGURE_ENEMY_EGYPTIAN_ARCHER)
    city.figures.remove_figures(FIGURE_SPEAR)
    var drown = test_figure_create(FIGURE_ENEMY_EGYPTIAN_ARCHER, cx + 4, cy + 4)
    if (!drown) {
        return test238_fail('drown create failed')
    }
    var dt = __figure_get_tile(drown)
    __test_make_floodplain_water(dt.x, dt.y)
    __test_figure_action_perform(drown)
    if (__test_figure_is_alive(drown) == 1) {
        return test238_fail('should drown on flooded floodplain')
    }
    __log_marker('enemy_miss_drown_ok')

    __test238_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test238_ok
        && __test_find_inlog('[test-marker] enemy_miss_params_ok')
        && __test_find_inlog('[test-marker] enemy_miss_initial_spear_ok')
        && __test_find_inlog('[test-marker] enemy_miss_drown_ok')
}

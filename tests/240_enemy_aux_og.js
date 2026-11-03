// FIG_ENEMY_AUX / figure_enemy_fast_sword: OG drown on flooded floodplain;
// INITIAL resets wait_ticks to 50 and clears ghost (invisible).
// Markers:
//   [test-marker] enemy_aux_params_ok
//   [test-marker] enemy_aux_initial_wait_ghost_ok
//   [test-marker] enemy_aux_drown_ok

var __test240_ok = false

function test240_fail(msg) {
    __log_info_native('[test:240] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:240] FIG_ENEMY_AUX / enemy fast_sword OG')

    test_ensure_city_session('data/default.map')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_BARBARIAN_SWORD)) {
        return test240_fail('barbarian sword not registered')
    }
    __log_marker('enemy_aux_params_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var sword = test_figure_create(FIGURE_ENEMY_BARBARIAN_SWORD, cx, cy)
    if (!sword) {
        return test240_fail('barbarian sword create failed')
    }

    __test_figure_set_action(sword, ACTION_151_ENEMY_FAST_SWORD_INITIAL)
    __test_figure_set_wait_ticks(sword, 1)
    __test_figure_set_visible(sword, 0)
    if (__test_figure_is_visible(sword) != 0) {
        return test240_fail('setup: sword should be invisible')
    }

    __test_figure_action_perform(sword)
    if (__test_figure_get_wait_ticks(sword) != 50) {
        return test240_fail('INITIAL should reset wait_ticks to 50, got '
            + __test_figure_get_wait_ticks(sword))
    }
    if (__test_figure_is_visible(sword) != 1) {
        return test240_fail('INITIAL should clear ghost/invisible')
    }
    __log_marker('enemy_aux_initial_wait_ghost_ok')

    city.figures.remove_figures(FIGURE_ENEMY_BARBARIAN_SWORD)
    var drown = test_figure_create(FIGURE_ENEMY_BARBARIAN_SWORD, cx + 4, cy + 4)
    if (!drown) {
        return test240_fail('drown create failed')
    }
    var dt = __figure_get_tile(drown)
    __test_make_floodplain_water(dt.x, dt.y)
    __test_figure_action_perform(drown)
    if (__test_figure_is_alive(drown) == 1) {
        return test240_fail('should drown on flooded floodplain')
    }
    __log_marker('enemy_aux_drown_ok')

    __test240_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test240_ok
        && __test_find_inlog('[test-marker] enemy_aux_params_ok')
        && __test_find_inlog('[test-marker] enemy_aux_initial_wait_ghost_ok')
        && __test_find_inlog('[test-marker] enemy_aux_drown_ok')
}

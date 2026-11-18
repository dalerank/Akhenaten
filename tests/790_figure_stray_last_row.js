// A figure whose tile y equals GRID_LENGTH is off the grid like x == GRID_LENGTH: the figure update removes it.

var __test790_ok = false

function test790_fail(reason) {
    __log_marker('figure_stray_last_row_fail:' + reason)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:790] figure on tile y == GRID_LENGTH is removed')
    test_ensure_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var stray = __test_figure_create(FIGURE_EXPLOSION, cx, cy)
    var control = __test_figure_create(FIGURE_EXPLOSION, cx + 2, cy)
    if (!stray || !control) {
        return test790_fail('figure_create')
    }

    __test_figure_set_tile_raw(stray, 10, 228)
    __test_figures_update()

    var stray_alive = __test_figure_is_alive(stray)
    var control_alive = __test_figure_is_alive(control)
    __log_info_native('[test:790] stray_alive=' + stray_alive + ' control_alive=' + control_alive)
    if (!control_alive) {
        return test790_fail('control_died')
    }
    if (stray_alive) {
        return test790_fail('stray_survived_tick')
    }

    __log_marker('figure_stray_last_row_ok')
    __test790_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test790_ok && __test_find_inlog('[test-marker] figure_stray_last_row_ok')
}

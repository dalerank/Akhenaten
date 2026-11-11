// Drawing must not change simulation state: the figure depth sort used to poof figures whose
// tile was off the grid. The sort now only reads; the figure update in the tick removes them.
// An explosion is used because it lives ~44 ticks without a home, road or destination.

var __test303_ok = false

function test303_fail(reason) {
    __log_marker('render_no_sim_writes_fail:' + reason)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:303] render does not write simulation state')
    test_ensure_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var stray = __test_figure_create(FIGURE_EXPLOSION, cx, cy)
    var control = __test_figure_create(FIGURE_EXPLOSION, cx + 2, cy)
    if (!stray || !control) {
        return test303_fail('figure_create')
    }

    __test_figure_set_tile_raw(stray, 240, 10)

    __test_map_figure_sort_by_y()
    var alive_after_sort = __test_figure_is_alive(stray)
    var x_after_sort = __test_figure_tile_x(stray)
    __log_info_native('[test:303] after sort: alive=' + alive_after_sort + ' x=' + x_after_sort)
    if (!alive_after_sort || x_after_sort != 240) {
        return test303_fail('sort_touched_figure')
    }

    __test_figures_update()
    var stray_alive = __test_figure_is_alive(stray)
    var control_alive = __test_figure_is_alive(control)
    __log_info_native('[test:303] after update: stray_alive=' + stray_alive + ' control_alive=' + control_alive)
    if (!control_alive) {
        return test303_fail('control_died')
    }
    if (stray_alive) {
        return test303_fail('stray_survived_tick')
    }

    __log_marker('render_no_sim_writes_ok')
    __test303_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test303_ok && __test_find_inlog('[test-marker] render_no_sim_writes_ok')
}

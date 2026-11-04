// FIG_SHIPWRECK / figure_shipwreck: OG figure_shipwreck_action —
// ++animation_frame, dead at 36; once wait_ticks < 1000 settle to open water (wait=1000).
// Markers:
//   [test-marker] shipwreck_settle_ok
//   [test-marker] shipwreck_alive_mid_ok
//   [test-marker] shipwreck_die_at_36_ok

var __test248_ok = false

function test248_fail(msg) {
    __log_info_native('[test:248] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:248] FIG_SHIPWRECK / figure_shipwreck OG')

    test_ensure_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    // Open-water patch so settle may find a tile (±2 water check).
    var x0 = cx
    var y0 = cy
    for (var dy = -3; dy <= 3; dy++) {
        for (var dx = -3; dx <= 3; dx++) {
            terrain.add({ x: x0 + dx, y: y0 + dy }, TERRAIN_WATER)
        }
    }

    city.figures.remove_figures(FIGURE_SHIPWRECK)
    city.figures.remove_figures(FIGURE_BUBBLES)

    // Place off the open centre so find_shipwreck_tile can relocate.
    var wreck = test_figure_create(FIGURE_SHIPWRECK, x0 - 3, y0 - 3)
    if (!wreck) {
        return test248_fail('shipwreck create failed')
    }
    __test_figure_set_wait_ticks(wreck, 0)
    test_figure_set_force_valid_animation(wreck, true)

    var before = __figure_get_tile(wreck)
    __test_figure_action_perform(wreck)
    if (!__test_figure_is_alive(wreck)) {
        return test248_fail('should stay alive after first tick')
    }
    if (__test_figure_get_wait_ticks(wreck) != 1000) {
        return test248_fail('settle: wait_ticks want 1000 got ' + __test_figure_get_wait_ticks(wreck))
    }
    __log_marker('shipwreck_settle_ok')

    // 34 more ticks → frame 35, still alive (first tick already advanced to 1).
    for (var i = 0; i < 34; i++) {
        __test_figure_action_perform(wreck)
    }
    if (!__test_figure_is_alive(wreck)) {
        return test248_fail('should still be alive at frame 35')
    }
    __log_marker('shipwreck_alive_mid_ok')

    // 36th increment → poof
    __test_figure_action_perform(wreck)
    if (__test_figure_is_alive(wreck) == 1) {
        return test248_fail('should die when animation_frame reaches 36')
    }
    __log_marker('shipwreck_die_at_36_ok')

    if (before) {
        __log_info_native('[test:248] start tile=' + before.x + ',' + before.y)
    }

    __test248_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test248_ok
        && __test_find_inlog('[test-marker] shipwreck_settle_ok')
        && __test_find_inlog('[test-marker] shipwreck_alive_mid_ok')
        && __test_find_inlog('[test-marker] shipwreck_die_at_36_ok')
}

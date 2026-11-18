// The simulation clock runs only while a city window (or the build/overlay menu over it) is current:
// an open advisor stops the day, going back to the city starts it again.
// Markers:
//   [test-marker] t793_city_runs
//   [test-marker] t793_advisor_stops
//   [test-marker] t793_build_menu_runs
//   [test-marker] t793_city_runs_again

var __t793_ok = false

function t793_fail(msg) {
    __log_info_native('[test:793] FAIL: ' + msg)
    game.paused = false
    ui.window_city_show()
    __test_signal_ready()
}

function t793_ticks_over(frames) {
    var before = __game_simtime_absolute_tick(true)
    __test_pump_frames(frames)
    return __game_simtime_absolute_tick(true) - before
}

function run_test() {
    __log_info_native('[test:793] sim time runs in city windows')
    test_ensure_city_session('data/default.map')
    game.paused = false
    ui.window_city_show()
    __test_pump_frames(3)

    var ran = t793_ticks_over(10)
    if (ran <= 0) {
        return t793_fail('city window ran ' + ran + ' ticks')
    }
    __log_marker('t793_city_runs')

    city.set_advisor_available(ADVISOR_LABOR, 1)
    if (!window_advisors_show_advisor(ADVISOR_LABOR)) {
        return t793_fail('labor advisor did not open')
    }
    __test_pump_frames(2)
    ran = t793_ticks_over(10)
    if (ran != 0) {
        return t793_fail('advisor window ran ' + ran + ' ticks, window ' + __game_window_get_id())
    }
    __log_marker('t793_advisor_stops')

    ui.window_city_show()
    __test_pump_frames(2)
    window_show_by_id('build_menu_widget')
    __test_pump_frames(2)
    if (!ui.window_is('build_menu_widget')) {
        return t793_fail('build menu did not open')
    }
    ran = t793_ticks_over(10)
    if (ran <= 0) {
        return t793_fail('build menu ran ' + ran + ' ticks')
    }
    __log_marker('t793_build_menu_runs')

    window_go_back()
    __test_pump_frames(2)
    ran = t793_ticks_over(10)
    if (ran <= 0) {
        return t793_fail('city after build menu ran ' + ran + ' ticks')
    }
    __log_marker('t793_city_runs_again')

    __t793_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __t793_ok
        && __test_find_inlog('[test-marker] t793_city_runs')
        && __test_find_inlog('[test-marker] t793_advisor_stops')
        && __test_find_inlog('[test-marker] t793_build_menu_runs')
        && __test_find_inlog('[test-marker] t793_city_runs_again')
}

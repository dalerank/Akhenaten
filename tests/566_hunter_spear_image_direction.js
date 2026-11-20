// Hunter spear / antelope javelin pick their frame from the 32-direction sheet, camera rotation included.
// Markers:
//   [test-marker] t566_ok
//   [test-marker] t566_fail:<what>

var __t566_failed = false
var T566_CLIMATE_DESERT = 2

function t566_fail(what) {
    __log_info_native('[test-marker] t566_fail:' + what)
    __t566_failed = true
}

function t566_check(type, name, dx, dy, want) {
    var frame = __test_missile_image_frame(type, 40, 40, 40 + dx, 40 + dy)
    __log_info_native('[test:566] ' + name + ' frame ' + frame + ' (want ' + want + ')')
    if (frame != want) {
        t566_fail(name + ':' + frame)
    }
}

function run_test() {
    test_ensure_city_session('data/default.map')
    // Central climate draws hunter spears with the 5-frame stick instead of the directional sheet.
    __test_set_scenario_climate(T566_CLIMATE_DESERT)
    __camera_rotate_north()

    t566_check(FIGURE_HUNTER_SPEAR, 'minus_y', 0, -5, 3)
    t566_check(FIGURE_HUNTER_SPEAR, 'plus_x', 5, 0, 11)
    t566_check(FIGURE_HUNTER_SPEAR, 'plus_y', 0, 5, 19)
    t566_check(FIGURE_HUNTER_SPEAR, 'minus_x', -5, 0, 27)
    t566_check(FIGURE_HUNTER_SPEAR, 'plus_x_minus_y', 5, -5, 7)
    t566_check(FIGURE_HUNTER_SPEAR, 'minus_x_minus_y', -5, -5, 31)
    t566_check(FIGURE_ANTELOPE_HUNTER_JAVELIN, 'javelin_plus_x', 5, 0, 11)

    // Orientation steps by 2; each step turns the view a quarter, 8 frames of the 32.
    __camera_rotate_right()
    t566_check(FIGURE_HUNTER_SPEAR, 'rotated_minus_y', 0, -5, 27)
    t566_check(FIGURE_HUNTER_SPEAR, 'rotated_plus_x', 5, 0, 3)
    __camera_rotate_north()

    test_reload_city_session('data/default.map')
    if (!__t566_failed) {
        __log_info_native('[test-marker] t566_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t566_failed && __test_find_inlog('[test-marker] t566_ok')
}

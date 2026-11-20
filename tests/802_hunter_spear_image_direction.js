// FIGURE_HUNTER_SPEAR has a 32-frame sheet, frame k pointing (k+1) * 11.25 deg clockwise from the screen top
// (the map's -x,-y corner) with the camera facing north. A shot along each map axis must show the frame of that
// axis, not the one of a 16-step direction read as a frame.
// Markers:
//   [test-marker] t802_ok
//   [test-marker] t802_fail:<what>

var __t802_failed = false
var T802_CLIMATE_DESERT = 2

function t802_fail(what) {
    __log_info_native('[test-marker] t802_fail:' + what)
    __t802_failed = true
}

function run_test() {
    test_ensure_city_session('data/default.map')
    // Central climate draws hunter spears with the 5-frame stick instead of the directional sheet.
    __test_set_scenario_climate(T802_CLIMATE_DESERT)
    __camera_rotate_north()

    var x = 40
    var y = 40
    var shots = [
        { name: 'minus_y', dx: 0, dy: -5, frame: 3 },
        { name: 'plus_x', dx: 5, dy: 0, frame: 11 },
        { name: 'plus_y', dx: 0, dy: 5, frame: 19 },
        { name: 'minus_x', dx: -5, dy: 0, frame: 27 },
        { name: 'plus_x_minus_y', dx: 5, dy: -5, frame: 7 },
        { name: 'minus_x_minus_y', dx: -5, dy: -5, frame: 31 },
    ]
    for (var i = 0; i < shots.length; i++) {
        var s = shots[i]
        var frame = __test_missile_image_frame(FIGURE_HUNTER_SPEAR, x, y, x + s.dx, y + s.dy)
        __log_info_native('[test:802] ' + s.name + ' frame ' + frame + ' (want ' + s.frame + ')')
        if (frame != s.frame) {
            t802_fail(s.name + ':' + frame)
        }
    }

    test_reload_city_session('data/default.map')
    if (!__t802_failed) {
        __log_info_native('[test-marker] t802_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t802_failed && __test_find_inlog('[test-marker] t802_ok')
}

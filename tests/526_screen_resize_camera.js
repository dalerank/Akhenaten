// Resizing the window resizes the city camera viewport: it grows by the same amount as the window and
// shrinks back when the size is restored, and it matches the window from the first frame of a session.
// Markers:
//   [test-marker] t526_ok
//   [test-marker] t526_fail:<what>

var __t526_failed = false

function t526_fail(what) {
    __log_info_native('[test-marker] t526_fail:' + what)
    __t526_failed = true
}

function t526_resize(w, h) {
    emit event_display_options_apply_resolution{ w: w, h: h }
    __test_process_events()
    __test_pump_frames(10)
}

function run_test() {
    if (!test_reload_city_session('data/default.map')) {
        t526_fail('load')
        __test_signal_ready()
        return
    }
    __test_pump_frames(5)

    var before_x = __camera.size_pixels.x
    var before_y = __camera.size_pixels.y

    t526_resize(1000, 700)
    var grown_x = __camera.size_pixels.x - before_x
    var grown_y = __camera.size_pixels.y - before_y

    t526_resize(800, 600)
    var back_x = __camera.size_pixels.x
    var back_y = __camera.size_pixels.y

    __log_info_native('[test:526] before=' + before_x + 'x' + before_y + ' grown=' + grown_x + 'x' + grown_y
        + ' back=' + back_x + 'x' + back_y)

    if (grown_x != 200 || grown_y != 100) {
        t526_fail('grow')
    } else if (back_x != before_x || back_y != before_y) {
        t526_fail('restore')
    } else {
        __log_info_native('[test-marker] t526_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t526_failed && __test_find_inlog('[test-marker] t526_ok')
}

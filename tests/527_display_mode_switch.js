// Display options apply live: fullscreen <-> windowed, a picked resolution resizes the window, and Cancel
// puts back the window mode and both sizes the window was opened with.
// Markers:
//   [test-marker] t527_ok
//   [test-marker] t527_fail:<what>

var __t527_failed = false

function t527_fail(what) {
    __log_info_native('[test-marker] t527_fail:' + what)
    __t527_failed = true
}

function t527_wait(pred) {
    for (var i = 0; i < 40; i++) {
        __test_process_events()
        if (pred()) {
            return true
        }
        __test_sleep_ms(50)
    }
    return pred()
}

function t527_state() {
    var s = __display_options_get_window_size()
    var o = game_features.gameopt_display_size
    return s.x + 'x' + s.y + ' fs=' + __display_options_is_fullscreen() + ' saved=' + o.x + 'x' + o.y
}

function t527_window_is(w, h) {
    var s = __display_options_get_window_size()
    return s.x == w && s.y == h
}

// The game renders at the window size divided by the interface scale.
function t527_screen_follows_window() {
    var s = __display_options_get_resolution()
    var scale = __display_options_get_scale()
    return Math.abs(sw(0) - Math.ceil(s.x * 100 / scale)) <= 1 && Math.abs(sh(0) - Math.ceil(s.y * 100 / scale)) <= 1
}

function t527_toggle() {
    emit event_app_toggle_fullscreen{ value: 0 }
}

function run_test() {
    var start = __display_options_get_window_size()
    __log_info_native('[test:527] start ' + start.x + 'x' + start.y + ' fs=' + __display_options_is_fullscreen())
    if (__display_options_is_fullscreen()) {
        t527_fail('starts_fullscreen')
        __test_signal_ready()
        return
    }

    t527_toggle()
    if (!t527_wait(function() { return __display_options_is_fullscreen() })) {
        t527_fail('enter_fullscreen')
    } else if (!t527_screen_follows_window()) {
        t527_fail('fullscreen_screen_size')
    }

    t527_toggle()
    if (!t527_wait(function() { return !__display_options_is_fullscreen() && t527_window_is(start.x, start.y) })) {
        t527_fail('leave_fullscreen:' + t527_state())
    } else if (!t527_screen_follows_window()) {
        t527_fail('windowed_screen_size')
    }

    var picked = { x: start.x + 64, y: start.y + 48 }
    emit event_display_options_apply_resolution{ w: picked.x, h: picked.y }
    if (!t527_wait(function() { return t527_window_is(picked.x, picked.y) })) {
        t527_fail('apply_resolution')
    } else if (!t527_screen_follows_window()) {
        t527_fail('resolution_screen_size')
    }

    // Cancel: open the window, change mode and sizes live, then go back through its Cancel handler.
    var fs_res = game_features.gameopt_fullscreen_resolution
    var orig_fs_res = { x: fs_res.x, y: fs_res.y }
    window_show_by_id("display_options_window")
    __test_pump_frames(3)
    __display_options_set_fullscreen_resolution(start.x, start.y)
    emit event_display_options_apply_resolution{ w: start.x, h: start.y }
    t527_wait(function() { return t527_window_is(start.x, start.y) })
    t527_toggle()
    t527_wait(function() { return __display_options_is_fullscreen() })

    display_options_window_go_back(display_options_window)
    if (!t527_wait(function() { return !__display_options_is_fullscreen() && t527_window_is(picked.x, picked.y) })) {
        var s = __display_options_get_window_size()
        t527_fail('cancel_restore:' + s.x + 'x' + s.y + ' fs=' + __display_options_is_fullscreen())
    }
    fs_res = game_features.gameopt_fullscreen_resolution
    if (fs_res.x != orig_fs_res.x || fs_res.y != orig_fs_res.y) {
        t527_fail('cancel_fullscreen_resolution:' + fs_res.x + 'x' + fs_res.y)
    }

    emit event_display_options_apply_resolution{ w: start.x, h: start.y }
    t527_wait(function() { return t527_window_is(start.x, start.y) })

    if (!__t527_failed) {
        __log_info_native('[test-marker] t527_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t527_failed && __test_find_inlog('[test-marker] t527_ok')
}

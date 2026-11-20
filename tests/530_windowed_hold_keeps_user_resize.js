// Leaving fullscreen, the game holds the requested window size against the OS resizing the window on the
// way out. Once that size has arrived the hold ends: a resize right after (a drag on the window frame)
// is kept, not reverted.
// Markers:
//   [test-marker] t530_ok
//   [test-marker] t530_fail:<what>

var __t530_failed = false

function t530_fail(what) {
    __log_info_native('[test-marker] t530_fail:' + what)
    __t530_failed = true
}

function t530_state() {
    var s = __display_options_get_window_size()
    var o = game_features.gameopt_display_size
    return s.x + 'x' + s.y + ' fs=' + __display_options_is_fullscreen() + ' saved=' + o.x + 'x' + o.y
}

function t530_window_is(w, h) {
    var s = __display_options_get_window_size()
    return s.x == w && s.y == h
}

// Short steps: the old hold lasted a second, the user resize has to land inside it.
function t530_wait(pred) {
    for (var i = 0; i < 30; i++) {
        __test_process_events()
        if (pred()) {
            return true
        }
        __test_sleep_ms(10)
    }
    return pred()
}

function run_test() {
    var start = __display_options_get_window_size()

    emit event_app_toggle_fullscreen{ value: 0 }
    if (!t530_wait(function() { return __display_options_is_fullscreen() })) {
        t530_fail('enter_fullscreen')
        __test_signal_ready()
        return
    }

    emit event_app_toggle_fullscreen{ value: 0 }
    if (!t530_wait(function() { return !__display_options_is_fullscreen() && t530_window_is(start.x, start.y) })) {
        t530_fail('leave_fullscreen:' + t530_state())
        __test_signal_ready()
        return
    }

    var dragged = { x: start.x - 96, y: start.y - 64 }
    __test_window_os_resize(dragged.x, dragged.y)
    t530_wait(function() { return t530_window_is(dragged.x, dragged.y) })
    __test_sleep_ms(200)

    var now = __display_options_get_window_size()
    var saved = game_features.gameopt_display_size
    __log_info_native('[test:530] dragged to ' + dragged.x + 'x' + dragged.y + ', window ' + now.x + 'x' + now.y
        + ', saved ' + saved.x + 'x' + saved.y)
    if (now.x != dragged.x || now.y != dragged.y) {
        t530_fail('resize_reverted')
    } else if (saved.x != dragged.x || saved.y != dragged.y) {
        t530_fail('resize_not_saved')
    }

    emit event_display_options_apply_resolution{ w: start.x, h: start.y }
    t530_wait(function() { return t530_window_is(start.x, start.y) })

    if (!__t530_failed) {
        __log_info_native('[test-marker] t530_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t530_failed && __test_find_inlog('[test-marker] t530_ok')
}

// A screen size change re-runs the ui_* scripts, which rebuilds their windows. Display options sets
// defer_relayout so its unsaved state survives; that must hold while a popup is open over it too (the
// popup draws it underneath). Once both are closed the relayout runs.
// display_options_snapshot is the window's script state: a re-run of its script resets it to 0x0.
// Markers:
//   [test-marker] t801_ok
//   [test-marker] t801_fail:<what>

var __t801_failed = false

function t801_fail(what) {
    __log_info_native('[test-marker] t801_fail:' + what)
    __t801_failed = true
}

function t801_snapshot_width() {
    return display_options_snapshot.window_size.x
}

function t801_resize(w, h) {
    emit event_display_options_apply_resolution{ w: w, h: h }
    __test_process_events()
    // Past the relayout settle delay (300 ms).
    __test_sleep_ms(600)
}

function run_test() {
    var start = __display_options_get_window_size()

    window_show_by_id("display_options_window")
    __test_pump_frames(3)
    if (t801_snapshot_width() != start.x) {
        t801_fail('snapshot_init:' + t801_snapshot_width())
        __test_signal_ready()
        return
    }

    ui.show_ok("t801", "t801")
    __test_pump_frames(3)
    if (__game_window_get_id() != "window_popup_dialog_ok") {
        t801_fail('popup_not_on_top:' + __game_window_get_id())
    }

    t801_resize(start.x + 64, start.y + 48)
    if (t801_snapshot_width() != start.x) {
        t801_fail('rebuilt_under_popup:' + t801_snapshot_width())
    }

    window_go_back()
    window_go_back()
    __test_pump_frames(3)
    __test_sleep_ms(600)
    __test_pump_frames(3)
    if (t801_snapshot_width() != 0) {
        t801_fail('no_relayout_after_close:' + t801_snapshot_width())
    }

    t801_resize(start.x, start.y)

    if (!__t801_failed) {
        __log_info_native('[test-marker] t801_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t801_failed && __test_find_inlog('[test-marker] t801_ok')
}

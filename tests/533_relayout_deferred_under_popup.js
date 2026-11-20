// A screen size change re-runs the ui_* scripts, which rebuilds their windows. Display options sets
// defer_relayout so its unsaved state survives; that must hold while a popup is open over it too (the
// popup draws it underneath). Once both are closed the relayout runs.
// display_options_snapshot is the window's script state: a re-run of its script resets it to 0x0.
// Markers:
//   [test-marker] t533_ok
//   [test-marker] t533_fail:<what>

var __t533_failed = false

function t533_fail(what) {
    __log_info_native('[test-marker] t533_fail:' + what)
    __t533_failed = true
}

function t533_snapshot_width() {
    return display_options_snapshot.window_size.x
}

function t533_resize(w, h) {
    emit event_display_options_apply_resolution{ w: w, h: h }
    __test_process_events()
    // Past the relayout settle delay (300 ms).
    __test_sleep_ms(600)
}

function run_test() {
    var start = __display_options_get_window_size()

    window_show_by_id("display_options_window")
    __test_pump_frames(3)
    if (t533_snapshot_width() != start.x) {
        t533_fail('snapshot_init:' + t533_snapshot_width())
        __test_signal_ready()
        return
    }

    ui.show_ok("t801", "t801")
    __test_pump_frames(3)
    if (__game_window_get_id() != "window_popup_dialog_ok") {
        t533_fail('popup_not_on_top:' + __game_window_get_id())
    }

    t533_resize(start.x + 64, start.y + 48)
    if (t533_snapshot_width() != start.x) {
        t533_fail('rebuilt_under_popup:' + t533_snapshot_width())
    }

    window_go_back()
    window_go_back()
    __test_pump_frames(3)
    __test_sleep_ms(600)
    __test_pump_frames(3)
    if (t533_snapshot_width() != 0) {
        t533_fail('no_relayout_after_close:' + t533_snapshot_width())
    }

    t533_resize(start.x, start.y)

    if (!__t533_failed) {
        __log_info_native('[test-marker] t533_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t533_failed && __test_find_inlog('[test-marker] t533_ok')
}

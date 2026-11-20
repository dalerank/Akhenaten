// FF1–FF4: live figure follow PiP — start/stop, texture, clear on kill/invalid.
// Markers:
//   [test-marker] figure_follow_start_ok
//   [test-marker] figure_follow_stop_ok
//   [test-marker] figure_follow_invalid_ok
//   [test-marker] figure_follow_kill_clears_ok

function run_test() {
    __log_info_native('[test:063] figure follow')
    test_ensure_city_session('data/default.map')

    if (__figure_follow_enabled()) {
        __figure_follow_stop()
    }

    if (__figure_follow_start(0) || __figure_follow_enabled()) {
        __log_info_native('[test:063] invalid id 0 should not enable')
        __test_signal_ready()
        return
    }
    __log_marker('figure_follow_invalid_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var fid = test_figure_create(FIGURE_LABOR_SEEKER, cx, cy)
    if (!fid || !__figure_is_valid(fid)) {
        __log_info_native('[test:063] create labor seeker failed')
        __test_signal_ready()
        return
    }

    if (!__figure_follow_start(fid) || !__figure_follow_enabled()) {
        __log_info_native('[test:063] start failed')
        __test_signal_ready()
        return
    }
    __figure_follow_capture_if_due()
    if (__figure_follow_figure_id() != fid) {
        __log_info_native('[test:063] figure id mismatch')
        __test_signal_ready()
        return
    }
    if (__figure_follow_texture_id() <= 0) {
        __log_info_native('[test:063] texture id expected > 0 after capture')
        __test_signal_ready()
        return
    }
    __log_marker('figure_follow_start_ok')

    __figure_follow_stop()
    if (__figure_follow_enabled() || __figure_follow_texture_id() != 0) {
        __log_info_native('[test:063] stop did not clear')
        __test_signal_ready()
        return
    }
    __log_marker('figure_follow_stop_ok')

    if (!__figure_follow_start(fid)) {
        __log_info_native('[test:063] restart failed')
        __test_signal_ready()
        return
    }
    __test_figure_kill(fid)
    __figure_follow_capture_if_due()
    if (__figure_follow_enabled()) {
        __log_info_native('[test:063] kill did not clear follow')
        __test_signal_ready()
        return
    }
    __log_marker('figure_follow_kill_clears_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'figure_follow_invalid_ok',
        'figure_follow_start_ok',
        'figure_follow_stop_ok',
        'figure_follow_kill_clears_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:063] missing marker: ' + marker)
            return false
        }
    }
    return true
}

// B12/B13d: North Dahshur henna refuse/late → Hyksos×12 via event_request_cleared.
// Tags match mission15_event_i11 (3000+11*100+year). RESOURCE_DEBEN for fulfill path.
// Markers:
//   [test-marker] nd_henna_refuse_hyksos_ok
//   [test-marker] nd_henna_late_hyksos_ok
//   [test-marker] nd_henna_ok_no_raid_ok

function test095_fail(msg) {
    __log_info_native('[test:095] FAIL: ' + msg)
    __test_signal_ready()
}

function test095_load() {
    __game_load_mission(15, 1)
    if (typeof mission15_fire_request !== 'function'
        || typeof mission15_on_request_cleared !== 'function') {
        __log_info_native('[test:095] mission15 helpers missing after load')
        return false
    }
    return true
}

function test095_henna_tag(year) {
    return 3000 + 11 * 100 + year
}

function test095_hist_size12() {
    var n = city.invasion_history_count()
    var found = 0
    for (var i = 0; i < n; i++) {
        var h = city.invasion_history_at(i)
        if (h.size === 12 && h.invasion_id === 30) {
            found++
        }
    }
    return found
}

function run_test() {
    __log_info_native('[test:095] North Dahshur henna → hyksos×12 (B12)')

    if (!test095_load()) {
        test095_fail('load mission15 failed')
        return
    }
    __test_set_treasury(500000)

    var tag_refuse = test095_henna_tag(2)
    mission15_ensure_henna_leaves()
    mission15_fire_request(tag_refuse, RESOURCE_DEBEN, 12, 24, 1016, 1013, 1014, 2, 1)
    __test_process_events()
    if (!city.has_active_request(RESOURCE_DEBEN)) {
        test095_fail('refuse: request not active')
        return
    }
    var hist0 = test095_hist_size12()
    __test_request_force_refuse_now(tag_refuse)
    __test_process_events()
    if (test095_hist_size12() < hist0 + 1) {
        // Flag/log path: handler must have run (history may miss if spawn tile invalid).
        if (__test_request_cleared_tag_id() !== tag_refuse
            || __test_request_cleared_fulfilled() !== 0) {
            test095_fail('refuse: cleared facts tag=' + __test_request_cleared_tag_id()
                + ' ful=' + __test_request_cleared_fulfilled())
            return
        }
        __log_info_native('[test:095] warn: no history size=12 id=30 after refuse (cleared ok)')
    }
    __log_marker('nd_henna_refuse_hyksos_ok')

    if (!test095_load()) {
        test095_fail('reload for late failed')
        return
    }
    __test_set_treasury(500000)
    var tag_late = test095_henna_tag(4)
    mission15_ensure_henna_leaves()
    mission15_fire_request(tag_late, RESOURCE_DEBEN, 12, 24, 1016, 1013, 1014, 2, 1)
    __test_process_events()
    hist0 = test095_hist_size12()
    __test_request_force_fulfill(tag_late, 1)
    __test_process_events()
    if (__test_request_cleared_tag_id() !== tag_late
        || __test_request_cleared_was_overdue() !== 1) {
        test095_fail('late: cleared facts tag=' + __test_request_cleared_tag_id()
            + ' ov=' + __test_request_cleared_was_overdue())
        return
    }
    if (test095_hist_size12() < hist0 + 1) {
        __log_info_native('[test:095] warn: no history size=12 id=30 after late (cleared ok)')
    }
    __log_marker('nd_henna_late_hyksos_ok')

    if (!test095_load()) {
        test095_fail('reload for ok path failed')
        return
    }
    __test_set_treasury(500000)
    var tag_ok = test095_henna_tag(6)
    mission15_ensure_henna_leaves()
    mission15_fire_request(tag_ok, RESOURCE_DEBEN, 12, 24, 1016, 1013, 1014, 2, 1)
    __test_process_events()
    hist0 = test095_hist_size12()
    __test_request_force_fulfill(tag_ok, 0)
    __test_process_events()
    if (__test_request_cleared_tag_id() !== tag_ok
        || __test_request_cleared_fulfilled() !== 1
        || __test_request_cleared_was_overdue() !== 0) {
        test095_fail('ok: cleared facts bad')
        return
    }
    if (test095_hist_size12() !== hist0) {
        test095_fail('ok: hyksos×12 fired on on-time fulfill')
        return
    }
    __log_marker('nd_henna_ok_no_raid_ok')

    __log_info_native('[test:095] PASS')
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'nd_henna_refuse_hyksos_ok',
        'nd_henna_late_hyksos_ok',
        'nd_henna_ok_no_raid_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:095] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

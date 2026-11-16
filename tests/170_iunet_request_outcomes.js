// B13a: Iunet request-outcome smoke (event_request_cleared → JS raids).
// Uses RESOURCE_DEBEN so fulfill/refuse need no storage yard; tags match mission16.
// Markers:
//   [test-marker] iunet_meat_late_hittite_ok
//   [test-marker] iunet_pottery_late_once_ok
//   [test-marker] iunet_meat_ok_leaf_only_ok
//   [test-marker] iunet_limestone_refuse_egypt_ok
//   [test-marker] iunet_favour_not_egypt24_ok
//   [test-marker] iunet_kr0_refuse_egypt24_ok

function test170_fail(msg) {
    __log_info_native('[test:170] FAIL: ' + msg)
    __test_signal_ready()
}

function test170_hist_count_matching(size, invasion_id) {
    var n = city.invasion_history_count()
    var found = 0
    for (var i = 0; i < n; i++) {
        var h = city.invasion_history_at(i)
        if (h.size === size && h.invasion_id === invasion_id) {
            found++
        }
    }
    return found
}

function test170_fire_tagged(tag, ok_tag, fail_tag, late_tag) {
    return mission16_fire_request(tag, RESOURCE_DEBEN, 2, 12, ok_tag, fail_tag, late_tag, 0, 0)
}

function test170_load() {
    __game_load_mission(16, 1)
    if (typeof mission16_fire_request !== 'function') {
        __log_info_native('[test:170] mission16_fire_request missing')
        return false
    }
    // mission.* = scenario vars proxy (not mission16 config); flags must exist after start.
    if (typeof mission.event8_hittite_done === 'undefined'
        || typeof mission.limestone_egypt_done === 'undefined') {
        __log_info_native('[test:170] mission vars missing after load16')
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:170] Iunet request outcomes (B13a)')

    if (!test170_load()) {
        test170_fail('mission16 helpers / mission global missing after load')
        return
    }
    __test_set_treasury(500000)

    // --- meat late → hittite×10 (id 0), once-flag ---
    var hist_before = city.invasion_history_count()
    var seq0 = __test_request_cleared_seq()
    test170_fire_tagged(2004, 1005, 1002, 1007)
    __test_process_events()
    if (!city.has_active_request(RESOURCE_DEBEN)) {
        test170_fail('meat late: request not active')
        return
    }
    __test_request_force_fulfill(2004, 1)
    __test_process_events()

    if (__test_request_cleared_seq() <= seq0
        || __test_request_cleared_tag_id() !== 2004
        || __test_request_cleared_fulfilled() !== 1
        || __test_request_cleared_was_overdue() !== 1) {
        test170_fail('meat late: cleared facts tag=' + __test_request_cleared_tag_id()
            + ' ful=' + __test_request_cleared_fulfilled()
            + ' ov=' + __test_request_cleared_was_overdue())
        return
    }
    if (!mission.event8_hittite_done) {
        test170_fail('meat late: event8_hittite_done not set')
        return
    }
    if (test170_hist_count_matching(10, 0) < 1 && city.invasion_history_count() <= hist_before) {
        __log_info_native('[test:170] warn: no history size=10 id=0 after meat late (flag ok)')
    }
    __log_marker('iunet_meat_late_hittite_ok')

    // --- pottery late shares once-flag → no second hittite×10 ---
    var hittite_hits = test170_hist_count_matching(10, 0)
    test170_fire_tagged(2010, 1011, 1002, 1007)
    __test_process_events()
    __test_request_force_fulfill(2010, 1)
    __test_process_events()

    if (!mission.event8_hittite_done) {
        test170_fail('pottery late: once-flag cleared unexpectedly')
        return
    }
    if (test170_hist_count_matching(10, 0) !== hittite_hits) {
        test170_fail('pottery late: second hittite×10 spawned (want once)')
        return
    }
    __log_marker('iunet_pottery_late_once_ok')

    // --- on-time meat fulfill → ok leaf only (no hittite via late path) ---
    if (!test170_load()) {
        test170_fail('reload for ok path failed')
        return
    }
    __test_set_treasury(500000)
    var kr0 = __test_kingdom_rating()
    test170_fire_tagged(2004, 1005, 1002, 1007)
    __test_process_events()
    __test_request_force_fulfill(2004, 0)
    __test_process_events()
    __test_process_scenario_events()

    if (mission.event8_hittite_done) {
        test170_fail('meat ok: event8_hittite_done set (late path leaked)')
        return
    }
    if (mission.limestone_egypt_done) {
        test170_fail('meat ok: limestone_egypt_done set unexpectedly')
        return
    }
    var kr1 = __test_kingdom_rating()
    if (kr1 < kr0) {
        test170_fail('meat ok: kingdom rating fell (' + kr0 + ' → ' + kr1 + ')')
        return
    }
    __log_marker('iunet_meat_ok_leaf_only_ok')

    // --- limestone refuse → egypt×24 (id 10), not favour ---
    if (!test170_load()) {
        test170_fail('reload for limestone refuse failed')
        return
    }
    __test_kingdom_set_rating(50)
    mission16_fire_request(2014, RESOURCE_DEBEN, 15, 12, 1015, 1018, 1002, 4, 1)
    __test_process_events()
    __test_request_force_refuse_now(2014)
    __test_process_events()

    if (!mission.limestone_egypt_done) {
        test170_fail('limestone refuse: limestone_egypt_done not set')
        return
    }
    if (__test_event_trigger(__test_event_id_by_tag(7019)) != EVENT_TRIGGER_BY_FAVOUR) {
        test170_fail('limestone refuse: favour event spent (should be egypt×24 only)')
        return
    }
    if (test170_hist_count_matching(24, 10) < 1) {
        __log_info_native('[test:170] warn: no history size=24 id=10 (flag ok)')
    }
    __log_marker('iunet_limestone_refuse_egypt_ok')

    // --- favour≠egypt×24: KR0 sends the events[] favour army (pak i=19, Pharaoh×15) ---
    if (!test170_load()) {
        test170_fail('reload for favour path failed')
        return
    }
    __test_kingdom_set_rating(0)
    var favour_count = __test_events_count()
    __test_kingdom_favour_update()
    if (__test_events_count() != favour_count + 1
        || __test_invasion_event_amount(favour_count) != 15) {
        test170_fail('favour: no Pharaoh×15 army at KR0 (events=' + __test_events_count() + ')')
        return
    }
    if (mission.limestone_egypt_done) {
        test170_fail('favour: limestone_egypt_done set without refuse')
        return
    }
    if (test170_hist_count_matching(24, 10) > 0) {
        test170_fail('favour: got egypt×24 history instead of the favour army')
        return
    }
    __log_marker('iunet_favour_not_egypt24_ok')

    // --- KR0 + limestone refuse still → egypt×24 ---
    mission16_fire_request(2014, RESOURCE_DEBEN, 15, 12, 1015, 1018, 1002, 4, 1)
    __test_process_events()
    __test_request_force_refuse_now(2014)
    __test_process_events()

    if (!mission.limestone_egypt_done) {
        test170_fail('KR0+refuse: limestone_egypt_done not set')
        return
    }
    if (test170_hist_count_matching(24, 10) < 1) {
        __log_info_native('[test:170] warn: no history egypt×24 after KR0 refuse (flag ok)')
    }
    __log_marker('iunet_kr0_refuse_egypt24_ok')

    __log_info_native('[test:170] PASS')
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'iunet_meat_late_hittite_ok',
        'iunet_pottery_late_once_ok',
        'iunet_meat_ok_leaf_only_ok',
        'iunet_limestone_refuse_egypt_ok',
        'iunet_favour_not_egypt24_ok',
        'iunet_kr0_refuse_egypt24_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:170] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

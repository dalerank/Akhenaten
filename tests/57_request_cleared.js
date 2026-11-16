// event_request_cleared facts — ok / late (overdue fulfill) / refuse; ok and late arrive after
// the OG delivery months.
// Uses RESOURCE_DEBEN so fulfill does not need a storage yard.
//
// Markers:
//   [test-marker] request_cleared_ok
//   [test-marker] request_cleared_late
//   [test-marker] request_cleared_refuse

function request_cleared_expect(label, tag, resource, fulfilled, was_overdue) {
    if (__test_request_cleared_tag_id() !== tag) {
        __log_info_native('[test:57] ' + label + ' tag got ' + __test_request_cleared_tag_id() + ' want ' + tag)
        return false
    }
    if (__test_request_cleared_resource() !== resource) {
        __log_info_native('[test:57] ' + label + ' resource got ' + __test_request_cleared_resource())
        return false
    }
    if (__test_request_cleared_fulfilled() !== fulfilled) {
        __log_info_native('[test:57] ' + label + ' fulfilled got ' + __test_request_cleared_fulfilled())
        return false
    }
    if (__test_request_cleared_was_overdue() !== was_overdue) {
        __log_info_native('[test:57] ' + label + ' was_overdue got ' + __test_request_cleared_was_overdue())
        return false
    }
    return true
}

// OG requests.c: dispatched goods arrive after 1..4 months.
function test57_wait_delivery(seq) {
    for (var m = 0; m < 4 && __test_request_cleared_seq() <= seq; m++) {
        __test_process_scenario_events()
    }
}

function run_test() {
    __log_info_native('[test:57] request_cleared ok/late/refuse')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(500000)

    var seq0 = __test_request_cleared_seq()

    // --- ok: fulfill before deadline ---
    var ok_tag = 5701
    var req = city.create_good_request({
        tag_id: ok_tag,
        resource: RESOURCE_DEBEN,
        amount: 50,
        months_initial: 6
    })
    city.create_chain_event({
        tag_id: 5711,
        type: EVENT_TYPE_REPUTATION_INCREASE,
        amount: 2
    })
    req.set_completed_action_tag(5711)
    req.execute()
    __test_process_events()

    if (!city.has_active_request(RESOURCE_DEBEN)) {
        __log_info_native('[test:57] ok path: request not active after execute')
        __test_signal_ready()
        return
    }

    __scenario_request_dispatch(0)
    __test_process_events()
    test57_wait_delivery(seq0)

    if (__test_request_cleared_seq() <= seq0) {
        __log_info_native('[test:57] ok path: no cleared emit')
        __test_signal_ready()
        return
    }
    if (!request_cleared_expect('ok', ok_tag, RESOURCE_DEBEN, 1, 0)) {
        __test_signal_ready()
        return
    }
    __log_marker('request_cleared_ok')

    // --- late: fulfill while overdue ---
    var late_tag = 5702
    var seq1 = __test_request_cleared_seq()
    var late_req = city.create_good_request({
        tag_id: late_tag,
        resource: RESOURCE_DEBEN,
        amount: 40,
        months_initial: 1
    })
    city.create_chain_event({
        tag_id: 5712,
        type: EVENT_TYPE_REPUTATION_DECREASE,
        amount: 5
    })
    late_req.set_too_late_action_tag(5712)
    late_req.execute()
    __test_process_events()
    __test_request_force_overdue(late_tag, 8)

    if (!city.has_active_request(RESOURCE_DEBEN)) {
        __log_info_native('[test:57] late path: request not active')
        __test_signal_ready()
        return
    }

    __scenario_request_dispatch(0)
    __test_process_events()
    test57_wait_delivery(seq1)

    if (__test_request_cleared_seq() <= seq1) {
        __log_info_native('[test:57] late path: no cleared emit')
        __test_signal_ready()
        return
    }
    if (!request_cleared_expect('late', late_tag, RESOURCE_DEBEN, 1, 1)) {
        __test_signal_ready()
        return
    }
    __log_marker('request_cleared_late')

    // --- refuse: grace expire ---
    var refuse_tag = 5703
    var seq2 = __test_request_cleared_seq()
    var refuse_req = city.create_good_request({
        tag_id: refuse_tag,
        resource: RESOURCE_DEBEN,
        amount: 30,
        months_initial: 1
    })
    city.create_chain_event({
        tag_id: 5713,
        type: EVENT_TYPE_REPUTATION_DECREASE,
        amount: 4
    })
    refuse_req.set_refusal_action_tag(5713)
    refuse_req.execute()
    __test_process_events()
    __test_request_force_refuse_now(refuse_tag)

    if (__test_request_cleared_seq() <= seq2) {
        __log_info_native('[test:57] refuse path: no cleared emit')
        __test_signal_ready()
        return
    }
    if (!request_cleared_expect('refuse', refuse_tag, RESOURCE_DEBEN, 0, 1)) {
        __test_signal_ready()
        return
    }
    __log_marker('request_cleared_refuse')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'request_cleared_ok',
        'request_cleared_late',
        'request_cleared_refuse'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:57] missing marker: ' + marker)
            return false
        }
    }
    return true
}

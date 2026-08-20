// Pharaoh request fields (tag / state / months / faction) round-trip through .svx.
// Fulfill after load must still emit event_request_cleared with the original tag.
// Markers:
//   [test-marker] request_saveload_active_ok
//   [test-marker] request_saveload_fulfill_tag_ok
//   [test-marker] request_saveload_overdue_ok

function test184_fail(msg) {
    __log_info_native('[test:184] FAIL: ' + msg)
    __test_signal_ready()
}

function test184_roundtrip(save_name) {
    if (!__game_write_savegame(save_name)) {
        test184_fail('write_savegame failed')
        return false
    }
    if (!__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        test184_fail('load_savegame failed')
        return false
    }
    __game_delete_savegame(save_name)
    return true
}

function run_test() {
    __log_info_native('[test:184] pharaoh request saveload')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(500000)
    __test_kingdom_set_rating(40)

    var tag = 18401
    var req = city.create_good_request({
        tag_id: tag,
        resource: RESOURCE_DEBEN,
        amount: 50,
        months_initial: 9
    })
    city.create_chain_event({
        tag_id: 18411,
        type: EVENT_TYPE_REPUTATION_INCREASE,
        amount: 4
    })
    req.set_completed_action_tag(18411)
    req.set_sender_faction(1)
    req.execute()
    __test_process_events()

    if (!__test_request_is_active(tag)) {
        test184_fail('active request missing after execute')
        return
    }

    var months = __test_request_months_left(tag)
    var state = __test_request_state(tag)
    if (months < 0 || state < 0) {
        test184_fail('snapshot months=' + months + ' state=' + state)
        return
    }

    if (!test184_roundtrip('test_184_request_active.svx')) {
        return
    }

    if (!__test_request_exists(tag)
        || !__test_request_is_active(tag)
        || __test_request_resource(tag) !== RESOURCE_DEBEN
        || __test_request_amount(tag) !== 50
        || __test_request_months_left(tag) !== months
        || __test_request_state(tag) !== state
        || __test_request_sender_faction(tag) !== 1) {
        test184_fail('after load tag=' + __test_request_exists(tag)
            + ' active=' + __test_request_is_active(tag)
            + ' res=' + __test_request_resource(tag)
            + ' amt=' + __test_request_amount(tag)
            + ' months=' + __test_request_months_left(tag) + ' want=' + months
            + ' state=' + __test_request_state(tag) + ' want=' + state
            + ' faction=' + __test_request_sender_faction(tag))
        return
    }
    __log_marker('request_saveload_active_ok')

    var kr0 = __test_kingdom_rating()
    var seq0 = __test_request_cleared_seq()
    __test_request_force_fulfill(tag, 0)
    __test_process_events()
    __test_process_scenario_events()

    if (__test_request_cleared_seq() <= seq0
        || __test_request_cleared_tag_id() !== tag
        || __test_request_cleared_fulfilled() !== 1
        || __test_request_cleared_was_overdue() !== 0) {
        test184_fail('fulfill after load tag=' + __test_request_cleared_tag_id()
            + ' ful=' + __test_request_cleared_fulfilled()
            + ' ov=' + __test_request_cleared_was_overdue()
            + ' seq=' + __test_request_cleared_seq())
        return
    }
    if (__test_request_is_active(tag)) {
        test184_fail('request still active after fulfill')
        return
    }
    if (__test_kingdom_rating() < kr0 + 4) {
        test184_fail('ok chain KR want>=' + (kr0 + 4) + ' got=' + __test_kingdom_rating())
        return
    }
    __log_marker('request_saveload_fulfill_tag_ok')

    var late_tag = 18402
    var late_req = city.create_good_request({
        tag_id: late_tag,
        resource: RESOURCE_DEBEN,
        amount: 35,
        months_initial: 3
    })
    late_req.execute()
    __test_process_events()
    __test_request_force_overdue(late_tag, 11)

    if (!test184_roundtrip('test_184_request_overdue.svx')) {
        return
    }

    if (!__test_request_is_active(late_tag)
        || __test_request_state(late_tag) !== 2
        || __test_request_months_left(late_tag) !== 11
        || __test_request_amount(late_tag) !== 35
        || __test_request_sender_faction(late_tag) !== 1) {
        test184_fail('overdue after load active=' + __test_request_is_active(late_tag)
            + ' state=' + __test_request_state(late_tag)
            + ' months=' + __test_request_months_left(late_tag)
            + ' amt=' + __test_request_amount(late_tag)
            + ' faction=' + __test_request_sender_faction(late_tag))
        return
    }

    seq0 = __test_request_cleared_seq()
    __test_request_force_fulfill(late_tag, 1)
    __test_process_events()
    __test_process_scenario_events()
    if (__test_request_cleared_seq() <= seq0
        || __test_request_cleared_tag_id() !== late_tag
        || __test_request_cleared_fulfilled() !== 1
        || __test_request_cleared_was_overdue() !== 1) {
        test184_fail('late fulfill after load tag=' + __test_request_cleared_tag_id()
            + ' ful=' + __test_request_cleared_fulfilled()
            + ' ov=' + __test_request_cleared_was_overdue())
        return
    }
    __log_marker('request_saveload_overdue_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'request_saveload_active_ok',
        'request_saveload_fulfill_tag_ok',
        'request_saveload_overdue_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:184] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

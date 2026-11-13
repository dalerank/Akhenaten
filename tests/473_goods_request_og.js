// Goods requests vs OG scenario_events.c:705-857 and requests.c:105-136:
//   the dispatch sends the goods off and they arrive 1..4 months later, the reward is the
//   on_completed chain only (no rating bonus of its own); a request not answered in time costs
//   3 Kingdom rating, gets 24 more months and, if answered then, fires on_too_late; never answered,
//   it fires on_refusal.
// Markers:
//   [test-marker] goods_request_og_travel_ok
//   [test-marker] goods_request_og_too_late_ok
//   [test-marker] goods_request_og_ignored_ok

var REQ_IN_PROGRESS = 1
var REQ_OVERDUE = 2
var REQ_FAILED = 5
var REQ_RECEIVED = 6
var REQ_DISPATCHED = 8
var REQ_DISPATCHED_LATE = 9

function test473_fail(msg) {
    __log_info_native('[test:473] FAIL: ' + msg)
}

function test473_request(tag, amount, months, completed_kr, late_kr, refuse_kr) {
    var req = city.create_good_request({ tag_id: tag, resource: RESOURCE_DEBEN, amount: amount, months_initial: months })
    city.create_chain_event({ tag_id: tag + 1, type: EVENT_TYPE_REPUTATION_INCREASE, amount: completed_kr })
    city.create_chain_event({ tag_id: tag + 2, type: EVENT_TYPE_REPUTATION_DECREASE, amount: late_kr })
    city.create_chain_event({ tag_id: tag + 3, type: EVENT_TYPE_REPUTATION_DECREASE, amount: refuse_kr })
    req.set_completed_action_tag(tag + 1)
    req.set_too_late_action_tag(tag + 2)
    req.set_refusal_action_tag(tag + 3)
    req.execute()
}

// Runs monthly passes until the request leaves `state`; returns the passes run.
function test473_months_until_not(tag, state, max) {
    var m = 0
    while (m < max && __test_request_state(tag) == state) {
        __test_process_scenario_events()
        m++
    }
    return m
}

function test473_travel() {
    __test_set_treasury(10000)
    __test_kingdom_set_rating(50)
    var tag = 47301
    test473_request(tag, 100, 12, 2, 1, 4)
    if (__test_request_state(tag) != REQ_IN_PROGRESS || __test_request_months_left(tag) != 12) {
        test473_fail('start: state=' + __test_request_state(tag) + ' months=' + __test_request_months_left(tag))
        return
    }
    __test_request_dispatch_by_tag(tag)
    __test_process_events()
    var travel = __test_request_months_left(tag)
    if (__test_request_state(tag) != REQ_DISPATCHED || travel < 1 || travel > 4 || __test_treasury() != 9900) {
        test473_fail('dispatch: state=' + __test_request_state(tag) + ' travel=' + travel + ' treasury=' + __test_treasury())
        return
    }
    var seq0 = __test_request_cleared_seq()
    var months = test473_months_until_not(tag, REQ_DISPATCHED, 6)
    if (months != travel || __test_request_state(tag) != REQ_RECEIVED || __test_request_cleared_seq() <= seq0
        || __test_request_cleared_fulfilled() != 1 || __test_request_cleared_was_overdue() != 0
        || __test_kingdom_rating() != 52) {
        // The completed chain child runs later in the same monthly pass: +2 and nothing else.
        test473_fail('arrival: months=' + months + ' travel=' + travel + ' state=' + __test_request_state(tag)
            + ' kr=' + __test_kingdom_rating() + ' (want 52)')
        return
    }
    __log_marker('goods_request_og_travel_ok')
}

function test473_too_late() {
    __test_set_treasury(10000)
    __test_kingdom_set_rating(50)
    var tag = 47311
    test473_request(tag, 100, 2, 2, 1, 4)
    __test_process_scenario_events()
    __test_process_scenario_events()
    if (__test_request_state(tag) != REQ_OVERDUE || __test_request_months_left(tag) != 24 || __test_kingdom_rating() != 47) {
        test473_fail('overdue: state=' + __test_request_state(tag) + ' months=' + __test_request_months_left(tag)
            + ' kr=' + __test_kingdom_rating())
        return
    }
    __test_request_dispatch_by_tag(tag)
    if (__test_request_state(tag) != REQ_DISPATCHED_LATE) {
        test473_fail('late dispatch: state=' + __test_request_state(tag))
        return
    }
    test473_months_until_not(tag, REQ_DISPATCHED_LATE, 6)
    __test_process_scenario_events()
    if (__test_request_state(tag) != REQ_RECEIVED || __test_request_cleared_was_overdue() != 1 || __test_kingdom_rating() != 46) {
        test473_fail('too late: state=' + __test_request_state(tag) + ' overdue=' + __test_request_cleared_was_overdue()
            + ' kr=' + __test_kingdom_rating())
        return
    }
    __log_marker('goods_request_og_too_late_ok')
}

function test473_ignored() {
    __test_kingdom_set_rating(50)
    var tag = 47321
    test473_request(tag, 100, 1, 2, 1, 4)
    __test_process_scenario_events()
    if (__test_request_state(tag) != REQ_OVERDUE || __test_kingdom_rating() != 47) {
        test473_fail('ignored overdue: state=' + __test_request_state(tag) + ' kr=' + __test_kingdom_rating())
        return
    }
    var seq0 = __test_request_cleared_seq()
    var months = test473_months_until_not(tag, REQ_OVERDUE, 30)
    __test_process_scenario_events()
    if (months != 24 || __test_request_state(tag) != REQ_FAILED || __test_request_is_active(tag)
        || __test_request_cleared_seq() <= seq0 || __test_request_cleared_fulfilled() != 0 || __test_kingdom_rating() != 43) {
        test473_fail('ignored: months=' + months + ' state=' + __test_request_state(tag) + ' kr=' + __test_kingdom_rating())
        return
    }
    __log_marker('goods_request_og_ignored_ok')
}

function run_test() {
    __log_info_native('[test:473] OG goods requests')
    test_reload_city_session('data/default.map')
    test473_travel()
    test473_too_late()
    test473_ignored()
    __test_signal_ready()
}

function check_valid() {
    var markers = ['goods_request_og_travel_ok', 'goods_request_og_too_late_ok', 'goods_request_og_ignored_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:473] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

// Troop requests vs OG scenario_events.c:859-972 and requests.c:181-199:
//   dispatched legions are away for the travel months (12 without a route); at the deadline they win
//   when their strength covers the amount (losses by troops_loss_brackets) or under Seth's blessing,
//   else they are lost (on_defeat); still more than 2 months away they come back too late (on_too_late);
//   never sent, the request is refused. The winners return after the travel months.
// Markers:
//   [test-marker] troops_request_og_win_ok
//   [test-marker] troops_request_og_return_ok
//   [test-marker] troops_request_og_defeat_ok
//   [test-marker] troops_request_og_seth_ok
//   [test-marker] troops_request_og_too_late_ok
//   [test-marker] troops_request_og_refuse_ok

var REQ_IN_PROGRESS = 1
var REQ_RECEIVED = 6
var REQ_TROOPS_AWAY = 10
var REQ_TROOPS_RETURN = 11
var REQ_TROOPS_RETURN_TOO_LATE = 12

function test377_fail(msg) {
    __log_info_native('[test:377] FAIL: ' + msg)
}

// Fresh city at year 1 month 0 with one company of 16 infantry (strength 16).
function test377_session() {
    test_reload_city_session('data/default.map')
    __test_simtime_set(1, 0)
    __test_kingdom_set_rating(50)
    __test_set_seth_protect_troops(0)
    return __test_land_company_create(16)
}

// Troop request with KR leaves: ok +2, refuse -3, late -4, defeat -5.
function test377_request(tag, amount) {
    var req = city.create_good_request({ tag_id: tag, resource: RESOURCE_TROOPS, amount: amount, months_initial: 12,
        subtype: EVENT_SUBTYPE_DISTANT_BATTLE })
    city.create_chain_event({ tag_id: tag + 1, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 2 })
    city.create_chain_event({ tag_id: tag + 2, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 3 })
    city.create_chain_event({ tag_id: tag + 3, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 4 })
    city.create_chain_event({ tag_id: tag + 4, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 5 })
    req.set_completed_action_tag(tag + 1)
    req.set_refusal_action_tag(tag + 2)
    req.set_too_late_action_tag(tag + 3)
    req.set_defeat_action_tag(tag + 4)
    req.execute()
}

// Monthly passes for months first..last of year 1 onwards (month 12 = year 2 month 0).
function test377_months(first, last) {
    for (var m = first; m <= last; m++) {
        __test_simtime_set(1 + ((m / 12) | 0), m % 12)
        __test_process_scenario_events()
    }
}

function test377_win_and_return() {
    var company = test377_session()
    if (!company) {
        test377_fail('no company')
        return
    }
    var tag = 47401
    test377_request(tag, 10)
    if (__test_request_state(tag) != REQ_IN_PROGRESS) {
        test377_fail('start: state=' + __test_request_state(tag))
        return
    }
    __test_request_dispatch_by_tag(tag)
    if (__test_request_state(tag) != REQ_TROOPS_AWAY || __test_request_months_left(tag) != 12
        || __test_formation_request_strength(__test_event_id_by_tag(tag)) != 16) {
        test377_fail('dispatch: state=' + __test_request_state(tag) + ' months=' + __test_request_months_left(tag)
            + ' strength=' + __test_formation_request_strength(__test_event_id_by_tag(tag)))
        return
    }
    test377_months(1, 11)
    if (__test_request_state(tag) != REQ_TROOPS_AWAY || __test_request_months_left(tag) != 1) {
        test377_fail('away: state=' + __test_request_state(tag) + ' months=' + __test_request_months_left(tag))
        return
    }
    var seq0 = __test_request_cleared_seq()
    test377_months(12, 12)
    // 16 against 10: (16 - 10) * 100 / 16 = 37% to spare, so 25% losses: 4 of 16.
    var alive = __test_formation_alive_count(company)
    if (__test_request_state(tag) != REQ_TROOPS_RETURN || __test_request_cleared_seq() <= seq0
        || __test_request_cleared_fulfilled() != 1 || alive != 12) {
        test377_fail('win: state=' + __test_request_state(tag) + ' fulfilled=' + __test_request_cleared_fulfilled()
            + ' alive=' + alive)
        return
    }
    __log_marker('troops_request_og_win_ok')

    test377_months(13, 13)
    if (__test_request_state(tag) != REQ_RECEIVED || __test_request_is_active(tag)
        || __test_formation_request_event_id(company) != -1 || __test_kingdom_rating() != 52) {
        test377_fail('return: state=' + __test_request_state(tag) + ' request_event=' + __test_formation_request_event_id(company)
            + ' kr=' + __test_kingdom_rating())
        return
    }
    __log_marker('troops_request_og_return_ok')
}

function test377_defeat() {
    var company = test377_session()
    var tag = 47411
    test377_request(tag, 40)
    __test_request_dispatch_by_tag(tag)
    test377_months(1, 13)
    if (__test_request_state(tag) != REQ_RECEIVED || __test_request_cleared_fulfilled() != 0
        || __test_formation_alive_count(company) != 0 || __test_kingdom_rating() != 45) {
        test377_fail('defeat: state=' + __test_request_state(tag) + ' fulfilled=' + __test_request_cleared_fulfilled()
            + ' alive=' + __test_formation_alive_count(company) + ' kr=' + __test_kingdom_rating())
        return
    }
    __log_marker('troops_request_og_defeat_ok')
}

function test377_seth() {
    var company = test377_session()
    __test_set_seth_protect_troops(10)
    var tag = 47421
    test377_request(tag, 40)
    __test_request_dispatch_by_tag(tag)
    test377_months(1, 12)
    if (__test_request_state(tag) != REQ_TROOPS_RETURN || __test_formation_alive_count(company) != 16) {
        test377_fail('seth: state=' + __test_request_state(tag) + ' alive=' + __test_formation_alive_count(company))
        return
    }
    __log_marker('troops_request_og_seth_ok')
}

// Sent in month 6 with 12 months of travel: at the deadline they are 6 months away.
function test377_too_late() {
    test377_session()
    var tag = 47431
    test377_request(tag, 10)
    test377_months(1, 6)
    __test_request_dispatch_by_tag(tag)
    test377_months(7, 12)
    if (__test_request_state(tag) != REQ_TROOPS_RETURN_TOO_LATE || __test_request_cleared_was_overdue() != 1) {
        test377_fail('too late: state=' + __test_request_state(tag) + ' overdue=' + __test_request_cleared_was_overdue())
        return
    }
    test377_months(13, 14)
    if (__test_request_state(tag) != REQ_RECEIVED || __test_kingdom_rating() != 46) {
        test377_fail('too late return: state=' + __test_request_state(tag) + ' kr=' + __test_kingdom_rating())
        return
    }
    __log_marker('troops_request_og_too_late_ok')
}

function test377_refuse() {
    test377_session()
    var tag = 47441
    test377_request(tag, 10)
    test377_months(1, 13)
    if (__test_request_state(tag) != REQ_RECEIVED || __test_request_cleared_fulfilled() != 0 || __test_kingdom_rating() != 47) {
        test377_fail('refuse: state=' + __test_request_state(tag) + ' fulfilled=' + __test_request_cleared_fulfilled()
            + ' kr=' + __test_kingdom_rating())
        return
    }
    __log_marker('troops_request_og_refuse_ok')
}

function run_test() {
    __log_info_native('[test:377] OG troop requests')
    test377_win_and_return()
    test377_defeat()
    test377_seth()
    test377_too_late()
    test377_refuse()
    __test_signal_ready()
}

function check_valid() {
    var markers = ['troops_request_og_win_ok', 'troops_request_og_return_ok', 'troops_request_og_defeat_ok',
        'troops_request_og_seth_ok', 'troops_request_og_too_late_ok', 'troops_request_og_refuse_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:377] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

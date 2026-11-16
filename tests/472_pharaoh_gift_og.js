// EVENT_TYPE_GIFT_FROM_PHARAOH vs OG scenario_events.c:473-581 and gift_buttons.c:
//   the offer is a gift message with Accept / Refuse (all fits), Accept / Later / Refuse (half fits)
//   or no buttons (less than half fits: offered again a month later, then a last chance, then lost);
//   money goes to the treasury; accept / refuse / too late fire on_completed / on_refusal / on_too_late.
// Markers:
//   [test-marker] gift_og_money_accept_ok
//   [test-marker] gift_og_refuse_ok
//   [test-marker] gift_og_later_ok
//   [test-marker] gift_og_too_late_ok

var GIFT_OFFERED = 1
var GIFT_OFFER_AGAIN = 2
var GIFT_OFFERED_AGAIN = 3
var GIFT_OFFER_LAST = 4
var GIFT_OFFERED_LAST = 5
var GIFT_TOO_LATE = 8
var GIFT_DONE = 9
var BTN_REFUSE = 1
var BTN_LATER = 2
var BTN_ACCEPT = 4

function test472_fail(msg) {
    __log_info_native('[test:472] FAIL: ' + msg)
}

// A gift with a reputation chain event on the given outcome; returns the gift's event id.
function test472_gift(tag, resource, amount, outcome, kr) {
    var leaf = tag + 1
    city.create_chain_event({ tag_id: leaf, type: kr > 0 ? EVENT_TYPE_REPUTATION_INCREASE : EVENT_TYPE_REPUTATION_DECREASE,
        amount: kr > 0 ? kr : -kr })
    var gift = city.create_pharaoh_gift({ tag_id: tag, resource: resource, amount: amount })
    if (outcome == 'ok') {
        __city_request_set_completed_action(tag, leaf)
    } else if (outcome == 'refuse') {
        __city_request_set_refusal_action(tag, leaf)
    } else {
        __city_request_set_too_late_action(tag, leaf)
    }
    gift.execute()
    return __test_event_id_by_tag(tag)
}

// Messages are not posted without game data, so the offer is checked by its log line.
function test472_offer_logged(id, buttons) {
    return __test_find_inlog('[gift] offer event=' + id + ' buttons=' + buttons + ' ')
}

function test472_money_accept() {
    __test_set_treasury(1000)
    __test_kingdom_set_rating(50)
    var id = test472_gift(47201, RESOURCE_DEBEN, 300, 'ok', 4)
    if (__test_event_state(id) != GIFT_OFFERED || !test472_offer_logged(id, BTN_ACCEPT | BTN_REFUSE)) {
        test472_fail('money offer: state=' + __test_event_state(id))
        return
    }
    __test_gift_reply(id, BTN_ACCEPT)
    // The chain child made by the reply runs on the next monthly pass.
    __test_process_scenario_events()
    if (__test_event_state(id) != GIFT_DONE || __test_treasury() != 1300
        || !__test_find_inlog('[gift] accepted event=' + id + ' delivered=300') || __test_kingdom_rating() != 54) {
        test472_fail('money accept: state=' + __test_event_state(id) + ' treasury=' + __test_treasury()
            + ' kr=' + __test_kingdom_rating())
        return
    }
    __log_marker('gift_og_money_accept_ok')
}

function test472_refuse() {
    __test_set_treasury(1000)
    __test_kingdom_set_rating(50)
    var id = test472_gift(47211, RESOURCE_DEBEN, 200, 'refuse', -3)
    __test_gift_reply(id, BTN_REFUSE)
    __test_process_scenario_events()
    if (__test_event_state(id) != GIFT_DONE || __test_treasury() != 1000 || __test_kingdom_rating() != 47
        || !__test_find_inlog('[gift] refused event=' + id)) {
        test472_fail('refuse: state=' + __test_event_state(id) + ' treasury=' + __test_treasury()
            + ' kr=' + __test_kingdom_rating())
        return
    }
    // A reply after the gift is settled does nothing.
    if (__test_gift_reply(id, BTN_ACCEPT) != 0 || __test_treasury() != 1000) {
        test472_fail('reply after refuse was taken')
        return
    }
    __log_marker('gift_og_refuse_ok')
}

// 40 loads offered, one storage yard with room for 32: half fits, so Later is offered.
function test472_later() {
    __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    var yard = __test_building_create(BUILDING_STORAGE_YARD, -1, -1)
    if (!yard) {
        test472_fail('no storage yard')
        return
    }
    __test_building_force_road_access(yard)
    __test_building_set_workers(yard, 6)
    __test_storage_yard_set_state(yard, RESOURCE_POTTERY, STORAGE_STATE_ACCEPT)
    var stored0 = __test_yards_stored(RESOURCE_POTTERY)
    __test_kingdom_set_rating(50)

    var id = test472_gift(47221, RESOURCE_POTTERY, 40, 'ok', 2)
    if (__test_event_state(id) != GIFT_OFFERED || !test472_offer_logged(id, BTN_ACCEPT | BTN_LATER | BTN_REFUSE)) {
        test472_fail('partial offer: state=' + __test_event_state(id) + ' stored0=' + stored0)
        return
    }
    __test_gift_reply(id, BTN_LATER)
    if (__test_event_state(id) != GIFT_OFFER_AGAIN) {
        test472_fail('later: state=' + __test_event_state(id))
        return
    }
    __test_process_scenario_events()
    if (__test_event_state(id) != GIFT_OFFERED_AGAIN) {
        test472_fail('offered again: state=' + __test_event_state(id))
        return
    }
    __test_gift_reply(id, BTN_LATER)
    __test_process_scenario_events()
    if (__test_event_state(id) != GIFT_OFFERED_LAST) {
        test472_fail('last chance: state=' + __test_event_state(id))
        return
    }
    __test_gift_reply(id, BTN_ACCEPT)
    __test_process_scenario_events()
    // Only what fits is stored: something, but not all 40 loads.
    var accepted = '[gift] accepted event=' + id + ' delivered='
    if (__test_event_state(id) != GIFT_DONE || !__test_find_inlog(accepted) || __test_find_inlog(accepted + '0')
        || __test_find_inlog(accepted + '40') || __test_kingdom_rating() != 52) {
        test472_fail('accept after later: state=' + __test_event_state(id) + ' kr=' + __test_kingdom_rating())
        return
    }
    __log_marker('gift_og_later_ok')
}

// No room at all: no buttons, offered again, last chance, then lost with on_too_late.
function test472_too_late() {
    test_reload_city_session('data/default.map')
    __test_kingdom_set_rating(50)
    var id = test472_gift(47231, RESOURCE_GRANITE, 20, 'late', -5)
    var states = [__test_event_state(id)]
    for (var m = 0; m < 4; m++) {
        __test_process_scenario_events()
        states.push(__test_event_state(id))
    }
    var want = [GIFT_OFFER_AGAIN, GIFT_OFFER_LAST, GIFT_TOO_LATE, GIFT_DONE, GIFT_DONE]
    if (states.join(',') != want.join(',') || __test_kingdom_rating() != 45) {
        test472_fail('too late: states=' + states.join(',') + ' want ' + want.join(',') + ' kr=' + __test_kingdom_rating())
        return
    }
    __log_marker('gift_og_too_late_ok')
}

function run_test() {
    __log_info_native('[test:472] OG gift from Pharaoh')
    test_reload_city_session('data/default.map')
    test472_money_accept()
    test472_refuse()
    test472_later()
    test472_too_late()
    __test_signal_ready()
}

function check_valid() {
    var markers = ['gift_og_money_accept_ok', 'gift_og_refuse_ok', 'gift_og_later_ok', 'gift_og_too_late_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:472] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

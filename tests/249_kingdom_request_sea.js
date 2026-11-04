// Kingdom troop request by sea (OG legion_requests + transport 221/222/223):
//   board → empire_service → dispatch → GOING/AWAY → return → land.
// Markers:
//   [test-marker] kingdom_request_sea_dispatch_ok
//   [test-marker] kingdom_request_sea_away_ok
//   [test-marker] kingdom_request_sea_return_ok
//   [test-marker] kingdom_request_sea_landed_ok

var __test249_ok = false

var ACTION_TRANSPORT_GOING_TO_REQUEST = 221
var ACTION_TRANSPORT_AWAY_ON_REQUEST = 222
var ACTION_TRANSPORT_RETURNING_FROM_REQUEST = 223

function test249_fail(msg) {
    __log_info_native('[test:249] ' + msg)
    __test_signal_ready()
}

function test249_board(ship, company) {
    __transport_ship_embark(ship, company)
    for (var i = 0; i < 40; i++) {
        __test_figure_action_perform(ship)
        if (__transport_ship_has_troops(ship)) {
            return true
        }
    }
    return false
}

function run_test() {
    __log_info_native('[test:249] kingdom request sea cycle')

    test_reload_city_session('data/default.map')
    var ship = __test_player_transport_spawn_for_embark(4)
    if (!ship) {
        return test249_fail('spawn failed')
    }
    var company = __test_player_transport_company_id()
    if (!company) {
        return test249_fail('no company')
    }
    if (!test249_board(ship, company)) {
        return test249_fail('board failed action=' + __figure_get_action_state(ship))
    }

    __test_formation_set_empire_service(company, 1)
    var event_id = 42
    __test_legion_dispatch_to_request(event_id)

    if (__test_formation_request_event_id(company) != event_id) {
        return test249_fail('formation request_event_id want ' + event_id
            + ' got ' + __test_formation_request_event_id(company))
    }
    if (__test_transport_ship_request_event_id(ship) != event_id) {
        return test249_fail('ship request_event_id want ' + event_id
            + ' got ' + __test_transport_ship_request_event_id(ship))
    }
    if (__figure_get_action_state(ship) != ACTION_TRANSPORT_GOING_TO_REQUEST) {
        return test249_fail('expected GOING_TO_REQUEST, got ' + __figure_get_action_state(ship))
    }
    var strength = __test_formation_request_strength(event_id)
    if (strength <= 0) {
        return test249_fail('expected positive request strength, got ' + strength)
    }
    __log_marker('kingdom_request_sea_dispatch_ok')

    // Arrive at river entry → AWAY (invisible off-map).
    __test_transport_ship_snap_to_destination(ship)
    __test_figure_set_action(ship, ACTION_TRANSPORT_GOING_TO_REQUEST)
    __test_figure_action_perform(ship)
    if (__figure_get_action_state(ship) != ACTION_TRANSPORT_AWAY_ON_REQUEST) {
        return test249_fail('expected AWAY_ON_REQUEST, got ' + __figure_get_action_state(ship))
    }
    if (!__transport_ship_has_troops(ship)) {
        return test249_fail('troops missing while away')
    }
    __log_marker('kingdom_request_sea_away_ok')

    // Battle aftermath → RETURNING_FROM_REQUEST.
    __test_legion_return_from_request(event_id)
    if (__figure_get_action_state(ship) != ACTION_TRANSPORT_RETURNING_FROM_REQUEST) {
        return test249_fail('expected RETURNING_FROM_REQUEST, got ' + __figure_get_action_state(ship))
    }
    if (__test_formation_request_event_id(company) != -1) {
        return test249_fail('formation request_event_id should clear on return, got '
            + __test_formation_request_event_id(company))
    }
    __log_marker('kingdom_request_sea_return_ok')

    // Land troops at landing_point / free land.
    __test_transport_ship_snap_to_destination(ship)
    __test_figure_action_perform(ship)
    if (__transport_ship_has_troops(ship)) {
        return test249_fail('expected empty ship after land, has_troops still set')
    }
    var alive = __test_formation_alive_count(company)
    if (alive < 1) {
        return test249_fail('expected landed company alive, got ' + alive)
    }
    __log_marker('kingdom_request_sea_landed_ok')

    __test249_ok = true
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'kingdom_request_sea_dispatch_ok',
        'kingdom_request_sea_away_ok',
        'kingdom_request_sea_return_ok',
        'kingdom_request_sea_landed_ok'
    ]
    if (!__test249_ok) {
        return false
    }
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            return false
        }
    }
    return true
}

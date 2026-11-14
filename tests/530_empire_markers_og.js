// Empire map markers vs OG window/empire_window.c:615-664 and editor/scenario_event_methods.c troops_request_state:
//   an invasion shows on its route (scenario_event.invasion) once its months left fit in the route's travel months,
//   at 100 - months_left * 100 / travel percent of the path, creeping (anim - 50) / 4 points on; troops sent to a
//   city walk its route away from ours (100 - months_left * 100 / travel) and back (months_left * 100 / travel).
//   A route has a path point every 5 pixels (io/empire_file.c), travel = points * 5 / 400 months.
// Markers:
//   [test-marker] empire_markers_route_ok
//   [test-marker] empire_markers_invasion_ok
//   [test-marker] empire_markers_invasion_gone_ok
//   [test-marker] empire_markers_troops_away_ok
//   [test-marker] empire_markers_troops_return_ok
//   [test-marker] empire_markers_troops_gone_ok
//   [test-marker] empire_markers_pick_ok

var REQ_TROOPS_RETURN = 11

function test530_fail(msg) {
    __log_info_native('[test:530] FAIL: ' + msg)
}

// A trading city, put on route 19 for the troops; the invasion walks route 18.
function test530_find_city() {
    for (var id = 1; id < 80; id++) {
        if (__test_empire_city_trade_only(id, RESOURCE_POTTERY, 1500) >= 0 && __test_empire_city_set_route(id, 19)) {
            return { id: id, route: 19 }
        }
    }
    return null
}

function test530_markers(anim) {
    __test_empire_markers_rebuild(anim)
    var out = []
    for (var i = 0; i < empire.marker_count; i++) {
        out.push(empire.get_marker(i))
    }
    return out
}

// The only marker of the event, checked against kind, sea and position; '' when it matches.
function test530_check(anim, event_id, kind, by_sea, x, y) {
    var all = test530_markers(anim)
    var found = null
    for (var i = 0; i < all.length; i++) {
        if (all[i].event_id == event_id) {
            if (found) {
                return 'two markers for event ' + event_id
            }
            found = all[i]
        }
    }
    if (!found) {
        return 'no marker for event ' + event_id
    }
    if (found.kind != kind || !!found.by_sea != by_sea || found.pos.x != x || found.pos.y != y) {
        return 'marker kind=' + found.kind + ' sea=' + found.by_sea + ' pos=' + found.pos.x + ',' + found.pos.y
            + ' want kind=' + kind + ' sea=' + by_sea + ' pos=' + x + ',' + y
    }
    return ''
}

function test530_has_marker(event_id) {
    var all = test530_markers(0)
    for (var i = 0; i < all.length; i++) {
        if (all[i].event_id == event_id) {
            return true
        }
    }
    return false
}

var test530_month = 0

// Monthly passes up to month `last` of year 1 onwards (month 12 = year 2 month 0).
function test530_months_to(last) {
    for (var m = test530_month + 1; m <= last; m++) {
        __test_simtime_set(1 + ((m / 12) | 0), m % 12)
        __test_process_scenario_events()
    }
    test530_month = Math.max(test530_month, last)
}

// Two straight legs of 1200 pixels: 241 + 241 path points, 482 * 5 / 400 = 6 travel months.
function test530_route(route_id, type, a, b, c) {
    __test_empire_route_set(route_id, type, a, b, c)
    return __test_empire_route_path_length(route_id) == 482 && __test_empire_route_travel_months(route_id) == 6
}

function test530_invasion(ours, route_id) {
    var a = { x: ours.x + 2400, y: ours.y }
    var b = { x: ours.x + 1200, y: ours.y }
    if (!test530_route(route_id, 1, a, b, ours)) {
        test530_fail('invasion route: points=' + __test_empire_route_path_length(route_id)
            + ' months=' + __test_empire_route_travel_months(route_id))
        return
    }
    var p = __test_empire_route_path_point(route_id, 241)
    if (p.x != b.x || p.y != b.y) {
        test530_fail('route point 241=' + p.x + ',' + p.y)
        return
    }
    __log_marker('empire_markers_route_ok')

    __test_og_invasions_set(1)
    var inv = city.create_invasion({ tag_id: 53001, invader: EVENT_INVADER_ENEMY, amount: 10, months_initial: 12,
        route: 1, empire_route: route_id, year: 1, month: 0 }).event_id

    var steps = [
        // month, anim, x: 7 months left is beyond the 6 travel months
        [6, 0, a.x],          // 6 left: 0%
        [8, 0, ours.x + 1585], // 4 left: 34% -> point 163
        [9, 0, b.x],          // 3 left: 50% -> point 241
        [9, 90, b.x - 50],    // creeping (90 - 50) / 4 = 10 points on
        [12, 0, ours.x]       // 0 left: 100% -> the last point
    ]
    __test_simtime_set(1, 5)
    if (test530_has_marker(inv)) {
        test530_fail('invasion shown 7 months ahead')
        return
    }
    for (var i = 0; i < steps.length; i++) {
        var s = steps[i]
        __test_simtime_set(1 + ((s[0] / 12) | 0), s[0] % 12)
        var err = test530_check(s[1], inv, EMPIRE_MARKER_INVASION, false, s[2], ours.y)
        if (err) {
            test530_fail('invasion month ' + s[0] + ' anim ' + s[1] + ': ' + err)
            return
        }
    }
    __log_marker('empire_markers_invasion_ok')

    __test_simtime_set(2, 1)
    if (test530_has_marker(inv)) {
        test530_fail('invasion still shown after its month')
        return
    }
    __log_marker('empire_markers_invasion_gone_ok')
    __test_og_invasions_set(0)
}

function test530_pick(ours, event_id, kind) {
    var all = test530_markers(0)
    var m = null
    for (var i = 0; i < all.length; i++) {
        if (all[i].event_id == event_id) {
            m = all[i]
        }
    }
    var scroll = __empire_map_get_scroll()
    __empire_map_select_object({ x: m.pos.x - scroll.x + 3, y: m.pos.y - scroll.y })
    var picked = empire.selected_marker_kind
    __empire_map_clear_selected_object()
    if (picked != kind || empire.selected_marker_kind != -1) {
        test530_fail('pick: kind=' + picked + ' after clear=' + empire.selected_marker_kind)
        return false
    }
    return true
}

// The city route runs from the far end to ours, as the empire files draw them: the percent counts from ours.
function test530_troops(ours, c) {
    var a = { x: ours.x + 1200, y: ours.y + 1200 }
    var b = { x: ours.x + 1200, y: ours.y }
    if (!test530_route(c.route, 2, a, b, ours)) {
        test530_fail('troops route: points=' + __test_empire_route_path_length(c.route))
        return
    }
    __test_simtime_set(1, 0)
    test530_month = 0
    __test_kingdom_set_rating(50)
    __test_set_seth_protect_troops(0)
    __test_land_company_create(16)
    var tag = 53011
    var req = city.create_good_request({ tag_id: tag, resource: RESOURCE_TROOPS, amount: 10, months_initial: 12,
        subtype: EVENT_SUBTYPE_DISTANT_BATTLE, city_id: c.id })
    req.execute()
    var ev = __test_event_id_by_tag(tag)
    if (test530_has_marker(ev)) {
        test530_fail('troops shown before they are sent')
        return
    }
    __test_request_dispatch_by_tag(tag)
    if (__test_request_months_left(tag) != 6) {
        test530_fail('dispatch: months=' + __test_request_months_left(tag))
        return
    }

    var away = [
        // month, x, y (months left = 6 - month, down to 1)
        [0, ours.x, ours.y],              // 0% from ours -> the last point
        [1, ours.x + 405, ours.y],        // 17% from ours -> point 400
        [3, b.x, b.y],                    // 50% -> point 241
        [5, a.x, ours.y + 815]            // 84% from ours -> point 77
    ]
    for (var i = 0; i < away.length; i++) {
        test530_months_to(away[i][0])
        var err = test530_check(0, ev, EMPIRE_MARKER_TROOPS_AWAY, true, away[i][1], away[i][2])
        if (err) {
            test530_fail('away month ' + away[i][0] + ': ' + err)
            return
        }
    }
    if (!test530_pick(ours, ev, EMPIRE_MARKER_TROOPS_AWAY)) {
        return
    }
    __log_marker('empire_markers_troops_away_ok')

    test530_months_to(12)
    if (__test_request_state(tag) != REQ_TROOPS_RETURN) {
        test530_fail('deadline: state=' + __test_request_state(tag))
        return
    }
    var back = [
        // month, x, y (months left = 6 at the deadline, then one less each month)
        [12, a.x, a.y],                   // 100% from ours -> point 0
        [13, a.x, ours.y + 795]           // 83% from ours -> point 81
    ]
    for (var j = 0; j < back.length; j++) {
        test530_months_to(back[j][0])
        var err2 = test530_check(0, ev, EMPIRE_MARKER_TROOPS_RETURN, true, back[j][1], back[j][2])
        if (err2) {
            test530_fail('return month ' + back[j][0] + ': ' + err2)
            return
        }
    }
    __log_marker('empire_markers_troops_return_ok')

    test530_months_to(18)
    if (test530_has_marker(ev) || __test_request_is_active(tag)) {
        test530_fail('troops still shown when back: active=' + __test_request_is_active(tag))
        return
    }
    __log_marker('empire_markers_troops_gone_ok')
    __log_marker('empire_markers_pick_ok')
}

function run_test() {
    __log_info_native('[test:530] empire map markers')
    test_reload_city_session('data/default.map')
    var c = test530_find_city()
    if (!c) {
        test530_fail('no empire city')
        __test_signal_ready()
        return
    }
    var ours = empire.ourcity.pos || { x: 100, y: 100 }
    __log_info_native('[test:530] city=' + c.id + ' route=' + c.route + ' ours=' + ours.x + ',' + ours.y)
    test530_invasion(ours, 18)
    test530_troops(ours, c)
    __test_signal_ready()
}

function check_valid() {
    var markers = ['empire_markers_route_ok', 'empire_markers_invasion_ok', 'empire_markers_invasion_gone_ok',
        'empire_markers_troops_away_ok', 'empire_markers_troops_return_ok', 'empire_markers_troops_gone_ok',
        'empire_markers_pick_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:530] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

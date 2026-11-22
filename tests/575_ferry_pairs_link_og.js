// Issue #741: two ferry pairs placed close together link to the landing they were placed with (OG
// construction pairing), the link survives a save, a deleted partner unlinks, and cancelling the tool
// removes an unpaired first landing.
// Markers:
//   [test-marker] t575_pairs_linked
//   [test-marker] t575_cost_first_only
//   [test-marker] t575_routes_cross
//   [test-marker] t575_roundtrip_ok
//   [test-marker] t575_delete_unlinks
//   [test-marker] t575_cancel_removes_first

var __t575_ok = false

function t575_fail(msg) {
    __log_info_native('[test:575] FAIL: ' + msg)
    test_planner_exit_build_mode()
    __test_signal_ready()
}

function t575_water_rect(x0, y0, x1, y1) {
    for (var y = y0; y <= y1; y++) {
        for (var x = x0; x <= x1; x++) {
            terrain.set_water({ x: x, y: y })
        }
    }
}

function t575_place_in(x0, y0, x1, y1) {
    for (var y = y0; y <= y1; y++) {
        for (var x = x0; x <= x1; x++) {
            var bid = test_ferry_try_place(x, y)
            if (bid) {
                return bid
            }
        }
    }
    return 0
}

function t575_cross(a, b) {
    var ta = __building_tile(a)
    var tb = __building_tile(b)
    return __test_citizen_road_by_ferry(ta.x, ta.y, tb.x, tb.y)
}

function t575_partners_ok(a1, a2, b1, b2) {
    return __ferry_partner_id(a1) == a2 && __ferry_partner_id(a2) == a1
        && __ferry_partner_id(b1) == b2 && __ferry_partner_id(b2) == b1
}

function t575_partners_str(ids) {
    return ids.map(function (id) { return id + '->' + __ferry_partner_id(id) }).join(' ')
}

function run_test() {
    __log_info_native('[test:575] ferry pairs link OG')
    game_features.set('gameplay_change_ferry_remake', false)
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_FERRY, true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    t575_water_rect(cx - 2, cy - 14, cx + 1, cy + 3)
    t575_water_rect(cx - 2, cy - 2, cx + 14, cy + 3)
    __map_water_cache_river_tiles()
    __map_water_rebuild_shores()
    __test_set_scenario_river_points(cx, cy, cx, cy)
    __test_map_routing_update_water()

    if (!test_planner_enter_build_mode(BUILDING_FERRY)) {
        return t575_fail('build mode')
    }

    var t0 = city.finance.treasury
    var a1 = t575_place_in(cx - 5, cy - 6, cx - 1, cy - 6)
    __test_process_events()
    var t1 = city.finance.treasury
    var a2 = t575_place_in(cx, cy - 7, cx + 3, cy - 5)
    __test_process_events()
    var t2 = city.finance.treasury
    var b1 = t575_place_in(cx + 3, cy - 4, cx + 6, cy - 2)
    var b2 = t575_place_in(cx + 3, cy + 2, cx + 7, cy + 4)
    if (!a1 || !a2 || !b1 || !b2) {
        return t575_fail('place a1=' + a1 + ' a2=' + a2 + ' b1=' + b1 + ' b2=' + b2)
    }
    test_planner_exit_build_mode()

    if (!t575_partners_ok(a1, a2, b1, b2)) {
        return t575_fail('partners ' + t575_partners_str([a1, a2, b1, b2]))
    }
    __log_marker('t575_pairs_linked')

    if (!(t1 < t0) || t2 != t1) {
        return t575_fail('pair cost t0=' + t0 + ' t1=' + t1 + ' t2=' + t2)
    }
    __log_marker('t575_cost_first_only')

    if (!t575_cross(a1, a2) || !t575_cross(b1, b2)) {
        return t575_fail('no citizen route a=' + t575_cross(a1, a2) + ' b=' + t575_cross(b1, b2))
    }
    __log_marker('t575_routes_cross')

    if (!__test_save_memory('t575') || !__test_load_memory('t575')) {
        return t575_fail('save/load memory')
    }
    if (!t575_partners_ok(a1, a2, b1, b2) || !t575_cross(a1, a2) || !t575_cross(b1, b2)) {
        return t575_fail('after load ' + t575_partners_str([a1, a2, b1, b2]))
    }
    var diff = __test_save_roundtrip('test_575_ferry.svx')
    if (diff !== '') {
        return t575_fail('save roundtrip: ' + diff)
    }
    __log_marker('t575_roundtrip_ok')

    __test_building_release_slot(a2, 1)
    if (__ferry_partner_id(a1) != 0 || __ferry_partner_id(b1) != b2) {
        return t575_fail('delete a2: ' + t575_partners_str([a1, b1]))
    }
    __log_marker('t575_delete_unlinks')

    if (!test_planner_enter_build_mode(BUILDING_FERRY)) {
        return t575_fail('build mode 2')
    }
    var c1 = t575_place_in(cx, cy - 13, cx + 3, cy - 10)
    if (!c1) {
        return t575_fail('place c1')
    }
    test_planner_exit_build_mode()
    __test_run_ticks(2)
    var c1_tile = __building_tile(c1)
    var at = city.get_building_at(c1_tile.x, c1_tile.y)
    if (at && at.id == c1 && __building_type(c1) == BUILDING_FERRY) {
        return t575_fail('cancel left the unpaired first landing ' + c1)
    }
    __log_marker('t575_cancel_removes_first')

    __t575_ok = true
    __log_info_native('[test:575] PASS')
    __test_signal_ready()
}

function check_valid() {
    return __t575_ok
        && __test_find_inlog('[test-marker] t575_pairs_linked')
        && __test_find_inlog('[test-marker] t575_cost_first_only')
        && __test_find_inlog('[test-marker] t575_routes_cross')
        && __test_find_inlog('[test-marker] t575_roundtrip_ok')
        && __test_find_inlog('[test-marker] t575_delete_unlinks')
        && __test_find_inlog('[test-marker] t575_cancel_removes_first')
}

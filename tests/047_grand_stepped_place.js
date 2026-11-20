// Grand Stepped Pyramid Complex (252): east-only causeway, place + claim + parts.

function planner_blocked_at(type, x, y) {
    if (!test_planner_enter_build_mode(type)) {
        return false
    }
    city_planner.update(x, y)
    var blocked = city_planner.can_be_placed() != CAN_PLACE
    test_planner_exit_build_mode()
    return blocked
}

function run_test() {
    __log_info_native('[test:047] grand stepped pyramid complex place')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(500000)

    if (!__scenario_building_allowed(BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX)) {
        __scenario_building_allow(BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX, true)
    }

    var px = 40
    var py = 40

    // South water only → blocked (east-only grand).
    test_prepare_pyramid_complex_causeway(px, py, 20, 4, 3, 2)
    if (planner_blocked_at(BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX, px, py)) {
        __log_marker('grand_stepped_south_blocked_ok')
    } else {
        __log_info_native('[test:047] grand stepped should reject south-only water')
        __log_marker('grand_stepped_south_blocked_fail')
        __test_signal_ready()
        return
    }

    // East water → placeable.
    var gx = 70
    var gy = 40
    test_prepare_pyramid_complex_causeway(gx, gy, 20, 4, 3, 1)
    if (planner_blocked_at(BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX, gx, gy)) {
        __log_info_native('[test:047] grand stepped should accept east water')
        __log_marker('grand_stepped_east_blocked_fail')
        __test_signal_ready()
        return
    }
    __log_marker('grand_stepped_east_ok')

    var bid = test_building_place(BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX, gx, gy)
    if (!bid) {
        __log_info_native('[test:047] east place failed')
        __log_marker('grand_stepped_place_fail')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    __log_marker('grand_stepped_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    if (__building_type(bid) != BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX) {
        __log_info_native('[test:047] unexpected type ' + __building_type(bid))
        __log_marker('grand_stepped_type_fail')
        __test_signal_ready()
        return
    }
    __log_marker('grand_stepped_type_ok')

    if (test_pyramid_complex_causeway_claimed(bid, tile.x, tile.y, 20, 4)) {
        __log_marker('grand_stepped_causeway_claimed_ok')
    } else {
        __log_info_native('[test:047] causeway tiles not claimed')
        __log_marker('grand_stepped_causeway_claimed_fail')
    }

    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 256) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    if (parts.length >= 80) {
        __log_marker('grand_stepped_parts_ok:' + parts.length)
    } else {
        __log_marker('grand_stepped_parts_fail:' + parts.length)
    }

    var mon = city.get_monument(bid)
    if (!mon) {
        __log_info_native('[test:047] city.get_monument failed')
        __test_signal_ready()
        return
    }
    var total = mon.phases_total()
    if (total >= 36) {
        __log_marker('grand_stepped_schedule_ok:' + total)
    } else {
        __log_info_native('[test:047] phases_total=' + total + ' want >=36')
        __log_marker('grand_stepped_schedule_fail:' + total)
    }

    __test_signal_ready()
}

function check_valid() {
    var required = [
        'grand_stepped_south_blocked_ok',
        'grand_stepped_east_ok',
        'grand_stepped_placed_ok',
        'grand_stepped_type_ok',
        'grand_stepped_causeway_claimed_ok',
        'grand_stepped_parts_ok',
        'grand_stepped_schedule_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:047] missing: ' + required[i])
            return false
        }
    }
    if (__test_find_inlog('grand_stepped_south_blocked_fail')
        || __test_find_inlog('grand_stepped_east_blocked_fail')
        || __test_find_inlog('grand_stepped_place_fail')
        || __test_find_inlog('grand_stepped_type_fail')
        || __test_find_inlog('grand_stepped_causeway_claimed_fail')
        || __test_find_inlog('grand_stepped_parts_fail')
        || __test_find_inlog('grand_stepped_schedule_fail')) {
        return false
    }
    return true
}

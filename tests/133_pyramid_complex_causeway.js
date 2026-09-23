// Causeway Slice A+B edge cases: grand east-only, south OK for plain complex.
// Monuments are non_deletable — no demolish/causeway-clear check.

function allow_complexes() {
    if (!__scenario_building_allowed(BUILDING_STEPPED_PYRAMID_COMPLEX)) {
        __scenario_building_allow(BUILDING_STEPPED_PYRAMID_COMPLEX, true)
    }
    if (!__scenario_building_allowed(BUILDING_GRAND_PYRAMID_COMPLEX)) {
        __scenario_building_allow(BUILDING_GRAND_PYRAMID_COMPLEX, true)
    }
}

function planner_blocked_at(type, x, y) {
    if (!test_planner_enter_build_mode(type)) {
        return false
    }
    city_planner.update(x, y)
    var blocked = city_planner.can_be_placed() != CAN_PLACE
    test_planner_exit_build_mode()
    return blocked
}

// Match C++ k_causeway_dir / k_causeway_perp (N:+x E:+y S:-x W:-y).
function causeway_dir_vectors(dir) {
    if (dir == 0) return { sx: 0, sy: -1, px: 1, py: 0 }
    if (dir == 1) return { sx: 1, sy: 0, px: 0, py: 1 }
    if (dir == 2) return { sx: 0, sy: 1, px: -1, py: 0 }
    return { sx: -1, sy: 0, px: 0, py: -1 }
}

function count_causeway_dir(bid, px, py, dir) {
    var half = ((20 - 2) / 2) | 0
    var v = causeway_dir_vectors(dir)
    var ox
    var oy
    if (dir == 0) { ox = px + half; oy = py - 1 }
    else if (dir == 1) { ox = px + 20; oy = py + half }
    else if (dir == 2) { ox = px + half; oy = py + 20 }
    else { ox = px - 1; oy = py + half }
    var n = 0
    for (var i = 0; i < 80; i++) {
        var x0 = ox + v.sx * i
        var y0 = oy + v.sy * i
        var a = city.get_building_at(x0, y0)
        var b = city.get_building_at(x0 + v.px, y0 + v.py)
        if (!a || a.id != bid || !b || b.id != bid) {
            break
        }
        n++
    }
    return { n: n, ox: ox, oy: oy, dir: dir, sx: v.sx, sy: v.sy }
}

function run_test() {
    __log_info_native('[test:133] pyramid complex causeway edges')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(500000)
    allow_complexes()

    var px = 40
    var py = 40

    // Grand: south water only → blocked (east-only).
    test_prepare_pyramid_complex_causeway(px, py, 20, 4, 3, 2)
    if (planner_blocked_at(BUILDING_GRAND_PYRAMID_COMPLEX, px, py)) {
        __log_marker('causeway_grand_south_blocked_ok')
    } else {
        __log_info_native('[test:133] grand should reject south-only water')
        __log_marker('causeway_grand_south_blocked_fail')
        __test_signal_ready()
        return
    }

    // Plain complex: same south water → placeable.
    if (!planner_blocked_at(BUILDING_STEPPED_PYRAMID_COMPLEX, px, py)) {
        __log_marker('causeway_plain_south_ok')
    } else {
        __log_info_native('[test:133] plain complex should accept south water')
        __log_marker('causeway_plain_south_fail')
        __test_signal_ready()
        return
    }

    var bid = test_building_place(BUILDING_STEPPED_PYRAMID_COMPLEX, px, py)
    if (!bid) {
        __log_info_native('[test:133] south place failed')
        __log_marker('causeway_plain_south_place_fail')
        __test_signal_ready()
        return
    }
    var tile = __building_tile(bid)
    __log_marker('causeway_plain_south_placed_ok:' + bid)

    var dirs = [0, 1, 2, 3]
    var claimed = null
    for (var di = 0; di < dirs.length; di++) {
        var info = count_causeway_dir(bid, tile.x, tile.y, dirs[di])
        __log_info_native('[test:133] dir=' + info.dir + ' len=' + info.n + ' at ' + info.ox + ',' + info.oy)
        if (info.n > 0 && (!claimed || info.n > claimed.n)) {
            claimed = info
        }
    }
    // With only south water prepared (and east rejected for grand), expect south.
    if (claimed && claimed.dir == 2 && claimed.n > 0) {
        __log_marker('causeway_south_claimed_ok:' + claimed.n)
    } else if (claimed && claimed.n > 0) {
        __log_info_native('[test:133] claimed dir=' + claimed.dir + ' len=' + claimed.n + ' (want south)')
        __log_marker('causeway_south_claimed_fail:dir' + claimed.dir)
        __test_signal_ready()
        return
    } else {
        __log_info_native('[test:133] no causeway tiles claimed for bid=' + bid)
        __log_marker('causeway_south_claimed_fail')
        __test_signal_ready()
        return
    }

    // Grand with east water → placeable (fresh site).
    var gx = 70
    var gy = 40
    test_prepare_pyramid_complex_causeway(gx, gy, 20, 4, 3, 1)
    if (!planner_blocked_at(BUILDING_GRAND_PYRAMID_COMPLEX, gx, gy)) {
        __log_marker('causeway_grand_east_ok')
    } else {
        __log_info_native('[test:133] grand should accept east water')
        __log_marker('causeway_grand_east_fail')
    }

    __test_signal_ready()
}

function check_valid() {
    var required = [
        'causeway_grand_south_blocked_ok',
        'causeway_plain_south_ok',
        'causeway_plain_south_placed_ok',
        'causeway_south_claimed_ok',
        'causeway_grand_east_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:133] missing: ' + required[i])
            return false
        }
    }
    if (__test_find_inlog('causeway_grand_south_blocked_fail')
        || __test_find_inlog('causeway_plain_south_fail')
        || __test_find_inlog('causeway_south_claimed_fail')
        || __test_find_inlog('causeway_grand_east_fail')) {
        return false
    }
    return true
}

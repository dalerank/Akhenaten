// SB3: Ship Bridge engine (type 83) without menu — place via map_bridge_add(is_ship=true).
// Markers: test_ship_bridge_placed / test_ship_bridge_min_reject / test_ship_bridge_long_ok

var __test136_ok = false

function test136_place_ship(start) {
    if (!__map_bridge_calculate_valid(start, true)) {
        return 0
    }
    return __map_bridge_add(start, true)
}

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    // --- min_length reject: length 4 < ship min 5 (low would accept) ---
    var start = test_prepare_bridge_channel(cx, cy, 3, 4)
    if (__map_bridge_calculate_valid(start, true) || test136_place_ship(start) > 0) {
        __log_info_native('[test:136] ship min_length should reject len=4'
            + ' valid=' + __map_bridge_calculate_valid(start, true)
            + ' calc_len=' + __map_bridge_calculate_length(start, true))
        __test_signal_ready()
        return
    }
    if (!__map_bridge_calculate_valid(start, false)) {
        __log_info_native('[test:136] low bridge should still accept len=4')
        __test_signal_ready()
        return
    }
    __log_marker('test_ship_bridge_min_reject')

    // --- happy path: length 6 (â‰¥ ship min 5) ---
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    start = test_prepare_bridge_channel(cx, cy, 3, 6)
    var length = test136_place_ship(start)
    if (length < 5) {
        __log_info_native('[test:136] place failed length=' + length
            + ' valid=' + __map_bridge_calculate_valid(start, true)
            + ' calc_len=' + __map_bridge_calculate_length(start, true))
        __test_signal_ready()
        return
    }

    var part = __map_bridge_part_at(start)
    if (part < 7 || part > 15) {
        __log_info_native('[test:136] expected ship bridge_part 7..15 got ' + part)
        __test_signal_ready()
        return
    }

    if (!terrain.is(start, TERRAIN_ROAD) || !terrain.is(start, TERRAIN_WATER)) {
        __log_info_native('[test:136] missing WATER|ROAD on ship bridge tile')
        __test_signal_ready()
        return
    }

    if (!__map_routing_citizen_is_road(start)) {
        __log_info_native('[test:136] citizen routing not ROAD on ship bridge')
        __test_signal_ready()
        return
    }

    __log_marker('test_ship_bridge_placed:len=' + length + ':' + start.x + ',' + start.y)

    // --- long span: length 10 > low OG max 5, OK for ship max 40 ---
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    start = test_prepare_bridge_channel(cx, cy, 3, 10)
    if (__map_bridge_calculate_valid(start, false)) {
        __log_info_native('[test:136] low should reject len=10 (OG middle cap)')
        __test_signal_ready()
        return
    }
    length = test136_place_ship(start)
    if (length < 5) {
        __log_info_native('[test:136] ship should accept len=10 got ' + length
            + ' valid=' + __map_bridge_calculate_valid(start, true)
            + ' calc_len=' + __map_bridge_calculate_length(start, true))
        __test_signal_ready()
        return
    }
    __log_marker('test_ship_bridge_long_ok:len=' + length)

    __test136_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test136_ok) {
        return false
    }
    var required = [
        '[test-marker] test_ship_bridge_min_reject',
        '[test-marker] test_ship_bridge_placed:',
        '[test-marker] test_ship_bridge_long_ok:'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:136] missing ' + required[i])
            return false
        }
    }
    return true
}

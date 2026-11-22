// A low bridge over a river that splits the map carries citizens who route over land (immigrants:
// TERRAIN_USAGE_ANY), not only those who route over roads (#741).

var __test576_ok = false

function t576_fail(msg) {
    __log_info_native('[test:576] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_LOW_BRIDGE, true)

    var w = __scenario_map.width
    var cx = (w / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var start = test_prepare_bridge_channel(cx, cy, w, 4)

    if (__test_citizen_land_route(cx, cy - 1, cx, cy + 4)) {
        return t576_fail('the river does not split the map')
    }
    if (!__map_bridge_calculate_valid(start, false) || __map_bridge_add(start, false) < 2) {
        return t576_fail('bridge not placed')
    }
    if (!__test_citizen_land_route(cx, cy - 1, cx, cy + 4)) {
        return t576_fail('no land route over the bridge')
    }

    __log_marker('bridge_land_route_ok')
    __test576_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test576_ok && __test_find_inlog('[test-marker] bridge_land_route_ok')
}

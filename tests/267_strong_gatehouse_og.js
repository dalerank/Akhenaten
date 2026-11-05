// Strong gatehouse (BUILDING_GATEHOUSE / id 171): config cost/labor, size-2 footprint claims
// four GATEHOUSE tiles; gatehouses do not request tower sentries.

var __test267_ok = false

function test267_fail(msg) {
    __log_info_native('[test:267] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:267] strong gatehouse OG')

    if (BUILDING_GATEHOUSE != 171) {
        test267_fail('BUILDING_GATEHOUSE id expected 171 got ' + BUILDING_GATEHOUSE)
        return
    }

    var expected_cost = [60, 90, 150, 250, 300]
    for (var d = 0; d < 5; d++) {
        if (building_strong_gatehouse.cost[d] != expected_cost[d]) {
            test267_fail('cost[' + d + '] expected ' + expected_cost[d]
                + ' got ' + building_strong_gatehouse.cost[d])
            return
        }
    }
    if (building_strong_gatehouse.laborers[0] != 9 || building_strong_gatehouse.fire_risk[0] != 0) {
        test267_fail('laborers/fire mismatch')
        return
    }
    if (building_strong_gatehouse.damage_risk[0] != 2) {
        test267_fail('damage_risk[0] expected 2 got ' + building_strong_gatehouse.damage_risk[0])
        return
    }
    __log_marker('test267_og_model')

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var gate_tiles = __test_gatehouse_place_2x2(BUILDING_GATEHOUSE, cx, cy)
    if (gate_tiles != 4) {
        test267_fail('2x2 footprint must claim 4 GATEHOUSE tiles, got ' + gate_tiles)
        return
    }
    __log_marker('test267_footprint_2x2')

    __test_tower_sentry_request_clear()
    var gid = __test_building_create(BUILDING_GATEHOUSE, cx + 8, cy)
    if (!gid) {
        test267_fail('gatehouse create failed')
        return
    }
    var b = city.get_building(gid)
    if (!b || b.type != BUILDING_GATEHOUSE) {
        test267_fail('created type expected BUILDING_GATEHOUSE got ' + (b ? b.type : 'null'))
        return
    }
    __test_building_set_workers(gid, 9)
    __test_building_force_road_access(gid)
    __test_buildings_generate_figures()
    if (__test_tower_sentry_request_get() != 0) {
        test267_fail('gatehouse must not request tower sentry, got ' + __test_tower_sentry_request_get())
        return
    }
    __log_marker('test267_gate_no_sentry')

    __test267_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test267_ok
        && __test_find_inlog('[test-marker] test267_og_model')
        && __test_find_inlog('[test-marker] test267_footprint_2x2')
        && __test_find_inlog('[test-marker] test267_gate_no_sentry')
}

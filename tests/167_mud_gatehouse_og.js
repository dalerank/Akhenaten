// Mud gatehouse OG: Pharaoh_Model cost/damage by difficulty; size-2 footprint claims
// four GATEHOUSE tiles (road pair + flanking sides); gatehouses do not request tower
// sentries (towers do).

var __test167_ok = false

function test167_fail(msg) {
    __log_info_native('[test:167] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:167] mud gatehouse OG')

    var expected_cost = [50, 200, 250, 300, 375]
    var expected_damage = [3, 12, 15, 18, 22]
    for (var d = 0; d < 5; d++) {
        if (building_mud_gatehouse.cost[d] != expected_cost[d]) {
            test167_fail('cost[' + d + '] expected ' + expected_cost[d] + ' got ' + building_mud_gatehouse.cost[d])
            return
        }
        if (building_mud_gatehouse.damage_risk[d] != expected_damage[d]) {
            test167_fail('damage_risk[' + d + '] expected ' + expected_damage[d] + ' got ' + building_mud_gatehouse.damage_risk[d])
            return
        }
    }
    if (building_mud_gatehouse.laborers[0] != 3 || building_mud_gatehouse.fire_risk[0] != 0) {
        test167_fail('laborers/fire mismatch')
        return
    }
    __log_marker('test167_og_model')

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var gate_tiles = __test_mud_gatehouse_place_2x2(cx, cy)
    if (gate_tiles != 4) {
        test167_fail('2x2 footprint must claim 4 GATEHOUSE tiles, got ' + gate_tiles)
        return
    }
    __log_marker('test167_footprint_2x2')

    __test_tower_sentry_request_clear()
    var gid = __test_building_create(BUILDING_MUD_GATEHOUSE, cx + 8, cy)
    if (!gid) {
        test167_fail('gatehouse create failed')
        return
    }
    __test_building_set_workers(gid, 3)
    __test_building_force_road_access(gid)
    __test_buildings_generate_figures()
    if (__test_tower_sentry_request_get() != 0) {
        test167_fail('gatehouse must not request tower sentry, got ' + __test_tower_sentry_request_get())
        return
    }
    __log_marker('test167_gate_no_sentry')

    __test167_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test167_ok
        && __test_find_inlog('[test-marker] test167_og_model')
        && __test_find_inlog('[test-marker] test167_footprint_2x2')
        && __test_find_inlog('[test-marker] test167_gate_no_sentry')
}

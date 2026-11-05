// Strong tower (BUILDING_TOWER / id 173): config cost/labor/fire; createable; may request sentry.

var __test268_ok = false

function test268_fail(msg) {
    __log_info_native('[test:268] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:268] strong tower OG')

    if (BUILDING_TOWER != 173) {
        test268_fail('BUILDING_TOWER id expected 173 got ' + BUILDING_TOWER)
        return
    }

    var expected_cost = [50, 80, 100, 150, 300]
    for (var d = 0; d < 5; d++) {
        if (building_strong_tower.cost[d] != expected_cost[d]) {
            test268_fail('cost[' + d + '] expected ' + expected_cost[d]
                + ' got ' + building_strong_tower.cost[d])
            return
        }
    }
    if (building_strong_tower.laborers[0] != 20) {
        test268_fail('laborers expected 20 got ' + building_strong_tower.laborers[0])
        return
    }
    if (building_strong_tower.fire_risk[0] != 4) {
        test268_fail('fire_risk expected 4 got ' + building_strong_tower.fire_risk[0])
        return
    }
    if (building_strong_tower.damage_risk[0] != 4) {
        test268_fail('damage_risk[0] expected 4 got ' + building_strong_tower.damage_risk[0])
        return
    }
    if (building_strong_tower.min_houses_coverage != 50) {
        test268_fail('min_houses_coverage expected 50 got ' + building_strong_tower.min_houses_coverage)
        return
    }
    __log_marker('test268_og_model')

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var tid = __test_building_create(BUILDING_TOWER, cx, cy)
    if (!tid) {
        test268_fail('tower create failed')
        return
    }
    var b = city.get_building(tid)
    if (!b || b.type != BUILDING_TOWER) {
        test268_fail('created type expected BUILDING_TOWER got ' + (b ? b.type : 'null'))
        return
    }
    __log_marker('test268_create')

    __test_tower_sentry_request_clear()
    __test_building_set_workers(tid, 20)
    __test_building_force_road_access(tid)
    __test_buildings_generate_figures()
    // Towers may raise a sentry request when staffed; gatehouses must not (covered in 267).
    __log_marker('test268_spawned')

    __test268_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test268_ok
        && __test_find_inlog('[test-marker] test268_og_model')
        && __test_find_inlog('[test-marker] test268_create')
        && __test_find_inlog('[test-marker] test268_spawned')
}

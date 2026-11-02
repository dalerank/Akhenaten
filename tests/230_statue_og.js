// Statue OG: small statue costs from Pharaoh_Model_*.txt, the rotate key steps one 0..15 counter
// (variant = n % 4, facing = n / 4) starting at 0, and the site refuses floodplain and the map edge band.

var __test230_ok = false

function test230_fail(msg) {
    __log_info_native('[test:230] FAIL: ' + msg)
    test_planner_exit_build_mode()
    __test_signal_ready()
}

function test230_counter() {
    return city_planner.global_rotation * 4 + city_planner.building_variant
}

function run_test() {
    __log_info_native('[test:230] statue OG')
    var flags = ['gameplay_change_statue_variants', 'gameplay_change_guild_statue_service']
    for (var i = 0; i < flags.length; i++) {
        if (game_features.default(flags[i])) {
            test230_fail(flags[i] + ' must default OFF')
            return
        }
    }

    var cost = building_small_statue.cost
    var og = [3, 10, 12, 14, 18]
    for (var c = 0; c < og.length; c++) {
        if (cost[c] != og[c]) {
            test230_fail('small statue cost[' + c + '] expected ' + og[c] + ' got ' + cost[c])
            return
        }
    }
    __log_marker('test230_cost')

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    if (!__scenario_building_allowed(BUILDING_SMALL_STATUE)) {
        __scenario_building_allow(BUILDING_SMALL_STATUE, true)
    }

    var tile = test_find_buildable_tile(BUILDING_SMALL_STATUE)
    if (!tile || !test_planner_enter_build_mode(BUILDING_SMALL_STATUE)) {
        test230_fail('enter build mode failed')
        return
    }
    city_planner.update(tile.x, tile.y)
    if (test230_counter() != 0) {
        test230_fail('OG statue must start at counter 0, got ' + test230_counter())
        return
    }
    for (var r = 1; r <= 17; r++) {
        city_planner_on_rotate_building({})
        var expected = r % 16
        if (test230_counter() != expected) {
            test230_fail('after ' + r + ' rotations expected ' + expected + ' got ' + test230_counter())
            return
        }
    }
    __log_marker('test230_rotate_counter')

    city_planner.update(tile.x, tile.y)
    if (city_planner.can_be_placed() != CAN_PLACE) {
        test230_fail('clear site must be placeable')
        return
    }
    terrain.add(tile, TERRAIN_FLOODPLAIN)
    city_planner.update(tile.x, tile.y)
    var on_flood = city_planner.can_be_placed()
    terrain.remove(tile, TERRAIN_FLOODPLAIN)
    if (on_flood == CAN_PLACE) {
        test230_fail('floodplain must refuse a statue')
        return
    }
    __log_marker('test230_floodplain')

    city_planner.update(1, 1)
    if (city_planner.can_be_placed() == CAN_PLACE) {
        test230_fail('map edge band must refuse a statue')
        return
    }
    __log_marker('test230_edge')

    test_planner_exit_build_mode()
    __test230_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test230_ok
        && __test_find_inlog('[test-marker] test230_cost')
        && __test_find_inlog('[test-marker] test230_rotate_counter')
        && __test_find_inlog('[test-marker] test230_floodplain')
        && __test_find_inlog('[test-marker] test230_edge')
}

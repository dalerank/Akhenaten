var __test257_ok = false

function test257_fail(msg) {
    __log_info_native('[test:257] ' + msg)
    __test_signal_ready()
}

function test257_expect(fid, action, secondary, marker) {
    var got_action = __test_figure_get_action(fid)
    var got_secondary = __test_warship_get_secondary_action(fid)
    if (got_action != action || (secondary >= 0 && got_secondary != secondary)) {
        test257_fail(marker + ': action=' + got_action + ' secondary=' + got_secondary)
        return false
    }
    __log_marker(marker)
    return true
}

function run_test() {
    __log_info_native('[test:257] original warship action states')

    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_SHIPWRIGHT, true)

    var bid = test_shoreline_building_place(BUILDING_SHIPWRIGHT, 3)
    if (!bid) {
        return test257_fail('shipwright place failed')
    }
    __test_building_set_workers(bid, 20)

    var fid = __test_spawn_warship_on_water()
    if (!fid) {
        return test257_fail('warship create failed')
    }
    if (!test257_expect(fid, 8, 16, 'warship_waiting_ok')) {
        return
    }

    __test_warship_set_order(fid, 4)
    if (!test257_expect(fid, 10, 16, 'warship_hunting_ok')) {
        return
    }

    __test_warship_set_order(fid, 2)
    if (!test257_expect(fid, 23, 22, 'warship_patrolling_ok')) {
        return
    }

    __test_warship_set_order(fid, 3)
    if (!test257_expect(fid, 20, -1, 'warship_docked_ok')) {
        return
    }

    __test_shipyard_set_water_access_to_figure(bid, fid)
    __test_warship_force_low_hull(fid)
    var low_ship = city.get_warship(fid)
    __test_figure_action_perform(fid)
    var repair_action = __test_figure_get_action(fid)
    if (repair_action != 13 && repair_action != 15) {
        return test257_fail('auto repair action=' + repair_action + ' damage=' + low_ship.damage + ' max=' + low_ship.max_damage)
    }
    __log_marker('warship_auto_repair_ok')

    __test257_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test257_ok
        && __test_find_inlog('[test-marker] warship_waiting_ok')
        && __test_find_inlog('[test-marker] warship_hunting_ok')
        && __test_find_inlog('[test-marker] warship_patrolling_ok')
        && __test_find_inlog('[test-marker] warship_docked_ok')
        && __test_find_inlog('[test-marker] warship_auto_repair_ok')
}

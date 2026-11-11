// The ship under repair survives a save/load: the shipwright repairs the warship queued first (here the one
// with the higher figure id) and must keep repairing it after loading, instead of the first queued ship by id.
// Markers:
//   [test-marker] shipyard_repair_saveload_ok

var __test311_ok = false

function test311_fail(msg) {
    __log_info_native('[test:311] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:311] shipyard repair save/load')

    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_SHIPWRIGHT, true)

    var bid = test_shoreline_building_place(BUILDING_SHIPWRIGHT, 3)
    if (!bid) {
        return test311_fail('shipwright place failed')
    }

    __test_building_set_workers(bid, 20)
    var yard = city.get_building(bid)
    yard.store_resource(RESOURCE_TIMBER, 100)

    var dock = yard.water_access_tile(0)
    if (!dock || dock.x < 0) {
        dock = yard.tile
    }

    var low = test_figure_create(FIGURE_WARSHIP, dock.x, dock.y)
    var high = test_figure_create(FIGURE_WARSHIP, dock.x, dock.y)
    if (!low || !high || high <= low) {
        return test311_fail('warship create failed low=' + low + ' high=' + high)
    }

    __test_figure_set_damage(low, 40)
    __test_figure_set_damage(high, 40)
    if (__test_shipyard_queue_ship(bid, high) != 1 || __test_shipyard_queue_ship(bid, low) != 1) {
        return test311_fail('queue_ship failed')
    }

    __test_building_update_day(bid)
    if (__test_shipyard_repair_fid(bid) != high) {
        return test311_fail('before save repair_fid=' + __test_shipyard_repair_fid(bid) + ' want ' + high)
    }

    var save_name = 'test_311_shipyard.svx'
    if (!__game_write_savegame(save_name)) {
        return test311_fail('write failed')
    }
    var loaded = __game_load_savegame(save_name)
    __game_delete_savegame(save_name)
    if (!loaded) {
        return test311_fail('load failed')
    }

    if (__test_shipyard_is_reparing(bid) != 1 || __test_shipyard_repair_fid(bid) != high) {
        return test311_fail('after load reparing=' + __test_shipyard_is_reparing(bid)
            + ' repair_fid=' + __test_shipyard_repair_fid(bid) + ' want ' + high)
    }

    __log_marker('shipyard_repair_saveload_ok')
    __test311_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test311_ok && __test_find_inlog('[test-marker] shipyard_repair_saveload_ok')
}

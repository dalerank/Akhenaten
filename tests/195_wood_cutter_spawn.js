// Wood cutter lumberjack spawn (JS in wood_cutter.js):
// 1) Empty yard has capacity for a lumberjack.
// 2) 500 timber (10 loads of 50) has no remaining capacity.
// 3) spawn_figure handler runs without error.

var __test195_ok = false

function test195_fail(msg) {
    __log_info_native('[test:195] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:195] wood cutter lumberjack spawn')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_WOOD_CUTTERS, -1, -1)
    if (!bid) {
        test195_fail('place failed')
        return
    }

    __test_building_set_workers(bid, 8)
    var b = city.get_building(bid)
    b.has_road_access = true
    b.figure_spawn_delay = 0

    if (!wood_cutter_has_lumberjack_capacity(b)) {
        test195_fail('empty yard should have lumberjack capacity')
        return
    }
    __log_marker('test195_empty_yard_has_capacity')

    b.consume_resource(RESOURCE_TIMBER, -500)
    if (wood_cutter_has_lumberjack_capacity(b)) {
        test195_fail('500 timber should fill spawn capacity')
        return
    }
    __log_marker('test195_full_stock_no_capacity')

    b.consume_resource(RESOURCE_TIMBER, 500)
    building_wood_cutter_spawn_figure({ bid: bid })
    __log_marker('test195_spawn_figure_ran')

    __test195_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test195_ok
        && __test_find_inlog('[test-marker] test195_empty_yard_has_capacity')
        && __test_find_inlog('[test-marker] test195_full_stock_no_capacity')
        && __test_find_inlog('[test-marker] test195_spawn_figure_ran')
}

// OG construction_warning_check_paint: warn only without a working henna farm, paint or henna in the
// yards; then needs_henna plus one hint: build a henna farm, else set up a trade route, else ask the
// overseer of commerce to import (importing as needed counts as importing).

var __test388_ok = false

var NEEDS_HENNA = '#building_needs_henna'
var BUILD_FARM = '#build_henna_farm'
var TRADE_ROUTE = '#import_henna_trade_route'
var OVERSEER = '#import_henna_overseer'

function test388_fail(msg) {
    __log_info_native('[test:388] FAIL: ' + msg)
    __test_signal_ready()
}

function test388_place() {
    __test_construction_warnings_reset()
    var bid = test_building_place(BUILDING_PAINT_WORKSHOP, -1, -1)
    __test_process_events()
    return bid
}

function test388_counts() {
    return 'needs=' + __test_construction_warning_count(NEEDS_HENNA)
        + ' farm=' + __test_construction_warning_count(BUILD_FARM)
        + ' route=' + __test_construction_warning_count(TRADE_ROUTE)
        + ' overseer=' + __test_construction_warning_count(OVERSEER)
}

function test388_expect(needs, farm, route, overseer, what) {
    if (__test_construction_warning_count(NEEDS_HENNA) != needs
        || __test_construction_warning_count(BUILD_FARM) != farm
        || __test_construction_warning_count(TRADE_ROUTE) != route
        || __test_construction_warning_count(OVERSEER) != overseer) {
        test388_fail(what + ': ' + test388_counts())
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:388] paint workshop place checks')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var henna = city.resources.henna
    var could_produce = henna.can_produce

    __city_resource_set_produce(RESOURCE_HENNA, true)
    if (!test388_place()) {
        test388_fail('place with henna farms possible failed')
        return
    }
    if (!test388_expect(1, 1, 0, 0, 'henna can be produced')) {
        return
    }
    __log_marker('test388_build_farm_ok')

    __city_resource_set_produce(RESOURCE_HENNA, false)
    if (!test388_place()) {
        test388_fail('place without henna farms failed')
        return
    }
    if (!henna.can_import) {
        if (!test388_expect(1, 0, 1, 0, 'no henna seller')) {
            return
        }
    } else if (henna.trade_status != TRADE_STATUS_IMPORT && henna.trade_status != TRADE_STATUS_IMPORT_AS_NEEDED) {
        if (!test388_expect(1, 0, 0, 1, 'henna not imported')) {
            return
        }
    }
    __log_marker('test388_trade_hint_ok')

    __city_resource_set_produce(RESOURCE_HENNA, true)
    if (!__scenario_building_allowed(BUILDING_STORAGE_YARD)) {
        __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    }
    var yard = __test_building_create(BUILDING_STORAGE_YARD, -1, -1)
    if (!yard || !__test_storage_yard_add_resource(yard, RESOURCE_PAINT, 100)) {
        test388_fail('could not stock paint in a storage yard')
        return
    }
    if (!test388_place()) {
        test388_fail('place with paint in the yards failed')
        return
    }
    if (!test388_expect(0, 0, 0, 0, 'paint in the yards must suppress the warnings')) {
        return
    }
    __log_marker('test388_paint_supply_suppresses_ok')

    __city_resource_set_produce(RESOURCE_HENNA, could_produce)
    __test388_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test388_ok
        && __test_find_inlog('[test-marker] test388_build_farm_ok')
        && __test_find_inlog('[test-marker] test388_trade_hint_ok')
        && __test_find_inlog('[test-marker] test388_paint_supply_suppresses_ok')
}

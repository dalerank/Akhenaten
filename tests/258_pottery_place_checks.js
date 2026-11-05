// Pottery on_place_checks (JS in pottery.js) must match OG workshop hints:
// warn only when there is no clay industry, clay yards, or pottery yards;
// then needs_clay + build_clay_pit / trade else-if chain (not all at once).

var __test258_ok = false

var NEEDS_CLAY = '#building_needs_clay'
var BUILD_CLAY_PIT = '#build_clay_pit'
var SETUP_TRADE = '#setup_trade_route_to_import'
var OVERSEER_IMPORT = '#overseer_of_commerce_to_import'

function test258_place_and_capture() {
    __test_construction_warnings_reset()
    var bid = test_building_place(BUILDING_POTTERY_WORKSHOP, -1, -1)
    __test_process_events()
    return bid
}

function test258_trade_warn_count() {
    return __test_construction_warning_count(SETUP_TRADE)
        + __test_construction_warning_count(OVERSEER_IMPORT)
}

function run_test() {
    __log_info_native('[test:258] pottery place checks')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test258_place_and_capture()
    if (!bid) {
        __log_info_native('[test:258] place without supply failed')
        __test_signal_ready()
        return
    }

    if (__test_construction_warning_count(NEEDS_CLAY) < 1) {
        __log_info_native('[test:258] FAIL: expected ' + NEEDS_CLAY + ' without clay/pottery supply')
        __test_signal_ready()
        return
    }

    var clay = city.resources.clay
    if (clay.can_produce) {
        if (__test_construction_warning_count(BUILD_CLAY_PIT) < 1) {
            __log_info_native('[test:258] FAIL: expected ' + BUILD_CLAY_PIT + ' when clay.can_produce')
            __test_signal_ready()
            return
        }
        if (test258_trade_warn_count() != 0) {
            __log_info_native('[test:258] FAIL: trade hints must not show when clay.can_produce')
            __test_signal_ready()
            return
        }
    }
    __log_marker('test258_no_supply_warns_ok')

    if (!__scenario_building_allowed(BUILDING_STORAGE_YARD)) {
        __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    }
    var yard = __test_building_create(BUILDING_STORAGE_YARD, -1, -1)
    if (!yard || !__test_storage_yard_add_resource(yard, RESOURCE_CLAY, 100)) {
        __log_info_native('[test:258] FAIL: could not stock clay in storage yard')
        __test_signal_ready()
        return
    }

    bid = test258_place_and_capture()
    if (!bid) {
        __log_info_native('[test:258] place with clay supply failed')
        __test_signal_ready()
        return
    }

    if (__test_construction_warning_count(NEEDS_CLAY) != 0
        || __test_construction_warning_count(BUILD_CLAY_PIT) != 0
        || test258_trade_warn_count() != 0) {
        __log_info_native('[test:258] FAIL: clay in yards must suppress pottery place warns'
            + ' needs=' + __test_construction_warning_count(NEEDS_CLAY)
            + ' pit=' + __test_construction_warning_count(BUILD_CLAY_PIT)
            + ' trade=' + test258_trade_warn_count())
        __test_signal_ready()
        return
    }
    __log_marker('test258_clay_supply_suppresses_ok')

    __test258_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test258_ok
        && __test_find_inlog('[test-marker] test258_no_supply_warns_ok')
        && __test_find_inlog('[test-marker] test258_clay_supply_suppresses_ok')
}

// OG construction_warning_check_cattle: warn needs_straw only when there is no
// active grain farm and no straw in storage yards; then the grain farm / trade hint.

var __test265_ok = false

var NEEDS_STRAW = '#building_needs_straw'
var BUILD_GRAIN = '#build_grain_farm'
var SETUP_TRADE = '#setup_trade_route_to_import'
var OVERSEER_IMPORT = '#overseer_of_commerce_to_import'

function test265_fail(msg) {
    __log_info_native('[test:265] FAIL: ' + msg)
    __test_signal_ready()
}

function test265_place() {
    __test_construction_warnings_reset()
    var bid = test_building_place(BUILDING_CATTLE_RANCH, -1, -1)
    __test_process_events()
    return bid
}

function test265_hint_count() {
    return __test_construction_warning_count(BUILD_GRAIN)
        + __test_construction_warning_count(SETUP_TRADE)
        + __test_construction_warning_count(OVERSEER_IMPORT)
}

function run_test() {
    __log_info_native('[test:265] cattle ranch place checks')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    if (!test265_place()) {
        test265_fail('place without supply failed')
        return
    }
    if (__test_construction_warning_count(NEEDS_STRAW) < 1) {
        test265_fail('expected ' + NEEDS_STRAW + ' without grain/straw supply')
        return
    }
    if (test265_hint_count() > 1) {
        test265_fail('hints must be an else-if chain, got ' + test265_hint_count())
        return
    }
    if (city.resources.grain.can_produce && __test_construction_warning_count(BUILD_GRAIN) < 1) {
        test265_fail('expected ' + BUILD_GRAIN + ' when grain.can_produce')
        return
    }
    __log_marker('test265_no_supply_warns_ok')

    if (!__scenario_building_allowed(BUILDING_STORAGE_YARD)) {
        __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    }
    var yard = __test_building_create(BUILDING_STORAGE_YARD, -1, -1)
    if (!yard || !__test_storage_yard_add_resource(yard, RESOURCE_STRAW, 100)) {
        test265_fail('could not stock straw in storage yard')
        return
    }

    if (!test265_place()) {
        test265_fail('place with straw supply failed')
        return
    }
    if (__test_construction_warning_count(NEEDS_STRAW) != 0 || test265_hint_count() != 0) {
        test265_fail('straw in yards must suppress warns needs=' + __test_construction_warning_count(NEEDS_STRAW)
            + ' hints=' + test265_hint_count())
        return
    }
    __log_marker('test265_straw_supply_suppresses_ok')

    __test265_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test265_ok
        && __test_find_inlog('[test-marker] test265_no_supply_warns_ok')
        && __test_find_inlog('[test-marker] test265_straw_supply_suppresses_ok')
}

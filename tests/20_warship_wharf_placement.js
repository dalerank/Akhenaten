// Warship wharf on synthetic shoreline via test_building_place.
// Marker: [test-marker] test_building_placed:type_182:...

var __test20_bid = null

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_WARSHIP_WHARF, true)
    __test20_bid = test_shoreline_building_place(BUILDING_WARSHIP_WHARF, 3)
    if (!__test20_bid) {
        __log_info_native('[test:20] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return test_assert_building_placed(__test20_bid, BUILDING_WARSHIP_WHARF, 'test:20')
}

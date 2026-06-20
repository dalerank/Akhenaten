// Ferry landing on synthetic shoreline via test_building_place.
// Marker: [test-marker] test_building_placed:type_136:...

var __test23_bid = null

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_FERRY, true)
    __test23_bid = test_shoreline_building_place(BUILDING_FERRY, 2)
    if (!__test23_bid) {
        __log_info_native('[test:23] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return test_assert_building_placed(__test23_bid, BUILDING_FERRY, 'test:23')
}

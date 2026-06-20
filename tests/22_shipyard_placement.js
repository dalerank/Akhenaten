// Shipyard on synthetic shoreline via test_building_place.
// Marker: [test-marker] test_building_placed:type_74:...

var __test22_bid = null

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_SHIPWRIGHT, true)
    __test22_bid = test_shoreline_building_place(BUILDING_SHIPWRIGHT, 3)
    if (!__test22_bid) {
        __log_info_native('[test:22] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return test_assert_building_placed(__test22_bid, BUILDING_SHIPWRIGHT, 'test:22')
}

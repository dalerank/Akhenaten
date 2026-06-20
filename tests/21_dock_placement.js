// Dock on synthetic shoreline via test_building_place.
// Marker: [test-marker] test_building_placed:type_75:...

var __test21_bid = null

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_DOCK, true)
    __test21_bid = test_shoreline_building_place(BUILDING_DOCK, 3)
    if (!__test21_bid) {
        __log_info_native('[test:21] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return test_assert_building_placed(__test21_bid, BUILDING_DOCK, 'test:21')
}

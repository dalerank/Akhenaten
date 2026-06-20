// Transport wharf on synthetic shoreline via test_building_place.
// Marker: [test-marker] test_building_placed:type_181:...

var __test19_bid = null

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_TRANSPORT_WHARF, true)
    __test19_bid = test_shoreline_building_place(BUILDING_TRANSPORT_WHARF, 2)
    if (!__test19_bid) {
        __log_info_native('[test:19] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return test_assert_building_placed(__test19_bid, BUILDING_TRANSPORT_WHARF, 'test:19')
}

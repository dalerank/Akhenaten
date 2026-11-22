// Ferry landing on synthetic shoreline via test_building_place.
// Marker: [test-marker] test_building_placed:type_136:...

var __test176_bid = null

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_FERRY, true)
    __test176_bid = (test_ferry_pair_place() || {}).first
    if (!__test176_bid) {
        __log_info_native('[test:176] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return test_assert_building_placed(__test176_bid, BUILDING_FERRY, 'test:23')
}

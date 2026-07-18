// Places a Cattle Ranch on data/default.map via build_planner (same path as player click).
// Marker: [test-marker] test_building_placed:type_<BUILDING_CATTLE_RANCH>:...

var __test31_bid = null

function run_test() {
    __log_info_native('[test:31] placing cattle ranch via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    var bid = test_building_place(BUILDING_CATTLE_RANCH, -1, -1)
    __test31_bid = bid
    if (!bid) {
        __log_info_native('[test:31] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return test_assert_building_placed(__test31_bid, BUILDING_CATTLE_RANCH, 'test:31')
}

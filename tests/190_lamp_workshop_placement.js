// Places a Lamp Workshop on data/default.map via build_planner.
// Marker: [test-marker] test_building_placed:type_<BUILDING_LAMP_WORKSHOP>:...

var __test190_bid = null

function run_test() {
    __log_info_native('[test:190] placing lamp workshop via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    var bid = test_building_place(BUILDING_LAMP_WORKSHOP, -1, -1)
    __test190_bid = bid
    if (!bid) {
        __log_info_native('[test:190] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return test_assert_building_placed(__test190_bid, BUILDING_LAMP_WORKSHOP, 'test:190')
}

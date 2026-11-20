// Places a Paint Workshop on data/default.map via build_planner.
// Marker: [test-marker] test_building_placed:type_<BUILDING_PAINT_WORKSHOP>:...

var __test109_bid = null

function run_test() {
    __log_info_native('[test:109] placing paint workshop via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    var bid = test_building_place(BUILDING_PAINT_WORKSHOP, -1, -1)
    __test109_bid = bid
    if (!bid) {
        __log_info_native('[test:109] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return test_assert_building_placed(__test109_bid, BUILDING_PAINT_WORKSHOP, 'test:191')
}

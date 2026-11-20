// Places a Bricks Workshop on data/default.map via build_planner (same path as player click).
// Marker: [test-marker] test_building_placed:type_<BUILDING_BRICKS_WORKSHOP>:...

var __test256_bid = null

function run_test() {
    __log_info_native('[test:256] placing bricks workshop via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    var bid = test_building_place(BUILDING_BRICKS_WORKSHOP, -1, -1)
    __test256_bid = bid
    if (!bid) {
        __log_info_native('[test:256] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return test_assert_building_placed(__test256_bid, BUILDING_BRICKS_WORKSHOP, 'test:27')
}

// Places a Chariots Workshop on data/default.map via build_planner (same path as player click).
// Marker: [test-marker] test_building_placed:type_<BUILDING_CHARIOTS_WORKSHOP>:...

var __test32_bid = null

function run_test() {
    __log_info_native('[test:32] placing chariots workshop via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    var bid = test_building_place(BUILDING_CHARIOTS_WORKSHOP, -1, -1)
    __test32_bid = bid
    if (!bid) {
        __log_info_native('[test:32] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return test_assert_building_placed(__test32_bid, BUILDING_CHARIOTS_WORKSHOP, 'test:32')
}

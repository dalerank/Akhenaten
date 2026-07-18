// Places a Grain Farm (floodplain) on data/default.map via build_planner on a synthetic floodplain patch.
// Marker: [test-marker] test_building_placed:type_<BUILDING_GRAIN_FARM>:...

var __test35_bid = null

function run_test() {
    __log_info_native('[test:35] placing floodplain grain farm via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    __test35_bid = test_farm_place(BUILDING_GRAIN_FARM, TERRAIN_FLOODPLAIN)
    if (!__test35_bid) {
        __log_info_native('[test:35] test_farm_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return test_assert_building_placed(__test35_bid, BUILDING_GRAIN_FARM, 'test:35')
}

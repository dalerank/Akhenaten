// Places a Clay Pit on data/default.map near synthetic water (needs.nearby_water, radius 3).
// Footprint must stay on land — place two tiles above the water patch, not on the shoreline.
// Marker: [test-marker] test_building_placed:type_<BUILDING_CLAY_PIT>:...

var __test33_bid = null

function run_test() {
    __log_info_native('[test:33] placing clay pit via build_planner near water')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_prepare_shoreline_patch(cx, cy, 6, 2)

    // 2x2 pit at (cx-1, cy-3)/(cy-2) stays dry; water at cy is within nearby_water radius.
    __test33_bid = test_building_place(BUILDING_CLAY_PIT, cx - 1, cy - 3)
    if (!__test33_bid) {
        __log_info_native('[test:33] test_building_place failed at ' + (cx - 1) + ',' + (cy - 3))
    }
    __test_signal_ready()
}

function check_valid() {
    return test_assert_building_placed(__test33_bid, BUILDING_CLAY_PIT, 'test:33')
}

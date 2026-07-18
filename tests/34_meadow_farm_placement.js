// Places a Grain Meadow Farm on data/default.map via build_planner on a synthetic meadow patch.
// Also checks that placement is rejected on clear land before the meadow is painted.
// Marker: [test-marker] test_building_placed:type_<BUILDING_GRAIN_MEADOW_FARM>:...

var __test34_bid = null
var __test34_rejected_without_meadow = false

function run_test() {
    __log_info_native('[test:34] placing meadow grain farm via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var type = BUILDING_GRAIN_MEADOW_FARM
    var footprint = __building_static_building_size(type)
    if (footprint <= 0) {
        footprint = 3
    }
    var place_x = cx - ((footprint / 2) | 0)
    var place_y = cy - ((footprint / 2) | 0)

    // Clear land must not accept a meadow farm (needs.meadow / finalize_check).
    var rejected = test_building_place(type, place_x, place_y)
    __test34_rejected_without_meadow = !rejected
    if (rejected) {
        __log_info_native('[test:34] unexpected place on clear land bid=' + rejected)
        __test34_bid = rejected
        __test_signal_ready()
        return
    }

    __test34_bid = test_farm_place(type, TERRAIN_MEADOW)
    if (!__test34_bid) {
        __log_info_native('[test:34] test_farm_place failed at ' + place_x + ',' + place_y)
    }
    __test_signal_ready()
}

function check_valid() {
    if (!__test34_rejected_without_meadow) {
        __log_info_native('[test:34] expected rejection without meadow')
        return false
    }
    return test_assert_building_placed(__test34_bid, BUILDING_GRAIN_MEADOW_FARM, 'test:34')
}

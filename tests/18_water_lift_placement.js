// Places a Water Lift on data/default.map: 4x2 water at map center, lift on the row above.
// Marker: [test-marker] test_building_placed:type_7:...

var __test18_bid = null

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_WATER_LIFT, true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var x0 = cx - 2
    for (var dy = 0; dy < 2; dy++) {
        for (var dx = 0; dx < 4; dx++) {
            terrain.add({ x: x0 + dx, y: cy + dy }, TERRAIN_WATER)
        }
    }
    __map_water_rebuild_shores()

    __test18_bid = test_building_place(BUILDING_WATER_LIFT, cx - 1, cy - 1)
    if (!__test18_bid) {
        __log_info_native('[test:18] test_building_place failed at ' + (cx - 1) + ',' + (cy - 1))
    }
    __test_signal_ready()
}

function check_valid() {
    var bid = __test18_bid
    if (!bid) {
        __log_info_native('[test:18] no building id from run_test')
        return false
    }

    if (__building_type(bid) != BUILDING_WATER_LIFT) {
        __log_info_native('[test:18] wrong building type for id ' + bid)
        return false
    }

    var tile = __building_tile(bid)
    var at = city.get_building_at(tile.x, tile.y)
    if (!at || at.id != bid) {
        __log_info_native('[test:18] map_building_at mismatch at ' + tile.x + ',' + tile.y)
        return false
    }

    var marker = '[test-marker] test_building_placed:type_' + BUILDING_WATER_LIFT
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:18] missing marker: ' + marker)
        return false
    }

    return true
}

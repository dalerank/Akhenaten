// Places a Pottery Workshop on data/default.map via build_planner (same path as player click).
// Marker: [test-marker] test_building_placed:type_114:...

var __test13_bid = null

function run_test() {
    __log_info_native('[test:13] placing pottery workshop via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    var bid = test_building_place(BUILDING_POTTERY_WORKSHOP, -1, -1)
    __test13_bid = bid
    if (!bid) {
        __log_info_native('[test:13] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    var bid = __test13_bid
    if (!bid) {
        __log_info_native('[test:13] no building id from run_test')
        return false
    }

    if (__building_type(bid) != BUILDING_POTTERY_WORKSHOP) {
        __log_info_native('[test:13] wrong building type for id ' + bid)
        return false
    }

    var tile = __building_tile(bid)
    var at = city.get_building_at(tile.x, tile.y)
    if (!at || at.id != bid) {
        __log_info_native('[test:13] map_building_at mismatch at ' + tile.x + ',' + tile.y)
        return false
    }

    var marker = '[test-marker] test_building_placed:type_' + BUILDING_POTTERY_WORKSHOP
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:13] missing marker: ' + marker)
        return false
    }
    return true
}

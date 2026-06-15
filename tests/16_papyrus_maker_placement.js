// Places a Papyrus Maker on data/default.map via build_planner (same path as player click).
// Marker: [test-marker] test_building_placed:type_203:...

var __test16_bid = null

function run_test() {
    __log_info_native('[test:16] placing papyrus maker via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    var bid = test_building_place(BUILDING_PAPYRUS_WORKSHOP, -1, -1)
    __test16_bid = bid
    if (!bid) {
        __log_info_native('[test:16] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    var bid = __test16_bid
    if (!bid) {
        __log_info_native('[test:16] no building id from run_test')
        return false
    }

    if (__building_type(bid) != BUILDING_PAPYRUS_WORKSHOP) {
        __log_info_native('[test:16] wrong building type for id ' + bid)
        return false
    }

    var tile = __building_tile(bid)
    var at = city.get_building_at(tile.x, tile.y)
    if (!at || at.id != bid) {
        __log_info_native('[test:16] map_building_at mismatch at ' + tile.x + ',' + tile.y)
        return false
    }

    var placed_marker = '[test-marker] test_building_placed:type_' + BUILDING_PAPYRUS_WORKSHOP
    if (!__test_find_inlog(placed_marker)) {
        __log_info_native('[test:16] missing marker: ' + placed_marker)
        return false
    }

    return true
}

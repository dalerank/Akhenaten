// Places a Brewery Workshop on data/default.map via build_planner (same path as player click).
// Also exercises the RESOURCE_WATER pseudo-resource path: b.stored_resource(RESOURCE_WATER).
// Marker: [test-marker] test_building_placed:type_<BUILDING_BREWERY_WORKSHOP>:...

var __test24_bid = null

function run_test() {
    __log_info_native('[test:24] placing brewery workshop via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    var bid = test_building_place(BUILDING_BREWERY_WORKSHOP, -1, -1)
    __test24_bid = bid
    if (!bid) {
        __log_info_native('[test:24] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    var bid = __test24_bid
    if (!bid) {
        __log_info_native('[test:24] no building id from run_test')
        return false
    }

    if (__building_type(bid) != BUILDING_BREWERY_WORKSHOP) {
        __log_info_native('[test:24] wrong building type for id ' + bid)
        return false
    }

    var tile = __building_tile(bid)
    var at = city.get_building_at(tile.x, tile.y)
    if (!at || at.id != bid) {
        __log_info_native('[test:24] map_building_at mismatch at ' + tile.x + ',' + tile.y)
        return false
    }

    // Pseudo-resource water is readable via the standard resource getter and never throws.
    var water = at.stored_resource(RESOURCE_WATER)
    if (typeof water != 'number') {
        __log_info_native('[test:24] stored_resource(RESOURCE_WATER) not a number: ' + water)
        return false
    }

    var marker = '[test-marker] test_building_placed:type_' + BUILDING_BREWERY_WORKSHOP
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:24] missing marker: ' + marker)
        return false
    }
    return true
}

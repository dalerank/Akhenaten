// Places a Work Camp on data/default.map via build_planner (same path as player click).
// Marker: [test-marker] test_building_placed:work_camp:...

var __test11_bid = null

function run_test() {
    __log_info_native('[test:11] placing work camp via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    var bid = test_building_place(BUILDING_WORK_CAMP, -1, -1)
    __test11_bid = bid
    if (!bid) {
        __log_info_native('[test:11] test_building_place failed')
    }
    __test_signal_ready()
}

function check_valid() {
    var bid = __test11_bid
    if (!bid) {
        __log_info_native('[test:11] no building id from run_test')
        return false
    }

    if (__building_type(bid) != BUILDING_WORK_CAMP) {
        __log_info_native('[test:11] wrong building type for id ' + bid)
        return false
    }

    var tile = __building_tile(bid)
    var at = city.get_building_at(tile.x, tile.y)
    if (!at || at.id != bid) {
        __log_info_native('[test:11] map_building_at mismatch at ' + tile.x + ',' + tile.y)
        return false
    }

    var marker = '[test-marker] test_building_placed:work_camp'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:11] missing marker: ' + marker)
        return false
    }
    return true
}

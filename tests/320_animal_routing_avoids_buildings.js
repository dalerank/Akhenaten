// Animals and hunters route like OG can_enter_animal: over the citizen land grid, so an ordinary
// building is not walkable for them (on the noncitizen grid it is a "break through" tile for enemies).

var __test320_ok = false

function test320_fail(msg) {
    __log_info_native('[test:320] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:320] animal routing avoids buildings')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_HUNTING_LODGE, -1, -1)
    if (!bid) {
        return test320_fail('lodge place failed')
    }
    var tile = __building_tile(bid)
    __test_map_routing_update_land()

    if (!__test_animal_can_travel(tile.x + 4, tile.y, tile.x + 2, tile.y)) {
        return test320_fail('open tile next to the lodge is unreachable')
    }
    if (__test_animal_can_travel(tile.x + 4, tile.y, tile.x, tile.y)) {
        return test320_fail('lodge tile is reachable for an animal')
    }
    __log_marker('animal_routing_ok')

    __test320_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test320_ok && __test_find_inlog('[test-marker] animal_routing_ok')
}

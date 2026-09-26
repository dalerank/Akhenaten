// Bandstand update_day (JS in bandstand.js):
// Decay juggler/musician visit timers and recount num_shows.
// Venue needs a road cross (same pattern as tests/41_city_smoke_run.js).

var __test209_ok = false

function place_bandstand() {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bx = cx - 14
    var by = cy - 14
    var pattern = [[0, 1, 0], [0, 1, 0], [1, 1, 1]]
    for (var dy = 0; dy < pattern.length; dy++) {
        for (var dx = 0; dx < pattern[dy].length; dx++) {
            if (pattern[dy][dx]) {
                terrain.add({ x: bx + dx, y: by + dy }, TERRAIN_ROAD)
            }
        }
    }
    return test_building_place(BUILDING_BANDSTAND, bx, by)
}

function run_test() {
    __log_info_native('[test:209] bandstand update_day show decay')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = place_bandstand()
    if (!bid) {
        __log_info_native('[test:209] place failed')
        __test_signal_ready()
        return
    }

    var b = city.get_entertainment_building(bid)
    if (!b) {
        __log_info_native('[test:209] get_entertainment_building failed')
        __test_signal_ready()
        return
    }

    b.juggler_visited = 2
    b.musician_visited = 1
    b.num_shows = 0

    __test_building_update_day(bid)
    b = city.get_entertainment_building(bid)
    if (b.juggler_visited != 1 || b.musician_visited != 0 || b.num_shows != 2) {
        __log_info_native('[test:209] FAIL after day1'
            + ' juggler=' + b.juggler_visited
            + ' musician=' + b.musician_visited
            + ' shows=' + b.num_shows)
        __test_signal_ready()
        return
    }
    __log_marker('test209_day1_both_active')

    __test_building_update_day(bid)
    b = city.get_entertainment_building(bid)
    if (b.juggler_visited != 0 || b.musician_visited != 0 || b.num_shows != 1) {
        __log_info_native('[test:209] FAIL after day2'
            + ' juggler=' + b.juggler_visited
            + ' musician=' + b.musician_visited
            + ' shows=' + b.num_shows)
        __test_signal_ready()
        return
    }
    __log_marker('test209_day2_juggler_only')

    __test_building_update_day(bid)
    b = city.get_entertainment_building(bid)
    if (b.juggler_visited != 0 || b.musician_visited != 0 || b.num_shows != 0) {
        __log_info_native('[test:209] FAIL after day3'
            + ' juggler=' + b.juggler_visited
            + ' musician=' + b.musician_visited
            + ' shows=' + b.num_shows)
        __test_signal_ready()
        return
    }
    __log_marker('test209_day3_idle')

    __test209_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test209_ok
        && __test_find_inlog('[test-marker] test209_day1_both_active')
        && __test_find_inlog('[test-marker] test209_day2_juggler_only')
        && __test_find_inlog('[test-marker] test209_day3_idle')
}

// A temple complex placed through the planner owns its whole 7x13 site in every view orientation: the main
// building, the altar, the oracle and every decorative tile (floor, statues) belong to the complex.
// Markers:
//   [test-marker] t574_ok
//   [test-marker] t574_fail:<what>
//   [test:574] view <n> owned <count> digest <crc>

var __t574_failed = false

function t574_fail(what) {
    __log_info_native('[test-marker] t574_fail:' + what)
    __t574_failed = true
}

function t574_owned(bid, cx, cy) {
    var owned = 0
    for (var y = cy - 16; y <= cy + 16; y++) {
        for (var x = cx - 16; x <= cx + 16; x++) {
            var b = __building_at(x, y)
            if (b && __building_main_id(b) == bid) {
                owned++
            }
        }
    }
    return owned
}

function t574_run() {
    for (var view = 0; view < 4; view++) {
        if (!test_reload_city_session('data/default.map')) {
            return t574_fail('load')
        }
        __test_set_treasury(50000)
        __camera_rotate_north()
        for (var r = 0; r < view; r++) {
            __camera_rotate_right()
        }
        var tile = test_find_buildable_tile(BUILDING_TEMPLE_COMPLEX_OSIRIS)
        if (!tile) {
            return t574_fail('no_tile:' + view)
        }
        var bid = test_building_place(BUILDING_TEMPLE_COMPLEX_OSIRIS, tile.x, tile.y)
        if (!bid) {
            return t574_fail('place:' + view)
        }
        var owned = t574_owned(bid, tile.x, tile.y)
        __log_info_native('[test:574] view ' + view + ' owned ' + owned + ' digest ' + __test_state_digest())
        if (owned != 91) {
            t574_fail('owned:' + view + ':' + owned)
        }
    }
    __camera_rotate_north()
}

function run_test() {
    t574_run()
    if (!__t574_failed) {
        __log_info_native('[test-marker] t574_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t574_failed && __test_find_inlog('[test-marker] t574_ok')
}

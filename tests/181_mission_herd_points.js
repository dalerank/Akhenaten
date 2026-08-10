// #624: mission JS is the only source of herd/fishing points (map values are discarded on
// load), so a mission that omits the keys silently ends up with no huntable wildlife.
// Loads every campaign mission and asserts configured herd points actually produce animals.
// Markers:
//   [test-marker] mission_herd_points_ok

var __test181_ok = false
var __test181_last = 53

var __test181_prey = [FIGURE_OSTRICH, FIGURE_ANTELOPE, FIGURE_BIRDS]

function test181_fail(msg) {
    __log_info_native('[test:181] FAIL: ' + msg)
    __test_signal_ready()
}

function test181_count_prey() {
    var total = 0
    for (var i = 0; i < __test181_prey.length; ++i) {
        total += __test_count_figures(__test181_prey[i])
    }
    return total
}

function run_test() {
    __log_info_native('[test:181] campaign herd points')

    var with_prey = 0
    for (var id = 0; id < __test181_last; ++id) {
        __game_load_mission(id, 1)

        var points = __test_count_scenario_map_points('prey')
        if (points == 0) {
            continue
        }

        with_prey++
        var prey = test181_count_prey()
        if (prey < 1) {
            test181_fail('mission ' + id + ' has ' + points + ' prey point(s) but no prey animals')
            return
        }
    }

    if (with_prey < 20) {
        test181_fail('only ' + with_prey + ' missions carry prey points, expected 20+')
        return
    }

    __log_marker('mission_herd_points_ok')
    __test181_ok = true
    __log_info_native('[test:181] PASS missions_with_prey=' + with_prey)
    __test_signal_ready()
}

function check_valid() {
    return __test181_ok
}

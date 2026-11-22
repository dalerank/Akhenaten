// Iterating buildings of a type goes through the building type index (city/building_index). After placing, changing the
// level of, expanding and destroying buildings, running the game and a save and load, the index must give exactly
// the buildings, in the same order, that a scan over all building slots gives. Every test also checks each tick that
// no building changed type without updating the index (a [building-index] line fails it).

var __test588_ok = false

function t588_fail(msg) {
    __log_info_native('[test:588] FAIL: ' + msg)
    __test_signal_ready()
}

function t588_check(stage) {
    var diff = __test_building_index_matches_scan()
    if (diff) {
        t588_fail(stage + ': ' + diff)
        return false
    }
    return true
}

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var cx = ((__scenario_map.width / 2) | 0) - 10
    var cy = ((__scenario_map.height / 2) | 0) - 10
    var ids = []
    var cells = [[0, 0], [1, 0], [0, 1], [1, 1], [4, 0], [6, 0]]
    for (var i = 0; i < cells.length; i++) {
        var bid = __test_building_create(BUILDING_HOUSE_SPACIOUS_APARTMENT, cx + cells[i][0], cy + cells[i][1])
        if (!bid) {
            return t588_fail('house ' + i + ' not created')
        }
        __test_house_set_population(bid, 8)
        ids.push(bid)
    }
    if (!t588_check('placed')) {
        return
    }

    __test_house_change_to(ids[4], BUILDING_HOUSE_STURDY_HUT)
    __test_house_change_to(ids[5], BUILDING_HOUSE_ELEGANT_MANOR)
    if (__test_house_expand(ids[0]) != BUILDING_HOUSE_COMMON_RESIDENCE) {
        return t588_fail('2x2 expansion did not happen')
    }
    if (!t588_check('changed and expanded')) {
        return
    }

    __test_building_destroy_by_enemy(ids[4])
    __test_run_ticks(200)
    if (!t588_check('after ticks')) {
        return
    }

    __test_save_memory('t588')
    __test_load_memory('t588')
    if (!t588_check('after load')) {
        return
    }

    __log_marker('building_index_matches_scan_ok')
    __test588_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test588_ok && __test_find_inlog('[test-marker] building_index_matches_scan_ok')
}

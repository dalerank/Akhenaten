// OG figure/enemy_ships.c figure_enemy_warship_action (:936): ENEMY_WARSHIP_STAY_MONTHS = 4 months after its
// ship_leave_month the warship turns LEAVING (18) for the river exit, where it is removed (enemy_warship_leave).
// Markers:
//   [test-marker] warship_stays_ok
//   [test-marker] warship_leaves_ok
//   [test-marker] warship_gone_ok

var __test457_ok = false

function test457_fail(msg) {
    __log_info_native('[test:457] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:457] enemy warship leaves after 4 months (OG ENEMY_WARSHIP_STAY_MONTHS)')

    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    __test_make_lake(cx - 10, cy, 20, 8)
    __test_invasion_points_clear()
    var exit = { x: cx - 7, y: cy + 4 }
    __test_set_scenario_river_points(cx + 7, cy + 4, exit.x, exit.y)

    __test_simtime_set_month(10)
    var ship = __test_figure_create(FIGURE_ENEMY_HITTITE_WAR_SHIP, cx + 2, cy + 4)
    if (!ship) {
        return test457_fail('could not create the warship')
    }
    for (var m = 10; m < 13; m++) {
        __test_simtime_set_month(m % 12)
        __test_figure_action_perform(ship)
        if (__test_figure_get_action(ship) == 18) {
            return test457_fail('left in month ' + (m % 12) + ', created in month 10')
        }
    }
    __log_marker('warship_stays_ok')

    __test_simtime_set_month(2)
    __test_figure_action_perform(ship)
    var dest = __figure_get_destination_tile(ship)
    if (__test_figure_get_action(ship) != 18 || !dest || dest.x != exit.x || dest.y != exit.y) {
        return test457_fail('month 2: action=' + __test_figure_get_action(ship) + ' dest='
            + (dest ? dest.x + ',' + dest.y : 'none'))
    }
    __log_marker('warship_leaves_ok')

    __test_simtime_set_month(3)
    for (var t = 0; t < 3000 && __test_figure_is_alive(ship); t++) {
        __test_figure_action_perform(ship)
    }
    if (__test_figure_is_alive(ship) || __test_figure_is_dying(ship)) {
        return test457_fail('still on the map at ' + __test_figure_tile_x(ship) + ',' + __test_figure_tile_y(ship))
    }
    __log_marker('warship_gone_ok')

    __test457_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test457_ok
        && __test_find_inlog('[test-marker] warship_stays_ok')
        && __test_find_inlog('[test-marker] warship_leaves_ok')
        && __test_find_inlog('[test-marker] warship_gone_ok')
}

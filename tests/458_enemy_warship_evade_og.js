// OG figure/enemy_ships.c ship_action_start: a warship with 15% of its hit points or less (but above 0) is forced to
// EVADING (12) every tick; enemy_warship_evade waits WARSHIP_EVADE_TICKS (75), then heads away from the nearest player
// ship within 18 tiles (ship_escape_moves), or patrols (17) when there is none. At 0 it turns corpse.
// Markers:
//   [test-marker] warship_evade_threshold_ok
//   [test-marker] warship_evade_away_ok
//   [test-marker] warship_evade_no_enemy_ok
//   [test-marker] warship_sinks_ok

var __test458_ok = false

function test458_fail(msg) {
    __log_info_native('[test:458] FAIL: ' + msg)
    __test_signal_ready()
}

function test458_session() {
    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    __test_make_lake(cx - 12, cy, 24, 10)
    __test_invasion_points_clear()
    __test_set_scenario_river_points(cx + 9, cy + 5, cx - 9, cy + 5)
    return { cx: cx, cy: cy }
}

function run_test() {
    __log_info_native('[test:458] enemy warship evades at 15% hull (OG ship_action_start)')

    var p = test458_session()
    // Hittite warship: 250 hit points.
    var ship = __test_figure_create(FIGURE_ENEMY_HITTITE_WAR_SHIP, p.cx, p.cy + 5)
    __test_figure_set_damage(ship, 200)
    __test_figure_action_perform(ship)
    if (__test_figure_get_action(ship) == 12) {
        return test458_fail('evades at 20%')
    }
    __test_figure_set_damage(ship, 212)
    __test_figure_action_perform(ship)
    if (__test_figure_get_action(ship) != 12) {
        return test458_fail('15%: action=' + __test_figure_get_action(ship))
    }
    __log_marker('warship_evade_threshold_ok')

    var player = __test_figure_create(FIGURE_WARSHIP, p.cx - 4, p.cy + 5)
    for (var t = 0; t < 80; t++) {
        __test_figure_action_perform(ship)
        if (__test_figure_get_action(ship) != 12) {
            return test458_fail('tick ' + t + ': action=' + __test_figure_get_action(ship))
        }
    }
    var dest = __figure_get_destination_tile(ship)
    if (!player || !dest || dest.x <= p.cx) {
        return test458_fail('escape from a ship to the west goes to ' + (dest ? dest.x + ',' + dest.y : 'none'))
    }
    __log_marker('warship_evade_away_ok')

    p = test458_session()
    ship = __test_figure_create(FIGURE_ENEMY_HITTITE_WAR_SHIP, p.cx, p.cy + 5)
    __test_figure_set_damage(ship, 220)
    var patrolled = false
    for (var u = 0; u < 80 && !patrolled; u++) {
        __test_figure_action_perform(ship)
        patrolled = __test_figure_get_action(ship) == 17
    }
    if (!patrolled) {
        return test458_fail('no player ship: never patrolled, action=' + __test_figure_get_action(ship))
    }
    __log_marker('warship_evade_no_enemy_ok')

    __test_figure_set_damage(ship, 250)
    __test_figure_action_perform(ship)
    if (!__test_figure_is_dying(ship)) {
        return test458_fail('0 hit points did not sink it')
    }
    __log_marker('warship_sinks_ok')

    __test458_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test458_ok
        && __test_find_inlog('[test-marker] warship_evade_threshold_ok')
        && __test_find_inlog('[test-marker] warship_evade_away_ok')
        && __test_find_inlog('[test-marker] warship_evade_no_enemy_ok')
        && __test_find_inlog('[test-marker] warship_sinks_ok')
}

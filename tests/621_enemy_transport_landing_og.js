// OG figure/enemy_ships.c figure_enemy_transport_action: WAITING (8) -> GOING_TO_LANDING (13) across the water to
// the landing point, enemy_transport_unload creates the carried soldiers as formations on the nearest free land
// tile, then WAITING again and LEAVING (17) for the river exit, where the ship turns corpse and sinks.
// Markers:
//   [test-marker] transport_sails_ok
//   [test-marker] transport_unload_ok
//   [test-marker] transport_leaves_ok

var __test621_ok = false

function test621_fail(msg) {
    __log_info_native('[test:621] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:621] enemy transport landing (OG enemy_transport_go_to_landing)')

    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    __test_make_lake(cx - 10, cy, 20, 8)
    __test_invasion_points_clear()
    __test_invasion_sea_point_set(0, cx + 8, cy + 6)
    __test_disembark_point_add(cx - 8, cy - 1)
    // Boats route only on water with no land around it: the lake's inner tiles.
    __test_set_scenario_river_points(cx + 8, cy + 1, cx - 9, cy + 6)

    if (!__test_sea_invasion_start(ENEMY_4_HITTITE, 16)) {
        return test621_fail('sea invasion did not start')
    }
    var ship = parseInt('' + __test_enemy_transports())
    var x0 = __test_figure_tile_x(ship)
    var y0 = __test_figure_tile_y(ship)

    var sailed = false
    for (var i = 0; i < 4000 && __test_enemy_transport_has_troops(ship); i++) {
        __test_figure_action_perform(ship)
        if (__test_figure_get_action(ship) == 13) {
            sailed = true
        }
    }
    var x = __test_figure_tile_x(ship)
    var y = __test_figure_tile_y(ship)
    if (!sailed || __test_enemy_transport_has_troops(ship) || Math.abs(x - x0) + Math.abs(y - y0) < 8
        || Math.abs(x - (cx - 8)) > 3 || Math.abs(y - (cy - 1)) > 3) {
        return test621_fail('voyage: sailed=' + sailed + ' troops=' + __test_enemy_transport_has_troops(ship)
            + ' from ' + x0 + ',' + y0 + ' to ' + x + ',' + y)
    }
    __log_marker('transport_sails_ok')

    var soldiers = __test_count_enemy_figures()
    var wait = __test_figure_get_wait_ticks(ship)
    if (soldiers != 16 || __test_figure_get_action(ship) != 8 || wait <= 0) {
        return test621_fail('unload: soldiers=' + soldiers + ' action=' + __test_figure_get_action(ship) + ' wait=' + wait)
    }
    __log_marker('transport_unload_ok')

    var left = false
    for (var j = 0; j < 6000 && __test_figure_is_alive(ship) && !__test_figure_is_dying(ship); j++) {
        __test_figure_action_perform(ship)
        if (__test_figure_get_action(ship) == 17) {
            left = true
        }
    }
    x = __test_figure_tile_x(ship)
    y = __test_figure_tile_y(ship)
    // The engine's boat movement may report arrival one tile past a westward destination.
    if (!left || __test_figure_is_alive(ship) && !__test_figure_is_dying(ship) || Math.abs(x - (cx - 9)) > 1
        || Math.abs(y - (cy + 6)) > 1) {
        return test621_fail('leaving: left=' + left + ' alive=' + __test_figure_is_alive(ship) + ' dying='
            + __test_figure_is_dying(ship) + ' at ' + x + ',' + y)
    }
    __log_marker('transport_leaves_ok')

    __test621_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test621_ok
        && __test_find_inlog('[test-marker] transport_sails_ok')
        && __test_find_inlog('[test-marker] transport_unload_ok')
        && __test_find_inlog('[test-marker] transport_leaves_ok')
}

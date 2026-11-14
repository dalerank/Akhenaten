// OG ships_player.c figure_warship_find_enemy_at: a loaded enemy transport scores 25, above an enemy warship (15);
// a ram that empties its hit points turns it corpse and the soldiers it carries are lost with it (they only exist
// as a count until enemy_transport_unload). OG enemy_ships.c ship_action_start: at 15% hull or less it evades (10).
// Markers:
//   [test-marker] transport_warship_target_ok
//   [test-marker] transport_sunk_ok
//   [test-marker] transport_evades_ok

var __test622_ok = false

function test622_fail(msg) {
    __log_info_native('[test:622] FAIL: ' + msg)
    __test_signal_ready()
}

function test622_session() {
    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    __test_make_lake(cx - 10, cy, 20, 8)
    __test_invasion_points_clear()
    __test_invasion_sea_point_set(0, cx + 8, cy + 6)
    __test_disembark_point_add(cx - 8, cy - 1)
    if (!__test_sea_invasion_start(ENEMY_4_HITTITE, 16)) {
        return 0
    }
    return parseInt('' + __test_enemy_transports())
}

function run_test() {
    __log_info_native('[test:622] enemy transport sunk by a player warship')

    var ship = test622_session()
    if (!ship) {
        return test622_fail('sea invasion did not start')
    }
    var warship = __test_figure_create(FIGURE_WARSHIP, __test_figure_tile_x(ship), __test_figure_tile_y(ship))
    var target = __test_warship_find_enemy(warship, 30)
    if (!warship || target != ship) {
        return test622_fail('warship ' + warship + ' targets ' + target + ', want loaded transport ' + ship)
    }
    __log_marker('transport_warship_target_ok')

    __test_figure_set_damage(ship, 99)
    for (var i = 0; i < 50 && __test_figure_is_alive(ship) && !__test_figure_is_dying(ship); i++) {
        __test_warship_ram(warship)
    }
    if (!__test_figure_is_dying(ship)) {
        return test622_fail('ram did not sink the transport: damage=' + __test_figure_get_damage(ship))
    }
    for (var j = 0; j < 300 && (__test_figure_is_alive(ship) || __test_figure_is_dying(ship)); j++) {
        __test_figure_action_perform_dying(ship)
    }
    if (__test_figure_is_alive(ship) || __test_figure_is_dying(ship) || __test_count_enemy_figures() != 0) {
        return test622_fail('after sinking: alive=' + __test_figure_is_alive(ship) + ' soldiers='
            + __test_count_enemy_figures())
    }
    __log_marker('transport_sunk_ok')

    ship = test622_session()
    // Hittite transport: 100 hit points, 10 left = 10%.
    __test_figure_set_damage(ship, 90)
    __test_figure_action_perform(ship)
    if (__test_figure_get_action(ship) != 10 || !__test_enemy_transport_has_troops(ship)) {
        return test622_fail('damaged transport action=' + __test_figure_get_action(ship))
    }
    __log_marker('transport_evades_ok')

    __test622_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test622_ok
        && __test_find_inlog('[test-marker] transport_warship_target_ok')
        && __test_find_inlog('[test-marker] transport_sunk_ok')
        && __test_find_inlog('[test-marker] transport_evades_ok')
}

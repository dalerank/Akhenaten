// An enemy transport saved mid-voyage (GOING_TO_LANDING, soldiers still a count on board) loads with its tile,
// action, soldier count, landing point and invasion sequence, and still lands its soldiers afterwards.
// Markers:
//   [test-marker] transport_saveload_state_ok
//   [test-marker] transport_saveload_lands_ok

var __test623_ok = false

function test623_fail(msg) {
    __log_info_native('[test:623] FAIL: ' + msg)
    __test_signal_ready()
}

function test623_state(id) {
    return [__test_figure_tile_x(id), __test_figure_tile_y(id), __test_figure_get_action(id),
        __test_enemy_transport_soldiers(id), __test_enemy_transport_has_troops(id),
        __test_enemy_transport_landing_x(id), __test_enemy_transport_landing_y(id),
        __test_enemy_transport_invasion_seq(id)].join(',')
}

function run_test() {
    __log_info_native('[test:623] enemy transport save round-trip mid-voyage')

    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    __test_make_lake(cx - 10, cy, 20, 8)
    __test_invasion_points_clear()
    __test_invasion_sea_point_set(0, cx + 8, cy + 6)
    __test_disembark_point_add(cx - 8, cy - 1)
    if (!__test_sea_invasion_start(ENEMY_4_HITTITE, 12)) {
        return test623_fail('sea invasion did not start')
    }
    var ship = parseInt('' + __test_enemy_transports())
    for (var i = 0; i < 80; i++) {
        __test_figure_action_perform(ship)
    }
    var before = test623_state(ship)
    if (__test_figure_get_action(ship) != 13) {
        return test623_fail('not under way before saving: ' + before)
    }

    var save_name = 'test_623_enemy_transport.svx'
    if (!__game_write_savegame(save_name)) {
        return test623_fail('write_savegame failed')
    }
    if (!__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        return test623_fail('load_savegame failed')
    }
    __game_delete_savegame(save_name)

    var after = test623_state(ship)
    if (after != before) {
        return test623_fail('state changed: before=' + before + ' after=' + after)
    }
    __log_marker('transport_saveload_state_ok')

    for (var j = 0; j < 4000 && __test_enemy_transport_has_troops(ship); j++) {
        __test_figure_action_perform(ship)
    }
    if (__test_enemy_transport_has_troops(ship) || __test_count_enemy_figures() != 12) {
        return test623_fail('after load: troops=' + __test_enemy_transport_has_troops(ship) + ' soldiers='
            + __test_count_enemy_figures())
    }
    __log_marker('transport_saveload_lands_ok')

    __test623_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test623_ok
        && __test_find_inlog('[test-marker] transport_saveload_state_ok')
        && __test_find_inlog('[test-marker] transport_saveload_lands_ok')
}

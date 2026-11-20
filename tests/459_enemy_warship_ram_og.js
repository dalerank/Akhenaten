// OG figure/enemy_ships.c enemy_warship_ram: a RAMMING (9) warship hits a player ship on its own tile or the one
// ahead for its fast (20% of attack, fewer than ship_steps straight steps) or slow (attack) ram damage, less 20 for a
// docked warship, divided by figure_ship_direction_table[target heading][own heading]; it then turns ATTACKING (10).
// The rammer takes no damage itself.
// Markers:
//   [test-marker] warship_ram_fast_ok
//   [test-marker] warship_ram_docked_ok

var __test459_ok = false

function test459_fail(msg) {
    __log_info_native('[test:459] FAIL: ' + msg)
    __test_signal_ready()
}

// Hittite warship (attack 100, ship_steps 3) heading east (2) onto a player warship on its own tile.
function test459_setup(player_action) {
    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    __test_make_lake(cx - 12, cy, 24, 10)
    __test_invasion_points_clear()
    __test_set_scenario_river_points(cx + 9, cy + 5, cx - 9, cy + 5)
    var ship = __test_figure_create(FIGURE_ENEMY_HITTITE_WAR_SHIP, cx, cy + 5)
    var player = __test_figure_create(FIGURE_WARSHIP, cx, cy + 5)
    __test_figure_set_direction(player, 0)
    if (player_action) {
        __test_figure_set_action(player, player_action)
    }
    __test_figure_set_direction(ship, 2)
    __test_figure_set_destination(ship, cx + 9, cy + 5)
    __test_figure_set_action(ship, 9)
    return { ship: ship, player: player }
}

function run_test() {
    __log_info_native('[test:459] enemy warship ram (OG enemy_warship_ram)')

    var s = test459_setup(0)
    __test_figure_action_perform(s.ship)
    // figure_ship_direction_table[0 * 8 + 2] = 1: (100 * 20%) / 1.
    if (__test_figure_get_damage(s.player) != 20 || __test_figure_get_action(s.ship) != 10
        || __test_figure_get_damage(s.ship) != 0) {
        return test459_fail('fast ram: player damage=' + __test_figure_get_damage(s.player) + ' action='
            + __test_figure_get_action(s.ship) + ' own damage=' + __test_figure_get_damage(s.ship))
    }
    __log_marker('warship_ram_fast_ok')

    // Docked player warship (action 20): (20 - 20) / 1 = 0.
    s = test459_setup(20)
    __test_figure_action_perform(s.ship)
    if (__test_figure_get_action(s.ship) != 10 || __test_figure_get_damage(s.player) != 0) {
        return test459_fail('docked: action=' + __test_figure_get_action(s.ship) + ' damage='
            + __test_figure_get_damage(s.player))
    }
    __log_marker('warship_ram_docked_ok')

    __test459_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test459_ok
        && __test_find_inlog('[test-marker] warship_ram_fast_ok')
        && __test_find_inlog('[test-marker] warship_ram_docked_ok')
}

// FIGURE_ASP idle cycle: OG figure_asp_action SPAWNED / CHOOSE / IDLE / REST (asp_walk_near) / WALK.
// Markers:
//   [test-marker] asp_spawned_ok
//   [test-marker] asp_choose_ok
//   [test-marker] asp_idle_ok
//   [test-marker] asp_rest_walk_near_ok
//   [test-marker] asp_walk_arrive_ok

var __test472_ok = false

// OG formation layout 9 (herd_roaming_offsets).
var test472_roaming_offsets = [
    [0, 0], [2, 1], [-1, -1], [1, 1], [1, 0], [-1, 1], [3, 1], [-2, -1],
    [0, 2], [-4, 0], [-1, 3], [0, 3], [1, 4], [4, 0], [2, 3], [-3, 2]
]

function test472_fail(msg) {
    __log_info_native('[test:472] FAIL: ' + msg)
    __test_signal_ready()
}

function test472_draws(n) {
    __test_random_set_state(0x2468ace, 0x1357bdf)
    var out = []
    for (var i = 0; i < n; i++) {
        __test_random_generate_next()
        out.push(__test_random_1_15bit())
    }
    __test_random_set_state(0x2468ace, 0x1357bdf)
    return out
}

function run_test() {
    __log_info_native('[test:472] asp OG idle cycle')
    test_reload_city_session('data/default.map')
    city.remove_animals()

    // Map centre: asp_walk_near skips spots that are blocked, taken or unreachable, and the first
    // accessible herd tile sits on the map edge.
    var home = { x: (__scenario_map.width / 2) | 0, y: (__scenario_map.height / 2) | 0 }
    if (terrain.is(home, TERRAIN_WATER)) {
        return test472_fail('map centre is water')
    }
    var herd = __test_create_herd(home.x, home.y, FIGURE_ASP, 1)
    var fid = herd ? __test_formation_figure(herd, 0) : 0
    if (!fid) {
        return test472_fail('herd create failed')
    }

    // SPAWNED (24): invisible while waiting, CHOOSE (8) when the wait runs out.
    __test_figure_set_action(fid, 24)
    __test_figure_set_wait_ticks(fid, 2)
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 24 || __test_figure_is_visible(fid) != 0) {
        return test472_fail('spawned want 24 invisible, got ' + __figure_get_action_state(fid))
    }
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 8) {
        return test472_fail('spawned want CHOOSE 8, got ' + __figure_get_action_state(fid))
    }
    __log_marker('asp_spawned_ok')

    // CHOOSE: draw & 1 -> REST (18) / IDLE (19); wait = draw % 100 + 50.
    var r = test472_draws(2)
    __test_figure_action_perform(fid)
    var want_action = (r[0] & 1) ? 18 : 19
    var want_wait = (r[1] % 100) + 50
    if (__figure_get_action_state(fid) != want_action || __test_figure_get_wait_ticks(fid) != want_wait) {
        return test472_fail('choose want ' + want_action + '/' + want_wait + ', got ' + __figure_get_action_state(fid)
            + '/' + __test_figure_get_wait_ticks(fid))
    }
    __log_marker('asp_choose_ok')

    // IDLE (19): CHOOSE when the wait runs out.
    __test_figure_set_action(fid, 19)
    __test_figure_set_wait_ticks(fid, 2)
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 19) {
        return test472_fail('idle left early: ' + __figure_get_action_state(fid))
    }
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 8) {
        return test472_fail('idle want CHOOSE 8, got ' + __figure_get_action_state(fid))
    }
    __log_marker('asp_idle_ok')

    // REST (18): asp_walk_near picks herd_roaming_offsets[draw % 16] around the herd destination -> WALK (9).
    var center = __test_formation_destination(herd)
    var cx = (center >> 16) & 0xffff
    var cy = center & 0xffff
    __test_figure_set_action(fid, 18)
    __test_figure_set_wait_ticks(fid, 1)
    r = test472_draws(1)
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 9) {
        return test472_fail('rest want WALK 9, got ' + __figure_get_action_state(fid))
    }
    var dest = __figure_get_destination_tile(fid)
    var dir = r[0] % 16
    var off = test472_roaming_offsets[dir]
    if (dest.x != cx + off[0] || dest.y != cy + off[1]) {
        return test472_fail('walk_near want offset #' + dir + ' ' + off + ' from ' + cx + ',' + cy
            + ', got ' + dest.x + ',' + dest.y)
    }
    __log_marker('asp_rest_walk_near_ok')

    // WALK arrival: draw & 1 -> REST / IDLE, wait = draw % 100 (no base ticks).
    var arrived = false
    for (var t = 0; t < 400 && !arrived; t++) {
        __test_figure_action_perform(fid)
        var a = __figure_get_action_state(fid)
        if (a == 18 || a == 19) {
            arrived = true
        } else if (a != 9) {
            return test472_fail('walk left to ' + a)
        }
    }
    if (!arrived) {
        return test472_fail('walk never arrived')
    }
    if (__test_figure_get_wait_ticks(fid) >= 100) {
        return test472_fail('arrival wait want < 100 (no rest base), got ' + __test_figure_get_wait_ticks(fid))
    }
    __log_marker('asp_walk_arrive_ok')

    __test472_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test472_ok) {
        return false
    }
    var markers = ['asp_spawned_ok', 'asp_choose_ok', 'asp_idle_ok', 'asp_rest_walk_near_ok', 'asp_walk_arrive_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:472] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.remove_animals()
}

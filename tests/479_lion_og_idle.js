// FIGURE_LION idle cycle: OG wild_predator_action(WILD_LION) SPAWNED / CHOOSE / IDLE / REST (wild_walk_near_herd) /
// WALK with the wild_predators lion row (rest_base 150, rest_range 200, also on arrival).
// Markers:
//   [test-marker] lion_spawned_ok
//   [test-marker] lion_choose_ok
//   [test-marker] lion_idle_ok
//   [test-marker] lion_rest_walk_near_ok
//   [test-marker] lion_blocked_terrain_ok
//   [test-marker] lion_walk_arrive_ok
//   [test-marker] lion_anims_ok

var __test479_ok = false

// OG formation layout 9 (herd_roaming_offsets).
var test479_roaming_offsets = [
    [0, 0], [2, 1], [-1, -1], [1, 1], [1, 0], [-1, 1], [3, 1], [-2, -1],
    [0, 2], [-4, 0], [-1, 3], [0, 3], [1, 4], [4, 0], [2, 3], [-3, 2]
]

function test479_fail(msg) {
    __log_info_native('[test:479] FAIL: ' + msg)
    __test_signal_ready()
}

function test479_draws(n) {
    __test_random_set_state(0x2468ace, 0x1357bdf)
    var out = []
    for (var i = 0; i < n; i++) {
        __test_random_generate_next()
        out.push(__test_random_1_15bit())
    }
    __test_random_set_state(0x2468ace, 0x1357bdf)
    return out
}

function test479_anim(fid, action) {
    __test_figure_set_action(fid, action)
    __test_figure_update_animation(fid)
    return __figure_get_anim_key(fid)
}

function run_test() {
    __log_info_native('[test:479] lion OG idle cycle')
    test_reload_city_session('data/default.map')
    city.remove_animals()

    var home = { x: (__scenario_map.width / 2) | 0, y: (__scenario_map.height / 2) | 0 }
    if (terrain.is(home, TERRAIN_WATER)) {
        return test479_fail('map centre is water')
    }
    var herd = __test_create_herd(home.x, home.y, FIGURE_LION, 1)
    var fid = herd ? __test_formation_figure(herd, 0) : 0
    if (!fid) {
        return test479_fail('herd create failed')
    }

    // SPAWNED (24): invisible while waiting, CHOOSE (8) when the wait runs out.
    __test_figure_set_action(fid, 24)
    __test_figure_set_wait_ticks(fid, 2)
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 24 || __test_figure_is_visible(fid) != 0) {
        return test479_fail('spawned want 24 invisible, got ' + __figure_get_action_state(fid))
    }
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 8) {
        return test479_fail('spawned want CHOOSE 8, got ' + __figure_get_action_state(fid))
    }
    __log_marker('lion_spawned_ok')

    // CHOOSE: draw & 1 -> REST (18) / IDLE (19); wait = draw % 200 + 150.
    var r = test479_draws(2)
    __test_figure_action_perform(fid)
    var want_action = (r[0] & 1) ? 18 : 19
    var want_wait = (r[1] % 200) + 150
    if (__figure_get_action_state(fid) != want_action || __test_figure_get_wait_ticks(fid) != want_wait) {
        return test479_fail('choose want ' + want_action + '/' + want_wait + ', got ' + __figure_get_action_state(fid)
            + '/' + __test_figure_get_wait_ticks(fid))
    }
    __log_marker('lion_choose_ok')

    // IDLE (19): CHOOSE when the wait runs out.
    __test_figure_set_action(fid, 19)
    __test_figure_set_wait_ticks(fid, 2)
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 19) {
        return test479_fail('idle left early: ' + __figure_get_action_state(fid))
    }
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 8) {
        return test479_fail('idle want CHOOSE 8, got ' + __figure_get_action_state(fid))
    }
    __log_marker('lion_idle_ok')

    // REST (18): herd_roaming_offsets[draw & 15] around the herd destination -> WALK (9).
    var center = __test_formation_destination(herd)
    var cx = (center >> 16) & 0xffff
    var cy = center & 0xffff
    __test_figure_set_action(fid, 18)
    __test_figure_set_wait_ticks(fid, 1)
    r = test479_draws(1)
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 9) {
        return test479_fail('rest want WALK 9, got ' + __figure_get_action_state(fid))
    }
    var dest = __figure_get_destination_tile(fid)
    var dir = r[0] & 15
    var off = test479_roaming_offsets[dir]
    if (dest.x != cx + off[0] || dest.y != cy + off[1]) {
        return test479_fail('walk_near want offset #' + dir + ' ' + off + ' from ' + cx + ',' + cy
            + ', got ' + dest.x + ',' + dest.y)
    }
    __log_marker('lion_rest_walk_near_ok')

    // ANIMAL_TERRAIN_BLOCKED (garden) on the drawn spot: animal_find_free_neighbour_direction takes the next one.
    var blocked = { x: cx + off[0], y: cy + off[1] }
    var next = test479_roaming_offsets[(dir + 1) & 15]
    terrain.add(blocked, TERRAIN_GARDEN)
    __test_figure_set_action(fid, 18)
    __test_figure_set_wait_ticks(fid, 1)
    test479_draws(1)
    __test_figure_action_perform(fid)
    terrain.remove(blocked, TERRAIN_GARDEN)
    dest = __figure_get_destination_tile(fid)
    if (__figure_get_action_state(fid) != 9 || dest.x != cx + next[0] || dest.y != cy + next[1]) {
        return test479_fail('blocked spot want offset #' + ((dir + 1) & 15) + ', got ' + dest.x + ',' + dest.y
            + ' action ' + __figure_get_action_state(fid))
    }
    __log_marker('lion_blocked_terrain_ok')

    // WALK arrival: draw & 1 -> REST / IDLE, wait = draw % 200 + 150.
    var arrived = false
    for (var t = 0; t < 400 && !arrived; t++) {
        __test_figure_action_perform(fid)
        var a = __figure_get_action_state(fid)
        if (a == 18 || a == 19) {
            arrived = true
        } else if (a != 9) {
            return test479_fail('walk left to ' + a)
        }
    }
    if (!arrived) {
        return test479_fail('walk never arrived')
    }
    var arrival_wait = __test_figure_get_wait_ticks(fid)
    if (arrival_wait < 150 || arrival_wait >= 350) {
        return test479_fail('arrival wait want 150..349, got ' + arrival_wait)
    }
    __log_marker('lion_walk_arrive_ok')

    // OG wild_image WILD_LION: CHOOSE first walk frame, WALK / RETURN walk, REST rest, IDLE / LOOK idle.
    var anims = [[8, 'choose'], [9, 'walk'], [23, 'walk'], [18, 'rest'], [19, 'idle'], [20, 'idle']]
    for (var i = 0; i < anims.length; i++) {
        var key = test479_anim(fid, anims[i][0])
        if (key != anims[i][1]) {
            return test479_fail('action ' + anims[i][0] + ' anim want ' + anims[i][1] + ', got ' + key)
        }
    }
    __log_marker('lion_anims_ok')

    __test479_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test479_ok) {
        return false
    }
    var markers = ['lion_spawned_ok', 'lion_choose_ok', 'lion_idle_ok', 'lion_rest_walk_near_ok', 'lion_blocked_terrain_ok', 'lion_walk_arrive_ok',
        'lion_anims_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:479] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.remove_animals()
}

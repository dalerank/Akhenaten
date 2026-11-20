// FIGURE_ASP hunt and bite: OG predator_find_prey_nearby (hunt_delay 30, hunt_radius 6 rings,
// chase wait radius * 18) and figure_combat_attack_figure_at (predator category bites citizens).
// Markers:
//   [test-marker] asp_hunt_delay_ok
//   [test-marker] asp_hunt_radius_ok
//   [test-marker] asp_hunt_skips_boats_ok
//   [test-marker] asp_bite_ok

var __test473_ok = false

function test473_fail(msg) {
    __log_info_native('[test:473] FAIL: ' + msg)
    __test_signal_ready()
}

var test473_spawned = []

// Kill instead of poof: a poofed figure stays on the tile grid until its own action runs, a corpse is
// never prey (predator_prey_on_tile_at skips FIGURE_ACTION_CORPSE).
function test473_clear() {
    city.remove_animals()
    for (var i = 0; i < test473_spawned.length; i++) {
        __test_figure_kill(test473_spawned[i])
    }
    test473_spawned = []
}

function test473_create(type, x, y) {
    var fid = test_figure_create(type, x, y)
    if (fid) {
        test473_spawned.push(fid)
    }
    return fid
}

// LOOK_FOR_PREY (20) for `ticks` ticks; returns the action after the last one.
function test473_look(asp, ticks) {
    __test_figure_set_action(asp, 20)
    for (var i = 0; i < ticks; i++) {
        __test_figure_action_perform(asp)
        if (__figure_get_action_state(asp) != 20) {
            return { tick: i + 1, action: __figure_get_action_state(asp) }
        }
    }
    return { tick: ticks, action: __figure_get_action_state(asp) }
}

function run_test() {
    __log_info_native('[test:473] asp OG hunt and bite')
    test_reload_city_session('data/default.map')
    test473_clear()

    var packed = __test_find_accessible_herd_tile(FIGURE_ASP)
    if (packed < 0) {
        return test473_fail('no accessible asp herd tile')
    }
    var x = (packed >> 16) & 0xffff
    var y = packed & 0xffff

    // A citizen 3 tiles away: no search before the 30th tick, then CHASE (21) with wait 6 * 18.
    var asp = test_figure_create(FIGURE_ASP, x, y)
    var prey = test473_create(FIGURE_IMMIGRANT, x + 3, y)
    if (!asp || !prey) {
        return test473_fail('spawn failed')
    }
    var res = test473_look(asp, 40)
    if (res.action != 21 || res.tick != 30) {
        return test473_fail('hunt want CHASE 21 on tick 30, got ' + res.action + ' on tick ' + res.tick)
    }
    if (__figure_get_target_figure_id(asp) != prey) {
        return test473_fail('chase target want ' + prey + ', got ' + __figure_get_target_figure_id(asp))
    }
    if (__test_figure_get_wait_ticks(asp) != 108) {
        return test473_fail('chase wait want 108, got ' + __test_figure_get_wait_ticks(asp))
    }
    __log_marker('asp_hunt_delay_ok')

    // Beyond 6 rings the search finds nothing.
    test473_clear()
    asp = test_figure_create(FIGURE_ASP, x, y)
    prey = test473_create(FIGURE_IMMIGRANT, x + 7, y)
    res = test473_look(asp, 61)
    if (res.action != 20) {
        return test473_fail('prey 7 tiles away want no chase, got ' + res.action)
    }
    __log_marker('asp_hunt_radius_ok')

    // Boats are never prey (figure_is_boat).
    test473_clear()
    asp = test_figure_create(FIGURE_ASP, x, y)
    var boat = test473_create(FIGURE_FISHING_BOAT, x + 1, y)
    if (boat) {
        res = test473_look(asp, 31)
        if (res.action != 20) {
            return test473_fail('boat want no chase, got ' + res.action)
        }
    }
    __log_marker('asp_hunt_skips_boats_ok')

    // Bite: the asp walks onto the citizen's tile and starts melee (OG category 7 attacks category 1).
    test473_clear()
    asp = test_figure_create(FIGURE_ASP, x, y)
    prey = test473_create(FIGURE_IMMIGRANT, x, y)
    __test_figure_set_action(asp, 18)
    if (__test_figure_combat_attack_at(asp, x, y) != 1) {
        return test473_fail('asp want in_attack against a citizen')
    }
    if (__test_figure_get_opponent_id(asp) != prey) {
        return test473_fail('opponent want ' + prey + ', got ' + __test_figure_get_opponent_id(asp))
    }
    var dmg0 = __test_figure_get_damage(prey)
    for (var j = 0; j < 30 && __test_figure_is_alive(prey); j++) {
        __test_figure_action_perform(asp)
    }
    if (__test_figure_is_alive(prey) && __test_figure_get_damage(prey) < dmg0 + 5) {
        return test473_fail('bite want +5 damage (attack 5), got ' + (__test_figure_get_damage(prey) - dmg0))
    }
    __log_marker('asp_bite_ok')

    __test473_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test473_ok) {
        return false
    }
    var markers = ['asp_hunt_delay_ok', 'asp_hunt_radius_ok', 'asp_hunt_skips_boats_ok', 'asp_bite_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:473] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    test473_clear()
}

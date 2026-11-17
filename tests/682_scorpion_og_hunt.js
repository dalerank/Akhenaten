// FIGURE_SCORPION hunt and bite: OG predator_find_prey_nearby with the scorpion climate record (hunt_delay 20,
// hunt_radius 6 rings, chase wait radius * 18), no hunger, and melee at OG attack 4.
// Markers:
//   [test-marker] scorpion_hunt_delay_ok
//   [test-marker] scorpion_hunt_radius_ok
//   [test-marker] scorpion_hunt_skips_boats_ok
//   [test-marker] scorpion_idle_no_hunt_ok
//   [test-marker] scorpion_bite_ok

var __test682_ok = false

function test682_fail(msg) {
    __log_info_native('[test:682] FAIL: ' + msg)
    __test_signal_ready()
}

var test682_spawned = []

// Kill instead of poof: a poofed figure stays on the tile grid until its own action runs, a corpse is
// never prey (predator_prey_on_tile_at skips FIGURE_ACTION_CORPSE).
function test682_clear() {
    city.remove_animals()
    for (var i = 0; i < test682_spawned.length; i++) {
        __test_figure_kill(test682_spawned[i])
    }
    test682_spawned = []
}

function test682_create(type, x, y) {
    var fid = test_figure_create(type, x, y)
    if (fid) {
        test682_spawned.push(fid)
    }
    return fid
}

// Runs `ticks` ticks in `action`; returns the first tick the action changed and the action then.
function test682_run(scorpion, action, ticks) {
    __test_figure_set_action(scorpion, action)
    for (var i = 0; i < ticks; i++) {
        __test_figure_action_perform(scorpion)
        if (__figure_get_action_state(scorpion) != action) {
            return { tick: i + 1, action: __figure_get_action_state(scorpion) }
        }
    }
    return { tick: ticks, action: __figure_get_action_state(scorpion) }
}

function run_test() {
    __log_info_native('[test:682] scorpion OG hunt and bite')
    test_reload_city_session('data/default.map')
    test682_clear()

    var packed = __test_find_accessible_herd_tile(FIGURE_SCORPION)
    if (packed < 0) {
        return test682_fail('no accessible scorpion herd tile')
    }
    var x = (packed >> 16) & 0xffff
    var y = packed & 0xffff

    // A citizen 3 tiles away: no search before the 20th tick, then CHASE (21) with wait 6 * 18.
    var scorpion = test_figure_create(FIGURE_SCORPION, x, y)
    var prey = test682_create(FIGURE_IMMIGRANT, x + 3, y)
    if (!scorpion || !prey) {
        return test682_fail('spawn failed')
    }
    var res = test682_run(scorpion, 20, 30)
    if (res.action != 21 || res.tick != 20) {
        return test682_fail('hunt want CHASE 21 on tick 20, got ' + res.action + ' on tick ' + res.tick)
    }
    if (__figure_get_target_figure_id(scorpion) != prey) {
        return test682_fail('chase target want ' + prey + ', got ' + __figure_get_target_figure_id(scorpion))
    }
    if (__test_figure_get_wait_ticks(scorpion) != 108) {
        return test682_fail('chase wait want 108, got ' + __test_figure_get_wait_ticks(scorpion))
    }
    __log_marker('scorpion_hunt_delay_ok')

    // Beyond 6 rings the search finds nothing.
    test682_clear()
    scorpion = test_figure_create(FIGURE_SCORPION, x, y)
    var far_x = x + 7 < __scenario_map.width - 2 ? x + 7 : x - 7
    prey = test682_create(FIGURE_IMMIGRANT, far_x, y)
    res = test682_run(scorpion, 20, 41)
    if (res.action != 20) {
        return test682_fail('prey 7 tiles away want no chase, got ' + res.action)
    }
    __log_marker('scorpion_hunt_radius_ok')

    // Boats are never prey (figure_is_boat).
    test682_clear()
    scorpion = test_figure_create(FIGURE_SCORPION, x, y)
    var boat = test682_create(FIGURE_FISHING_BOAT, x + 1, y)
    if (boat) {
        res = test682_run(scorpion, 20, 21)
        if (res.action != 20) {
            return test682_fail('boat want no chase, got ' + res.action)
        }
    }
    __log_marker('scorpion_hunt_skips_boats_ok')

    // IDLE (19) never searches: OG calls predator_find_prey_nearby only in REST, PROWL and LOOK_FOR_PREY.
    test682_clear()
    scorpion = test_figure_create(FIGURE_SCORPION, x, y)
    prey = test682_create(FIGURE_IMMIGRANT, x + 1, y)
    __test_figure_set_wait_ticks(scorpion, 100)
    res = test682_run(scorpion, 19, 40)
    if (res.action != 19) {
        return test682_fail('idle scorpion want no hunt, got ' + res.action + ' on tick ' + res.tick)
    }
    __log_marker('scorpion_idle_no_hunt_ok')

    // Bite: melee against a citizen on its tile, OG attack 4 per hit.
    test682_clear()
    scorpion = test_figure_create(FIGURE_SCORPION, x, y)
    prey = test682_create(FIGURE_IMMIGRANT, x, y)
    __test_figure_set_action(scorpion, 18)
    if (__test_figure_combat_attack_at(scorpion, x, y) != 1) {
        return test682_fail('scorpion want in_attack against a citizen')
    }
    if (__test_figure_get_opponent_id(scorpion) != prey) {
        return test682_fail('opponent want ' + prey + ', got ' + __test_figure_get_opponent_id(scorpion))
    }
    var dmg0 = __test_figure_get_damage(prey)
    for (var j = 0; j < 30 && __test_figure_is_alive(prey); j++) {
        __test_figure_action_perform(scorpion)
    }
    if (__test_figure_is_alive(prey) && __test_figure_get_damage(prey) < dmg0 + 4) {
        return test682_fail('bite want +4 damage (attack 4), got ' + (__test_figure_get_damage(prey) - dmg0))
    }
    __log_marker('scorpion_bite_ok')

    __test682_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test682_ok) {
        return false
    }
    var markers = ['scorpion_hunt_delay_ok', 'scorpion_hunt_radius_ok', 'scorpion_hunt_skips_boats_ok', 'scorpion_idle_no_hunt_ok',
        'scorpion_bite_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:682] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    test682_clear()
}

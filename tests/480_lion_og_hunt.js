// FIGURE_LION hunt and bite: OG predator_find_prey_nearby with the lion climate record (hunt_delay 18,
// hunt_radius 14 rings, chase wait radius * 18), no hunger, and melee at OG attack 10.
// Markers:
//   [test-marker] lion_hunt_delay_ok
//   [test-marker] lion_hunt_radius_ok
//   [test-marker] lion_hunt_skips_boats_ok
//   [test-marker] lion_idle_no_hunt_ok
//   [test-marker] lion_bite_ok

var __test480_ok = false

function test480_fail(msg) {
    __log_info_native('[test:480] FAIL: ' + msg)
    __test_signal_ready()
}

var test480_spawned = []

// Kill instead of poof: a poofed figure stays on the tile grid until its own action runs, a corpse is
// never prey (predator_prey_on_tile_at skips FIGURE_ACTION_CORPSE).
function test480_clear() {
    city.remove_animals()
    for (var i = 0; i < test480_spawned.length; i++) {
        __test_figure_kill(test480_spawned[i])
    }
    test480_spawned = []
}

function test480_create(type, x, y) {
    var fid = test_figure_create(type, x, y)
    if (fid) {
        test480_spawned.push(fid)
    }
    return fid
}

// Runs `ticks` ticks in `action`; returns the first tick the action changed and the action then.
function test480_run(lion, action, ticks) {
    __test_figure_set_action(lion, action)
    for (var i = 0; i < ticks; i++) {
        __test_figure_action_perform(lion)
        if (__figure_get_action_state(lion) != action) {
            return { tick: i + 1, action: __figure_get_action_state(lion) }
        }
    }
    return { tick: ticks, action: __figure_get_action_state(lion) }
}

function run_test() {
    __log_info_native('[test:480] lion OG hunt and bite')
    test_reload_city_session('data/default.map')
    test480_clear()

    var packed = __test_find_accessible_herd_tile(FIGURE_LION)
    if (packed < 0) {
        return test480_fail('no accessible lion herd tile')
    }
    var x = (packed >> 16) & 0xffff
    var y = packed & 0xffff

    // A citizen 3 tiles away: no search before the 18th tick, then CHASE (21) with wait 14 * 18.
    var lion = test_figure_create(FIGURE_LION, x, y)
    var prey = test480_create(FIGURE_IMMIGRANT, x + 3, y)
    if (!lion || !prey) {
        return test480_fail('spawn failed')
    }
    var res = test480_run(lion, 20, 30)
    if (res.action != 21 || res.tick != 18) {
        return test480_fail('hunt want CHASE 21 on tick 18, got ' + res.action + ' on tick ' + res.tick)
    }
    if (__figure_get_target_figure_id(lion) != prey) {
        return test480_fail('chase target want ' + prey + ', got ' + __figure_get_target_figure_id(lion))
    }
    if (__test_figure_get_wait_ticks(lion) != 252) {
        return test480_fail('chase wait want 252, got ' + __test_figure_get_wait_ticks(lion))
    }
    __log_marker('lion_hunt_delay_ok')

    // Beyond 14 rings the search finds nothing.
    test480_clear()
    lion = test_figure_create(FIGURE_LION, x, y)
    var far_x = x + 15 < __scenario_map.width - 2 ? x + 15 : x - 15
    prey = test480_create(FIGURE_IMMIGRANT, far_x, y)
    res = test480_run(lion, 20, 37)
    if (res.action != 20) {
        return test480_fail('prey 15 tiles away want no chase, got ' + res.action)
    }
    __log_marker('lion_hunt_radius_ok')

    // Boats are never prey (figure_is_boat).
    test480_clear()
    lion = test_figure_create(FIGURE_LION, x, y)
    var boat = test480_create(FIGURE_FISHING_BOAT, x + 1, y)
    if (boat) {
        res = test480_run(lion, 20, 19)
        if (res.action != 20) {
            return test480_fail('boat want no chase, got ' + res.action)
        }
    }
    __log_marker('lion_hunt_skips_boats_ok')

    // IDLE (19) never searches: OG calls predator_find_prey_nearby only in REST, PROWL and LOOK_FOR_PREY.
    test480_clear()
    lion = test_figure_create(FIGURE_LION, x, y)
    prey = test480_create(FIGURE_IMMIGRANT, x + 1, y)
    __test_figure_set_wait_ticks(lion, 100)
    res = test480_run(lion, 19, 40)
    if (res.action != 19) {
        return test480_fail('idle lion want no hunt, got ' + res.action + ' on tick ' + res.tick)
    }
    __log_marker('lion_idle_no_hunt_ok')

    // Bite: melee against a citizen on its tile, OG attack 10 per hit.
    test480_clear()
    lion = test_figure_create(FIGURE_LION, x, y)
    prey = test480_create(FIGURE_IMMIGRANT, x, y)
    __test_figure_set_action(lion, 18)
    if (__test_figure_combat_attack_at(lion, x, y) != 1) {
        return test480_fail('lion want in_attack against a citizen')
    }
    if (__test_figure_get_opponent_id(lion) != prey) {
        return test480_fail('opponent want ' + prey + ', got ' + __test_figure_get_opponent_id(lion))
    }
    var dmg0 = __test_figure_get_damage(prey)
    for (var j = 0; j < 30 && __test_figure_is_alive(prey); j++) {
        __test_figure_action_perform(lion)
    }
    if (__test_figure_is_alive(prey) && __test_figure_get_damage(prey) < dmg0 + 10) {
        return test480_fail('bite want +10 damage (attack 10), got ' + (__test_figure_get_damage(prey) - dmg0))
    }
    __log_marker('lion_bite_ok')

    __test480_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test480_ok) {
        return false
    }
    var markers = ['lion_hunt_delay_ok', 'lion_hunt_radius_ok', 'lion_hunt_skips_boats_ok', 'lion_idle_no_hunt_ok',
        'lion_bite_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:480] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    test480_clear()
}

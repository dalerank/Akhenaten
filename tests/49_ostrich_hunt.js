// Stationary ostrich + hunter with lodge home.
// Polls for: hunter enters HUNT → force a shot (anim unreliable under --no-resource)
// → ostrich dies → gamemeat appears on the lodge.
//
// Markers:
//   [test-marker] ostrich_hunt_setup_ok
//   [test-marker] ostrich_hunt_hunting_ok
//   [test-marker] ostrich_hunt_killed_ok
//   [test-marker] ostrich_hunt_meat_ok
//
// Action/state constants come from C++ token_holder binds
// (e_ostrich_hunter_action, e_ostrich_action, e_figure_state, e_common_action).

var __test49_ok = false

function test49_action_name(a) {
    if (a == ACTION_8_RECALCULATE) return 'RECALC'
    if (a == ACTION_9_OSTRICH_HUNTER_CHASE_PREY) return 'CHASE'
    if (a == ACTION_10_OSTRICH_HUNTER_PICKUP_ANIMAL) return 'PICKUP'
    if (a == ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT) return 'GO_PICKUP'
    if (a == ACTION_12_OSTRICH_HUNTER_MOVE_PACKED) return 'MOVE_PACKED'
    if (a == ACTION_13_OSTRICH_HUNTER_WAIT_FOR_ACTION) return 'WAIT'
    if (a == ACTION_14_OSTRICH_HUNTER_UNLOADING) return 'UNLOAD'
    if (a == ACTION_15_OSTRICH_HUNTER_HUNT) return 'HUNT'
    if (a == ACTION_16_OSTRICH_HUNTER_INVESTIGATE) return 'INVESTIGATE'
    if (a == ACTION_12_OSTRICH_HUNTER_MOVE_RANDOM_PACKED) return 'MOVE_RANDOM_PACKED'
    if (a == ACTION_12_OSTRICH_HUNTER_LOOK_RANDOM_PACKED) return 'LOOK_RANDOM_PACKED'
    return '?' + a
}

function run_test() {
    __log_info_native('[test:49] ostrich hunt (stationary prey, poll meat)')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_HUNTING_LODGE, -1, -1)
    if (!bid) {
        __log_info_native('[test:49] FAIL: lodge place failed')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    if (!tile) {
        __log_info_native('[test:49] FAIL: lodge tile missing')
        __test_signal_ready()
        return
    }

    // Prey next to lodge; hunter within attack_distance (OG: 3).
    var ostrich = test_figure_create(FIGURE_OSTRICH, tile.x + 2, tile.y)
    var hunter = test_figure_create(FIGURE_OSTRICH_HUNTER, tile.x + 4, tile.y)
    if (!ostrich || !hunter) {
        __log_info_native('[test:49] FAIL: spawn ostrich/hunter failed')
        __test_signal_ready()
        return
    }

    test_figure_set_home(hunter, bid)
    test_figure_set_speed(ostrich, 0)
    // Under --no-resource hunt/pack/unload need animctx to tick without atlas.
    test_figure_set_force_valid_animation(hunter, true)
    test_figure_set_force_valid_animation(ostrich, true)
    __test_figure_set_action(ostrich, ACTION_19_OSTRICH_IDLE)
    __test_figure_set_action(hunter, ACTION_8_RECALCULATE)

    var meat0 = city.get_building(bid).stored_resource(RESOURCE_GAMEMEAT)
    __log_marker('ostrich_hunt_setup_ok')

    var hunting = false
    var killed = false
    var meat_ok = false
    var shots = 0

    for (var i = 0; i < 80; i++) {
        test_figure_set_speed(ostrich, 0)
        __test_pump_frames(30)

        var ha = __figure_is_valid(hunter) ? __figure_get_action_state(hunter) : -1

        // Natural OG shoot can leave HUNT within one pump; GO_PICKUP also counts.
        if (!hunting && (ha == ACTION_15_OSTRICH_HUNTER_HUNT
                || ha == ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT
                || ha == ACTION_10_OSTRICH_HUNTER_PICKUP_ANIMAL)) {
            __log_marker('ostrich_hunt_hunting_ok')
            hunting = true
        }

        // Under --no-resource the hunt anim may never finish, so force shots
        // once the hunter has acquired the prey and entered HUNT.
        if (hunting && !killed && shots < 4) {
            var mid = __test_hunter_force_shot(hunter)
            if (mid) {
                shots++
            }
            __test_pump_frames(20)
        }

        if (!killed) {
            var oa = __figure_is_valid(ostrich) ? __figure_get_action_state(ostrich) : -1
            var dead = !__figure_is_valid(ostrich)
                || __figure_get_state(ostrich) == FIGURE_STATE_DYING
                || oa == 12 // ACTION_12_OSTRICH_HUNTED
                || oa == 149 // FIGURE_ACTION_149_CORPSE
                || test_figure_get_damage(ostrich) >= 100
            if (dead) {
                __log_marker('ostrich_hunt_killed_ok')
                killed = true
            }
        }

        var meat = city.get_building(bid).stored_resource(RESOURCE_GAMEMEAT)
        if (meat >= meat0 + 100) {
            __log_marker('ostrich_hunt_meat_ok')
            meat_ok = true
            break
        }
    }

    if (!hunting) {
        __log_info_native('[test:49] FAIL: hunter never entered HUNT'
            + ' action=' + __figure_get_action_state(hunter))
        __test_signal_ready()
        return
    }
    if (!killed) {
        __log_info_native('[test:49] FAIL: ostrich not killed'
            + ' state=' + __figure_get_state(ostrich)
            + ' dmg=' + test_figure_get_damage(ostrich)
            + ' shots=' + shots
            + ' arrows=' + __test_count_figures(FIGURE_HUNTER_ARROW))
        __test_signal_ready()
        return
    }
    if (!meat_ok) {
        __log_info_native('[test:49] FAIL: no gamemeat on lodge'
            + ' stored=' + city.get_building(bid).stored_resource(RESOURCE_GAMEMEAT)
            + ' hunter_action=' + (__figure_is_valid(hunter)
                ? test49_action_name(__figure_get_action_state(hunter))
                : 'gone')
            + ' hunter_anim=' + (__figure_is_valid(hunter) ? __figure_get_anim_key(hunter) : '-'))
        __test_signal_ready()
        return
    }

    __test49_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test49_ok) {
        __log_info_native('[test:49] run_test did not complete')
        return false
    }

    var markers = [
        '[test-marker] ostrich_hunt_setup_ok',
        '[test-marker] ostrich_hunt_hunting_ok',
        '[test-marker] ostrich_hunt_killed_ok',
        '[test-marker] ostrich_hunt_meat_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog(markers[i])) {
            __log_info_native('[test:49] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

// Two ostriches + hunter: kill one, companion in range must get e_figure_flag_scared.
// Based on 49_ostrich_hunt.js setup; does not wait for meat delivery.
//
// Markers:
//   [test-marker] ostrich_herd_scare_setup_ok
//   [test-marker] ostrich_herd_scare_hunting_ok
//   [test-marker] ostrich_herd_scare_killed_ok
//   [test-marker] ostrich_herd_scare_companion_scared_ok

var __test51_ok = false

function run_test() {
    __log_info_native('[test:51] ostrich herd scare (companion gets e_figure_flag_scared)')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_HUNTING_LODGE, -1, -1)
    if (!bid) {
        __log_info_native('[test:51] FAIL: lodge place failed')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    if (!tile) {
        __log_info_native('[test:51] FAIL: lodge tile missing')
        __test_signal_ready()
        return
    }

    // Prey closer to hunter than companion so hunter acquires the prey.
    var prey = test_figure_create(FIGURE_OSTRICH, tile.x + 2, tile.y)
    var companion = test_figure_create(FIGURE_OSTRICH, tile.x + 1, tile.y)
    var hunter = test_figure_create(FIGURE_OSTRICH_HUNTER, tile.x + 4, tile.y)
    if (!prey || !companion || !hunter) {
        __log_info_native('[test:51] FAIL: spawn prey/companion/hunter failed')
        __test_signal_ready()
        return
    }

    test_figure_set_home(hunter, bid)
    test_figure_set_speed(prey, 0)
    test_figure_set_speed(companion, 0)
    test_figure_set_force_valid_animation(hunter, true)
    test_figure_set_force_valid_animation(prey, true)
    test_figure_set_force_valid_animation(companion, true)
    __test_figure_set_action(prey, ACTION_19_OSTRICH_IDLE)
    __test_figure_set_action(companion, ACTION_19_OSTRICH_IDLE)
    __test_figure_set_action(hunter, ACTION_8_RECALCULATE)

    if (__figure_is_scared(companion)) {
        __log_info_native('[test:51] FAIL: companion already scared at setup')
        __test_signal_ready()
        return
    }

    __log_info_native('[test:51] setup lodge=' + bid
        + ' prey=' + prey + ' companion=' + companion + ' hunter=' + hunter)
    __log_marker('ostrich_herd_scare_setup_ok')

    var hunting = false
    var killed = false
    var scared = false
    var shots = 0

    for (var i = 0; i < 80; i++) {
        test_figure_set_speed(prey, 0)
        test_figure_set_speed(companion, 0)
        __test_pump_frames(30)

        var ha = __figure_is_valid(hunter) ? __figure_get_action_state(hunter) : -1

        if (!hunting && (ha == ACTION_15_OSTRICH_HUNTER_HUNT
                || ha == ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT
                || ha == ACTION_10_OSTRICH_HUNTER_PICKUP_ANIMAL)) {
            __log_marker('ostrich_herd_scare_hunting_ok')
            hunting = true
        }

        if (hunting && !killed && shots < 4) {
            var mid = __test_hunter_force_shot(hunter)
            if (mid) {
                shots++
            }
            __test_pump_frames(20)
        }

        if (!killed) {
            var pa = __figure_is_valid(prey) ? __figure_get_action_state(prey) : -1
            var dead = !__figure_is_valid(prey)
                || __figure_get_state(prey) == FIGURE_STATE_DYING
                || pa == 12 || pa == 149
                || test_figure_get_damage(prey) >= 100
            if (dead) {
                __log_marker('ostrich_herd_scare_killed_ok')
                killed = true
            }
        }

        if (killed && __figure_is_valid(companion) && __figure_is_scared(companion)) {
            __log_marker('ostrich_herd_scare_companion_scared_ok')
            scared = true
            break
        }
    }

    if (!hunting) {
        __log_info_native('[test:51] FAIL: hunter never entered HUNT'
            + ' action=' + __figure_get_action_state(hunter))
        __test_signal_ready()
        return
    }
    if (!killed) {
        __log_info_native('[test:51] FAIL: prey not killed'
            + ' state=' + __figure_get_state(prey)
            + ' dmg=' + test_figure_get_damage(prey)
            + ' shots=' + shots)
        __test_signal_ready()
        return
    }
    if (!scared) {
        __log_info_native('[test:51] FAIL: companion not scared'
            + ' valid=' + (__figure_is_valid(companion) ? 1 : 0)
            + ' scared=' + (__figure_is_scared(companion) ? 1 : 0)
            + ' action=' + (__figure_is_valid(companion) ? __figure_get_action_state(companion) : -1)
            + ' hunter_action=' + (__figure_is_valid(hunter) ? __figure_get_action_state(hunter) : -1))
        __test_signal_ready()
        return
    }

    __test51_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test51_ok) {
        __log_info_native('[test:51] run_test did not complete')
        return false
    }

    var markers = [
        '[test-marker] ostrich_herd_scare_setup_ok',
        '[test-marker] ostrich_herd_scare_hunting_ok',
        '[test-marker] ostrich_herd_scare_killed_ok',
        '[test-marker] ostrich_herd_scare_companion_scared_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog(markers[i])) {
            __log_info_native('[test:51] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

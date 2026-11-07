// Birds hunter prey filter + hunt → gamemeat (BH3).
// Stationary bird; ostrich/antelope on map must be ignored as target.
// Markers:
//   [test-marker] birds_hunt_setup_ok
//   [test-marker] birds_hunt_hunting_ok
//   [test-marker] birds_hunt_killed_ok
//   [test-marker] birds_hunt_meat_ok
//   [test-marker] birds_hunt_ignored_ostrich_ok

var __test80_ok = false

function run_test() {
    __log_info_native('[test:80] birds hunt prey filter + meat')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_HUNTING_LODGE, -1, -1)
    if (!bid) {
        __log_info_native('[test:80] FAIL: lodge place failed')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    if (!tile) {
        __log_info_native('[test:80] FAIL: lodge tile missing')
        __test_signal_ready()
        return
    }

    // Ostrich closer than birds — must still be ignored by prey filter.
    var ostrich = test_figure_create(FIGURE_OSTRICH, tile.x + 2, tile.y)
    var antelope = test_figure_create(FIGURE_ANTELOPE, tile.x + 2, tile.y + 1)
    var bird = test_figure_create(FIGURE_BIRDS, tile.x + 3, tile.y)
    var hunter = test_figure_create(FIGURE_BIRDS_HUNTER, tile.x + 4, tile.y)
    if (!ostrich || !antelope || !bird || !hunter) {
        __log_info_native('[test:80] FAIL: spawn failed')
        __test_signal_ready()
        return
    }

    test_figure_set_home(hunter, bid)
    test_figure_set_speed(ostrich, 0)
    test_figure_set_speed(antelope, 0)
    test_figure_set_speed(bird, 0)
    test_figure_set_force_valid_animation(hunter, true)
    test_figure_set_force_valid_animation(bird, true)
    __test_figure_set_action(ostrich, ACTION_19_OSTRICH_IDLE)
    __test_figure_set_action(antelope, ACTION_19_OSTRICH_IDLE)
    __test_figure_set_action(bird, 19) // ACTION_19_BIRDS_IDLE
    __test_figure_set_action(hunter, ACTION_8_RECALCULATE)

    var meat0 = city.get_building(bid).stored_resource(RESOURCE_GAMEMEAT)
    __log_marker('birds_hunt_setup_ok')

    var hunting = false
    var killed = false
    var meat_ok = false
    var shots = 0

    for (var i = 0; i < 80; i++) {
        test_figure_set_speed(ostrich, 0)
        test_figure_set_speed(antelope, 0)
        test_figure_set_speed(bird, 0)
        // The shot state lasts a few ticks: sample every frame, not every 30.
        var ha = -1
        var target = 0
        for (var f = 0; f < 30; f++) {
            __test_pump_frames(1)
            ha = __figure_is_valid(hunter) ? __figure_get_action_state(hunter) : -1
            target = __figure_is_valid(hunter) ? __figure_get_target_figure_id(hunter) : 0
            if (ha == ACTION_15_OSTRICH_HUNTER_HUNT || target == ostrich || target == antelope) {
                break
            }
        }

        if (target == ostrich || target == antelope) {
            __log_info_native('[test:80] FAIL: hunter targeted wrong prey: ' + target)
            __test_signal_ready()
            return
        }

        if (!hunting && ha == ACTION_15_OSTRICH_HUNTER_HUNT) {
            if (target != bird && target != 0) {
                __log_info_native('[test:80] FAIL: hunt target not bird: ' + target)
                __test_signal_ready()
                return
            }
            __log_marker('birds_hunt_hunting_ok')
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
            var dead = !__figure_is_valid(bird)
                || __figure_get_state(bird) == FIGURE_STATE_DYING
                || test_figure_get_damage(bird) >= 100
            if (dead) {
                __log_marker('birds_hunt_killed_ok')
                killed = true
            }
        }

        var meat = city.get_building(bid).stored_resource(RESOURCE_GAMEMEAT)
        if (meat >= meat0 + 100) {
            __log_marker('birds_hunt_meat_ok')
            meat_ok = true
            break
        }
    }

    if (!__figure_is_valid(ostrich)) {
        __log_info_native('[test:80] FAIL: ostrich was killed (should be ignored)')
        __test_signal_ready()
        return
    }
    if (!__figure_is_valid(antelope)) {
        __log_info_native('[test:80] FAIL: antelope was killed (should be ignored)')
        __test_signal_ready()
        return
    }
    __log_marker('birds_hunt_ignored_ostrich_ok')

    if (!hunting || !killed || !meat_ok) {
        __log_info_native('[test:80] FAIL: hunting=' + hunting
            + ' killed=' + killed + ' meat=' + meat_ok)
        __test_signal_ready()
        return
    }

    __test80_ok = true
    __log_info_native('[test:80] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test80_ok) {
        __log_info_native('[test:80] run_test did not complete')
        return false
    }
    var markers = [
        '[test-marker] birds_hunt_setup_ok',
        '[test-marker] birds_hunt_hunting_ok',
        '[test-marker] birds_hunt_killed_ok',
        '[test-marker] birds_hunt_meat_ok',
        '[test-marker] birds_hunt_ignored_ostrich_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog(markers[i])) {
            __log_info_native('[test:80] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

// Antelope hunter prey filter + hunt → gamemeat (AH4).
// Stationary antelope; ostrich on map must be ignored as target.
// Markers:
//   [test-marker] antelope_hunt_setup_ok
//   [test-marker] antelope_hunt_hunting_ok
//   [test-marker] antelope_hunt_killed_ok
//   [test-marker] antelope_hunt_meat_ok
//   [test-marker] antelope_hunt_ignored_ostrich_ok

var __test73_ok = false

function run_test() {
    __log_info_native('[test:73] antelope hunt prey filter + meat')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_HUNTING_LODGE, -1, -1)
    if (!bid) {
        __log_info_native('[test:73] FAIL: lodge place failed')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    if (!tile) {
        __log_info_native('[test:73] FAIL: lodge tile missing')
        __test_signal_ready()
        return
    }

    // Ostrich closer than antelope — must still be ignored by prey filter.
    // Hunter within OG attack_distance (3) of antelope.
    var ostrich = test_figure_create(FIGURE_OSTRICH, tile.x + 1, tile.y)
    var antelope = test_figure_create(FIGURE_ANTELOPE, tile.x + 3, tile.y)
    var hunter = test_figure_create(FIGURE_ANTELOPE_HUNTER, tile.x + 4, tile.y)
    if (!ostrich || !antelope || !hunter) {
        __log_info_native('[test:73] FAIL: spawn failed')
        __test_signal_ready()
        return
    }

    // Lodge may spawn other climate hunters — keep this test on the hand-made one.
    city.figures.remove_figures(FIGURE_OSTRICH_HUNTER)
    city.figures.remove_figures(FIGURE_BIRDS_HUNTER)

    test_figure_set_home(hunter, bid)
    test_figure_set_speed(ostrich, 0)
    test_figure_set_speed(antelope, 0)
    test_figure_set_force_valid_animation(hunter, true)
    test_figure_set_force_valid_animation(antelope, true)
    __test_figure_set_action(ostrich, ACTION_19_OSTRICH_IDLE)
    __test_figure_set_action(antelope, ACTION_19_OSTRICH_IDLE) // same value as ANTELOPE_IDLE (19)
    __test_figure_set_action(hunter, ACTION_8_RECALCULATE)

    var meat0 = city.get_building(bid).stored_resource(RESOURCE_GAMEMEAT)
    __log_marker('antelope_hunt_setup_ok')

    var hunting = false
    var killed = false
    var meat_ok = false
    var shots = 0

    for (var i = 0; i < 80; i++) {
        test_figure_set_speed(ostrich, 0)
        test_figure_set_speed(antelope, 0)
        __test_pump_frames(30)

        var ha = __figure_is_valid(hunter) ? __figure_get_action_state(hunter) : -1
        var target = __figure_is_valid(hunter) ? __figure_get_target_figure_id(hunter) : 0

        if (target == ostrich) {
            __log_info_native('[test:73] FAIL: hunter targeted ostrich')
            __test_signal_ready()
            return
        }

        if (!hunting && (ha == ACTION_15_OSTRICH_HUNTER_HUNT
                || ha == ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT
                || ha == ACTION_10_OSTRICH_HUNTER_PICKUP_ANIMAL)) {
            if (target != antelope && target != 0) {
                __log_info_native('[test:73] FAIL: hunt target not antelope: ' + target)
                __test_signal_ready()
                return
            }
            __log_marker('antelope_hunt_hunting_ok')
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
            var aa = __figure_is_valid(antelope) ? __figure_get_action_state(antelope) : -1
            var dead = !__figure_is_valid(antelope)
                || __figure_get_state(antelope) == FIGURE_STATE_DYING
                || aa == 12 // ACTION_12_ANTELOPE_HUNTED
                || aa == 149 // FIGURE_ACTION_149_CORPSE
                || test_figure_get_damage(antelope) >= 100
            if (dead) {
                __log_marker('antelope_hunt_killed_ok')
                killed = true
            }
        }

        var meat = city.get_building(bid).stored_resource(RESOURCE_GAMEMEAT)
        if (meat >= meat0 + 100) {
            __log_marker('antelope_hunt_meat_ok')
            meat_ok = true
            break
        }
    }

    if (!__figure_is_valid(ostrich)) {
        __log_info_native('[test:73] FAIL: ostrich was killed (should be ignored)')
        __test_signal_ready()
        return
    }
    __log_marker('antelope_hunt_ignored_ostrich_ok')

    if (!hunting || !killed || !meat_ok) {
        __log_info_native('[test:73] FAIL: hunting=' + hunting
            + ' killed=' + killed + ' meat=' + meat_ok)
        __test_signal_ready()
        return
    }

    __test73_ok = true
    __log_info_native('[test:73] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test73_ok) {
        __log_info_native('[test:73] run_test did not complete')
        return false
    }
    var markers = [
        '[test-marker] antelope_hunt_setup_ok',
        '[test-marker] antelope_hunt_hunting_ok',
        '[test-marker] antelope_hunt_killed_ok',
        '[test-marker] antelope_hunt_meat_ok',
        '[test-marker] antelope_hunt_ignored_ostrich_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog(markers[i])) {
            __log_info_native('[test:73] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

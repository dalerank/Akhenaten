// FIG_HUNTER / FIG_HUNTER_SPEAR: OG spear marks herd prey HUNTED (no HP damage),
// then hunter goes to pick up. Remake keeps climate hunter types + herd scare.
// Markers:
//   [test-marker] hunter_spear_hunted_ok
//   [test-marker] hunter_spear_no_hp_ok
//   [test-marker] hunter_spear_go_pickup_ok

var __test253_ok = false

function test253_fail(msg) {
    __log_info_native('[test:253] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:253] FIG_HUNTER spear → HUNTED (OG)')

    test_ensure_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_HUNTING_LODGE, -1, -1)
    if (!bid) {
        return test253_fail('lodge place failed')
    }
    var tile = __building_tile(bid)
    if (!tile) {
        return test253_fail('lodge tile missing')
    }

    var prey = test_figure_create(FIGURE_OSTRICH, tile.x + 1, tile.y)
    var hunter = test_figure_create(FIGURE_OSTRICH_HUNTER, tile.x + 2, tile.y)
    if (!prey || !hunter) {
        return test253_fail('spawn failed')
    }

    test_figure_set_home(hunter, bid)
    test_figure_set_speed(prey, 0)
    test_figure_set_force_valid_animation(hunter, true)
    test_figure_set_force_valid_animation(prey, true)
    __test_figure_set_action(prey, ACTION_19_OSTRICH_IDLE)
    __test_figure_set_action(hunter, ACTION_8_RECALCULATE)

    var hunting = false
    for (var i = 0; i < 40; i++) {
        test_figure_set_speed(prey, 0)
        __test_pump_frames(20)
        if (__figure_get_action_state(hunter) == ACTION_15_OSTRICH_HUNTER_HUNT) {
            hunting = true
            break
        }
    }
    if (!hunting) {
        return test253_fail('hunter never entered HUNT')
    }

    var mid = __test_hunter_force_shot(hunter)
    if (!mid) {
        return test253_fail('force shot failed')
    }
    var dmg0 = __test_figure_get_damage(prey)
    for (var t = 0; t < 40 && __test_figure_is_alive(mid) == 1; t++) {
        __test_figure_action_perform(mid)
    }

    if (__figure_get_action_state(prey) != 12) { // ACTION_12_OSTRICH_HUNTED
        return test253_fail('prey should be HUNTED, action=' + __figure_get_action_state(prey))
    }
    __log_marker('hunter_spear_hunted_ok')

    if (__test_figure_get_damage(prey) != dmg0) {
        return test253_fail('OG spear must not apply HP damage')
    }
    __log_marker('hunter_spear_no_hp_ok')

    if (__figure_get_action_state(hunter) != ACTION_11_OSTRICH_HUNTER_GOING_TO_PICKUP_POINT) {
        return test253_fail('hunter should GO_PICKUP, action=' + __figure_get_action_state(hunter))
    }
    __log_marker('hunter_spear_go_pickup_ok')

    __test253_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test253_ok
        && __test_find_inlog('[test-marker] hunter_spear_hunted_ok')
        && __test_find_inlog('[test-marker] hunter_spear_no_hp_ok')
        && __test_find_inlog('[test-marker] hunter_spear_go_pickup_ok')
}

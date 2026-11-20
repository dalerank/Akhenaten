// FIGURE_ASP death: OG Figure_model row 102 (10 hit points), the corpse stays 128 ticks
// (figure_combat_handle_corpse) on the ASP_DEATH sprites, PREDATOR_DYING (12) turns into a corpse.
// Markers:
//   [test-marker] asp_hit_points_ok
//   [test-marker] asp_corpse_ok
//   [test-marker] asp_dying_ok

var __test474_ok = false

function test474_fail(msg) {
    __log_info_native('[test:474] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:474] asp OG death')
    test_reload_city_session('data/default.map')
    city.remove_animals()

    var packed = __test_find_accessible_herd_tile(FIGURE_ASP)
    if (packed < 0) {
        return test474_fail('no accessible asp herd tile')
    }
    var x = (packed >> 16) & 0xffff
    var y = packed & 0xffff

    var asp = test_figure_create(FIGURE_ASP, x, y)
    if (!asp) {
        return test474_fail('create failed')
    }
    if (__test_figure_max_damage(asp) != 10) {
        return test474_fail('max_damage want 10, got ' + __test_figure_max_damage(asp))
    }
    __log_marker('asp_hit_points_ok')

    // Corpse: death sprites, removed on the 128th tick.
    __test_figure_kill(asp)
    __test_figure_set_wait_ticks(asp, 0)
    for (var t = 1; t < 128; t++) {
        __test_figure_action_perform_dying(asp)
        if (!__figure_is_valid(asp)) {
            return test474_fail('corpse removed early on tick ' + t)
        }
        if (__figure_get_action_state(asp) != 149) {
            return test474_fail('corpse left state 149 on tick ' + t + ': ' + __figure_get_action_state(asp))
        }
    }
    if (__figure_get_anim_key(asp) != 'death') {
        return test474_fail('corpse anim want death, got ' + __figure_get_anim_key(asp))
    }
    __test_figure_action_perform_dying(asp)
    if (__figure_is_valid(asp)) {
        return test474_fail('corpse want removed on tick 128')
    }
    __log_marker('asp_corpse_ok')

    // PREDATOR_DYING (12): a corpse once the wait passes dying_ticks (500).
    var asp2 = test_figure_create(FIGURE_ASP, x, y)
    if (!asp2) {
        return test474_fail('create2 failed')
    }
    __test_figure_set_action(asp2, 12)
    __test_figure_set_wait_ticks(asp2, 499)
    __test_figure_action_perform(asp2)
    if (__figure_get_action_state(asp2) != 12) {
        return test474_fail('dying left early: ' + __figure_get_action_state(asp2))
    }
    __test_figure_action_perform(asp2)
    if (__figure_get_action_state(asp2) != 149) {
        return test474_fail('dying want corpse 149, got ' + __figure_get_action_state(asp2))
    }
    __log_marker('asp_dying_ok')

    __test474_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test474_ok) {
        return false
    }
    var markers = ['asp_hit_points_ok', 'asp_corpse_ok', 'asp_dying_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:474] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.remove_animals()
}

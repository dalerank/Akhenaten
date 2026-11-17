// FIGURE_SCORPION death: OG Figure_model row 104 (7 hit points), the corpse stays 128 ticks (figure_combat_handle_corpse)
// on the SCORPION_DEATH sprites, PREDATOR_DYING (12) turns into a corpse after WILD_DYING_TICKS (500), and the death
// image is SCORPION_DEATH + min(wait, 5) without a direction (wild_image).
// Markers:
//   [test-marker] scorpion_hit_points_ok
//   [test-marker] scorpion_corpse_ok
//   [test-marker] scorpion_dying_ok
//   [test-marker] scorpion_death_image_ok

var __test683_ok = false

function test683_fail(msg) {
    __log_info_native('[test:683] FAIL: ' + msg)
    __test_signal_ready()
}

function test683_dying_image(fid, wait) {
    __test_figure_set_wait_ticks(fid, wait)
    return __test_figure_death_frame(fid)
}

function run_test() {
    __log_info_native('[test:683] scorpion OG death')
    test_reload_city_session('data/default.map')
    city.remove_animals()

    var packed = __test_find_accessible_herd_tile(FIGURE_SCORPION)
    if (packed < 0) {
        return test683_fail('no accessible scorpion herd tile')
    }
    var x = (packed >> 16) & 0xffff
    var y = packed & 0xffff

    var scorpion = test_figure_create(FIGURE_SCORPION, x, y)
    if (!scorpion) {
        return test683_fail('create failed')
    }
    if (__test_figure_max_damage(scorpion) != 7) {
        return test683_fail('max_damage want 7, got ' + __test_figure_max_damage(scorpion))
    }
    __log_marker('scorpion_hit_points_ok')

    // Corpse: death sprites, removed on the 128th tick.
    __test_figure_kill(scorpion)
    __test_figure_set_wait_ticks(scorpion, 0)
    for (var t = 1; t < 128; t++) {
        __test_figure_action_perform_dying(scorpion)
        if (!__figure_is_valid(scorpion)) {
            return test683_fail('corpse removed early on tick ' + t)
        }
        if (__figure_get_action_state(scorpion) != 149) {
            return test683_fail('corpse left state 149 on tick ' + t + ': ' + __figure_get_action_state(scorpion))
        }
    }
    if (__figure_get_anim_key(scorpion) != 'death') {
        return test683_fail('corpse anim want death, got ' + __figure_get_anim_key(scorpion))
    }
    __test_figure_action_perform_dying(scorpion)
    if (__figure_is_valid(scorpion)) {
        return test683_fail('corpse want removed on tick 128')
    }
    __log_marker('scorpion_corpse_ok')

    // PREDATOR_DYING (12): a corpse once the wait passes 500.
    var scorpion2 = test_figure_create(FIGURE_SCORPION, x, y)
    if (!scorpion2) {
        return test683_fail('create2 failed')
    }
    __test_figure_set_action(scorpion2, 12)
    __test_figure_set_wait_ticks(scorpion2, 499)
    __test_figure_action_perform(scorpion2)
    if (__figure_get_action_state(scorpion2) != 12) {
        return test683_fail('dying left early: ' + __figure_get_action_state(scorpion2))
    }
    __test_figure_action_perform(scorpion2)
    if (__figure_get_action_state(scorpion2) != 149) {
        return test683_fail('dying want corpse 149, got ' + __figure_get_action_state(scorpion2))
    }
    __log_marker('scorpion_dying_ok')

    // Death image: one frame per wait tick without directions, last frame 5.
    var scorpion3 = test_figure_create(FIGURE_SCORPION, x, y)
    if (!scorpion3) {
        return test683_fail('create3 failed')
    }
    __test_figure_set_action(scorpion3, 12)
    __test_figure_update_animation(scorpion3)
    var img2 = test683_dying_image(scorpion3, 2)
    var img3 = test683_dying_image(scorpion3, 3)
    var img9 = test683_dying_image(scorpion3, 9)
    if (img3 - img2 != 1 || img9 - img2 != 3) {
        return test683_fail('death image want +1 per frame up to frame 5, got ' + img2 + ' ' + img3 + ' ' + img9)
    }
    __log_marker('scorpion_death_image_ok')

    __test683_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test683_ok) {
        return false
    }
    var markers = ['scorpion_hit_points_ok', 'scorpion_corpse_ok', 'scorpion_dying_ok', 'scorpion_death_image_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:683] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.remove_animals()
}

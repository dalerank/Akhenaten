// FIGURE_LION death: OG Figure_model row 103 (12 hit points), the corpse stays 128 ticks (figure_combat_handle_corpse)
// on the LION_DEATH sprites, PREDATOR_DYING (12) turns into a corpse after WILD_DYING_TICKS (500), and the death image
// is LION_DEATH + min(wait, 5) * 8 + direction (wild_image).
// Markers:
//   [test-marker] lion_hit_points_ok
//   [test-marker] lion_corpse_ok
//   [test-marker] lion_dying_ok
//   [test-marker] lion_death_image_ok

var __test673_ok = false

function test673_fail(msg) {
    __log_info_native('[test:673] FAIL: ' + msg)
    __test_signal_ready()
}

function test673_dying_image(fid, wait) {
    __test_figure_set_wait_ticks(fid, wait)
    return __test_figure_death_frame(fid)
}

function run_test() {
    __log_info_native('[test:673] lion OG death')
    test_reload_city_session('data/default.map')
    city.remove_animals()

    var packed = __test_find_accessible_herd_tile(FIGURE_LION)
    if (packed < 0) {
        return test673_fail('no accessible lion herd tile')
    }
    var x = (packed >> 16) & 0xffff
    var y = packed & 0xffff

    var lion = test_figure_create(FIGURE_LION, x, y)
    if (!lion) {
        return test673_fail('create failed')
    }
    if (__test_figure_max_damage(lion) != 12) {
        return test673_fail('max_damage want 12, got ' + __test_figure_max_damage(lion))
    }
    __log_marker('lion_hit_points_ok')

    // Corpse: death sprites, removed on the 128th tick.
    __test_figure_kill(lion)
    __test_figure_set_wait_ticks(lion, 0)
    for (var t = 1; t < 128; t++) {
        __test_figure_action_perform_dying(lion)
        if (!__figure_is_valid(lion)) {
            return test673_fail('corpse removed early on tick ' + t)
        }
        if (__figure_get_action_state(lion) != 149) {
            return test673_fail('corpse left state 149 on tick ' + t + ': ' + __figure_get_action_state(lion))
        }
    }
    if (__figure_get_anim_key(lion) != 'death') {
        return test673_fail('corpse anim want death, got ' + __figure_get_anim_key(lion))
    }
    __test_figure_action_perform_dying(lion)
    if (__figure_is_valid(lion)) {
        return test673_fail('corpse want removed on tick 128')
    }
    __log_marker('lion_corpse_ok')

    // PREDATOR_DYING (12): a corpse once the wait passes 500.
    var lion2 = test_figure_create(FIGURE_LION, x, y)
    if (!lion2) {
        return test673_fail('create2 failed')
    }
    __test_figure_set_action(lion2, 12)
    __test_figure_set_wait_ticks(lion2, 499)
    __test_figure_action_perform(lion2)
    if (__figure_get_action_state(lion2) != 12) {
        return test673_fail('dying left early: ' + __figure_get_action_state(lion2))
    }
    __test_figure_action_perform(lion2)
    if (__figure_get_action_state(lion2) != 149) {
        return test673_fail('dying want corpse 149, got ' + __figure_get_action_state(lion2))
    }
    __log_marker('lion_dying_ok')

    // Death image: one frame per wait tick with 8 directions each, last frame 5.
    var lion3 = test_figure_create(FIGURE_LION, x, y)
    if (!lion3) {
        return test673_fail('create3 failed')
    }
    __test_figure_set_action(lion3, 12)
    __test_figure_update_animation(lion3)
    var img2 = test673_dying_image(lion3, 2)
    var img3 = test673_dying_image(lion3, 3)
    var img9 = test673_dying_image(lion3, 9)
    if (img3 - img2 != 8 || img9 - img2 != 24) {
        return test673_fail('death image want +8 per frame up to frame 5, got ' + img2 + ' ' + img3 + ' ' + img9)
    }
    __log_marker('lion_death_image_ok')

    __test673_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test673_ok) {
        return false
    }
    var markers = ['lion_hit_points_ok', 'lion_corpse_ok', 'lion_dying_ok', 'lion_death_image_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:673] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.remove_animals()
}

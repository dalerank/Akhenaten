// FIGURE_HIPPO: OG figure_hippo_action.
// Markers:
//   [test-marker] hippo_spawned_ok
//   [test-marker] hippo_choose_ok
//   [test-marker] hippo_rest_to_walk_ok
//   [test-marker] hippo_dying_to_corpse_ok
//   [test-marker] hippo_chase_timeout_ok
//   [test-marker] hippo_animate_hold_ok
//   [test-marker] hippo_attack_ok

var __test272_ok = false

function test272_fail(msg) {
    __log_info_native('[test:272] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:272] hippo OG')
    test_reload_city_session('data/default.map')
    city.figures.remove_figures(FIGURE_HIPPO)

    var fid = test_figure_create(FIGURE_HIPPO, 12, 14)
    if (!fid) {
        return test272_fail('create failed')
    }
    test_figure_set_force_valid_animation(fid, true)

    // SPAWNED (24): invisible until wait expires → CHOOSE / REST / WATER.
    __test_figure_set_action(fid, 24)
    __test_figure_set_wait_ticks(fid, 2)
    __test_figure_action_perform(fid)
    if (__test_figure_is_visible(fid) != 0) {
        return test272_fail('spawned want invisible, visible=' + __test_figure_is_visible(fid))
    }
    __test_figure_set_wait_ticks(fid, 0)
    __test_figure_action_perform(fid)
    var after_spawn = __figure_get_action_state(fid)
    if (after_spawn != 8 && after_spawn != 18 && after_spawn != 19) {
        return test272_fail('spawned→8/18/19 got ' + after_spawn)
    }
    if (__test_figure_is_visible(fid) != 1) {
        return test272_fail('after spawn want visible')
    }
    __log_marker('hippo_spawned_ok')

    // CHOOSE (8) → REST(18) or WATER(19) (idle weights 50/50, no animate/charge).
    __test_figure_set_action(fid, 8)
    __test_figure_action_perform(fid)
    var chosen = __figure_get_action_state(fid)
    if (chosen != 18 && chosen != 19) {
        return test272_fail('choose want 18/19, got ' + chosen)
    }
    __log_marker('hippo_choose_ok')

    // REST (18) wait 0 → WALK (9) or stay REST with no_tile wait.
    __test_figure_set_action(fid, 18)
    __test_figure_set_wait_ticks(fid, 0)
    __test_figure_action_perform(fid)
    var act = __figure_get_action_state(fid)
    if (act != 9 && act != 18) {
        return test272_fail('rest→walk want 9/18, got ' + act)
    }
    __log_marker('hippo_rest_to_walk_ok')

    // DYING (12) → corpse (149).
    __test_figure_set_action(fid, 12)
    __test_figure_set_wait_ticks(fid, 500)
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 149) {
        return test272_fail('dying→corpse want 149, got ' + __figure_get_action_state(fid))
    }
    __log_marker('hippo_dying_to_corpse_ok')

    // CHASE (21) timeout → RETURN (23) or WALK (9).
    city.figures.remove_figures(FIGURE_HIPPO)
    var fid2 = test_figure_create(FIGURE_HIPPO, 20, 20)
    if (!fid2) {
        return test272_fail('create2 failed')
    }
    test_figure_set_force_valid_animation(fid2, true)
    __test_figure_set_action(fid2, 21)
    __test_figure_set_wait_ticks(fid2, 0)
    __test_figure_action_perform(fid2)
    var a2 = __figure_get_action_state(fid2)
    if (a2 != 23 && a2 != 9) {
        return test272_fail('chase timeout want 23/9, got ' + a2)
    }
    __log_marker('hippo_chase_timeout_ok')

    // ANIMATE (26): mid-frame hold while wait > 0 stays in 26.
    city.figures.remove_figures(FIGURE_HIPPO)
    var fid3 = test_figure_create(FIGURE_HIPPO, 24, 24)
    if (!fid3) {
        return test272_fail('create3 failed')
    }
    test_figure_set_force_valid_animation(fid3, true)
    __test_figure_set_action(fid3, 26)
    __test_figure_set_wait_ticks(fid3, 20)
    __test_figure_action_perform(fid3)
    if (__figure_get_action_state(fid3) != 26) {
        return test272_fail('animate hold want 26, got ' + __figure_get_action_state(fid3))
    }
    __log_marker('hippo_animate_hold_ok')

    // ATTACK vs immigrant.
    city.figures.remove_figures(FIGURE_HIPPO)
    city.figures.remove_figures(FIGURE_IMMIGRANT)
    var prey = test_figure_create(FIGURE_IMMIGRANT, 22, 22)
    var fid4 = test_figure_create(FIGURE_HIPPO, 22, 22)
    if (!prey || !fid4) {
        return test272_fail('attack spawn failed')
    }
    test_figure_set_force_valid_animation(fid4, true)
    __test_figure_set_action(fid4, 18)
    if (__test_figure_combat_attack_at(fid4, 22, 22) != 1) {
        return test272_fail('combat_attack_at want in_attack')
    }
    if (__test_figure_get_opponent_id(fid4) != prey) {
        return test272_fail('opponent want prey=' + prey + ' got ' + __test_figure_get_opponent_id(fid4))
    }
    var dmg0 = __test_figure_get_damage(prey)
    for (var i = 0; i < 16; i++) {
        __test_figure_action_perform(fid4)
    }
    if (__test_figure_in_attack(fid4) != 1 && __test_figure_is_alive(prey) != 0) {
        return test272_fail('after attack ticks want still in_attack or prey dead')
    }
    if (__test_figure_is_alive(prey) && __test_figure_get_damage(prey) <= dmg0) {
        return test272_fail('prey damage want > ' + dmg0 + ' got ' + __test_figure_get_damage(prey))
    }
    __log_marker('hippo_attack_ok')

    __test272_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test272_ok) {
        return false
    }
    var markers = [
        'hippo_spawned_ok',
        'hippo_choose_ok',
        'hippo_rest_to_walk_ok',
        'hippo_dying_to_corpse_ok',
        'hippo_chase_timeout_ok',
        'hippo_animate_hold_ok',
        'hippo_attack_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:272] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

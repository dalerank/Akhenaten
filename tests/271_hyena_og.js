// FIGURE_HYENA: OG wild_predator_action(WILD_HYENA).
// Markers:
//   [test-marker] hyena_spawned_ok
//   [test-marker] hyena_choose_rest_or_idle_ok
//   [test-marker] hyena_idle_to_choose_ok
//   [test-marker] hyena_dying_to_corpse_ok
//   [test-marker] hyena_chase_timeout_ok
//   [test-marker] hyena_return_to_rest_ok
//   [test-marker] hyena_attack_ok

var __test271_ok = false

function test271_fail(msg) {
    __log_info_native('[test:271] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:271] hyena OG')
    test_reload_city_session('data/default.map')
    city.figures.remove_figures(FIGURE_HYENA)

    var fid = test_figure_create(FIGURE_HYENA, 12, 14)
    if (!fid) {
        return test271_fail('create failed')
    }
    test_figure_set_force_valid_animation(fid, true)

    // SPAWNED (24): invisible until wait expires → CHOOSE (8).
    __test_figure_set_action(fid, 24)
    __test_figure_set_wait_ticks(fid, 2)
    __test_figure_action_perform(fid)
    if (__test_figure_is_visible(fid) != 0) {
        return test271_fail('spawned want invisible, visible=' + __test_figure_is_visible(fid))
    }
    __test_figure_set_wait_ticks(fid, 0)
    __test_figure_action_perform(fid)
    var after_spawn = __figure_get_action_state(fid)
    if (after_spawn != 8 && after_spawn != 18 && after_spawn != 19) {
        return test271_fail('spawned→choose/rest/idle want 8/18/19, got ' + after_spawn)
    }
    if (__test_figure_is_visible(fid) != 1) {
        return test271_fail('after spawn want visible')
    }
    __log_marker('hyena_spawned_ok')

    // CHOOSE (8) → REST(18) or IDLE(19).
    __test_figure_set_action(fid, 8)
    __test_figure_action_perform(fid)
    var chosen = __figure_get_action_state(fid)
    if (chosen != 18 && chosen != 19) {
        return test271_fail('choose want 18/19, got ' + chosen)
    }
    __log_marker('hyena_choose_rest_or_idle_ok')

    // IDLE (19) wait 0 → CHOOSE (8).
    __test_figure_set_action(fid, 19)
    __test_figure_set_wait_ticks(fid, 0)
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 8) {
        return test271_fail('idle→choose want 8, got ' + __figure_get_action_state(fid))
    }
    __log_marker('hyena_idle_to_choose_ok')

    // DYING (12): after dying_ticks → corpse (149).
    __test_figure_set_action(fid, 12)
    __test_figure_set_wait_ticks(fid, 500)
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 149) {
        return test271_fail('dying→corpse want 149, got ' + __figure_get_action_state(fid))
    }
    __log_marker('hyena_dying_to_corpse_ok')

    // CHASE (21) timeout on frame advance → RETURN_TO_HERD (23) or WALK (9).
    city.figures.remove_figures(FIGURE_HYENA)
    var fid2 = test_figure_create(FIGURE_HYENA, 20, 20)
    if (!fid2) {
        return test271_fail('create2 failed')
    }
    test_figure_set_force_valid_animation(fid2, true)
    __test_figure_set_action(fid2, 21)
    __test_figure_set_wait_ticks(fid2, 0)
    var a2 = 21
    for (var i = 0; i < 20; i++) {
        __test_figure_action_perform(fid2)
        a2 = __figure_get_action_state(fid2)
        if (a2 != 21) {
            break
        }
    }
    if (a2 != 23 && a2 != 9 && a2 != 18) {
        return test271_fail('chase timeout want 23/9/18, got ' + a2)
    }
    __log_marker('hyena_chase_timeout_ok')

    // RETURN_TO_HERD (23) with no walkable herd tile → REST (18).
    city.figures.remove_figures(FIGURE_HYENA)
    var fid3 = test_figure_create(FIGURE_HYENA, 30, 30)
    if (!fid3) {
        return test271_fail('create3 failed')
    }
    test_figure_set_force_valid_animation(fid3, true)
    __test_figure_set_action(fid3, 23)
    __test_figure_action_perform(fid3)
    var a3 = __figure_get_action_state(fid3)
    if (a3 != 18 && a3 != 9) {
        return test271_fail('return_to_herd want 18/9, got ' + a3)
    }
    __log_marker('hyena_return_to_rest_ok')

    // ATTACK: hostile hyena vs citizen on same tile.
    city.figures.remove_figures(FIGURE_HYENA)
    city.figures.remove_figures(FIGURE_IMMIGRANT)
    var prey = test_figure_create(FIGURE_IMMIGRANT, 22, 22)
    var fid4 = test_figure_create(FIGURE_HYENA, 22, 22)
    if (!prey || !fid4) {
        return test271_fail('attack spawn failed')
    }
    test_figure_set_force_valid_animation(fid4, true)
    __test_figure_set_action(fid4, 18)
    if (__test_figure_combat_attack_at(fid4, 22, 22) != 1) {
        return test271_fail('combat_attack_at want in_attack')
    }
    if (__test_figure_get_opponent_id(fid4) != prey) {
        return test271_fail('opponent want prey=' + prey + ' got ' + __test_figure_get_opponent_id(fid4))
    }
    var dmg0 = __test_figure_get_damage(prey)
    for (var j = 0; j < 16; j++) {
        __test_figure_action_perform(fid4)
    }
    if (__test_figure_in_attack(fid4) != 1 && __test_figure_is_alive(prey) != 0) {
        return test271_fail('after attack ticks want still in_attack or prey dead')
    }
    if (__test_figure_is_alive(prey) && __test_figure_get_damage(prey) <= dmg0) {
        return test271_fail('prey damage want > ' + dmg0 + ' got ' + __test_figure_get_damage(prey))
    }
    __log_marker('hyena_attack_ok')

    __test271_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test271_ok) {
        return false
    }
    var markers = [
        'hyena_spawned_ok',
        'hyena_choose_rest_or_idle_ok',
        'hyena_idle_to_choose_ok',
        'hyena_dying_to_corpse_ok',
        'hyena_chase_timeout_ok',
        'hyena_return_to_rest_ok',
        'hyena_attack_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:271] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

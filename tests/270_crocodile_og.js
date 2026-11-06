// FIGURE_CROCODILE: OG figure_crocodile_action (0x0049D0F0).
// Markers:
//   [test-marker] croc_spawned_ok
//   [test-marker] croc_choose_rest_or_water_ok
//   [test-marker] croc_rest_to_walk_ok
//   [test-marker] croc_dying_to_corpse_ok
//   [test-marker] croc_chase_timeout_ok
//   [test-marker] croc_attack_ok

var __test270_ok = false

function test270_fail(msg) {
    __log_info_native('[test:270] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:270] crocodile OG')
    test_reload_city_session('data/default.map')
    city.figures.remove_figures(FIGURE_CROCODILE)

    var fid = test_figure_create(FIGURE_CROCODILE, 12, 14)
    if (!fid) {
        return test270_fail('create failed')
    }
    test_figure_set_force_valid_animation(fid, true)

    // SPAWNED (24): invisible until wait expires → CHOOSE (8) → REST(18)/WATER(19).
    __test_figure_set_action(fid, 24)
    __test_figure_set_wait_ticks(fid, 2)
    __test_figure_action_perform(fid)
    if (__test_figure_is_visible(fid) != 0) {
        return test270_fail('spawned want invisible, visible=' + __test_figure_is_visible(fid))
    }
    __test_figure_set_wait_ticks(fid, 0)
    __test_figure_action_perform(fid)
    var after_spawn = __figure_get_action_state(fid)
    if (after_spawn != 8 && after_spawn != 18 && after_spawn != 19) {
        return test270_fail('spawned→choose/rest/water want 8/18/19, got ' + after_spawn)
    }
    if (__test_figure_is_visible(fid) != 1) {
        return test270_fail('after spawn want visible')
    }
    __log_marker('croc_spawned_ok')

    // CHOOSE (8) → REST(18) or GO_TO_WATER(19).
    __test_figure_set_action(fid, 8)
    __test_figure_action_perform(fid)
    var chosen = __figure_get_action_state(fid)
    if (chosen != 18 && chosen != 19) {
        return test270_fail('choose want 18/19, got ' + chosen)
    }
    __log_marker('croc_choose_rest_or_water_ok')

    // REST (18) with wait 0 → WALK (9) near herd/tile (or stay REST with no_tile wait).
    __test_figure_set_action(fid, 18)
    __test_figure_set_wait_ticks(fid, 0)
    __test_figure_action_perform(fid)
    var act = __figure_get_action_state(fid)
    if (act != 9 && act != 18) {
        return test270_fail('rest→walk want 9 (or rest retry 18), got ' + act)
    }
    __log_marker('croc_rest_to_walk_ok')

    // DYING (12): after dying_ticks → corpse (149).
    __test_figure_set_action(fid, 12)
    __test_figure_set_wait_ticks(fid, 500)
    __test_figure_action_perform(fid)
    if (__figure_get_action_state(fid) != 149) {
        return test270_fail('dying→corpse want 149, got ' + __figure_get_action_state(fid))
    }
    __log_marker('croc_dying_to_corpse_ok')

    // CHASE (21) timeout → RETURN_TO_HERD (23) (or WALK 9 if walk_near succeeds).
    city.figures.remove_figures(FIGURE_CROCODILE)
    var fid2 = test_figure_create(FIGURE_CROCODILE, 20, 20)
    if (!fid2) {
        return test270_fail('create2 failed')
    }
    test_figure_set_force_valid_animation(fid2, true)
    __test_figure_set_action(fid2, 21)
    __test_figure_set_wait_ticks(fid2, 0)
    __test_figure_action_perform(fid2)
    var a2 = __figure_get_action_state(fid2)
    if (a2 != 23 && a2 != 9) {
        return test270_fail('chase timeout want 23/9, got ' + a2)
    }
    __log_marker('croc_chase_timeout_ok')

    // ATTACK: hostile croc vs citizen on same tile → in_attack + opponent + damage.
    city.figures.remove_figures(FIGURE_CROCODILE)
    city.figures.remove_figures(FIGURE_IMMIGRANT)
    var prey = test_figure_create(FIGURE_IMMIGRANT, 22, 22)
    var fid3 = test_figure_create(FIGURE_CROCODILE, 22, 22)
    if (!prey || !fid3) {
        return test270_fail('attack spawn failed')
    }
    test_figure_set_force_valid_animation(fid3, true)
    __test_figure_set_action(fid3, 18)
    if (__test_figure_combat_attack_at(fid3, 22, 22) != 1) {
        return test270_fail('combat_attack_at want in_attack')
    }
    if (__test_figure_get_opponent_id(fid3) != prey) {
        return test270_fail('opponent want prey=' + prey + ' got ' + __test_figure_get_opponent_id(fid3))
    }
    var dmg0 = __test_figure_get_damage(prey)
    for (var i = 0; i < 16; i++) {
        __test_figure_action_perform(fid3)
    }
    if (__test_figure_in_attack(fid3) != 1 && __test_figure_is_alive(prey) != 0) {
        return test270_fail('after attack ticks want still in_attack or prey dead')
    }
    if (__test_figure_is_alive(prey) && __test_figure_get_damage(prey) <= dmg0) {
        return test270_fail('prey damage want > ' + dmg0 + ' got ' + __test_figure_get_damage(prey))
    }
    __log_marker('croc_attack_ok')

    __test270_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test270_ok) {
        return false
    }
    var markers = [
        'croc_spawned_ok',
        'croc_choose_rest_or_water_ok',
        'croc_rest_to_walk_ok',
        'croc_dying_to_corpse_ok',
        'croc_chase_timeout_ok',
        'croc_attack_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:270] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

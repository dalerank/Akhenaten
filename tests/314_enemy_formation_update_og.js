// Enemy formation update vs OG formation_enemy_update (formation.c:520-719):
// - only the first formation of an invasion picks the target; every formation of it carries that target;
// - formations get battalion indices 0..n-1 in update order (they pick their gather spot by it);
// - with no building to attack, the first formation routs after 48 updates without a target.
// Markers:
//   [test-marker] enemy_formations_share_target_ok
//   [test-marker] enemy_formation_indices_ok
//   [test-marker] enemy_formation_no_target_rout_ok

function test314_fail(msg) {
    __log_info_native('[test:314] FAIL: ' + msg)
}

function test314_invade(size) {
    var mid_y = (__scenario_map.height / 2) | 0
    city.start_foreign_army_invasion({
        mode: ATTACK_TYPE_ENEMIES,
        enemy: ENEMY_0_BARBARIAN,
        size: size,
        invasion_id: 1,
        tilex: 2,
        tiley: mid_y,
        want_destroy_buildings: 0,
        invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
    })
}

function test314_states() {
    var ids = __test_enemy_formations()
    var out = []
    if (ids === '') {
        return out
    }
    var list = ids.split(',')
    for (var i = 0; i < list.length; i++) {
        var p = __test_enemy_formation_state(+list[i]).split(',')
        out.push({ id: +list[i], index: +p[1], bid: +p[2], x: +p[3], y: +p[4], wait: +p[5], no_target: +p[6] })
    }
    return out
}

function test314_shared_target() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    test_building_place(BUILDING_STORAGE_YARD, -1, -1)
    test_building_place(BUILDING_GRANARY, -1, -1)
    test314_invade(40)
}

function run_test() {
    __log_info_native('[test:314] enemy formation update OG')

    test314_shared_target()
    __test_enemy_formations_update()
    var states = test314_states()
    if (states.length < 2) {
        test314_fail('want several enemy formations, got ' + states.length)
    } else {
        var bid = states[0].bid
        var same = bid > 0
        for (var i = 1; i < states.length; i++) {
            same = same && states[i].bid == bid
        }
        if (same) {
            __log_marker('enemy_formations_share_target_ok')
        } else {
            test314_fail('targets differ: ' + JSON.stringify(states))
        }

        var seen = {}
        var ok = true
        for (var i = 0; i < states.length; i++) {
            ok = ok && states[i].index >= 0 && states[i].index < states.length && !seen[states[i].index]
            seen[states[i].index] = true
        }
        if (ok) {
            __log_marker('enemy_formation_indices_ok')
        } else {
            test314_fail('battalion indices: ' + JSON.stringify(states))
        }
    }

    // No buildings at all: nothing to attack.
    test_reload_city_session('data/default.map')
    test314_invade(8)
    var updates = 0
    var first = test314_states()
    while (updates < 60 && first.length > 0 && first[0].no_target <= 48) {
        __test_enemy_formations_update()
        updates++
        first = test314_states()
    }
    if (first.length == 0) {
        test314_fail('enemy formation vanished')
    } else if (first[0].no_target == 49 && updates == 49) {
        __log_marker('enemy_formation_no_target_rout_ok')
    } else {
        test314_fail('no-target counter ' + first[0].no_target + ' after ' + updates + ' updates, want 49 after 49')
    }

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('enemy_formations_share_target_ok') && __test_find_inlog('enemy_formation_indices_ok')
        && __test_find_inlog('enemy_formation_no_target_rout_ok')
}

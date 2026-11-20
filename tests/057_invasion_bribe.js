// Invasion bribe (Enhanced): flag ON → pay → army gone, no COMPLETED tag.
//
// Markers:
//   [test-marker] bribe_flag_off_refuse
//   [test-marker] bribe_ok
//   [test-marker] bribe_no_completed_tag
//   [test-marker] bribe_kingdome_banned

function run_test() {
    __log_info_native('[test:057] invasion bribe')
    test_ensure_city_session('data/default.map')

    __image_request_pak(PACK_ENEMY_BARBARIAN)
    __test_pump_frames(2)
    __test_clear_enemy_formations()

    var mid_y = ((__scenario_map.height / 2) | 0)
    var bribe_prev = game_features.get('gameplay_enhanced_invasion_bribe')
    var ar_prev = game_features.get('gameplay_enhanced_auto_resolve_invasions')

    function restore() {
        game_features.set('gameplay_enhanced_invasion_bribe', bribe_prev)
        game_features.set('gameplay_enhanced_auto_resolve_invasions', ar_prev)
        __test_clear_enemy_formations()
    }

    // --- flag OFF: refuse ---
    game_features.set('gameplay_enhanced_invasion_bribe', false)
    game_features.set('gameplay_enhanced_auto_resolve_invasions', false)
    var seq_off = city.start_foreign_army_invasion({
        invasion_id: 41,
        enemy: ENEMY_0_BARBARIAN,
        size: 6,
        tilex: 2,
        tiley: mid_y
    })
    __test_pump_frames(3)
    __test_set_treasury(50000)
    var refuse = __invasion_bribe_try(seq_off)
    var enemies_off = __test_count_enemy_figures()
    if (refuse == 0 && enemies_off > 0 && seq_off > 0) {
        __log_marker('bribe_flag_off_refuse')
    } else {
        __log_info_native('[test:057] flag OFF: try=' + refuse + ' enemies=' + enemies_off + ' seq=' + seq_off)
        __log_marker('bribe_flag_off_refuse_fail')
    }
    __test_clear_enemy_formations()

    // --- flag ON: pay + despawn, no completed chain ---
    game_features.set('gameplay_enhanced_invasion_bribe', true)
    city.create_chain_event({
        tag_id: 13801,
        type: EVENT_TYPE_REPUTATION_INCREASE,
        amount: 5
    })
    var kr_before = city.rating_kingdom
    __test_set_treasury(50000)
    var treasury_before = city.finance.treasury

    var seq = city.start_foreign_army_invasion({
        invasion_id: 42,
        enemy: ENEMY_0_BARBARIAN,
        size: 8,
        tilex: 2,
        tiley: mid_y,
        on_completed_tag: 13801
    })
    __test_pump_frames(4)

    var cost = __invasion_bribe_cost(seq)
    var allowed = __invasion_bribe_allowed(seq)
    var enemies_before = __test_count_enemy_figures()
    var try_ok = __invasion_bribe_try(seq)
    __test_pump_frames(2)
    __test_process_invasion_binds()

    var enemies_after = __test_count_enemy_figures()
    var treasury_after = city.finance.treasury
    var kr_after = city.rating_kingdom

    if (try_ok == 1 && allowed == 1 && cost > 0 && enemies_before > 0
            && enemies_after == 0
            && treasury_after == treasury_before - cost
            && kr_after == kr_before - 2) {
        __log_marker('bribe_ok')
    } else {
        __log_info_native('[test:057] bribe: try=' + try_ok + ' allowed=' + allowed
            + ' cost=' + cost + ' enemies ' + enemies_before + '->' + enemies_after
            + ' treasury ' + treasury_before + '->' + treasury_after
            + ' kr ' + kr_before + '->' + kr_after)
        __log_marker('bribe_ok_fail')
    }

    // Completed tag must NOT fire (+5 KR)
    if (kr_after == kr_before - 2) {
        __log_marker('bribe_no_completed_tag')
    } else {
        __log_info_native('[test:057] expected no completed tag, kr=' + kr_after)
        __log_marker('bribe_no_completed_tag_fail')
    }

    // --- kingdom army: banned (isolated spawn like tests/109) ---
    __test_clear_enemy_formations()
    __test_poof_kingdome_figures()
    __test_figures_update()
    __image_request_pak(PACK_ENEMY_EGYPTIAN)
    __test_pump_frames(4)
    game_features.set('gameplay_enhanced_invasion_bribe', true)
    game_features.set('gameplay_enhanced_auto_resolve_invasions', false)
    __test_set_treasury(50000)
    var seq_k = city.start_foreign_army_invasion({
        mode: ATTACK_TYPE_ENEMIES,
        enemy: ENEMY_3_EGYPTIAN,
        kind: INVASION_KIND_KINGDOME,
        size: 8,
        invasion_id: 24,
        tilex: 2,
        tiley: mid_y,
        want_destroy_buildings: 0,
        invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
    })
    __test_pump_frames(6)
    __test_figures_update()
    var k_soldiers = __test_city_kingdome_soldiers()
    var k_favour = __test_kingdome_invasion_favour_only()
    var k_allowed = __invasion_bribe_allowed(seq_k)
    var k_try = __invasion_bribe_try(seq_k)
    if (seq_k > 0 && k_favour == 1 && k_soldiers > 0 && k_allowed == 0 && k_try == 0) {
        __log_marker('bribe_kingdome_banned_ok')
    } else {
        __log_info_native('[test:057] kingdom ban: allowed=' + k_allowed + ' try=' + k_try
            + ' kingdome_soldiers=' + k_soldiers + ' favour_only=' + k_favour
            + ' enemy_figs=' + __test_count_enemy_figures() + ' seq=' + seq_k
            + ' kind_const=' + INVASION_KIND_KINGDOME)
        __log_marker('bribe_kingdome_banned_fail')
    }

    restore()
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('bribe_flag_off_refuse')
        && __test_find_inlog('bribe_ok')
        && __test_find_inlog('bribe_no_completed_tag')
        && __test_find_inlog('bribe_kingdome_banned_ok')
}

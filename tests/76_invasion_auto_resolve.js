// Auto-resolve invasions (Enhanced): flag ON → pending freeze → resolve by strength.
//
// Markers:
//   [test-marker] auto_resolve_flag_off_no_pending
//   [test-marker] auto_resolve_pending_ok
//   [test-marker] auto_resolve_frozen_ok
//   [test-marker] auto_resolve_lose_ok
//   [test-marker] auto_resolve_empty_cancel_ok
//   [test-marker] auto_resolve_queue_timer_ok
//   [test-marker] auto_resolve_flag_off_mid_ok
//   [test-marker] auto_resolve_uprising_excluded
//   [test-marker] auto_resolve_win_ok
//   [test-marker] auto_resolve_pharaoh_ok
//   [test-marker] auto_resolve_queue_full_ok
//   [test-marker] auto_resolve_saveload_ok | auto_resolve_saveload_skipped
//   [test-marker] auto_resolve_chain_spawn_ok

function run_test() {
    __log_info_native('[test:76] invasion auto-resolve')
    test_ensure_city_session('data/default.map')

    __image_request_pak(PACK_ENEMY_BARBARIAN)
    __test_pump_frames(2)
    __test_clear_enemy_formations()

    var mid_y = ((__scenario_map.height / 2) | 0)
    var flags_prev = game_features.get('gameplay_enhanced_auto_resolve_invasions')

    function restore() {
        __invasion_auto_resolve_test_set_player_strength(-1)
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_clear_enemy_formations()
    }

    // --- flag OFF: no pending ---
    game_features.set('gameplay_enhanced_auto_resolve_invasions', false)
    var seq_off = city.start_foreign_army_invasion({
        invasion_id: 11,
        enemy: ENEMY_0_BARBARIAN,
        size: 8,
        tilex: 2,
        tiley: mid_y
    })
    __test_pump_frames(3)
    if (__invasion_auto_resolve_pending_count() == 0 && seq_off > 0) {
        __log_marker('auto_resolve_flag_off_no_pending')
    } else {
        __log_info_native('[test:76] expected no pending when flag OFF, count='
            + __invasion_auto_resolve_pending_count())
        __log_marker('auto_resolve_flag_off_no_pending_fail')
    }
    __test_clear_enemy_formations()

    // --- flag ON: pending + freeze ---
    game_features.set('gameplay_enhanced_auto_resolve_invasions', true)
    city.create_chain_event({
        tag_id: 7201,
        type: EVENT_TYPE_REPUTATION_INCREASE,
        amount: 2
    })
    var kr_before = city.rating_kingdom
    var seq = city.start_foreign_army_invasion({
        invasion_id: 12,
        enemy: ENEMY_0_BARBARIAN,
        size: 6,
        tilex: 2,
        tiley: mid_y,
        on_completed_tag: 7201
    })
    __test_pump_frames(4)

    if (__invasion_auto_resolve_pending_count() >= 1 && seq > 0) {
        __log_marker('auto_resolve_pending_ok')
    } else {
        __log_info_native('[test:76] expected pending after spawn, count='
            + __invasion_auto_resolve_pending_count() + ' seq=' + seq)
        __log_marker('auto_resolve_pending_fail')
    }

    if (__invasion_auto_resolve_is_seq_frozen(seq) == 1
            || __invasion_auto_resolve_is_frozen(12) == 1) {
        __log_marker('auto_resolve_frozen_ok')
    } else {
        __log_marker('auto_resolve_frozen_fail')
    }

    var days = __invasion_auto_resolve_head_days_left()
    if (days != 8) {
        __log_info_native('[test:76] expected days_left=8, got ' + days)
    }

    // Resolve now — empty fort → lose (−10 KR), no completed tag (+2)
    var enemy_before = __invasion_auto_resolve_enemy_strength()
    var try_ok = __invasion_auto_resolve_try_now()
    __test_pump_frames(2)

    var enemy_after = __test_count_enemy_figures()
    var pending_after = __invasion_auto_resolve_pending_count()
    var kr_after = city.rating_kingdom

    if (try_ok == 1 && pending_after == 0 && enemy_after == 0
            && kr_after == kr_before - 10 && enemy_before > 0) {
        __log_marker('auto_resolve_lose_ok')
    } else {
        __log_info_native('[test:76] resolve: try=' + try_ok + ' pending=' + pending_after
            + ' enemies=' + enemy_after + ' kr ' + kr_before + '->' + kr_after
            + ' enemy_str=' + enemy_before)
        __log_marker('auto_resolve_lose_fail')
    }

    // --- empty army Resolve → cancel, no fake +25 KR ---
    __test_clear_enemy_formations()
    game_features.set('gameplay_enhanced_auto_resolve_invasions', true)
    var kr_empty = city.rating_kingdom
    var seq_empty = city.start_foreign_army_invasion({
        invasion_id: 31,
        enemy: ENEMY_0_BARBARIAN,
        size: 4,
        tilex: 2,
        tiley: mid_y,
        on_completed_tag: 7201
    })
    __test_pump_frames(3)
    __test_clear_enemy_formations()
    var pending_after_clear = __invasion_auto_resolve_pending_count()
    var kr_empty_after = city.rating_kingdom
    if (pending_after_clear == 0 && kr_empty_after == kr_empty && seq_empty > 0) {
        __log_marker('auto_resolve_empty_cancel_ok')
    } else {
        __log_info_native('[test:76] empty cancel: pending_after_clear=' + pending_after_clear
            + ' kr ' + kr_empty + '->' + kr_empty_after)
        __log_marker('auto_resolve_empty_cancel_fail')
    }

    // --- head-only timer: 2 waves ---
    __test_clear_enemy_formations()
    game_features.set('gameplay_enhanced_auto_resolve_invasions', true)
    var seq_a = city.start_foreign_army_invasion({
        invasion_id: 21,
        enemy: ENEMY_0_BARBARIAN,
        size: 4,
        tilex: 2,
        tiley: mid_y
    })
    var seq_b = city.start_foreign_army_invasion({
        invasion_id: 22,
        enemy: ENEMY_0_BARBARIAN,
        size: 4,
        tilex: 3,
        tiley: mid_y
    })
    __test_pump_frames(3)
    var days_a0 = __invasion_auto_resolve_head_days_left()
    __invasion_auto_resolve_update_day() // arms grace (no decrement)
    __invasion_auto_resolve_update_day()
    __invasion_auto_resolve_update_day()
    var days_a3 = __invasion_auto_resolve_head_days_left()
    var pending_2 = __invasion_auto_resolve_pending_count()
    if (pending_2 == 2 && days_a0 == 8 && days_a3 == 6
            && __invasion_auto_resolve_is_seq_frozen(seq_a) == 1
            && __invasion_auto_resolve_is_seq_frozen(seq_b) == 1) {
        __log_marker('auto_resolve_queue_timer_ok')
    } else {
        __log_info_native('[test:76] queue timer: pending=' + pending_2
            + ' days ' + days_a0 + '->' + days_a3
            + ' seq_a=' + seq_a + ' seq_b=' + seq_b)
        __log_marker('auto_resolve_queue_timer_fail')
    }

    game_features.set('gameplay_enhanced_auto_resolve_invasions', false)
    if (__invasion_auto_resolve_pending_count() == 0) {
        __log_marker('auto_resolve_flag_off_mid_ok')
    } else {
        __log_marker('auto_resolve_flag_off_mid_fail')
    }
    __test_clear_enemy_formations()
    game_features.set('gameplay_enhanced_auto_resolve_invasions', true)

    // Natives should not enqueue
    __test_clear_enemy_formations()
    city.start_foreign_army_invasion({
        invasion_id: 13,
        mode: ATTACK_TYPE_NATIVES,
        size: 5,
        tilex: 3,
        tiley: mid_y
    })
    __test_pump_frames(3)
    if (__invasion_auto_resolve_pending_count() == 0) {
        __log_marker('auto_resolve_uprising_excluded')
    } else {
        __log_info_native('[test:76] natives should not enqueue pending')
        __log_marker('auto_resolve_uprising_excluded_fail')
    }

    // --- win: mock player strength >= enemy → +25 KR + completed tag ---
    __test_clear_enemy_formations()
    game_features.set('gameplay_enhanced_auto_resolve_invasions', true)
    city.create_chain_event({
        tag_id: 7202,
        type: EVENT_TYPE_REPUTATION_INCREASE,
        amount: 3
    })
    var kr_win_before = city.rating_kingdom
    var seq_win = city.start_foreign_army_invasion({
        invasion_id: 41,
        enemy: ENEMY_0_BARBARIAN,
        size: 4,
        tilex: 2,
        tiley: mid_y,
        on_completed_tag: 7202
    })
    __test_pump_frames(3)
    var enemy_win = __invasion_auto_resolve_enemy_strength()
    __invasion_auto_resolve_test_set_player_strength(enemy_win + 10)
    var try_win = __invasion_auto_resolve_try_now()
    __test_pump_frames(2)
    __invasion_auto_resolve_test_set_player_strength(-1)
    var kr_win_after = city.rating_kingdom
    if (try_win == 1 && __invasion_auto_resolve_pending_count() == 0
            && __test_count_enemy_figures() == 0
            && kr_win_after == kr_win_before + 25 + 3 && seq_win > 0) {
        __log_marker('auto_resolve_win_ok')
    } else {
        __log_info_native('[test:76] win: try=' + try_win + ' pending='
            + __invasion_auto_resolve_pending_count()
            + ' enemies=' + __test_count_enemy_figures()
            + ' kr ' + kr_win_before + '->' + kr_win_after
            + ' enemy_str=' + enemy_win)
        __log_marker('auto_resolve_win_fail')
    }

    // --- Pharaoh kind enqueues ---
    __test_clear_enemy_formations()
    game_features.set('gameplay_enhanced_auto_resolve_invasions', true)
    __image_request_pak(PACK_ENEMY_EGYPTIAN)
    var seq_ph = city.start_foreign_army_invasion({
        invasion_id: 42,
        enemy: ENEMY_3_EGYPTIAN,
        size: 4,
        tilex: 2,
        tiley: mid_y
    })
    __test_pump_frames(4)
    if (seq_ph > 0 && __invasion_auto_resolve_pending_count() >= 1
            && __invasion_auto_resolve_is_seq_frozen(seq_ph) == 1) {
        __log_marker('auto_resolve_pharaoh_ok')
    } else {
        __log_info_native('[test:76] pharaoh: seq=' + seq_ph
            + ' pending=' + __invasion_auto_resolve_pending_count())
        __log_marker('auto_resolve_pharaoh_fail')
    }
    __test_clear_enemy_formations()
    // clear may sweep pending
    game_features.set('gameplay_enhanced_auto_resolve_invasions', false)
    game_features.set('gameplay_enhanced_auto_resolve_invasions', true)

    // --- queue full: 8 pending, 9th stays manual (not frozen) ---
    __test_clear_enemy_formations()
    var full_seqs = []
    var i
    for (i = 0; i < 8; i++) {
        full_seqs.push(city.start_foreign_army_invasion({
            invasion_id: 50 + i,
            enemy: ENEMY_0_BARBARIAN,
            size: 2,
            tilex: 2 + (i % 4),
            tiley: mid_y
        }))
        __test_pump_frames(1)
    }
    var pending_full = __invasion_auto_resolve_pending_count()
    var seq_overflow = city.start_foreign_army_invasion({
        invasion_id: 59,
        enemy: ENEMY_0_BARBARIAN,
        size: 2,
        tilex: 6,
        tiley: mid_y
    })
    __test_pump_frames(2)
    var pending_after_overflow = __invasion_auto_resolve_pending_count()
    if (pending_full == 8 && pending_after_overflow == 8 && seq_overflow > 0
            && __invasion_auto_resolve_is_seq_frozen(seq_overflow) == 0) {
        __log_marker('auto_resolve_queue_full_ok')
    } else {
        __log_info_native('[test:76] queue full: pending ' + pending_full + '->'
            + pending_after_overflow + ' overflow_frozen='
            + __invasion_auto_resolve_is_seq_frozen(seq_overflow))
        __log_marker('auto_resolve_queue_full_fail')
    }
    game_features.set('gameplay_enhanced_auto_resolve_invasions', false)
    __test_clear_enemy_formations()
    game_features.set('gameplay_enhanced_auto_resolve_invasions', true)

    // --- save/load pending ---
    __test_clear_enemy_formations()
    var seq_sl = city.start_foreign_army_invasion({
        invasion_id: 61,
        enemy: ENEMY_0_BARBARIAN,
        size: 3,
        tilex: 2,
        tiley: mid_y
    })
    __test_pump_frames(3)
    var days_sl = __invasion_auto_resolve_head_days_left()
    var save_name = 'test_76_auto_resolve.svx'
    if (!__test_save_memory(save_name)) {
        __log_marker('auto_resolve_saveload_skipped')
    } else if (!__test_load_memory(save_name)) {
        __test_drop_memory_save(save_name)
        __log_marker('auto_resolve_saveload_skipped')
    } else {
        __test_drop_memory_save(save_name)
        game_features.set('gameplay_enhanced_auto_resolve_invasions', true)
        if (__invasion_auto_resolve_pending_count() >= 1
                && __invasion_auto_resolve_is_seq_frozen(seq_sl) == 1
                && __invasion_auto_resolve_head_days_left() == days_sl) {
            __log_marker('auto_resolve_saveload_ok')
        } else {
            __log_info_native('[test:76] saveload: pending='
                + __invasion_auto_resolve_pending_count()
                + ' frozen=' + __invasion_auto_resolve_is_seq_frozen(seq_sl)
                + ' days=' + __invasion_auto_resolve_head_days_left())
            __log_marker('auto_resolve_saveload_fail')
        }
    }
    game_features.set('gameplay_enhanced_auto_resolve_invasions', false)
    __test_clear_enemy_formations()
    game_features.set('gameplay_enhanced_auto_resolve_invasions', true)

    // --- AC13: win then another wave enqueues (no double-KR / stuck resolving) ---
    __test_clear_enemy_formations()
    city.create_chain_event({
        tag_id: 7211,
        type: EVENT_TYPE_REPUTATION_INCREASE,
        amount: 1
    })
    var kr_ch = city.rating_kingdom
    var seq_ch = city.start_foreign_army_invasion({
        invasion_id: 71,
        enemy: ENEMY_0_BARBARIAN,
        size: 3,
        tilex: 2,
        tiley: mid_y,
        on_completed_tag: 7211
    })
    __test_pump_frames(3)
    var e_ch = __invasion_auto_resolve_enemy_strength()
    __invasion_auto_resolve_test_set_player_strength(e_ch + 5)
    var try_ch = __invasion_auto_resolve_try_now()
    // Follow-up wave after win (simulates mission chain side-effect).
    var seq_follow = city.start_foreign_army_invasion({
        invasion_id: 72,
        enemy: ENEMY_0_BARBARIAN,
        size: 2,
        tilex: 4,
        tiley: mid_y
    })
    __test_pump_frames(2)
    __invasion_auto_resolve_test_set_player_strength(-1)
    var kr_ch_after = city.rating_kingdom
    if (try_ch == 1 && seq_follow > 0
            && __invasion_auto_resolve_pending_count() == 1
            && __invasion_auto_resolve_is_seq_frozen(seq_follow) == 1
            && kr_ch_after == kr_ch + 25 + 1) {
        __log_marker('auto_resolve_chain_spawn_ok')
    } else {
        __log_info_native('[test:76] chain: try=' + try_ch + ' pending='
            + __invasion_auto_resolve_pending_count()
            + ' kr ' + kr_ch + '->' + kr_ch_after
            + ' follow=' + seq_follow)
        __log_marker('auto_resolve_chain_spawn_fail')
    }

    restore()
    __test_signal_ready()
}

function check_valid() {
    var required = [
        'auto_resolve_flag_off_no_pending',
        'auto_resolve_pending_ok',
        'auto_resolve_frozen_ok',
        'auto_resolve_lose_ok',
        'auto_resolve_empty_cancel_ok',
        'auto_resolve_queue_timer_ok',
        'auto_resolve_flag_off_mid_ok',
        'auto_resolve_uprising_excluded',
        'auto_resolve_win_ok',
        'auto_resolve_pharaoh_ok',
        'auto_resolve_queue_full_ok',
        'auto_resolve_chain_spawn_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        var marker = '[test-marker] ' + required[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:76] missing marker: ' + marker)
            return false
        }
    }
    if (__test_find_inlog('[test-marker] auto_resolve_saveload_ok')) {
        return true
    }
    if (__test_find_inlog('[test-marker] auto_resolve_saveload_skipped')) {
        return true
    }
    __log_info_native('[test:76] missing saveload ok/skip marker')
    return false
}

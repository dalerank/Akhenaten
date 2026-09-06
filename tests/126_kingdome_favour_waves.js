// Favour-KR integral: two KINGDOME waves accumulate size; invented 10% mounted
// share yields ≥1 mounted when adjusted size ≥ 10; wipe without +10 KR.
// Markers:
//   [test-marker] favour_waves_spawn1_ok
//   [test-marker] favour_waves_mounted_ok
//   [test-marker] favour_waves_accumulate_ok
//   [test-marker] favour_waves_wipe_ok
//   [test-marker] favour_waves_all_ok

function count_live(ftype) {
    return __test_count_figures(ftype)
}

function count_kingdome_live() {
    return count_live(FIGURE_ENEMY_KINGDOME_JAVELIN)
        + count_live(FIGURE_ENEMY_KINGDOME_INFANTRY)
        + count_live(FIGURE_ENEMY_KINGDOME_MOUNTED)
}

function run_test() {
    __log_info_native('[test:126] kingdom favour two-wave + mounted share')
    test_ensure_city_session('data/default.map')

    __image_request_pak(PACK_ENEMY_EGYPTIAN)
    __test_pump_frames(2)
    // The city session is shared with every earlier test: drop leftover invasion bookkeeping.
    __test_kingdome_invasion_reset()
    __test_clear_enemy_formations()

    var flags_prev = game_features.get('gameplay_enhanced_auto_resolve_invasions')
    game_features.set('gameplay_enhanced_auto_resolve_invasions', false)

    var mid_y = ((__scenario_map.height / 2) | 0)
    var kr_before = city.rating_kingdom

    // size 50 → even very-easy (40%) yields adjusted ≥ 10 → n3 ≥ 1 mounted.
    var seq1 = city.start_foreign_army_invasion({
        mode: ATTACK_TYPE_ENEMIES,
        enemy: ENEMY_3_EGYPTIAN,
        kind: INVASION_KIND_KINGDOME,
        size: 50,
        invasion_id: 26,
        tilex: 2,
        tiley: mid_y,
        want_destroy_buildings: 0,
        invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
    })
    __test_pump_frames(4)
    // process_invasion() clears the slot when kingdome_soldiers is still 0, and that counter is
    // rebuilt by the figure pass -- pump_frames alone often advances 0 sim ticks.
    __test_figures_update()

    if (!seq1 || seq1 <= 0) {
        __log_info_native('[test:126] wave1 spawn failed seq=' + seq1)
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    var size1 = __test_kingdome_invasion_size()
    if (__test_kingdome_invasion_favour_only() != 1 || size1 <= 0) {
        __log_info_native('[test:126] wave1 bookkeeping favour_only='
            + __test_kingdome_invasion_favour_only() + ' size=' + size1)
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    __log_marker('favour_waves_spawn1_ok')

    var mounted = count_live(FIGURE_ENEMY_KINGDOME_MOUNTED)
    if (size1 >= 10 && mounted <= 0) {
        __log_info_native('[test:126] want mounted>0 for size>=10, size='
            + size1 + ' mounted=' + mounted)
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    __log_marker('favour_waves_mounted_ok')

    var seq2 = city.start_foreign_army_invasion({
        mode: ATTACK_TYPE_ENEMIES,
        enemy: ENEMY_3_EGYPTIAN,
        kind: INVASION_KIND_KINGDOME,
        size: 20,
        invasion_id: 27,
        tilex: 2,
        tiley: mid_y + 2,
        want_destroy_buildings: 0,
        invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
    })
    __test_pump_frames(4)
    __test_figures_update()

    if (!seq2 || seq2 <= 0) {
        __log_info_native('[test:126] wave2 spawn failed seq=' + seq2)
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    var size2 = __test_kingdome_invasion_size()
    if (size2 <= size1 || __test_kingdome_invasion_favour_only() != 1) {
        __log_info_native('[test:126] accumulate failed size1=' + size1
            + ' size2=' + size2 + ' favour=' + __test_kingdome_invasion_favour_only())
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    __log_marker('favour_waves_accumulate_ok')

    __test_clear_enemy_formations()
    __test_poof_kingdome_figures()
    // pump_frames often advances 0 sim ticks (tick_timer_ms); force update so
    // DEAD figures delete and kingdome_soldiers recounts to 0.
    __test_figures_update()
    __test_figures_update()
    if (__test_city_kingdome_soldiers() != 0 || count_kingdome_live() != 0) {
        __test_poof_kingdome_figures()
        __test_figures_update()
    }
    if (__test_city_kingdome_soldiers() != 0 || count_kingdome_live() != 0) {
        __log_info_native('[test:126] kingdom figures still on map: live='
            + count_kingdome_live()
            + ' kingdome_soldiers=' + __test_city_kingdome_soldiers())
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    __test_kingdome_set_kills_to_size()
    __test_process_kingdome_invasion()

    if (__test_kingdome_invasion_favour_only() != 0 || __test_kingdome_invasion_size() != 0) {
        __log_info_native('[test:126] wipe incomplete favour_only='
            + __test_kingdome_invasion_favour_only()
            + ' size=' + __test_kingdome_invasion_size())
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }

    var kr_after = city.rating_kingdom
    if (kr_after != kr_before) {
        __log_info_native('[test:126] KR changed on favour wipe: '
            + kr_before + ' -> ' + kr_after)
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    __log_marker('favour_waves_wipe_ok')
    __log_marker('favour_waves_all_ok')

    game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
    __test_clear_enemy_formations()
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'favour_waves_spawn1_ok',
        'favour_waves_mounted_ok',
        'favour_waves_accumulate_ok',
        'favour_waves_wipe_ok',
        'favour_waves_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:126] missing marker: ' + marker)
            return false
        }
    }
    return true
}

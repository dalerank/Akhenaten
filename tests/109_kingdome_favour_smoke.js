// Favour-KR smoke: INVASION_KIND_KINGDOME → figures 55–57, favour_only bookkeeping,
// wipe without Caesar respect (+10 KR).
// Markers:
//   [test-marker] favour_smoke_spawn_ok
//   [test-marker] favour_smoke_type_ok
//   [test-marker] favour_smoke_bookkeeping_ok
//   [test-marker] favour_smoke_wipe_ok
//   [test-marker] favour_smoke_all_ok

function run_test() {
    __log_info_native('[test:109] kingdom favour invasion smoke')
    test_ensure_city_session('data/default.map')

    __image_request_pak(PACK_ENEMY_EGYPTIAN)
    __test_pump_frames(2)
    __test_clear_enemy_formations()
    // The city session is shared with every earlier test: drop leftover invasion bookkeeping.
    __test_kingdome_invasion_reset()

    // Disable auto-resolve so wipe path is manual kill tally.
    var flags_prev = game_features.get('gameplay_enhanced_auto_resolve_invasions')
    game_features.set('gameplay_enhanced_auto_resolve_invasions', false)

    var mid_y = ((__scenario_map.height / 2) | 0)
    var kr_before = city.rating_kingdom

    var seq = city.start_foreign_army_invasion({
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
    __test_pump_frames(4)

    if (!seq || seq <= 0) {
        __log_info_native('[test:109] spawn failed seq=' + seq)
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    __log_marker('favour_smoke_spawn_ok')

    __test_pump_frames(2)
    // pump_frames often advances 0 sim ticks, and the counter is rebuilt by the figure pass.
    __test_figures_update()
    var ks = __test_city_kingdome_soldiers()
    if (ks <= 0) {
        __log_info_native('[test:109] kingdome_soldiers=0 after spawn')
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    __log_marker('favour_smoke_type_ok')

    if (__test_kingdome_invasion_favour_only() != 1 || __test_kingdome_invasion_size() <= 0) {
        __log_info_native('[test:109] bookkeeping favour_only='
            + __test_kingdome_invasion_favour_only()
            + ' size=' + __test_kingdome_invasion_size())
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    __log_marker('favour_smoke_bookkeeping_ok')

    // Wipe army. Poof (not kill — DYING still tallies kingdome_soldiers) + force
    // figures.update: pump_frames often yields 0 sim ticks under integraltests.
    __test_clear_enemy_formations()
    __test_poof_kingdome_figures()
    __test_figures_update()
    __test_figures_update()
    if (__test_city_kingdome_soldiers() != 0) {
        __test_poof_kingdome_figures()
        __test_figures_update()
    }
    if (__test_city_kingdome_soldiers() != 0) {
        __log_info_native('[test:109] soldiers still on map after clear: '
            + __test_city_kingdome_soldiers())
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    __test_kingdome_set_kills_to_size()
    __test_process_kingdome_invasion()

    if (__test_kingdome_invasion_favour_only() != 0 || __test_kingdome_invasion_size() != 0) {
        __log_info_native('[test:109] wipe incomplete favour_only='
            + __test_kingdome_invasion_favour_only()
            + ' size=' + __test_kingdome_invasion_size())
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }

    var kr_after = city.rating_kingdom
    if (kr_after != kr_before) {
        __log_info_native('[test:109] KR changed on favour wipe: '
            + kr_before + ' -> ' + kr_after)
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    __log_marker('favour_smoke_wipe_ok')
    __log_marker('favour_smoke_all_ok')

    game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
    __test_clear_enemy_formations()
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'favour_smoke_spawn_ok',
        'favour_smoke_type_ok',
        'favour_smoke_bookkeeping_ok',
        'favour_smoke_wipe_ok',
        'favour_smoke_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:109] missing marker: ' + marker)
            return false
        }
    }
    return true
}

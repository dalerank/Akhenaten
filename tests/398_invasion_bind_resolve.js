// Invasion bind: spawn with on_completed_tag → wipe → fire chain (same month).
// History ring records spawn.
//
// Markers:
//   [test-marker] invasion_bind_spawn_ok
//   [test-marker] invasion_bind_no_sync_chain
//   [test-marker] invasion_bind_resolve_ok
//   [test-marker] invasion_bind_history_ok

function run_test() {
    __log_info_native('[test:398] invasion bind resolve + history')
    test_ensure_city_session('data/default.map')

    __image_request_pak(PACK_ENEMY_BARBARIAN)
    __test_pump_frames(2)
    __test_clear_enemy_formations()

    var mid_y = ((__scenario_map.height / 2) | 0)
    var kr_before = city.rating_kingdom
    var hist_before = city.invasion_history_count()

    city.create_chain_event({
        tag_id: 5001,
        type: EVENT_TYPE_REPUTATION_INCREASE,
        amount: 3
    })

    var seq = city.start_foreign_army_invasion({
        invasion_id: 7,
        enemy: ENEMY_0_BARBARIAN,
        size: 10,
        tilex: 2,
        tiley: mid_y,
        want_destroy_buildings: 10,
        invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM,
        on_completed_tag: 5001
    })
    __test_pump_frames(4)

    var enemy_figs = __test_count_enemy_figures()
    var formations = city.num_enemy_formations
    __log_info_native('[test:398] after spawn seq=' + seq + ' figures=' + enemy_figs + ' formations=' + formations)
    if (enemy_figs > 0 || formations > 0) {
        __log_marker('invasion_bind_spawn_ok')
    } else {
        __log_info_native('[test:398] expected enemy figures/formations > 0 after spawn')
        __log_marker('invasion_bind_spawn_fail')
    }

    if (city.rating_kingdom == kr_before) {
        __log_marker('invasion_bind_no_sync_chain')
    } else {
        __log_info_native('[test:398] KR changed on spawn: ' + kr_before + ' -> ' + city.rating_kingdom)
        __log_marker('invasion_bind_no_sync_chain_fail')
    }

    if (city.invasion_history_count() > hist_before && seq > 0) {
        __log_marker('invasion_bind_history_ok')
    } else {
        __log_info_native('[test:398] history count=' + city.invasion_history_count() + ' seq=' + seq)
        __log_marker('invasion_bind_history_fail')
    }

    // seen tick, then wipe, then resolve
    __test_process_invasion_binds()
    __test_clear_enemy_formations()
    __test_pump_frames(2)
    __test_process_invasion_binds()

    if (city.rating_kingdom == kr_before + 3) {
        __log_marker('invasion_bind_resolve_ok')
    } else {
        __log_info_native('[test:398] expected KR ' + (kr_before + 3) + ' after bind resolve, got ' + city.rating_kingdom)
        __log_marker('invasion_bind_resolve_fail:' + city.rating_kingdom)
    }

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'invasion_bind_spawn_ok',
        'invasion_bind_no_sync_chain',
        'invasion_bind_history_ok',
        'invasion_bind_resolve_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:398] missing marker: ' + marker)
            return false
        }
    }
    return true
}

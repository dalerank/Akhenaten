// Pharaoh does not auto-spawn Caesar-3 wrath armies at low KR. Campaign missions
// that punish KR=0 use JS favour ticks (Timna+); Men-nefer has none.
// Markers:
//   [test-marker] no_wrath_countdown_ok
//   [test-marker] no_wrath_spawn_ok
//   [test-marker] no_wrath_all_ok

function run_test() {
    __log_info_native('[test:203] no Caesar wrath auto-invasion at low KR')
    test_ensure_city_session('data/default.map')

    __test_clear_enemy_formations()
    __test_kingdome_invasion_reset()
    __test_kingdom_set_rating(2)

    var flags_prev = game_features.get('gameplay_enhanced_auto_resolve_invasions')
    game_features.set('gameplay_enhanced_auto_resolve_invasions', false)

    __test_process_kingdome_invasion()
    if (__test_kingdome_invasion_days_until() != 0) {
        __log_info_native('[test:203] countdown armed days='
            + __test_kingdome_invasion_days_until())
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    __log_marker('no_wrath_countdown_ok')

    var i
    for (i = 0; i < 200; i++) {
        __test_process_kingdome_invasion()
    }

    if (__test_kingdome_invasion_size() != 0 || __test_city_kingdome_soldiers() != 0
        || __test_kingdome_invasion_days_until() != 0) {
        __log_info_native('[test:203] spawned size='
            + __test_kingdome_invasion_size()
            + ' soldiers=' + __test_city_kingdome_soldiers()
            + ' days=' + __test_kingdome_invasion_days_until())
        game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
        __test_signal_ready()
        return
    }
    __log_marker('no_wrath_spawn_ok')
    __log_marker('no_wrath_all_ok')

    game_features.set('gameplay_enhanced_auto_resolve_invasions', flags_prev)
    __test_kingdome_invasion_reset()
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'no_wrath_countdown_ok',
        'no_wrath_spawn_ok',
        'no_wrath_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:203] missing marker: ' + marker)
            return false
        }
    }
    return true
}

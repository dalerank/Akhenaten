// Kingdom favour-army figures (55–57) — register + spawn/action + city tally.
// INVASION_KIND_KINGDOME remaps egyptian slots → these types (pause/retreat/kill).
// Markers:
//   [test-marker] kingdome_army_control_ok
//   [test-marker] kingdome_army_registered_ok
//   [test-marker] kingdome_army_spawn_ok
//   [test-marker] kingdome_army_count_ok
//   [test-marker] kingdome_army_all_ok

function run_test() {
    __log_info_native('[test:014] kingdom army figures (ES6)')
    test_ensure_city_session('data/default.map')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_SPEAR)) {
        __log_info_native('[test:014] control failed: egyptian spear not registered')
        __test_signal_ready()
        return
    }
    __log_marker('kingdome_army_control_ok')

    var types = [
        FIGURE_ENEMY_KINGDOME_JAVELIN,
        FIGURE_ENEMY_KINGDOME_INFANTRY,
        FIGURE_ENEMY_KINGDOME_MOUNTED
    ]
    for (var i = 0; i < types.length; i++) {
        if (!__test_enemy_figure_registered(types[i])) {
            __log_info_native('[test:014] not registered: ' + types[i])
            __test_signal_ready()
            return
        }
    }
    __log_marker('kingdome_army_registered_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var spawned = []
    for (var j = 0; j < types.length; j++) {
        var eid = test_figure_create(types[j], cx + j, cy)
        if (!eid || !__figure_is_valid(eid) || !__test_figure_is_enemy(eid)) {
            __log_info_native('[test:014] spawn failed type ' + types[j])
            __test_signal_ready()
            return
        }
        if (__figure_get_type(eid) != types[j]) {
            __log_info_native('[test:014] wrong type after create ' + types[j])
            __test_signal_ready()
            return
        }
        __test_figure_action_perform(eid)
        if (!__figure_is_valid(eid)) {
            __log_info_native('[test:014] poofed on first action type ' + types[j])
            __test_signal_ready()
            return
        }
        spawned.push(eid)
    }
    __log_marker('kingdome_army_spawn_ok')

    // Kingdom figures tally kingdome_soldiers (not enemies).
    var ks = __test_city_kingdome_soldiers()
    if (ks < types.length) {
        __log_info_native('[test:014] kingdome_soldiers want >=' + types.length + ' got ' + ks)
        __test_signal_ready()
        return
    }
    __log_marker('kingdome_army_count_ok')

    for (var k = 0; k < spawned.length; k++) {
        __test_figure_kill(spawned[k])
    }
    __log_marker('kingdome_army_all_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'kingdome_army_control_ok',
        'kingdome_army_registered_ok',
        'kingdome_army_spawn_ok',
        'kingdome_army_count_ok',
        'kingdome_army_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:014] missing marker: ' + marker)
            return false
        }
    }
    return true
}

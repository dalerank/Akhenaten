// Egyptian camel + mounted archer — register + spawn smoke.
// FIGURE_ENEMY_EGYPTIAN_CAMEL (46) / MOUNTED_ARCHER (52) have METAINFO leaves;
// not in enemy_egyptian.figure_types[]. Sound branches already know these types.
// Markers:
//   [test-marker] egyptian_mount_control_ok
//   [test-marker] egyptian_camel_registered_ok
//   [test-marker] egyptian_mounted_archer_registered_ok
//   [test-marker] egyptian_camel_spawn_ok
//   [test-marker] egyptian_mounted_archer_spawn_ok
//   [test-marker] egyptian_mount_all_ok

function run_test() {
    __log_info_native('[test:555] egyptian camel/mounted archer (ES3)')
    test_ensure_city_session('data/default.map')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_CHARIOT)) {
        __log_info_native('[test:555] control failed: chariot not registered')
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_mount_control_ok')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_CAMEL)) {
        __log_info_native('[test:555] FIGURE_ENEMY_EGYPTIAN_CAMEL not registered')
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_camel_registered_ok')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_MOUNTED_ARCHER)) {
        __log_info_native('[test:555] FIGURE_ENEMY_EGYPTIAN_MOUNTED_ARCHER not registered')
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_mounted_archer_registered_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var camel = test_figure_create(FIGURE_ENEMY_EGYPTIAN_CAMEL, cx, cy)
    if (!camel || !__figure_is_valid(camel) || !__test_figure_is_enemy(camel)) {
        __log_info_native('[test:555] camel spawn/dcast_enemy failed')
        __test_signal_ready()
        return
    }
    __test_figure_action_perform(camel)
    if (!__figure_is_valid(camel) || __figure_get_type(camel) != FIGURE_ENEMY_EGYPTIAN_CAMEL) {
        __log_info_native('[test:555] camel died or type changed after action')
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_camel_spawn_ok')

    var archer = test_figure_create(FIGURE_ENEMY_EGYPTIAN_MOUNTED_ARCHER, cx + 1, cy)
    if (!archer || !__figure_is_valid(archer) || !__test_figure_is_enemy(archer)) {
        __log_info_native('[test:555] mounted archer spawn/dcast_enemy failed')
        __test_signal_ready()
        return
    }
    __test_figure_action_perform(archer)
    if (!__figure_is_valid(archer) || __figure_get_type(archer) != FIGURE_ENEMY_EGYPTIAN_MOUNTED_ARCHER) {
        __log_info_native('[test:555] mounted archer died or type changed after action')
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_mounted_archer_spawn_ok')
    __log_marker('egyptian_mount_all_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'egyptian_mount_control_ok',
        'egyptian_camel_registered_ok',
        'egyptian_mounted_archer_registered_ok',
        'egyptian_camel_spawn_ok',
        'egyptian_mounted_archer_spawn_ok',
        'egyptian_mount_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:555] missing marker: ' + marker)
            return false
        }
    }
    return true
}

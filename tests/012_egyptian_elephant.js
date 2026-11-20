// Egyptian war elephant — register + spawn/action + soldier target + trampling AoE.
// FIGURE_ENEMY_EGYPTIAN_ELEPHANT (47) → figure_egyptian_elephant (figure_enemy_elephant).
// Not in enemy_egyptian.figure_types[]. Splash trampling = adjacent soldiers (Chebyshev 1).
// Markers:
//   [test-marker] egyptian_elephant_control_ok
//   [test-marker] egyptian_elephant_registered_ok
//   [test-marker] egyptian_elephant_spawn_ok
//   [test-marker] egyptian_elephant_soldier_target_ok
//   [test-marker] egyptian_elephant_trample_ok
//   [test-marker] egyptian_elephant_trample_kill_ok
//   [test-marker] egyptian_elephant_all_ok

function run_test() {
    __log_info_native('[test:012] egyptian elephant (ES4)')
    test_ensure_city_session('data/default.map')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_CAMEL)) {
        __log_info_native('[test:012] control failed: camel not registered')
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_elephant_control_ok')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_ELEPHANT)) {
        __log_info_native('[test:012] FIGURE_ENEMY_EGYPTIAN_ELEPHANT not registered')
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_elephant_registered_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var eid = test_figure_create(FIGURE_ENEMY_EGYPTIAN_ELEPHANT, cx, cy)
    if (!eid || !__figure_is_valid(eid) || !__test_figure_is_enemy(eid)) {
        __log_info_native('[test:012] elephant spawn/dcast_enemy failed')
        __test_signal_ready()
        return
    }
    if (__figure_get_type(eid) != FIGURE_ENEMY_EGYPTIAN_ELEPHANT) {
        __log_info_native('[test:012] wrong type after create')
        __test_signal_ready()
        return
    }
    __test_figure_action_perform(eid)
    if (!__figure_is_valid(eid)) {
        __log_info_native('[test:012] elephant poofed on first action')
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_elephant_spawn_ok')

    var tile = __figure_get_tile(eid)
    var target = __test_soldier_combat_target(tile.x, tile.y, 12)
    if (!target || __figure_get_type(target) != FIGURE_ENEMY_EGYPTIAN_ELEPHANT) {
        __log_info_native('[test:012] soldier combat target want elephant, got ' + target)
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_elephant_soldier_target_ok')

    // Two infantry adjacent — one force-trample should damage both.
    var s1 = test_figure_create(FIGURE_INFANTRY, tile.x + 1, tile.y)
    var s2 = test_figure_create(FIGURE_INFANTRY, tile.x, tile.y + 1)
    if (!s1 || !s2 || !__figure_is_valid(s1) || !__figure_is_valid(s2)) {
        __log_info_native('[test:012] infantry spawn for trample failed')
        __test_signal_ready()
        return
    }
    var d1_before = __test_figure_get_damage(s1)
    var d2_before = __test_figure_get_damage(s2)
    if (!__test_elephant_trample(eid)) {
        __log_info_native('[test:012] __test_elephant_trample failed')
        __test_signal_ready()
        return
    }
    var d1_after = __test_figure_get_damage(s1)
    var d2_after = __test_figure_get_damage(s2)
    if (d1_after <= d1_before || d2_after <= d2_before) {
        __log_info_native('[test:012] trample want both soldiers damaged, got '
            + d1_before + '->' + d1_after + ', ' + d2_before + '->' + d2_after)
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_elephant_trample_ok')

    // Lethal splash: stack until damage exceeds max — must kill (not only accumulate).
    var splash = d1_after - d1_before
    if (splash <= 0) {
        __log_info_native('[test:012] splash delta unexpected')
        __test_signal_ready()
        return
    }
    var guard = 0
    while (__test_figure_is_alive(s1) && guard < 64) {
        if (!__test_elephant_trample(eid)) {
            break
        }
        guard++
    }
    if (__test_figure_is_alive(s1)) {
        __log_info_native('[test:012] trample never killed soldier after ' + guard + ' hits, damage='
            + __test_figure_get_damage(s1))
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_elephant_trample_kill_ok')

    __test_figure_kill(eid)
    if (__test_figure_is_alive(s2)) {
        __test_figure_kill(s2)
    }
    __log_marker('egyptian_elephant_all_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'egyptian_elephant_control_ok',
        'egyptian_elephant_registered_ok',
        'egyptian_elephant_spawn_ok',
        'egyptian_elephant_soldier_target_ok',
        'egyptian_elephant_trample_ok',
        'egyptian_elephant_trample_kill_ok',
        'egyptian_elephant_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:012] missing marker: ' + marker)
            return false
        }
    }
    return true
}

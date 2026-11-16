// OG scenario/invasion.c invasion_start_sea (:139): one enemy transport per 16 soldiers (the size capped at 150),
// each waiting n*40+10 ticks (FIGURE_ACTION_ENEMY_TRANSPORT_WAITING = 8), all bound for the one landing point;
// the ships carry a soldier count, no soldier exists before a transport lands.
// Markers:
//   [test-marker] transport_launch_split_ok
//   [test-marker] transport_launch_no_soldiers_ok
//   [test-marker] transport_launch_cap_ok

var __test620_ok = false

function test620_fail(msg) {
    __log_info_native('[test:620] FAIL: ' + msg)
    __test_signal_ready()
}

function test620_session() {
    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    __test_make_lake(cx - 10, cy, 20, 8)
    __test_invasion_points_clear()
    __test_invasion_sea_point_set(0, cx + 8, cy + 6)
    __test_disembark_point_add(cx - 8, cy - 1)
    return { lx: cx - 8, ly: cy - 1 }
}

function test620_transports() {
    var list = '' + __test_enemy_transports()
    var ids = []
    var parts = list.length ? list.split(',') : []
    for (var i = 0; i < parts.length; i++) {
        ids.push(parseInt(parts[i]))
    }
    return ids
}

function run_test() {
    __log_info_native('[test:620] enemy transport launch (OG invasion_start_sea)')

    var p = test620_session()
    if (!__test_sea_invasion_start(ENEMY_4_HITTITE, 40)) {
        return test620_fail('sea invasion of 40 did not start')
    }
    var ships = test620_transports()
    if (ships.length != 3) {
        return test620_fail('40 soldiers: transports=' + ships.length + ' want 3')
    }
    var want_soldiers = [16, 16, 8]
    var seq = __test_enemy_transport_invasion_seq(ships[0])
    for (var i = 0; i < ships.length; i++) {
        var id = ships[i]
        var soldiers = __test_enemy_transport_soldiers(id)
        var wait = __test_figure_get_wait_ticks(id)
        var action = __test_figure_get_action(id)
        if (soldiers != want_soldiers[i] || wait != i * 40 + 10 || action != 8 || !__test_enemy_transport_has_troops(id)
            || __test_enemy_transport_landing_x(id) != p.lx || __test_enemy_transport_landing_y(id) != p.ly
            || __test_enemy_transport_invasion_seq(id) != seq) {
            return test620_fail('ship ' + i + ': soldiers=' + soldiers + ' wait=' + wait + ' action=' + action
                + ' landing=' + __test_enemy_transport_landing_x(id) + ',' + __test_enemy_transport_landing_y(id)
                + ' seq=' + __test_enemy_transport_invasion_seq(id))
        }
    }
    __log_marker('transport_launch_split_ok')

    if (__test_count_enemy_figures() != 0) {
        return test620_fail('soldiers exist before landing: ' + __test_count_enemy_figures())
    }
    __log_marker('transport_launch_no_soldiers_ok')

    test620_session()
    if (!__test_sea_invasion_start(ENEMY_4_HITTITE, 200)) {
        return test620_fail('sea invasion of 200 did not start')
    }
    ships = test620_transports()
    var total = 0
    for (var j = 0; j < ships.length; j++) {
        total += __test_enemy_transport_soldiers(ships[j])
    }
    if (ships.length != 10 || total != 150 || __test_enemy_transport_soldiers(ships[9]) != 6) {
        return test620_fail('200 soldiers: transports=' + ships.length + ' total=' + total)
    }
    __log_marker('transport_launch_cap_ok')

    __test620_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test620_ok
        && __test_find_inlog('[test-marker] transport_launch_split_ok')
        && __test_find_inlog('[test-marker] transport_launch_no_soldiers_ok')
        && __test_find_inlog('[test-marker] transport_launch_cap_ok')
}

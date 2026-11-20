// E3b smoke: spawn enemy transport with troops → sail → disembark ≥1 visible soldier.
// Also covers E3c via_sea spawn (transport + the invasion's one warship) and E3a-smoke Seth sink.
// Markers:
//   [test-marker] transport_loaded_ok
//   [test-marker] transport_disembark_ok
//   [test-marker] sea_invasion_fleet_ok
//   [test-marker] seth_sink_enemy_warship_ok

function run_test() {
    __log_info_native('[test:011] enemy transport disembark / sea invasion / Seth sink')
    test_reload_city_session('data/default.map')

    // --- E3b disembark ---
    var ship = __test_enemy_transport_spawn_loaded(ENEMY_4_HITTITE, 4)
    if (!ship) {
        __log_info_native('[test:011] failed to spawn loaded transport')
        __test_signal_ready()
        return
    }
    if (!__test_enemy_transport_has_troops(ship)) {
        __log_info_native('[test:011] transport has no troops after load')
        __test_signal_ready()
        return
    }
    __log_marker('transport_loaded_ok')

    var disembarked = false
    for (var i = 0; i < 400; i++) {
        __test_figure_action_perform(ship)
        __test_pump_frames(1)
        if (__test_count_visible_enemy_soldiers() >= 1 && !__test_enemy_transport_has_troops(ship)) {
            disembarked = true
            break
        }
    }
    if (!disembarked) {
        __log_info_native('[test:011] disembark failed; visible=' + __test_count_visible_enemy_soldiers()
            + ' has_troops=' + __test_enemy_transport_has_troops(ship))
        __test_signal_ready()
        return
    }
    __log_marker('transport_disembark_ok')

    // --- E3c via_sea fleet ---
    test_reload_city_session('data/default.map')
    if (!__test_start_sea_invasion(ENEMY_4_HITTITE, 8, 1)) {
        __log_info_native('[test:011] sea invasion failed to start')
        __test_signal_ready()
        return
    }
    var transports = __test_count_enemy_transports()
    var warships = __test_count_enemy_warships()
    if (transports < 1 || warships < 1) {
        __log_info_native('[test:011] sea fleet incomplete: transports=' + transports + ' warships=' + warships)
        __test_signal_ready()
        return
    }
    __log_marker('sea_invasion_fleet_ok')

    // --- E3a-smoke: sink_all_ships kills enemy warship ---
    test_reload_city_session('data/default.map')
    var wid = __test_spawn_enemy_warship_on_water(ENEMY_4_HITTITE)
    if (!wid) {
        __log_info_native('[test:011] failed to spawn enemy warship')
        __test_signal_ready()
        return
    }
    if (__test_count_enemy_warships() < 1) {
        __log_info_native('[test:011] warship count zero after spawn')
        __test_signal_ready()
        return
    }
    __test_seth_sink_all_ships()
    if (__test_count_enemy_warships() != 0) {
        __log_info_native('[test:011] seth sink left warships=' + __test_count_enemy_warships())
        __test_signal_ready()
        return
    }
    __log_marker('seth_sink_enemy_warship_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'transport_loaded_ok',
        'transport_disembark_ok',
        'sea_invasion_fleet_ok',
        'seth_sink_enemy_warship_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:011] missing marker: ' + marker)
            return false
        }
    }
    return true
}

// E3d + CC52.N + E3c-followup smoke: mission via_sea fleet spawn.
// Markers:
//   [test-marker] rowarty_sea_invasion_ok
//   [test-marker] actium_sea_invasion_ok
//   [test-marker] baki_sea_invasion_ok
//   [test-marker] heh_sea_invasion_ok
//   [test-marker] sawu_sea_invasion_ok

function run_test() {
    __log_info_native('[test:139] naval mission via_sea (Rowarty + Actium + Baki/Heh/Sawu)')

    // Warships come only from the invasion's OG warship count, which these raid helpers do not pass.
    function expect_fleet(label, marker) {
        var transports = __test_count_enemy_transports()
        if (transports < 1) {
            __log_info_native('[test:139] ' + label + ' fleet incomplete: transports=' + transports)
            return false
        }
        __log_marker(marker)
        return true
    }

    // --- E3d: Rowarty loc>=9 via_sea ---
    __game_load_mission(36, 1)
    if (typeof mission36_enemy_raid !== 'function') {
        __log_info_native('[test:139] mission36_enemy_raid missing after load')
        __test_signal_ready()
        return
    }
    mission36_enemy_raid(990, 8, 9, 1)
    if (!expect_fleet('rowarty', 'rowarty_sea_invasion_ok')) {
        __test_signal_ready()
        return
    }

    // --- CC52.N: Actium Persian via_sea ---
    __game_load_mission(52, 1)
    if (typeof mission52_enemy_raid !== 'function') {
        __log_info_native('[test:139] mission52_enemy_raid missing after load')
        __test_signal_ready()
        return
    }
    mission52_enemy_raid(991, 8, 0)
    if (!expect_fleet('actium', 'actium_sea_invasion_ok')) {
        __test_signal_ready()
        return
    }

    // --- E3c: Baki favour loc2 = packed sea[0] ---
    __game_load_mission(35, 1)
    if (typeof mission35_favour_wave !== 'function') {
        __log_info_native('[test:139] mission35_favour_wave missing after load')
        __test_signal_ready()
        return
    }
    mission35_favour_wave(8, 992, 2)
    if (!expect_fleet('baki', 'baki_sea_invasion_ok')) {
        __test_signal_ready()
        return
    }

    // --- E3c: Heh kushite loc3 = packed sea[0] ---
    __game_load_mission(30, 1)
    if (typeof mission30_kushite_raid !== 'function') {
        __log_info_native('[test:139] mission30_kushite_raid missing after load')
        __test_signal_ready()
        return
    }
    mission30_kushite_raid(993, 8, 3)
    if (!expect_fleet('heh', 'heh_sea_invasion_ok')) {
        __test_signal_ready()
        return
    }

    // --- E3c: Sawu libyan loc2 = packed sea[0] ---
    __game_load_mission(29, 1)
    if (typeof mission29_libyan_raid !== 'function') {
        __log_info_native('[test:139] mission29_libyan_raid missing after load')
        __test_signal_ready()
        return
    }
    mission29_libyan_raid(994, 8, 2)
    if (!expect_fleet('sawu', 'sawu_sea_invasion_ok')) {
        __test_signal_ready()
        return
    }

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'rowarty_sea_invasion_ok',
        'actium_sea_invasion_ok',
        'baki_sea_invasion_ok',
        'heh_sea_invasion_ok',
        'sawu_sea_invasion_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:139] missing marker: ' + marker)
            return false
        }
    }
    return true
}

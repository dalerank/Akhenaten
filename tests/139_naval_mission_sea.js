// E3d + CC52.N + E3c-followup smoke: mission via_sea fleet spawn.
// Markers:
//   [test-marker] rowarty_sea_invasion_ok
//   [test-marker] actium_sea_invasion_ok
//   [test-marker] heh_sea_invasion_ok
//   [test-marker] sawu_sea_invasion_ok

function run_test() {
    __log_info_native('[test:139] naval mission via_sea (Rowarty + Actium + Heh/Sawu)')

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
    mission_start_raid(mission36, { key: "t", invasion_id: 990, invader: EVENT_INVADER_ENEMY, enemy: ENEMY_1_ASSYRIAN,
        amount: 8, months_initial: 0, warships: 0, attack_target: EVENT_ATTACK_TARGET_VAULTS }, 9)
    if (!expect_fleet('rowarty', 'rowarty_sea_invasion_ok')) {
        __test_signal_ready()
        return
    }

    // --- CC52.N: Actium Persian via_sea ---
    __game_load_mission(52, 1)
    mission_start_raid(mission52, { key: "t", invasion_id: 991, invader: EVENT_INVADER_ENEMY, enemy: ENEMY_9_PERSIAN,
        amount: 8, months_initial: 0, warships: 0, attack_target: EVENT_ATTACK_TARGET_TROOPS }, 9)
    if (!expect_fleet('actium', 'actium_sea_invasion_ok')) {
        __test_signal_ready()
        return
    }

    // --- Heh / Sawu: location 9 = sea point 0 through the shared raid helper ---
    __game_load_mission(30, 1)
    mission_start_raid(mission30, { key: "t", invasion_id: 993, invader: EVENT_INVADER_ENEMY, enemy: ENEMY_6_KUSHITE,
        amount: 8, months_initial: 0, attack_target: EVENT_ATTACK_TARGET_RANDOM }, 9)
    if (!expect_fleet('heh', 'heh_sea_invasion_ok')) {
        __test_signal_ready()
        return
    }

    __game_load_mission(29, 1)
    mission_start_raid(mission29, { key: "t", invasion_id: 994, invader: EVENT_INVADER_ENEMY, enemy: ENEMY_7_LIBIAN,
        amount: 8, months_initial: 0, attack_target: EVENT_ATTACK_TARGET_RANDOM }, 9)
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

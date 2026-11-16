// OG scenario_invasion_start (invasion.c:283): an invasion whose point is 9+ sails from sea point point - 9 with the
// event's phrase_var warships. Mission raids started from JS pass that count: Behdet i=9 (Kushite ×5, 2 warships),
// Thinis i=38 (Kushite ×29 at loc 10, 2 warships) and Iunet's warship-only i=3 (Hittite, 0 soldiers, 1 warship).
// Markers:
//   [test-marker] behdet_raid_warships_ok
//   [test-marker] thinis_raid_warships_ok
//   [test-marker] iunet_warship_only_raid_ok

function test637_fail(msg) {
    __log_info_native('[test:637] FAIL: ' + msg)
    __test_signal_ready()
}

function test637_load(id, fn_name) {
    __game_load_mission(id, 1)
    if (eval('typeof ' + fn_name) !== 'function') {
        test637_fail('mission ' + id + ': ' + fn_name + ' missing')
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:637] mission raids send the OG warship count')

    if (!test637_load(6, 'mission6_kushite_invasion_1')) {
        return
    }
    var ships = __test_count_enemy_warships()
    mission6_kushite_invasion_1({ years_since_start: 5, month: 1 })
    var warships = __test_count_enemy_warships() - ships
    if (warships != 2 || __test_count_enemy_transports() < 1) {
        return test637_fail('behdet: warships=' + warships + ' transports=' + __test_count_enemy_transports())
    }
    __log_marker('behdet_raid_warships_ok')

    if (!test637_load(23, 'mission23_start_enemy29_then_egypt33')) {
        return
    }
    ships = __test_count_enemy_warships()
    mission23_start_enemy29_then_egypt33()
    warships = __test_count_enemy_warships() - ships
    if (warships != 2 || __test_count_enemy_transports() < 1) {
        return test637_fail('thinis: warships=' + warships + ' transports=' + __test_count_enemy_transports())
    }
    __log_marker('thinis_raid_warships_ok')

    if (!test637_load(16, 'mission16_event_i3_warships')) {
        return
    }
    ships = __test_count_enemy_warships()
    var transports = __test_count_enemy_transports()
    mission16_event_i3_warships({ years_since_start: 2, month: 7 })
    warships = __test_count_enemy_warships() - ships
    if (warships != 1 || __test_count_enemy_transports() != transports) {
        return test637_fail('iunet: warships=' + warships + ' transports=' + (__test_count_enemy_transports() - transports))
    }
    __log_marker('iunet_warship_only_raid_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = ['behdet_raid_warships_ok', 'thinis_raid_warships_ok', 'iunet_warship_only_raid_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:637] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

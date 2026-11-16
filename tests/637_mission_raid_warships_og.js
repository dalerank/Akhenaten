// OG scenario_invasion_start (invasion.c:283): an invasion whose point is 9+ sails from sea point point - 9 with the
// event's phrase_var warships. Thinis i=38 (Kushite ×29 at loc 10, 2 warships) passes that count; the raids on the
// shared helper (Behdet, Iunet and the others) are checked by test 640.
// Markers:
//   [test-marker] thinis_raid_warships_ok

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

    if (!test637_load(23, 'mission23_start_enemy29_then_egypt33')) {
        return
    }
    var ships = __test_count_enemy_warships()
    mission23_start_enemy29_then_egypt33()
    var warships = __test_count_enemy_warships() - ships
    if (warships != 2 || __test_count_enemy_transports() < 1) {
        return test637_fail('thinis: warships=' + warships + ' transports=' + __test_count_enemy_transports())
    }
    __log_marker('thinis_raid_warships_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = ['thinis_raid_warships_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:637] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

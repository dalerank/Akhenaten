// OG house_evolve.c evolve_level: a decaying house waits HOUSE_DEVOLVE_DELAY_DAYS (2) and devolves on the
// third bad day. A missing config key used to zero can_devolve and devolve on the first day.
//   [test-marker] house_devolve_delay_ok

var __test294_ok = false

function test294_fail(msg) {
    __log_info_native('[test:294] FAIL: ' + msg)
}

function test294_check(cx, cy) {
    var bid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx, cy - 14)
    if (!bid || !__test_house_change_to(bid, BUILDING_HOUSE_STURDY_HUT)) {
        test294_fail('house create/change failed')
        return false
    }
    __test_house_set_population(bid, 5)

    var status = __test_house_evolve_status(bid)
    if (status != -1) {
        test294_fail('sturdy hut is not decaying on this map, status=' + status)
        return false
    }

    var want = [BUILDING_HOUSE_STURDY_HUT, BUILDING_HOUSE_STURDY_HUT, BUILDING_HOUSE_CRUDE_HUT]
    for (var day = 0; day < want.length; day++) {
        var got = __test_house_evolve_day(bid)
        if (got != want[day]) {
            test294_fail('day ' + (day + 1) + ' type=' + got + ' want=' + want[day])
            return false
        }
    }
    return true
}

function run_test() {
    __test294_ok = false
    if (test_reload_city_session('data/default.map')) {
        var cx = (__scenario_map.width / 2) | 0
        var cy = (__scenario_map.height / 2) | 0
        if (test294_check(cx, cy)) {
            __test294_ok = true
            __log_info_native('[test-marker] house_devolve_delay_ok')
        }
    } else {
        test294_fail('session reload failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return __test294_ok && __test_find_inlog('[test-marker] house_devolve_delay_ok')
}

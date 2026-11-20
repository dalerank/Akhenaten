// OG building_house_change_to has no delay between two evolutions. The remake's "at most once every 7 days"
// (house_up_delay) runs only with gameplay_change_house_evolve_delay.
//   [test-marker] house_evolve_delay_flag_ok

var __test354_ok = false
var __test354_feat_prev = false

function test354_fail(msg) {
    __log_info_native('[test:354] FAIL: ' + msg)
}

// A crude hut that has just changed type today and meets the sturdy hut's needs.
function test354_fresh_hut(x, y) {
    var bid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, x, y)
    if (!bid || !__test_house_change_to(bid, BUILDING_HOUSE_CRUDE_HUT)) {
        return 0
    }
    __test_house_set_population(bid, 5)
    var house = city.get_house(bid)
    house.has_water_access = 1
    house.water_supply = 1
    return bid
}

function test354_evolve_once(x, y, want, what) {
    var bid = test354_fresh_hut(x, y)
    if (!bid) {
        test354_fail(what + ': hut create failed')
        return false
    }
    var status = __test_house_evolve_status(bid)
    if (status != 1) {
        test354_fail(what + ': crude hut cannot evolve on this map, status=' + status)
        return false
    }
    var got = __test_house_evolve_day(bid)
    if (got != want) {
        test354_fail(what + ': type after one day=' + got + ' want ' + want)
        return false
    }
    return true
}

function test354_check(cx, cy) {
    game_features.gameplay_change_house_evolve_delay = false
    if (!test354_evolve_once(cx, cy - 14, BUILDING_HOUSE_STURDY_HUT, 'flag off')) {
        return false
    }
    game_features.gameplay_change_house_evolve_delay = true
    if (!test354_evolve_once(cx + 4, cy - 14, BUILDING_HOUSE_CRUDE_HUT, 'flag on')) {
        return false
    }
    return true
}

function run_test() {
    __test354_ok = false
    __test354_feat_prev = !!game_features.gameplay_change_house_evolve_delay
    if (test_reload_city_session('data/default.map')) {
        var cx = (__scenario_map.width / 2) | 0
        var cy = (__scenario_map.height / 2) | 0
        if (test354_check(cx, cy)) {
            __test354_ok = true
            __log_info_native('[test-marker] house_evolve_delay_flag_ok')
        }
    } else {
        test354_fail('session reload failed')
    }
    game_features.gameplay_change_house_evolve_delay = __test354_feat_prev
    __test_signal_ready()
}

function check_valid() {
    return __test354_ok && __test_find_inlog('[test-marker] house_evolve_delay_flag_ok')
}

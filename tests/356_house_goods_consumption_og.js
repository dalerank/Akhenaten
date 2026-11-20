// OG house_evolve.c: houses eat goods right after their evolve on days 0 and 7 of the month. A house bigger
// than 1x1 uses 4x the model's amounts and eats a quarter of that per call; a 1x1 house with amount 1 eats it
// only when day % 4 == 0 (remainder 1: days 0 and 4, 8, 12 -> of the two consumption days, day 0).
//   [test-marker] house_goods_consumption_og_ok

var __test356_ok = false

function test356_fail(msg) {
    __log_info_native('[test:356] FAIL: ' + msg)
}

// house.inv slots: 0 pottery, 1 jewelry, 2 linen, 3 beer.
function test356_stock(house, value) {
    for (var i = 0; i < 4; i++) {
        house.set_inv(i, value)
    }
}

function test356_inv(house, want, what) {
    for (var i = 0; i < 4; i++) {
        if (house.inv(i) != want[i]) {
            test356_fail(what + ': inv=[' + house.inv(0) + ', ' + house.inv(1) + ', ' + house.inv(2) + ', '
                + house.inv(3) + '] want [' + want.join(', ') + ']')
            return false
        }
    }
    return true
}

function test356_check(cx, cy) {
    var small_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx, cy - 14)
    if (!small_id || !__test_house_change_to(small_id, BUILDING_HOUSE_SPACIOUS_APARTMENT)) {
        test356_fail('small house create/change failed')
        return false
    }
    __test_house_set_population(small_id, 10)
    var small = city.get_house(small_id)

    // Spacious apartment: pottery 1, beer 1. Evolve pass on a day that is not a consumption day, then 7, then 0.
    test356_stock(small, 10)
    __test_city_house_process_evolve_on_day(3)
    if (!test356_inv(small, [10, 10, 10, 10], 'day 3')) {
        return false
    }
    __test_city_house_process_evolve_on_day(7)
    if (!test356_inv(small, [10, 10, 10, 10], '1x1 on day 7')) {
        return false
    }
    __test_city_house_process_evolve_on_day(0)
    if (!test356_inv(small, [9, 10, 10, 9], '1x1 on day 0')) {
        return false
    }

    // Modest estate as a 4x4: pottery 1, linen 1, beer 1 -> 1 a call; jewelry 2 -> 2 a call, both days.
    var big_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx + 4, cy - 14)
    if (!big_id || !__test_house_change_to(big_id, BUILDING_HOUSE_MODEST_ESTATE)) {
        test356_fail('big house create/change failed')
        return false
    }
    __test_house_set_population(big_id, 10)
    var big = city.get_house(big_id)
    big.size = 4
    test356_stock(big, 10)
    __test_house_consume_goods(big_id, 0)
    if (!test356_inv(big, [9, 8, 9, 9], 'big on day 0')) {
        return false
    }
    __test_house_consume_goods(big_id, 7)
    if (!test356_inv(big, [8, 6, 8, 8], 'big on day 7')) {
        return false
    }
    return true
}

function run_test() {
    __test356_ok = false
    if (test_reload_city_session('data/default.map')) {
        var cx = (__scenario_map.width / 2) | 0
        var cy = (__scenario_map.height / 2) | 0
        if (test356_check(cx, cy)) {
            __test356_ok = true
            __log_info_native('[test-marker] house_goods_consumption_og_ok')
        }
    } else {
        test356_fail('session reload failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return __test356_ok && __test_find_inlog('[test-marker] house_goods_consumption_og_ok')
}

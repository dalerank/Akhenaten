// OG house_evolve_checks.c: a house whose (size-scaled) jewelry need is 2 or more also needs two luxury kinds.
// OG empire.c counts the kinds by the culture (empire_city_cultures in empire.js) of the open cities that sell
// luxury goods while the city imports them, plus one kind when the city has a luxury workshop.
//   [test-marker] house_second_luxury_ok

var __test353_ok = false
var TEST431_ROUTE_A = 19
var TEST431_ROUTE_B = 18

function test353_fail(msg) {
    __log_info_native('[test:353] FAIL: ' + msg)
}

function test353_serve_all(house) {
    house.has_water_access = 1
    house.water_supply = 1
    house.entertainment = 100
    house.education = 3
    house.num_gods = 3
    house.dentist = 100
    house.magistrate = 100
    house.health = 100
    house.fancy_bazaar_access = 1
    house.set_food(0, 100)
    house.set_food(1, 100)
    for (var i = 0; i < 4; i++) {
        house.set_inv(i, 20)
    }
}

function test353_expect(bid, want_kinds, want_ok, what) {
    var kinds = __test_city_update_luxury_goods_kinds()
    if (kinds != want_kinds) {
        test353_fail(what + ': luxury kinds=' + kinds + ' want ' + want_kinds)
        return false
    }
    var got = __test_house_has_requirements(bid, 0)
    if (got != want_ok) {
        test353_fail(what + ': requirements=' + got + ' want ' + want_ok + ' second_luxury=' + city.houses.missing.second_luxury)
        return false
    }
    return true
}

function test353_check(cx, cy) {
    var bid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx, cy - 14)
    if (!bid || !__test_house_change_to(bid, BUILDING_HOUSE_MODEST_ESTATE)) {
        test353_fail('house create/change failed')
        return false
    }
    __test_house_set_population(bid, 10)
    var house = city.get_house(bid)
    house.size = 4
    if (house.model.jewelry != 2) {
        test353_fail('modest estate model.jewelry=' + house.model.jewelry + ' want 2')
        return false
    }
    test353_serve_all(house)

    __test_empire_close_cities()
    __test_city_set_trade(RESOURCE_LUXURY_GOODS, 1, 0)
    if (!test353_expect(bid, 0, 0, 'no source')) {
        return false
    }
    if (city.houses.missing.second_luxury != 1) {
        test353_fail('missing second_luxury=' + city.houses.missing.second_luxury + ' want 1')
        return false
    }

    // Abu (0) and Abedju (1) both sell jewelry; Bahariya Oasis (2) sells wine.
    __test_empire_city_luxury_source(79, 0, TEST431_ROUTE_A)
    __test_empire_city_luxury_source(78, 1, TEST431_ROUTE_B)
    if (!test353_expect(bid, 1, 0, 'two cities, one culture')) {
        return false
    }

    __test_empire_city_luxury_source(78, 2, TEST431_ROUTE_B)
    if (!test353_expect(bid, 2, 1, 'two cultures')) {
        return false
    }

    __test_city_set_trade(RESOURCE_LUXURY_GOODS, 0, 0)
    if (!test353_expect(bid, 0, 0, 'not importing')) {
        return false
    }

    house.size = 1
    if (__test_house_has_requirements(bid, 0) != 1) {
        test353_fail('a 1x1 house needs (2+2)/4 = 1 jewelry and no second kind')
        return false
    }
    return true
}

function run_test() {
    __test353_ok = false
    if (test_reload_city_session('data/default.map')) {
        var cx = (__scenario_map.width / 2) | 0
        var cy = (__scenario_map.height / 2) | 0
        if (test353_check(cx, cy)) {
            __test353_ok = true
            __log_info_native('[test-marker] house_second_luxury_ok')
        }
    } else {
        test353_fail('session reload failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return __test353_ok && __test_find_inlog('[test-marker] house_second_luxury_ok')
}

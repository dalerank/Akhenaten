// OG house_evolve_checks.c: the model's courthouse column is checked against magistrate access, not the
// physician, and counts houses_missing_any_courthouse / houses_missing_courthouse / houses_requiring_courthouse.
// The health advisor then picks its OG demand and advice text from those counters.
//   [test-marker] house_courthouse_requirement_ok

var __test430_ok = false

function test430_fail(msg) {
    __log_info_native('[test:430] FAIL: ' + msg)
}

function test430_serve_all_but_courthouse(house) {
    house.has_water_access = 1
    house.water_supply = 1
    house.entertainment = 100
    house.education = 3
    house.num_gods = 3
    house.dentist = 100
    house.health = 100
    house.physician = 100
    house.set_food(0, 100)
    house.set_inv(0, 10)
    house.set_inv(3, 10)
}

function test430_check(cx, cy) {
    var bid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx, cy - 14)
    if (!bid || !__test_house_change_to(bid, BUILDING_HOUSE_SPACIOUS_APARTMENT)) {
        test430_fail('house create/change failed')
        return false
    }
    __test_house_set_population(bid, 10)
    var house = city.get_house(bid)
    if (house.model.courthouse != 1) {
        test430_fail('spacious apartment model.courthouse=' + house.model.courthouse + ' want 1')
        return false
    }
    test430_serve_all_but_courthouse(house)

    house.magistrate = 0
    var got = __test_house_has_requirements(bid, 0)
    if (got != 0) {
        test430_fail('no magistrate access must fail the requirements, got ' + got)
        return false
    }
    if (city.houses.missing.any_courthouse != 1 || city.houses.missing.courthouse != 0) {
        test430_fail('missing any_courthouse=' + city.houses.missing.any_courthouse + ' courthouse=' + city.houses.missing.courthouse)
        return false
    }
    if (city.houses.health != 4) {
        test430_fail('health demand without any courthouse=' + city.houses.health + ' want 4')
        return false
    }

    house.magistrate = 50
    house.physician = 0
    got = __test_house_has_requirements(bid, 0)
    if (got != 1) {
        test430_fail('magistrate access without a physician must pass, got ' + got)
        return false
    }
    if (city.houses.requiring.courthouse != 1 || city.houses.missing.any_courthouse != 0) {
        test430_fail('requiring courthouse=' + city.houses.requiring.courthouse + ' missing any=' + city.houses.missing.any_courthouse)
        return false
    }
    return true
}

function run_test() {
    __test430_ok = false
    if (test_reload_city_session('data/default.map')) {
        var cx = (__scenario_map.width / 2) | 0
        var cy = (__scenario_map.height / 2) | 0
        if (test430_check(cx, cy)) {
            __test430_ok = true
            __log_info_native('[test-marker] house_courthouse_requirement_ok')
        }
    } else {
        test430_fail('session reload failed')
    }
    __test_signal_ready()
}

function check_valid() {
    return __test430_ok && __test_find_inlog('[test-marker] house_courthouse_requirement_ok')
}

// OG jeweler (building_industry.c produce / spawn_industry): progress needs 100 gems in stock all along, grows by
// the worker count each day up to 400, and when it is done the gems are taken and a 100 luxury goods cart leaves.
// Akhenaten's jeweler set progress to 0 when it started a cycle, so the remake cycle never advanced:
// update_day took the gems again every day and no luxury goods were made.
// gameplay_change_jeweler_nearby_discount (remake): the cart takes 5 fewer gems per neighbouring jeweler, down to 50.

var __test461_ok = false
var __test461_prev_discount = false

function test461_restore() {
    game_features.set('gameplay_change_jeweler_nearby_discount', __test461_prev_discount)
}

function test461_fail(msg) {
    test461_restore()
    __log_info_native('[test:461] FAIL: ' + msg)
    __test_signal_ready()
}

function test461_staff(bid) {
    __test_building_force_road_access(bid)
    __test_building_set_houses_covered(bid, 100)
    __test_building_set_workers(bid, 12)
}

function test461_gems_taken_by_cart(bid) {
    city.get_building(bid).consume_resource(RESOURCE_GEMS, -100)
    for (var i = 0; i < 40; i++) {
        __test_city_industry_update_production()
        __test_building_update_day(bid)
    }
    if (__building_industry_progress(bid) != 400) {
        return -1
    }
    __test_building_spawn_figure(bid)
    return 100 - test461_gems(bid)
}

function test461_check_discount() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    game_features.set('gameplay_change_jeweler_nearby_discount', true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = __test_building_create(BUILDING_JEWELS_WORKSHOP, cx, cy)
    var west = __test_building_create(BUILDING_JEWELS_WORKSHOP, cx - 2, cy)
    var east = __test_building_create(BUILDING_JEWELS_WORKSHOP, cx + 2, cy)
    if (!bid || !west || !east) {
        test461_fail('jeweler cluster create failed ' + bid + '/' + west + '/' + east)
        return false
    }
    test461_staff(bid)

    var taken = test461_gems_taken_by_cart(bid)
    if (taken != 90) {
        test461_fail('discount on, two neighbours: expected 90 gems taken, got ' + taken)
        return false
    }
    __log_marker('test461_discount_ok')
    return true
}

function test461_gems(bid) {
    return city.get_building(bid).stored_resource(RESOURCE_GEMS)
}

function run_test() {
    __log_info_native('[test:461] jeweler OG production cycle')
    __test461_prev_discount = game_features.get('gameplay_change_jeweler_nearby_discount') === true
    game_features.set('gameplay_change_jeweler_nearby_discount', false)
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_JEWELS_WORKSHOP, -1, -1)
    if (!bid) {
        bid = __test_building_create(BUILDING_JEWELS_WORKSHOP, -1, -1)
    }
    if (!bid) {
        test461_fail('jeweler place/create failed')
        return
    }

    test461_staff(bid)

    city.get_building(bid).consume_resource(RESOURCE_GEMS, -100)
    __test_building_update_day(bid)
    if (test461_gems(bid) != 100) {
        test461_fail('update_day must not take gems, gems=' + test461_gems(bid))
        return
    }
    __test_city_industry_update_production()
    if (__building_industry_progress(bid) != 12) {
        test461_fail('one day with 12 workers expected 12 got ' + __building_industry_progress(bid))
        return
    }
    __log_marker('test461_needs_gems_ok')

    for (var i = 0; i < 40; i++) {
        __test_city_industry_update_production()
        __test_building_update_day(bid)
    }
    if (__building_industry_progress(bid) != 400) {
        test461_fail('progress must cap at 400, got ' + __building_industry_progress(bid))
        return
    }
    if (test461_gems(bid) != 100) {
        test461_fail('a done cycle keeps its gems until the cart leaves, gems=' + test461_gems(bid))
        return
    }
    __log_marker('test461_progress_400_ok')

    __test_building_spawn_figure(bid)
    var cart = city.get_building(bid).get_figure(BUILDING_SLOT_CARTPUSHER)
    if (!cart || !cart.valid) {
        test461_fail('missing cartpusher after the cycle')
        return
    }
    var res = __test_figure_resource(cart.id)
    var amount = __test_figure_carrying_amount(cart.id)
    if (res != RESOURCE_LUXURY_GOODS || amount != 100) {
        test461_fail('expected a 100 luxury goods cart, got ' + res + '/' + amount)
        return
    }
    if (__building_industry_progress(bid) != 0 || test461_gems(bid) != 0) {
        test461_fail('cart start must reset progress and take the gems, progress=' + __building_industry_progress(bid)
            + ' gems=' + test461_gems(bid))
        return
    }
    __log_marker('test461_cart_ok')

    if (!test461_check_discount()) {
        return
    }

    test461_restore()
    __test461_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test461_ok
        && __test_find_inlog('[test-marker] test461_needs_gems_ok')
        && __test_find_inlog('[test-marker] test461_progress_400_ok')
        && __test_find_inlog('[test-marker] test461_cart_ok')
        && __test_find_inlog('[test-marker] test461_discount_ok')
}

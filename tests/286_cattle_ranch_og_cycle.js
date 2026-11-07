// OG cattle ranch cycle: progress needs 100 straw in stock all along, the target is
// 400 (input industry), straw is taken and the 100 meat cart leaves when the
// progress is done; no meat is kept in the ranch, a busy cart holds progress at 400.

var __test286_ok = false

function test286_fail(msg) {
    __log_info_native('[test:286] FAIL: ' + msg)
    __test_signal_ready()
}

function test286_straw(bid) {
    return city.get_building(bid).stored_resource(RESOURCE_STRAW)
}

function test286_meat(bid) {
    return city.get_building(bid).stored_resource(RESOURCE_MEAT)
}

function test286_cart(bid) {
    return city.get_building(bid).get_figure(BUILDING_SLOT_CARTPUSHER)
}

function run_test() {
    __log_info_native('[test:286] cattle ranch OG production cycle')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_CATTLE_RANCH, -1, -1)
    if (!bid) {
        bid = __test_building_create(BUILDING_CATTLE_RANCH, -1, -1)
    }
    if (!bid) {
        test286_fail('ranch place/create failed')
        return
    }
    __test_building_force_road_access(bid)
    __test_building_set_houses_covered(bid, 100)
    __test_building_set_workers(bid, 12)
    __test_building_update_day(bid)

    __test_city_industry_update_production()
    if (__building_industry_progress(bid) != 0) {
        test286_fail('no straw must hold progress at 0, got ' + __building_industry_progress(bid))
        return
    }

    city.get_building(bid).consume_resource(RESOURCE_STRAW, -100)
    __test_building_update_day(bid)
    if (test286_straw(bid) != 100) {
        test286_fail('update_day must not take straw, straw=' + test286_straw(bid))
        return
    }
    __test_city_industry_update_production()
    if (__building_industry_progress(bid) != 12) {
        test286_fail('one day with 12 workers expected 12 got ' + __building_industry_progress(bid))
        return
    }
    __log_marker('test286_needs_straw_ok')

    for (var i = 0; i < 40; i++) {
        __test_city_industry_update_production()
        __test_building_update_day(bid)
    }
    if (__building_industry_progress(bid) != 400 || __building_industry_progress_pct(bid) != 100) {
        test286_fail('progress must cap at 400, got ' + __building_industry_progress(bid)
            + ' pct=' + __building_industry_progress_pct(bid))
        return
    }
    if (test286_meat(bid) != 0 || test286_straw(bid) != 100) {
        test286_fail('done cycle keeps straw and stores no meat, meat=' + test286_meat(bid)
            + ' straw=' + test286_straw(bid))
        return
    }
    __log_marker('test286_progress_400_ok')

    __test_building_spawn_figure(bid)
    var cart = test286_cart(bid)
    if (!cart || !cart.valid) {
        test286_fail('missing cartpusher after the cycle')
        return
    }
    var res = __test_figure_resource(cart.id)
    var amount = __test_figure_carrying_amount(cart.id)
    if (res != RESOURCE_MEAT || amount != 100) {
        test286_fail('expected a 100 meat cart, got ' + res + '/' + amount)
        return
    }
    if (__building_industry_progress(bid) != 0 || test286_straw(bid) != 0 || test286_meat(bid) != 0) {
        test286_fail('cart start must reset progress and take straw, progress=' + __building_industry_progress(bid)
            + ' straw=' + test286_straw(bid) + ' meat=' + test286_meat(bid))
        return
    }
    __log_marker('test286_cart_ok')

    city.get_building(bid).consume_resource(RESOURCE_STRAW, -200)
    for (var j = 0; j < 40; j++) {
        __test_city_industry_update_production()
        __test_building_update_day(bid)
    }
    __test_building_spawn_figure(bid)
    if (__building_industry_progress(bid) != 400 || test286_straw(bid) != 200 || test286_meat(bid) != 0) {
        test286_fail('busy cart must hold progress at 400, progress=' + __building_industry_progress(bid)
            + ' straw=' + test286_straw(bid) + ' meat=' + test286_meat(bid))
        return
    }
    __log_marker('test286_busy_cart_holds_ok')

    __test286_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test286_ok
        && __test_find_inlog('[test-marker] test286_needs_straw_ok')
        && __test_find_inlog('[test-marker] test286_progress_400_ok')
        && __test_find_inlog('[test-marker] test286_cart_ok')
        && __test_find_inlog('[test-marker] test286_busy_cart_holds_ok')
}

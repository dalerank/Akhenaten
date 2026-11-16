// OG paint maker (Pharaoh_Model_*.txt row 233, building_industry.c, city_channels.c):
// cost 20/80/100/120/150, labor seeker below 51 houses, paintmaker_r.wav ambient and info sound;
// progress needs 100 henna in stock all along, runs to 400 at one point per worker a day,
// henna is taken and a 100 paint cart leaves when the progress is done, no paint is kept;
// the work animation runs while there is any henna and some workers.

var __test387_ok = false

function test387_fail(msg) {
    __log_info_native('[test:387] FAIL: ' + msg)
    __test_signal_ready()
}

function test387_henna(bid) {
    return city.get_building(bid).stored_resource(RESOURCE_HENNA)
}

function test387_paint(bid) {
    return city.get_building(bid).stored_resource(RESOURCE_PAINT)
}

function test387_animates(bid) {
    var b = city.get_building(bid)
    b.play_animation = true
    building_paint_workshop_on_update_animation({ bid: bid })
    return city.get_building(bid).play_animation
}

function run_test() {
    __log_info_native('[test:387] paint workshop OG rules')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_PAINT_WORKSHOP, -1, -1)
    if (!bid) {
        bid = __test_building_create(BUILDING_PAINT_WORKSHOP, -1, -1)
    }
    if (!bid) {
        test387_fail('paint workshop place/create failed')
        return
    }

    var b = city.get_building(bid)
    var og_cost = [20, 80, 100, 120, 150][game.difficulty]
    if (b.params.cost != og_cost) {
        test387_fail('cost=' + b.params.cost + ' expected ' + og_cost + ' on difficulty ' + game.difficulty)
        return
    }
    if (b.params.min_houses_coverage != 50 || b.params.laborers != 12 || b.size != 2) {
        test387_fail('houses=' + b.params.min_houses_coverage + ' laborers=' + b.params.laborers + ' size=' + b.size)
        return
    }
    if (b.params.info_sound != 'Wavs/paintmaker_r.wav') {
        test387_fail('info_sound=' + b.params.info_sound)
        return
    }
    var channel = __test_sound_city_mark_building(bid, 4)
    if (channel != SOUND_CHANNEL_CITY_PAINT_WORKSHOP) {
        test387_fail('sound channel=' + channel)
        return
    }
    __log_marker('test387_static_ok')

    __test_building_force_road_access(bid)
    __test_building_set_houses_covered(bid, 100)
    __test_building_set_workers(bid, 12)
    __test_building_update_day(bid)

    if (test387_animates(bid)) {
        test387_fail('animates without henna')
        return
    }
    __test_city_industry_update_production()
    if (__building_industry_progress(bid) != 0) {
        test387_fail('no henna must hold progress at 0, got ' + __building_industry_progress(bid))
        return
    }

    city.get_building(bid).consume_resource(RESOURCE_HENNA, -100)
    __test_building_update_day(bid)
    if (test387_henna(bid) != 100) {
        test387_fail('update_day must not take henna, henna=' + test387_henna(bid))
        return
    }
    __test_city_industry_update_production()
    if (__building_industry_progress(bid) != 12) {
        test387_fail('one day with 12 workers expected 12 got ' + __building_industry_progress(bid))
        return
    }
    if (!test387_animates(bid)) {
        test387_fail('stopped with henna and workers')
        return
    }
    __log_marker('test387_needs_henna_ok')

    for (var i = 0; i < 40; i++) {
        __test_city_industry_update_production()
        __test_building_update_day(bid)
    }
    if (__building_industry_progress(bid) != 400 || __building_industry_progress_pct(bid) != 100) {
        test387_fail('progress must cap at 400, got ' + __building_industry_progress(bid)
            + ' pct=' + __building_industry_progress_pct(bid))
        return
    }
    if (test387_paint(bid) != 0 || test387_henna(bid) != 100) {
        test387_fail('done cycle keeps henna and stores no paint, paint=' + test387_paint(bid)
            + ' henna=' + test387_henna(bid))
        return
    }
    if (!test387_animates(bid)) {
        test387_fail('done cycle with henna must keep animating')
        return
    }
    __log_marker('test387_progress_400_ok')

    __test_building_spawn_figure(bid)
    var cart = city.get_building(bid).get_figure(BUILDING_SLOT_CARTPUSHER)
    if (!cart || !cart.valid) {
        test387_fail('missing cartpusher after the cycle')
        return
    }
    var res = __test_figure_resource(cart.id)
    var amount = __test_figure_carrying_amount(cart.id)
    if (res != RESOURCE_PAINT || amount != 100) {
        test387_fail('expected a 100 paint cart, got ' + res + '/' + amount)
        return
    }
    if (__building_industry_progress(bid) != 0 || test387_henna(bid) != 0 || test387_paint(bid) != 0) {
        test387_fail('cart start must reset progress and take henna, progress=' + __building_industry_progress(bid)
            + ' henna=' + test387_henna(bid) + ' paint=' + test387_paint(bid))
        return
    }
    if (test387_animates(bid)) {
        test387_fail('animates after the henna was taken')
        return
    }
    __log_marker('test387_cart_ok')

    __test387_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test387_ok
        && __test_find_inlog('[test-marker] test387_static_ok')
        && __test_find_inlog('[test-marker] test387_needs_henna_ok')
        && __test_find_inlog('[test-marker] test387_progress_400_ok')
        && __test_find_inlog('[test-marker] test387_cart_ok')
}

// OG spawn_hunting_lodge cart: loads > 0 (not hunter-delay gated), always haul 100,
// Osiris oracle ×2 on cart amount; consume 100 from storage.
// Markers:
//   [test-marker] hunting_lodge_cart_basic
//   [test-marker] hunting_lodge_cart_ungated
//   [test-marker] hunting_lodge_cart_osiris

var __test259_ok = false

function test259_fail(msg) {
    __log_info_native('[test:259] FAIL: ' + msg)
    __test_signal_ready()
}

function test259_place_lodge() {
    var bid = test_building_place(BUILDING_HUNTING_LODGE, -1, -1)
    if (!bid) {
        return 0
    }
    __test_building_set_workers(bid, 6)
    __test_building_force_road_access(bid)
    return bid
}

function test259_clear_cart(bid) {
    city.figures.remove_figures(FIGURE_CART_PUSHER)
    __test_building_set_figure_slot(bid, BUILDING_SLOT_CARTPUSHER, 0)
}

function test259_cart_amount(bid) {
    var b = city.get_building(bid)
    var cart = b.get_figure(BUILDING_SLOT_CARTPUSHER)
    if (!cart || !cart.valid) {
        return -1
    }
    return __test_figure_carrying_amount(cart.id)
}

function test259_place_osiris_oracle() {
    __scenario_building_allow(BUILDING_TEMPLE_COMPLEX_OSIRIS, true)
    var cid = test_building_place(BUILDING_TEMPLE_COMPLEX_OSIRIS, -1, -1)
    if (!cid) {
        var cx = (__scenario_map.width / 2) | 0
        var cy = (__scenario_map.height / 2) | 0
        cid = __test_building_create(BUILDING_TEMPLE_COMPLEX_OSIRIS, cx + 12, cy + 12)
    }
    var complex = city.get_temple_complex()
    if (!complex && cid) {
        complex = new TempleComplex(cid)
    }
    if (!cid || !complex || complex.type != BUILDING_TEMPLE_COMPLEX_OSIRIS) {
        return null
    }
    complex.temple_complex_upgrades = TEMPLE_COMPLEX_UPGRADE_ORACLE
    return complex
}

function run_test() {
    __log_info_native('[test:259] hunting lodge OG cart')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test259_place_lodge()
    if (!bid) {
        return test259_fail('lodge place failed')
    }

    test259_clear_cart(bid)
    var b = city.get_building(bid)
    b.store_resource(RESOURCE_GAMEMEAT, 100)
    __test_building_set_figure_spawn_delay(bid, 0)

    __test_hunting_lodge_spawn_figure(bid)
    if (test259_cart_amount(bid) != 100) {
        return test259_fail('basic cart want 100, got ' + test259_cart_amount(bid))
    }
    if (b.stored_resource(RESOURCE_GAMEMEAT) != 0) {
        return test259_fail('basic should consume 100, left=' + b.stored_resource(RESOURCE_GAMEMEAT))
    }
    __log_marker('hunting_lodge_cart_basic')

    // Cart must fire during hunter cooldown and must not reset figure_spawn_delay.
    test259_clear_cart(bid)
    b.store_resource(RESOURCE_GAMEMEAT, 100)
    __test_building_set_figure_spawn_delay(bid, 0)
    __test_building_set_workers(bid, 3) // 50% → spawn_delay 10
    __test_hunting_lodge_spawn_figure(bid)
    if (test259_cart_amount(bid) != 100) {
        return test259_fail('ungated cart want 100, got ' + test259_cart_amount(bid))
    }
    var delay_after = __test_building_figure_spawn_delay(bid)
    if (delay_after != 1) {
        return test259_fail('cart must not reset hunter delay, want 1 got ' + delay_after)
    }
    __log_marker('hunting_lodge_cart_ungated')

    // Fresh map: Osiris first (so city.get_temple_complex tracks it), then lodge → cart ×2.
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    if (!test259_place_osiris_oracle()) {
        return test259_fail('osiris complex place failed')
    }
    bid = test259_place_lodge()
    if (!bid) {
        return test259_fail('lodge place after osiris failed')
    }
    test259_clear_cart(bid)
    b = city.get_building(bid)
    b.store_resource(RESOURCE_GAMEMEAT, 100)
    __test_hunting_lodge_spawn_figure(bid)
    if (test259_cart_amount(bid) != 200) {
        return test259_fail('osiris cart want 200, got ' + test259_cart_amount(bid))
    }
    if (b.stored_resource(RESOURCE_GAMEMEAT) != 0) {
        return test259_fail('osiris should still consume 100, left=' + b.stored_resource(RESOURCE_GAMEMEAT))
    }
    __log_marker('hunting_lodge_cart_osiris')

    __test259_ok = true
    __log_info_native('[test:259] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test259_ok) {
        __log_info_native('[test:259] run_test did not complete')
        return false
    }
    var markers = [
        '[test-marker] hunting_lodge_cart_basic',
        '[test-marker] hunting_lodge_cart_ungated',
        '[test-marker] hunting_lodge_cart_osiris'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog(markers[i])) {
            __log_info_native('[test:259] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

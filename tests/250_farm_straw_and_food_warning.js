// OG grain harvest also sends a fixed 100-load straw cart (progress clear must not kill it).
// Farm food warning fires when floodplain food ≫ granary free space.
// Markers:
//   [test-marker] grain_straw_cart_ok
//   [test-marker] farm_food_warning_granary

var __test250_result = null

function test250_fail(reason) {
    __test250_result = { ok: false, reason: reason }
    __log_info_native('[test:250] FAIL: ' + reason)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:250] grain straw + farm food warning')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var grain_bid = test_farm_place(BUILDING_GRAIN_FARM, TERRAIN_FLOODPLAIN)
    if (!grain_bid) {
        test250_fail('no_grain_farm')
        return
    }

    __building_farm_set_progress(grain_bid, 1000)
    __test_farm_harvest_and_clear_osiris(grain_bid)

    var primary_res = __building_farm_cart_resource(grain_bid, BUILDING_SLOT_CARTPUSHER)
    var primary_amt = __building_farm_cart_amount(grain_bid, BUILDING_SLOT_CARTPUSHER)
    var straw_res = __building_farm_cart_resource(grain_bid, BUILDING_SLOT_CARTPUSHER_2)
    var straw_amt = __building_farm_cart_amount(grain_bid, BUILDING_SLOT_CARTPUSHER_2)

    if (primary_res !== RESOURCE_GRAIN || primary_amt <= 0) {
        test250_fail('primary_cart:' + primary_res + '/' + primary_amt)
        return
    }
    if (straw_res !== RESOURCE_STRAW || straw_amt !== 100) {
        test250_fail('straw_cart:' + straw_res + '/' + straw_amt)
        return
    }
    __log_info_native('[test-marker] grain_straw_cart_ok')

    // Food warning: lots of food farms, no granary capacity → #build_granaries / #build_granary
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    for (var i = 0; i < 6; i++) {
        var cx = ((__scenario_map.width / 2) | 0) + (i * 4)
        var cy = (__scenario_map.height / 2) | 0
        test_prepare_terrain_patch(cx, cy, 5, TERRAIN_FLOODPLAIN)
        var bid = test_building_place(BUILDING_GRAIN_FARM, cx - 1, cy - 1)
        if (bid) {
            __building_farm_set_progress(bid, 2000)
        }
    }
    var warn = __test_farm_food_warning()
    if (warn !== 1 && warn !== 2) {
        test250_fail('no_food_warning:' + warn)
        return
    }
    __log_info_native('[test-marker] farm_food_warning_granary')

    __test250_result = { ok: true }
    __test_signal_ready()
}

function check_valid() {
    if (!__test250_result || !__test250_result.ok) {
        return false
    }
    return __test_find_inlog('[test-marker] grain_straw_cart_ok')
        && __test_find_inlog('[test-marker] farm_food_warning_granary')
}

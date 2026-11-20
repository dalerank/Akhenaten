// OG produce(): a cursed farm does not grow; the curse counts down only on a
// staffed day (floodplain: a laborer is on the farm), and that day gives no growth.

var __test269_ok = false

function test269_fail(msg) {
    __log_info_native('[test:269] FAIL: ' + msg)
    __test_signal_ready()
}

function test269_curse(bid) {
    return __test_building_curse_days(bid)
}

function run_test() {
    __log_info_native('[test:269] farm curse OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_prepare_terrain_patch(cx, cy, 8, TERRAIN_FLOODPLAIN)
    var bid = test_building_place(BUILDING_FIGS_FARM, cx - 1, cy - 1)
    if (!bid) {
        return test269_fail('fig farm place failed')
    }
    for (var dx = 0; dx < 3; dx++) {
        for (var dy = 0; dy < 3; dy++) {
            __map_set_fertility_at({ x: cx - 1 + dx, y: cy - 1 + dy }, 80)
        }
    }

    __building_farm_set_progress(bid, 0)
    __building_farm_set_labor_days(bid, 0)
    city.get_building(bid).curse_days_left = 3
    if (test269_curse(bid) != 3) {
        return test269_fail('could not set curse days, got ' + test269_curse(bid))
    }

    for (var i = 0; i < 5; i++) {
        __test_update_farms()
    }
    if (test269_curse(bid) != 3 || __building_farm_progress(bid) != 0) {
        return test269_fail('unstaffed days must keep the curse, curse=' + test269_curse(bid)
            + ' progress=' + __building_farm_progress(bid))
    }
    __log_marker('test269_unstaffed_keeps_curse_ok')

    __building_farm_set_labor_days(bid, 40)
    for (var j = 0; j < 3; j++) {
        __test_update_farms()
    }
    if (test269_curse(bid) != 0 || __building_farm_progress(bid) != 0) {
        return test269_fail('three staffed cursed days must not grow, curse=' + test269_curse(bid)
            + ' progress=' + __building_farm_progress(bid))
    }
    __log_marker('test269_cursed_no_growth_ok')

    __test_update_farms()
    if (__building_farm_progress(bid) <= 0) {
        return test269_fail('after the curse the farm must grow, progress=' + __building_farm_progress(bid))
    }
    __log_marker('test269_grows_after_curse_ok')

    __test269_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test269_ok
        && __test_find_inlog('[test-marker] test269_unstaffed_keeps_curse_ok')
        && __test_find_inlog('[test-marker] test269_cursed_no_growth_ok')
        && __test_find_inlog('[test-marker] test269_grows_after_curse_ok')
}

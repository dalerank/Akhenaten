// Well update_animation (JS in well.js):
// play_animation follows necessity_status vs WELL_NECESSARY.
// update_month sets is_fancy from tile desirability without throwing.

var __test195_ok = false

function run_test() {
    __log_info_native('[test:195] well animation necessity')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    // Wells require groundwater; --no-resource maps often have none.
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    terrain.add({ x: cx, y: cy }, TERRAIN_GROUNDWATER)
    var bid = test_building_place(BUILDING_WELL, cx, cy)
    if (!bid) {
        bid = test_building_place(BUILDING_WELL, -1, -1)
    }
    if (!bid) {
        __log_info_native('[test:195] place failed')
        __test_signal_ready()
        return
    }

    var well = city.get_well(bid)
    if (!well) {
        __log_info_native('[test:195] FAIL: get_well returned null')
        __test_signal_ready()
        return
    }

    var status = well.necessity_status(building_well.unnecessary_range_check)
    var ev = { bid: bid }
    building_well_update_animation(ev)
    well = city.get_well(bid)

    var expect_on = (status == WELL_NECESSARY)
    if (well.play_animation != expect_on) {
        __log_info_native('[test:195] FAIL: play_animation=' + well.play_animation
            + ' status=' + status + ' expect_on=' + expect_on)
        __test_signal_ready()
        return
    }
    __log_marker('test195_animation_matches_necessity')

    try {
        building_well_update_month(ev)
    } catch (e) {
        __log_info_native('[test:195] FAIL: update_month threw ' + e)
        __test_signal_ready()
        return
    }
    well = city.get_well(bid)
    var expect_fancy = __desirability_at_tile(well.tile.x, well.tile.y) >= building_well.desirability_fancy
    if (!!well.is_fancy != expect_fancy) {
        __log_info_native('[test:195] FAIL: is_fancy=' + well.is_fancy + ' expect=' + expect_fancy)
        __test_signal_ready()
        return
    }
    __log_marker('test195_update_month_ok')

    __test195_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test195_ok
        && __test_find_inlog('[test-marker] test195_animation_matches_necessity')
        && __test_find_inlog('[test-marker] test195_update_month_ok')
}

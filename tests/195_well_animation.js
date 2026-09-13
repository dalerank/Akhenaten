// Well update_animation (JS in well.js):
// play_animation follows necessity_status vs WELL_NECESSARY.

var __test195_ok = false

function run_test() {
    __log_info_native('[test:195] well animation necessity')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_WELL, -1, -1)
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

    __test195_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test195_ok
        && __test_find_inlog('[test-marker] test195_animation_matches_necessity')
}

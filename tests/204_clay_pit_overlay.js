// Clay pit overlay_anims (JS in clay_pit.js):
// 1) Default clay overlay is seeded on place.
// 2) update_graphic removes it (and work animation) when destroy_reason is set.

var __test204_ok = false
var __test204_bid = null

function run_test() {
    __log_info_native('[test:204] clay pit overlay vs destroy_reason')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_prepare_shoreline_patch(cx, cy, 6, 2)

    __test204_bid = test_building_place(BUILDING_CLAY_PIT, cx - 1, cy - 3)
    if (!__test204_bid) {
        __log_info_native('[test:204] place failed')
        __test_signal_ready()
        return
    }

    var ev = { bid: __test204_bid }
    var b = city.get_building(__test204_bid)
    if (!b.has_overlay("clay")) {
        __log_info_native('[test:204] FAIL: clay overlay missing after place')
        __test_signal_ready()
        return
    }
    __log_marker('test204_overlay_seeded')

    b.destroy_reason = e_destroy_flooded
    b.play_animation = true
    building_clay_pit_on_update_graphic(ev)
    b = city.get_building(__test204_bid)
    if (b.has_overlay("clay")) {
        __log_info_native('[test:204] FAIL: clay overlay still present after flood')
        __test_signal_ready()
        return
    }
    if (b.play_animation) {
        __log_info_native('[test:204] FAIL: play_animation left true after flood')
        __test_signal_ready()
        return
    }
    __log_marker('test204_overlay_removed_on_flood')

    b.destroy_reason = e_destroy_simple
    building_clay_pit_on_update_graphic(ev)
    b = city.get_building(__test204_bid)
    if (!b.has_overlay("clay")) {
        __log_info_native('[test:204] FAIL: clay overlay not restored after flood')
        __test_signal_ready()
        return
    }
    __log_marker('test204_overlay_restored')

    __test204_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test204_ok
        && __test_find_inlog('[test-marker] test204_overlay_seeded')
        && __test_find_inlog('[test-marker] test204_overlay_removed_on_flood')
        && __test_find_inlog('[test-marker] test204_overlay_restored')
}

// Stone quarry extra anim (anims[0]): work_2 only while staffed above 50%.
// Markers:
//   [test-marker] stone_quarry_work_2_above_half
//   [test-marker] stone_quarry_work_2_at_half

var __test211_ok = false

function run_test() {
    __log_info_native('[test:211] stone quarry work_2 staffing')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    terrain.add({ x: cx + 2, y: cy }, TERRAIN_ROCK)
    terrain.add({ x: cx + 2, y: cy + 1 }, TERRAIN_ROCK)

    var bid = test_building_place(BUILDING_STONE_QUARRY, cx, cy)
    if (!bid) {
        bid = __test_building_create(BUILDING_STONE_QUARRY, cx, cy)
    }
    if (!bid) {
        __log_info_native('[test:211] place/create failed')
        __test_signal_ready()
        return
    }

    var max_workers = city.get_building(bid).max_workers
    var half = Math.floor(max_workers / 2)
    if (max_workers < 2) {
        __log_info_native('[test:211] max_workers=' + max_workers)
        __test_signal_ready()
        return
    }

    __test_building_set_workers(bid, half + 1)
    __test_building_update_day(bid)
    var above = __test_building_slot_anim_key(bid, 0)
    if (above != "work_2") {
        __log_info_native('[test:211] above half key=' + above + ' workers=' + (half + 1) + '/' + max_workers)
        __test_signal_ready()
        return
    }
    __log_marker('stone_quarry_work_2_above_half')

    __test_building_set_workers(bid, half)
    __test_building_update_day(bid)
    var at_half = __test_building_slot_anim_key(bid, 0)
    if (at_half == "work_2") {
        __log_info_native('[test:211] at half still work_2 workers=' + half + '/' + max_workers)
        __test_signal_ready()
        return
    }
    __log_marker('stone_quarry_work_2_at_half')

    __test211_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test211_ok
        && __test_find_inlog('[test-marker] stone_quarry_work_2_above_half')
        && __test_find_inlog('[test-marker] stone_quarry_work_2_at_half')
}

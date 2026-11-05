// Mastaba OG engine: place one brick course every 2s → COMPLETE → FINISHED.

function run_test() {
    __log_info_native('[test:260] mastaba OG full block build (layered)')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_MASTABA)) {
        __scenario_building_allow(BUILDING_SMALL_MASTABA, true)
    }

    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 5, y: cy - 2}, {x: cx - 5, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_MASTABA, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        __log_info_native('[test:260] failed to place mastaba')
        __test_signal_ready()
        return
    }

    __test_camera_center_building(bid)
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)
    var remaining0 = __pyramid_remaining_blocks(bid)
    if (remaining0 != 55) {
        __log_info_native('[test:260] expected 55 blocks, got ' + remaining0)
        __log_marker('mastaba_og_complete_init_fail:' + remaining0)
        __test_signal_ready()
        return
    }
    __log_marker('mastaba_og_complete_init_ok:55')

    // Small mastaba brick phases: 9+9+9+9+9+10 = 55
    var layers = [9, 9, 9, 9, 9, 10]
    var mon = new Monument(bid)
    var total_placed = 0
    for (var li = 0; li < layers.length; li++) {
        var n = mon.boost_engine_blocks(layers[li])
        total_placed += n
        __log_marker('mastaba_og_complete_layer:' + (li + 1) + ':' + n)
        if (li + 1 < layers.length) {
            __test_sleep_ms(2000)
        }
    }

    if (total_placed == 55) {
        __log_marker('mastaba_og_complete_boost_ok:55')
    } else {
        __log_info_native('[test:260] boost placed ' + total_placed + ' (want 55)')
        __log_marker('mastaba_og_complete_boost_fail:' + total_placed)
    }

    var rem = __pyramid_remaining_blocks(bid)
    if (rem == 0) {
        __log_marker('mastaba_og_complete_remaining_ok:0')
    } else {
        __log_marker('mastaba_og_complete_remaining_fail:' + rem)
    }

    __test_sleep_ms(2000)

    // COMPLETE (8) → finalize MONUMENT_FINISHED (-1)
    __test_building_update_day(bid)
    var ph = __test_monument_phase(bid)
    if (ph != -1) {
        __test_building_update_day(bid)
        ph = __test_monument_phase(bid)
    }
    if (ph == -1) {
        __log_marker('mastaba_og_complete_finished_ok')
    } else {
        __log_marker('mastaba_og_complete_finished_fail:' + ph)
    }

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] mastaba_og_complete_init_ok:55')
        && __test_find_inlog('[test-marker] mastaba_og_complete_boost_ok:55')
        && __test_find_inlog('[test-marker] mastaba_og_complete_remaining_ok:0')
        && __test_find_inlog('[test-marker] mastaba_og_complete_finished_ok')
}

// Pyramid block-engine state (remaining blocks, per-part blocks) survives save/load.
// Note: game load truncates akhenaten-log.txt, so the success marker is written after the load.

function run_test() {
    __log_info_native('[test:278] stepped pyramid block state saveload')
    test_reload_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_STEPPED_PYRAMID)) {
        __scenario_building_allow(BUILDING_SMALL_STEPPED_PYRAMID, true)
    }
    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 4, y: cy - 4}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_STEPPED_PYRAMID, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        __log_marker('stepped_blocks_saveload_place_fail')
        __test_signal_ready()
        return
    }

    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)
    var mon = new Monument(bid)
    var placed = mon.boost_engine_blocks(10)
    var before = __pyramid_remaining_blocks(bid)
    if (placed != 10 || before != 110) {
        __log_marker('stepped_blocks_saveload_boost_fail:' + placed + ':' + before)
        __test_signal_ready()
        return
    }

    var save_name = 'test_278_stepped_blocks.svx'
    if (!__game_write_savegame(save_name) || !__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        __log_marker('stepped_blocks_saveload_skipped')
        __test_signal_ready()
        return
    }
    __game_delete_savegame(save_name)

    __test_pump_frames(20)
    var after = __pyramid_remaining_blocks(bid)
    if (after == before) {
        __log_marker('stepped_blocks_saveload_ok:' + after)
    } else {
        __log_marker('stepped_blocks_saveload_fail:' + before + '->' + after)
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] stepped_blocks_saveload_ok:110')
}

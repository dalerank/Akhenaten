// OG sun temple: 100 chained parts from the part-desc table, 220 sandstone to place,
// completed temple blocks a second, stage-0 carpenter spot (260 ticks).

var __t296_ok = false

function t296_fail(msg) {
    __log_info_native('[test:296] FAIL: ' + msg)
    __test_signal_ready()
}

function t296_work_until_leaves(bid, fid, limit) {
    for (var i = 0; i < limit; i++) {
        if (__test_sun_temple_work(bid, fid) != 0) {
            return i + 1
        }
    }
    return -1
}

function run_test() {
    __log_info_native('[test:296] OG sun temple')
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_SUN_TEMPLE)) {
        __scenario_building_allow(BUILDING_SUN_TEMPLE, true)
    }
    if (!__scenario_building_allowed(BUILDING_STORAGE_YARD)) {
        __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    }
    __test_set_treasury(50000)

    var need = 220
    var sy = 0
    var yard_spots = [
        {x: 8, y: 8}, {x: 12, y: 12}, {x: 20, y: 8}, {x: 8, y: 40}
    ]
    for (var yi = 0; yi < yard_spots.length && !sy; yi++) {
        sy = test_staffed_yard_with_resource(RESOURCE_SANDSTONE, need, yard_spots[yi].x, yard_spots[yi].y)
    }
    if (!sy) {
        sy = test_staffed_yard_with_resource(RESOURCE_SANDSTONE, need, -1, -1)
    }
    if (!sy) {
        return t296_fail('sandstone yard')
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    // Origin must leave room for part offsets (dx -6..4, dy -9..9).
    var candidates = [
        {x: cx, y: cy},
        {x: 40, y: 40},
        {x: 50, y: 50},
        {x: 60, y: 45},
        {x: 30, y: 50}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SUN_TEMPLE, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        return t296_fail('place failed')
    }

    var parts = __test_sun_temple_part_count(bid)
    if (parts != 100) {
        return t296_fail('expected 100 parts, got ' + parts)
    }
    __log_marker('t296_100_parts')

    if (__test_sun_temple_stage(bid) != 0) {
        return t296_fail('initial stage ' + __test_sun_temple_stage(bid))
    }
    if (!__test_sun_temple_has_spot(bid, FIGURE_CARPENTER) || __test_sun_temple_has_spot(bid, FIGURE_STONEMASON)) {
        return t296_fail('stage 0 must want a carpenter only')
    }
    __log_marker('t296_stage0_carpenter')

    var t0 = __building_tile(bid)
    var carpenter = __test_figure_create(FIGURE_CARPENTER, t0.x, t0.y + 6)
    for (var w = 0; w < 100; w++) {
        if (__test_sun_temple_work(bid, carpenter) != 0) {
            return t296_fail('stage 0 spot emptied early at tick ' + w)
        }
    }
    var work0 = __test_sun_temple_spot_work(bid, 0)
    var fig0 = __test_sun_temple_spot_figure(bid, 0)
    if (work0 != 160 || fig0 != carpenter) {
        return t296_fail('before save: spot0 work ' + work0 + ' fig ' + fig0 + ' (want 160 / ' + carpenter + ')')
    }

    var save_name = 'test_296_sun_temple_spots.svx'
    if (__game_write_savegame(save_name) && __game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        if (__building_type(bid) != BUILDING_SUN_TEMPLE
            || __test_sun_temple_stage(bid) != 0
            || __test_sun_temple_spot_work(bid, 0) != work0
            || __test_sun_temple_spot_figure(bid, 0) != carpenter) {
            return t296_fail('after load: stage ' + __test_sun_temple_stage(bid)
                + ' work ' + __test_sun_temple_spot_work(bid, 0)
                + ' fig ' + __test_sun_temple_spot_figure(bid, 0))
        }
        __log_marker('t296_saveload_ok')
    } else {
        __log_marker('t296_saveload_skipped')
    }

    var worked = t296_work_until_leaves(bid, carpenter, 1000)
    if (worked != 160 || __test_sun_temple_stage(bid) != 1) {
        return t296_fail('stage 0 spot: worked ' + worked + ' stage ' + __test_sun_temple_stage(bid))
    }
    __log_marker('t296_stage0_260_ticks')

    // OG: a completed temple blocks a new one (percent == 100 / finished).
    __test_monument_set_phase(bid, -1)
    if (test_building_place(BUILDING_SUN_TEMPLE, 20, 60)) {
        return t296_fail('second sun temple placed after completed')
    }
    __log_marker('t296_only_one_completed')

    __t296_ok = true
    __log_info_native('[test:296] PASS')
    __test_signal_ready()
}

function check_valid() {
    // Assertions already gated run_test (fail → early return, __t296_ok stays false).
    // Avoid __test_find_inlog here: with a multi-MB akhenaten-log.txt the seek-from-mark
    // path can miss markers that are present on disk after the process exits.
    return !!__t296_ok
}

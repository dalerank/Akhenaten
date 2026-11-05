// Medium true (smooth) pyramid — place, height→polish→finish.
// Height courses through 31 (like medium stepped); polish 32–34 (3 layers);
// terminal 35; finish = set_phase(phases_total).

function find_medium_true_pyramid_main() {
    for (var bi = 1; bi < 500; bi++) {
        if (__building_type(bi) != BUILDING_MEDIUM_PYRAMID) continue
        var b = city.get_building(bi)
        if (b && !b.prev_part_building_id) return bi
    }
    return 0
}

function run_test() {
    __log_info_native('[test:109] medium true pyramid place + phase walk (height→polish→finish)')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_MEDIUM_PYRAMID)) {
        __scenario_building_allow(BUILDING_MEDIUM_PYRAMID, true)
    }

    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 6, y: cy - 6}, {x: cx, y: cy}, {x: 36, y: 36}, {x: 28, y: 28}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_MEDIUM_PYRAMID, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_MEDIUM_PYRAMID, -1, -1)
    }
    if (!bid) {
        __log_info_native('[test:109] failed to place BUILDING_MEDIUM_PYRAMID')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    __log_marker('true_pyramid_medium_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    if (__building_type(bid) != BUILDING_MEDIUM_PYRAMID) {
        __log_info_native('[test:109] unexpected type ' + __building_type(bid))
        __test_signal_ready()
        return
    }

    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 128) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    // 12×12 / 2×2 = 36 parts
    if (parts.length >= 30) {
        __log_marker('true_pyramid_medium_parts_ok:' + parts.length)
    } else {
        __log_marker('true_pyramid_medium_parts_fail:' + parts.length)
    }

    var mon0 = city.get_monument(bid)
    if (!mon0) {
        __log_info_native('[test:109] city.get_monument failed')
        __test_signal_ready()
        return
    }
    var total = mon0.phases_total()
    // height 0–31 + polish 32–34 + terminal → phases_total >= 35
    if (total < 35) {
        __log_info_native('[test:109] phases_total=' + total + ' want >=35')
        __log_marker('true_pyramid_medium_schedule_fail:' + total)
        __test_signal_ready()
        return
    }
    __log_marker('true_pyramid_medium_schedule_ok:' + total)

    var all_ok = true
    var check_phases = [0, 2, 12, 24, 31, 32, 34]
    for (var ci = 0; ci < check_phases.length; ci++) {
        var want = check_phases[ci]
        __test_monument_set_phase(bid, want)
        __test_pump_frames(2)
        var got = __test_monument_phase(bid)
        if (got != want) {
            __log_info_native('[test:109] phase want ' + want + ' got ' + got)
            all_ok = false
        }
    }

    __test_monument_set_phase(bid, total)
    __test_pump_frames(2)
    var fin = __test_monument_phase(bid)
    if (fin != -1 && fin != 255) {
        __log_info_native('[test:109] finish want -1 after set_phase(total), got ' + fin)
        all_ok = false
    }
    __log_marker('true_pyramid_medium_finish_phase:' + fin)

    if (all_ok) {
        __log_marker('true_pyramid_medium_phases_ok')
    } else {
        __log_marker('true_pyramid_medium_phases_fail')
    }

    // Polish mid-band @32: no limestone/stone; guild must still request stonemasons.
    // set_phase fills tiles to 200 → park mid-progress before any day tick / pump.
    __test_monument_set_phase(bid, 32)
    __test_monument_set_all_progress(bid, 50)
    __test_pump_frames(2)
    var mon32 = city.get_monument(bid)
    if (mon32 && mon32.phase() == 32) {
        var pct = mon32.material_pct_min()
        if (pct == 100) {
            __log_marker('true_pyramid_medium_polish_no_lime_ok')
        } else {
            __log_marker('true_pyramid_medium_polish_pct_fail:' + pct)
        }
        if (mon32.need_stonemason()) {
            __log_marker('true_pyramid_medium_polish_mason_ok')
        } else {
            __log_marker('true_pyramid_medium_polish_mason_fail')
        }
    } else {
        __log_marker('true_pyramid_medium_polish_phase_fail')
    }

    var save_name = 'test_109_true_pyramid_medium_polish.svx'
    if (!__game_write_savegame(save_name)) {
        __log_marker('true_pyramid_medium_saveload_skipped')
    } else if (!__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        __log_marker('true_pyramid_medium_saveload_skipped')
    } else {
        __game_delete_savegame(save_name)
        var found = find_medium_true_pyramid_main()
        var ph = found ? __test_monument_phase(found) : -999
        if (!found || ph != 32) {
            __log_info_native('[test:109] after load found=' + found + ' phase=' + ph)
            __log_marker('true_pyramid_medium_saveload_fail:' + ph)
        } else {
            __log_marker('true_pyramid_medium_saveload_ok:' + found)
            bid = found
        }
    }

    // Remake polish day-tick finish retired — OG square block engine owns phase>=2
    // (see tests/267_true_medium_pyramid_og_complete.js).

    __log_info_native('[test:109] done')
    __test_signal_ready()
}

function check_valid() {
    var required = [
        'true_pyramid_medium_placed_ok',
        'true_pyramid_medium_schedule_ok',
        'true_pyramid_medium_phases_ok',
        'true_pyramid_medium_polish_no_lime_ok',
        'true_pyramid_medium_polish_mason_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:109] missing: ' + required[i])
            return false
        }
    }
    if (__test_find_inlog('true_pyramid_medium_phases_fail')
        || __test_find_inlog('true_pyramid_medium_polish_pct_fail')
        || __test_find_inlog('true_pyramid_medium_polish_mason_fail')
        || __test_find_inlog('true_pyramid_medium_saveload_fail')) {
        return false
    }
    if (!__test_find_inlog('true_pyramid_medium_saveload_skipped')
        && !__test_find_inlog('true_pyramid_medium_saveload_ok')) {
        __log_info_native('[test:109] missing saveload marker')
        return false
    }
    return true
}

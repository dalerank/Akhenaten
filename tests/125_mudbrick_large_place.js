// Large mudbrick (brick-core) pyramid — 16×16 place, height→polish→finish.
// Height courses through 35; polish 36–39 (4 layers); terminal 40;
// finish = set_phase(phases_total); block-engine finish lives in the OG complete tests.

function find_large_mudbrick_pyramid_main() {
    for (var bi = 1; bi < 500; bi++) {
        if (__building_type(bi) != BUILDING_LARGE_MUDBRICK_PYRAMID) continue
        var b = city.get_building(bi)
        if (b && !b.prev_part_building_id) return bi
    }
    return 0
}

function run_test() {
    __log_info_native('[test:125] large mudbrick pyramid place + phase walk (height→polish→finish)')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_LARGE_MUDBRICK_PYRAMID)) {
        __scenario_building_allow(BUILDING_LARGE_MUDBRICK_PYRAMID, true)
    }

    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 8, y: cy - 8}, {x: cx, y: cy}, {x: 32, y: 32}, {x: 24, y: 24}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_LARGE_MUDBRICK_PYRAMID, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_LARGE_MUDBRICK_PYRAMID, -1, -1)
    }
    if (!bid) {
        __log_info_native('[test:125] failed to place BUILDING_LARGE_MUDBRICK_PYRAMID')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    __log_marker('mudbrick_pyramid_large_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    if (__building_type(bid) != BUILDING_LARGE_MUDBRICK_PYRAMID) {
        __log_info_native('[test:125] unexpected type ' + __building_type(bid))
        __test_signal_ready()
        return
    }

    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 128) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    // 16×16 / 2×2 = 64 parts
    if (parts.length >= 50) {
        __log_marker('mudbrick_pyramid_large_parts_ok:' + parts.length)
    } else {
        __log_marker('mudbrick_pyramid_large_parts_fail:' + parts.length)
    }

    var mon0 = city.get_monument(bid)
    if (!mon0) {
        __log_info_native('[test:125] city.get_monument failed')
        __test_signal_ready()
        return
    }
    var total = mon0.phases_total()
    // height 0–35 + polish 36–39 + terminal → phases_total >= 40
    if (total < 40) {
        __log_info_native('[test:125] phases_total=' + total + ' want >=40')
        __log_marker('mudbrick_pyramid_large_schedule_fail:' + total)
        __test_signal_ready()
        return
    }
    __log_marker('mudbrick_pyramid_large_schedule_ok:' + total)

    var all_ok = true
    var check_phases = [0, 2, 12, 24, 35, 36, 39]
    for (var ci = 0; ci < check_phases.length; ci++) {
        var want = check_phases[ci]
        __test_monument_set_phase(bid, want)
        __test_pump_frames(2)
        var got = __test_monument_phase(bid)
        if (got != want) {
            __log_info_native('[test:125] phase want ' + want + ' got ' + got)
            all_ok = false
        }
    }

    __test_monument_set_phase(bid, total)
    __test_pump_frames(2)
    var fin = __test_monument_phase(bid)
    if (fin != -1 && fin != 255) {
        __log_info_native('[test:125] finish want -1 after set_phase(total), got ' + fin)
        all_ok = false
    }
    __log_marker('mudbrick_pyramid_large_finish_phase:' + fin)

    if (all_ok) {
        __log_marker('mudbrick_pyramid_large_phases_ok')
    } else {
        __log_marker('mudbrick_pyramid_large_phases_fail')
    }

    // Polish mid-band @36: no limestone/bricks required → material_pct_min 100
    // set_phase fills tiles to 200 → park mid-progress before any day tick / pump.
    __test_monument_set_phase(bid, 36)
    __test_monument_set_all_progress(bid, 50)
    __test_pump_frames(2)
    var mon36 = city.get_monument(bid)
    if (mon36 && mon36.phase() == 36) {
        var pct = mon36.material_pct_min()
        if (pct == 100) {
            __log_marker('mudbrick_pyramid_large_polish_no_lime_ok')
        } else {
            __log_marker('mudbrick_pyramid_large_polish_pct_fail:' + pct)
        }
    } else {
        __log_marker('mudbrick_pyramid_large_polish_phase_fail')
    }

    var save_name = 'test_125_mudbrick_pyramid_large_polish.svx'
    if (!__game_write_savegame(save_name)) {
        __log_marker('mudbrick_pyramid_large_saveload_skipped')
    } else if (!__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        __log_marker('mudbrick_pyramid_large_saveload_skipped')
    } else {
        __game_delete_savegame(save_name)
        var found = find_large_mudbrick_pyramid_main()
        var ph = found ? __test_monument_phase(found) : -999
        if (!found || ph != 36) {
            __log_info_native('[test:125] after load found=' + found + ' phase=' + ph)
            __log_marker('mudbrick_pyramid_large_saveload_fail:' + ph)
        } else {
            __log_marker('mudbrick_pyramid_large_saveload_ok:' + found)
            bid = found
        }
    }

    // Remake polish day-tick finish retired — OG square block engine owns phase>=2
    // (see tests/264_mudbrick_large_pyramid_og_complete.js).

    __log_info_native('[test:125] done')
    __test_signal_ready()
}

function check_valid() {
    var required = [
        'mudbrick_pyramid_large_placed_ok',
        'mudbrick_pyramid_large_schedule_ok',
        'mudbrick_pyramid_large_phases_ok',
        'mudbrick_pyramid_large_polish_no_lime_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:125] missing: ' + required[i])
            return false
        }
    }
    if (__test_find_inlog('mudbrick_pyramid_large_phases_fail')
        || __test_find_inlog('mudbrick_pyramid_large_polish_pct_fail')
        || __test_find_inlog('mudbrick_pyramid_large_saveload_fail')) {
        return false
    }
    if (!__test_find_inlog('mudbrick_pyramid_large_saveload_skipped')
        && !__test_find_inlog('mudbrick_pyramid_large_saveload_ok')) {
        __log_info_native('[test:125] missing saveload marker')
        return false
    }
    return true
}

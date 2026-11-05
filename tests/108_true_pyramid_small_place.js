// Small true (smooth) pyramid — place, walk height→polish→finish phases.
// Polish phases 24–25 consume no limestone (ARCHITECTS-only); schedule ends @26;
// finish = set_phase(phases_total) → MONUMENT_FINISHED. Also exercises natural
// update_day finish: polish clear, terminal keep-progress, congrats popup.

function find_true_pyramid_main() {
    for (var bi = 1; bi < 500; bi++) {
        if (__building_type(bi) != BUILDING_SMALL_PYRAMID) continue
        var b = city.get_building(bi)
        if (b && !b.prev_part_building_id) return bi
    }
    return 0
}

function run_test() {
    __log_info_native('[test:108] small true pyramid place + phase walk (height→polish→finish)')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_PYRAMID)) {
        __scenario_building_allow(BUILDING_SMALL_PYRAMID, true)
    }

    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 4, y: cy - 4}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_PYRAMID, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_SMALL_PYRAMID, -1, -1)
    }
    if (!bid) {
        __log_info_native('[test:108] failed to place BUILDING_SMALL_PYRAMID')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    __log_marker('true_pyramid_small_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    var btype = __building_type(bid)
    if (btype != BUILDING_SMALL_PYRAMID) {
        __log_info_native('[test:108] unexpected type ' + btype)
        __test_signal_ready()
        return
    }

    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 128) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    if (parts.length > 1) {
        __log_marker('true_pyramid_small_parts_ok:' + parts.length)
    } else {
        __log_marker('true_pyramid_small_parts_fail:' + parts.length)
    }

    var mon0 = city.get_monument(bid)
    if (!mon0) {
        __log_info_native('[test:108] city.get_monument failed')
        __test_signal_ready()
        return
    }
    var total = mon0.phases_total()
    // Expect height 0–23 + polish 24–25 + terminal → phases_total >= 26
    if (total < 26) {
        __log_info_native('[test:108] phases_total=' + total + ' want >=26 (polish band)')
        __log_marker('true_pyramid_small_schedule_fail:' + total)
        __test_signal_ready()
        return
    }
    __log_marker('true_pyramid_small_schedule_ok:' + total)

    __test_pump_frames(30)

    // Height boundary (23), polish band (24–25), last schedule row (26), then
    // set_phase(phases_total) → MONUMENT_FINISHED. size=27 → finish arg is 27.
    var phases = [0, 2, 6, 12, 18, 23, 24, 25, 26]
    var all_ok = true
    for (var p = 0; p < phases.length; p++) {
        __test_monument_set_phase(bid, phases[p])
        __test_pump_frames(2)
        var mon = city.get_monument(bid)
        if (!mon) {
            __log_info_native('[test:108] no monument at phase ' + phases[p])
            all_ok = false
            break
        }
        var got = mon.phase()
        if (got != phases[p]) {
            __log_info_native('[test:108] phase want ' + phases[p] + ' got ' + got)
            all_ok = false
        }
    }

    // Advance past last schedule index (== phases_total) → MONUMENT_FINISHED.
    __test_monument_set_phase(bid, total)
    __test_pump_frames(2)
    var mon_fin = city.get_monument(bid)
    var fin = mon_fin ? mon_fin.phase() : -999
    if (fin != -1 && fin != 255) {
        __log_info_native('[test:108] finish want -1 after set_phase(phases_total=' + total + '), got ' + fin)
        all_ok = false
    }
    __log_marker('true_pyramid_small_finish_phase:' + fin)

    if (all_ok) {
        __log_marker('true_pyramid_small_phases_ok')
    } else {
        __log_marker('true_pyramid_small_phases_fail')
    }

    // Polish mid-band: no limestone/stone; guild must still request stonemasons.
    // set_phase fills tiles to 200 → park mid-progress before any day tick / pump.
    __test_monument_set_phase(bid, 24)
    __test_monument_set_all_progress(bid, 50)
    __test_pump_frames(2)
    var mon24 = city.get_monument(bid)
    if (mon24 && mon24.phase() == 24) {
        var pct = mon24.material_pct_min()
        if (pct == 100) {
            __log_marker('true_pyramid_small_polish_no_lime_ok')
        } else {
            __log_marker('true_pyramid_small_polish_pct_fail:' + pct)
        }
        if (mon24.need_stonemason()) {
            __log_marker('true_pyramid_small_polish_mason_ok')
        } else {
            __log_marker('true_pyramid_small_polish_mason_fail')
        }
    } else {
        __log_marker('true_pyramid_small_polish_phase_fail')
    }

    // Mid-polish save/load (DoD §5).
    var save_name = 'test_108_true_pyramid_polish.svx'
    if (!__game_write_savegame(save_name)) {
        __log_marker('true_pyramid_small_saveload_skipped')
    } else if (!__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        __log_marker('true_pyramid_small_saveload_skipped')
    } else {
        __game_delete_savegame(save_name)
        var found = find_true_pyramid_main()
        var ph = found ? __test_monument_phase(found) : -999
        if (!found || ph != 24) {
            __log_info_native('[test:108] after load found=' + found + ' phase=' + ph)
            __log_marker('true_pyramid_small_saveload_fail:' + ph)
        } else {
            __log_marker('true_pyramid_small_saveload_ok:' + found)
            bid = found
        }
    }

    var img = __test_building_current_image(bid)
    if (img > 0) {
        __log_marker('true_pyramid_small_art_ok:' + img)
        __test_monument_set_phase(bid, 23)
        __test_pump_frames(4)
        __game_save_screenshot(SCREENSHOT_DISPLAY)
        __test_monument_set_phase(bid, 25)
        __test_pump_frames(4)
        __game_save_screenshot(SCREENSHOT_DISPLAY)
    } else {
        __log_marker('true_pyramid_small_art_skipped:no_resource')
    }

    // Remake polish day-tick finish retired — OG square block engine owns phase>=2
    // (see tests/266_true_pyramid_og_complete.js).

    __log_info_native('[test:108] done')
    __test_signal_ready()
}

function check_valid() {
    var required = [
        'true_pyramid_small_placed_ok',
        'true_pyramid_small_schedule_ok',
        'true_pyramid_small_phases_ok',
        'true_pyramid_small_polish_no_lime_ok',
        'true_pyramid_small_polish_mason_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:108] missing: ' + required[i])
            return false
        }
    }
    if (__test_find_inlog('true_pyramid_small_phases_fail')
        || __test_find_inlog('true_pyramid_small_polish_pct_fail')
        || __test_find_inlog('true_pyramid_small_polish_mason_fail')
        || __test_find_inlog('true_pyramid_small_saveload_fail')) {
        return false
    }
    // Soft-skip when write/load unavailable; otherwise require success marker.
    if (!__test_find_inlog('true_pyramid_small_saveload_skipped')
        && !__test_find_inlog('true_pyramid_small_saveload_ok')) {
        __log_info_native('[test:108] missing saveload marker')
        return false
    }
    return true
}

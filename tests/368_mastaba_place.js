// Small mastaba multi-part monument — place via planner, verify linked parts,
// image_stick resolves (#431), walk construction phases, and capture screenshots.

function run_test() {
    __log_info_native('[test:368] small mastaba place + parts + image_stick + phases')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_MASTABA)) {
        __scenario_building_allow(BUILDING_SMALL_MASTABA, true)
    }

    __test_set_treasury(500000)

    // Mastaba pack for per-phase art; General for image_stick (pharaoh_general/plazatiles_*).
    __image_request_pak(PACK_MASTABA)
    __image_request_pak(PACK_GENERAL)
    __test_pump_frames(4)

    // Footprint init_tiles [10, 4] (orientation 0) — prefer map centre.
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 5, y: cy - 2}, {x: cx - 5, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}, {x: 20, y: 40}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_MASTABA, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_SMALL_MASTABA, -1, -1)
    }
    if (!bid) {
        __log_info_native('[test:368] failed to place BUILDING_SMALL_MASTABA')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    __log_marker('mastaba_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    // config_north has 10 entries (main + wall/entrance/side parts).
    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 16) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    if (parts.length == 10) {
        __log_marker('mastaba_parts_ok:10')
    } else {
        __log_info_native('[test:368] expected 10 parts, got ' + parts.length)
        __log_marker('mastaba_parts_fail:' + parts.length)
    }

    // Each part type must declare building_size:2 (omitted → size 0 → thin strip on map).
    var part_types = [
        BUILDING_SMALL_MASTABA,
        BUILDING_SMALL_MASTABA_SIDE,
        BUILDING_SMALL_MASTABA_WALL,
        BUILDING_SMALL_MASTABA_ENTRANCE
    ]
    var size_ok = true
    for (var si = 0; si < part_types.length; si++) {
        var psz = __building_static_building_size(part_types[si])
        if (psz != 2) {
            size_ok = false
            __log_info_native('[test:368] type ' + part_types[si] + ' building_size=' + psz)
        }
    }
    if (size_ok) {
        __log_marker('mastaba_parts_size_ok')
    } else {
        __log_marker('mastaba_parts_size_fail')
    }

    // #431: image_stick must resolve (was mastaba/pyramid_phase_one_00021 — missing).
    // Under --no-resource image_id_from_group stubs to 0 (first_img always 0; get_image may
    // still return a placeholder object with tid=0) — skip unless the asset really resolves.
    var params = city.get_building_params_by_type(BUILDING_SMALL_MASTABA)
    var stick_img = params.first_img('image_stick')
    var plazatiles = get_image('pharaoh_general/plazatiles_00064')
    var plazatiles_tid = (plazatiles && plazatiles.tid) ? plazatiles.tid : 0
    if (stick_img > 0) {
        __log_marker('mastaba_image_stick_ok:' + stick_img)
    } else if (plazatiles_tid > 0) {
        __log_info_native('[test:368] plazatiles tid=' + plazatiles_tid + ' but image_stick first_img=0')
        __log_marker('mastaba_image_stick_fail')
    } else {
        __log_info_native('[test:368] plazatiles unavailable (--no-resource) — skipping image_stick check')
        __log_marker('mastaba_image_stick_skipped:no_resource')
    }

    // Walk construction stages. Phase 8 triggers finalize (MONUMENT_FINISHED = -1).
    __test_monument_set_phase(bid, 1)
    __test_pump_frames(2)
    var art_available = __test_building_current_image(bid) > 0

    if (art_available) {
        var phases = [1, 2, 3, 4, 5, 6, 7, 8]
        var all_stages_ok = true
        for (var p = 0; p < phases.length; p++) {
            __test_monument_set_phase(bid, phases[p])
            __test_pump_frames(2)
            var got_phase = __test_monument_phase(bid)
            // After phase 8, finalize sets MONUMENT_FINISHED (-1).
            var phase_ok = (phases[p] == 8) ? (got_phase == -1) : (got_phase == phases[p])
            if (!phase_ok) {
                all_stages_ok = false
                __log_info_native('[test:368] stage ' + phases[p] + ' phase got=' + got_phase)
                __log_marker('mastaba_stage' + phases[p] + '_phase_fail:' + got_phase)
            }
            var stage_ok = phase_ok
            for (var k = 0; k < parts.length; k++) {
                var img = __test_building_current_image(parts[k])
                if (img <= 0) {
                    stage_ok = false
                    all_stages_ok = false
                    __log_info_native('[test:368] stage ' + phases[p] + ' part ' + parts[k] + ' img=' + img)
                }
            }
            __log_marker('mastaba_stage' + phases[p] + (stage_ok ? '_art_ok' : '_art_fail'))
        }
        if (all_stages_ok) {
            __log_marker('mastaba_all_stages_art_ok')
        }
    } else {
        __log_info_native('[test:368] art packs not loaded (--no-resource) — skipping per-stage art check')
        __log_marker('mastaba_art_skipped:no_resource')
    }

    // Deliver bricks into the monument (phase 2 requirement: 4800).
    __test_monument_set_phase(bid, 2)
    if (__test_monument_add_resource(bid, RESOURCE_BRICKS, 4800)) {
        var pct = __test_monument_resource_pct(bid, RESOURCE_BRICKS)
        if (pct >= 100) {
            __log_marker('mastaba_bricks_ok:' + pct)
        } else {
            __log_info_native('[test:368] bricks pct expected >=100, got ' + pct)
            __log_marker('mastaba_bricks_pct:' + pct)
        }
    } else {
        __log_info_native('[test:368] __test_monument_add_resource bricks failed')
        __log_marker('mastaba_bricks_fail')
    }

    __test_show_tile_info(bid)
    __test_pump_frames(6)
    window_go_back()
    __test_pump_frames(2)
    __log_marker('mastaba_info_ok')

    // Finished monument (phase 8 → finalize / MONUMENT_FINISHED). Display shot must be
    // the completed mastaba — mid-phase was confusing ("only half built").
    __test_monument_set_phase(bid, 8)
    var fin_phase = __test_monument_phase(bid)
    if (fin_phase == -1) {
        __log_marker('mastaba_finished_ok')
    } else {
        __log_info_native('[test:368] expected finished phase -1, got ' + fin_phase)
        __log_marker('mastaba_finished_fail:' + fin_phase)
    }
    __test_pump_frames(2)
    __test_camera_center_building(bid)
    __test_process_events()
    window_go_back()
    __test_pump_frames(10)
    __game_save_screenshot(SCREENSHOT_DISPLAY)
    __test_pump_frames(2)
    __log_marker('mastaba_screenshot_done')

    __game_save_screenshot(SCREENSHOT_FULL_CITY)
    __test_pump_frames(2)
    __log_marker('mastaba_city_screenshot_done')

    __test_signal_ready()
}

function check_valid() {
    var required = [
        'mastaba_placed_ok',
        'mastaba_parts_ok:10',
        'mastaba_parts_size_ok',
        'mastaba_bricks_ok',
        'mastaba_info_ok',
        'mastaba_finished_ok',
        'mastaba_screenshot_done'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:368] missing marker: ' + required[i])
            return false
        }
    }
    var stick_ok = __test_find_inlog('mastaba_image_stick_ok')
    var stick_skipped = __test_find_inlog('mastaba_image_stick_skipped:no_resource')
    if (!stick_ok && !stick_skipped) {
        __log_info_native('[test:368] missing image_stick marker (neither ok nor skip)')
        return false
    }
    var art_ok = __test_find_inlog('mastaba_all_stages_art_ok')
    var art_skipped = __test_find_inlog('mastaba_art_skipped:no_resource')
    if (!art_ok && !art_skipped) {
        __log_info_native('[test:368] missing art marker (neither all_stages_art_ok nor skip)')
        return false
    }
    return true
}

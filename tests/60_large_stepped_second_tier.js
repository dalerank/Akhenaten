// Second-tier pipeline: place Large Stepped Pyramid (16x16), walk through
// layer-0 bricks and into layer-1 (phase 17 = full second tier), screenshot.
//
// Zoom convention: higher percentage = farther out (25 close-up … 250 far).
// Run WITH Pharaoh data + writable screenshot dir:
//   build\Debug\akhenaten.exe --integraltests --integraltest-only 60_large_stepped_second_tier ^
//     --nointro --nomouse --no-logo --nosound --nocrashdlg --window --size 1000x750 ^
//     --screenshot-dir d:/Work/Akhenaten/tmp/second_tier_shot "d:/Work/Cleop"

function run_test() {
    __log_info_native('[test:60] large stepped — build second tier + screenshot')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_LARGE_STEPPED_PYRAMID)) {
        __scenario_building_allow(BUILDING_LARGE_STEPPED_PYRAMID, true)
    }
    __test_set_treasury(500000)

    var foot = 16
    var cx = ((__scenario_map.width - foot) / 2) | 0
    var cy = ((__scenario_map.height - foot) / 2) | 0

    // Zoom out + aim map centre *before* place so the 20×20 footprint fits on screen.
    __camera_sidebar_collapsed(1)
    __zoom_set(180)
    __test_pump_frames(20)
    city.camera_go_to({x: cx + (foot / 2) | 0, y: cy + (foot / 2) | 0})
    __test_pump_frames(20)

    var bid = test_building_place(BUILDING_LARGE_STEPPED_PYRAMID, cx, cy)
    if (!bid) {
        var candidates = [
            {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}, {x: 60, y: 40}
        ]
        for (var i = 0; i < candidates.length && !bid; i++) {
            bid = test_building_place(BUILDING_LARGE_STEPPED_PYRAMID, candidates[i].x, candidates[i].y)
        }
    }
    if (!bid) {
        bid = test_building_place(BUILDING_LARGE_STEPPED_PYRAMID, -1, -1)
    }
    if (!bid) {
        __log_info_native('[test:60] failed to place BUILDING_LARGE_STEPPED_PYRAMID')
        __log_marker('second_tier_place_fail')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    __log_marker('second_tier_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    __test_pump_frames(30)

    __test_monument_set_phase(bid, 17)
    __test_pump_frames(4)

    var got_phase = __test_monument_phase(bid)
    if (got_phase != 17) {
        __log_info_native('[test:60] expected phase 17, got ' + got_phase)
        __log_marker('second_tier_phase_fail:' + got_phase)
    } else {
        __log_marker('second_tier_phase_ok:17')
    }

    // Inner ring at main+(2,2) should be on layer 1 after phase 12.
    var inner = city.get_building_at(tile.x + 2, tile.y + 2)
    if (inner && inner.id) {
        __log_marker('second_tier_inner_ok:' + inner.id)
    } else {
        __log_marker('second_tier_inner_fail')
    }

    if (__test_building_current_image(bid) <= 0) {
        __log_info_native('[test:60] art packs not loaded (--no-resource) — skipping screenshot')
        __log_marker('second_tier_art_skipped:no_resource')
        __test_signal_ready()
        return
    }
    __log_marker('second_tier_art_ok')

    __test_process_events()
    window_go_back()
    __zoom_set(180)
    __test_pump_frames(10)
    __test_camera_center_building(bid)
    __test_pump_frames(8)
    __game_save_screenshot(SCREENSHOT_DISPLAY)
    __log_marker('second_tier_screenshot_display_done')

    __test_pump_frames(2)
    __game_save_screenshot(SCREENSHOT_FULL_CITY)
    __log_marker('second_tier_screenshot_fullcity_done')
    __log_marker('second_tier_screenshot_done')

    __test_signal_ready()
}

function check_valid() {
    if (!__test_find_inlog('second_tier_placed_ok')) {
        __log_info_native('[test:60] missing marker: second_tier_placed_ok')
        return false
    }
    if (!__test_find_inlog('second_tier_phase_ok')) {
        __log_info_native('[test:60] missing marker: second_tier_phase_ok')
        return false
    }
    if (__test_find_inlog('second_tier_art_skipped:no_resource')) {
        return true
    }
    if (!__test_find_inlog('second_tier_art_ok')) {
        __log_info_native('[test:60] missing marker: second_tier_art_ok')
        return false
    }
    if (!__test_find_inlog('second_tier_screenshot_done')) {
        __log_info_native('[test:60] missing marker: second_tier_screenshot_done')
        return false
    }
    return true
}

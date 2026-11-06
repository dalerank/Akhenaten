// Large stepped — fifth / apex tier (layer 4). Phase 30 retargets the inner 4×4
// to layer=4; phase 35 = full apex brick tier.
//
// Zoom: higher % = farther out. Mirror camera plumbing from test 60.
//   build\Debug\akhenaten.exe --integraltests --integraltest-only 63_large_stepped_fifth_tier ^
//     --nointro --nomouse --no-logo --nosound --nocrashdlg --window --size 1000x750 ^
//     --screenshot-dir d:/Work/Akhenaten/tmp/fifth_tier_shot "d:/Work/Cleop"

function run_test() {
    __log_info_native('[test:63] large stepped — build fifth tier + screenshot')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_LARGE_STEPPED_PYRAMID)) {
        __scenario_building_allow(BUILDING_LARGE_STEPPED_PYRAMID, true)
    }
    __test_set_treasury(500000)

    var foot = 16
    var cx = ((__scenario_map.width - foot) / 2) | 0
    var cy = ((__scenario_map.height - foot) / 2) | 0

    __camera_sidebar_collapsed(1)
    __zoom_set(180)
    __test_pump_frames(20)
    city.camera_go_to({x: cx + (foot / 2) | 0, y: cy + (foot / 2) | 0})
    __test_pump_frames(20)

    var bid = test_building_place(BUILDING_LARGE_STEPPED_PYRAMID, cx, cy)
    if (!bid) {
        bid = test_building_place(BUILDING_LARGE_STEPPED_PYRAMID, -1, -1)
    }
    if (!bid) {
        __log_info_native('[test:63] failed to place BUILDING_LARGE_STEPPED_PYRAMID')
        __log_marker('fifth_tier_place_fail')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    __log_marker('fifth_tier_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    __test_pump_frames(30)

    // Level 5 = layer 4 apex, full brick course at phase 35.
    __test_monument_set_phase(bid, 35)
    __test_pump_frames(4)

    var got_phase = __test_monument_phase(bid)
    if (got_phase != 35) {
        __log_info_native('[test:63] expected phase 35, got ' + got_phase)
        __log_marker('fifth_tier_phase_fail:' + got_phase)
    } else {
        __log_marker('fifth_tier_phase_ok:35')
    }

    var apex = city.get_building_at(tile.x + 6, tile.y + 6)
    if (apex && apex.id) {
        __log_marker('fifth_tier_apex_ok:' + apex.id)
    } else {
        __log_marker('fifth_tier_apex_fail')
    }

    if (__test_building_current_image(bid) <= 0) {
        __log_info_native('[test:63] art packs not loaded (--no-resource) — skipping screenshot')
        __log_marker('fifth_tier_art_skipped:no_resource')
        __test_signal_ready()
        return
    }
    __log_marker('fifth_tier_art_ok')

    __test_process_events()
    window_go_back()
    __zoom_set(180)
    __test_pump_frames(10)
    __test_camera_center_building(bid)
    __test_pump_frames(8)
    __game_save_screenshot(SCREENSHOT_DISPLAY)
    __log_marker('fifth_tier_screenshot_display_done')

    __test_pump_frames(2)
    __game_save_screenshot(SCREENSHOT_FULL_CITY)
    __log_marker('fifth_tier_screenshot_fullcity_done')
    __log_marker('fifth_tier_screenshot_done')

    __test_signal_ready()
}

function check_valid() {
    if (!__test_find_inlog('fifth_tier_placed_ok')) {
        __log_info_native('[test:63] missing marker: fifth_tier_placed_ok')
        return false
    }
    if (!__test_find_inlog('fifth_tier_phase_ok')) {
        __log_info_native('[test:63] missing marker: fifth_tier_phase_ok')
        return false
    }
    if (__test_find_inlog('fifth_tier_art_skipped:no_resource')) {
        return true
    }
    if (!__test_find_inlog('fifth_tier_art_ok')) {
        __log_info_native('[test:63] missing marker: fifth_tier_art_ok')
        return false
    }
    if (!__test_find_inlog('fifth_tier_screenshot_done')) {
        __log_info_native('[test:63] missing marker: fifth_tier_screenshot_done')
        return false
    }
    return true
}

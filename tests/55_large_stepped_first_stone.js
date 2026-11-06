// Layer-2 focus: verify the FIRST STONE STAGE of the Large Stepped Pyramid
// (16x16) renders correctly. That is the bottom brick layer (layer 0) laid across
// the full footprint during phases 6..11 — corner sprites at the 4 corners, wall
// sprites along the 4 edges, floor sprites in the interior, growing course 0 -> 5.
//
// Foundation (0..6) is stage A; this test steps just past it into stage B's first
// tier and screenshots each course so the brick ring can be eyeballed. Run against a
// WRITABLE Pharaoh copy (d:/Work/Cleop) so full_city_*.png screenshots actually save.

function run_test() {
    __log_info_native('[test:55] large stepped pyramid — first stone stage render')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_LARGE_STEPPED_PYRAMID)) {
        __scenario_building_allow(BUILDING_LARGE_STEPPED_PYRAMID, true)
    }
    __test_set_treasury(500000)

    // Footprint 16x16 — place centred so the whole ring is on screen.
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 8, y: cy - 8}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}, {x: 60, y: 40}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_LARGE_STEPPED_PYRAMID, candidates[i].x, candidates[i].y)
    }
    if (!bid) { bid = test_building_place(BUILDING_LARGE_STEPPED_PYRAMID, -1, -1) }
    if (!bid) {
        __log_info_native('[test:55] failed to place BUILDING_LARGE_STEPPED_PYRAMID')
        __log_marker('first_stone_place_fail')
        __test_signal_ready()
        return
    }
    var tile = __building_tile(bid)
    __log_marker('first_stone_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    // Let the async pak-queue resolve the stepped_pyramid pack (placement kicks it off).
    __test_pump_frames(30)
    __test_monument_set_phase(bid, 6)
    __test_pump_frames(4)
    if (__test_building_current_image(bid) <= 0) {
        __log_info_native('[test:55] art packs not loaded (--no-resource) — skipping')
        __log_marker('first_stone_art_skipped:no_resource')
        __test_signal_ready()
        return
    }

    // Walk the first brick tier: phase 6 (course 0) .. phase 11 (course 5), plus 12
    // (moment the tier is complete and layer flips to 1). One screenshot per course.
    var phases = [6, 7, 8, 9, 10, 11, 12]
    var all_ok = true
    for (var p = 0; p < phases.length; p++) {
        __test_monument_set_phase(bid, phases[p])
        __test_pump_frames(4)
        var img = __test_building_current_image(bid)
        if (img <= 0) {
            all_ok = false
            __log_info_native('[test:55] phase ' + phases[p] + ' img=' + img)
        }
        __test_camera_center_building(bid)
        __test_process_events()
        window_go_back()             // dismiss any residual popup before the shot
        __test_pump_frames(3)
        __game_save_screenshot(SCREENSHOT_FULL_CITY)
        __test_pump_frames(2)
        __log_marker('first_stone_shot_phase' + phases[p] + ':img=' + img)
    }
    __log_marker(all_ok ? 'first_stone_art_ok' : 'first_stone_art_fail')
    __log_marker('first_stone_screenshot_done')

    __test_signal_ready()
}

function check_valid() {
    if (!__test_find_inlog('first_stone_placed_ok')) {
        __log_info_native('[test:55] missing marker: first_stone_placed_ok')
        return false
    }
    if (__test_find_inlog('first_stone_art_skipped:no_resource')) {
        return true
    }
    var required = ['first_stone_art_ok', 'first_stone_screenshot_done']
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:55] missing marker: ' + required[i])
            return false
        }
    }
    return true
}

// First-tier pipeline: place Large Stepped Pyramid (16x16), verify the part
// ring (corners/walls/fillers), walk foundation → first brick tier + ramp climb
// (phase 13 = SE turn + east-face ascent), then take end screenshots.
//
// Phase advance walks 0→1→…→13 so on_phase_changed hooks fire (setup_phase_6 etc.).
// Run WITH Pharaoh data + writable screenshot dir:
//   build\Debug\akhenaten.exe --integraltests --integraltest-only 58_large_stepped_first_tier ^
//     --nointro --nomouse --no-logo --nosound --nocrashdlg --window --size 1000x750 ^
//     --screenshot-dir d:/Work/Akhenaten/tmp/first_tier_shot "d:/Work/Cleop"

function run_test() {
    __log_info_native('[test:58] large stepped — build first tier + screenshot')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_LARGE_STEPPED_PYRAMID)) {
        __scenario_building_allow(BUILDING_LARGE_STEPPED_PYRAMID, true)
    }
    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 8, y: cy - 8}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}, {x: 60, y: 40}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_LARGE_STEPPED_PYRAMID, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_LARGE_STEPPED_PYRAMID, -1, -1)
    }
    if (!bid) {
        __log_info_native('[test:58] failed to place BUILDING_LARGE_STEPPED_PYRAMID')
        __log_marker('first_tier_place_fail')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    __log_marker('first_tier_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    var n_mainish = 0
    var n_corner = 0
    var n_wall = 0
    var n_other = 0
    var parts = 0
    var cur = city.get_building(bid)
    var seen = {}
    function count_part(b) {
        if (!b || !b.id || seen[b.id]) { return }
        seen[b.id] = true
        parts++
        var t = __building_type(b.id)
        if (t == BUILDING_LARGE_STEPPED_PYRAMID) { n_mainish++ }
        else if (t == BUILDING_LARGE_STEPPED_PYRAMID_CORNER) { n_corner++ }
        else if (t == BUILDING_LARGE_STEPPED_PYRAMID_WALL) { n_wall++ }
        else { n_other++ }
    }
    var walk = cur
    while (walk) {
        count_part(walk)
        walk = walk.next_part_building_id ? city.get_building(walk.next_part_building_id) : null
    }
    walk = cur
    while (walk && walk.prev_part_building_id) {
        walk = city.get_building(walk.prev_part_building_id)
        count_part(walk)
    }
    while (walk) {
        count_part(walk)
        walk = walk.next_part_building_id ? city.get_building(walk.next_part_building_id) : null
    }

    __log_marker('first_tier_parts:' + parts + ':mainish=' + n_mainish + ':corner=' + n_corner + ':wall=' + n_wall + ':other=' + n_other)
    // 16×16 → 8×8 parts of 2×2 = 64; walls (8-2)*4 = 24; 3 corners + mainish fillers.
    if (parts == 64 && n_corner == 3 && n_wall == 24 && n_mainish == 37 && n_other == 0) {
        __log_marker('first_tier_layout_ok')
    } else {
        __log_info_native('[test:58] unexpected layout parts=' + parts + ' corner=' + n_corner + ' wall=' + n_wall + ' mainish=' + n_mainish)
        __log_marker('first_tier_layout_fail')
    }

    var corners = [
        {x: tile.x, y: tile.y},
        {x: tile.x + 14, y: tile.y},
        {x: tile.x, y: tile.y + 14},
        {x: tile.x + 14, y: tile.y + 14}
    ]
    var corners_ok = true
    for (var c = 0; c < corners.length; c++) {
        var at = city.get_building_at(corners[c].x, corners[c].y)
        var at_type = at ? __building_type(at.id) : 0
        var ok = (at_type == BUILDING_LARGE_STEPPED_PYRAMID || at_type == BUILDING_LARGE_STEPPED_PYRAMID_CORNER)
        __log_marker('first_tier_corner' + c + ':' + corners[c].x + ',' + corners[c].y + ':type=' + at_type + (ok ? ':ok' : ':bad'))
        if (!ok) { corners_ok = false }
    }
    __log_marker(corners_ok ? 'first_tier_corners_ok' : 'first_tier_corners_fail')

    __test_pump_frames(30)

    // Phase 13: first tier complete and ramp has turned SE + climbed east face.
    __test_monument_set_phase(bid, 13)
    __test_pump_frames(4)

    var got_phase = __test_monument_phase(bid)
    if (got_phase != 13) {
        __log_info_native('[test:58] expected phase 13, got ' + got_phase)
        __log_marker('first_tier_phase_fail:' + got_phase)
    } else {
        __log_marker('first_tier_phase_ok:13')
    }

    if (__test_building_current_image(bid) <= 0) {
        __log_info_native('[test:58] art packs not loaded (--no-resource) — skipping screenshot')
        __log_marker('first_tier_art_skipped:no_resource')
        __test_signal_ready()
        return
    }
    __log_marker('first_tier_art_ok')

    __test_camera_center_building(bid)
    __test_process_events()
    window_go_back()
    __test_pump_frames(6)

    __game_save_screenshot(SCREENSHOT_FULL_CITY)
    __test_pump_frames(2)
    __game_save_screenshot(SCREENSHOT_DISPLAY)
    __test_pump_frames(2)
    __log_marker('first_tier_screenshot_done')

    __test_signal_ready()
}

function check_valid() {
    if (!__test_find_inlog('first_tier_placed_ok')) {
        __log_info_native('[test:58] missing marker: first_tier_placed_ok')
        return false
    }
    if (!__test_find_inlog('first_tier_layout_ok')) {
        __log_info_native('[test:58] missing marker: first_tier_layout_ok')
        return false
    }
    if (!__test_find_inlog('first_tier_corners_ok')) {
        __log_info_native('[test:58] missing marker: first_tier_corners_ok')
        return false
    }
    if (!__test_find_inlog('first_tier_phase_ok')) {
        __log_info_native('[test:58] missing marker: first_tier_phase_ok')
        return false
    }
    if (__test_find_inlog('first_tier_art_skipped:no_resource')) {
        return true
    }
    if (!__test_find_inlog('first_tier_art_ok')) {
        __log_info_native('[test:58] missing marker: first_tier_art_ok')
        return false
    }
    if (!__test_find_inlog('first_tier_screenshot_done')) {
        __log_info_native('[test:58] missing marker: first_tier_screenshot_done')
        return false
    }
    return true
}

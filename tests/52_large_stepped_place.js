// Large Stepped Pyramid (16x16) — place via planner, verify linked parts
// (8x8 blocks = 64 tiles), walk a few construction phases, capture a screenshot.
// Asserts placement / parts / build-phase progression. Marble polish is true-pyramid
// only, not stepped.

function run_test() {
    __log_info_native('[test:52] large stepped pyramid place + parts + phases + screenshot')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_LARGE_STEPPED_PYRAMID)) {
        __scenario_building_allow(BUILDING_LARGE_STEPPED_PYRAMID, true)
    }

    // Fund the treasury so placing doesn't trigger the "Out of money" popup.
    __test_set_treasury(500000)

    // Footprint is 16x16 — place near the map centre so the whole pyramid fits.
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
        __log_info_native('[test:52] failed to place BUILDING_LARGE_STEPPED_PYRAMID')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    __log_marker('large_stepped_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    // Collect linked part building ids. 16x16 -> 8x8 blocks of 2x2 = 64 tiles total.
    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 256) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    // Forward traversal from main reaches all parts only when main is the list head
    // (orientation-dependent), so assert linkage (>1 part) and log the count.
    if (parts.length > 1) {
        __log_marker('large_stepped_parts_ok:' + parts.length)
    } else {
        __log_info_native('[test:52] no linked parts, got ' + parts.length)
        __log_marker('large_stepped_parts_fail:' + parts.length)
    }

    // Give the async pak-queue time to resolve the stepped_pyramid pack before we
    // start driving phases (placement kicks off the load).
    __test_pump_frames(30)
    __test_monument_set_phase(bid, 6)
    __test_pump_frames(4)
    var art_available = __test_building_current_image(bid) > 0

    if (!art_available) {
        __log_info_native('[test:52] art packs not loaded (--no-resource) — skipping art/screenshots')
        __log_marker('large_stepped_art_skipped:no_resource')
        __test_signal_ready()
        return
    }

    // Screenshot EACH construction stage: foundation (0-6), then each brick tier.
    // Filenames are timestamped (full_city_<ts>.png), so time order == this order.
    // Screenshots save into the data dir, so run against a WRITABLE Pharaoh copy
    // (e.g. d:/Work/Cleop), not a read-only Program Files install.
    // Through all 5 brick tiers; 35 = full apex course, 36 = terminal marker.
    var phases = [0, 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 18, 21, 24, 28, 32, 35, 36]
    var all_phases_ok = true
    for (var p = 0; p < phases.length; p++) {
        __test_monument_set_phase(bid, phases[p])
        __test_pump_frames(4)
        var img = __test_building_current_image(bid)
        if (img <= 0) {
            all_phases_ok = false
            __log_info_native('[test:52] phase ' + phases[p] + ' img=' + img)
        }
        __test_camera_center_building(bid)
        __test_process_events()
        window_go_back()            // dismiss any residual popup before the shot
        __test_pump_frames(3)
        __game_save_screenshot(SCREENSHOT_FULL_CITY)
        __test_pump_frames(2)
        __log_marker('large_stepped_shot_phase' + phases[p])
    }
    __log_marker(all_phases_ok ? 'large_stepped_phases_art_ok' : 'large_stepped_phases_art_fail')
    __log_marker('large_stepped_screenshot_done')

    // Info window opens without error.
    __test_show_tile_info(bid)
    __test_pump_frames(6)
    window_go_back()
    __test_pump_frames(2)
    __log_marker('large_stepped_info_ok')

    __test_signal_ready()
}

function check_valid() {
    // Always required: placement + linked parts.
    var required = ['large_stepped_placed_ok', 'large_stepped_parts_ok']
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:52] missing marker: ' + required[i])
            return false
        }
    }
    // Under --no-resource the art path is skipped and we stop early — that's a pass.
    if (__test_find_inlog('large_stepped_art_skipped:no_resource')) {
        return true
    }
    // With resources: every stage must render art and the screenshots must be taken.
    var resource_required = ['large_stepped_phases_art_ok', 'large_stepped_screenshot_done', 'large_stepped_info_ok']
    for (var j = 0; j < resource_required.length; j++) {
        if (!__test_find_inlog(resource_required[j])) {
            __log_info_native('[test:52] missing marker: ' + resource_required[j])
            return false
        }
    }
    return true
}

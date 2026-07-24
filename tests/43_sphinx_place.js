// C6: Sphinx multi-part monument — place via planner, verify 3 linked parts,
// walk construction stages 1..6 (art resolves per part), and capture a screenshot.

function run_test() {
    __log_info_native('[test:43] sphinx place + parts + phases + screenshot')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SPHINX)) {
        __scenario_building_allow(BUILDING_SPHINX, true)
    }

    // Fund the treasury so placing the sphinx doesn't trigger the "Out of money" popup
    // (which would otherwise cover the screenshot).
    __test_set_treasury(500000)

    // Footprint is 6x18 — place at the map centre so the whole sphinx fits (and is
    // fully captured by the full-city screenshot), origin = centre - (3, 9).
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 3, y: cy - 9}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}, {x: 60, y: 40}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SPHINX, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_SPHINX, -1, -1)
    }
    if (!bid) {
        __log_info_native('[test:43] failed to place BUILDING_SPHINX')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    __log_marker('sphinx_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    // Collect the 3 linked part building ids (main + b + c).
    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 8) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    if (parts.length == 3) {
        __log_marker('sphinx_parts_ok:3')
    } else {
        __log_info_native('[test:43] expected 3 parts, got ' + parts.length)
        __log_marker('sphinx_parts_fail:' + parts.length)
    }

    // Walk construction stages. art_stage(): phase<=1 -> 1, 2..5 -> 2..5, >=6 -> 6.
    // Art only resolves when the sphinx image packs are loaded (resource run);
    // under --no-resource first_img() returns 0, so gate the assertion.
    __test_monument_set_phase(bid, 1)
    __test_pump_frames(2)
    var art_available = __test_building_current_image(bid) > 0

    if (art_available) {
        var phases = [1, 2, 3, 4, 5, 6]
        var all_stages_ok = true
        for (var p = 0; p < phases.length; p++) {
            __test_monument_set_phase(bid, phases[p])
            __test_pump_frames(2)
            var stage_ok = true
            for (var k = 0; k < parts.length; k++) {
                var img = __test_building_current_image(parts[k])
                if (img <= 0) {
                    stage_ok = false
                    all_stages_ok = false
                    __log_info_native('[test:43] stage ' + phases[p] + ' part ' + parts[k] + ' img=' + img)
                }
            }
            __log_marker('sphinx_stage' + phases[p] + (stage_ok ? '_art_ok' : '_art_fail'))
        }
        if (all_stages_ok) {
            __log_marker('sphinx_all_stages_art_ok')
        }
    } else {
        __log_info_native('[test:43] art packs not loaded (--no-resource) — skipping per-stage art check')
        __log_marker('sphinx_art_skipped:no_resource')
    }

    // Info window opens without error (also centers the camera on the sphinx).
    __test_show_tile_info(bid)
    __test_pump_frames(6)
    window_go_back()             // close info window
    __test_pump_frames(2)
    __log_marker('sphinx_info_ok')

    // Finished statue (stage 6): center on the footprint and screenshot a clean city view.
    __test_monument_set_phase(bid, 6)
    __test_pump_frames(2)
    __test_camera_center_building(bid)  // center on the sphinx (monument center_point)
    __test_process_events()
    window_go_back()             // dismiss any residual popup
    __test_pump_frames(10)
    __game_save_screenshot(SCREENSHOT_DISPLAY)  // -> <dir>/city_<timestamp>.png
    __test_pump_frames(2)
    __log_marker('sphinx_screenshot_done')

    // Whole-city screenshot (renders the entire map, not just the viewport).
    __game_save_screenshot(SCREENSHOT_FULL_CITY) // -> <dir>/full_city_<timestamp>.png
    __test_pump_frames(2)
    __log_marker('sphinx_city_screenshot_done')

    __test_signal_ready()
}

function check_valid() {
    // Every run must place the sphinx, get 3 parts, screenshot, and open info clean.
    var required = [
        'sphinx_placed_ok',
        'sphinx_parts_ok:3',
        'sphinx_screenshot_done',
        'sphinx_info_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:43] missing marker: ' + required[i])
            return false
        }
    }
    // Per-stage art check only when resources are present; otherwise it is skipped.
    var art_ok = __test_find_inlog('sphinx_all_stages_art_ok')
    var art_skipped = __test_find_inlog('sphinx_art_skipped:no_resource')
    if (!art_ok && !art_skipped) {
        __log_info_native('[test:43] missing art marker (neither all_stages_art_ok nor skip)')
        return false
    }
    return true
}

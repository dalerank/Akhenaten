// Small obelisk place via planner after staffing a Storage Yard with granite
// from placement_resources (100 in small_obelisk.js). Also rejects place without granite
// and a second unfinished obelisk, then exercises monument resource delivery.

function run_test() {
    __log_info_native('[test:44] small obelisk reject + place + granite consume + add_resource')
    test_reload_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_OBELISK)) {
        __scenario_building_allow(BUILDING_SMALL_OBELISK, true)
    }
    if (!__scenario_building_allowed(BUILDING_STORAGE_YARD)) {
        __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    }

    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    // --- reject place without granite in staffed SY ---
    var rejected_no_granite = test_building_place(BUILDING_SMALL_OBELISK, cx - 1, cy - 1)
    if (!rejected_no_granite) {
        rejected_no_granite = test_building_place(BUILDING_SMALL_OBELISK, -1, -1)
    }
    if (rejected_no_granite) {
        __log_info_native('[test:44] unexpected place without granite bid=' + rejected_no_granite)
        __test_signal_ready()
        return
    }
    __log_marker('obelisk_reject_no_granite_ok')

    // Granite amount must match building_small_obelisk.placement_resources in small_obelisk.js.
    var granite_need = 100

    // Keep the Storage Yard off-centre so the 3×3 obelisk can sit at the map centre
    // (auto-place prefers centre and would steal the screenshot spot).
    var sy = 0
    var yard_spots = [
        {x: 10, y: 10}, {x: 15, y: 15}, {x: 20, y: 10}, {x: 10, y: 20}, {x: 8, y: 40}
    ]
    for (var yi = 0; yi < yard_spots.length && !sy; yi++) {
        sy = test_staffed_yard_with_resource(RESOURCE_GRANITE, granite_need, yard_spots[yi].x, yard_spots[yi].y)
    }
    if (!sy) {
        // Last resort: anywhere (obelisk centre place may then fail — logged below).
        sy = test_staffed_yard_with_resource(RESOURCE_GRANITE, granite_need, -1, -1)
    }
    if (!sy) {
        __log_info_native('[test:44] staffed yard setup failed')
        __test_signal_ready()
        return
    }

    var staffed_before = __test_yards_stored_staffed(RESOURCE_GRANITE)
    if (staffed_before < granite_need) {
        __log_info_native('[test:44] staffed granite ' + staffed_before + ' < need ' + granite_need)
        __test_signal_ready()
        return
    }
    __log_marker('obelisk_granite_ready:' + staffed_before)

    // Footprint 3×3 — prefer map centre (screenshots). Fall back for --no-resource maps
    // where the staffed yard may have taken the centre tile.
    var bid = test_building_place(BUILDING_SMALL_OBELISK, cx - 1, cy - 1)
    if (!bid) {
        bid = test_building_place(BUILDING_SMALL_OBELISK, cx, cy)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_SMALL_OBELISK, -1, -1)
    }
    if (!bid) {
        __log_info_native('[test:44] failed to place BUILDING_SMALL_OBELISK')
        __test_signal_ready()
        return
    }

    __test_process_events()
    __test_pump_frames(2)

    var tile = __building_tile(bid)
    __log_marker('obelisk_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    var b = city.get_building(bid)
    if (!b || b.type != BUILDING_SMALL_OBELISK) {
        __log_info_native('[test:44] placed building type mismatch')
        __test_signal_ready()
        return
    }

    // --- only one unfinished obelisk (still unfinished — do not finish yet) ---
    var second = test_building_place(BUILDING_SMALL_OBELISK, cx + 10, cy + 10)
    if (!second) {
        second = test_building_place(BUILDING_SMALL_OBELISK, cx + 15, cy + 15)
    }
    if (!second) {
        second = test_building_place(BUILDING_SMALL_OBELISK, 20, 50)
    }
    if (second) {
        __log_info_native('[test:44] unexpected second unfinished obelisk bid=' + second)
        __test_signal_ready()
        return
    }
    __log_marker('obelisk_reject_only_one_ok')

    // Single building — no multi-part chain (unlike sphinx).
    if (b.next_part_building_id > 0 || b.prev_part_building_id > 0) {
        __log_info_native('[test:44] unexpected part link next=' + b.next_part_building_id
            + ' prev=' + b.prev_part_building_id)
        __log_marker('obelisk_parts_fail')
    } else {
        __log_marker('obelisk_single_ok')
    }

    var footprint = __building_static_building_size(BUILDING_SMALL_OBELISK)
    if (footprint == 3) {
        __log_marker('obelisk_size_ok:3')
    } else {
        __log_info_native('[test:44] expected footprint 3, got ' + footprint)
        __log_marker('obelisk_size_fail:' + footprint)
    }

    var staffed_after = __test_yards_stored_staffed(RESOURCE_GRANITE)
    if (staffed_after <= staffed_before - granite_need) {
        __log_marker('obelisk_granite_consumed:' + staffed_before + '->' + staffed_after)
    } else {
        __log_info_native('[test:44] granite not consumed: before=' + staffed_before
            + ' after=' + staffed_after + ' need=' + granite_need)
        __log_marker('obelisk_granite_fail:' + staffed_before + '->' + staffed_after)
    }

    // Carpenter slot + one scaffold visit (consumes stages.stage_1.timber from a staffed yard).
    var timber_need = 200 // matches stage_1.timber in small_obelisk.js
    var ty = 0
    var timber_spots = [
        {x: 12, y: 40}, {x: 25, y: 25}, {x: 30, y: 10}, {x: 40, y: 40}
    ]
    for (var ti = 0; ti < timber_spots.length && !ty; ti++) {
        ty = test_staffed_yard_with_resource(RESOURCE_TIMBER, timber_need, timber_spots[ti].x, timber_spots[ti].y)
    }
    if (!ty) {
        ty = test_staffed_yard_with_resource(RESOURCE_TIMBER, timber_need, -1, -1)
    }

    var cid = __test_figure_create(FIGURE_CARPENTER, tile.x, tile.y)
    if (cid && b) {
        b.add_workers(cid)
    }
    var mon = city.get_monument(bid)
    if (mon && mon.workers_assigned() >= 1) {
        __log_marker('obelisk_workers_ok')
    } else {
        __log_info_native('[test:44] workers_assigned expected >=1, got '
            + (mon ? mon.workers_assigned() : -1) + ' cid=' + cid)
        __log_marker('obelisk_workers_fail')
    }

    __test_monument_set_phase(bid, 0)
    if (ty && __test_obelisk_place_scaffold(bid)) {
        var pct = __test_monument_resource_pct(bid, RESOURCE_TIMBER)
        if (pct >= 100) {
            __log_marker('obelisk_monument_add_resource_ok:' + pct)
        } else {
            __log_info_native('[test:44] timber pct expected >=100, got ' + pct)
            __log_marker('obelisk_monument_add_resource_pct:' + pct)
        }
    } else {
        __log_info_native('[test:44] __test_obelisk_place_scaffold failed ty=' + ty)
        __log_marker('obelisk_monument_add_resource_fail')
    }

    __test_show_tile_info(bid)
    __test_pump_frames(4)
    window_go_back()
    __test_pump_frames(2)
    __log_marker('obelisk_info_ok')

    // Finished art for screenshots (phase == phases() → MONUMENT_FINISHED; no ladder).
    __test_monument_set_phase(bid, 5)
    __test_pump_frames(2)
    __test_camera_center_building(bid)
    __test_process_events()
    window_go_back()
    __test_pump_frames(10)
    __game_save_screenshot(SCREENSHOT_DISPLAY)
    __test_pump_frames(2)
    __log_marker('obelisk_screenshot_done')

    __game_save_screenshot(SCREENSHOT_FULL_CITY)
    __test_pump_frames(2)
    __log_marker('obelisk_city_screenshot_done')

    __test_signal_ready()
}

function check_valid() {
    var required = [
        'obelisk_reject_no_granite_ok',
        'obelisk_placed_ok',
        'obelisk_reject_only_one_ok',
        'obelisk_single_ok',
        'obelisk_size_ok:3',
        'obelisk_granite_consumed',
        'obelisk_workers_ok',
        'obelisk_monument_add_resource_ok',
        'obelisk_info_ok',
        'obelisk_screenshot_done',
        'obelisk_city_screenshot_done'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:44] missing marker: ' + required[i])
            return false
        }
    }
    return true
}

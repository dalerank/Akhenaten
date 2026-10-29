// Large obelisk (5×5): placement granite 200, 18 OG work spots (8 carpenter + 10 mason),
// reject without granite / second unfinished, scaffold advances phase.

function run_test() {
    __log_info_native('[test:45] large obelisk reject + place + granite consume + scaffold')
    test_reload_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_LARGE_OBELISK)) {
        __scenario_building_allow(BUILDING_LARGE_OBELISK, true)
    }
    if (!__scenario_building_allowed(BUILDING_STORAGE_YARD)) {
        __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    }

    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var rejected_no_granite = test_building_place(BUILDING_LARGE_OBELISK, cx - 2, cy - 2)
    if (!rejected_no_granite) {
        rejected_no_granite = test_building_place(BUILDING_LARGE_OBELISK, -1, -1)
    }
    if (rejected_no_granite) {
        __log_info_native('[test:45] unexpected place without granite bid=' + rejected_no_granite)
        __test_signal_ready()
        return
    }
    __log_marker('lobelisk_reject_no_granite_ok')

    // Matches building_large_obelisk.placement_resources in large_obelisk.js.
    var granite_need = 200

    var sy = 0
    var yard_spots = [
        {x: 10, y: 10}, {x: 15, y: 15}, {x: 20, y: 10}, {x: 10, y: 20}, {x: 8, y: 40}
    ]
    for (var yi = 0; yi < yard_spots.length && !sy; yi++) {
        sy = test_staffed_yard_with_resource(RESOURCE_GRANITE, granite_need, yard_spots[yi].x, yard_spots[yi].y)
    }
    if (!sy) {
        sy = test_staffed_yard_with_resource(RESOURCE_GRANITE, granite_need, -1, -1)
    }
    if (!sy) {
        __log_info_native('[test:45] staffed yard setup failed')
        __test_signal_ready()
        return
    }

    var staffed_before = __test_yards_stored_staffed(RESOURCE_GRANITE)
    if (staffed_before < granite_need) {
        __log_info_native('[test:45] staffed granite ' + staffed_before + ' < need ' + granite_need)
        __test_signal_ready()
        return
    }
    __log_marker('lobelisk_granite_ready:' + staffed_before)

    // Footprint 5×5 — prefer map centre.
    var bid = test_building_place(BUILDING_LARGE_OBELISK, cx - 2, cy - 2)
    if (!bid) {
        bid = test_building_place(BUILDING_LARGE_OBELISK, cx, cy)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_LARGE_OBELISK, -1, -1)
    }
    if (!bid) {
        __log_info_native('[test:45] failed to place BUILDING_LARGE_OBELISK')
        __test_signal_ready()
        return
    }

    __test_process_events()
    __test_pump_frames(2)

    var tile = __building_tile(bid)
    __log_marker('lobelisk_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    var b = city.get_building(bid)
    if (!b || b.type != BUILDING_LARGE_OBELISK) {
        __log_info_native('[test:45] placed building type mismatch')
        __test_signal_ready()
        return
    }

    var second = test_building_place(BUILDING_LARGE_OBELISK, cx + 12, cy + 12)
    if (!second) {
        second = test_building_place(BUILDING_SMALL_OBELISK, cx + 12, cy + 12)
    }
    if (!second) {
        second = test_building_place(BUILDING_LARGE_OBELISK, 20, 50)
    }
    if (second) {
        __log_info_native('[test:45] unexpected second unfinished obelisk bid=' + second)
        __test_signal_ready()
        return
    }
    __log_marker('lobelisk_reject_only_one_ok')

    if (b.next_part_building_id > 0 || b.prev_part_building_id > 0) {
        __log_info_native('[test:45] unexpected part link next=' + b.next_part_building_id
            + ' prev=' + b.prev_part_building_id)
        __log_marker('lobelisk_parts_fail')
    } else {
        __log_marker('lobelisk_single_ok')
    }

    var footprint = __building_static_building_size(BUILDING_LARGE_OBELISK)
    if (footprint == 5) {
        __log_marker('lobelisk_size_ok:5')
    } else {
        __log_info_native('[test:45] expected footprint 5, got ' + footprint)
        __log_marker('lobelisk_size_fail:' + footprint)
    }

    var staffed_after = __test_yards_stored_staffed(RESOURCE_GRANITE)
    if (staffed_after <= staffed_before - granite_need) {
        __log_marker('lobelisk_granite_consumed:' + staffed_before + '->' + staffed_after)
    } else {
        __log_info_native('[test:45] granite not consumed: before=' + staffed_before
            + ' after=' + staffed_after + ' need=' + granite_need)
        __log_marker('lobelisk_granite_fail:' + staffed_before + '->' + staffed_after)
    }

    // First carpenter stage timber (stage_1.timber / work_ticks 320).
    var timber_need = 200
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
        __log_marker('lobelisk_workers_ok')
    } else {
        __log_info_native('[test:45] workers_assigned expected >=1, got '
            + (mon ? mon.workers_assigned() : -1) + ' cid=' + cid)
        __log_marker('lobelisk_workers_fail')
    }

    __test_monument_set_phase(bid, 0)
    if (ty && __test_obelisk_place_scaffold(bid)) {
        var phase_after = mon ? mon.phase() : -99
        if (phase_after == 1) {
            __log_marker('lobelisk_monument_add_resource_ok:' + phase_after)
        } else {
            __log_info_native('[test:45] phase expected 1 after scaffold, got ' + phase_after)
            __log_marker('lobelisk_monument_add_resource_pct:' + phase_after)
        }
    } else {
        __log_info_native('[test:45] __test_obelisk_place_scaffold failed ty=' + ty)
        __log_marker('lobelisk_monument_add_resource_fail')
    }

    // 18 OG work stages; set_phase(18) == phases() → MONUMENT_FINISHED (-1).
    __test_monument_set_phase(bid, 18)
    mon = city.get_monument(bid)
    var fin = mon ? mon.phase() : -999
    if (fin == -1 || fin == 255) {
        __log_marker('lobelisk_finish_ok')
    } else {
        __log_info_native('[test:45] expected finished phase -1 after set_phase(18), got ' + fin)
        __log_marker('lobelisk_finish_fail:' + fin)
    }

    __test_show_tile_info(bid)
    __test_pump_frames(4)
    window_go_back()
    __test_pump_frames(2)
    __log_marker('lobelisk_info_ok')

    __test_camera_center_building(bid)
    __test_process_events()
    window_go_back()
    __test_pump_frames(10)
    __game_save_screenshot(SCREENSHOT_DISPLAY)
    __test_pump_frames(2)
    __log_marker('lobelisk_screenshot_done')

    __game_save_screenshot(SCREENSHOT_FULL_CITY)
    __test_pump_frames(2)
    __log_marker('lobelisk_city_screenshot_done')

    __test_signal_ready()
}

function check_valid() {
    var required = [
        'lobelisk_reject_no_granite_ok',
        'lobelisk_placed_ok',
        'lobelisk_reject_only_one_ok',
        'lobelisk_single_ok',
        'lobelisk_size_ok:5',
        'lobelisk_granite_consumed',
        'lobelisk_workers_ok',
        'lobelisk_monument_add_resource_ok',
        'lobelisk_finish_ok',
        'lobelisk_info_ok',
        'lobelisk_screenshot_done',
        'lobelisk_city_screenshot_done'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:45] missing marker: ' + required[i])
            return false
        }
    }
    return true
}

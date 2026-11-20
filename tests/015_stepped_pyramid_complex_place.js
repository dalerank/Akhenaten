// Stepped Pyramid Complex (20x20 + causeway-to-water). Temples/art still open.

function run_test() {
    __log_info_native('[test:015] stepped pyramid complex place + parts + phases')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_STEPPED_PYRAMID_COMPLEX)) {
        __scenario_building_allow(BUILDING_STEPPED_PYRAMID_COMPLEX, true)
    }

    __test_set_treasury(500000)

    var px = 30
    var py = 30

    // Without a water link the complex must be rejected.
    if (test_planner_enter_build_mode(BUILDING_STEPPED_PYRAMID_COMPLEX)) {
        city_planner.update(px, py)
        if (city_planner.can_be_placed() == CAN_PLACE) {
            __log_info_native('[test:015] inland place should be blocked')
            __log_marker('complex_stepped_inland_fail')
            test_planner_exit_build_mode()
            __test_signal_ready()
            return
        }
        test_planner_exit_build_mode()
        __log_marker('complex_stepped_inland_blocked_ok')
    } else {
        __log_info_native('[test:015] failed to enter build mode for inland check')
        __test_signal_ready()
        return
    }

    test_prepare_pyramid_complex_causeway(px, py, 20, 4, 3)

    var bid = test_building_place(BUILDING_STEPPED_PYRAMID_COMPLEX, px, py)
    if (!bid) {
        var cx = (__scenario_map.width / 2) | 0
        var cy = (__scenario_map.height / 2) | 0
        test_prepare_pyramid_complex_causeway(cx, cy, 20, 4, 3)
        bid = test_building_place(BUILDING_STEPPED_PYRAMID_COMPLEX, cx, cy)
    }
    if (!bid) {
        __log_info_native('[test:015] failed to place BUILDING_STEPPED_PYRAMID_COMPLEX')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    __log_marker('complex_stepped_placed_ok:' + bid + ':' + tile.x + ',' + tile.y)

    if (test_pyramid_complex_causeway_claimed(bid, tile.x, tile.y, 20, 4)) {
        __log_marker('complex_stepped_causeway_claimed_ok')
    } else {
        __log_info_native('[test:015] causeway tiles not claimed to bid=' + bid)
        __log_marker('complex_stepped_causeway_claimed_fail')
    }

    var btype = __building_type(bid)
    if (btype != BUILDING_STEPPED_PYRAMID_COMPLEX) {
        __log_info_native('[test:015] expected type complex, got ' + btype)
        __log_marker('complex_stepped_type_fail:' + btype)
    } else {
        __log_marker('complex_stepped_type_ok')
    }

    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 256) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    if (parts.length == 100) {
        __log_marker('complex_stepped_parts_ok:' + parts.length)
    } else {
        __log_info_native('[test:015] expected 100 linked parts, got ' + parts.length)
        __log_marker('complex_stepped_parts_fail:' + parts.length)
    }

    __test_pump_frames(30)
    __test_monument_set_phase(bid, 6)
    __test_pump_frames(4)
    var art_available = __test_building_current_image(bid) > 0

    if (!art_available) {
        __log_info_native('[test:015] art packs not loaded (--no-resource) — skipping art/screenshots')
        // Still verify finish phase exists in schedule.
        __test_monument_set_phase(bid, 36)
        __test_pump_frames(4)
        var ph = __test_monument_phase(bid)
        if (ph == 36) {
            __log_marker('complex_stepped_finish_phase_ok')
        } else {
            __log_marker('complex_stepped_finish_phase_fail:' + ph)
        }
        __log_marker('complex_stepped_art_skipped:no_resource')
        __test_signal_ready()
        return
    }

    var phases = [0, 6, 12, 18, 24, 30, 35, 36]
    var all_phases_ok = true
    for (var p = 0; p < phases.length; p++) {
        __test_monument_set_phase(bid, phases[p])
        __test_pump_frames(4)
        var img = __test_building_current_image(bid)
        if (img <= 0 && phases[p] != 36) {
            all_phases_ok = false
            __log_info_native('[test:015] phase ' + phases[p] + ' img=' + img)
        }
        __test_camera_center_building(bid)
        __test_process_events()
        window_go_back()
        __test_pump_frames(3)
        __game_save_screenshot(SCREENSHOT_FULL_CITY)
        __test_pump_frames(2)
        __log_marker('complex_stepped_shot_phase' + phases[p])
    }
    __log_marker(all_phases_ok ? 'complex_stepped_phases_art_ok' : 'complex_stepped_phases_art_fail')
    __log_marker('complex_stepped_screenshot_done')

    __test_show_tile_info(bid)
    __test_pump_frames(6)
    window_go_back()
    __test_pump_frames(2)
    __log_marker('complex_stepped_info_ok')

    __test_signal_ready()
}

function check_valid() {
    var required = ['complex_stepped_inland_blocked_ok', 'complex_stepped_placed_ok', 'complex_stepped_causeway_claimed_ok', 'complex_stepped_parts_ok', 'complex_stepped_type_ok']
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:015] missing marker: ' + required[i])
            return false
        }
    }
    if (__test_find_inlog('complex_stepped_art_skipped:no_resource')) {
        return !!__test_find_inlog('complex_stepped_finish_phase_ok')
    }
    var resource_required = ['complex_stepped_phases_art_ok', 'complex_stepped_screenshot_done', 'complex_stepped_info_ok']
    for (var j = 0; j < resource_required.length; j++) {
        if (!__test_find_inlog(resource_required[j])) {
            __log_info_native('[test:015] missing marker: ' + resource_required[j])
            return false
        }
    }
    return true
}

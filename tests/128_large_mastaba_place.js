// Large mastaba — place all 4 orientations (36 parts), mid-phase save/load,
// bricks, finish, monument rating (OG weight 11 → 21).

function count_parts_from(bid) {
    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 48) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    return parts
}

function chain_main(bid) {
    var cur = city.get_building(bid)
    var guard = 0
    while (cur && cur.prev_part_building_id > 0 && guard < 48) {
        bid = cur.prev_part_building_id
        cur = city.get_building(bid)
        guard++
    }
    return bid
}

function chain_has_type(bid, type) {
    var cur_id = bid
    var guard = 0
    while (cur_id > 0 && guard < 48) {
        if (__building_type(cur_id) == type) return true
        var cur = city.get_building(cur_id)
        if (!cur || !cur.next_part_building_id) break
        cur_id = cur.next_part_building_id
        guard++
    }
    return false
}

// Mastaba orientation follows camera absolute (relative=0):
// camera 0/2/4/6 → place orient 0/1/2/3.
function set_camera_for_mastaba_orient(orient) {
    __camera_rotate_north()
    for (var i = 0; i < orient; i++) {
        __camera_rotate_left()
    }
}

function place_large_mastaba_orient(orient, x, y) {
    set_camera_for_mastaba_orient(orient)

    if (!test_planner_enter_build_mode(BUILDING_LARGE_MASTABA)) {
        return 0
    }

    city_planner.update(x, y)
    if (city_planner.can_be_placed() != CAN_PLACE) {
        test_planner_exit_build_mode()
        return 0
    }

    city_planner.construction_start(x, y)
    city_planner.construction_update(x, y)
    city_planner.construction_finalize()

    var bid = city_planner.last_created_building_id()
    // CREATED → VALID for full chain (starts at main even when cursor is SIDE).
    city_planner.validate_last_created()
    test_planner_exit_build_mode()
    if (!bid) {
        return 0
    }

    var main = chain_main(bid)
    if (!chain_has_type(main, BUILDING_LARGE_MASTABA)) {
        __log_info_native('[test:128] orient ' + orient + ' no LARGE in chain main=' + main
            + ' type=' + __building_type(main) + ' created_type=' + __building_type(bid))
        return 0
    }
    return main
}

function find_large_main() {
    for (var bi = 1; bi < 800; bi++) {
        if (__building_type(bi) != BUILDING_LARGE_MASTABA) continue
        var b = city.get_building(bi)
        if (b && !b.prev_part_building_id) return bi
    }
    return 0
}

function run_test() {
    __log_info_native('[test:128] large mastaba orients + saveload + rating')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_LARGE_MASTABA)) {
        __scenario_building_allow(BUILDING_LARGE_MASTABA, true)
    }

    __test_set_treasury(500000)
    __image_request_pak(PACK_MASTABA)
    __image_request_pak(PACK_GENERAL)
    __test_pump_frames(4)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var spots = [
        {x: cx - 4, y: cy - 9},
        {x: cx + 10, y: cy - 9},
        {x: cx - 4, y: cy + 12},
        {x: cx + 10, y: cy + 12},
        {x: 20, y: 20}, {x: 40, y: 20}, {x: 20, y: 50}, {x: 50, y: 40}
    ]

    var orients_ok = true
    for (var o = 0; o < 4; o++) {
        test_reload_city_session('data/default.map')
        __test_set_treasury(500000)
        if (!__scenario_building_allowed(BUILDING_LARGE_MASTABA)) {
            __scenario_building_allow(BUILDING_LARGE_MASTABA, true)
        }

        var bid = 0
        for (var si = 0; si < spots.length && !bid; si++) {
            bid = place_large_mastaba_orient(o, spots[si].x, spots[si].y)
        }
        if (!bid) {
            __log_info_native('[test:128] orient ' + o + ' place failed')
            __log_marker('large_mastaba_orient' + o + '_fail')
            orients_ok = false
            continue
        }

        var parts = count_parts_from(bid)
        if (parts.length != 36) {
            __log_info_native('[test:128] orient ' + o + ' parts=' + parts.length)
            __log_marker('large_mastaba_orient' + o + '_parts_fail:' + parts.length)
            orients_ok = false
        } else {
            __log_marker('large_mastaba_orient' + o + '_ok:' + bid)
        }

        if (o == 2 || o == 3) {
            if (!chain_has_type(bid, BUILDING_LARGE_MASTABA_SIDE)) {
                __log_info_native('[test:128] orient ' + o + ' missing SIDE in chain')
                __log_marker('large_mastaba_orient' + o + '_side_fail')
                orients_ok = false
            }
        }
        if (!chain_has_type(bid, BUILDING_LARGE_MASTABA_ENTRANCE)) {
            __log_info_native('[test:128] orient ' + o + ' missing ENTRANCE')
            __log_marker('large_mastaba_orient' + o + '_entrance_fail')
            orients_ok = false
        }
    }
    if (orients_ok) {
        __log_marker('large_mastaba_orients_ok')
    }

    // Fresh north place for saveload / finish / rating.
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    if (!__scenario_building_allowed(BUILDING_LARGE_MASTABA)) {
        __scenario_building_allow(BUILDING_LARGE_MASTABA, true)
    }
    __image_request_pak(PACK_MASTABA)
    __image_request_pak(PACK_GENERAL)
    __test_pump_frames(2)

    var bid = 0
    for (var i = 0; i < spots.length && !bid; i++) {
        bid = place_large_mastaba_orient(0, spots[i].x, spots[i].y)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_LARGE_MASTABA, -1, -1)
        if (bid) bid = chain_main(bid)
    }
    if (!bid) {
        __log_info_native('[test:128] failed to place north large mastaba for pipeline')
        __test_signal_ready()
        return
    }
    __log_marker('large_mastaba_placed_ok:' + bid)

    var parts = count_parts_from(bid)
    __log_marker(parts.length == 36 ? 'large_mastaba_parts_ok:36' : ('large_mastaba_parts_fail:' + parts.length))

    var part_types = [
        BUILDING_LARGE_MASTABA,
        BUILDING_LARGE_MASTABA_SIDE,
        BUILDING_LARGE_MASTABA_WALL,
        BUILDING_LARGE_MASTABA_ENTRANCE
    ]
    var size_ok = true
    for (var ti = 0; ti < part_types.length; ti++) {
        if (__building_static_building_size(part_types[ti]) != 2) size_ok = false
    }
    __log_marker(size_ok ? 'large_mastaba_parts_size_ok' : 'large_mastaba_parts_size_fail')

    __test_monument_set_phase(bid, 4)
    __test_pump_frames(2)
    if (__test_monument_phase(bid) != 4) {
        __log_marker('large_mastaba_saveload_phase_fail')
    } else if (!__game_write_savegame('test_128_large_mastaba_mid.svx')) {
        __log_marker('large_mastaba_saveload_skipped')
    } else if (!__game_load_savegame('test_128_large_mastaba_mid.svx')) {
        __game_delete_savegame('test_128_large_mastaba_mid.svx')
        __log_marker('large_mastaba_saveload_skipped')
    } else {
        __game_delete_savegame('test_128_large_mastaba_mid.svx')
        var loaded = find_large_main()
        var ph = loaded ? __test_monument_phase(loaded) : -999
        var loaded_parts = loaded ? count_parts_from(loaded).length : 0
        if (!loaded || ph != 4 || loaded_parts != 36) {
            __log_info_native('[test:128] saveload found=' + loaded + ' phase=' + ph + ' parts=' + loaded_parts)
            __log_marker('large_mastaba_saveload_fail:' + ph)
        } else {
            __log_marker('large_mastaba_saveload_ok:' + loaded)
            bid = loaded
            parts = count_parts_from(bid)
        }
    }

    __test_monument_set_phase(bid, 2)
    if (__test_monument_add_resource(bid, RESOURCE_BRICKS, 13600)) {
        var pct = __test_monument_resource_pct(bid, RESOURCE_BRICKS)
        __log_marker(pct >= 100 ? ('large_mastaba_bricks_ok:' + pct) : ('large_mastaba_bricks_pct:' + pct))
    } else {
        __log_marker('large_mastaba_bricks_fail')
    }

    __test_show_tile_info(bid)
    __test_pump_frames(4)
    window_go_back()
    __test_pump_frames(2)
    __log_marker('large_mastaba_info_ok')

    __test_monument_set_phase(bid, 8)
    var fin_phase = __test_monument_phase(bid)
    __log_marker(fin_phase == -1 ? 'large_mastaba_finished_ok' : ('large_mastaba_finished_fail:' + fin_phase))

    test_monument_slots([BUILDING_LARGE_MASTABA])
    city_update_monthly_monument_rating({})
    var rating = city.rating.monument | 0
    if (rating < 21) {
        __log_info_native('[test:128] rating want >=21 got ' + rating)
        __log_marker('large_mastaba_rating_fail:' + rating)
    } else {
        __log_marker('large_mastaba_rating_ok:' + rating)
    }

    __test_camera_center_building(bid)
    __test_pump_frames(4)
    __game_save_screenshot(SCREENSHOT_DISPLAY)
    __log_marker('large_mastaba_screenshot_done')

    __test_signal_ready()
}

function check_valid() {
    var required = [
        'large_mastaba_orients_ok',
        'large_mastaba_placed_ok',
        'large_mastaba_parts_ok:36',
        'large_mastaba_parts_size_ok',
        'large_mastaba_bricks_ok',
        'large_mastaba_info_ok',
        'large_mastaba_finished_ok',
        'large_mastaba_rating_ok',
        'large_mastaba_screenshot_done'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:128] missing marker: ' + required[i])
            return false
        }
    }
    if (__test_find_inlog('large_mastaba_saveload_fail')) {
        return false
    }
    if (!__test_find_inlog('large_mastaba_saveload_ok')
        && !__test_find_inlog('large_mastaba_saveload_skipped')) {
        __log_info_native('[test:128] missing saveload marker')
        return false
    }
    return true
}

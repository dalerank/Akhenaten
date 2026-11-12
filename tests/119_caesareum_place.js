// OG caesareum: nine 5x5 parts in a 15x15 square around the clicked tile, free, one per city,
// 19 stages worked by stonemasons (2 marble sleds each, granite in stage 18) and carpenters at 27 spots.

function t119_fail(msg) {
    __log_info_native('[test:119] FAIL: ' + msg)
    __test_signal_ready()
}

function t119_work_until_leaves(bid, fid, limit) {
    for (var i = 0; i < limit; i++) {
        if (__test_caesareum_work(bid, fid) != 0) {
            return i + 1
        }
    }
    return -1
}

function run_test() {
    __log_info_native('[test:119] OG caesareum')
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_CAESAREUM)) {
        __scenario_building_allow(BUILDING_CAESAREUM, true)
    }
    __test_set_treasury(5000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    // OG TERRAIN_BLOCKS_MONUMENT: a road anywhere in the 15x15 square blocks the site.
    if (test_planner_enter_build_mode(BUILDING_CAESAREUM)) {
        city_planner.update(cx, cy)
        var free = city_planner.can_be_placed() == CAN_PLACE
        if (free) {
            __test_make_road(cx + 6, cy - 7)
            city_planner.update(cx + 1, cy)
            city_planner.update(cx, cy)
            if (city_planner.can_be_placed() == CAN_PLACE) {
                test_planner_exit_build_mode()
                return t119_fail('road inside the footprint must block the site')
            }
            __log_marker('t119_road_blocks')
        }
        test_planner_exit_build_mode()
    }

    var bid = 0
    var center = null
    var candidates = [{x: cx + 20, y: cy}, {x: cx - 20, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}, {x: 60, y: 40}]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_CAESAREUM, candidates[i].x, candidates[i].y)
        center = candidates[i]
    }
    if (!bid) {
        return t119_fail('place failed')
    }
    if (city.finance.treasury != 5000) {
        return t119_fail('OG caesareum is free, treasury ' + city.finance.treasury)
    }

    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 12) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    if (parts.length != 9) {
        return t119_fail('expected 9 parts, got ' + parts.length)
    }
    var t0 = __building_tile(bid)
    if (t0.x != center.x - 7 || t0.y != center.y - 7) {
        return t119_fail('main at ' + t0.x + ',' + t0.y + ' for center ' + center.x + ',' + center.y)
    }
    for (var p = 0; p < 9; p++) {
        var tp = __building_tile(parts[p])
        if (tp.x != t0.x + 5 * ((p / 3) | 0) || tp.y != t0.y + 5 * (p % 3)) {
            return t119_fail('part ' + p + ' at ' + tp.x + ',' + tp.y)
        }
    }
    __log_marker('t119_parts_ok')

    if (test_building_place(BUILDING_CAESAREUM, 20, 60)) {
        return t119_fail('second caesareum placed')
    }
    __log_marker('t119_only_one')

    if (__test_caesareum_stage(bid) != 0 || __test_caesareum_progress(bid) != 5
        || __test_caesareum_material(bid) != 38 * 400) {
        return t119_fail('initial stage ' + __test_caesareum_stage(bid) + ' progress ' + __test_caesareum_progress(bid)
            + ' material ' + __test_caesareum_material(bid))
    }
    if (!__test_caesareum_has_spot(bid, FIGURE_STONEMASON) || __test_caesareum_has_spot(bid, FIGURE_CARPENTER)) {
        return t119_fail('stage 0 must want a stonemason only')
    }
    if (__test_caesareum_block_resource(bid) != RESOURCE_MARBLE) {
        return t119_fail('stage 0 block resource ' + __test_caesareum_block_resource(bid))
    }
    if (__test_caesareum_sled_arrived(bid) != 0 || __test_caesareum_sled_arrived(bid) != 1
        || __test_caesareum_sled_arrived(bid) != 0) {
        return t119_fail('mason must wake on every second sled')
    }
    __test_caesareum_sled_arrived(bid)
    __log_marker('t119_initial_ok')

    var mason = __test_figure_create(FIGURE_STONEMASON, t0.x + 8, t0.y + 15)
    if (!__test_caesareum_claim(bid, mason) || __test_caesareum_worker(bid) != mason) {
        return t119_fail('mason did not take the worker slot')
    }
    var carpenter = __test_figure_create(FIGURE_CARPENTER, t0.x + 8, t0.y + 15)
    var worked = t119_work_until_leaves(bid, mason, 2000)
    if (worked != 700 || __test_caesareum_stage(bid) != 1 || __test_caesareum_worker(bid) != 0) {
        return t119_fail('stage 0 spot: worked ' + worked + ' stage ' + __test_caesareum_stage(bid))
    }
    __log_marker('t119_stage0_700_ticks')

    __test_caesareum_set_stage(bid, 2)
    if (!__test_caesareum_has_spot(bid, FIGURE_CARPENTER) || !__test_caesareum_has_spot(bid, FIGURE_STONEMASON)) {
        return t119_fail('stage 2 wants a carpenter and a stonemason')
    }
    worked = t119_work_until_leaves(bid, carpenter, 2000)
    if (worked != 400 || __test_caesareum_stage(bid) != 2 || __test_caesareum_has_spot(bid, FIGURE_CARPENTER)) {
        return t119_fail('stage 2 carpenter: worked ' + worked + ' stage ' + __test_caesareum_stage(bid))
    }
    for (var w = 0; w < 100; w++) {
        __test_caesareum_work(bid, mason)
    }
    var work3 = __test_caesareum_spot_work(bid, 3)
    if (work3 != 600) {
        return t119_fail('stage 2 mason spot left ' + work3)
    }
    __log_marker('t119_stage_needs_all_spots')

    var save_name = 'test_119_caesareum_spots.svx'
    if (__game_write_savegame(save_name) && __game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        if (__building_type(bid) != BUILDING_CAESAREUM || __test_caesareum_stage(bid) != 2
            || __test_caesareum_spot_work(bid, 3) != work3 || __test_caesareum_spot_work(bid, 2) != 0) {
            return t119_fail('after load: stage ' + __test_caesareum_stage(bid) + ' spot3 ' + __test_caesareum_spot_work(bid, 3))
        }
        __log_marker('t119_saveload_ok')
    } else {
        __log_marker('t119_saveload_skipped')
    }

    var i0 = __test_building_current_image(parts[0])
    var i1 = __test_building_current_image(parts[1])
    if (i0 > 0 && i0 != i1) {
        __test_caesareum_set_stage(bid, 5)
        var i5 = __test_building_current_image(parts[0])
        if (i5 == i0 || i5 <= 0) {
            return t119_fail('stage change must swap the part art')
        }
        __log_marker('t119_art_ok')
    } else {
        __log_marker('t119_art_skipped')
    }

    __test_caesareum_set_stage(bid, 18)
    if (__test_caesareum_block_resource(bid) != RESOURCE_GRANITE || __test_caesareum_material(bid) != 2 * 400) {
        return t119_fail('stage 18 needs 2 granite sleds, material ' + __test_caesareum_material(bid))
    }
    var mason2 = __test_figure_create(FIGURE_STONEMASON, t0.x + 8, t0.y + 15)
    worked = t119_work_until_leaves(bid, mason2, 2000)
    if (worked != 550 || __test_monument_phase(bid) != -1 || __test_caesareum_progress(bid) != 100
        || __test_monument_phase(parts[8]) != -1) {
        return t119_fail('last spot: worked ' + worked + ' phase ' + __test_monument_phase(bid))
    }
    if (__test_caesareum_has_spot(bid, FIGURE_STONEMASON)) {
        return t119_fail('finished caesareum still wants masons')
    }
    __log_marker('t119_finished')

    __log_marker('t119_ok')
    __test_signal_ready()
}

function check_valid() {
    var required = ['t119_parts_ok', 't119_only_one', 't119_initial_ok', 't119_stage0_700_ticks',
        't119_stage_needs_all_spots', 't119_finished', 't119_ok']
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])) {
            __log_info_native('[test:119] missing marker ' + required[i])
            return false
        }
    }
    return true
}

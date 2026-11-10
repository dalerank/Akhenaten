// OG sphinx: three 6x6 parts along map +x, free to place, one per city, 16 stages worked down by
// carpenters and stonemasons at 22 spots (1 work per tick), per-part packs that change one at a time.

var __t43_ok = false

function t43_fail(msg) {
    __log_info_native('[test:43] FAIL: ' + msg)
    __test_signal_ready()
}

function t43_work_until_leaves(bid, fid, limit) {
    for (var i = 0; i < limit; i++) {
        if (__test_sphinx_work(bid, fid) != 0) {
            return i + 1
        }
    }
    return -1
}

function run_test() {
    __log_info_native('[test:43] OG sphinx')
    game_features.set('gameplay_sphinx_artisans', false)
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_SPHINX)) {
        __scenario_building_allow(BUILDING_SPHINX, true)
    }
    __test_set_treasury(5000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [{x: cx - 9, y: cy - 3}, {x: 30, y: 30}, {x: 40, y: 40}, {x: 60, y: 40}]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SPHINX, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        return t43_fail('place failed')
    }
    if (city.finance.treasury != 5000) {
        return t43_fail('OG sphinx is free, treasury ' + city.finance.treasury)
    }

    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 8) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    if (parts.length != 3) {
        return t43_fail('expected 3 parts, got ' + parts.length)
    }
    var t0 = __building_tile(parts[0])
    for (var p = 1; p < 3; p++) {
        var tp = __building_tile(parts[p])
        if (tp.x != t0.x + 6 * p || tp.y != t0.y) {
            return t43_fail('part ' + p + ' at ' + tp.x + ',' + tp.y + ' main ' + t0.x + ',' + t0.y)
        }
    }
    __log_marker('t43_parts_along_x')

    if (test_building_place(BUILDING_SPHINX, 20, 60)) {
        return t43_fail('second sphinx placed')
    }
    __log_marker('t43_only_one')

    if (__test_sphinx_stage(bid) != 1) {
        return t43_fail('initial stage ' + __test_sphinx_stage(bid))
    }
    if (!__test_sphinx_has_spot(bid, FIGURE_CARPENTER) || __test_sphinx_has_spot(bid, FIGURE_STONEMASON)) {
        return t43_fail('stage 1 must want a carpenter only')
    }
    var carpenter = __test_figure_create(FIGURE_CARPENTER, t0.x, t0.y + 7)
    var worked = t43_work_until_leaves(bid, carpenter, 1000)
    if (worked != 500 || __test_sphinx_stage(bid) != 2) {
        return t43_fail('stage 1 spot: worked ' + worked + ' stage ' + __test_sphinx_stage(bid))
    }
    __log_marker('t43_stage1_500_ticks')

    __test_sphinx_set_stage(bid, 4)
    var mason = __test_figure_create(FIGURE_STONEMASON, t0.x, t0.y + 7)
    worked = t43_work_until_leaves(bid, mason, 2000)
    if (worked != 600 || __test_sphinx_stage(bid) != 4 || !__test_sphinx_has_spot(bid, FIGURE_STONEMASON)) {
        return t43_fail('stage 4 first spot: worked ' + worked + ' stage ' + __test_sphinx_stage(bid))
    }
    worked = t43_work_until_leaves(bid, mason, 2000) + t43_work_until_leaves(bid, mason, 2000)
    if (worked != 1200 || __test_sphinx_stage(bid) != 5) {
        return t43_fail('stage 4 needs all three spots: worked ' + worked + ' stage ' + __test_sphinx_stage(bid))
    }
    __log_marker('t43_stage_needs_all_spots')

    // Stage 5 with spot 6 partly worked must survive save/load (spot state lives on the parts).
    for (var w = 0; w < 100; w++) {
        __test_sphinx_work(bid, mason)
    }
    var work6 = __test_sphinx_spot_work(bid, 6)
    var save_name = 'test_43_sphinx_spots.svx'
    if (__game_write_savegame(save_name) && __game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        if (__building_type(bid) != BUILDING_SPHINX || __test_sphinx_stage(bid) != 5
            || __test_sphinx_spot_work(bid, 6) != work6 || __test_sphinx_spot_work(bid, 3) != 0) {
            return t43_fail('after load: stage ' + __test_sphinx_stage(bid) + ' spot6 ' + __test_sphinx_spot_work(bid, 6)
                + ' (was ' + work6 + ') spot3 ' + __test_sphinx_spot_work(bid, 3))
        }
        __log_marker('t43_saveload_ok')
    } else {
        __log_marker('t43_saveload_skipped')
    }

    __test_sphinx_set_stage(bid, 4)
    var a4 = [__test_building_current_image(parts[0]), __test_building_current_image(parts[1]), __test_building_current_image(parts[2])]
    // Without Pharaoh data every part falls back to the same placeholder image.
    var art = a4[0] > 0 && a4[0] != a4[1]
    if (art) {
        __test_sphinx_set_stage(bid, 5)
        var a5 = [__test_building_current_image(parts[0]), __test_building_current_image(parts[1]), __test_building_current_image(parts[2])]
        var changed = 0
        for (var k = 0; k < 3; k++) {
            changed += (a4[k] != a5[k]) ? 1 : 0
        }
        if (changed != 1) {
            return t43_fail('stage 4->5 must swap exactly one part pack, swapped ' + changed)
        }
        for (var s = 1; s <= 16; s++) {
            __test_sphinx_set_stage(bid, s)
            for (var k2 = 0; k2 < 3; k2++) {
                if (__test_building_current_image(parts[k2]) <= 0) {
                    return t43_fail('stage ' + s + ' part ' + k2 + ' has no art')
                }
            }
        }
        var params = city.get_building_params_by_type(BUILDING_SPHINX)
        var keys = ['worker_carpenter_walk', 'worker_carpenter_work', 'worker_mason_walk', 'worker_mason_work', 'worker_mason_block']
        for (var w2 = 0; w2 < keys.length; w2++) {
            if (!(params.first_img(keys[w2]) > 0)) {
                return t43_fail('worker sprite ' + keys[w2] + ' does not resolve')
            }
        }
        __log_marker('t43_art_ok')
    } else {
        __log_marker('t43_art_skipped')
    }

    __test_sphinx_set_stage(bid, 15)
    worked = t43_work_until_leaves(bid, mason, 2000)
    if (worked != 450 || __test_monument_phase(bid) != -1) {
        return t43_fail('last spot: worked ' + worked + ' phase ' + __test_monument_phase(bid))
    }
    __log_marker('t43_finished')

    // Enhanced: after carving the sphinx waits for artisans' paint and clay.
    game_features.set('gameplay_sphinx_artisans', true)
    __test_sphinx_set_stage(bid, 15)
    worked = t43_work_until_leaves(bid, mason, 2000)
    if (worked != 450 || __test_monument_phase(bid) != 16) {
        game_features.set('gameplay_sphinx_artisans', false)
        return t43_fail('painting stage: worked ' + worked + ' phase ' + __test_monument_phase(bid))
    }
    __test_monument_add_resource(bid, RESOURCE_PAINT, 400)
    __test_monument_add_resource(bid, RESOURCE_CLAY, 400)
    __test_building_update_day(bid)
    game_features.set('gameplay_sphinx_artisans', false)
    if (__test_monument_phase(bid) != -1) {
        return t43_fail('painted sphinx not finished, phase ' + __test_monument_phase(bid))
    }
    __log_marker('t43_artisans_painting')

    __test_show_tile_info(bid)
    __test_pump_frames(4)
    window_go_back()
    __test_pump_frames(2)
    __test_camera_center_building(bid)
    __test_pump_frames(4)
    __game_save_screenshot(SCREENSHOT_DISPLAY)
    __test_pump_frames(2)

    __t43_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __t43_ok
        && __test_find_inlog('[test-marker] t43_parts_along_x')
        && __test_find_inlog('[test-marker] t43_only_one')
        && __test_find_inlog('[test-marker] t43_stage1_500_ticks')
        && __test_find_inlog('[test-marker] t43_stage_needs_all_spots')
        && __test_find_inlog('[test-marker] t43_finished')
        && __test_find_inlog('[test-marker] t43_artisans_painting')
}

// OG Abu Simbel construction: 56 stages, one work spot each (12 carpenter stages, then the stage
// table), 1 work per tick, one worker at a time, spot state survives save/load, art per part stage.

function t340_fail(msg) {
    __log_info_native('[test:340] FAIL: ' + msg)
    __test_signal_ready()
}

function t340_paint_site(ox, oy) {
    for (var dy = -13; dy <= 11; dy++) {
        for (var dx = -7; dx <= 8; dx++) {
            var t = { x: ox + dx, y: oy + dy }
            terrain.remove(t, TERRAIN_NOT_CLEAR | TERRAIN_FLOODPLAIN | TERRAIN_ROCK_NEAR_MONUMENT)
            if (dx >= -5 && dx <= 3 && dy >= -11 && dy <= 9) {
                terrain.add(t, TERRAIN_ROCK | TERRAIN_ROCK_NEAR_MONUMENT)
            }
        }
    }
}

function t340_work_until_leaves(bid, fid, limit) {
    for (var i = 0; i < limit; i++) {
        if (__test_abu_simbel_work(bid, fid) != 0) {
            return i + 1
        }
    }
    return -1
}

function run_test() {
    __log_info_native('[test:340] OG abu simbel work')
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_ABU_SIMBEL)) {
        __scenario_building_allow(BUILDING_ABU_SIMBEL, true)
    }
    var ox = (__scenario_map.width / 2) | 0
    var oy = (__scenario_map.height / 2) | 0
    t340_paint_site(ox, oy)
    var bid = test_building_place(BUILDING_ABU_SIMBEL, ox, oy)
    if (!bid) {
        return t340_fail('place failed')
    }

    // Stage 0: a carpenter scaffold of 200 work.
    if (!__test_abu_simbel_has_spot(bid, FIGURE_CARPENTER) || __test_abu_simbel_has_spot(bid, FIGURE_STONEMASON)) {
        return t340_fail('stage 0 must want a carpenter only')
    }
    if (__test_abu_simbel_needs(bid, FIGURE_CARPENTER) != 1 || __test_abu_simbel_needs(bid, FIGURE_STONEMASON) != 0) {
        return t340_fail('guild demand at stage 0')
    }
    var carpenter = __test_figure_create(FIGURE_CARPENTER, ox + 7, oy - 1)
    var mason = __test_figure_create(FIGURE_STONEMASON, ox + 7, oy - 1)
    if (t340_work_until_leaves(bid, mason, 10) != 1 || __test_abu_simbel_spot_work(bid) != 200) {
        return t340_fail('a stonemason must not work a carpenter stage')
    }
    var worked = t340_work_until_leaves(bid, carpenter, 1000)
    if (worked != 200 || __test_abu_simbel_stage(bid) != 1 || __test_abu_simbel_spot_work(bid) != 200) {
        return t340_fail('stage 0: worked ' + worked + ' stage ' + __test_abu_simbel_stage(bid))
    }
    __log_marker('t340_stage0_200_ticks')

    // Stage 12: first stonemason stage, 1550 work; stage 11 is the last carpenter one.
    __test_abu_simbel_set_stage(bid, 11)
    if (!__test_abu_simbel_has_spot(bid, FIGURE_CARPENTER) || __test_abu_simbel_spot_work(bid) != 400) {
        return t340_fail('stage 11 spot')
    }
    __test_abu_simbel_set_stage(bid, 12)
    if (!__test_abu_simbel_has_spot(bid, FIGURE_STONEMASON) || __test_abu_simbel_has_spot(bid, FIGURE_CARPENTER)) {
        return t340_fail('stage 12 must want a stonemason only')
    }
    for (var w = 0; w < 300; w++) {
        __test_abu_simbel_work(bid, mason)
    }
    if (__test_abu_simbel_spot_work(bid) != 1250) {
        return t340_fail('stage 12 work left ' + __test_abu_simbel_spot_work(bid))
    }
    var save_name = 'test_391_abu_simbel.svx'
    if (__game_write_savegame(save_name) && __game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        if (__building_type(bid) != BUILDING_ABU_SIMBEL || __test_abu_simbel_stage(bid) != 12
            || __test_abu_simbel_spot_work(bid) != 1250) {
            return t340_fail('after load: stage ' + __test_abu_simbel_stage(bid) + ' work ' + __test_abu_simbel_spot_work(bid))
        }
        __log_marker('t340_saveload_ok')
    } else {
        __log_marker('t340_saveload_skipped')
    }

    // Art: stage 12 moves part 14 (north statue) from art stage 0 to 1, nothing else.
    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 20) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    __test_abu_simbel_set_stage(bid, 12)
    var before = []
    for (var k = 0; k < parts.length; k++) {
        before.push(__test_building_current_image(parts[k]))
    }
    if (before[14] > 0) {
        __test_abu_simbel_set_stage(bid, 13)
        var changed = []
        for (var k2 = 0; k2 < parts.length; k2++) {
            if (__test_building_current_image(parts[k2]) != before[k2]) {
                changed.push(k2)
            }
        }
        if (changed.length != 1 || changed[0] != 14) {
            return t340_fail('stage 12 done must change only part 14, changed ' + changed.join(','))
        }
        for (var s = 0; s <= 56; s++) {
            __test_abu_simbel_set_stage(bid, s)
            for (var k3 = 0; k3 < parts.length; k3++) {
                if (__test_building_current_image(parts[k3]) <= 0) {
                    return t340_fail('stage ' + s + ' part ' + k3 + ' has no art')
                }
            }
        }
        __log_marker('t340_art_ok')
    } else {
        __log_marker('t340_art_skipped:no_resource')
    }

    // Last stage: 400 stonemason work, then finished.
    __test_abu_simbel_set_stage(bid, 55)
    if (__test_abu_simbel_progress(bid) != 98) {
        return t340_fail('progress at 55 ' + __test_abu_simbel_progress(bid))
    }
    worked = t340_work_until_leaves(bid, mason, 2000)
    if (worked != 400 || __test_monument_phase(bid) != -1 || __test_abu_simbel_progress(bid) != 100) {
        return t340_fail('last spot: worked ' + worked + ' phase ' + __test_monument_phase(bid))
    }
    if (__test_abu_simbel_needs(bid, FIGURE_STONEMASON) != 0 || __test_abu_simbel_needs(bid, FIGURE_CARPENTER) != 0) {
        return t340_fail('finished monument still asks for workers')
    }
    __log_marker('t340_finished')

    __log_marker('t340_ok')
    __test_signal_ready()
}

function check_valid() {
    var required = ['t340_stage0_200_ticks', 't340_finished', 't340_ok']
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])) {
            __log_info_native('[test:340] missing marker ' + required[i])
            return false
        }
    }
    if (!__test_find_inlog('[test-marker] t340_saveload_ok')) {
        __log_info_native('[test:340] missing save/load')
        return false
    }
    return true
}

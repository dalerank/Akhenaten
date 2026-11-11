// OG mausoleum: 116 chained parts, 240 sandstone to place, one unfinished at a time,
// 50-tick laborer ground stage, mason/carpenter gating, save/load of part state.

var __t297_ok = false

function t297_fail(msg) {
    __log_info_native('[test:297] FAIL: ' + msg)
    __test_signal_ready()
}

function t297_work_until_leaves(part, fid, limit) {
    for (var i = 0; i < limit; i++) {
        if (__test_mausoleum_work(part, fid) != 0) {
            return i + 1
        }
    }
    return -1
}

function run_test() {
    __log_info_native('[test:297] OG mausoleum')
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_MAUSOLEUM)) {
        __scenario_building_allow(BUILDING_MAUSOLEUM, true)
    }
    if (!__scenario_building_allowed(BUILDING_STORAGE_YARD)) {
        __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    }
    __test_set_treasury(50000)

    var sy = 0
    var yard_spots = [
        {x: 8, y: 8}, {x: 12, y: 12}, {x: 20, y: 8}, {x: 8, y: 40}
    ]
    for (var yi = 0; yi < yard_spots.length && !sy; yi++) {
        sy = test_staffed_yard_with_resource(RESOURCE_SANDSTONE, 300, yard_spots[yi].x, yard_spots[yi].y)
    }
    if (!sy) {
        sy = test_staffed_yard_with_resource(RESOURCE_SANDSTONE, 300, -1, -1)
    }
    if (!sy) {
        return t297_fail('sandstone yard')
    }
    var before = __test_yards_stored_staffed(RESOURCE_SANDSTONE)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx, y: cy},
        {x: 40, y: 40},
        {x: 50, y: 50},
        {x: 60, y: 45},
        {x: 30, y: 50}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_MAUSOLEUM, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        return t297_fail('place failed')
    }

    var parts = __test_mausoleum_part_count(bid)
    if (parts != 116) {
        return t297_fail('expected 116 parts, got ' + parts)
    }
    __log_marker('t297_116_parts')

    var taken = before - __test_yards_stored_staffed(RESOURCE_SANDSTONE)
    if (taken != 240) {
        return t297_fail('placement took ' + taken + ' sandstone, want 240')
    }
    __log_marker('t297_240_sandstone')

    for (var k = 0; k < 4; k++) {
        if ((__test_mausoleum_part_kind(__test_mausoleum_part_id(bid, k)) & 255) != k) {
            return t297_fail('part ' + k + ' is not block kind ' + k)
        }
    }
    var first_ground = __test_mausoleum_part_id(bid, 4)
    if ((__test_mausoleum_part_kind(first_ground) & 255) < 4) {
        return t297_fail('part 4 is not a ground part')
    }

    var ax = __test_mausoleum_access_x(bid)
    var ay = __test_mausoleum_access_y(bid)
    var t0 = __building_tile(__test_mausoleum_part_id(bid, 0))
    if (ax == t0.x && ay == t0.y) {
        return t297_fail('access point sits on the main block')
    }

    // A second mausoleum needs its own 240 sandstone, so the only thing left to refuse it is the unfinished one.
    var sy2 = test_staffed_yard_with_resource(RESOURCE_SANDSTONE, 300, 20, 40)
    if (!sy2) {
        sy2 = test_staffed_yard_with_resource(RESOURCE_SANDSTONE, 300, -1, -1)
    }
    if (sy2 && test_building_place(BUILDING_MAUSOLEUM, 120, 20)) {
        return t297_fail('second mausoleum placed while the first is unfinished')
    }
    __log_marker('t297_second_rejected')

    if (__test_mausoleum_has_work(bid, FIGURE_LABORER) != 1) {
        return t297_fail('untouched site must want a laborer')
    }
    if (__test_mausoleum_has_work(bid, FIGURE_STONEMASON) || __test_mausoleum_has_work(bid, FIGURE_CARPENTER)) {
        return t297_fail('untouched site must not want masons or carpenters')
    }

    var laborer = __test_figure_create(FIGURE_LABORER, ax, ay)
    var part = __test_mausoleum_find_work(laborer)
    if (!part || __test_mausoleum_part_stage(part) != 0) {
        return t297_fail('laborer got no ground part (' + part + ')')
    }
    if (__test_mausoleum_part_worker(part) != laborer) {
        return t297_fail('part did not record the laborer')
    }
    var worked = t297_work_until_leaves(part, laborer, 200)
    if (worked != 50 || __test_mausoleum_part_stage(part) != 1) {
        return t297_fail('ground stage: worked ' + worked + ' stage ' + __test_mausoleum_part_stage(part))
    }
    if (__test_mausoleum_part_worker(part) != 0) {
        return t297_fail('part kept its laborer after the 50 ticks')
    }
    __log_marker('t297_ground_50_ticks')

    var guard = 0
    while (guard++ < 400) {
        part = __test_mausoleum_find_work(laborer)
        if (!part) {
            break
        }
        if (t297_work_until_leaves(part, laborer, 200) != 50) {
            return t297_fail('ground tick count off on part ' + part)
        }
    }
    if ((__test_mausoleum_work_flags(bid) & 4) == 0) {
        return t297_fail('ground-started flag missing, flags ' + __test_mausoleum_work_flags(bid))
    }
    if (__test_mausoleum_has_work(bid, FIGURE_STONEMASON) != 1) {
        return t297_fail('leveled ground must want a stonemason')
    }
    if (__test_mausoleum_has_work(bid, FIGURE_CARPENTER)) {
        return t297_fail('carpenter wanted before the low blocks are done')
    }
    __log_marker('t297_ground_all_leveled')

    var mason = __test_figure_create(FIGURE_STONEMASON, ax, ay)
    var mpart = __test_mausoleum_find_work(mason)
    if (!mpart || __test_mausoleum_part_worker(mpart) != mason) {
        return t297_fail('mason got no block part (' + mpart + ')')
    }
    var mworked = t297_work_until_leaves(mpart, mason, 200)
    if (mworked != 50) {
        return t297_fail('mason worked ' + mworked + ' ticks, want 50')
    }
    var block_has_bits = false
    for (var b = 0; b < 4; b++) {
        if (__test_mausoleum_part_stage(__test_mausoleum_part_id(bid, b)) != 0) {
            block_has_bits = true
        }
    }
    if (!block_has_bits) {
        return t297_fail('mason tick did not add a block subtile')
    }
    __log_marker('t297_mason_subtile')

    var save_name = 'test_297_mausoleum.svx'
    if (__game_write_savegame(save_name) && __game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        if (__building_type(bid) != BUILDING_MAUSOLEUM
            || __test_mausoleum_part_count(bid) != 116
            || __test_mausoleum_part_stage(first_ground) != 1
            || (__test_mausoleum_work_flags(bid) & 4) == 0) {
            return t297_fail('after load: parts ' + __test_mausoleum_part_count(bid)
                + ' ground stage ' + __test_mausoleum_part_stage(first_ground)
                + ' flags ' + __test_mausoleum_work_flags(bid))
        }
        __log_marker('t297_saveload_ok')
    } else {
        __log_marker('t297_saveload_skipped')
    }

    __test_monument_set_phase(bid, -1)
    if (__test_monument_phase(bid) != -1 || __test_mausoleum_progress(bid) != 100) {
        return t297_fail('finish: phase ' + __test_monument_phase(bid) + ' progress ' + __test_mausoleum_progress(bid))
    }
    __log_marker('t297_finished')

    __t297_ok = true
    __log_info_native('[test:297] PASS')
    __test_signal_ready()
}

function check_valid() {
    return !!__t297_ok
}

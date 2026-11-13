// Helpers for --integraltests (city session + build_planner placement).

var CAN_PLACE = 0

function test_log_building_placed(bid) {
    if (!bid) {
        return
    }
    var type = __building_type(bid)
    var tile = __building_tile(bid)
    if (!type || !tile) {
        return
    }
    var marker
    if (type == BUILDING_WORK_CAMP) {
        marker = 'test_building_placed:work_camp:' + bid + ':' + tile.x + ',' + tile.y
    } else {
        marker = 'test_building_placed:type_' + type + ':' + bid + ':' + tile.x + ',' + tile.y
    }
    __log_marker(marker)
}

// Between tests the C++ driver calls test_reset_session_between_tests(), so the
// first ensure in a test always load_map()'s a clean map. Mid-test re-calls are
// no-ops while the session stays active (use test_reload_city_session to force).
function test_ensure_city_session(map_path) {
    if (game.session_active) {
        return true
    }
    return __test_start_city_session(map_path)
}

function test_reload_city_session(map_path) {
    __test_end_city_session()
    return __test_start_city_session(map_path)
}

function test_planner_enter_build_mode(type) {
    if (!__scenario_building_allowed(type)) {
        __scenario_building_allow(type, true)
    }
    emit event_city_building_mode{ value: type }
    __test_process_events()
    return city_planner.build_type == type
}

function test_planner_exit_build_mode() {
    if (city_planner.in_progress) {
        city_planner.construction_cancel()
    }
    emit event_city_building_mode{ value: BUILDING_NONE }
    __test_process_events()
}

function test_find_buildable_tile(type) {
    if (!test_planner_enter_build_mode(type)) {
        return null
    }

    var footprint = __building_static_building_size(type)
    var w = __scenario_map.width
    var h = __scenario_map.height
    var cx = (w / 2) | 0
    var cy = (h / 2) | 0
    var best = null
    var best_dist_sq = 999999999

    for (var y = footprint; y < h - footprint; y++) {
        for (var x = footprint; x < w - footprint; x++) {
            var dx = x - cx
            var dy = y - cy
            var dist_sq = dx * dx + dy * dy
            if (best && dist_sq >= best_dist_sq) {
                continue
            }
            city_planner.update(x, y)
            if (city_planner.can_be_placed() == CAN_PLACE) {
                best = { x: x, y: y }
                best_dist_sq = dist_sq
            }
        }
    }

    test_planner_exit_build_mode()
    return best
}

// The monument rating counts the scenario's monument slots only (OG monument_register): gives the slots the
// def ids of these building types, in order.
function test_monument_slots(types) {
    var defs = [0, 0, 0]
    for (var i = 0; i < types.length && i < 3; i++) {
        defs[i] = MONUMENT_DEF_IDS[types[i]][0]
    }
    __scenario_monuments.first = defs[0]
    __scenario_monuments.second = defs[1]
    __scenario_monuments.third = defs[2]
}

var TEST_WIN_CRITERIA_GOALS = ['population', 'culture', 'prosperity', 'monuments', 'kingdom', 'housing_count', 'housing_level']
var TEST_WIN_CRITERIA_TIMES = ['time_limit', 'survival_time']

function test_win_criteria_snapshot() {
    var wc = __win_criteria
    var snap = {}
    for (var i = 0; i < TEST_WIN_CRITERIA_GOALS.length; i++) {
        var g = TEST_WIN_CRITERIA_GOALS[i]
        snap[g] = { enabled: wc[g].enabled, goal: wc[g].goal }
    }
    for (var j = 0; j < TEST_WIN_CRITERIA_TIMES.length; j++) {
        var t = TEST_WIN_CRITERIA_TIMES[j]
        snap[t] = { enabled: wc[t].enabled, years: wc[t].years }
    }
    return snap
}

// Restores a test_win_criteria_snapshot and the scenario end year it gives.
function test_win_criteria_restore(snap) {
    var wc = __win_criteria
    for (var i = 0; i < TEST_WIN_CRITERIA_GOALS.length; i++) {
        var g = TEST_WIN_CRITERIA_GOALS[i]
        wc[g].enabled = snap[g].enabled
        wc[g].goal = snap[g].goal
    }
    for (var j = 0; j < TEST_WIN_CRITERIA_TIMES.length; j++) {
        var t = TEST_WIN_CRITERIA_TIMES[j]
        wc[t].enabled = snap[t].enabled
        wc[t].years = snap[t].years
    }
    __test_scenario_init_max_year()
}

function test_building_place(type, x, y) {
    var place = null
    if (x >= 0 && y >= 0) {
        place = { x: x, y: y }
    } else {
        place = test_find_buildable_tile(type)
    }

    if (!place) {
        __log_info_native('[test_planner] no buildable tile for type ' + type)
        return 0
    }

    if (!test_planner_enter_build_mode(type)) {
        __log_info_native('[test_planner] failed to enter build mode for type ' + type)
        return 0
    }

    city_planner.update(place.x, place.y)
    if (city_planner.can_be_placed() != CAN_PLACE) {
        __log_info_native('[test_planner] tile not placeable at ' + place.x + ',' + place.y)
        test_planner_exit_build_mode()
        return 0
    }

    city_planner.construction_start(place.x, place.y)
    city_planner.construction_update(place.x, place.y)
    city_planner.construction_finalize()

    var bid = city_planner.last_created_building_id()
    city_planner.validate_last_created()
    if (!bid || __building_type(bid) != type) {
        __log_info_native('[test_planner] construction_finalize did not create type ' + type)
        test_planner_exit_build_mode()
        return 0
    }
    test_planner_exit_build_mode()
    test_log_building_placed(bid)
    return bid
}

// Synthetic shoreline: land row at cy - 1, water patch below (see tests/17, tests/19).
// Sets river entry into the patch so OG open-water checks (warship/dock) can pass.
function test_prepare_shoreline_patch(cx, cy, water_width, water_height) {
    var x0 = cx - ((water_width / 2) | 0)
    for (var dy = 0; dy < water_height; dy++) {
        for (var dx = 0; dx < water_width; dx++) {
            // set_water updates terrain + river tile images; add(WATER) is flag-only.
            terrain.set_water({ x: x0 + dx, y: cy + dy })
        }
    }
    // Boat routing only starts from WATER_0_PASSABLE tiles (fully surrounded water).
    // Use the patch interior — edge shoreline tiles are WATER_N1_BLOCKED.
    var entry_y = cy + ((water_height / 2) | 0)
    __test_set_scenario_river_points(cx, entry_y, cx, entry_y)
    __map_water_cache_river_tiles()
    __map_water_rebuild_shores()
    __test_map_routing_update_water()
}

// Straight N–S channel (width ≥ 3) with land shores — valid Low Bridge span.
// Returns start tile on the north water row (middle column).
function test_prepare_bridge_channel(cx, cy, water_width, water_length) {
    if (water_width < 3) {
        water_width = 3
    }
    var x0 = cx - ((water_width / 2) | 0)
    for (var dy = 0; dy < water_length; dy++) {
        for (var dx = 0; dx < water_width; dx++) {
            terrain.set_water({ x: x0 + dx, y: cy + dy })
        }
    }
    __map_water_cache_river_tiles()
    __map_water_rebuild_shores()
    __test_map_routing_update_water()
    return { x: cx, y: cy }
}

// Water strip so a variable-length causeway can reach it.
// dir: 0=N 1=E 2=S 3=W (map). Default east — probe prefers east first.
// gap = clear land tiles between pyramid face and water (causeway length).
function test_prepare_pyramid_complex_causeway(pyramid_x, pyramid_y, pyramid_size, gap, water_depth, dir) {
    if (typeof pyramid_size !== 'number' || pyramid_size <= 0) {
        pyramid_size = 20
    }
    if (typeof gap !== 'number' || gap < 1) {
        gap = 4
    }
    if (typeof water_depth !== 'number' || water_depth < 2) {
        water_depth = 3
    }
    if (typeof dir !== 'number') {
        dir = 1
    }
    dir = dir & 3
    var half = ((pyramid_size - 2) / 2) | 0
    var ox
    var oy
    var step_x
    var step_y
    var perp_x
    var perp_y
    // Perp must match C++ k_causeway_perp: N:+x E:+y S:-x W:-y.
    if (dir == 0) { // north: strip goes -y from north face
        ox = pyramid_x + half
        oy = pyramid_y - 1
        step_x = 0; step_y = -1; perp_x = 1; perp_y = 0
    } else if (dir == 1) { // east
        ox = pyramid_x + pyramid_size
        oy = pyramid_y + half
        step_x = 1; step_y = 0; perp_x = 0; perp_y = 1
    } else if (dir == 2) { // south
        ox = pyramid_x + half
        oy = pyramid_y + pyramid_size
        step_x = 0; step_y = 1; perp_x = -1; perp_y = 0
    } else { // west
        ox = pyramid_x - 1
        oy = pyramid_y + half
        step_x = -1; step_y = 0; perp_x = 0; perp_y = -1
    }
    var water_base_x = ox + step_x * gap
    var water_base_y = oy + step_y * gap
    for (var w = -1; w < 3; w++) {
        for (var d = 0; d < water_depth; d++) {
            terrain.add({
                x: water_base_x + step_x * d + perp_x * w,
                y: water_base_y + step_y * d + perp_y * w
            }, TERRAIN_WATER)
        }
    }
    __map_water_rebuild_shores()
    // Shore rebuild can paint floodplain onto the approach strip; strip probe
    // rejects TERRAIN_NOT_CLEAR (includes floodplain). Keep the gap clear.
    for (var i = 0; i < gap; i++) {
        for (var ww = 0; ww < 2; ww++) {
            terrain.remove({
                x: ox + step_x * i + perp_x * ww,
                y: oy + step_y * i + perp_y * ww
            }, TERRAIN_FLOODPLAIN)
        }
    }
}

function test_pyramid_complex_causeway_claimed(bid, pyramid_x, pyramid_y, pyramid_size, gap) {
    if (typeof pyramid_size !== 'number' || pyramid_size <= 0) {
        pyramid_size = 20
    }
    if (typeof gap !== 'number' || gap < 1) {
        gap = 4
    }
    var causeway_y = pyramid_y + (((pyramid_size - 2) / 2) | 0)
    var ox = pyramid_x + pyramid_size
    for (var i = 0; i < gap; i++) {
        for (var w = 0; w < 2; w++) {
            var at = city.get_building_at(ox + i, causeway_y + w)
            if (!at || !at.valid) {
                return false
            }
            var ok_owner = (at.id == bid)
                || at.type == BUILDING_MORTUARY_TEMPLE
                || at.type == BUILDING_CAUSEWAY
                || at.type == BUILDING_VALLEY_TEMPLE
            if (!ok_owner) {
                return false
            }
            if (!terrain.is({ x: ox + i, y: causeway_y + w }, TERRAIN_BUILDING)) {
                return false
            }
        }
    }
    // Tile at water edge must not be claimed (water starts at ox+gap).
    var past = city.get_building_at(ox + gap, causeway_y)
    if (past && past.valid && past.id == bid) {
        return false
    }
    return true
}

// Paint a square terrain patch centered on (cx, cy). Used for farm meadow/floodplain.
function test_prepare_terrain_patch(cx, cy, size, terrain_mask) {
    var x0 = cx - ((size / 2) | 0)
    var y0 = cy - ((size / 2) | 0)
    for (var dy = 0; dy < size; dy++) {
        for (var dx = 0; dx < size; dx++) {
            terrain.add({ x: x0 + dx, y: y0 + dy }, terrain_mask)
        }
    }
}

// Place a farm on a synthetic meadow/floodplain patch near map center.
function test_farm_place(type, terrain_mask) {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var footprint = __building_static_building_size(type)
    if (footprint <= 0) {
        footprint = 3
    }
    test_prepare_terrain_patch(cx, cy, footprint + 2, terrain_mask)
    var place_x = cx - ((footprint / 2) | 0)
    var place_y = cy - ((footprint / 2) | 0)
    return test_building_place(type, place_x, place_y)
}

function test_log_figure_created(fid) {
    if (!fid) {
        return
    }
    var type = __figure_get_type(fid)
    var tile = __figure_get_tile(fid)
    if (!type || !tile) {
        return
    }
    __log_marker('test_figure_created:type_' + type + ':' + fid + ':' + tile.x + ',' + tile.y)
}

function test_figure_create(type, x, y) {
    var place_x = (typeof x === 'number') ? x : -1
    var place_y = (typeof y === 'number') ? y : -1
    var fid = __test_figure_create(type, place_x, place_y)
    if (!fid) {
        __log_info_native('[test_figure] create failed for type ' + type)
        return 0
    }
    test_log_figure_created(fid)
    return fid
}

function test_figure_set_home(fid, bid) {
    __test_figure_set_home(fid, bid)
}

function test_figure_set_speed(fid, speed) {
    __test_figure_set_speed(fid, speed)
}

function test_figure_set_force_valid_animation(fid, enabled) {
    __test_figure_set_force_valid_animation(fid, enabled ? 1 : 0)
}

function test_figure_get_damage(fid) {
    return __test_figure_get_damage(fid)
}

function test_assert_figure_created(fid, type, tag) {
    if (!fid) {
        __log_info_native('[' + tag + '] no figure id')
        return false
    }

    if (!__figure_is_valid(fid)) {
        __log_info_native('[' + tag + '] figure ' + fid + ' not valid')
        return false
    }

    if (__figure_get_type(fid) != type) {
        __log_info_native('[' + tag + '] wrong figure type for id ' + fid)
        return false
    }

    var tile = __figure_get_tile(fid)
    if (!tile || !__map_has_figure_at(tile)) {
        __log_info_native('[' + tag + '] map_has_figure_at mismatch')
        return false
    }

    var marker = '[test-marker] test_figure_created:type_' + type + ':' + fid + ':'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[' + tag + '] missing marker: ' + marker)
        return false
    }

    return true
}

function test_assert_building_placed(bid, type, tag) {
    if (!bid) {
        __log_info_native('[' + tag + '] no building id')
        return false
    }

    if (__building_type(bid) != type) {
        __log_info_native('[' + tag + '] wrong building type for id ' + bid)
        return false
    }

    var tile = __building_tile(bid)
    var at = city.get_building_at(tile.x, tile.y)
    if (!at || at.id != bid) {
        __log_info_native('[' + tag + '] map_building_at mismatch at ' + tile.x + ',' + tile.y)
        return false
    }

    var marker = '[test-marker] test_building_placed:type_' + type + ':' + bid + ':'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[' + tag + '] missing marker: ' + marker)
        return false
    }

    return true
}

function test_staffed_yard_with_resource(resource, amount, x, y) {
    var place_x = (typeof x === 'number') ? x : -1
    var place_y = (typeof y === 'number') ? y : -1
    var sy = test_building_place(BUILDING_STORAGE_YARD, place_x, place_y)
    if (!sy) {
        __log_info_native('[test_yard] failed to place BUILDING_STORAGE_YARD')
        return 0
    }

    var b = city.get_building(sy)
    if (!b) {
        return 0
    }
    var staff = b.max_workers > 0 ? b.max_workers : 1
    b.num_workers = staff

    if (!__test_storage_yard_add_resource(sy, resource, amount)) {
        __log_info_native('[test_yard] add_resource failed bid=' + sy + ' res=' + resource + ' amt=' + amount)
        return 0
    }

    __log_marker('test_staffed_yard_ok:' + sy + ':' + resource + ':' + amount)
    return sy
}

function test_shoreline_building_place(type, building_size) {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var water_width = building_size + 2
    var water_height = 2
    if (building_size >= 3) {
        water_width = building_size + 4
        water_height = 3
    }
    test_prepare_shoreline_patch(cx, cy, water_width, water_height)

    var candidates = [{ x: cx - 1, y: cy - 1 }]
    if (building_size >= 3) {
        candidates.push({ x: cx - 2, y: cy - 1 })
        candidates.push({ x: cx - 1, y: cy - 2 })
    }

    if (!test_planner_enter_build_mode(type)) {
        __log_info_native('[test_planner] failed to enter build mode for type ' + type)
        return 0
    }

    for (var i = 0; i < candidates.length; i++) {
        var place = candidates[i]
        city_planner.update(place.x, place.y)
        if (city_planner.can_be_placed() != CAN_PLACE) {
            continue
        }
        city_planner.construction_start(place.x, place.y)
        city_planner.construction_update(place.x, place.y)
        city_planner.construction_finalize()
        var bid = city_planner.last_created_building_id()
        city_planner.validate_last_created()
        if (bid && __building_type(bid) == type) {
            test_planner_exit_build_mode()
            test_log_building_placed(bid)
            return bid
        }
    }

    __log_info_native('[test_planner] no valid shoreline tile for type ' + type)
    test_planner_exit_build_mode()
    return 0
}

// OG mudbrick block engine: place → phase 2 → boost one masonry course per
// footprint ring step → update_day → FINISHED.
// opts: { tag, marker, type, total, nlayers, candidates, sleep_ms, prepare }
// marker prefix for log markers, e.g. 'mudbrick_og_medium'.
function test_mudbrick_pyramid_og_complete(opts) {
    var tag = opts.tag || '?'
    var marker = opts.marker || ('mudbrick_og_' + tag)
    var type = opts.type
    var total = opts.total
    var nlayers = opts.nlayers
    var sleep_ms = opts.sleep_ms != null ? opts.sleep_ms : 100

    __log_info_native('[test:' + tag + '] mudbrick OG complete type=' + type + ' total=' + total)

    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(type)) {
        __scenario_building_allow(type, true)
    }
    __test_set_treasury(500000)

    if (opts.prepare) {
        opts.prepare()
    }

    var bid = 0
    var candidates = opts.candidates || []
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(type, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        bid = test_building_place(type, -1, -1)
    }
    if (!bid) {
        __log_info_native('[test:' + tag + '] failed to place type ' + type)
        __log_marker(marker + '_place_fail')
        __test_signal_ready()
        return 0
    }

    __test_camera_center_building(bid)
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)

    var remaining0 = __pyramid_remaining_blocks(bid)
    if (remaining0 != total) {
        __log_info_native('[test:' + tag + '] expected ' + total + ' blocks, got ' + remaining0)
        __log_marker(marker + '_init_fail:' + remaining0)
        __test_signal_ready()
        return 0
    }
    __log_marker(marker + '_init_ok:' + total)

    // Show carpenter ramp sprites for the whole unfinished block phase.
    __pyramid_force_show_ramps(bid, 1)
    __log_marker(marker + '_ramps_force_on')

    var steps = nlayers * 6
    var blocks_per_step = (total / steps) | 0
    if (blocks_per_step < 1) {
        blocks_per_step = 1
    }

    var mon = new Monument(bid)
    var total_placed = 0
    for (var c = 0; c < steps; c++) {
        var want = blocks_per_step
        if (c == steps - 1) {
            want = total - total_placed
        }
        if (want < 1) {
            break
        }
        var n = mon.boost_engine_blocks(want)
        total_placed += n
        __log_marker(marker + '_layer:' + (c + 1) + ':' + n)
        if (sleep_ms > 0) {
            __test_sleep_ms(sleep_ms)
        }
    }

    if (total_placed == total) {
        __log_marker(marker + '_boost_ok:' + total)
    } else {
        __log_info_native('[test:' + tag + '] boost placed ' + total_placed + ' (want ' + total + ')')
        __log_marker(marker + '_boost_fail:' + total_placed)
    }

    var rem = __pyramid_remaining_blocks(bid)
    if (rem == 0) {
        __log_marker(marker + '_remaining_ok:0')
    } else {
        __log_marker(marker + '_remaining_fail:' + rem)
    }

    // Still unfinished here — capture ramps if Pharaoh art is loaded.
    if (__test_building_current_image(bid) > 0) {
        __test_camera_center_building(bid)
        __test_process_events()
        __test_pump_frames(4)
        __game_save_screenshot(SCREENSHOT_FULL_CITY)
        __test_pump_frames(2)
        __log_marker(marker + '_ramps_screenshot_ok')
    } else {
        __log_marker(marker + '_ramps_screenshot_skipped:no_resource')
    }

    // Keep force_show_ramps on through finish so sprites stay for --integraltest-keep.
    if (sleep_ms > 0) {
        __test_sleep_ms(sleep_ms)
    }

    __test_building_update_day(bid)
    var ph = __test_monument_phase(bid)
    if (ph != -1) {
        __test_building_update_day(bid)
        ph = __test_monument_phase(bid)
    }
    if (ph == -1) {
        __log_marker(marker + '_finished_ok')
    } else {
        __log_marker(marker + '_finished_fail:' + ph)
    }

    // OG monuments_check_completion: one completion popup per pyramid.
    var congrats = 0
    for (var mi = 0; mi < __city_message_count(); mi++) {
        var key = __lang_get_message_id(__city_message_mm_text_id(mi))
        if (key && key.indexOf('pyramid_congratulations') >= 0) {
            congrats++
        }
    }
    if (congrats == 1) {
        __log_marker(marker + '_congrats_ok')
    } else {
        __log_marker(marker + '_congrats_fail:' + congrats)
    }

    __test_signal_ready()
    return bid
}

function test_mudbrick_pyramid_og_complete_valid(marker, total) {
    return __test_find_inlog('[test-marker] ' + marker + '_init_ok:' + total)
        && __test_find_inlog('[test-marker] ' + marker + '_boost_ok:' + total)
        && __test_find_inlog('[test-marker] ' + marker + '_remaining_ok:0')
        && __test_find_inlog('[test-marker] ' + marker + '_ramps_force_on')
        && (__test_find_inlog('[test-marker] ' + marker + '_ramps_screenshot_ok')
            || __test_find_inlog('[test-marker] ' + marker + '_ramps_screenshot_skipped:no_resource'))
        && __test_find_inlog('[test-marker] ' + marker + '_finished_ok')
        && __test_find_inlog('[test-marker] ' + marker + '_congrats_ok')
}

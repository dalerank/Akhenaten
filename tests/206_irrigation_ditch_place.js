// Irrigation ditch construction_update / construction_place / can_place are JS.
// Marker: [test-marker] test_irrigation_ditch_placed:...

var __test206_ok = false

function test206_place(start, end) {
    if (!test_planner_enter_build_mode(BUILDING_IRRIGATION_DITCH)) {
        return { ok: false, reason: 'build_mode', tiles: [] }
    }

    if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_CANALS, start)) {
        test_planner_exit_build_mode()
        return { ok: false, reason: 'routing', tiles: [] }
    }

    var preview = routed_building.preview_path(ROUTED_BUILDING_CANALS, start, end)
    if (!preview.ok || !preview.tiles || preview.tiles.length < 1) {
        test_planner_exit_build_mode()
        return { ok: false, reason: preview.reason || 'preview', tiles: preview.tiles || [] }
    }

    city_planner.update(end.x, end.y)
    city_planner.construction_start(start.x, start.y)
    if (!city_planner.in_progress) {
        test_planner_exit_build_mode()
        return { ok: false, reason: 'construction_start', tiles: preview.tiles }
    }
    city_planner.construction_update(end.x, end.y)
    var preview_items = city_planner.construction_update_items
    if (preview_items < 1) {
        test_planner_exit_build_mode()
        return { ok: false, reason: 'construction_update items=' + preview_items, tiles: preview.tiles }
    }
    for (var i = 0; i < preview.tiles.length; i++) {
        if (!terrain.is(preview.tiles[i], TERRAIN_CANAL)) {
            test_planner_exit_build_mode()
            return { ok: false, reason: 'construction_update missing canal', tiles: preview.tiles }
        }
    }
    city_planner.construction_finalize()
    var items = city_planner.construction_update_items
    test_planner_exit_build_mode()
    return { ok: true, tiles: preview.tiles, items: items, preview_items: preview_items }
}

function run_test() {
    __log_info_native('[test:206] irrigation ditch construction_place')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_prepare_shoreline_patch(cx, cy, 6, 2)

    if (!test_planner_enter_build_mode(BUILDING_IRRIGATION_DITCH)) {
        __log_info_native('[test:206] FAIL: build_mode for can_place')
        __test_signal_ready()
        return
    }
    var inland = { x: cx, y: cy - 8 }
    city_planner.update(inland.x, inland.y)
    if (city_planner.can_be_placed() != CAN_NOT_PLACE) {
        test_planner_exit_build_mode()
        __log_info_native('[test:206] FAIL: inland can_place want CAN_NOT_PLACE got ' + city_planner.can_be_placed())
        __test_signal_ready()
        return
    }
    test_planner_exit_build_mode()
    __log_marker('test_irrigation_ditch_can_place_inland_blocked')

    if (!test_planner_enter_build_mode(BUILDING_IRRIGATION_DITCH)) {
        __log_info_native('[test:206] FAIL: build_mode for construction_start')
        __test_signal_ready()
        return
    }
    city_planner.construction_start(inland.x, inland.y)
    if (city_planner.in_progress) {
        test_planner_exit_build_mode()
        __log_info_native('[test:206] FAIL: inland construction_start stayed in_progress')
        __test_signal_ready()
        return
    }
    test_planner_exit_build_mode()
    __log_marker('test_irrigation_ditch_construction_start_inland_blocked')

    var start = { x: cx - 2, y: cy - 1 }
    var end = { x: cx + 2, y: cy - 1 }
    var placed = test206_place(start, end)
    if (!placed.ok) {
        __log_info_native('[test:206] FAIL: ' + placed.reason)
        __test_signal_ready()
        return
    }

    for (var i = 0; i < placed.tiles.length; i++) {
        var t = placed.tiles[i]
        if (!terrain.is(t, TERRAIN_CANAL)) {
            __log_info_native('[test:206] FAIL: missing TERRAIN_CANAL at ' + t.x + ',' + t.y)
            __test_signal_ready()
            return
        }
    }

    __log_marker('test_irrigation_ditch_placed:' + start.x + ',' + start.y + '-'
        + end.x + ',' + end.y + ':tiles=' + placed.tiles.length)
    __test206_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test206_ok
        && __test_find_inlog('[test-marker] test_irrigation_ditch_can_place_inland_blocked')
        && __test_find_inlog('[test-marker] test_irrigation_ditch_construction_start_inland_blocked')
        && __test_find_inlog('[test-marker] test_irrigation_ditch_placed:')
}

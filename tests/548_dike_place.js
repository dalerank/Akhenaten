// Place dike strip on floodplain; flag OFF rejects; clear+undo.
// Marker: [test-marker] test_dike_placed:...

var __test548_result = null
var __test548_feat_prev = false

function test548_find_floodplain_tile() {
    var w = __scenario_map.width
    var h = __scenario_map.height
    for (var y = 1; y < h - 1; y++) {
        for (var x = 1; x < w - 1; x++) {
            var t = { x: x, y: y }
            if (!terrain.is(t, TERRAIN_FLOODPLAIN)) {
                continue
            }
            if (terrain.is(t, TERRAIN_WATER) || terrain.is(t, TERRAIN_BUILDING)
                || terrain.is(t, TERRAIN_CANAL) || terrain.is(t, TERRAIN_WALL)) {
                continue
            }
            return t
        }
    }
    return null
}

function test548_try_route(start, end_dx, end_dy) {
    var end = { x: start.x + end_dx, y: start.y + end_dy }
    if (end.x < 0 || end.y < 0 || end.x >= __scenario_map.width || end.y >= __scenario_map.height) {
        return null
    }

    if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_DIKE, start)) {
        return null
    }

    var preview = routed_building.preview_path(ROUTED_BUILDING_DIKE, start, end)
    if (!preview.ok || !preview.tiles || preview.tiles.length < 1) {
        return null
    }
    return {
        start_x: start.x,
        start_y: start.y,
        end_x: end.x,
        end_y: end.y,
        tiles: preview.tiles,
    }
}

function test548_find_route() {
    if (!test_planner_enter_build_mode(BUILDING_DIKE)) {
        __log_info_native('[test:548] enter_build_mode(BUILDING_DIKE) failed')
        return null
    }

    var w = __scenario_map.width
    var h = __scenario_map.height
    var deltas = [[0, 1], [1, 0], [0, 2], [2, 0], [0, 3], [3, 0], [0, 4], [4, 0]]

    for (var y = 1; y < h - 1; y++) {
        for (var x = 1; x < w - 1; x++) {
            var start = { x: x, y: y }
            if (!terrain.is(start, TERRAIN_FLOODPLAIN)) {
                continue
            }
            if (terrain.is(start, TERRAIN_WATER) || terrain.is(start, TERRAIN_BUILDING)
                || terrain.is(start, TERRAIN_CANAL) || terrain.is(start, TERRAIN_WALL)) {
                continue
            }

            for (var di = 0; di < deltas.length; di++) {
                var route = test548_try_route(start, deltas[di][0], deltas[di][1])
                if (route) {
                    test_planner_exit_build_mode()
                    return route
                }
            }

            // Single-tile place as last resort for this seed.
            var one = test548_try_route(start, 0, 0)
            if (one) {
                test_planner_exit_build_mode()
                return one
            }
        }
    }

    test_planner_exit_build_mode()
    return null
}

function test548_dike_place(start_x, start_y, end_x, end_y) {
    if (!test_planner_enter_build_mode(BUILDING_DIKE)) {
        return { ok: false, reason: 'build_mode', tiles: [] }
    }

    var start = { x: start_x, y: start_y }
    if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_DIKE, start)) {
        test_planner_exit_build_mode()
        return { ok: false, reason: 'routing', tiles: [] }
    }

    var preview = routed_building.preview_path(ROUTED_BUILDING_DIKE, start, { x: end_x, y: end_y })
    if (!preview.ok) {
        test_planner_exit_build_mode()
        return { ok: false, reason: preview.reason || 'preview', tiles: preview.tiles || [] }
    }

    city_planner.update(end_x, end_y)
    city_planner.construction_start(start_x, start_y)
    city_planner.construction_update(end_x, end_y)
    city_planner.construction_finalize()

    test_planner_exit_build_mode()
    return { ok: true, tiles: preview.tiles }
}

function test548_assert_dike(tiles, tag) {
    for (var i = 0; i < tiles.length; i++) {
        var t = tiles[i]
        if (!terrain.is(t, TERRAIN_DIKE)) {
            __log_info_native('[test:548] ' + tag + ': missing TERRAIN_DIKE at ' + t.x + ',' + t.y)
            return false
        }
    }
    return true
}

function run_test() {
    __log_info_native('[test:548] dike place smoke')
    __log_info_native('[test:548] BUILDING_DIKE=' + BUILDING_DIKE + ' ROUTED_BUILDING_DIKE=' + ROUTED_BUILDING_DIKE
        + ' TERRAIN_DIKE=' + TERRAIN_DIKE)
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    __test548_feat_prev = game_features.get('gameplay_enhanced_flood_basins') === true

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_prepare_terrain_patch(cx, cy, 8, TERRAIN_FLOODPLAIN)

    game_features.set('gameplay_enhanced_flood_basins', false)
    var fp = { x: cx, y: cy }
    if (!terrain.is(fp, TERRAIN_FLOODPLAIN)) {
        __test548_result = { ok: false, reason: 'patch_failed' }
        __log_info_native('[test:548] terrain patch did not set FLOODPLAIN')
        game_features.set('gameplay_enhanced_flood_basins', __test548_feat_prev)
        __test_signal_ready()
        return
    }
    __log_info_native('[test:548] floodplain patch at ' + fp.x + ',' + fp.y)

    // Flag OFF → place must not set bit.
    if (test_planner_enter_build_mode(BUILDING_DIKE)) {
        city_planner.update(fp.x, fp.y)
        city_planner.construction_start(fp.x, fp.y)
        city_planner.construction_update(fp.x, fp.y)
        city_planner.construction_finalize()
        test_planner_exit_build_mode()
        if (terrain.is(fp, TERRAIN_DIKE)) {
            __test548_result = { ok: false, reason: 'flag_off_placed' }
            game_features.set('gameplay_enhanced_flood_basins', __test548_feat_prev)
            __test_signal_ready()
            return
        }
    }

    game_features.set('gameplay_enhanced_flood_basins', true)

    var route = test548_find_route()
    if (!route) {
        // Direct place on patch center → center+4 east.
        route = {
            start_x: cx - 2,
            start_y: cy,
            end_x: cx + 2,
            end_y: cy,
            tiles: null,
        }
        __log_info_native('[test:548] find_route failed; trying direct place on patch')
    }

    var placed = test548_dike_place(route.start_x, route.start_y, route.end_x, route.end_y)
    if (!placed.ok) {
        __test548_result = { ok: false, reason: 'place:' + (placed.reason || 'unknown') }
        game_features.set('gameplay_enhanced_flood_basins', __test548_feat_prev)
        __test_signal_ready()
        return
    }

    if (!test548_assert_dike(placed.tiles, 'after_place')) {
        __test548_result = { ok: false, reason: 'missing_dike_bit' }
        game_features.set('gameplay_enhanced_flood_basins', __test548_feat_prev)
        __test_signal_ready()
        return
    }

    __log_marker('test_dike_placed:' + route.start_x + ',' + route.start_y + '-'
        + route.end_x + ',' + route.end_y + ':tiles=' + placed.tiles.length)

    var tile = placed.tiles[0]
    if (!test_planner_enter_build_mode(BUILDING_CLEAR_LAND)) {
        __test548_result = { ok: false, reason: 'clear_mode' }
        game_features.set('gameplay_enhanced_flood_basins', __test548_feat_prev)
        __test_signal_ready()
        return
    }
    city_planner.update(tile.x, tile.y)
    city_planner.construction_start(tile.x, tile.y)
    city_planner.construction_update(tile.x, tile.y)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()

    if (terrain.is(tile, TERRAIN_DIKE)) {
        __test548_result = { ok: false, reason: 'clear_left_dike' }
        game_features.set('gameplay_enhanced_flood_basins', __test548_feat_prev)
        __test_signal_ready()
        return
    }

    if (!__ui_game_can_undo()) {
        __test548_result = { ok: false, reason: 'no_undo' }
        game_features.set('gameplay_enhanced_flood_basins', __test548_feat_prev)
        __test_signal_ready()
        return
    }
    __ui_game_undo_perform()
    if (!terrain.is(tile, TERRAIN_DIKE)) {
        __test548_result = { ok: false, reason: 'undo_missing_dike' }
        game_features.set('gameplay_enhanced_flood_basins', __test548_feat_prev)
        __test_signal_ready()
        return
    }

    __test548_result = { ok: true, tiles: placed.tiles.length }
    game_features.set('gameplay_enhanced_flood_basins', __test548_feat_prev)
    __log_info_native('[test:548] PASS tiles=' + placed.tiles.length)
    __test_signal_ready()
}

function check_valid() {
    if (!__test548_result || !__test548_result.ok) {
        __log_info_native('[test:548] FAIL: ' + (__test548_result && __test548_result.reason
            ? __test548_result.reason : 'no_result'))
        return false
    }
    return true
}

// Sealed floodplain basin detect via TERRAIN_DIKE contour.
// Marker: [test-marker] test_basin_sealed:...

var __test551_result = null
var __test551_feat_prev = false

function test551_add_dike_rect(x0, y0, x1, y1) {
    for (var x = x0; x <= x1; x++) {
        terrain.add({ x: x, y: y0 }, TERRAIN_DIKE)
        terrain.add({ x: x, y: y1 }, TERRAIN_DIKE)
    }
    for (var y = y0; y <= y1; y++) {
        terrain.add({ x: x0, y: y }, TERRAIN_DIKE)
        terrain.add({ x: x1, y: y }, TERRAIN_DIKE)
    }
}

function test551_interior_ids(x0, y0, x1, y1) {
    var ids = []
    for (var y = y0 + 1; y < y1; y++) {
        for (var x = x0 + 1; x < x1; x++) {
            ids.push(terrain.basin_id({ x: x, y: y }))
        }
    }
    return ids
}

function run_test() {
    __log_info_native('[test:551] flood basin seal')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    __test551_feat_prev = game_features.get('gameplay_enhanced_flood_basins') === true

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    // Patch large enough for a 6x6 dike rectangle with 4x4 interior (16 tiles).
    // Patch must be larger than BASIN_MAX_AREA so exterior floodplain is not a false basin.
    test_prepare_terrain_patch(cx, cy, 22, TERRAIN_FLOODPLAIN)

    var x0 = cx - 3
    var y0 = cy - 3
    var x1 = cx + 2
    var y1 = cy + 2

    // Flag OFF → no basin ids even with a closed contour.
    game_features.set('gameplay_enhanced_flood_basins', false)
    if (building_menu_ctrl.is_enabled(BUILDING_DIKE)) {
        __test551_result = { ok: false, reason: 'menu_dike_enabled_flag_off' }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }
    test551_add_dike_rect(x0, y0, x1, y1)
    __map_basin_rebuild()
    var off_ids = test551_interior_ids(x0, y0, x1, y1)
    for (var i = 0; i < off_ids.length; i++) {
        if (off_ids[i] !== 0) {
            __test551_result = { ok: false, reason: 'flag_off_has_id' }
            game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
            __test_signal_ready()
            return
        }
    }
    if (__map_basin_count() !== 0) {
        __test551_result = { ok: false, reason: 'flag_off_count' }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }

    // Flag ON → closed rectangle seals interior.
    game_features.set('gameplay_enhanced_flood_basins', true)
    // Contour already present from above; rebuild under flag ON.
    __map_basin_rebuild()

    var ids = test551_interior_ids(x0, y0, x1, y1)
    if (ids.length < 4) {
        __test551_result = { ok: false, reason: 'interior_too_small:' + ids.length }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }

    var sealed_id = ids[0]
    if (!sealed_id) {
        __test551_result = { ok: false, reason: 'not_sealed' }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }

    for (var j = 1; j < ids.length; j++) {
        if (ids[j] !== sealed_id) {
            __test551_result = { ok: false, reason: 'id_mismatch' }
            game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
            __test_signal_ready()
            return
        }
    }

    if (!terrain.basin_sealed({ x: cx, y: cy })) {
        __test551_result = { ok: false, reason: 'sealed_flag_false' }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }

    var area = __map_basin_area(sealed_id)
    if (area !== ids.length) {
        __test551_result = { ok: false, reason: 'area:' + area + '!=' + ids.length }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }

    // Exterior of the rectangle on this large patch must NOT be a basin.
    var outside = { x: x0 - 2, y: y0 - 2 }
    if (terrain.basin_id(outside) !== 0) {
        __test551_result = { ok: false, reason: 'exterior_false_basin:' + terrain.basin_id(outside) }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }

    // Natural-only pocket near map corner (away from center dike rect).
    // Plus a decorative DIKE on adjacent dry land — must still NOT be a basin.
    var nx = 8
    var ny = 8
    if (nx + 4 >= x0 - 3) {
        nx = (__scenario_map.width - 10) | 0
        ny = (__scenario_map.height - 10) | 0
    }
    test_prepare_terrain_patch(nx, ny, 4, TERRAIN_FLOODPLAIN)
    terrain.add({ x: nx - 3, y: ny }, TERRAIN_DIKE)
    __map_basin_rebuild()
    if (terrain.basin_id({ x: nx, y: ny }) !== 0) {
        __test551_result = { ok: false, reason: 'natural_or_decorative_basin:' + terrain.basin_id({ x: nx, y: ny }) }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }
    // Sealed dike basin must still be present after rebuild (ids may renumber).
    if (!terrain.basin_sealed({ x: cx, y: cy })) {
        __test551_result = { ok: false, reason: 'sealed_lost_after_natural_check' }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }
    sealed_id = terrain.basin_id({ x: cx, y: cy })
    area = __map_basin_area(sealed_id)

    // Corner crest only touches interior diagonally — must still resolve adjacent basin.
    var corner_adj = terrain.basin_adjacent_id({ x: x0, y: y0 })
    if (corner_adj !== sealed_id) {
        __test551_result = { ok: false, reason: 'corner_adjacent_miss:' + corner_adj }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }
    var edge_adj = terrain.basin_adjacent_id({ x: x0 + 1, y: y0 })
    if (edge_adj !== sealed_id) {
        __test551_result = { ok: false, reason: 'edge_adjacent_miss:' + edge_adj }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }

    // Long meadow DIKE spur from a pocket toward distant FP must NOT seal.
    var sx0 = 10
    var sy0 = (__scenario_map.height / 2) | 0
    if (sy0 > cy - 12 && sy0 < cy + 12) {
        sy0 = 24
    }
    for (var sy = sy0; sy < sy0 + 3; sy++) {
        for (var sx = sx0; sx < sx0 + 3; sx++) {
            terrain.add({ x: sx, y: sy }, TERRAIN_FLOODPLAIN)
        }
    }
    // Spur of 8 meadow dikes toward a distant FP tile (longer than crest-run cap of 6).
    for (var si = 0; si < 8; si++) {
        terrain.add({ x: sx0 + 3 + si, y: sy0 + 1 }, TERRAIN_DIKE)
    }
    terrain.add({ x: sx0 + 11, y: sy0 + 1 }, TERRAIN_FLOODPLAIN)
    __map_basin_rebuild()
    if (terrain.basin_id({ x: sx0 + 1, y: sy0 + 1 }) !== 0) {
        __test551_result = { ok: false, reason: 'spur_false_seal' }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }
    if (!terrain.basin_sealed({ x: cx, y: cy })) {
        __test551_result = { ok: false, reason: 'sealed_lost_after_spur_check' }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }
    sealed_id = terrain.basin_id({ x: cx, y: cy })
    area = __map_basin_area(sealed_id)

    // Meadow-edge crest: DIKE on clear land (no FLOODPLAIN bit) around a pocket
    // must still load-bear-seal when exterior floodplain is reachable through the crest.
    var mx0 = 14
    var my0 = 14
    var mx1 = 19
    var my1 = 19
    if (mx1 + 2 >= x0 - 2) {
        mx0 = (__scenario_map.width - 22) | 0
        my0 = (__scenario_map.height - 22) | 0
        mx1 = mx0 + 5
        my1 = my0 + 5
    }
    for (var my = my0 + 1; my < my1; my++) {
        for (var mx = mx0 + 1; mx < mx1; mx++) {
            terrain.add({ x: mx, y: my }, TERRAIN_FLOODPLAIN)
        }
    }
    // Exterior FP beyond one crest face (load-bearing target).
    terrain.add({ x: mx0 - 1, y: my0 + 2 }, TERRAIN_FLOODPLAIN)
    terrain.add({ x: mx0 - 1, y: my0 + 3 }, TERRAIN_FLOODPLAIN)
    test551_add_dike_rect(mx0, my0, mx1, my1)
    __map_basin_rebuild()
    if (!terrain.basin_sealed({ x: mx0 + 2, y: my0 + 2 })) {
        __test551_result = { ok: false, reason: 'meadow_edge_not_sealed' }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }
    // Center basin must remain sealed (ids are renumbered on rebuild).
    if (!terrain.basin_sealed({ x: cx, y: cy })) {
        __test551_result = { ok: false, reason: 'sealed_lost_after_meadow_edge' }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }
    sealed_id = terrain.basin_id({ x: cx, y: cy })
    area = __map_basin_area(sealed_id)

    __log_marker('test_basin_sealed:id=' + sealed_id + ':area=' + area)

    // Breach: remove one crest tile → interior merges with open floodplain → unsealed.
    if (!test_planner_enter_build_mode(BUILDING_CLEAR_LAND)) {
        __test551_result = { ok: false, reason: 'clear_mode' }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }
    var breach = { x: x0 + 1, y: y0 }
    city_planner.update(breach.x, breach.y)
    city_planner.construction_start(breach.x, breach.y)
    city_planner.construction_update(breach.x, breach.y)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()

    if (terrain.is(breach, TERRAIN_DIKE)) {
        __test551_result = { ok: false, reason: 'breach_dike_left' }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }

    var after = terrain.basin_id({ x: cx, y: cy })
    if (after !== 0) {
        __test551_result = { ok: false, reason: 'breach_still_sealed:' + after }
        game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
        __test_signal_ready()
        return
    }

    __test551_result = { ok: true, area: area, id: sealed_id }
    game_features.set('gameplay_enhanced_flood_basins', __test551_feat_prev)
    __log_info_native('[test:551] PASS area=' + area)
    __test_signal_ready()
}

function check_valid() {
    if (!__test551_result || !__test551_result.ok) {
        __log_info_native('[test:551] FAIL: ' + (__test551_result && __test551_result.reason
            ? __test551_result.reason : 'no_result'))
        return false
    }
    return true
}

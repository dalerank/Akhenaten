// Flood basins (Enhanced) on the OG canal model: irrigation stamps stay inside the basin.
// Marker: [test-marker] test_basin_irrigation_hold:...

var __test107_result = null
var __test107_feat_prev = false

function test107_add_dike_rect(x0, y0, x1, y1) {
    for (var x = x0; x <= x1; x++) {
        terrain.add({ x: x, y: y0 }, TERRAIN_DIKE)
        terrain.add({ x: x, y: y1 }, TERRAIN_DIKE)
    }
    for (var y = y0; y <= y1; y++) {
        terrain.add({ x: x0, y: y }, TERRAIN_DIKE)
        terrain.add({ x: x1, y: y }, TERRAIN_DIKE)
    }
}

function test107_fail(reason) {
    __test107_result = { ok: false, reason: reason }
    game_features.set('gameplay_enhanced_flood_basins', __test107_feat_prev)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:107] flood basin irrigation hold')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    __test107_feat_prev = game_features.get('gameplay_enhanced_flood_basins') === true
    game_features.set('gameplay_enhanced_flood_basins', true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_prepare_terrain_patch(cx, cy, 24, TERRAIN_FLOODPLAIN)

    var x0 = cx - 4
    var y0 = cy - 4
    var x1 = cx + 3
    var y1 = cy + 3
    test107_add_dike_rect(x0, y0, x1, y1)
    __map_basin_rebuild()

    var inside = { x: cx, y: cy }
    var outside = { x: x0 - 3, y: y0 - 3 }
    if (!terrain.basin_sealed(inside)) {
        test107_fail('inside_not_sealed')
        return
    }
    if (terrain.basin_id(outside) !== 0) {
        test107_fail('outside_false_basin')
        return
    }

    // OG fill stamps the canal tiles it walks onto, not its start: start one tile in from near_wall.
    var near_wall = { x: x0 + 1, y: cy }
    var feed = { x: x0 + 2, y: cy }
    var across_wall = { x: x0 - 1, y: cy }
    terrain.add(near_wall, TERRAIN_CANAL)
    terrain.add(feed, TERRAIN_CANAL)

    __buildings_update_water_lifts_cycle()
    __map_canal_fill_from_offset(feed)
    if (__map_canal_at(near_wall) <= 0) {
        test107_fail('near_wall_not_filled')
        return
    }
    if (!terrain.is(near_wall, TERRAIN_IRRIGATION_RANGE)) {
        test107_fail('near_wall_no_irrigation_stamp')
        return
    }
    if (terrain.is(across_wall, TERRAIN_IRRIGATION_RANGE)) {
        test107_fail('irrigation_leaked_across_dike')
        return
    }

    __irrigation_value_update()
    if (__irrigation_value_get(near_wall) <= 0) {
        test107_fail('near_wall_no_irrigation_value')
        return
    }
    if (__irrigation_value_get(across_wall) > 0) {
        test107_fail('irrigation_value_leaked_across_dike')
        return
    }

    // Flag OFF stamps unclipped (OG); flag ON rebuilds basins and restamps clipped.
    game_features.set('gameplay_enhanced_flood_basins', false)
    __buildings_update_water_lifts_cycle()
    __map_canal_fill_from_offset(feed)
    if (!terrain.is(across_wall, TERRAIN_IRRIGATION_RANGE)) {
        test107_fail('flag_off_expected_across_stamp')
        return
    }
    if (terrain.basin_id(inside) !== 0) {
        test107_fail('flag_off_basin_id_stale:' + terrain.basin_id(inside))
        return
    }
    game_features.set('gameplay_enhanced_flood_basins', true)
    if (!terrain.basin_sealed(inside)) {
        test107_fail('reseal_failed')
        return
    }
    if (terrain.is(across_wall, TERRAIN_IRRIGATION_RANGE)) {
        test107_fail('stale_stamp_after_reseal')
        return
    }
    if (!terrain.is(near_wall, TERRAIN_IRRIGATION_RANGE)) {
        test107_fail('near_wall_lost_stamp_after_reseal')
        return
    }

    __log_marker('test_basin_irrigation_hold:clipped')
    __test107_result = { ok: true }
    game_features.set('gameplay_enhanced_flood_basins', __test107_feat_prev)
    __log_info_native('[test:107] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test107_result || !__test107_result.ok) {
        __log_info_native('[test:107] FAIL: ' + (__test107_result && __test107_result.reason
            ? __test107_result.reason : 'no_result'))
        return false
    }
    return __test_find_inlog('[test-marker] test_basin_irrigation_hold:')
}

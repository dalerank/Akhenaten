// Osiris-style perimeter dike breach unseals flood basins.
// Marker: [test-marker] test_basin_breach:...

var __test024_result = null
var __test024_feat_prev = false

function test024_add_dike_rect(x0, y0, x1, y1) {
    for (var x = x0; x <= x1; x++) {
        terrain.add({ x: x, y: y0 }, TERRAIN_DIKE)
        terrain.add({ x: x, y: y1 }, TERRAIN_DIKE)
    }
    for (var y = y0; y <= y1; y++) {
        terrain.add({ x: x0, y: y }, TERRAIN_DIKE)
        terrain.add({ x: x1, y: y }, TERRAIN_DIKE)
    }
}

function test024_fail(reason) {
    __test024_result = { ok: false, reason: reason }
    game_features.set('gameplay_enhanced_flood_basins', __test024_feat_prev)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:024] flood basin dike breach')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    __test024_feat_prev = game_features.get('gameplay_enhanced_flood_basins') === true
    game_features.set('gameplay_enhanced_flood_basins', true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_prepare_terrain_patch(cx, cy, 22, TERRAIN_FLOODPLAIN)

    var x0 = cx - 3
    var y0 = cy - 3
    var x1 = cx + 2
    var y1 = cy + 2
    test024_add_dike_rect(x0, y0, x1, y1)
    __map_basin_rebuild()

    if (!terrain.basin_sealed({ x: cx, y: cy })) {
        test024_fail('not_sealed_before_breach')
        return
    }

    // Flag OFF → breach is a no-op.
    game_features.set('gameplay_enhanced_flood_basins', false)
    var off_removed = __map_basin_breach_perimeter(3)
    if (off_removed !== 0) {
        test024_fail('flag_off_removed:' + off_removed)
        return
    }
    game_features.set('gameplay_enhanced_flood_basins', true)
    __map_basin_rebuild()
    if (!terrain.basin_sealed({ x: cx, y: cy })) {
        test024_fail('seal_lost_after_flag_toggle')
        return
    }

    var before_dike = 0
    for (var y = y0; y <= y1; y++) {
        for (var x = x0; x <= x1; x++) {
            if (terrain.is({ x: x, y: y }, TERRAIN_DIKE)) {
                before_dike++
            }
        }
    }

    var removed = __map_basin_breach_perimeter(2)
    if (removed < 1 || removed > 2) {
        test024_fail('removed_count:' + removed)
        return
    }

    var after_dike = 0
    for (var y2 = y0; y2 <= y1; y2++) {
        for (var x2 = x0; x2 <= x1; x2++) {
            if (terrain.is({ x: x2, y: y2 }, TERRAIN_DIKE)) {
                after_dike++
            }
        }
    }
    if (after_dike !== before_dike - removed) {
        test024_fail('dike_tile_delta:' + before_dike + '->' + after_dike + ':rm=' + removed)
        return
    }

    if (terrain.basin_sealed({ x: cx, y: cy })) {
        test024_fail('still_sealed_after_breach')
        return
    }
    if (terrain.basin_id({ x: cx, y: cy }) !== 0) {
        test024_fail('basin_id_after_breach:' + terrain.basin_id({ x: cx, y: cy }))
        return
    }

    // Overlay id resolves when Enhanced menu lists it.
    if (OVERLAY_FLOOD_BASIN <= OVERLAY_NONE || OVERLAY_FLOOD_BASIN >= OVERLAY_SIZE) {
        test024_fail('overlay_id_invalid:' + OVERLAY_FLOOD_BASIN)
        return
    }
    city.current_overlay = OVERLAY_FLOOD_BASIN
    var title = __city_get_overlay_title(OVERLAY_FLOOD_BASIN)
    if (!title) {
        test024_fail('overlay_title_empty')
        return
    }
    city.current_overlay = OVERLAY_NONE

    __log_marker('test_basin_breach:removed=' + removed)
    __test024_result = { ok: true, removed: removed }
    game_features.set('gameplay_enhanced_flood_basins', __test024_feat_prev)
    __log_info_native('[test:024] PASS removed=' + removed)
    __test_signal_ready()
}

function check_valid() {
    if (!__test024_result || !__test024_result.ok) {
        __log_info_native('[test:024] FAIL: ' + (__test024_result && __test024_result.reason
            ? __test024_result.reason : 'no_result'))
        return false
    }
    return true
}

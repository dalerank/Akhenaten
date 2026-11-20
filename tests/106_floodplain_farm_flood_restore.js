// Flood hide/restore for a floodplain farm that overlaps Nile water.
// Recede used to treat river tiles as "still flooded", so the farm never
// regained TERRAIN_BUILDING, occupancy stayed, and rebuild said "Some tiles blocked".
// Markers:
//   [test-marker] floodplain_farm_hidden
//   [test-marker] floodplain_farm_restored
//   [test-marker] flooded_farm_not_demolished
//   [test-marker] dry_farm_demolished
//   [test-marker] floodplain_farm_rebuilt

var __test106_result = null

function test106_fail(reason) {
    __test106_result = { ok: false, reason: reason }
    __log_info_native('[test:106] FAIL: ' + reason)
    __test_signal_ready()
}

function test106_refresh_flood_caches() {
    __map_water_cache_river_tiles()
    var width = __map_floodplain_rebuild_rows()
    __map_floodplain_rebuild_shores()
    city.floods.floodplain_width = width
    city.floods.has_floodplains = width > 0
    return width
}

function test106_run_inundation(is_flooding) {
    city.floods.fticks = 25 * 40
    for (var row = 0; row < 30; row++) {
        __map_floodplain_update_inundation(row, is_flooding)
    }
}

function test106_try_clear(tile) {
    var imm_prev = game_features.get('gameplay_change_immediate_delete')
    game_features.set('gameplay_change_immediate_delete', true)
    if (!test_planner_enter_build_mode(BUILDING_CLEAR_LAND)) {
        game_features.set('gameplay_change_immediate_delete', imm_prev)
        return false
    }
    city_planner.update(tile.x, tile.y)
    city_planner.construction_start(tile.x, tile.y)
    city_planner.construction_update(tile.x, tile.y)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()
    game_features.set('gameplay_change_immediate_delete', imm_prev)
    return true
}

function run_test() {
    __log_info_native('[test:106] floodplain farm flood restore')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    for (var dx = 0; dx < 10; dx++) {
        var nile = { x: cx + dx, y: cy }
        terrain.remove(nile, TERRAIN_FLOODPLAIN)
        terrain.add(nile, TERRAIN_WATER)
        for (var dy = -2; dy <= 4; dy++) {
            if (dy === 0) {
                continue
            }
            var fp = { x: cx + dx, y: cy + dy }
            terrain.remove(fp, TERRAIN_WATER)
            terrain.add(fp, TERRAIN_FLOODPLAIN)
        }
    }
    if (test106_refresh_flood_caches() <= 0) {
        test106_fail('no_floodplain_rows')
        return
    }

    // Origin on floodplain, middle row overlaps the Nile (3 water + 6 floodplain).
    var farm_x = cx + 2
    var farm_y = cy - 1
    var bid = __test_building_create(BUILDING_GRAIN_FARM, farm_x, farm_y)
    if (!bid) {
        test106_fail('create_farm')
        return
    }
    if (__building_at(farm_x, farm_y) != bid) {
        test106_fail('not_on_grid')
        return
    }

    var field = { x: farm_x, y: farm_y }
    test106_run_inundation(1)
    if (!terrain.is(field, TERRAIN_WATER)) {
        test106_fail('floodplain_not_inundated')
        return
    }
    if (terrain.is(field, TERRAIN_BUILDING)) {
        test106_fail('still_building_while_flooded')
        return
    }
    if (__building_at(field.x, field.y) != bid) {
        test106_fail('occupancy_lost_during_flood')
        return
    }
    __log_marker('floodplain_farm_hidden')

    test106_run_inundation(-1)
    if (terrain.is(field, TERRAIN_WATER)) {
        test106_fail('floodplain_still_wet')
        return
    }
    if (!terrain.is(field, TERRAIN_BUILDING)) {
        test106_fail('not_restored_after_recede')
        return
    }
    if (__building_at(field.x, field.y) != bid) {
        test106_fail('occupancy_lost_after_recede')
        return
    }
    __log_marker('floodplain_farm_restored')

    test106_run_inundation(1)
    if (!test106_try_clear(field)) {
        test106_fail('clear_mode')
        return
    }
    if (__building_at(field.x, field.y) != bid) {
        test106_fail('flooded_farm_was_demolished')
        return
    }
    __log_marker('flooded_farm_not_demolished')

    test106_run_inundation(-1)
    if (!test106_try_clear(field)) {
        test106_fail('clear_mode_dry')
        return
    }
    if (__building_at(farm_x, farm_y) != 0 || __building_at(farm_x, farm_y + 2) != 0) {
        test106_fail('dry_farm_not_cleared')
        return
    }
    var footprint = building_farm_footprint_check({ x: farm_x, y: farm_y }, 3)
    if (footprint.blocked) {
        test106_fail('footprint_blocked_after_demolish')
        return
    }
    __log_marker('dry_farm_demolished')

    var bid2 = __test_building_create(BUILDING_GRAIN_FARM, farm_x, farm_y)
    if (!bid2) {
        test106_fail('rebuild_failed')
        return
    }
    if (__building_at(field.x, field.y) != bid2) {
        test106_fail('rebuild_occupancy')
        return
    }
    __log_marker('floodplain_farm_rebuilt')

    __test106_result = { ok: true }
    __test_signal_ready()
}

function check_valid() {
    if (!__test106_result || !__test106_result.ok) {
        __log_info_native('[test:106] FAIL: ' + (__test106_result && __test106_result.reason
            ? __test106_result.reason : 'no_result'))
        return false
    }
    var markers = [
        'floodplain_farm_hidden',
        'floodplain_farm_restored',
        'flooded_farm_not_demolished',
        'dry_farm_demolished',
        'floodplain_farm_rebuilt'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:106] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

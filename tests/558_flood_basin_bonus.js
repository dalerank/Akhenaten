// Sealed flood basin fertility restore bonus + farm progress bonus.
// Marker: [test-marker] test_basin_bonus:...

var __test558_result = null
var __test558_feat_prev = false

function test558_add_dike_rect(x0, y0, x1, y1) {
    for (var x = x0; x <= x1; x++) {
        terrain.add({ x: x, y: y0 }, TERRAIN_DIKE)
        terrain.add({ x: x, y: y1 }, TERRAIN_DIKE)
    }
    for (var y = y0; y <= y1; y++) {
        terrain.add({ x: x0, y: y }, TERRAIN_DIKE)
        terrain.add({ x: x1, y: y }, TERRAIN_DIKE)
    }
}

function test558_fail(reason) {
    __test558_result = { ok: false, reason: reason }
    game_features.set('gameplay_enhanced_flood_basins', __test558_feat_prev)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:558] flood basin bonus')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    __test558_feat_prev = game_features.get('gameplay_enhanced_flood_basins') === true
    game_features.set('gameplay_enhanced_flood_basins', true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    // Large floodplain so exterior of the dike rect is open (unsealed).
    test_prepare_terrain_patch(cx, cy, 24, TERRAIN_FLOODPLAIN)

    var x0 = cx - 4
    var y0 = cy - 4
    var x1 = cx + 3
    var y1 = cy + 3
    test558_add_dike_rect(x0, y0, x1, y1)
    __map_basin_rebuild()

    var inside = { x: cx, y: cy }
    var outside = { x: x0 - 3, y: y0 - 3 }
    if (!terrain.basin_sealed(inside)) {
        test558_fail('inside_not_sealed')
        return
    }
    if (terrain.basin_id(outside) !== 0) {
        test558_fail('outside_false_basin')
        return
    }

    // Mediocre flood quality → mid-range fertility bonus %.
    city.floods.quality_current = 50

    var FERT_NO_MALUS = 0
    var FERT_WITH_MALUS = 1

    // Simulate inundation restore on both tiles, then apply the basin bonus.
    __map_soil_set_depletion(inside, 0)
    __map_soil_set_depletion(outside, 0)
    var fert_in_before = __map_get_fertility_at(inside, FERT_WITH_MALUS)
    var fert_out_before = __map_get_fertility_at(outside, FERT_WITH_MALUS)
    __map_floodplain_apply_basin_fertility_bonus(inside)
    __map_floodplain_apply_basin_fertility_bonus(outside)
    var fert_in = __map_get_fertility_at(inside, FERT_WITH_MALUS)
    var fert_out = __map_get_fertility_at(outside, FERT_WITH_MALUS)

    if (fert_out !== fert_out_before) {
        test558_fail('outside_bonus_leaked:' + fert_out_before + '->' + fert_out)
        return
    }
    if (fert_in <= fert_in_before) {
        test558_fail('inside_no_bonus:' + fert_in_before + '->' + fert_in)
        return
    }
    if (fert_in <= fert_out) {
        test558_fail('inside_not_gt_outside:' + fert_in + '<=' + fert_out)
        return
    }

    // Flag OFF → apply is no-op (reset inside fert and re-check).
    __map_soil_set_depletion(inside, 0)
    var base = __map_get_fertility_at(inside, FERT_WITH_MALUS)
    game_features.set('gameplay_enhanced_flood_basins', false)
    __map_floodplain_apply_basin_fertility_bonus(inside)
    if (__map_get_fertility_at(inside, FERT_WITH_MALUS) !== base) {
        test558_fail('flag_off_still_bonus')
        return
    }
    game_features.set('gameplay_enhanced_flood_basins', true)
    __map_basin_rebuild()

    // Progress: two floodplain farms, same fertility, sealed vs open.
    // Place farms carefully — grain farm is 3x3; leave room inside/outside.
    var farm_in_x = cx - 1
    var farm_in_y = cy - 1
    var farm_out_x = x0 - 6
    var farm_out_y = y0 - 6
    if (farm_out_x < 2) {
        farm_out_x = x1 + 3
        farm_out_y = y1 + 3
    }

    var bid_in = test_building_place(BUILDING_GRAIN_FARM, farm_in_x, farm_in_y)
    var bid_out = test_building_place(BUILDING_GRAIN_FARM, farm_out_x, farm_out_y)
    if (!bid_in || !bid_out) {
        test558_fail('farm_place:' + bid_in + ',' + bid_out)
        return
    }

    // Equalize fertility under both farms (no differential fert for progress check).
    __map_set_fertility_at({ x: farm_in_x, y: farm_in_y }, 80)
    __map_set_fertility_at({ x: farm_in_x + 1, y: farm_in_y }, 80)
    __map_set_fertility_at({ x: farm_in_x, y: farm_in_y + 1 }, 80)
    __map_set_fertility_at({ x: farm_in_x + 1, y: farm_in_y + 1 }, 80)
    __map_set_fertility_at({ x: farm_in_x + 2, y: farm_in_y + 2 }, 80)
    __map_set_fertility_at({ x: farm_out_x, y: farm_out_y }, 80)
    __map_set_fertility_at({ x: farm_out_x + 1, y: farm_out_y }, 80)
    __map_set_fertility_at({ x: farm_out_x, y: farm_out_y + 1 }, 80)
    __map_set_fertility_at({ x: farm_out_x + 1, y: farm_out_y + 1 }, 80)
    __map_set_fertility_at({ x: farm_out_x + 2, y: farm_out_y + 2 }, 80)

    __building_farm_set_progress(bid_in, 0)
    __building_farm_set_progress(bid_out, 0)
    __building_farm_set_labor_days(bid_in, 40)
    __building_farm_set_labor_days(bid_out, 40)

    var days = 20
    for (var i = 0; i < days; i++) {
        __test_update_farms()
    }

    var prog_in = __building_farm_progress(bid_in)
    var prog_out = __building_farm_progress(bid_out)
    if (prog_out <= 0) {
        test558_fail('outside_no_progress')
        return
    }
    // Sealed farm should outpace control by roughly the +15% progress bonus.
    if (prog_in <= prog_out) {
        test558_fail('progress_no_bonus:in=' + prog_in + ':out=' + prog_out)
        return
    }
    if (prog_in * 100 < prog_out * 108) {
        test558_fail('progress_bonus_too_small:in=' + prog_in + ':out=' + prog_out)
        return
    }

    __log_marker('test_basin_bonus:fert_in=' + fert_in + ':fert_out=' + fert_out
        + ':prog_in=' + prog_in + ':prog_out=' + prog_out)
    __test558_result = { ok: true, fert_in: fert_in, fert_out: fert_out, prog_in: prog_in, prog_out: prog_out }
    game_features.set('gameplay_enhanced_flood_basins', __test558_feat_prev)
    __log_info_native('[test:558] PASS fert ' + fert_in + '>' + fert_out + ' prog ' + prog_in + '>' + prog_out)
    __test_signal_ready()
}

function check_valid() {
    if (!__test558_result || !__test558_result.ok) {
        __log_info_native('[test:558] FAIL: ' + (__test558_result && __test558_result.reason
            ? __test558_result.reason : 'no_result'))
        return false
    }
    return true
}

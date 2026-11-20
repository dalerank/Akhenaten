// OG farm water access: an IRRIGATION_RANGE tile under the 3x3 footprint. The 5x5 zone around the
// farm's origin is the Enhanced gameplay_change_irrigation_range_5x5.
// Markers: [test-marker] farm_irrigation_zone_og_3x3 / farm_irrigation_zone_5x5

var __test381_result = null
var __test381_feat_prev = false
var __test381_feat = 'gameplay_change_irrigation_range_5x5'

function test381_fail(reason) {
    __test381_result = { ok: false, reason: reason }
    game_features.set(__test381_feat, __test381_feat_prev)
    __log_info_native('[test:381] FAIL: ' + reason)
    __test_signal_ready()
}

function test381_irrigated_with_stamp(farm, origin, dx, dy) {
    for (var y = -3; y <= 5; y++) {
        for (var x = -3; x <= 5; x++) {
            terrain.remove({ x: origin.x + x, y: origin.y + y }, TERRAIN_IRRIGATION_RANGE)
        }
    }
    terrain.add({ x: origin.x + dx, y: origin.y + dy }, TERRAIN_IRRIGATION_RANGE)
    return !!__building_farm_is_irrigated(farm)
}

function run_test() {
    __log_info_native('[test:381] farm irrigation zone')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __test381_feat_prev = game_features.get(__test381_feat) === true

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_prepare_terrain_patch(cx, cy, 8, TERRAIN_FLOODPLAIN)
    var farm = __test_building_create(BUILDING_GRAIN_FARM, cx, cy)
    if (!farm) {
        return test381_fail('create_farm')
    }
    var origin = __building_tile(farm)

    game_features.set(__test381_feat, false)
    if (!test381_irrigated_with_stamp(farm, origin, 2, 2)) {
        return test381_fail('og_footprint_corner_not_irrigated')
    }
    if (test381_irrigated_with_stamp(farm, origin, -1, -1)) {
        return test381_fail('og_irrigated_outside_footprint')
    }
    if (test381_irrigated_with_stamp(farm, origin, 3, 1)) {
        return test381_fail('og_irrigated_east_of_footprint')
    }
    __log_marker('farm_irrigation_zone_og_3x3')

    game_features.set(__test381_feat, true)
    if (!test381_irrigated_with_stamp(farm, origin, -1, -1)) {
        return test381_fail('5x5_not_irrigated_at_-1_-1')
    }
    if (!test381_irrigated_with_stamp(farm, origin, -2, 2)) {
        return test381_fail('5x5_not_irrigated_at_-2_2')
    }
    if (test381_irrigated_with_stamp(farm, origin, 3, 1)) {
        return test381_fail('5x5_irrigated_outside_zone')
    }
    __log_marker('farm_irrigation_zone_5x5')

    game_features.set(__test381_feat, __test381_feat_prev)
    __test381_result = { ok: true }
    __log_info_native('[test:381] PASS')
    __test_signal_ready()
}

function check_valid() {
    return !!(__test381_result && __test381_result.ok)
        && __test_find_inlog('[test-marker] farm_irrigation_zone_og_3x3')
        && __test_find_inlog('[test-marker] farm_irrigation_zone_5x5')
}

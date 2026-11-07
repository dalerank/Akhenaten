// OG building_farm_expected_produce: a growing farm gains at least 1 progress a day,
// even on poor soil (floodplain) or with a single worker (meadow).

var __test291_ok = false

function test291_fail(msg) {
    __log_info_native('[test:291] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:291] farm minimum growth OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var flood = test_farm_place(BUILDING_FIGS_FARM, TERRAIN_FLOODPLAIN)
    if (!flood) {
        return test291_fail('floodplain fig farm place failed')
    }
    var t = __building_tile(flood)
    for (var dx = 0; dx < 3; dx++) {
        for (var dy = 0; dy < 3; dy++) {
            __map_set_fertility_at({ x: t.x + dx, y: t.y + dy }, 5)
        }
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = ((__scenario_map.height / 2) | 0) + 8
    test_prepare_terrain_patch(cx, cy, 5, TERRAIN_MEADOW)
    var meadow = test_building_place(BUILDING_FIGS_MEADOW_FARM, cx - 1, cy - 1)
    if (!meadow) {
        return test291_fail('meadow fig farm place failed')
    }

    __building_farm_set_progress(flood, 0)
    __building_farm_set_labor_days(flood, 40)
    __building_farm_set_progress(meadow, 0)
    __test_building_set_workers(meadow, 1)

    for (var i = 0; i < 3; i++) {
        __test_update_farms()
        __test_building_set_workers(meadow, 1)
    }
    var pf = __building_farm_progress(flood)
    var pm = __building_farm_progress(meadow)
    if (pf < 3) {
        return test291_fail('poor floodplain soil must still grow 1 a day, progress=' + pf)
    }
    __log_marker('test291_floodplain_min_ok')
    if (pm < 3) {
        return test291_fail('one meadow worker must still grow 1 a day, progress=' + pm)
    }
    __log_marker('test291_meadow_min_ok')

    __test291_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test291_ok
        && __test_find_inlog('[test-marker] test291_floodplain_min_ok')
        && __test_find_inlog('[test-marker] test291_meadow_min_ok')
}

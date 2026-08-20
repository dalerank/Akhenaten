// #648: single-tile road on dry floodplain via planner (Vanilla click-to-place).
// Marker: [test-marker] test_floodplain_road_click:...

var __test182_result = null

function run_test() {
    __log_info_native('[test:182] single-tile floodplain road via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_prepare_terrain_patch(cx, cy, 6, TERRAIN_FLOODPLAIN)

    var tile = { x: cx, y: cy }
    if (!terrain.is(tile, TERRAIN_FLOODPLAIN) || terrain.is(tile, TERRAIN_WATER)) {
        __test182_result = { ok: false, reason: 'patch_failed' }
        __log_info_native('[test:182] expected dry floodplain at ' + tile.x + ',' + tile.y)
        __test_signal_ready()
        return
    }

    if (!test_planner_enter_build_mode(BUILDING_ROAD)) {
        __test182_result = { ok: false, reason: 'build_mode' }
        __log_info_native('[test:182] enter_build_mode(BUILDING_ROAD) failed')
        __test_signal_ready()
        return
    }

    if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_ROAD, tile)) {
        test_planner_exit_build_mode()
        __test182_result = { ok: false, reason: 'routing_start' }
        __log_info_native('[test:182] cannot start road routing on floodplain')
        __test_signal_ready()
        return
    }

    city_planner.update(tile.x, tile.y)
    city_planner.construction_start(tile.x, tile.y)
    city_planner.construction_update(tile.x, tile.y)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()

    if (!terrain.is(tile, TERRAIN_ROAD)) {
        __test182_result = { ok: false, reason: 'not_placed' }
        __log_info_native('[test:182] TERRAIN_ROAD missing after single-tile place')
        __test_signal_ready()
        return
    }

    __test182_result = { ok: true, x: tile.x, y: tile.y }
    __log_marker('test_floodplain_road_click:' + tile.x + ',' + tile.y)
    __test_signal_ready()
}

function check_valid() {
    if (!__test182_result || !__test182_result.ok) {
        __log_info_native('[test:182] run_test did not place floodplain road')
        return false
    }
    if (!__test_find_inlog('[test-marker] test_floodplain_road_click:')) {
        __log_info_native('[test:182] missing log marker')
        return false
    }
    return true
}

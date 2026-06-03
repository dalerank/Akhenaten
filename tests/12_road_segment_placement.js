// Builds a dirt road via build_planner (routed drag) on a valid segment near map center.
// Marker: [test-marker] test_road_placed:...

var __test12_result = null

function test12_find_road_route(end_dx, end_dy) {
    if (!test_planner_enter_build_mode(BUILDING_ROAD)) {
        return null
    }

    var w = __scenario_map.width
    var h = __scenario_map.height
    var cx = (w / 2) | 0
    var cy = (h / 2) | 0
    var best = null
    var best_dist_sq = 999999999

    for (var y = 1; y < h - 1; y++) {
        for (var x = 1; x < w - 1; x++) {
            var dx = x - cx
            var dy = y - cy
            var dist_sq = dx * dx + dy * dy
            if (best && dist_sq >= best_dist_sq) {
                continue
            }

            var end_x = x + end_dx
            var end_y = y + end_dy
            if (end_x < 0 || end_y < 0 || end_x >= w || end_y >= h) {
                continue
            }

            var start = { x: x, y: y }
            var end = { x: end_x, y: end_y }
            if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_ROAD, start)) {
                continue
            }

            var preview = routed_building.preview_path(ROUTED_BUILDING_ROAD, start, end)
            if (!preview.ok || preview.tiles.length < 2) {
                continue
            }

            best = {
                start_x: x,
                start_y: y,
                end_x: end_x,
                end_y: end_y,
                tiles: preview.tiles,
            }
            best_dist_sq = dist_sq
        }
    }

    test_planner_exit_build_mode()
    return best
}

function test12_road_place(start_x, start_y, end_x, end_y) {
    var start = { x: start_x, y: start_y }
    var end = { x: end_x, y: end_y }

    if (!test_planner_enter_build_mode(BUILDING_ROAD)) {
        return { ok: false, reason: 'build_mode', tiles: [] }
    }

    if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_ROAD, start)) {
        test_planner_exit_build_mode()
        return { ok: false, reason: 'routing', tiles: [] }
    }

    var preview = routed_building.preview_path(ROUTED_BUILDING_ROAD, start, end)
    if (!preview.ok) {
        test_planner_exit_build_mode()
        return { ok: false, reason: preview.reason || 'preview', tiles: preview.tiles || [] }
    }

    city_planner.update(end_x, end_y)
    city_planner.construction_start(start_x, start_y)
    city_planner.construction_update(end_x, end_y)
    city_planner.construction_finalize()

    var items = city_planner.construction_update_items
    test_planner_exit_build_mode()
    return { ok: true, tiles: preview.tiles, items: items }
}

function run_test() {
    __log_info_native('[test:12] placing road segment via build_planner')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var route = test12_find_road_route(0, 5)
    if (!route) {
        __test12_result = { ok: false, reason: 'no_route', tiles: [] }
        __log_info_native('[test:12] test12_find_road_route failed')
    } else {
        __test12_result = test12_road_place(route.start_x, route.start_y, route.end_x, route.end_y)
        if (!__test12_result.ok) {
            __log_info_native('[test:12] test12_road_place failed: ' + (__test12_result.reason || 'unknown'))
        } else {
            __log_marker('test_road_placed:' + route.start_x + ',' + route.start_y + '-'
                + route.end_x + ',' + route.end_y + ':tiles=' + __test12_result.tiles.length)
        }
    }
    __test_signal_ready()
}

function check_valid() {
    if (!__test12_result || !__test12_result.ok) {
        __log_info_native('[test:12] run_test did not place road')
        return false
    }

    var tiles = __test12_result.tiles
    for (var i = 0; i < tiles.length; i++) {
        var t = tiles[i]
        if (!terrain.is(t, TERRAIN_ROAD)) {
            __log_info_native('[test:12] missing TERRAIN_ROAD at ' + t.x + ',' + t.y)
            return false
        }
    }

    if (!__test_find_inlog('[test-marker] test_road_placed:')) {
        __log_info_native('[test:12] missing log marker')
        return false
    }

    return true
}

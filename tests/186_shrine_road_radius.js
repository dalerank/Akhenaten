// #639: shrines need a road within two tiles, not an adjacent one (Vanilla).
// Markers:
//   [test-marker] shrine_road_radius_hover_excluded_ok
//   [test-marker] shrine_road_radius_far_warns_ok
//   [test-marker] shrine_road_radius_two_tiles_ok
//   [test-marker] shrine_road_radius_adjacent_ok

var SHRINE_NEAR_ROAD = '#shrines_near_road_required'
var NEEDS_ROAD = '#needs_road_access'

function test186_clear_roads(cx, cy, radius) {
    for (var y = cy - radius; y <= cy + radius; y++) {
        for (var x = cx - radius; x <= cx + radius; x++) {
            terrain.remove({ x: x, y: y }, TERRAIN_ROAD)
        }
    }
}

function test186_place_shrine(x, y) {
    __test_construction_warnings_reset()
    var bid = test_building_place(BUILDING_SHRINE_RA, x, y)
    __test_process_events()
    return bid
}

function test186_warnings_ok(step, expect_shrine_warning) {
    var near = __test_construction_warning_count(SHRINE_NEAR_ROAD)
    var needs = __test_construction_warning_count(NEEDS_ROAD)
    if (needs != 0) {
        __log_info_native('[test:186] ' + step + ': unexpected ' + NEEDS_ROAD)
        return false
    }
    var want = expect_shrine_warning ? 1 : 0
    if (near != want) {
        __log_info_native('[test:186] ' + step + ': ' + SHRINE_NEAR_ROAD + ' count ' + near + ', want ' + want)
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:186] shrine road radius warning')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    // Shrines are out of the adjacent road access hover/ghost allowlist.
    if (__test_building_type_hover_road_access(BUILDING_SHRINE_RA) != 0
        || __test_building_type_ghost_road_access(BUILDING_SHRINE_RA) != 0) {
        __log_info_native('[test:186] shrine still uses adjacent road access')
        __test_signal_ready()
        return
    }
    __log_marker('shrine_road_radius_hover_excluded_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test186_clear_roads(cx, cy, 12)
    __test_update_road_network()

    // No road within two tiles: warn with the shrine text, never the generic one.
    var far_id = test186_place_shrine(cx, cy)
    if (!far_id) {
        __log_info_native('[test:186] far shrine placement failed')
        __test_signal_ready()
        return
    }
    if (!test186_warnings_ok('far', true)) {
        __test_signal_ready()
        return
    }
    __log_marker('shrine_road_radius_far_warns_ok')

    // Road two tiles away (one empty tile between): within two spaces, no warning.
    var x2 = cx + 8
    terrain.add({ x: x2 + 2, y: cy }, TERRAIN_ROAD)
    __test_update_road_network()
    var two_id = test186_place_shrine(x2, cy)
    if (!two_id) {
        __log_info_native('[test:186] two-tile shrine placement failed')
        __test_signal_ready()
        return
    }
    if (!test186_warnings_ok('two_tiles', false)) {
        __test_signal_ready()
        return
    }
    __log_marker('shrine_road_radius_two_tiles_ok')

    // Adjacent road: no warning either.
    var x3 = cx - 8
    terrain.add({ x: x3 + 1, y: cy }, TERRAIN_ROAD)
    __test_update_road_network()
    var adj_id = test186_place_shrine(x3, cy)
    if (!adj_id) {
        __log_info_native('[test:186] adjacent shrine placement failed')
        __test_signal_ready()
        return
    }
    if (!test186_warnings_ok('adjacent', false)) {
        __test_signal_ready()
        return
    }
    __log_marker('shrine_road_radius_adjacent_ok')

    __log_info_native('[test:186] ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'shrine_road_radius_hover_excluded_ok',
        'shrine_road_radius_far_warns_ok',
        'shrine_road_radius_two_tiles_ok',
        'shrine_road_radius_adjacent_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:186] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

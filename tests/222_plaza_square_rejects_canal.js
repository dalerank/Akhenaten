// OG map_plaza_square_fits: a 2x2 plaza graphic needs four plaza roads with no
// water / building / canal on the square. Canal on a neighbour must force 1x1.
// Markers:
//   [test-marker] plaza_2x2_ok
//   [test-marker] plaza_canal_rejects_2x2_ok

function run_test() {
    __log_info_native('[test:222] plaza 2x2 rejects canal neighbour')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_prepare_terrain_patch(cx, cy, 4, TERRAIN_NONE)

    var tiles = [
        { x: cx, y: cy },
        { x: cx + 1, y: cy },
        { x: cx, y: cy + 1 },
        { x: cx + 1, y: cy + 1 }
    ]
    for (var i = 0; i < tiles.length; i++) {
        var t = tiles[i]
        if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_ROAD, t)) {
            __log_info_native('[test:222] cannot route road at ' + t.x + ',' + t.y)
            __test_signal_ready()
            return
        }
        __place_routed_building(t, t, ROUTED_BUILDING_ROAD)
        if (!terrain.is(t, TERRAIN_ROAD)) {
            __log_info_native('[test:222] road missing at ' + t.x + ',' + t.y)
            __test_signal_ready()
            return
        }
        __test_set_desirability(t.x, t.y, 20)
        __test_plaza_mark_tile(t.x, t.y)
    }

    __test_plaza_update_all()
    if (__test_map_multi_tile_size(cx, cy) != 2) {
        __log_info_native('[test:222] expected 2x2 plaza, size=' + __test_map_multi_tile_size(cx, cy))
        __test_signal_ready()
        return
    }
    __log_marker('plaza_2x2_ok')

    // Canal on SE neighbour: OG plaza_square_fits rejects the square.
    terrain.add({ x: cx + 1, y: cy + 1 }, TERRAIN_CANAL)
    __test_plaza_update_all()
    if (__test_map_multi_tile_size(cx, cy) != 1) {
        __log_info_native('[test:222] canal neighbour still 2x2, size=' + __test_map_multi_tile_size(cx, cy))
        __test_signal_ready()
        return
    }
    __log_marker('plaza_canal_rejects_2x2_ok')
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] plaza_2x2_ok')
        && __test_find_inlog('[test-marker] plaza_canal_rejects_2x2_ok')
}

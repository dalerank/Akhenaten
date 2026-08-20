// #644: granary touches both road networks; finish tile on asker net (stable prefer).
// Markers:
//   [test-marker] granary_dual_path_ok

function run_test() {
    __log_info_native('[test:185] granary dual-path access')
    test_ensure_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var gx = cx - 10
    var gy = cy - 10

    var granary_id = __test_building_create(BUILDING_GRANARY, gx, gy)
    if (!granary_id) {
        __log_info_native('[test:185] granary create failed')
        __test_signal_ready()
        return
    }

    // Clear leftover roads near the footprint so A/B stay disconnected components.
    var xx
    var yy
    for (yy = gy - 2; yy <= gy + 5; yy++) {
        for (xx = gx - 10; xx <= gx + 10; xx++) {
            terrain.remove({ x: xx, y: yy }, TERRAIN_ROAD)
        }
    }

    // West = net A (longer). East = net B stub. Granary is impassable so nets stay separate.
    var y
    for (y = gy; y <= gy + 3; y++) {
        terrain.add({ x: gx - 1, y: y }, TERRAIN_ROAD)
        terrain.add({ x: gx + 4, y: y }, TERRAIN_ROAD)
    }
    var x
    for (x = gx - 8; x <= gx - 2; x++) {
        terrain.add({ x: x, y: gy + 1 }, TERRAIN_ROAD)
        terrain.add({ x: x, y: gy + 2 }, TERRAIN_ROAD)
    }
    for (x = gx + 5; x <= gx + 7; x++) {
        terrain.add({ x: x, y: gy + 1 }, TERRAIN_ROAD)
        terrain.add({ x: x, y: gy + 2 }, TERRAIN_ROAD)
    }

    __test_update_road_network()
    __test_check_kingdome_access()

    var granary = city.get_building(granary_id)
    if (!granary || !granary.has_road_access) {
        __log_info_native('[test:185] granary missing road access')
        __test_signal_ready()
        return
    }

    var prefer_a = __test_grid_offset_xy(gx - 3, gy + 1)
    var prefer_b = __test_grid_offset_xy(gx + 5, gy + 1)
    var net_a = __test_tile_road_network(prefer_a)
    var net_b = __test_tile_road_network(prefer_b)
    if (net_a <= 0 || net_b <= 0 || net_a == net_b) {
        __log_info_native('[test:185] expected two networks got A=' + net_a + ' B=' + net_b
            + ' prefer_a=' + prefer_a + ' prefer_b=' + prefer_b)
        __test_signal_ready()
        return
    }

    if (!__test_granary_touches_network(granary_id, net_a)
        || !__test_granary_touches_network(granary_id, net_b)) {
        __log_info_native('[test:185] touches failed A=' + net_a + ' B=' + net_b)
        __test_signal_ready()
        return
    }

    var primary = __test_building_road_access_tile(granary_id)
    var finish_b = __test_granary_access_on_network(granary_id, net_b, prefer_b)
    if (finish_b < 0) {
        __log_info_native('[test:185] access_on_network B failed')
        __test_signal_ready()
        return
    }
    if (__test_tile_road_network(finish_b) != net_b) {
        __log_info_native('[test:185] finish B not on net B tile=' + finish_b
            + ' net=' + __test_tile_road_network(finish_b))
        __test_signal_ready()
        return
    }
    if (finish_b == primary) {
        __log_info_native('[test:185] finish B should differ from primary road_access')
        __test_signal_ready()
        return
    }

    var finish_b2 = __test_granary_access_on_network(granary_id, net_b, prefer_b)
    if (finish_b2 != finish_b) {
        __log_info_native('[test:185] finish not stable ' + finish_b + ' vs ' + finish_b2)
        __test_signal_ready()
        return
    }

    var finish_a = __test_granary_access_on_network(granary_id, net_a, prefer_a)
    if (finish_a < 0 || __test_tile_road_network(finish_a) != net_a) {
        __log_info_native('[test:185] finish A invalid')
        __test_signal_ready()
        return
    }

    __log_marker('granary_dual_path_ok')
    __test_signal_ready()
}

function check_valid() {
    var marker = '[test-marker] granary_dual_path_ok'
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:185] missing marker: ' + marker)
        return false
    }
    return true
}

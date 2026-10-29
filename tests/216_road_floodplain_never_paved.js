// OG map_tiles_road_desirability_paved (0x0047B8E0): floodplain roads stay dirt
// even when desirability > 4.
// Markers:
//   [test-marker] road_floodplain_never_paved_ok
//   [test-marker] road_dry_paved_at_high_des_ok

function run_test() {
    __log_info_native('[test:216] road paved rules vs floodplain')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    // Floodplain road at high desirability → not paved.
    test_prepare_terrain_patch(cx, cy, 4, TERRAIN_FLOODPLAIN)
    var flood = { x: cx, y: cy }
    if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_ROAD, flood)) {
        __log_info_native('[test:216] cannot route on floodplain')
        __test_signal_ready()
        return
    }
    __place_routed_building(flood, flood, ROUTED_BUILDING_ROAD)
    if (!terrain.is(flood, TERRAIN_ROAD)) {
        __log_info_native('[test:216] floodplain road not placed')
        __test_signal_ready()
        return
    }
    __test_set_desirability(flood.x, flood.y, 20)
    if (__test_road_is_paved(flood.x, flood.y) != 0) {
        __log_info_native('[test:216] floodplain road incorrectly paved at des=20')
        __test_signal_ready()
        return
    }
    __log_marker('road_floodplain_never_paved_ok')

    // Dry land at high desirability → paved (sanity that helper/des work).
    var dry = { x: cx + 8, y: cy + 8 }
    test_prepare_terrain_patch(dry.x, dry.y, 3, TERRAIN_NONE)
    if (!__map_routing_calculate_distances_for_building(ROUTED_BUILDING_ROAD, dry)) {
        __log_info_native('[test:216] cannot route on dry land')
        __test_signal_ready()
        return
    }
    __place_routed_building(dry, dry, ROUTED_BUILDING_ROAD)
    if (!terrain.is(dry, TERRAIN_ROAD)) {
        __log_info_native('[test:216] dry road not placed')
        __test_signal_ready()
        return
    }
    __test_set_desirability(dry.x, dry.y, 20)
    if (__test_road_is_paved(dry.x, dry.y) != 1) {
        __log_info_native('[test:216] dry road not paved at des=20')
        __test_signal_ready()
        return
    }
    __log_marker('road_dry_paved_at_high_des_ok')

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] road_floodplain_never_paved_ok')
        && __test_find_inlog('[test-marker] road_dry_paved_at_high_des_ok')
}

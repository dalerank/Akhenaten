// OG find_work: nearer floodplain farm with no road/garden path to its road_access
// is skipped; laborer takes the next reachable farm instead of poofing.

function test292_fail(msg) {
    __log_info_native('[test:292] ' + msg)
    __test_signal_ready()
}

function chebyshev(a, b) {
    var dx = a.x - b.x
    if (dx < 0) dx = -dx
    var dy = a.y - b.y
    if (dy < 0) dy = -dy
    return dx > dy ? dx : dy
}

function test292_place_floodplain_farm(x, y) {
    var type = BUILDING_GRAIN_FARM
    var footprint = __building_static_building_size(type)
    if (footprint <= 0) {
        footprint = 3
    }
    test_prepare_terrain_patch(x, y, footprint + 2, TERRAIN_FLOODPLAIN)
    return test_building_place(type, x, y)
}

function run_test() {
    __log_info_native('[test:292] laborer skip unreachable farm')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_WORK_CAMP)) {
        __scenario_building_allow(BUILDING_WORK_CAMP, true)
    }
    if (!__scenario_building_allowed(BUILDING_GRAIN_FARM)) {
        __scenario_building_allow(BUILDING_GRAIN_FARM, true)
    }

    __test_set_treasury(500000)
    city.floods.state = FLOOD_STATE_FARMABLE

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var camp = test_building_place(BUILDING_WORK_CAMP, cx - 20, cy)
    if (!camp) {
        camp = test_building_place(BUILDING_WORK_CAMP, -1, -1)
    }
    if (!camp) {
        return test292_fail('place work camp failed')
    }
    var camp_tile = __building_tile(camp)
    var laborer_tile = { x: camp_tile.x + 1, y: camp_tile.y }
    __test_make_road(laborer_tile.x, laborer_tile.y)
    __test_building_set_road_access(camp, laborer_tile.x, laborer_tile.y)

    var farm_a = test292_place_floodplain_farm(cx - 4, cy)
    var farm_b = test292_place_floodplain_farm(cx + 8, cy)
    if (!farm_a) {
        farm_a = __test_building_create(BUILDING_GRAIN_FARM, cx - 4, cy)
    }
    if (!farm_b) {
        farm_b = __test_building_create(BUILDING_GRAIN_FARM, cx + 8, cy)
    }
    if (!farm_a || !farm_b || farm_a == farm_b) {
        return test292_fail('place two floodplain farms failed a=' + farm_a + ' b=' + farm_b)
    }

    // Ensure floodplain under both (create path may skip terrain).
    test_prepare_terrain_patch(cx - 4, cy, 5, TERRAIN_FLOODPLAIN)
    test_prepare_terrain_patch(cx + 8, cy, 5, TERRAIN_FLOODPLAIN)

    var tile_a = __building_tile(farm_a)
    var tile_b = __building_tile(farm_b)
    var dist_a = chebyshev(laborer_tile, tile_a)
    var dist_b = chebyshev(laborer_tile, tile_b)
    var near = dist_a <= dist_b ? farm_a : farm_b
    var far = dist_a <= dist_b ? farm_b : farm_a
    var far_tile = dist_a <= dist_b ? tile_b : tile_a

    var near_b = city.get_building(near)
    near_b.num_workers = 0
    near_b.distance_from_entry = 1
    // Isolated access: empty land far from the laborer's road — no citizen path.
    __test_building_set_road_access(near, laborer_tile.x + 80, laborer_tile.y + 80)

    var far_b = city.get_building(far)
    far_b.num_workers = 0
    far_b.distance_from_entry = 1
    // Reachable: road by the farm; access on the laborer's road tile (same network).
    __test_make_road(far_tile.x, far_tile.y)
    __test_make_road(far_tile.x + 1, far_tile.y)
    __test_building_set_road_access(far, laborer_tile.x, laborer_tile.y)

    __test_map_routing_update_land()

    var fid = __test_figure_create(FIGURE_LABORER, laborer_tile.x, laborer_tile.y)
    __test_figure_set_home_slot(fid, camp)

    var dest = __worker_find_work(fid) | 0
    if (dest != far) {
        return test292_fail('want reachable farm ' + far + ' got ' + dest
            + ' (near=' + near + ' dist_near=' + (dist_a <= dist_b ? dist_a : dist_b)
            + ' dist_far=' + (dist_a <= dist_b ? dist_b : dist_a) + ')')
    }

    __log_marker('laborer_skip_unreachable_farm_ok:' + dest)
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] laborer_skip_unreachable_farm_ok:')
}

// Gems seed per rock sprite (1x1/2x2/3x3) plus a 1-tile halo beyond that footprint.
// Markers:
//   [test-marker] gemstone_mine_progress_ok

var __test202_ok = false

function run_test() {
    __log_info_native('[test:202] gemstone mine production beside rock')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var mine_x = cx
    var mine_y = cy
    terrain.add({ x: mine_x + 2, y: mine_y }, TERRAIN_ROCK)
    terrain.add({ x: mine_x + 2, y: mine_y + 1 }, TERRAIN_ROCK)
    __test_map_gems_init()

    var bid = test_building_place(BUILDING_GEMSTONE_MINE, mine_x, mine_y)
    if (!bid) {
        bid = __test_building_create(BUILDING_GEMSTONE_MINE, mine_x, mine_y)
    }
    if (!bid) {
        __log_info_native('[test:202] place/create failed')
        __test_signal_ready()
        return
    }

    var b = city.get_building(bid)
    if (!b || b.output_resource_id != RESOURCE_GEMS) {
        __log_info_native('[test:202] output is not gems: ' + (b ? b.output_resource_id : 'no building'))
        __test_signal_ready()
        return
    }

    __test_building_set_workers(bid, 8)
    __test_building_update_day(bid)
    var before = __building_industry_progress_pct(bid)
    var i
    for (i = 0; i < 8; i++) {
        __test_city_industry_update_production()
    }
    var after = __building_industry_progress_pct(bid)
    if (after <= before) {
        __log_info_native('[test:202] progress did not increase before=' + before + ' after=' + after)
        __test_signal_ready()
        return
    }

    __log_marker('gemstone_mine_progress_ok')
    __test202_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test202_ok && __test_find_inlog('[test-marker] gemstone_mine_progress_ok')
}

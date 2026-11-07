// OG farm arrival: floodplain farm gets full model laborers (not distance-scaled).

function test284_fail(msg) {
    __log_info_native('[test:284] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:284] laborer farm staffing OG')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_WORK_CAMP)) {
        __scenario_building_allow(BUILDING_WORK_CAMP, true)
    }
    if (!__scenario_building_allowed(BUILDING_GRAIN_FARM)) {
        __scenario_building_allow(BUILDING_GRAIN_FARM, true)
    }

    __test_set_treasury(500000)
    var camp = test_building_place(BUILDING_WORK_CAMP, -1, -1)
    if (!camp) {
        return test284_fail('place work camp failed')
    }

    var farm = test_farm_place(BUILDING_GRAIN_FARM, TERRAIN_FLOODPLAIN)
    if (!farm) {
        farm = __test_building_create(BUILDING_GRAIN_FARM, -1, -1)
    }
    if (!farm) {
        return test284_fail('place floodplain farm failed')
    }

    __test_building_force_road_access(farm)
    var farm_b = city.get_building(farm)
    var max_workers = farm_b.max_workers | 0
    if (max_workers <= 0) {
        return test284_fail('farm max_workers unset')
    }
    farm_b.num_workers = 0

    var tile = __building_tile(farm)
    var fid = __test_figure_create(FIGURE_LABORER, tile.x, tile.y)
    __test_figure_set_home_slot(fid, camp)

    var staffed = __worker_force_farm_arrival(fid, farm) | 0
    if (staffed != max_workers) {
        return test284_fail('OG farm staffing want max_workers=' + max_workers + ' got ' + staffed)
    }
    __log_marker('laborer_farm_staffing_og_ok:' + staffed)
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] laborer_farm_staffing_og_ok:')
}

// Frog vs OG animals_wild.c:443-446: a frog that cannot reach the road by its house (DIRECTION_LOST) frees the
// house's immigrant slot, sets the house's distance_from_entry to 0 and dies.
// Markers:
//   [test-marker] frog741_lost_ok

function test504_fail(msg) {
    __log_info_native('[test:504] FAIL: ' + msg)
    __test_signal_ready()
}

function test504_road(x, y) {
    if (!test_planner_enter_build_mode(BUILDING_ROAD)) {
        return false
    }
    __map_routing_calculate_distances_for_building(ROUTED_BUILDING_ROAD, { x: x, y: y })
    city_planner.update(x, y)
    city_planner.construction_start(x, y)
    city_planner.construction_update(x, y)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()
    return __map_terrain_is({ x: x, y: y }, TERRAIN_ROAD)
}

function test504_hut(x, y) {
    if (!test_planner_enter_build_mode(BUILDING_HOUSE_VACANT_LOT)) {
        return 0
    }
    city_planner.update(x, y)
    if (city_planner.can_be_placed() != CAN_PLACE) {
        test_planner_exit_build_mode()
        return 0
    }
    city_planner.construction_start(x, y)
    city_planner.construction_update(x, y)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()
    var hid = __building_at(x, y)
    if (!hid || __building_type(hid) != BUILDING_HOUSE_CRUDE_HUT) {
        return 0
    }
    return hid
}

function test504_site() {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    for (var i = 0; i < 12; i++) {
        var x = cx - 12 + (i % 4) * 6
        var y = cy - 9 + ((i / 4) | 0) * 7
        if (!test504_road(x, y + 1)) {
            continue
        }
        var hid = test504_hut(x, y)
        if (!hid) {
            continue
        }
        var pond = { x: x, y: y + 4 }
        terrain.add(pond, TERRAIN_WATER)
        for (var dy = -1; dy <= 1; dy++) {
            for (var dx = -1; dx <= 1; dx++) {
                if (dx != 0 || dy != 0) {
                    terrain.add({ x: pond.x + dx, y: pond.y + dy }, TERRAIN_ROCK)
                }
            }
        }
        __test_map_routing_update_land()
        __test_map_routing_update_water()
        return { hid: hid, water: pond }
    }
    return null
}

function run_test() {
    __log_info_native('[test:504] lost frog OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    city.figures.remove_figures(FIGURE_FROG)

    var site = test504_site()
    if (!site) {
        return test504_fail('no site for hut + road + walled pond')
    }
    __test_house_set_population(site.hid, 10)
    city.get_building(site.hid).distance_from_entry = 7

    var fid = __test_frog_create_at(site.hid, site.water.x, site.water.y)
    if (!fid) {
        return test504_fail('frog not created')
    }
    for (var t = 0; t < 2000 && __figure_is_valid(fid); t++) {
        __test_figure_action_perform(fid)
    }
    var b = city.get_building(site.hid)
    var slot = __test_building_figure_id(site.hid, 2)
    if (__figure_is_valid(fid) || b.distance_from_entry != 0 || slot == fid || city.get_house(site.hid).population != 10) {
        return test504_fail('alive=' + __figure_is_valid(fid) + ' distance_from_entry=' + b.distance_from_entry
            + ' slot=' + slot + ' pop=' + city.get_house(site.hid).population)
    }
    __log_marker('frog741_lost_ok')
    __test_signal_ready()
}

function check_valid() {
    if (!__test_find_inlog('[test-marker] frog741_lost_ok')) {
        __log_info_native('[test:504] missing marker: frog741_lost_ok')
        return false
    }
    return true
}

function done() {
    city.figures.remove_figures(FIGURE_FROG)
}

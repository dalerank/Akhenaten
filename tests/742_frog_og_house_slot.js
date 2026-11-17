// Frog vs OG city_disasters.c city_frogs_create and animals_wild.c figure_frog_action:
//   the frog only takes the house's immigrant slot; a homeless already walking to that house keeps walking
//   (carriers.c homeless action never checks the slot);
//   a frog entering an empty house still creates the (empty) homeless walker (house_population.c:403).
// Markers:
//   [test-marker] frog742_homeless_keeps_going_ok
//   [test-marker] frog742_empty_house_homeless_ok

var ACTION_HOMELESS_GOING_TO_HOUSE = 1

function test742_fail(msg) {
    __log_info_native('[test:742] FAIL: ' + msg)
    __test_signal_ready()
}

function test742_road(x, y) {
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

function test742_hut(x, y) {
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

function test742_sites(count) {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var sites = []
    for (var i = 0; i < 16 && sites.length < count; i++) {
        var x = cx - 12 + (i % 4) * 6
        var y = cy - 12 + ((i / 4) | 0) * 6
        if (!test742_road(x, y + 1)) {
            continue
        }
        var hid = test742_hut(x, y)
        if (!hid) {
            continue
        }
        terrain.add({ x: x, y: y + 3 }, TERRAIN_WATER)
        terrain.add({ x: x, y: y + 4 }, TERRAIN_WATER)
        sites.push({ hid: hid, tile: { x: x, y: y }, road: { x: x, y: y + 1 }, water: { x: x, y: y + 3 } })
    }
    __test_map_routing_update_land()
    __test_map_routing_update_water()
    return sites
}

function test742_count_at(type, tile) {
    __test_process_events()
    var n = 0
    for (var i = 1; i < 2000; i++) {
        if (__test_figure_is_alive(i) == 1 && __figure_get_type(i) == type && __test_figure_tile_x(i) == tile.x
            && __test_figure_tile_y(i) == tile.y) {
            n++
        }
    }
    return n
}

function run_test() {
    __log_info_native('[test:742] frog house slot OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    city.figures.remove_figures(FIGURE_FROG)
    city.figures.remove_figures(FIGURE_HOMELESS)

    var sites = test742_sites(2)
    if (sites.length < 2) {
        return test742_fail('placed ' + sites.length + ' sites, want 2')
    }

    var a = sites[0]
    __test_house_set_population(a.hid, 2)
    city.get_building(a.hid).distance_from_entry = 5
    city.get_building(sites[1].hid).distance_from_entry = 0
    var hl = __test_figure_create(FIGURE_HOMELESS, a.road.x, a.road.y)
    if (!hl) {
        return test742_fail('homeless not created')
    }
    for (var t = 0; t < 200 && __test_figure_get_action(hl) != ACTION_HOMELESS_GOING_TO_HOUSE; t++) {
        __test_figure_action_perform(hl)
    }
    if (__test_figure_get_action(hl) != ACTION_HOMELESS_GOING_TO_HOUSE || __test_building_figure_id(a.hid, 2) != hl) {
        return test742_fail('homeless not heading to hut: action=' + __test_figure_get_action(hl)
            + ' slot=' + __test_building_figure_id(a.hid, 2))
    }
    var fa = __test_frog_create_at(a.hid, a.water.x, a.water.y)
    if (!fa || __test_building_figure_id(a.hid, 2) != fa) {
        return test742_fail('frog A not created or slot not taken')
    }
    if (__test_figure_get_action(hl) != ACTION_HOMELESS_GOING_TO_HOUSE) {
        return test742_fail('homeless action after frog=' + __test_figure_get_action(hl) + ' want '
            + ACTION_HOMELESS_GOING_TO_HOUSE)
    }
    __log_marker('frog742_homeless_keeps_going_ok')
    city.figures.remove_figures(FIGURE_FROG)
    city.figures.remove_figures(FIGURE_HOMELESS)

    var b = sites[1]
    if (city.get_house(b.hid).population != 0) {
        return test742_fail('hut B not empty')
    }
    var homeless_before = test742_count_at(FIGURE_HOMELESS, b.tile)
    var fb = __test_frog_create_at(b.hid, b.water.x, b.water.y)
    if (!fb) {
        return test742_fail('frog B not created')
    }
    for (var t2 = 0; t2 < 6000 && __figure_is_valid(fb); t2++) {
        __test_figure_action_perform(fb)
    }
    var frog_alive = __figure_is_valid(fb) && __figure_get_type(fb) == FIGURE_FROG
    var homeless_after = test742_count_at(FIGURE_HOMELESS, b.tile)
    if (frog_alive || city.get_house(b.hid).frog_infest_days < 1 || homeless_after != homeless_before + 1) {
        return test742_fail('empty hut: frog alive=' + frog_alive + ' days=' + city.get_house(b.hid).frog_infest_days
            + ' homeless ' + homeless_before + ' -> ' + homeless_after)
    }
    __log_marker('frog742_empty_house_homeless_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = ['frog742_homeless_keeps_going_ok', 'frog742_empty_house_homeless_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:742] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.figures.remove_figures(FIGURE_FROG)
    city.figures.remove_figures(FIGURE_HOMELESS)
}

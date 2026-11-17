// Frog vs OG animals_wild.c figure_frog_action and city_disasters.c city_frogs_create:
//   city_frogs_create logs "Created frog %d at: %d, %d, headed for building: %d";
//   the frog has one animation group (681) for every state but the corpse;
//   while it hops into the house it is a ghost only when in_building_wait_ticks is set (:475): drawn from the
//   road to the footprint, hidden once over it;
//   in the house the people become homeless and the house is shut.
// Markers:
//   [test-marker] frog740_created_log_ok
//   [test-marker] frog740_walk_anim_ok
//   [test-marker] frog740_visible_entering_ok
//   [test-marker] frog740_infest_ok

var ACTION_FROG_CREATED = 120
var ACTION_FROG_ENTERING_HOUSE = 122

function test740_fail(msg) {
    __log_info_native('[test:740] FAIL: ' + msg)
    __test_signal_ready()
}

function test740_road(x, y) {
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

function test740_hut(x, y) {
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

function test740_site() {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    for (var i = 0; i < 12; i++) {
        var x = cx - 12 + (i % 4) * 6
        var y = cy - 9 + ((i / 4) | 0) * 6
        if (!test740_road(x, y + 1)) {
            continue
        }
        var hid = test740_hut(x, y)
        if (!hid) {
            continue
        }
        terrain.add({ x: x, y: y + 3 }, TERRAIN_WATER)
        terrain.add({ x: x, y: y + 4 }, TERRAIN_WATER)
        __test_map_routing_update_land()
        __test_map_routing_update_water()
        return { hid: hid, water: { x: x, y: y + 3 } }
    }
    return null
}

function run_test() {
    __log_info_native('[test:740] frog enters house OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    city.figures.remove_figures(FIGURE_FROG)

    var site = test740_site()
    if (!site) {
        return test740_fail('no site for hut + road + water')
    }
    if (__test_house_set_population(site.hid, 10) < 1) {
        return test740_fail('hut population')
    }

    var fid = __test_frog_create_at(site.hid, site.water.x, site.water.y)
    if (!fid) {
        return test740_fail('frog not created')
    }
    if (!__test_find_inlog('Created frog ' + fid + ' at: ' + site.water.x + ', ' + site.water.y + ', headed for building: ' + site.hid)) {
        return test740_fail('no OG creation debug line for frog ' + fid)
    }
    __log_marker('frog740_created_log_ok')

    __test_figure_set_action(fid, ACTION_FROG_CREATED)
    __test_figure_update_animation(fid)
    var key = __figure_get_anim_key(fid)
    if (key != 'walk') {
        return test740_fail('CREATED anim key want "walk", got "' + key + '"')
    }
    __log_marker('frog740_walk_anim_ok')

    var entering_ticks = 0
    var visible_entering = 0
    for (var t = 0; t < 6000 && __figure_is_valid(fid); t++) {
        __test_figure_action_perform(fid)
        if (__figure_is_valid(fid) && __figure_get_action_state(fid) == ACTION_FROG_ENTERING_HOUSE) {
            entering_ticks++
            if (__test_figure_is_visible(fid) == 1) {
                visible_entering++
            }
        }
    }
    if (entering_ticks < 2 || visible_entering < 1 || visible_entering == entering_ticks) {
        return test740_fail('entering ticks=' + entering_ticks + ' visible=' + visible_entering)
    }
    __log_marker('frog740_visible_entering_ok')

    var h = city.get_house(site.hid)
    if (__figure_is_valid(fid) || h.population != 0 || h.frog_infest_days < 1) {
        return test740_fail('infest: alive=' + __figure_is_valid(fid) + ' pop=' + h.population + ' days=' + h.frog_infest_days)
    }
    __log_marker('frog740_infest_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = ['frog740_created_log_ok', 'frog740_walk_anim_ok', 'frog740_visible_entering_ok', 'frog740_infest_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:740] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

function done() {
    city.figures.remove_figures(FIGURE_FROG)
}

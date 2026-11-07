// OG reed gatherer load: a gatherer brings 50 reeds home (ANIMAL_RULE_REED_GATHERER_REEDS_LOAD);
// the building's storage check counts gatherers by the same load.

var __test287_ok = false

function test287_fail(msg) {
    __log_info_native('[test:287] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:287] reed gatherer load 50')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_REED_GATHERER, -1, -1)
    if (!bid) {
        bid = __test_building_create(BUILDING_REED_GATHERER, -1, -1)
    }
    if (!bid) {
        return test287_fail('reed gatherer place/create failed')
    }

    var t = __building_tile(bid)
    var rx = t.x + 2
    var ry = t.y
    terrain.add({ x: rx, y: ry }, TERRAIN_ROAD)
    terrain.add({ x: rx + 1, y: ry }, TERRAIN_ROAD)
    __test_building_set_road_access(bid, rx, ry)
    __test_map_routing_update_land()

    var b = city.get_building(bid)
    var before = b.stored_resource(RESOURCE_REEDS)
    var fid = test_figure_create(FIGURE_REED_GATHERER, rx, ry)
    if (!fid) {
        return test287_fail('create reed gatherer failed')
    }
    test_figure_set_home(fid, bid)
    __test_figure_set_action(fid, 11)
    for (var tick = 0; tick < 64; tick++) {
        if (!__test_figure_is_alive(fid) || b.stored_resource(RESOURCE_REEDS) != before) {
            break
        }
        __test_figure_action_perform(fid)
    }

    var after = city.get_building(bid).stored_resource(RESOURCE_REEDS)
    if (after - before != 50) {
        return test287_fail('return home should store +50 reeds, before=' + before + ' after=' + after
            + ' alive=' + __test_figure_is_alive(fid) + ' action=' + __test_figure_get_action(fid))
    }
    __log_marker('test287_load_50_ok')

    __test287_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test287_ok && __test_find_inlog('[test-marker] test287_load_50_ok')
}

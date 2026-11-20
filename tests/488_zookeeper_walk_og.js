// Zookeeper OG walk (walkers.c figure_entertainer_action, FIG_ZOOKEEPER): an armed walker (Figure_model 105,
// category 2) that roams 512 ticks, returns to a road near the zoo and vanishes there. Sent back to
// ENTERTAINER_CREATED (as after a ferry) it exits to the road, walks to the closest working zoo and vanishes there.

var __test488_ok = false

function test488_fail(msg) {
    __log_info_native('[test:488] FAIL: ' + msg)
    __test_signal_ready()
}

function test488_zoo() {
    if (!__scenario_building_allowed(BUILDING_ZOO)) {
        __scenario_building_allow(BUILDING_ZOO, true)
    }
    city.resources.set_produce(RESOURCE_STRAW, true)
    city.resources.set_produce(RESOURCE_GAMEMEAT, true)
    var bid = test_building_place(BUILDING_ZOO, -1, -1)
    if (!bid) {
        return 0
    }
    var zt = __building_tile(bid)
    for (var dx = -2; dx < 9; dx++) {
        terrain.add({ x: zt.x + dx, y: zt.y + 6 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_building_set_road_access(bid, zt.x, zt.y + 6)
    return bid
}

function test488_spawn(bid) {
    city.figures.remove_figures(FIGURE_ZOOKEEPER)
    __test_figures_update()
    var b = city.get_building(bid)
    b.consume_resource(RESOURCE_STRAW, -200)
    b.consume_resource(RESOURCE_GAMEMEAT, -200)
    b.figure_spawn_delay = 0
    for (var i = 0; i < 300; i++) {
        __test_building_set_workers(bid, 30)
        __test_building_spawn_figure(bid)
        var fid = __test_building_figure_id(bid, 0)
        if (fid && __figure_get_type(fid) == FIGURE_ZOOKEEPER) {
            return fid
        }
    }
    return 0
}

function test488_params() {
    if (__test_figure_type_category(FIGURE_ZOOKEEPER) != figure_category_armed) {
        test488_fail('OG zookeeper is fighting unit 2 (armed), got category ' + __test_figure_type_category(FIGURE_ZOOKEEPER))
        return false
    }
    if (__test_figure_type_max_roam(FIGURE_ZOOKEEPER) != 512) {
        test488_fail('OG entertainer roam is 512, got ' + __test_figure_type_max_roam(FIGURE_ZOOKEEPER))
        return false
    }
    __log_marker('test488_params')
    return true
}

function test488_roam(bid) {
    var fid = test488_spawn(bid)
    if (!fid || __figure_get_action_state(fid) != 4) {
        test488_fail('zookeeper expected roaming (4) at spawn, fid ' + fid)
        return false
    }
    var returned_at = -1
    var gone = false
    for (var t = 1; t <= 3000; t++) {
        __test_figure_action_perform(fid)
        if (!__figure_is_valid(fid) || __figure_get_type(fid) != FIGURE_ZOOKEEPER) {
            gone = true
            break
        }
        var st = __figure_get_action_state(fid)
        if (st != 4 && st != 5) {
            test488_fail('roaming zookeeper must only roam (4) and return (5), state ' + st + ' at tick ' + t)
            return false
        }
        if (st == 5 && returned_at < 0) {
            returned_at = t
        }
    }
    if (returned_at != 512) {
        test488_fail('OG zookeeper roams 512 ticks before returning, returned at tick ' + returned_at)
        return false
    }
    if (!gone) {
        test488_fail('returning zookeeper must vanish at the road near the zoo')
        return false
    }
    __log_marker('test488_roam')
    return true
}

function test488_venue(bid) {
    var fid = test488_spawn(bid)
    if (!fid) {
        test488_fail('no zookeeper for the venue walk')
        return false
    }
    __test_figure_set_action(fid, 0)
    __test_figure_set_wait_ticks(fid, 1)
    var to_venue = false
    var gone = false
    for (var t = 1; t <= 4000; t++) {
        __test_figure_action_perform(fid)
        if (!__figure_is_valid(fid) || __figure_get_type(fid) != FIGURE_ZOOKEEPER) {
            gone = true
            break
        }
        var st = __figure_get_action_state(fid)
        if (st == 2) {
            to_venue = true
        }
    }
    if (!to_venue) {
        test488_fail('created zookeeper must head to the closest working zoo (2)')
        return false
    }
    if (!gone) {
        test488_fail('zookeeper must vanish when it reaches the zoo, state ' + __figure_get_action_state(fid))
        return false
    }
    __log_marker('test488_venue')
    return true
}

function run_test() {
    __log_info_native('[test:488] zookeeper walk OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var bid = test488_zoo()
    if (!bid) {
        test488_fail('zoo place failed')
        return
    }
    if (!test488_params() || !test488_roam(bid) || !test488_venue(bid)) {
        return
    }

    __test488_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test488_ok
        && __test_find_inlog('[test-marker] test488_params')
        && __test_find_inlog('[test-marker] test488_roam')
        && __test_find_inlog('[test-marker] test488_venue')
}

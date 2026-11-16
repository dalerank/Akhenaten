// Magistrate OG service and walk (service.c:661, walkers.c law_walker_action with is_constable 0): crime within 2
// tiles drops by the courthouse reduction (500), inhabited houses within 2 tiles get courthouse access 96 (empty
// ones and other buildings do not), min_max_seen is the highest crime seen and no houses count. The walker goes
// created -> roaming 640 -> returning to a road near home -> entering -> gone.

var __test601_ok = false

function test601_fail(msg) {
    __log_info_native('[test:601] FAIL: ' + msg)
    __test_signal_ready()
}

function test601_courthouse() {
    var bid = test_building_place(BUILDING_COURTHOUSE, -1, -1)
    if (!bid) {
        return 0
    }
    var bt = __building_tile(bid)
    for (var dx = -3; dx < 7; dx++) {
        terrain.add({ x: bt.x + dx, y: bt.y + 3 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_building_set_road_access(bid, bt.x, bt.y + 3)
    __test_building_set_workers(bid, 10)
    return bid
}

function test601_spawn(bid) {
    city.figures.remove_figures(FIGURE_MAGISTRATE)
    __test_figures_update()
    city.get_building(bid).figure_spawn_delay = 0
    __test_building_spawn_figure(bid)
    return __test_building_figure_id(bid, 0)
}

function test601_service(bid) {
    var fid = test601_spawn(bid)
    if (!fid) {
        test601_fail('no magistrate spawned')
        return false
    }
    var mt = __figure_get_tile(fid)
    var near_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, mt.x + 1, mt.y + 1)
    var empty_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, mt.x - 1, mt.y + 1)
    var far_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, mt.x + 1, mt.y + 4)
    if (!near_id || !empty_id || !far_id) {
        test601_fail('house create failed')
        return false
    }
    __test_house_set_population(near_id, 10)
    __test_house_set_population(far_id, 10)
    city.get_house(near_id).criminal_active = 60
    city.get_house(empty_id).criminal_active = 70
    city.get_house(far_id).criminal_active = 40
    city.get_house(near_id).magistrate = 0
    city.get_house(empty_id).magistrate = 0
    city.get_house(far_id).magistrate = 0

    var houses = __test_figure_provide_service(fid)
    if (houses != 0) {
        test601_fail('OG magistrate counts no houses, got ' + houses)
        return false
    }
    if (city.get_house(near_id).criminal_active != 0 || city.get_house(empty_id).criminal_active != 0) {
        test601_fail('crime within 2 tiles must drop by 500 to 0')
        return false
    }
    if (city.get_house(far_id).criminal_active != 40) {
        test601_fail('crime 4 tiles away must stay 40, got ' + city.get_house(far_id).criminal_active)
        return false
    }
    if (city.get_figure(fid).min_max_seen != 70) {
        test601_fail('min_max_seen must be the highest crime seen (70), got ' + city.get_figure(fid).min_max_seen)
        return false
    }
    if (city.get_house(near_id).magistrate != 96) {
        test601_fail('inhabited house near the magistrate must get access 96, got ' + city.get_house(near_id).magistrate)
        return false
    }
    if (city.get_house(empty_id).magistrate != 0) {
        test601_fail('empty house must not get courthouse access, got ' + city.get_house(empty_id).magistrate)
        return false
    }
    if (city.get_house(far_id).magistrate != 0) {
        test601_fail('house 4 tiles away must not get courthouse access')
        return false
    }
    __test_figure_provide_service(fid)
    if (city.get_figure(fid).min_max_seen != 0) {
        test601_fail('min_max_seen is set each pass (OG), got ' + city.get_figure(fid).min_max_seen)
        return false
    }
    __log_marker('test601_coverage')
    return true
}

function test601_walk(bid) {
    var fid = test601_spawn(bid)
    if (!fid || __figure_get_action_state(fid) != 70) {
        test601_fail('magistrate expected in ACTION_70')
        return false
    }

    var returned_at = -1
    var entered = false
    var gone = false
    for (var t = 1; t <= 2000; t++) {
        __test_figure_action_perform(fid)
        if (!__figure_is_valid(fid) || __figure_get_type(fid) != FIGURE_MAGISTRATE) {
            gone = true
            break
        }
        var st = __figure_get_action_state(fid)
        if (t == 1 && st != 72) {
            test601_fail('created magistrate must start roaming on the first tick, state ' + st)
            return false
        }
        if (st == 74 || st == 75) {
            test601_fail('OG magistrate never heads for a fort, state ' + st)
            return false
        }
        if (st == 73 && returned_at < 0) {
            returned_at = t
        }
        if (st == 71) {
            entered = true
        }
    }
    if (returned_at != 641) {
        test601_fail('OG law walker roams 640 ticks before returning, returned at tick ' + returned_at)
        return false
    }
    if (!entered || !gone) {
        test601_fail('magistrate must enter the courthouse and disappear (entered ' + entered + ', gone ' + gone + ')')
        return false
    }
    __log_marker('test601_walk')
    return true
}

function run_test() {
    __log_info_native('[test:601] magistrate service OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var bid = test601_courthouse()
    if (!bid) {
        test601_fail('courthouse place failed')
        return
    }
    if (!test601_service(bid) || !test601_walk(bid)) {
        return
    }

    __test601_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test601_ok
        && __test_find_inlog('[test-marker] test601_coverage')
        && __test_find_inlog('[test-marker] test601_walk')
}

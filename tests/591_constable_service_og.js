// Constable OG service and walk (service.c:657, walkers.c law_walker_action): crime coverage lowers the crime of
// houses within 2 tiles by the police reduction (100) and min_max_seen keeps the highest crime seen; no houses
// count to the station. The walker goes created -> roaming 640 -> returning to a road near home -> entering ->
// gone. Killed, it shows the death animation and disappears; the station then sends a new one.

var __test591_ok = false

function test591_fail(msg) {
    __log_info_native('[test:591] FAIL: ' + msg)
    __test_signal_ready()
}

function test591_station() {
    var bid = test_building_place(BUILDING_POLICE_STATION, -1, -1)
    if (!bid) {
        return 0
    }
    var bt = __building_tile(bid)
    for (var dx = -2; dx < 4; dx++) {
        terrain.add({ x: bt.x + dx, y: bt.y + 1 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_building_set_road_access(bid, bt.x, bt.y + 1)
    __test_building_set_workers(bid, 6)
    return bid
}

function test591_spawn(bid) {
    city.get_building(bid).figure_spawn_delay = 0
    __test_building_spawn_figure(bid)
    return __test_building_figure_id(bid, 0)
}

function test591_service(bid) {
    var fid = test591_spawn(bid)
    if (!fid) {
        test591_fail('no constable spawned')
        return false
    }
    var ct = __figure_get_tile(fid)
    var near_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, ct.x + 1, ct.y + 1)
    var far_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, ct.x + 1, ct.y + 4)
    if (!near_id || !far_id) {
        test591_fail('house create failed')
        return false
    }
    __test_house_set_population(near_id, 10)
    __test_house_set_population(far_id, 10)
    city.get_house(near_id).criminal_active = 60
    city.get_house(far_id).criminal_active = 40

    var houses = __test_figure_provide_service(fid)
    if (houses != 0) {
        test591_fail('OG constable counts no houses, got ' + houses)
        return false
    }
    if (city.get_house(near_id).criminal_active != 0) {
        test591_fail('crime near the constable must drop by 100 to 0, got ' + city.get_house(near_id).criminal_active)
        return false
    }
    if (city.get_house(far_id).criminal_active != 40) {
        test591_fail('crime 4 tiles away must stay 40, got ' + city.get_house(far_id).criminal_active)
        return false
    }
    if (city.get_figure(fid).min_max_seen != 60) {
        test591_fail('min_max_seen must be the highest crime seen (60), got ' + city.get_figure(fid).min_max_seen)
        return false
    }
    __test_figure_provide_service(fid)
    if (city.get_figure(fid).min_max_seen != 0) {
        test591_fail('min_max_seen is set each pass (OG), got ' + city.get_figure(fid).min_max_seen)
        return false
    }
    __log_marker('test591_coverage')
    return true
}

function test591_walk(bid) {
    city.figures.remove_figures(FIGURE_CONSTABLE)
    __test_figures_update()
    var fid = test591_spawn(bid)
    if (!fid || __figure_get_action_state(fid) != 70) {
        test591_fail('constable expected in ACTION_70')
        return false
    }

    var returned_at = -1
    var entered = false
    var gone = false
    for (var t = 1; t <= 2000; t++) {
        __test_figure_action_perform(fid)
        if (!__figure_is_valid(fid) || __figure_get_type(fid) != FIGURE_CONSTABLE) {
            gone = true
            break
        }
        var st = __figure_get_action_state(fid)
        if (t == 1 && st != 72) {
            test591_fail('created constable must start roaming on the first tick, state ' + st)
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
        test591_fail('OG law walker roams 640 ticks before returning, returned at tick ' + returned_at)
        return false
    }
    if (!entered || !gone) {
        test591_fail('constable must enter the station and disappear (entered ' + entered + ', gone ' + gone + ')')
        return false
    }
    __log_marker('test591_walk')
    return true
}

function test591_death(bid) {
    __test_figures_update()
    var fid = test591_spawn(bid)
    if (!fid) {
        test591_fail('no constable for the death check')
        return false
    }
    __test_figure_kill(fid)
    if (!__test_figure_is_dying(fid)) {
        test591_fail('killed constable must be dying')
        return false
    }
    __test_figure_action_perform_dying(fid)
    if (__figure_get_anim_key(fid) != 'death') {
        test591_fail('dying constable must use the death animation, got ' + __figure_get_anim_key(fid))
        return false
    }
    for (var t = 0; t < 1000 && __figure_is_valid(fid) && __figure_get_type(fid) == FIGURE_CONSTABLE; t++) {
        __test_figure_action_perform_dying(fid)
    }
    if (__figure_is_valid(fid) && __figure_get_type(fid) == FIGURE_CONSTABLE) {
        test591_fail('corpse must disappear')
        return false
    }
    var next = test591_spawn(bid)
    if (!next || next == 0) {
        test591_fail('station must send a new constable after the death')
        return false
    }
    __log_marker('test591_death')
    return true
}

function run_test() {
    __log_info_native('[test:591] constable service OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var bid = test591_station()
    if (!bid) {
        test591_fail('police station place failed')
        return
    }
    if (!test591_service(bid) || !test591_walk(bid) || !test591_death(bid)) {
        return
    }

    __test591_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test591_ok
        && __test_find_inlog('[test-marker] test591_coverage')
        && __test_find_inlog('[test-marker] test591_walk')
        && __test_find_inlog('[test-marker] test591_death')
}

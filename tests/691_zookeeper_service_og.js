// Zookeeper OG service and combat (service.c service_provide_zoo_coverage, military.c category_attacks): zoo
// access 96 for inhabited houses within 2 tiles, only those count to the zoo; empty houses and other buildings
// get nothing. As an armed walker it attacks a criminal on its tile. Killed, it shows the death animation.

var __test691_ok = false

function test691_fail(msg) {
    __log_info_native('[test:691] FAIL: ' + msg)
    __test_signal_ready()
}

function test691_zoo() {
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

function test691_spawn(bid) {
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

function test691_service(bid) {
    var fid = test691_spawn(bid)
    if (!fid) {
        test691_fail('no zookeeper spawned')
        return false
    }
    var ct = __figure_get_tile(fid)
    var near_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, ct.x, ct.y + 1)
    var empty_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, ct.x + 1, ct.y + 2)
    var far_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, ct.x, ct.y + 4)
    if (!near_id || !empty_id || !far_id) {
        test691_fail('house create failed')
        return false
    }
    __test_house_set_population(near_id, 10)
    __test_house_set_population(empty_id, 0)
    __test_house_set_population(far_id, 10)

    var houses = __test_figure_provide_service(fid)
    if (houses != 1) {
        test691_fail('OG counts only inhabited houses within 2 tiles (1), got ' + houses)
        return false
    }
    if (city.get_house(near_id).zookeeper != 96) {
        test691_fail('house near the zookeeper must get zoo access 96, got ' + city.get_house(near_id).zookeeper)
        return false
    }
    if (city.get_house(empty_id).zookeeper != 0) {
        test691_fail('empty house must get no zoo access, got ' + city.get_house(empty_id).zookeeper)
        return false
    }
    if (city.get_house(far_id).zookeeper != 0) {
        test691_fail('house 4 tiles away must get no zoo access, got ' + city.get_house(far_id).zookeeper)
        return false
    }
    __log_marker('test691_coverage')
    return true
}

function test691_combat(bid) {
    var fid = test691_spawn(bid)
    if (!fid) {
        test691_fail('no zookeeper for the combat check')
        return false
    }
    var ct = __figure_get_tile(fid)
    var robber = __test_figure_create(FIGURE_ROBBER, ct.x, ct.y)
    if (!robber) {
        test691_fail('robber create failed')
        return false
    }
    if (__test_figure_combat_attack_at(fid, ct.x, ct.y) != 1) {
        test691_fail('armed zookeeper must attack a criminal on its tile')
        return false
    }
    if (__test_figure_get_opponent_id(fid) != robber) {
        test691_fail('zookeeper opponent must be the robber, got ' + __test_figure_get_opponent_id(fid))
        return false
    }
    __test_figure_action_perform(fid)
    if (__figure_is_valid(fid) && __figure_get_type(fid) == FIGURE_ZOOKEEPER && __figure_get_action_state(fid) != 4) {
        test691_fail('fighting zookeeper keeps its roaming state under the attack flag, state ' + __figure_get_action_state(fid))
        return false
    }
    city.figures.remove_figures(FIGURE_ROBBER)
    __log_marker('test691_combat')
    return true
}

function test691_death(bid) {
    var fid = test691_spawn(bid)
    if (!fid) {
        test691_fail('no zookeeper for the death check')
        return false
    }
    __test_figure_kill(fid)
    if (!__test_figure_is_dying(fid)) {
        test691_fail('killed zookeeper must be dying')
        return false
    }
    __test_figure_action_perform_dying(fid)
    if (__figure_get_anim_key(fid) != 'death') {
        test691_fail('dying zookeeper must use the death animation, got ' + __figure_get_anim_key(fid))
        return false
    }
    for (var t = 0; t < 1000 && __figure_is_valid(fid) && __figure_get_type(fid) == FIGURE_ZOOKEEPER; t++) {
        __test_figure_action_perform_dying(fid)
    }
    if (__figure_is_valid(fid) && __figure_get_type(fid) == FIGURE_ZOOKEEPER) {
        test691_fail('corpse must disappear')
        return false
    }
    __log_marker('test691_death')
    return true
}

function run_test() {
    __log_info_native('[test:691] zookeeper service OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var bid = test691_zoo()
    if (!bid) {
        test691_fail('zoo place failed')
        return
    }
    if (!test691_service(bid) || !test691_combat(bid) || !test691_death(bid)) {
        return
    }

    __test691_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test691_ok
        && __test_find_inlog('[test-marker] test691_coverage')
        && __test_find_inlog('[test-marker] test691_combat')
        && __test_find_inlog('[test-marker] test691_death')
}

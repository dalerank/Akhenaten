// Constable OG vs criminals: OG has no criminal search or arrest roll (the remake removed criminals within 22
// tiles at 75%). A constable is a fighting unit and fights a criminal on the tile it walks into (military.c
// category_attacks 2 -> 4); the criminal dies from the hits and the constable goes back to its walk.

var __test593_ok = false

function test593_fail(msg) {
    __log_info_native('[test:593] FAIL: ' + msg)
    __test_signal_ready()
}

function test593_tick(fid, n) {
    for (var i = 0; i < n; i++) {
        __test_figure_action_perform(fid)
    }
}

function run_test() {
    __log_info_native('[test:593] constable vs criminal OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    __test_clear_enemy_formations()
    __test_city_set_security_breach(0)

    var bid = test_building_place(BUILDING_POLICE_STATION, -1, -1)
    if (!bid) {
        test593_fail('police station place failed')
        return
    }
    var bt = __building_tile(bid)
    for (var dx = -6; dx < 7; dx++) {
        terrain.add({ x: bt.x + dx, y: bt.y + 1 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_building_set_road_access(bid, bt.x, bt.y + 1)
    __test_building_set_workers(bid, 6)
    city.get_building(bid).figure_spawn_delay = 0
    __test_building_spawn_figure(bid)
    var fid = __test_building_figure_id(bid, 0)
    if (!fid) {
        test593_fail('no constable spawned')
        return
    }

    var far = test_figure_create(FIGURE_ROBBER, bt.x + 3, bt.y + 3)
    if (!far) {
        test593_fail('robber create failed')
        return
    }
    test593_tick(fid, 200)
    if (!__test_figure_is_alive(far) || __figure_get_action_state(fid) == 76) {
        test593_fail('OG constable neither arrests nor chases a criminal nearby')
        return
    }
    __log_marker('test593_no_arrest')

    var ct = __figure_get_tile(fid)
    var robber = __test_figure_create(FIGURE_ROBBER, ct.x, ct.y)
    if (!robber) {
        test593_fail('robber on the constable tile create failed')
        return
    }
    var walk_state = __figure_get_action_state(fid)
    if (__test_figure_combat_attack_at(fid, ct.x, ct.y) != 1) {
        test593_fail('constable must fight a criminal on its tile')
        return
    }
    __log_marker('test593_fight')

    for (var t = 0; t < 500 && __test_figure_is_alive(robber); t++) {
        __test_figure_action_perform(fid)
    }
    if (__test_figure_is_alive(robber)) {
        test593_fail('robber must die from the constable hits')
        return
    }
    __test_figure_action_perform(fid)
    if (__test_figure_in_attack(fid) || __figure_get_action_state(fid) != walk_state) {
        test593_fail('constable must resume its walk after the fight, state ' + __figure_get_action_state(fid))
        return
    }
    __log_marker('test593_resume')

    __test593_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test593_ok
        && __test_find_inlog('[test-marker] test593_no_arrest')
        && __test_find_inlog('[test-marker] test593_fight')
        && __test_find_inlog('[test-marker] test593_resume')
}

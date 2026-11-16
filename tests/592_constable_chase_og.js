// Constable OG enemy chase (walkers.c constable_fight_enemy, figure_closest_enemy_for_constable, law_walker_chase):
// only during a security breach or an invasion, searched on every 10th wrap of the 12-frame walk cycle (120 ticks),
// enemy soldiers within 30 at double distance; the chase marks the target, the fight starts on contact, and once the
// target is dead the constable returns to a road near home.

var __test592_ok = false

function test592_fail(msg) {
    __log_info_native('[test:592] FAIL: ' + msg)
    __test_city_set_security_breach(0)
    __test_signal_ready()
}

function test592_tick(fid, n) {
    for (var i = 0; i < n; i++) {
        __test_figure_action_perform(fid)
    }
}

function run_test() {
    __log_info_native('[test:592] constable chase OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    __test_clear_enemy_formations()
    __test_city_set_security_breach(0)

    if (__test_figure_type_category(FIGURE_CONSTABLE) != figure_category_armed) {
        test592_fail('OG constable is a fighting unit (category 2)')
        return
    }

    var bid = test_building_place(BUILDING_POLICE_STATION, -1, -1)
    if (!bid) {
        test592_fail('police station place failed')
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
        test592_fail('no constable spawned')
        return
    }

    var enemy = test_figure_create(FIGURE_ENEMY_EGYPTIAN_SPEAR, bt.x + 6, bt.y + 1)
    if (!enemy) {
        test592_fail('enemy create failed')
        return
    }

    // Created tick resets the walk cycle; 120 more ticks = 10 wraps, no search without a breach or invasion.
    test592_tick(fid, 121)
    if (__figure_get_action_state(fid) == 76) {
        test592_fail('no chase without a security breach or enemy formations')
        return
    }
    __log_marker('test592_no_breach')

    __test_city_set_security_breach(10000)
    test592_tick(fid, 119)
    if (__figure_get_action_state(fid) == 76) {
        test592_fail('OG searches only on the 10th walk-cycle wrap, chased too early')
        return
    }
    test592_tick(fid, 1)
    if (__figure_get_action_state(fid) != 76) {
        test592_fail('constable must chase on the 10th wrap, state ' + __figure_get_action_state(fid))
        return
    }
    if (__figure_get_target_figure_id(fid) != enemy || __test_figure_targeted_by(enemy) != fid) {
        test592_fail('chase must mark the enemy as the target')
        return
    }
    __log_marker('test592_chase')

    var fought = false
    for (var t = 0; t < 1500; t++) {
        __test_figure_action_perform(fid)
        if (__test_figure_in_attack(fid)) {
            fought = true
            break
        }
    }
    if (!fought || __test_figure_get_opponent_id(fid) != enemy) {
        test592_fail('constable must fight the enemy on contact')
        return
    }
    if (__figure_get_anim_key(fid) != 'attack') {
        test592_fail('fighting constable must use the attack animation, got ' + __figure_get_anim_key(fid))
        return
    }
    __log_marker('test592_fight')

    __test_figure_set_damage(enemy, 49)
    var returning = false
    for (var t2 = 0; t2 < 2000; t2++) {
        __test_figure_action_perform(fid)
        if (__figure_get_action_state(fid) == 73) {
            returning = true
            break
        }
    }
    if (__test_figure_is_alive(enemy)) {
        test592_fail('enemy must die from the constable hits')
        return
    }
    if (!returning) {
        test592_fail('constable must return home after the target died, state ' + __figure_get_action_state(fid))
        return
    }
    __log_marker('test592_return')

    __test_city_set_security_breach(0)
    __test592_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test592_ok
        && __test_find_inlog('[test-marker] test592_no_breach')
        && __test_find_inlog('[test-marker] test592_chase')
        && __test_find_inlog('[test-marker] test592_fight')
        && __test_find_inlog('[test-marker] test592_return')
}

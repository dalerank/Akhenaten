// Magistrate OG combat (walkers.c law_walker_action with is_constable 0, Figure_model 89: fighting unit 1, 10 hit
// points, attack 0, armor 0): it never searches for or chases enemies, even during a security breach, but an enemy
// can engage it in melee; it fights with its walk sprites, dies, and its corpse disappears.

var __test602_ok = false

function test602_fail(msg) {
    __log_info_native('[test:602] FAIL: ' + msg)
    __test_city_set_security_breach(0)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:602] magistrate combat OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    __test_clear_enemy_formations()

    if (__test_figure_type_category(FIGURE_MAGISTRATE) != figure_category_citizen) {
        test602_fail('OG magistrate is fighting unit 1 (citizen)')
        return
    }
    if (figure_magistrate.max_damage != 10 || figure_magistrate.attack_value != 0 || figure_magistrate.defense_value != 0) {
        test602_fail('OG magistrate stats: 10 hit points, attack 0, armor 0')
        return
    }

    var bid = test_building_place(BUILDING_COURTHOUSE, -1, -1)
    if (!bid) {
        test602_fail('courthouse place failed')
        return
    }
    var bt = __building_tile(bid)
    for (var dx = -6; dx < 9; dx++) {
        terrain.add({ x: bt.x + dx, y: bt.y + 3 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_building_set_road_access(bid, bt.x, bt.y + 3)
    __test_building_set_workers(bid, 10)
    city.get_building(bid).figure_spawn_delay = 0
    __test_building_spawn_figure(bid)
    var fid = __test_building_figure_id(bid, 0)
    if (!fid) {
        test602_fail('no magistrate spawned')
        return
    }

    var enemy = test_figure_create(FIGURE_ENEMY_EGYPTIAN_SPEAR, bt.x + 8, bt.y + 3)
    if (!enemy) {
        test602_fail('enemy create failed')
        return
    }
    __test_city_set_security_breach(10000)
    for (var t = 0; t < 241; t++) {
        __test_figure_action_perform(fid)
        if (__figure_get_action_state(fid) == 76 || __test_figure_targeted_by(enemy) == fid) {
            test602_fail('OG magistrate never chases enemies')
            return
        }
    }
    __test_city_set_security_breach(0)
    __log_marker('test602_no_chase')

    var mt = __figure_get_tile(fid)
    enemy = test_figure_create(FIGURE_ENEMY_EGYPTIAN_SPEAR, mt.x, mt.y)
    if (enemy) {
        __test_figure_combat_attack_at(enemy, mt.x, mt.y)
    }
    if (!enemy || !__test_figure_in_attack(fid) || __test_figure_get_opponent_id(fid) != enemy) {
        test602_fail('enemy must be able to attack the magistrate')
        return
    }
    __test_figure_action_perform(fid)
    if (__figure_get_anim_key(fid) != 'attack') {
        test602_fail('fighting magistrate must use the attack animation, got ' + __figure_get_anim_key(fid))
        return
    }
    var anims = figure_magistrate.animations
    if (anims.attack.id != anims.walk.id || anims.attack.pack != anims.walk.pack) {
        test602_fail('OG magistrate fights with its walk sprites')
        return
    }
    __log_marker('test602_attacked')

    // A formation-less enemy does not run its melee; the fight ends with the kill its hit would make.
    for (var c = 0; c < 30; c++) {
        __test_figure_action_perform(fid)
    }
    if (!__test_figure_in_attack(fid)) {
        test602_fail('magistrate must stay in the fight')
        return
    }
    __test_figure_kill(fid)
    if (__test_figure_is_alive(fid) || !__test_figure_is_dying(fid)) {
        test602_fail('killed magistrate must be dying')
        return
    }
    __test_figure_action_perform_dying(fid)
    if (__figure_get_anim_key(fid) != 'death') {
        test602_fail('dead magistrate must use the death animation, got ' + __figure_get_anim_key(fid))
        return
    }
    for (var d = 0; d < 1000 && __figure_is_valid(fid) && __figure_get_type(fid) == FIGURE_MAGISTRATE; d++) {
        __test_figure_action_perform_dying(fid)
    }
    if (__figure_is_valid(fid) && __figure_get_type(fid) == FIGURE_MAGISTRATE) {
        test602_fail('corpse must disappear')
        return
    }
    __log_marker('test602_death')

    __test602_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test602_ok
        && __test_find_inlog('[test-marker] test602_no_chase')
        && __test_find_inlog('[test-marker] test602_attacked')
        && __test_find_inlog('[test-marker] test602_death')
}

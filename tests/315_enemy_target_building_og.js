// Enemy target building vs OG formation_enemy_set_target_building (formation_enemy.c:185-243): the type that comes
// first in the attack list wins regardless of distance, distance only decides between buildings of one type.
// Food list: granary, storage yard, bazaar, ... — a far granary beats a near bazaar.
// Markers:
//   [test-marker] enemy_target_list_order_ok

function test315_fail(msg) {
    __log_info_native('[test:315] FAIL: ' + msg)
}

function run_test() {
    __log_info_native('[test:315] enemy target building OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var mid_y = (__scenario_map.height / 2) | 0
    var bazaar = test_building_place(BUILDING_BAZAAR, 12, mid_y)
    var granary = test_building_place(BUILDING_GRANARY, 40, mid_y)
    if (!bazaar || !granary) {
        test315_fail('place failed bazaar=' + bazaar + ' granary=' + granary)
        __test_signal_ready()
        return
    }

    city.start_foreign_army_invasion({
        mode: ATTACK_TYPE_ENEMIES,
        enemy: ENEMY_0_BARBARIAN,
        size: 8,
        invasion_id: 1,
        tilex: 2,
        tiley: mid_y,
        want_destroy_buildings: 0,
        invasion_attack_target: EVENT_ATTACK_TARGET_FOOD
    })
    __test_run_ticks(50)
    __test_enemy_formations_update()

    var ids = __test_enemy_formations()
    var state = ids === '' ? '' : __test_enemy_formation_state(+ids.split(',')[0])
    var bid = state === '' ? -1 : +state.split(',')[2]
    if (bid == granary) {
        __log_marker('enemy_target_list_order_ok')
    } else {
        test315_fail('target ' + bid + ' want granary ' + granary + ' (bazaar ' + bazaar + ') state=' + state)
    }

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('enemy_target_list_order_ok')
}

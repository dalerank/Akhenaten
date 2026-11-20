// FIGURE_BEDOUIN in combat vs OG: an enemy soldier for the player (missiles.c:272 and walkers.c:775 count it with
// the enemy soldiers, military.c:707 gives it the enemy-soldier priority), never a missile target of another
// enemy (enemy.c:105 skips it), and a fighter that attacks a citizen it meets (formation_orders.c:337).
// Markers:
//   [test-marker] bedouin_registered_ok
//   [test-marker] bedouin_soldier_target_ok
//   [test-marker] bedouin_not_enemy_missile_target_ok
//   [test-marker] bedouin_attacks_citizen_ok

function test500_fail(msg) {
    __log_info_native('[test:500] FAIL: ' + msg)
}

function run_test() {
    __log_info_native('[test:500] OG Bedouin combat')
    test_reload_city_session('data/default.map')
    __test_clear_enemy_formations()
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    if (!__test_enemy_figure_registered(FIGURE_BEDOUIN)) {
        test500_fail('FIGURE_BEDOUIN has no enemy class')
        __test_signal_ready()
        return
    }
    __log_marker('bedouin_registered_ok')

    var bedouin = test_figure_create(FIGURE_BEDOUIN, cx, cy)
    __test_figure_set_faction(bedouin, 0)
    if (!bedouin || __test_figure_is_enemy(bedouin) != 1) {
        test500_fail('bedouin=' + bedouin + ' is_enemy=' + __test_figure_is_enemy(bedouin))
    } else if (__test_soldier_combat_target(cx + 2, cy, 8) != bedouin) {
        test500_fail('soldier target ' + __test_soldier_combat_target(cx + 2, cy, 8) + ' want ' + bedouin)
    } else {
        __log_marker('bedouin_soldier_target_ok')
    }

    var archer = test_figure_create(FIGURE_ENEMY_BARBARIAN_ARCHER, cx + 3, cy)
    __test_figure_set_faction(archer, 0)
    var target = __test_enemy_missile_target(archer, 10)
    if (!archer || target == bedouin) {
        test500_fail('enemy archer ' + archer + ' targets the bedouin')
    } else {
        __log_marker('bedouin_not_enemy_missile_target_ok')
    }

    city.figures.remove_figures(FIGURE_IMMIGRANT)
    var prey = test_figure_create(FIGURE_IMMIGRANT, cx, cy + 4)
    var raider = test_figure_create(FIGURE_BEDOUIN, cx, cy + 4)
    __test_figure_set_faction(raider, 0)
    if (raider) {
        __test_figure_combat_attack_at(raider, cx, cy + 4)
    }
    if (!prey || !raider) {
        test500_fail('attack spawn failed')
    } else if (__test_figure_get_opponent_id(raider) != prey || __test_figure_get_opponent_id(prey) != raider) {
        test500_fail('bedouin did not engage the citizen: opponent=' + __test_figure_get_opponent_id(raider)
            + ' citizen opponent=' + __test_figure_get_opponent_id(prey))
    } else {
        __log_marker('bedouin_attacks_citizen_ok')
    }

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'bedouin_registered_ok',
        'bedouin_soldier_target_ok',
        'bedouin_not_enemy_missile_target_ok',
        'bedouin_attacks_citizen_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:500] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

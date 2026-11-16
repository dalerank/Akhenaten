// Formation update cadence vs OG (tick.c): formation_update_all runs at tick 5 (with the deployed-morale check)
// and at tick 29 of every day, so an enemy formation's wait counter grows by 2 per day.
// Markers:
//   [test-marker] formation_update_twice_a_day_ok

var TICKS_PER_DAY = 50

function test313_fail(msg) {
    __log_info_native('[test:313] FAIL: ' + msg)
}

function run_test() {
    __log_info_native('[test:313] formation update twice a day')
    test_reload_city_session('data/default.map')

    var mid_y = (__scenario_map.height / 2) | 0
    city.start_foreign_army_invasion({
        mode: ATTACK_TYPE_ENEMIES,
        enemy: ENEMY_0_BARBARIAN,
        size: 8,
        invasion_id: 1,
        tilex: 2,
        tiley: mid_y,
        want_destroy_buildings: 0,
        invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
    })

    var fid = __test_first_enemy_formation()
    if (!fid) {
        test313_fail('no enemy formation')
        __test_signal_ready()
        return
    }

    var before = __test_formation_wait_ticks(fid)
    __test_run_ticks(TICKS_PER_DAY)
    var after = __test_formation_wait_ticks(fid)
    if (after - before == 2) {
        __log_marker('formation_update_twice_a_day_ok')
    } else {
        test313_fail('wait_ticks per day ' + (after - before) + ' (' + before + ' -> ' + after + '), want 2')
    }

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('formation_update_twice_a_day_ok')
}

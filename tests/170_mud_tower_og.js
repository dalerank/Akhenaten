// Mud tower OG model from Pharaoh_Model_*.txt: cost/damage by difficulty,
// laborers 6, fire 0, labor seeker threshold 51 (seek_labor limit in spawn_tower).

var __test170_ok = false

function test170_fail(msg) {
    __log_info_native('[test:170] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:170] mud tower OG')

    var expected_cost = [30, 120, 150, 180, 225]
    var expected_damage = [3, 12, 15, 18, 22]
    for (var d = 0; d < 5; d++) {
        if (building_mud_tower.cost[d] != expected_cost[d]) {
            test170_fail('cost[' + d + '] expected ' + expected_cost[d] + ' got ' + building_mud_tower.cost[d])
            return
        }
        if (building_mud_tower.damage_risk[d] != expected_damage[d]) {
            test170_fail('damage_risk[' + d + '] expected ' + expected_damage[d] + ' got ' + building_mud_tower.damage_risk[d])
            return
        }
    }
    if (building_mud_tower.laborers[0] != 6) {
        test170_fail('laborers expected 6 got ' + building_mud_tower.laborers[0])
        return
    }
    if (building_mud_tower.fire_risk[0] != 0) {
        test170_fail('fire_risk expected 0 got ' + building_mud_tower.fire_risk[0])
        return
    }
    if (building_mud_tower.min_houses_coverage != 51) {
        test170_fail('min_houses_coverage expected 51 got ' + building_mud_tower.min_houses_coverage)
        return
    }
    __log_marker('test170_og_model')

    __test170_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test170_ok && __test_find_inlog('[test-marker] test170_og_model')
}

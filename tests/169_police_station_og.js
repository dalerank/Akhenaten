// Police station OG model from Pharaoh_Model_*.txt: cost/fire by difficulty, damage_risk 0.
// Spawn delays 0/1/3/7/15 stay on figure_spawn_timer (architect/firehouse family).

var __test169_ok = false

function test169_fail(msg) {
    __log_info_native('[test:169] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:169] police station OG model')
    test_reload_city_session('data/default.map')

    var expected_cost = [6, 24, 30, 36, 45]
    var expected_fire = [2, 8, 10, 12, 15]
    for (var d = 0; d < 5; d++) {
        if (building_police_station.cost[d] != expected_cost[d]) {
            test169_fail('cost[' + d + '] expected ' + expected_cost[d] + ' got ' + building_police_station.cost[d])
            return
        }
        if (building_police_station.fire_risk[d] != expected_fire[d]) {
            test169_fail('fire_risk[' + d + '] expected ' + expected_fire[d] + ' got ' + building_police_station.fire_risk[d])
            return
        }
    }
    if (building_police_station.damage_risk[0] != 0) {
        test169_fail('damage_risk must be 0, got ' + building_police_station.damage_risk[0])
        return
    }
    if (building_police_station.laborers[0] != 6) {
        test169_fail('laborers expected 6 got ' + building_police_station.laborers[0])
        return
    }
    __log_marker('test169_og_model')

    __test169_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test169_ok
        && __test_find_inlog('[test-marker] test169_og_model')
}

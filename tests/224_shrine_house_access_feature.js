// OG: shrine does not grant house religion; remake path is behind
// gameplay_change_shrine_house_access (radius-3 shrine_access → num_gods=1).
// Markers:
//   [test-marker] test224_og_no_shrine_num_gods
//   [test-marker] test224_feature_shrine_num_gods

var __test224_ok = false
var __test224_prev = false

function test224_fail(msg) {
    game_features.set('gameplay_change_shrine_house_access', __test224_prev)
    __log_info_native('[test:224] FAIL: ' + msg)
    __test_signal_ready()
}

function test224_refresh_house(hid) {
    __test_update_religion_supply_houses()
    __test_house_calculate_culture_aggregates()
    return city.get_house(hid)
}

function run_test() {
    __log_info_native('[test:224] shrine house access feature')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_SHRINE_OSIRIS, true)

    __test224_prev = game_features.get('gameplay_change_shrine_house_access') === true

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var hid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx, cy)
    if (!hid) {
        return test224_fail('create house failed')
    }
    __test_house_set_population(hid, 5)

    var sid = __test_building_create(BUILDING_SHRINE_OSIRIS, cx + 1, cy)
    if (!sid) {
        return test224_fail('create shrine failed')
    }

    // OG default: nearby shrine must not invent num_gods.
    game_features.set('gameplay_change_shrine_house_access', false)
    var house = test224_refresh_house(hid)
    if (house.shrine_access) {
        return test224_fail('OG path should clear shrine_access')
    }
    if (house.num_gods != 0) {
        return test224_fail('OG path num_gods want 0, got ' + house.num_gods)
    }
    __log_marker('test224_og_no_shrine_num_gods')

    // Feature on: radius access + culture bump to 1 god.
    game_features.set('gameplay_change_shrine_house_access', true)
    house = test224_refresh_house(hid)
    if (!house.shrine_access) {
        return test224_fail('feature path should set shrine_access')
    }
    if (house.num_gods != 1) {
        return test224_fail('feature path num_gods want 1, got ' + house.num_gods)
    }
    __log_marker('test224_feature_shrine_num_gods')

    game_features.set('gameplay_change_shrine_house_access', __test224_prev)
    __test224_ok = true
    __log_info_native('[test:224] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test224_ok) {
        return false
    }
    return __test_find_inlog('[test-marker] test224_og_no_shrine_num_gods')
        && __test_find_inlog('[test-marker] test224_feature_shrine_num_gods')
}

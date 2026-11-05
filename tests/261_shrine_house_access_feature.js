// OG: shrine does not grant house religion; remake path is behind
// gameplay_change_shrine_house_access (radius-3 shrine_access → num_gods=1).
// Markers:
//   [test-marker] test261_og_no_shrine_num_gods
//   [test-marker] test261_feature_shrine_num_gods

var __test261_ok = false
var __test261_prev = false

function test261_fail(msg) {
    game_features.set('gameplay_change_shrine_house_access', __test261_prev)
    __log_info_native('[test:261] FAIL: ' + msg)
    __test_signal_ready()
}

function test261_refresh_house(hid) {
    __test_update_religion_supply_houses()
    __test_house_calculate_culture_aggregates()
    return city.get_house(hid)
}

function run_test() {
    __log_info_native('[test:261] shrine house access feature')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_SHRINE_OSIRIS, true)

    __test261_prev = game_features.get('gameplay_change_shrine_house_access') === true

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var hid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx, cy)
    if (!hid) {
        return test261_fail('create house failed')
    }
    __test_house_set_population(hid, 5)

    var sid = __test_building_create(BUILDING_SHRINE_OSIRIS, cx + 1, cy)
    if (!sid) {
        return test261_fail('create shrine failed')
    }

    // OG default: nearby shrine must not invent num_gods.
    game_features.set('gameplay_change_shrine_house_access', false)
    var house = test261_refresh_house(hid)
    if (house.shrine_access) {
        return test261_fail('OG path should clear shrine_access')
    }
    if (house.num_gods != 0) {
        return test261_fail('OG path num_gods want 0, got ' + house.num_gods)
    }
    __log_marker('test261_og_no_shrine_num_gods')

    // Feature on: radius access + culture bump to 1 god.
    game_features.set('gameplay_change_shrine_house_access', true)
    house = test261_refresh_house(hid)
    if (!house.shrine_access) {
        return test261_fail('feature path should set shrine_access')
    }
    if (house.num_gods != 1) {
        return test261_fail('feature path num_gods want 1, got ' + house.num_gods)
    }
    __log_marker('test261_feature_shrine_num_gods')

    game_features.set('gameplay_change_shrine_house_access', __test261_prev)
    __test261_ok = true
    __log_info_native('[test:261] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test261_ok) {
        return false
    }
    return __test_find_inlog('[test-marker] test261_og_no_shrine_num_gods')
        && __test_find_inlog('[test-marker] test261_feature_shrine_num_gods')
}

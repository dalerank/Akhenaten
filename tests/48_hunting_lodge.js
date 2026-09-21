// Hunting lodge: place on data/default.map and verify config for the
// game-meat hunting fix (#421) — max_hunters, hunter attack range/damage/delay.
//
// Markers:
//   [test-marker] test_building_placed:type_<BUILDING_HUNTING_LODGE>:...
//   [test-marker] hunting_lodge_config_ok
//   [test-marker] ostrich_hunter_config_ok

var __test48_bid = null
var __test48_ok = false

function test48_dcy_first(v) {
    if (v === undefined || v === null) {
        return null
    }
    // uint8_dcy may be a JS array (one entry per difficulty) or a scalar.
    if (typeof v === 'object' && v.length !== undefined) {
        return v[0]
    }
    return v
}

function test48_expect(cond, msg) {
    if (!cond) {
        __log_info_native('[test:48] FAIL: ' + msg)
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:48] hunting lodge placement + config')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    // --- lodge config (hunting_lodge.js) ---
    var lodge = building_hunting_lodge
    if (!lodge) {
        __log_info_native('[test:48] FAIL: building_hunting_lodge config missing')
        __test_signal_ready()
        return
    }

    var max_hunters = test48_dcy_first(lodge.max_hunters)
    var delay100 = lodge.spawn_delay && lodge.spawn_delay[0] && lodge.spawn_delay[0].delay
    if (!test48_expect(max_hunters == 3, 'max_hunters want 3, got ' + max_hunters)
        || !test48_expect(delay100 == 1, 'spawn_delay 100% want 1, got ' + delay100)) {
        __test_signal_ready()
        return
    }
    __log_marker('hunting_lodge_config_ok')

    // --- hunter combat config (figures.js) ---
    var hunter = figure_ostrich_hunter
    if (!hunter) {
        __log_info_native('[test:48] FAIL: figure_ostrich_hunter config missing')
        __test_signal_ready()
        return
    }
    if (!test48_expect(hunter.attack_distance == 5,
            'attack_distance want 5, got ' + hunter.attack_distance)
        || !test48_expect(hunter.animal_attack_value == 100,
            'animal_attack_value want 100, got ' + hunter.animal_attack_value)
        || !test48_expect(hunter.missile_delay == 25,
            'missile_delay want 25, got ' + hunter.missile_delay)) {
        __test_signal_ready()
        return
    }
    __log_marker('ostrich_hunter_config_ok')

    // --- placement ---
    var bid = test_building_place(BUILDING_HUNTING_LODGE, -1, -1)
    __test48_bid = bid
    if (!bid) {
        __log_info_native('[test:48] FAIL: test_building_place failed')
        __test_signal_ready()
        return
    }

    __test48_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!__test48_ok) {
        __log_info_native('[test:48] run_test did not complete')
        return false
    }

    if (!test_assert_building_placed(__test48_bid, BUILDING_HUNTING_LODGE, 'test:48')) {
        return false
    }

    var markers = [
        '[test-marker] hunting_lodge_config_ok',
        '[test-marker] ostrich_hunter_config_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog(markers[i])) {
            __log_info_native('[test:48] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

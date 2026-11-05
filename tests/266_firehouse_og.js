// OG Firehouse / FIGURE_FIREMAN:
//   labor seeker 101, roam 640, detect distance 25,
//   fire_risk -= service_reduction (100) under gameplay_og_fireman;
//   remake default zeros fire_risk in the service radius.
// Markers:
//   [test-marker] firehouse_og_config_ok
//   [test-marker] firehouse_og_risk_subtract_ok
//   [test-marker] firehouse_remake_zero_ok

var __test266_ok = false
var __test266_feat_prev = null

function test266_fail(msg) {
    __log_info_native('[test:266] FAIL: ' + msg)
    if (__test266_feat_prev !== null) {
        game_features.set('gameplay_og_fireman', __test266_feat_prev)
    }
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:266] firehouse OG behavior')
    test_ensure_city_session('data/default.map')

    __test266_feat_prev = game_features.get('gameplay_og_fireman')

    var cfg = building_firehouse
    if (!cfg) {
        return test266_fail('missing building_firehouse config')
    }
    if ((cfg.min_houses_coverage | 0) !== 101) {
        return test266_fail('min_houses_coverage want 101 got ' + cfg.min_houses_coverage)
    }
    if ((cfg.building_size | 0) !== 1) {
        return test266_fail('building_size want 1 got ' + cfg.building_size)
    }
    if ((cfg.laborers[0] | 0) !== 6) {
        return test266_fail('laborers want 6 got ' + cfg.laborers[0])
    }
    if ((__test_figure_type_max_roam(FIGURE_FIREMAN) | 0) !== 640) {
        return test266_fail('fireman max_roam want 640')
    }
    if ((figure_fireman.fire_detection_distance | 0) !== 25) {
        return test266_fail('fire_detection_distance want 25 got ' + figure_fireman.fire_detection_distance)
    }
    __log_marker('firehouse_og_config_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    // --- OG: absolute subtract, not zero ---
    game_features.set('gameplay_og_fireman', true)
    var hut = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx, cy)
    if (!hut) {
        return test266_fail('create hut failed')
    }
    var hut_b = city.get_building(hut)
    hut_b.fire_risk = 250
    var fireman = test_figure_create(FIGURE_FIREMAN, cx, cy)
    if (!fireman) {
        return test266_fail('create fireman for OG risk failed')
    }
    __test_figure_provide_service(fireman)
    var after = hut_b.fire_risk | 0
    var amount = (figure_fireman.risk_reduction_amount | 0) || 100
    var expect = 250 - amount
    if (expect < 0) {
        expect = 0
    }
    if (after !== expect) {
        return test266_fail('OG fire_risk want ' + expect + ' got ' + after + ' (amount=' + amount + ')')
    }
    __log_marker('firehouse_og_risk_subtract_ok')

    // --- Remake default: full clear ---
    game_features.set('gameplay_og_fireman', false)
    hut_b.fire_risk = 250
    var remake_fireman = test_figure_create(FIGURE_FIREMAN, cx, cy)
    if (!remake_fireman) {
        return test266_fail('create remake fireman failed')
    }
    __test_figure_provide_service(remake_fireman)
    if ((hut_b.fire_risk | 0) !== 0) {
        return test266_fail('remake fire_risk want 0 got ' + hut_b.fire_risk)
    }
    __log_marker('firehouse_remake_zero_ok')

    game_features.set('gameplay_og_fireman', __test266_feat_prev)
    __test266_ok = true
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'firehouse_og_config_ok',
        'firehouse_og_risk_subtract_ok',
        'firehouse_remake_zero_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:266] missing marker: ' + markers[i])
            return false
        }
    }
    return __test266_ok
}

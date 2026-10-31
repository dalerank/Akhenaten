// Enhanced: manor+ houses skipped by labor seeker when feature is on.
// Markers:
//   [test-marker] nobles_labor_flag_off_ok
//   [test-marker] nobles_labor_og_counts_ok
//   [test-marker] nobles_labor_feature_skips_ok
//   [test-marker] nobles_labor_hut_still_counts_ok

function run_test() {
    __log_info_native('[test:218] nobles dont provide labor')
    test_ensure_city_session('data/default.map')

    var prev = game_features.get('gameplay_change_nobles_dont_provide_labor')
    function finish() {
        game_features.set('gameplay_change_nobles_dont_provide_labor', prev)
        __test_signal_ready()
    }

    if (game_features.default('gameplay_change_nobles_dont_provide_labor')) {
        __log_info_native('[test:218] flag default should be OFF')
        finish()
        return
    }
    __log_marker('nobles_labor_flag_off_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var manor_id = __test_building_create(BUILDING_HOUSE_COMMON_MANOR, cx, cy)
    var hut_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx + 8, cy)
    if (!manor_id || !hut_id) {
        __log_info_native('[test:218] create failed manor=' + manor_id + ' hut=' + hut_id)
        finish()
        return
    }
    if (__test_house_set_population(manor_id, 40) < 1 || __test_house_set_population(hut_id, 20) < 1) {
        __log_info_native('[test:218] set population failed')
        finish()
        return
    }

    var home_id = __test_building_create(BUILDING_POTTERY_WORKSHOP, cx - 6, cy)
    if (!home_id) {
        __log_info_native('[test:218] home workshop create failed')
        finish()
        return
    }

    var seeker_manor = test_figure_create(FIGURE_LABOR_SEEKER, cx, cy)
    var seeker_hut = test_figure_create(FIGURE_LABOR_SEEKER, cx + 8, cy)
    if (!seeker_manor || !seeker_hut) {
        __log_info_native('[test:218] seeker create failed')
        finish()
        return
    }
    __test_figure_set_home(seeker_manor, home_id)
    __test_figure_set_home(seeker_hut, home_id)

    game_features.set('gameplay_change_nobles_dont_provide_labor', false)
    var og_manor = __test_figure_provide_service(seeker_manor)
    if (og_manor < 1) {
        __log_info_native('[test:218] OG should count manor tiles, got ' + og_manor)
        finish()
        return
    }
    __log_marker('nobles_labor_og_counts_ok')

    game_features.set('gameplay_change_nobles_dont_provide_labor', true)
    var enh_manor = __test_figure_provide_service(seeker_manor)
    if (enh_manor !== 0) {
        __log_info_native('[test:218] feature ON should skip manor, got ' + enh_manor)
        finish()
        return
    }
    __log_marker('nobles_labor_feature_skips_ok')

    var enh_hut = __test_figure_provide_service(seeker_hut)
    if (enh_hut < 1) {
        __log_info_native('[test:218] hut should still count with feature ON, got ' + enh_hut)
        finish()
        return
    }
    __log_marker('nobles_labor_hut_still_counts_ok')

    finish()
}

function check_valid() {
    return __test_find_inlog('[test-marker] nobles_labor_flag_off_ok')
        && __test_find_inlog('[test-marker] nobles_labor_og_counts_ok')
        && __test_find_inlog('[test-marker] nobles_labor_feature_skips_ok')
        && __test_find_inlog('[test-marker] nobles_labor_hut_still_counts_ok')
}

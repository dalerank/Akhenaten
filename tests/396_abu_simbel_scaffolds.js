// OG Abu Simbel built parts: stages 0..11 raise the 12 scaffolds, a scaffold's second stage lowers it.
// They are drawn only with gameplay_change_abu_simbel_draw_scaffolds, from the front record in view 0.

var t396_flag_prev = false

function t396_fail(msg) {
    __log_info_native('[test:396] FAIL: ' + msg)
    game_features.gameplay_change_abu_simbel_draw_scaffolds = t396_flag_prev
    __test_signal_ready()
}

function t396_paint_site(ox, oy) {
    for (var dy = -13; dy <= 11; dy++) {
        for (var dx = -7; dx <= 8; dx++) {
            var t = { x: ox + dx, y: oy + dy }
            terrain.remove(t, TERRAIN_NOT_CLEAR | TERRAIN_FLOODPLAIN | TERRAIN_ROCK_NEAR_MONUMENT)
            if (dx >= -5 && dx <= 3 && dy >= -11 && dy <= 9) {
                terrain.add(t, TERRAIN_ROCK | TERRAIN_ROCK_NEAR_MONUMENT)
            }
        }
    }
}

function t396_expect_raised(bid, stage, want) {
    __test_abu_simbel_set_stage(bid, stage)
    var got = __test_abu_simbel_scaffolds_raised(bid)
    if (got != want) {
        t396_fail('stage ' + stage + ': ' + got + ' scaffolds raised, want ' + want)
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:396] abu simbel scaffolds')
    t396_flag_prev = !!game_features.gameplay_change_abu_simbel_draw_scaffolds
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_ABU_SIMBEL)) {
        __scenario_building_allow(BUILDING_ABU_SIMBEL, true)
    }
    var ox = (__scenario_map.width / 2) | 0
    var oy = (__scenario_map.height / 2) | 0
    t396_paint_site(ox, oy)
    var bid = test_building_place(BUILDING_ABU_SIMBEL, ox, oy)
    if (!bid) {
        return t396_fail('place failed')
    }

    // Lowered by stages 16, 18, 20, 22, 24, 27, 32, 34, 36, 38, 40 and 45.
    var steps = [[0, 0], [6, 6], [12, 12], [16, 12], [17, 11], [38, 3], [39, 2], [45, 1], [46, 0], [56, 0]]
    for (var i = 0; i < steps.length; i++) {
        if (!t396_expect_raised(bid, steps[i][0], steps[i][1])) {
            return
        }
    }
    __log_marker('t396_raised_ok')

    __test_abu_simbel_set_stage(bid, 12)
    game_features.gameplay_change_abu_simbel_draw_scaffolds = false
    if (__test_abu_simbel_scaffold_draws(bid) != 0) {
        return t396_fail('flag off draws ' + __test_abu_simbel_scaffold_draws(bid) + ' scaffolds')
    }
    game_features.gameplay_change_abu_simbel_draw_scaffolds = true
    var draws = __test_abu_simbel_scaffold_draws(bid)
    // Without the game data the scaffold images are missing and nothing is drawn.
    if (draws != 12 && draws != 0) {
        return t396_fail('flag on draws ' + draws + ' scaffolds at stage 12')
    }
    __log_marker(draws == 12 ? 't396_draw_ok' : 't396_draw_skipped:no_resource')

    game_features.gameplay_change_abu_simbel_draw_scaffolds = t396_flag_prev
    __log_marker('t396_ok')
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] t396_raised_ok') && __test_find_inlog('[test-marker] t396_ok')
}

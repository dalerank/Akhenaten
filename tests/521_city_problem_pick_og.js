// OG figure_phrase_pick_city_problem: the random byte is masked with the sum of the weight shares (not taken
// modulo), a calm city has nothing to say (9), a pick on a calm weight is "nothing to complain" (8).
// OG window_figure_info_button_city_problem ("tell me more"): clears the current problem and moves to the last
// weight above the running best index, which is not always the heaviest problem.
// Markers:
//   [test-marker] problem_pick_mask_ok
//   [test-marker] problem_pick_nothing_ok
//   [test-marker] problem_pick_calm_ok
//   [test-marker] problem_button_walk_ok

function test521_picks(randoms) {
    var out = []
    for (var i = 0; i < randoms.length; i++) {
        out.push(__test_city_problem_pick(randoms[i]))
    }
    return out.join(',')
}

function run_test() {
    __log_info_native('[test:521] OG city problem pick and tell-me-more button')
    test_ensure_city_session('data/default.map')
    function finish() {
        __test_signal_ready()
    }

    // Weights 8,6,8,8,4,8,0,6 of 48: shares sum to 96, so only 0/32/64/96 can come up.
    __test_city_problem_weights(15, 0, 1, 0, 0, 70, 100, 25, 0, 1000, 0, 0)
    var mask = test521_picks([0, 31, 32, 64, 127])
    if (mask != '0,0,2,4,7') {
        __log_info_native('[test:521] mask picks want 0,0,2,4,7 got ' + mask)
        finish()
        return
    }
    __log_marker('problem_pick_mask_ok')

    // Weights 1,4,4,0,1,1,8,1 of 20: shares 5,20,20,0,5,5,40,5.
    __test_city_problem_weights(50, 1, 1, 1, 0, 100, 100, 50, 50, 100, 20, 50)
    var nothing = test521_picks([0, 32, 64, 127])
    if (nothing != '8,2,6,8') {
        __log_info_native('[test:521] nothing picks want 8,2,6,8 got ' + nothing)
        finish()
        return
    }
    __log_marker('problem_pick_nothing_ok')

    __test_city_problem_weights(100, 12, 0, 0, 0, 0, 0, 100, 100, 0, 0, 100)
    var calm = test521_picks([0, 64, 127])
    if (calm != '9,9,9' || __test_city_problem_other_loaded(9)) {
        __log_info_native('[test:521] calm picks want 9,9,9 got ' + calm)
        finish()
        return
    }
    __log_marker('problem_pick_calm_ok')

    __test_city_problem_weights(15, 0, 1, 0, 0, 70, 100, 25, 0, 1000, 0, 0)
    if (!__test_city_problem_other_loaded(0)) {
        __log_info_native('[test:521] crisis city must load another problem')
        finish()
        return
    }
    var walk = [0]
    for (var i = 0; i < 7; i++) {
        walk.push(__test_city_problem_next(walk[walk.length - 1]))
    }
    if (walk.join(',') != '0,7,5,4,3,2,1,1') {
        __log_info_native('[test:521] button walk want 0,7,5,4,3,2,1,1 got ' + walk.join(','))
        finish()
        return
    }
    __log_marker('problem_button_walk_ok')
    finish()
}

function check_valid() {
    return __test_find_inlog('[test-marker] problem_pick_mask_ok')
        && __test_find_inlog('[test-marker] problem_pick_nothing_ok')
        && __test_find_inlog('[test-marker] problem_pick_calm_ok')
        && __test_find_inlog('[test-marker] problem_button_walk_ok')
}

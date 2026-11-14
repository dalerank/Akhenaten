// OG figure_phrase_determine: the talkers without a phrase of their own speak about the city's problem (0..7, the
// advisor of the problem), "nothing to complain" (8) or nothing at all (9, city-life group); priests have a phrase
// per god; the advisor button opens the advisor of the phrase. The remake heuristics stay behind
// gameplay_change_walker_phrases_remake. Result format "group:phrase:file".
// Markers:
//   [test-marker] problems_calm_ok
//   [test-marker] problems_health_ok
//   [test-marker] problems_pick_ok
//   [test-marker] problems_priest_ok
//   [test-marker] problems_advisor_ok
//   [test-marker] problems_remake_flag_ok

function test523_expect(name, got, want) {
    if (got != want) {
        __log_info_native('[test:523] ' + name + ' want "' + want + '" got "' + got + '"')
        return false
    }
    return true
}

function run_test() {
    __log_info_native('[test:523] OG walker city problem phrases')
    test_ensure_city_session('data/default.map')
    var remake0 = game_features.get('gameplay_change_walker_phrases_remake') === true
    game_features.set('gameplay_change_walker_phrases_remake', false)
    __test_city_problem_calm()

    var juggler = __test_figure_create(FIGURE_JUGGLER, -1, -1)
    var physician = __test_figure_create(FIGURE_PHYSICIAN, -1, -1)
    var embalmer = __test_figure_create(FIGURE_EMBALMER, -1, -1)

    var ok = test523_expect('juggler calm', __test_figure_phrase(juggler), '13:9:juggler_g10.wav')
    ok = test523_expect('physician calm', __test_figure_phrase(physician), '13:9:doctor_g10.wav') && ok
    if (ok) {
        __log_marker('problems_calm_ok')
    }

    __test_city_problem_set('health', 30)
    ok = test523_expect('physician sick city', __test_figure_phrase(physician), '8:10:doctor_e01.wav')
    __test_city_problem_set('health', 25)
    ok = test523_expect('embalmer sick city', __test_figure_phrase(embalmer), '8:10:embalmer_e01.wav') && ok
    if (ok) {
        __log_marker('problems_health_ok')
    }

    // Only health weighs (8 of 14): the pick says the health problem, or "nothing to complain" on a calm weight.
    __test_city_problem_set('health', 15)
    var said = __test_figure_phrase(juggler)
    if (said == '8:0:juggler_g01.wav' || said == '13:8:juggler_g09.wav') {
        if (__figure_phrase_has_other_problem(juggler) == (said == '13:8:juggler_g09.wav')) {
            __log_marker('problems_pick_ok')
        } else {
            __log_info_native('[test:523] tell-me-more availability wrong after ' + said)
        }
    } else {
        __log_info_native('[test:523] juggler health pick got ' + said)
    }
    __test_city_problem_calm()

    var ra = __test_building_create(BUILDING_TEMPLE_RA, -1, -1)
    var priest = __test_figure_create(FIGURE_PRIEST, -1, -1)
    __test_figure_set_home(priest, ra)
    __test_city_problem_set('kingdom', 10)
    ok = test523_expect('ra priest low kingdom', __test_figure_phrase(priest), '5:11:priest_ra_e02.wav')
    var kingdom_advisor = __figure_phrase_advisor(priest)
    __test_city_problem_set('kingdom', 100)
    ok = test523_expect('ra priest calm', __test_figure_phrase(priest), '13:9:priest_ra_g10.wav') && ok
    if (ok) {
        __log_marker('problems_priest_ok')
    }

    __test_city_problem_set('health', 30)
    __test_figure_phrase(physician)
    var health_advisor = __figure_phrase_advisor(physician)
    __test_city_problem_calm()
    if (health_advisor == ADVISOR_HEALTH && kingdom_advisor == ADVISOR_RATINGS) {
        __log_marker('problems_advisor_ok')
    } else {
        __log_info_native('[test:523] advisors health=' + health_advisor + ' kingdom=' + kingdom_advisor)
    }

    game_features.set('gameplay_change_walker_phrases_remake', true)
    __test_figure_phrase(physician)
    var remake_advisor = __figure_phrase_advisor(physician)
    game_features.set('gameplay_change_walker_phrases_remake', remake0)
    if (remake_advisor == 0) {
        __log_marker('problems_remake_flag_ok')
    } else {
        __log_info_native('[test:523] remake flag advisor ' + remake_advisor)
    }

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] problems_calm_ok')
        && __test_find_inlog('[test-marker] problems_health_ok')
        && __test_find_inlog('[test-marker] problems_pick_ok')
        && __test_find_inlog('[test-marker] problems_priest_ok')
        && __test_find_inlog('[test-marker] problems_advisor_ok')
        && __test_find_inlog('[test-marker] problems_remake_flag_ok')
}

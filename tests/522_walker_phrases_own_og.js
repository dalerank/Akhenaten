// OG figure_phrase_determine: walkers' own phrases by their state, with the advisor group (OG advisor ids) and the
// speech file of OG phrase_names_walkers. Result format "group:phrase:file".
// Markers:
//   [test-marker] phrase_constable_ok
//   [test-marker] phrase_labor_seeker_ok
//   [test-marker] phrase_tax_collector_ok
//   [test-marker] phrase_immigrant_ok
//   [test-marker] phrase_emigrant_ok
//   [test-marker] phrase_market_trader_ok
//   [test-marker] phrase_silent_ok

function test522_expect(name, got, want) {
    if (got != want) {
        __log_info_native('[test:522] ' + name + ' want "' + want + '" got "' + got + '"')
        return false
    }
    return true
}

function test522_walker(type) {
    var fid = __test_figure_create(type, -1, -1)
    if (!fid) {
        __log_info_native('[test:522] cannot create figure type ' + type)
    }
    return fid
}

function run_test() {
    __log_info_native('[test:522] OG walker own phrases')
    test_ensure_city_session('data/default.map')
    __test_city_problem_calm()

    // Constable actions have no script names: 72 roaming. OG FIGURE_ACTION_ATTACK is our attack flag.
    var constable = test522_walker(FIGURE_CONSTABLE)
    __test_figure_set_phrase_state(constable, 72, 50)
    var ok = test522_expect('constable low crime', __test_figure_phrase(constable), '0:10:police_e01.wav')
    __test_figure_set_phrase_state(constable, 72, 150)
    ok = test522_expect('constable crime', __test_figure_phrase(constable), '13:11:police_e02.wav') && ok
    // Third call: the phrase sequence is 3, a fight says 14 + 3.
    __test_figure_set_phrase_state(constable, 72, 0)
    var ct = __figure_get_tile(constable)
    var robber = __test_figure_create(FIGURE_ROBBER, ct.x, ct.y)
    if (!robber) {
        __log_info_native('[test:522] cannot create robber')
        ok = false
    }
    if (__test_figure_combat_attack_at(constable, ct.x, ct.y) != 1) {
        __log_info_native('[test:522] constable must start a fight with a robber on its tile')
        ok = false
    }
    ok = test522_expect('constable fight', __test_figure_phrase(constable), '0:17:police_e08.wav') && ok
    if (ok) {
        __log_marker('phrase_constable_ok')
    }

    var seeker = test522_walker(FIGURE_LABOR_SEEKER)
    __test_city_problem_set('unemployment_percentage', 10)
    ok = test522_expect('seeker unemployment', __test_figure_phrase(seeker), '0:10:labor_e01.wav')
    __test_city_problem_set('unemployment_percentage', 0)
    __test_city_problem_set('workers_needed', 10)
    ok = test522_expect('seeker workers needed', __test_figure_phrase(seeker), '0:11:labor_e02.wav') && ok
    __test_city_problem_set('workers_needed', 0)
    if (ok) {
        __log_marker('phrase_labor_seeker_ok')
    }

    var taxman = test522_walker(FIGURE_TAX_COLLECTOR)
    __test_figure_set_phrase_state(taxman, ACTION_0_TAX_COLLECTOR_CREATED, 8)
    ok = test522_expect('taxman rich houses', __test_figure_phrase(taxman), '12:11:taxman_e02.wav')
    __test_figure_set_phrase_state(taxman, ACTION_0_TAX_COLLECTOR_CREATED, 1)
    ok = test522_expect('taxman some houses', __test_figure_phrase(taxman), '12:12:taxman_e03.wav') && ok
    if (ok) {
        __log_marker('phrase_tax_collector_ok')
    }

    var immigrant = test522_walker(FIGURE_IMMIGRANT)
    var seq = [__test_figure_phrase(immigrant), __test_figure_phrase(immigrant), __test_figure_phrase(immigrant)]
    if (test522_expect('immigrant sequence', seq.join(' '), '0:1:Immigrant_e02.wav 0:2:Immigrant_e03.wav 0:0:Immigrant_e01.wav')) {
        __log_marker('phrase_immigrant_ok')
    }

    var emigrant = test522_walker(FIGURE_EMIGRANT)
    __test_city_problem_set('low_mood_cause', 3)
    ok = test522_expect('emigrant taxes', __test_figure_phrase(emigrant), '12:2:Emigrant_e03.wav')
    __test_city_problem_set('low_mood_cause', 1)
    ok = test522_expect('emigrant food', __test_figure_phrase(emigrant), '1:1:Emigrant_e02.wav') && ok
    __test_city_problem_set('low_mood_cause', 0)
    ok = test522_expect('emigrant other', __test_figure_phrase(emigrant), '1:3:Emigrant_e04.wav') && ok
    if (ok) {
        __log_marker('phrase_emigrant_ok')
    }

    var trader = test522_walker(FIGURE_MARKET_TRADER)
    __test_figure_set_phrase_state(trader, ACTION_125_ROAMER_ROAMING, 0)
    ok = test522_expect('trader roaming', __test_figure_phrase(trader), '6:1:mkt_seller_e02.wav')
    __test_figure_set_phrase_state(trader, ACTION_126_ROAMER_RETURNING, 0)
    ok = test522_expect('trader returning', __test_figure_phrase(trader), '6:0:mkt_seller_e01.wav') && ok
    if (ok) {
        __log_marker('phrase_market_trader_ok')
    }

    // OG gives a protester and a docker close to its dock no phrase at all.
    var protester = test522_walker(FIGURE_PROTESTER)
    ok = test522_expect('protester', __test_figure_phrase(protester), '0:-1:')
    var docker = test522_walker(FIGURE_DOCKER)
    __test_figure_set_phrase_state(docker, ACTION_0_DOCKER_IDLING, 0)
    ok = test522_expect('docker idle', __test_figure_phrase(docker), '0:-1:') && ok
    if (ok) {
        __log_marker('phrase_silent_ok')
    }

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] phrase_constable_ok')
        && __test_find_inlog('[test-marker] phrase_labor_seeker_ok')
        && __test_find_inlog('[test-marker] phrase_tax_collector_ok')
        && __test_find_inlog('[test-marker] phrase_immigrant_ok')
        && __test_find_inlog('[test-marker] phrase_emigrant_ok')
        && __test_find_inlog('[test-marker] phrase_market_trader_ok')
        && __test_find_inlog('[test-marker] phrase_silent_ok')
}

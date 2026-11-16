// OG update_kingdom_yearly (city/ratings.c): -1 a year from the third mission on (and on custom maps), +1 when
// the tribute was paid and last year's expenses were below its income, -3/-5/-8 by unpaid tribute years; and a
// Ra temple complex adds +1 after the yearly ratings (building/temple_complex.c).
// Markers:
//   [test-marker] kingdom_yearly_profit_ok
//   [test-marker] kingdom_yearly_tribute_ok
//   [test-marker] kingdom_yearly_decay_ok
//   [test-marker] kingdom_ra_complex_ok

function kingdom_delta(setup) {
    __test_finance_last_year_set('tribute_not_paid_last_year', 0)
    __test_finance_last_year_set('tribute_not_paid_total_years', 0)
    __test_finance_last_year_set('income_total', 1000)
    __test_finance_last_year_set('expenses_total', 1000)
    setup()
    __test_kingdom_set_rating(50)
    __test_city_ratings_update(1)
    return __test_kingdom_rating() - 50
}

function run_test() {
    __log_info_native('[test:454] OG yearly kingdom favour')
    test_ensure_city_session('data/default.map')
    // The default map is open play, where the kingdom rating stays 50.
    var open_play0 = scenario.is_open_play
    scenario.is_open_play = false
    function finish() {
        scenario.is_open_play = open_play0
        __test_signal_ready()
    }
    __test_simtime_set_month(1)

    var even = kingdom_delta(function() {})
    var profit = kingdom_delta(function() {
        __test_finance_last_year_set('expenses_total', 900)
    })
    if (profit - even !== 1) {
        __log_info_native('[test:454] profit bonus want +1 got ' + (profit - even))
        finish()
        return
    }
    __log_marker('kingdom_yearly_profit_ok')

    var tribute = [0, 0, 0, 0]
    for (var years = 1; years <= 3; years++) {
        tribute[years] = kingdom_delta(function() {
            __test_finance_last_year_set('expenses_total', 900)
            __test_finance_last_year_set('tribute_not_paid_last_year', 1)
            __test_finance_last_year_set('tribute_not_paid_total_years', years)
        })
    }
    if (tribute[1] - even !== -3 || tribute[2] - even !== -5 || tribute[3] - even !== -8) {
        __log_info_native('[test:454] tribute penalties ' + (tribute[1] - even) + '/' + (tribute[2] - even) + '/' + (tribute[3] - even))
        finish()
        return
    }
    __log_marker('kingdom_yearly_tribute_ok')

    // Near zero the penalties must not wrap the 8-bit rating.
    __test_finance_last_year_set('tribute_not_paid_last_year', 1)
    __test_finance_last_year_set('tribute_not_paid_total_years', 3)
    __test_kingdom_set_rating(2)
    __test_city_ratings_update(1)
    if (__test_kingdom_rating() !== 0) {
        __log_info_native('[test:454] rating 2 - 8 want 0 got ' + __test_kingdom_rating())
        finish()
        return
    }
    __log_marker('kingdom_yearly_decay_ok')

    __test_kingdom_set_rating(50)
    __test_city_ra_yearly_favour()
    var without_ra = __test_kingdom_rating()
    var ra = __test_building_create(BUILDING_TEMPLE_COMPLEX_RA, -1, -1)
    __test_city_buildings_update_tick()
    __test_city_ra_yearly_favour()
    var with_ra = __test_kingdom_rating()
    if (!ra || without_ra !== 50 || with_ra !== 51) {
        __log_info_native('[test:454] Ra complex bid=' + ra + ' without=' + without_ra + ' with=' + with_ra)
        finish()
        return
    }
    __log_marker('kingdom_ra_complex_ok')
    finish()
}

function check_valid() {
    return __test_find_inlog('[test-marker] kingdom_yearly_profit_ok')
        && __test_find_inlog('[test-marker] kingdom_yearly_tribute_ok')
        && __test_find_inlog('[test-marker] kingdom_yearly_decay_ok')
        && __test_find_inlog('[test-marker] kingdom_ra_complex_ok')
}

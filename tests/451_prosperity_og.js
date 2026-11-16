// OG prosperity (city/ratings.c): recomputed only in months 0/3/6/9, capped by the house models' prosperity
// weighted by population, and changed by the OG terms (finances +5/-8, trade +-1, unemployment +2..-3, wages
// +2..-3, tribute -1, senet +1). The wage term reads wage_rate_paid_last_year / 12, so the yearly sum must add
// the wage rate each month, not the money paid.
// Markers:
//   [test-marker] prosperity_og_cap_ok
//   [test-marker] prosperity_og_quarterly_ok
//   [test-marker] prosperity_og_terms_ok
//   [test-marker] prosperity_og_wage_rate_ok

var PROSPERITY_FIELDS = ['taxes', 'exports', 'donated', 'gold_delivered', 'imports', 'wages', 'construction',
    'construction_this_year', 'interest', 'salary', 'tribute_not_paid_last_year', 'senet_house_plays']

function prosperity_neutral_inputs() {
    for (var i = 0; i < PROSPERITY_FIELDS.length; i++) {
        __test_finance_last_year_set(PROSPERITY_FIELDS[i], 0)
    }
    __test_finance_last_year_set('workers_needed', 0)
    __test_finance_last_year_set('unemployment_percentage', 7)
    __test_finance_last_year_set('wages_kingdome', 30)
    __test_finance_last_year_set('wage_rate_paid_last_year', 30 * 12)
}

function prosperity_change_after(setup) {
    prosperity_neutral_inputs()
    setup()
    __test_ratings_set(city.rating.culture | 0, 50, 100)
    __test_city_update_prosperity()
    return (city.rating.prosperity | 0) - 50
}

function run_test() {
    __log_info_native('[test:451] OG prosperity')
    test_ensure_city_session('data/default.map')

    var a = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    var b = __test_building_create(BUILDING_HOUSE_SPACIOUS_APARTMENT, -1, -1)
    if (!a || !b || a === b) {
        __log_info_native('[test:451] house create failed a=' + a + ' b=' + b)
        __test_signal_ready()
        return
    }
    var pop_a = __test_house_set_population(a, 5)
    var pop_b = __test_house_set_population(b, 15)
    var pa = __test_house_model_value(a, "prosperity")
    var pb = __test_house_model_value(b, "prosperity")
    // The default map has no other houses.
    var want_cap = ((pa * pop_a + pb * pop_b) / (pop_a + pop_b)) | 0
    if (pa === pb) {
        __log_info_native("[test:451] both house models have prosperity " + pa + ", the weighting is not exercised")
        __test_signal_ready()
        return
    }
    __test_simtime_set_month(1)
    __test_city_ratings_update(0)
    if ((city.rating.prosperity_max | 0) !== want_cap) {
        __log_info_native('[test:451] cap want ' + want_cap + ' got ' + city.rating.prosperity_max)
        __test_signal_ready()
        return
    }
    __log_marker('prosperity_og_cap_ok')

    var cadence = ''
    for (var m = 0; m < 12; m++) {
        __test_ratings_set(city.rating.culture | 0, 100, 100)
        __test_simtime_set_month(m)
        __test_city_ratings_update(0)
        cadence += ((city.rating.prosperity | 0) === 100) ? '-' : 'Q'
    }
    if (want_cap >= 100 || cadence !== 'Q--Q--Q--Q--') {
        __log_info_native('[test:451] quarterly cadence ' + cadence + ' cap=' + want_cap)
        __test_signal_ready()
        return
    }
    __log_marker('prosperity_og_quarterly_ok')

    var base = prosperity_change_after(function() {})
    var good = prosperity_change_after(function() {
        __test_finance_last_year_set('taxes', 1000)
        __test_finance_last_year_set('exports', 200)
        __test_finance_last_year_set('imports', 100)
        __test_finance_last_year_set('unemployment_percentage', 2)
        __test_finance_last_year_set('wage_rate_paid_last_year', 36 * 12)
        __test_finance_last_year_set('senet_house_plays', 1)
    })
    var bad = prosperity_change_after(function() {
        __test_finance_last_year_set('imports', 1000)
        __test_finance_last_year_set('exports', 100)
        __test_finance_last_year_set('unemployment_percentage', 25)
        __test_finance_last_year_set('wage_rate_paid_last_year', 19 * 12)
        __test_finance_last_year_set('tribute_not_paid_last_year', 1)
    })
    var short_staffed = prosperity_change_after(function() {
        __test_finance_last_year_set('workers_needed', 10)
    })
    // good: +5 profit, +1 trade, +2 unemployment, +2 wages, +1 senet; bad: -8 loss, -1 trade, -3, -3, -1 tribute.
    if (good - base !== 11 || bad - base !== -16 || short_staffed - base !== -1) {
        __log_info_native('[test:451] terms base=' + base + ' good=' + good + ' bad=' + bad + ' short=' + short_staffed)
        __test_signal_ready()
        return
    }
    __log_marker('prosperity_og_terms_ok')

    city.finance.wages = 33
    city.finance.wage_rate_paid_this_year = 0
    __city_finance_pay_monthly_wages()
    __city_finance_pay_monthly_wages()
    if ((city.finance.wage_rate_paid_this_year | 0) !== 66) {
        __log_info_native('[test:451] wage rate sum want 66 got ' + city.finance.wage_rate_paid_this_year)
        __test_signal_ready()
        return
    }
    __log_marker('prosperity_og_wage_rate_ok')
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] prosperity_og_cap_ok')
        && __test_find_inlog('[test-marker] prosperity_og_quarterly_ok')
        && __test_find_inlog('[test-marker] prosperity_og_terms_ok')
        && __test_find_inlog('[test-marker] prosperity_og_wage_rate_ok')
}

// OG city_migration_update (sentiment.c): the migration percentage comes from the city sentiment alone
// (>= 71: 100, >= 61: 75, >= 50: 50, >= 41: 0, >= 31: -10, >= 21: -25, else -50); unemployment reaches it only
// through the sentiment. Issue #724: sentiment 67 with 28% unemployment gave -5 and immigration stopped.
// Markers:
//   [test-marker] migration_sentiment_only_ok

var __t497_ok = false

function t497_check(sentiment, unemployment, want) {
    __test_sentiment_set(sentiment)
    __test_finance_last_year_set('unemployment_percentage', unemployment)
    var got = __test_migration_update_status()
    if (got != want) {
        __log_info_native('[test:497] FAIL: sentiment=' + sentiment + ' unemployment=' + unemployment + '% percentage=' + got + ' want ' + want)
        return false
    }
    return true
}

function run_test() {
    test_reload_city_session('data/default.map')

    var cases = [
        [67, 28, 75],
        [70, 54, 75],
        [80, 100, 100],
        [71, 0, 100],
        [61, 0, 75],
        [60, 30, 50],
        [50, 0, 50],
        [49, 0, 0],
        [41, 0, 0],
        [40, 0, -10],
        [31, 0, -10],
        [30, 0, -25],
        [21, 0, -25],
        [20, 0, -50],
        [0, 0, -50],
    ]
    var ok = true
    for (var i = 0; i < cases.length; i++) {
        ok = t497_check(cases[i][0], cases[i][1], cases[i][2]) && ok
    }
    if (ok) {
        __t497_ok = true
        __log_info_native('[test-marker] migration_sentiment_only_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return __t497_ok
}

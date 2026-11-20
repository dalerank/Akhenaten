// PF0/FN1 smoke: estimated_uncollected mirrors coverage + tax %; never negative.
// Markers:
//   [test-marker] finance_unc_nonneg_ok
//   [test-marker] finance_unc_uncovered_ok
//   [test-marker] finance_unc_covered_ok
//   [test-marker] finance_unc_taxpct_ok
//   [test-marker] finance_estimate_all_ok

function run_test() {
    __log_info_native('[test:055] prosperity/finance estimate (FN1)')
    test_reload_city_session('data/default.map')
    __test_pump_frames(2)

    var hid = test_building_place(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    if (!hid) {
        hid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, -1, -1)
    }
    if (!hid || __test_house_set_population(hid, 100) < 1) {
        __log_info_native('[test:055] house setup failed hid=' + hid)
        __test_signal_ready()
        return
    }

    var house = city.get_house(hid)
    if (!house) {
        __log_info_native('[test:055] city.get_house failed')
        __test_signal_ready()
        return
    }

    house.tax_coverage = 0
    city.finance.tax_percentage = 10
    __city_finance_update_estimate_taxes()

    var unc0 = city.taxes.estimated_uncollected | 0
    if (unc0 < 0) {
        __log_info_native('[test:055] estimated_uncollected negative: ' + unc0)
        __test_signal_ready()
        return
    }
    __log_marker('finance_unc_nonneg_ok')

    if (unc0 <= 0) {
        __log_info_native('[test:055] uncovered house should project uncollected > 0, got '
            + unc0)
        __test_signal_ready()
        return
    }
    __log_marker('finance_unc_uncovered_ok')

    house.tax_coverage = 50
    __city_finance_update_estimate_taxes()
    var unc_cov = city.taxes.estimated_uncollected | 0
    if (unc_cov < 0) {
        __log_info_native('[test:055] covered estimate negative: ' + unc_cov)
        __test_signal_ready()
        return
    }
    if (unc_cov >= unc0) {
        __log_info_native('[test:055] covering house should lower uncollected: unc0='
            + unc0 + ' unc_cov=' + unc_cov)
        __test_signal_ready()
        return
    }
    __log_marker('finance_unc_covered_ok')

    house.tax_coverage = 0
    city.finance.tax_percentage = 20
    __city_finance_update_estimate_taxes()
    var unc_hi = city.taxes.estimated_uncollected | 0
    if (unc_hi <= unc0) {
        __log_info_native('[test:055] higher tax% should raise uncollected: unc0='
            + unc0 + ' unc_hi=' + unc_hi)
        __test_signal_ready()
        return
    }
    __log_marker('finance_unc_taxpct_ok')
    __log_marker('finance_estimate_all_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'finance_unc_nonneg_ok',
        'finance_unc_uncovered_ok',
        'finance_unc_covered_ok',
        'finance_unc_taxpct_ok',
        'finance_estimate_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:055] missing marker: ' + marker)
            return false
        }
    }
    return true
}

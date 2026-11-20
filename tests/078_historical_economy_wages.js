// HE1/HE2: gameplay_enhanced_historical_economy — grain wage split.
// Markers:
//   [test-marker] he_flag_off_ok
//   [test-marker] he_off_full_treasury_ok
//   [test-marker] he_on_grain_paid_ok
//   [test-marker] he_on_treasury_saved_ok
//   [test-marker] he_empty_granary_fallback_ok
//   [test-marker] he_all_ok

function run_test() {
    __log_info_native('[test:078] historical economy grain wages')
    test_ensure_city_session('data/default.map')

    var he_prev = game_features.get('gameplay_enhanced_historical_economy')
    if (game_features.default('gameplay_enhanced_historical_economy')) {
        __log_info_native('[test:078] historical economy flag default should be OFF')
        __test_signal_ready()
        return
    }
    __log_marker('he_flag_off_ok')

    function finish() {
        game_features.set('gameplay_enhanced_historical_economy', he_prev)
        __test_signal_ready()
    }

    var granary = __test_building_create(BUILDING_GRANARY, -1, -1)
    if (!granary) {
        __log_info_native('[test:078] granary create failed')
        finish()
        return
    }

    // wages=30, workers=2000 → monthly = 30*2000/10/12 = 500
    city.finance.wages = 30
    city.labor.workers_employed = 2000
    var monthly = (city.finance.wages * city.labor.workers_employed / 10 / 12) | 0
    if (monthly < 100) {
        __log_info_native('[test:078] monthly wages too small: ' + monthly)
        finish()
        return
    }

    function prep_pay(grain_amount) {
        __test_set_treasury(100000)
        city.finance.wages_so_far = 0
        city.finance.wages_grain_deben_so_far = 0
        city.finance.wage_rate_paid_this_year = 0
        if (!__test_granary_set_resource(granary, RESOURCE_GRAIN, grain_amount)) {
            return false
        }
        return true
    }

    // OFF: full treasury drain, grain untouched
    game_features.set('gameplay_enhanced_historical_economy', false)
    if (!prep_pay(400)) {
        __log_info_native('[test:078] prep OFF failed')
        finish()
        return
    }
    var grain_before = __granary_get_amount(granary, RESOURCE_GRAIN)
    var treas_before = city.finance.treasury | 0
    __city_finance_pay_monthly_wages()
    var drain_off = treas_before - (city.finance.treasury | 0)
    var grain_off = __granary_get_amount(granary, RESOURCE_GRAIN)
    var grain_deben_off = city.finance.wages_grain_deben_so_far | 0
    if (drain_off != monthly || grain_off != grain_before || grain_deben_off != 0) {
        __log_info_native('[test:078] OFF path mismatch monthly=' + monthly
            + ' drain=' + drain_off
            + ' grain ' + grain_before + '→' + grain_off
            + ' grain_deben=' + grain_deben_off)
        finish()
        return
    }
    __log_marker('he_off_full_treasury_ok')

    // ON + stocked granary
    game_features.set('gameplay_enhanced_historical_economy', true)
    if (!prep_pay(400)) {
        __log_info_native('[test:078] prep ON failed')
        finish()
        return
    }
    grain_before = __granary_get_amount(granary, RESOURCE_GRAIN)
    treas_before = city.finance.treasury | 0
    __city_finance_pay_monthly_wages()
    var drain_on = treas_before - (city.finance.treasury | 0)
    var grain_on = __granary_get_amount(granary, RESOURCE_GRAIN)
    var grain_deben = city.finance.wages_grain_deben_so_far | 0
    var wages_so_far = city.finance.wages_so_far | 0

    if (grain_deben <= 0 || grain_on >= grain_before) {
        __log_info_native('[test:078] ON should pay some grain: deben=' + grain_deben
            + ' grain ' + grain_before + '→' + grain_on)
        finish()
        return
    }
    __log_marker('he_on_grain_paid_ok')

    if (drain_on >= monthly || (drain_on + grain_deben) != monthly || wages_so_far != monthly) {
        __log_info_native('[test:078] ON treasury/accounting mismatch monthly=' + monthly
            + ' drain=' + drain_on + ' grain_deben=' + grain_deben
            + ' wages_so_far=' + wages_so_far)
        finish()
        return
    }
    __log_marker('he_on_treasury_saved_ok')

    // Empty granary → full treasury fallback
    if (!prep_pay(0)) {
        __log_info_native('[test:078] prep empty failed')
        finish()
        return
    }
    treas_before = city.finance.treasury | 0
    __city_finance_pay_monthly_wages()
    var drain_empty = treas_before - (city.finance.treasury | 0)
    var grain_deben_empty = city.finance.wages_grain_deben_so_far | 0
    if (drain_empty != monthly || grain_deben_empty != 0) {
        __log_info_native('[test:078] empty fallback want drain=' + monthly
            + ' got ' + drain_empty + ' grain_deben=' + grain_deben_empty)
        finish()
        return
    }
    __log_marker('he_empty_granary_fallback_ok')
    __log_marker('he_all_ok')
    finish()
}

function check_valid() {
    var markers = [
        'he_flag_off_ok',
        'he_off_full_treasury_ok',
        'he_on_grain_paid_ok',
        'he_on_treasury_saved_ok',
        'he_empty_granary_fallback_ok',
        'he_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:078] missing marker: ' + marker)
            return false
        }
    }
    return true
}

// WR1 / WR4: fixed worker ratio — % of plebs via gameplay_fixed_worker_percent.
// Markers:
//   [test-marker] fixed_workers_calc_ok
//   [test-marker] fixed_workers_on_pool_ok
//   [test-marker] fixed_workers_advisor_pct_ok
//   [test-marker] fixed_workers_percent_feature_ok
//   [test-marker] fixed_workers_advisor_not_38_ok
//   [test-marker] fixed_workers_age_skew_ok

function fixed_workers_snapshot_ages() {
    var snap = []
    for (var i = 0; i < 100; i++) {
        snap.push(city.population_stats.at_age(i))
    }
    return snap
}

function fixed_workers_restore_ages(snap) {
    for (var i = 0; i < 100; i++) {
        city.population_stats.set_at_age(i, snap[i])
    }
}

function fixed_workers_clear_ages() {
    for (var i = 0; i < 100; i++) {
        city.population_stats.set_at_age(i, 0)
    }
}

function fixed_workers_fill_ages(lo, hi, per_age) {
    for (var i = lo; i < hi; i++) {
        city.population_stats.set_at_age(i, per_age)
    }
}

function run_test() {
    __log_info_native('[test:482] fixed workers ratio')
    test_ensure_city_session('data/default.map')

    var ages_snap = fixed_workers_snapshot_ages()
    var flags_fixed = game_features.get('gameplay_change_fixed_workers')
    var flags_pct = game_features.get('gameplay_fixed_worker_percent')

    function done() {
        fixed_workers_restore_ages(ages_snap)
        game_features.set('gameplay_fixed_worker_percent', flags_pct)
        game_features.set('gameplay_change_fixed_workers', flags_fixed)
        __test_signal_ready()
    }

    game_features.set('gameplay_change_fixed_workers', true)
    game_features.set('gameplay_fixed_worker_percent', 38)

    var calc = city.labor.calc_fixed_workers_available(1000)
    if (calc != 380) {
        __log_info_native('[test:482] calc want 380 got ' + calc)
        done()
        return
    }
    __log_marker('fixed_workers_calc_ok')

    city.labor.calculate_workers(1000, 250)
    var avail = city.labor.workers_available
    if (avail != 380) {
        __log_info_native('[test:482] pool want 380 got ' + avail)
        done()
        return
    }
    __log_marker('fixed_workers_on_pool_ok')

    // Advisor must use workers_available / total — never hardcode 38.
    if (typeof advisor_population_percent_in_workforce_value !== 'function') {
        __log_info_native('[test:482] advisor helper missing')
        done()
        return
    }
    var cur = city.population_stats.current
    if (!cur) {
        var pct_empty = advisor_population_percent_in_workforce_value()
        if (pct_empty != 0) {
            __log_info_native('[test:482] advisor empty want 0 got ' + pct_empty)
            done()
            return
        }
        __log_marker('fixed_workers_advisor_pct_ok')
        // Empty city → 0% of total (already ≠ feature percent 38).
        __log_marker('fixed_workers_advisor_not_38_ok')
    } else {
        var pct = advisor_population_percent_in_workforce_value()
        var expect = (100 * avail / cur) | 0
        if (pct != expect) {
            __log_info_native('[test:482] advisor want ' + expect + ' got ' + pct
                + ' (avail=' + avail + ' cur=' + cur + ')')
            done()
            return
        }
        __log_marker('fixed_workers_advisor_pct_ok')
        // Mixed plebs/patricians: % of total must not falsely read as feature percent.
        if (pct == 38) {
            __log_info_native('[test:482] advisor pct unexpectedly 38 of total'
                + ' (avail=' + avail + ' cur=' + cur + ')')
            done()
            return
        }
        __log_marker('fixed_workers_advisor_not_38_ok')
    }

    game_features.set('gameplay_fixed_worker_percent', 40)
    calc = city.labor.calc_fixed_workers_available(1000)
    city.labor.calculate_workers(1000, 0)
    if (calc != 400 || city.labor.workers_available != 400) {
        __log_info_native('[test:482] percent feature want 400 got calc='
            + calc + ' avail=' + city.labor.workers_available)
        done()
        return
    }
    __log_marker('fixed_workers_percent_feature_ok')

    // Age skew: fixed ON stable; OFF differs young vs working-age census.
    game_features.set('gameplay_fixed_worker_percent', 38)
    game_features.set('gameplay_change_fixed_workers', true)
    fixed_workers_clear_ages()
    fixed_workers_fill_ages(0, 20, 50) // children only
    city.labor.calculate_workers(1000, 0)
    var fixed_young = city.labor.workers_available

    fixed_workers_clear_ages()
    fixed_workers_fill_ages(20, 50, 50) // working ages 20–49
    city.labor.calculate_workers(1000, 0)
    var fixed_working = city.labor.workers_available
    if (fixed_young != 380 || fixed_working != 380) {
        __log_info_native('[test:482] fixed age-invariant want 380 got young='
            + fixed_young + ' working=' + fixed_working)
        done()
        return
    }

    game_features.set('gameplay_change_fixed_workers', false)
    fixed_workers_clear_ages()
    fixed_workers_fill_ages(0, 20, 50)
    city.labor.calculate_workers(1000, 0)
    var off_young = city.labor.workers_available

    fixed_workers_clear_ages()
    fixed_workers_fill_ages(20, 50, 50)
    city.labor.calculate_workers(1000, 0)
    var off_working = city.labor.workers_available
    if (off_young == off_working) {
        __log_info_native('[test:482] OFF age-skew expected differ young='
            + off_young + ' working=' + off_working)
        done()
        return
    }
    __log_marker('fixed_workers_age_skew_ok')

    done()
}

function check_valid() {
    var markers = [
        'fixed_workers_calc_ok',
        'fixed_workers_on_pool_ok',
        'fixed_workers_advisor_pct_ok',
        'fixed_workers_advisor_not_38_ok',
        'fixed_workers_percent_feature_ok',
        'fixed_workers_age_skew_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:482] missing marker: ' + marker)
            return false
        }
    }
    return true
}

run_test()

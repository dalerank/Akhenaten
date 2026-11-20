// RT4 per-tomb burial ledger: steal from destination tomb stock only;
// second tomb's goods stay put.

var ACTION_TOMB_ROBBER_CREATED = 120
var ACTION_TOMB_ROBBER_CAUGHT = 124

function place_finished_mastaba_near(preferred) {
    if (!__scenario_building_allowed(BUILDING_SMALL_MASTABA)) {
        __scenario_building_allow(BUILDING_SMALL_MASTABA, true)
    }
    var candidates = preferred.concat([
        {x: 40, y: 40}, {x: 60, y: 40}, {x: 40, y: 60}, {x: 20, y: 20}, {x: 70, y: 70}
    ])
    var bid = 0
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_MASTABA, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_SMALL_MASTABA, -1, -1)
    }
    if (!bid) {
        return 0
    }
    __test_monument_set_phase(bid, 8)
    var ph = __test_monument_phase(bid)
    if (ph != -1 && ph != 255) {
        return 0
    }
    return bid
}

function kill_tomb_robbers() {
    for (var i = 1; i < 2000; i++) {
        if (__figure_is_valid(i) && __figure_get_type(i) == FIGURE_TOMB_ROBER) {
            __test_figure_set_action(i, ACTION_TOMB_ROBBER_CAUGHT)
            __test_figure_action_perform(i)
        }
    }
}

function run_test() {
    __log_info_native('[test:083] burial tomb ledger isolation')
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    __test_burial_provisions_clear()
    __test_sentiment_set(10)

    // Finish first before placing second — unfinished mastaba is unique.
    var a = place_finished_mastaba_near([{x: 30, y: 30}, {x: 35, y: 35}])
    var b = place_finished_mastaba_near([{x: 55, y: 55}, {x: 60, y: 50}])
    if (!a || !b || a == b) {
        __log_info_native('[test:083] place finished mastabas failed a=' + a + ' b=' + b)
        __test_signal_ready()
        return
    }
    __log_marker('ledger_tombs_ok:' + a + ',' + b)

    if (!__test_burial_provisions_set(RESOURCE_LINEN, 8)) {
        __log_info_native('[test:083] burial set failed')
        __test_signal_ready()
        return
    }

    // Deposit uneven stock — city dispatched tracks sum.
    if (__test_monument_add_burial_stock(a, RESOURCE_LINEN, 3) != 3) {
        __log_info_native('[test:083] add stock A failed')
        __test_signal_ready()
        return
    }
    if (__test_monument_add_burial_stock(b, RESOURCE_LINEN, 1) != 1) {
        __log_info_native('[test:083] add stock B failed')
        __test_signal_ready()
        return
    }
    if (__scenario_burial_provisions_dispatched(RESOURCE_LINEN) != 4) {
        __log_info_native('[test:083] city dispatched want 4 got '
            + __scenario_burial_provisions_dispatched(RESOURCE_LINEN))
        __test_signal_ready()
        return
    }
    __log_marker('ledger_stock_ok')

    kill_tomb_robbers()
    var fid = __test_tomb_robber_try_spawn(1)
    if (!fid) {
        __log_info_native('[test:083] try_spawn failed')
        __test_signal_ready()
        return
    }
    // CREATED sets target_tomb_id (needed for ledger steal).
    __test_figure_set_action(fid, ACTION_TOMB_ROBBER_CREATED)
    __test_figure_action_perform(fid)

    // Nearest-with-stock from map entry — whichever is chosen loses 1; the other stays.
    var stock_a_before = __test_monument_burial_stock(a, RESOURCE_LINEN)
    var stock_b_before = __test_monument_burial_stock(b, RESOURCE_LINEN)
    if (!__test_tomb_robber_commit_plunder(fid)) {
        __log_info_native('[test:083] commit_plunder failed')
        __test_signal_ready()
        return
    }

    var stock_a = __test_monument_burial_stock(a, RESOURCE_LINEN)
    var stock_b = __test_monument_burial_stock(b, RESOURCE_LINEN)
    var city = __scenario_burial_provisions_dispatched(RESOURCE_LINEN)

    if (city != 3) {
        __log_info_native('[test:083] city dispatched want 3 got ' + city)
        __test_signal_ready()
        return
    }
    if (stock_a + stock_b != 3) {
        __log_info_native('[test:083] tomb stocks sum want 3 got a=' + stock_a + ' b=' + stock_b)
        __test_signal_ready()
        return
    }
    // Exactly one tomb lost one load; the other unchanged.
    var lost_a = stock_a_before - stock_a
    var lost_b = stock_b_before - stock_b
    if (!((lost_a == 1 && lost_b == 0) || (lost_a == 0 && lost_b == 1))) {
        __log_info_native('[test:083] expected one tomb -1 got da=' + lost_a + ' db=' + lost_b)
        __test_signal_ready()
        return
    }
    __log_marker('ledger_steal_isolated_ok')
    __log_marker('ledger_all_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'ledger_tombs_ok',
        'ledger_stock_ok',
        'ledger_steal_isolated_ok',
        'ledger_all_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])
            && !__test_find_inlog(markers[i])) {
            __log_info_native('[test:083] missing marker ' + markers[i])
            return false
        }
    }
    return true
}

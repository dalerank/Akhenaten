// OG trade caravan: fixed capacity 800 under gameplay_og_trader.
// Markers:
//   [test-marker] caravan_og_capacity_fixed_ok
//   [test-marker] caravan_remake_capacity_roll_ok

var __test202_og_ok = false
var __test202_remake_ok = false

function test202_spawn_caravan() {
    return test_figure_create(FIGURE_TRADE_CARAVAN)
}

function run_test() {
    __log_info_native('[test:202] caravan og trade capacity')
    test_reload_city_session('data/default.map')

    game_features.set('gameplay_change_trader_capacity_1600', false)
    game_features.set('gameplay_og_trader', true)

    city.figures.remove_figures(FIGURE_TRADE_CARAVAN)
    var i
    var bad = 0
    for (i = 0; i < 80; i++) {
        var fid = test202_spawn_caravan()
        var cap = __test_trader_capacity(fid)
        if (cap != 800) {
            bad++
            __log_info_native('[test:202] OG want capacity 800 got ' + cap)
            break
        }
    }
    city.figures.remove_figures(FIGURE_TRADE_CARAVAN)
    if (bad) {
        game_features.set('gameplay_og_trader', false)
        __test_signal_ready()
        return
    }
    __log_marker('caravan_og_capacity_fixed_ok')
    __test202_og_ok = true

    game_features.set('gameplay_og_trader', false)
    var max_seen = 0
    var min_seen = 9999
    var batch
    for (batch = 0; batch < 100; batch++) {
        for (i = 0; i < 50; i++) {
            fid = test202_spawn_caravan()
            cap = __test_trader_capacity(fid)
            if (cap < 0) { continue }
            if (cap > max_seen) { max_seen = cap }
            if (cap < min_seen) { min_seen = cap }
        }
        city.figures.remove_figures(FIGURE_TRADE_CARAVAN)
        if (max_seen == 800 && min_seen < 800) {
            break
        }
    }
    if (min_seen < 100 || max_seen != 800 || min_seen >= 800) {
        __log_info_native('[test:202] remake roll want min in [100,800) max==800 got min='
            + min_seen + ' max=' + max_seen)
        __test_signal_ready()
        return
    }
    __log_marker('caravan_remake_capacity_roll_ok')
    __test202_remake_ok = true

    __test_signal_ready()
}

function check_valid() {
    if (!__test202_og_ok) {
        __log_info_native('[test:202] OG fixed capacity check failed')
        return false
    }
    if (!__test202_remake_ok) {
        __log_info_native('[test:202] remake capacity roll check failed')
        return false
    }
    return true
}

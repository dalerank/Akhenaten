// TC1a–e / TC4a: trader trip capacity restoration + flag 1600.
// Markers:
//   [test-marker] trader_capacity_params_ok
//   [test-marker] trader_capacity_off_roll_ok
//   [test-marker] trader_capacity_on_ok
//   [test-marker] trader_capacity_buy_gate_ok
//   [test-marker] trader_capacity_has_traded_max_ok

var __test466_params_ok = false
var __test466_off_ok = false
var __test466_on_ok = false
var __test466_buy_ok = false
var __test466_htm_ok = false

function test466_spawn_caravan() {
    return test_figure_create(FIGURE_TRADE_CARAVAN)
}

function run_test() {
    __log_info_native('[test:466] trader capacity 800/1600')
    test_reload_city_session('data/default.map')

    game_features.set('gameplay_change_trader_capacity_1600', false)

    var params_max = __test_trader_static_max_capacity(FIGURE_TRADE_CARAVAN)
    var params_rand = __test_trader_static_capacity_random(FIGURE_TRADE_CARAVAN)
    var ship_max = __test_trader_static_max_capacity(FIGURE_TRADE_SHIP)
    if (params_max != 800 || params_rand != 701 || ship_max != 1200) {
        __log_info_native('[test:466] params want caravan 800/701 ship 1200 got '
            + params_max + '/' + params_rand + ' ship=' + ship_max)
        __test_signal_ready()
        return
    }
    __log_marker('trader_capacity_params_ok')
    __test466_params_ok = true

    city.figures.remove_figures(FIGURE_TRADE_CARAVAN)
    var max_seen = 0
    var min_seen = 9999
    var i
    var batch
    for (batch = 0; batch < 100; batch++) {
        for (i = 0; i < 50; i++) {
            var fid = test466_spawn_caravan()
            var cap = __test_trader_capacity(fid)
            if (cap < 0) { continue }
            if (cap > max_seen) { max_seen = cap }
            if (cap < min_seen) { min_seen = cap }
        }
        city.figures.remove_figures(FIGURE_TRADE_CARAVAN)
        if (max_seen == 800) {
            break
        }
    }
    if (min_seen < 100 || max_seen != 800) {
        __log_info_native('[test:466] OFF roll want max==800 min>=100 got min='
            + min_seen + ' max=' + max_seen)
        __test_signal_ready()
        return
    }
    __log_marker('trader_capacity_off_roll_ok')
    __test466_off_ok = true

    game_features.set('gameplay_change_trader_capacity_1600', true)
    city.figures.remove_figures(FIGURE_TRADE_CARAVAN)
    city.figures.remove_figures(FIGURE_TRADE_SHIP)
    // Ship first — caravan spam can exhaust the figure pool.
    var ship = 0
    for (i = 0; i < 30 && !ship; i++) {
        ship = test_figure_create(FIGURE_TRADE_SHIP)
    }
    var ship_cap = __test_trader_capacity(ship)
    game_features.set('gameplay_change_trader_capacity_1600', false)
    var ship_cap_after = __test_trader_capacity(ship)
    game_features.set('gameplay_change_trader_capacity_1600', true)

    max_seen = 0
    min_seen = 9999
    for (batch = 0; batch < 80; batch++) {
        for (i = 0; i < 50; i++) {
            fid = test466_spawn_caravan()
            cap = __test_trader_capacity(fid)
            if (cap < 0) { continue }
            if (cap > max_seen) { max_seen = cap }
            if (cap < min_seen) { min_seen = cap }
        }
        city.figures.remove_figures(FIGURE_TRADE_CARAVAN)
        if (max_seen >= 1500) {
            break
        }
    }
    // Flag expands the roll ceiling; require a near-top sample (exact 1600 is a 1/1501 lottery).
    if (min_seen < 100 || max_seen < 1500 || ship_cap != 1600 || ship_cap_after != 1600) {
        __log_info_native('[test:466] ON want caravan max>=1500 ship==1600 snap got min='
            + min_seen + ' max=' + max_seen + ' ship=' + ship_cap + ' after_off=' + ship_cap_after)
        game_features.set('gameplay_change_trader_capacity_1600', false)
        __test_signal_ready()
        return
    }
    __log_marker('trader_capacity_on_ok')
    __test466_on_ok = true

    // Buy gate uses runtime capacity (flag still ON; roll may be < 700).
    city.figures.remove_figures(FIGURE_TRADE_CARAVAN)
    fid = test466_spawn_caravan()
    cap = __test_trader_capacity(fid)
    var buy_ok_at = (cap > 100) ? Math.min(700, cap - 100) : 0
    __test_trader_set_bought(fid, buy_ok_at)
    if (__test_trader_buy_under_capacity(fid) != 1) {
        __log_info_native('[test:466] buy gate should allow at bought=' + buy_ok_at + ' capacity=' + cap)
        game_features.set('gameplay_change_trader_capacity_1600', false)
        __test_signal_ready()
        return
    }
    __test_trader_set_bought(fid, cap)
    if (__test_trader_buy_under_capacity(fid) != 0) {
        __log_info_native('[test:466] buy gate should block at bought>=capacity=' + cap)
        game_features.set('gameplay_change_trader_capacity_1600', false)
        __test_signal_ready()
        return
    }
    __log_marker('trader_capacity_buy_gate_ok')
    __test466_buy_ok = true

    if (__test_empire_trader_has_traded_max(1200, 0, 1600) != 0) {
        __log_info_native('[test:466] has_traded_max(1600) should be false at bought=1200')
        game_features.set('gameplay_change_trader_capacity_1600', false)
        __test_signal_ready()
        return
    }
    if (__test_empire_trader_has_traded_max(1600, 0, 1600) != 1) {
        __log_info_native('[test:466] has_traded_max(1600) should be true at bought=1600')
        game_features.set('gameplay_change_trader_capacity_1600', false)
        __test_signal_ready()
        return
    }
    if (__test_empire_trader_has_traded_max(0, 1200, 1200) != 1) {
        __log_info_native('[test:466] has_traded_max(1200) should be true at sold=1200')
        game_features.set('gameplay_change_trader_capacity_1600', false)
        __test_signal_ready()
        return
    }
    __log_marker('trader_capacity_has_traded_max_ok')
    __test466_htm_ok = true

    game_features.set('gameplay_change_trader_capacity_1600', false)
    city.figures.remove_figures(FIGURE_TRADE_CARAVAN)
    city.figures.remove_figures(FIGURE_TRADE_SHIP)
    __test_signal_ready()
}

function check_valid() {
    if (!__test466_params_ok) {
        __log_info_native('[test:466] params check failed')
        return false
    }
    if (!__test466_off_ok) {
        __log_info_native('[test:466] OFF roll check failed')
        return false
    }
    if (!__test466_on_ok) {
        __log_info_native('[test:466] ON capacity check failed')
        return false
    }
    if (!__test466_buy_ok) {
        __log_info_native('[test:466] buy gate check failed')
        return false
    }
    if (!__test466_htm_ok) {
        __log_info_native('[test:466] has_traded_max check failed')
        return false
    }
    return true
}

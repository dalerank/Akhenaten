// OG: desirability > fancy threshold → second FIGURE_MARKET_TRADER (not a building slot).
// Markers:
//   [test-marker] bazaar_fancy_trader_threshold_ok
//   [test-marker] bazaar_fancy_trader_low_desir_one_ok
//   [test-marker] bazaar_fancy_trader_high_desir_two_ok

var __test239_ok = {
    threshold: false,
    low: false,
    high: false
}

function run_test() {
    __log_info_native('[test:239] bazaar fancy second trader')
    test_ensure_city_session('data/default.map')

    var bid = __test_building_create(BUILDING_BAZAAR, -1, -1)
    if (!bid) {
        __log_info_native('[test:239] create bazaar failed')
        __test_signal_ready()
        return
    }

    var bazaar = city.get_building(bid)
    var t = __building_tile(bid)
    terrain.add({ x: t.x, y: t.y - 1 }, TERRAIN_ROAD)
    __test_update_road_network()
    bazaar.has_road_access = true
    bazaar.road_access = { x: t.x, y: t.y - 1 }
    bazaar.num_workers = 5
    bazaar.road_network_id = 1
    bazaar.distance_from_entry = 10

    var thr = __test_bazaar_fancy_threshold(bid)
    if (thr < 0) {
        __log_info_native('[test:239] missing fancy threshold')
        __test_signal_ready()
        return
    }
    __log_marker('bazaar_fancy_trader_threshold_ok')
    __test239_ok.threshold = true

    // Stock so traders may leave; no linked storage → buyers stay home.
    __test_bazaar_set_inventory(bid, 0, 200)
    __test_bazaar_set_inventory(bid, 4, 50)

    __test_set_desirability(t.x, t.y, thr)
    var i
    for (i = 0; i < 12; i++) {
        __test_bazaar_force_spawn(bid)
    }
    var traders_low = __test_bazaar_count_traders(bid)
    var second_low = __test_bazaar_second_trader_id(bid)
    if (traders_low > 1 || second_low != 0) {
        __log_info_native('[test:239] low desir expected <=1 trader / no second, got '
            + traders_low + ' second=' + second_low)
        __test_signal_ready()
        return
    }
    __log_marker('bazaar_fancy_trader_low_desir_one_ok')
    __test239_ok.low = true

    __test_set_desirability(t.x, t.y, thr + 1)
    for (i = 0; i < 12; i++) {
        __test_bazaar_force_spawn(bid)
    }
    var traders_high = __test_bazaar_count_traders(bid)
    var second_high = __test_bazaar_second_trader_id(bid)
    if (traders_high < 2 || second_high <= 0) {
        __log_info_native('[test:239] high desir expected 2 traders + second id, got '
            + traders_high + ' second=' + second_high)
        __test_signal_ready()
        return
    }
    __log_marker('bazaar_fancy_trader_high_desir_two_ok')
    __test239_ok.high = true

    __test_signal_ready()
}

function check_valid() {
    return __test239_ok.threshold
        && __test239_ok.low
        && __test239_ok.high
        && __test_find_inlog('[test-marker] bazaar_fancy_trader_threshold_ok')
        && __test_find_inlog('[test-marker] bazaar_fancy_trader_low_desir_one_ok')
        && __test_find_inlog('[test-marker] bazaar_fancy_trader_high_desir_two_ok')
}

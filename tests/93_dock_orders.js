// DO4: Dock per-good orders — any-match, accept-none, overlap score.
//
// Markers:
//   [test-marker] dock_orders_any_match_ok
//   [test-marker] dock_orders_none_ok
//   [test-marker] dock_orders_restore_ok
//   [test-marker] dock_orders_score_ok
//   [test-marker] dock_orders_accept_all_ok
//   [test-marker] dock_orders_weight_ok
//   [test-marker] dock_orders_ship_ok

function run_test() {
    __log_info_native('[test:93] dock orders any-match')

    test_ensure_city_session('data/default.map')
    __test_set_treasury(500000)

    if (!__scenario_building_allowed(BUILDING_DOCK)) {
        __scenario_building_allow(BUILDING_DOCK, true)
    }

    var bid = __test_building_create(BUILDING_DOCK, -1, -1)
    if (!bid) {
        __log_info_native('[test:93] dock create failed')
        __test_signal_ready()
        return
    }

    var dock = city.get_dock(bid)
    if (!dock) {
        __log_info_native('[test:93] get_dock failed')
        __test_signal_ready()
        return
    }

    // Fresh dock = accept all → matches pottery+beer
    if (!__test_dock_any_match(bid, RESOURCE_POTTERY, RESOURCE_BEER, 0)) {
        __log_info_native('[test:93] accept-all should match partner goods')
        __test_signal_ready()
        return
    }
    if (__test_dock_match_score(bid, RESOURCE_POTTERY, RESOURCE_BEER, 0) !== 2) {
        __log_info_native('[test:93] accept-all score expected 2, got ' + __test_dock_match_score(bid, RESOURCE_POTTERY, RESOURCE_BEER, 0))
        __test_signal_ready()
        return
    }
    __log_marker('dock_orders_accept_all_ok')

    dock.unaccept_all_goods()
    if (dock.accepts_any_goods()) {
        __log_info_native('[test:93] accept-none should clear accepts_any_goods')
        __test_signal_ready()
        return
    }
    if (__test_dock_any_match(bid, RESOURCE_POTTERY, RESOURCE_BEER, 0)) {
        __log_info_native('[test:93] accept-none should reject ships')
        __test_signal_ready()
        return
    }
    if (__test_dock_match_score(bid, RESOURCE_POTTERY, RESOURCE_BEER, 0) !== 0) {
        __log_info_native('[test:93] accept-none score expected 0')
        __test_signal_ready()
        return
    }
    __log_marker('dock_orders_none_ok')

    dock.accept_all_goods()
    if (!dock.accepts_any_goods()) {
        __log_info_native('[test:93] accept_all_goods should restore accepts_any_goods')
        __test_signal_ready()
        return
    }
    if (!__test_dock_any_match(bid, RESOURCE_POTTERY, RESOURCE_BEER, 0)) {
        __log_info_native('[test:93] accept_all_goods should match partner goods again')
        __test_signal_ready()
        return
    }
    __log_marker('dock_orders_restore_ok')

    dock.unaccept_all_goods()
    dock.toggle_good_accepted(RESOURCE_POTTERY)
    if (!__test_dock_any_match(bid, RESOURCE_POTTERY, RESOURCE_BEER, 0)) {
        __log_info_native('[test:93] pottery-only should any-match partner pottery+beer')
        __test_signal_ready()
        return
    }
    if (__test_dock_any_match(bid, RESOURCE_BEER, RESOURCE_LINEN, 0)) {
        __log_info_native('[test:93] pottery-only must not match beer+linen')
        __test_signal_ready()
        return
    }
    __log_marker('dock_orders_any_match_ok')

    if (__test_dock_match_score(bid, RESOURCE_POTTERY, RESOURCE_BEER, 0) !== 1) {
        __log_info_native('[test:93] pottery-only score expected 1')
        __test_signal_ready()
        return
    }
    dock.toggle_good_accepted(RESOURCE_BEER)
    if (__test_dock_match_score(bid, RESOURCE_POTTERY, RESOURCE_BEER, 0) !== 2) {
        __log_info_native('[test:93] pottery+beer score expected 2')
        __test_signal_ready()
        return
    }
    __log_marker('dock_orders_score_ok')

    // Weighted: import match ×2, export-only ×1 — import pier beats export-only pier.
    // trade_score(imports..., exports...): pottery import + beer export with both accepted → 2+1=3
    var weighted = __test_dock_trade_score(bid, RESOURCE_POTTERY, 0, 0, RESOURCE_BEER, 0, 0)
    if (weighted !== 3) {
        __log_info_native('[test:93] weighted pottery-import+beer-export expected 3, got ' + weighted)
        __test_signal_ready()
        return
    }
    if (__test_dock_trade_score(bid, 0, 0, 0, RESOURCE_BEER, 0, 0) !== 1) {
        __log_info_native('[test:93] export-only beer expected weight 1')
        __test_signal_ready()
        return
    }
    if (__test_dock_trade_score(bid, RESOURCE_POTTERY, 0, 0, 0, 0, 0) !== 2) {
        __log_info_native('[test:93] import-only pottery expected weight 2')
        __test_signal_ready()
        return
    }

    // Two docks: pottery specialist scores higher on pottery import than beer specialist.
    var dock_tile = __building_tile(bid)
    var bid2 = __test_building_create(BUILDING_DOCK, dock_tile.x + 10, dock_tile.y)
    if (!bid2 || bid2 === bid) {
        __log_info_native('[test:93] second dock create failed bid2=' + bid2 + ' bid=' + bid)
        __test_signal_ready()
        return
    }
    var dock2 = city.get_dock(bid2)
    dock2.unaccept_all_goods()
    dock2.toggle_good_accepted(RESOURCE_BEER)

    dock.unaccept_all_goods()
    dock.toggle_good_accepted(RESOURCE_POTTERY)

    var pottery_dock = __test_dock_trade_score(bid, RESOURCE_POTTERY, 0, 0, RESOURCE_BEER, 0, 0)
    var beer_dock = __test_dock_trade_score(bid2, RESOURCE_POTTERY, 0, 0, RESOURCE_BEER, 0, 0)
    if (!(pottery_dock > beer_dock)) {
        __log_info_native('[test:93] pottery dock should outscore beer dock for pottery-import+beer-export (got ' + pottery_dock + ' vs ' + beer_dock + ')')
        __test_signal_ready()
        return
    }
    __log_marker('dock_orders_weight_ok')

    // Ship integration (lite): match_score_for_ship + smart-routing free-dock filter.
    var ship = test_figure_create(FIGURE_TRADE_SHIP)
    if (!ship) {
        __log_info_native('[test:93] trade ship create failed')
        __test_signal_ready()
        return
    }
    dock.accept_all_goods()
    dock2.unaccept_all_goods()
    var ship_score = __test_dock_match_score_for_ship(bid, ship)
    if (ship_score < 0) {
        __log_info_native('[test:93] match_score_for_ship failed')
        __test_signal_ready()
        return
    }

    __test_building_set_workers(bid, 12)
    __test_building_set_workers(bid2, 12)

    var prev_smart = game_features.get('gameplay_change_dock_smart_routing')
    game_features.set('gameplay_change_dock_smart_routing', true)
    dock.unaccept_all_goods()
    dock2.unaccept_all_goods()
    if (__test_map_get_free_dock(ship) !== 0) {
        __log_info_native('[test:93] smart: accept-none dock must not be chosen as free destination')
        game_features.set('gameplay_change_dock_smart_routing', prev_smart)
        __test_signal_ready()
        return
    }
    game_features.set('gameplay_change_dock_smart_routing', false)
    // OG linear list: staffed docks are eligible even with accept-none.
    var og_free = __test_map_get_free_dock(ship)
    if (og_free !== bid && og_free !== bid2) {
        __log_info_native('[test:93] OG free dock expected staffed pier, got ' + og_free)
        game_features.set('gameplay_change_dock_smart_routing', prev_smart)
        __test_signal_ready()
        return
    }
    game_features.set('gameplay_change_dock_smart_routing', prev_smart)

    // yard_proximity is defined (10000 if no road/SY); must not crash.
    if (__test_dock_yard_proximity(bid) < 0) {
        __log_info_native('[test:93] yard_proximity failed')
        __test_signal_ready()
        return
    }
    __log_marker('dock_orders_ship_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'dock_orders_accept_all_ok',
        'dock_orders_none_ok',
        'dock_orders_restore_ok',
        'dock_orders_any_match_ok',
        'dock_orders_score_ok',
        'dock_orders_weight_ok',
        'dock_orders_ship_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:93] missing marker: ' + marker)
            return false
        }
    }
    return true
}

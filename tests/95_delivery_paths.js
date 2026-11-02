// Recorded visitor paths: granary/lodge/palace/bazaar keep last 4 handoff trails for hover UI.
//
// Markers:
//   [test-marker] delivery_paths_granary_push_ok
//   [test-marker] delivery_paths_ring4_ok
//   [test-marker] delivery_paths_evict_ok
//   [test-marker] delivery_paths_lodge_ok
//   [test-marker] delivery_paths_palace_ok
//   [test-marker] delivery_paths_bazaar_ok
//   [test-marker] delivery_paths_feature_ok

function test95_push_path(bid, tile_x, tile_y) {
    var pid = __test_recorded_path_acquire()
    if (!pid) {
        return 0
    }
    __test_recorded_path_append(pid, tile_x, tile_y)
    __test_building_push_recorded_path(bid, pid)
    return pid
}

function run_test() {
    __log_info_native('[test:95] delivery paths recorded')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    var granary = __test_building_create(BUILDING_GRANARY, cx, cy)
    if (!granary) {
        __log_info_native('[test:95] granary create failed')
        __test_signal_ready()
        return
    }

    var p1 = test95_push_path(granary, cx, cy)
    if (!p1) {
        __log_info_native('[test:95] path acquire failed')
        __test_signal_ready()
        return
    }
    if (__test_building_recorded_path_at(granary, 0) != p1) {
        __log_info_native('[test:95] granary newest path want ' + p1
            + ' got ' + __test_building_recorded_path_at(granary, 0))
        __test_signal_ready()
        return
    }
    if (__test_recorded_path_tile_count(p1) < 1) {
        __log_info_native('[test:95] path should have tiles')
        __test_signal_ready()
        return
    }
    __log_marker('delivery_paths_granary_push_ok')

    var p2 = test95_push_path(granary, cx + 1, cy)
    var p3 = test95_push_path(granary, cx + 2, cy)
    var p4 = test95_push_path(granary, cx + 3, cy)
    if (__test_building_recorded_path_at(granary, 0) != p4
        || __test_building_recorded_path_at(granary, 1) != p3
        || __test_building_recorded_path_at(granary, 2) != p2
        || __test_building_recorded_path_at(granary, 3) != p1) {
        __log_info_native('[test:95] ring order want newest-first ' + p4 + ',' + p3 + ',' + p2 + ',' + p1
            + ' got ' + __test_building_recorded_path_at(granary, 0)
            + ',' + __test_building_recorded_path_at(granary, 1)
            + ',' + __test_building_recorded_path_at(granary, 2)
            + ',' + __test_building_recorded_path_at(granary, 3))
        __test_signal_ready()
        return
    }
    __log_marker('delivery_paths_ring4_ok')

    var p5 = test95_push_path(granary, cx + 4, cy)
    if (__test_building_recorded_path_at(granary, 0) != p5
        || __test_building_recorded_path_at(granary, 1) != p4
        || __test_building_recorded_path_at(granary, 2) != p3
        || __test_building_recorded_path_at(granary, 3) != p2) {
        __log_info_native('[test:95] after 5th push ring want ' + p5 + ',' + p4 + ',' + p3 + ',' + p2)
        __test_signal_ready()
        return
    }
    if (__test_recorded_path_used(p1) != 0) {
        __log_info_native('[test:95] oldest path should be released after eviction')
        __test_signal_ready()
        return
    }
    __log_marker('delivery_paths_evict_ok')

    var lodge = __test_building_create(BUILDING_HUNTING_LODGE, cx + 8, cy)
    if (!lodge) {
        __log_info_native('[test:95] hunting lodge create failed')
        __test_signal_ready()
        return
    }
    var lp = test95_push_path(lodge, cx + 8, cy)
    if (__test_building_recorded_path_at(lodge, 0) != lp) {
        __log_info_native('[test:95] lodge should keep recorded path')
        __test_signal_ready()
        return
    }
    if (__test_building_recorded_path_at(granary, 0) != p5) {
        __log_info_native('[test:95] lodge push must not clear granary ring')
        __test_signal_ready()
        return
    }
    __log_marker('delivery_paths_lodge_ok')

    var palace = __test_building_create(BUILDING_VILLAGE_PALACE, cx + 14, cy)
    if (!palace) {
        __log_info_native('[test:95] village palace create failed')
        __test_signal_ready()
        return
    }
    var pp = test95_push_path(palace, cx + 14, cy)
    if (__test_building_recorded_path_at(palace, 0) != pp) {
        __log_info_native('[test:95] palace should keep recorded path')
        __test_signal_ready()
        return
    }
    if (__test_building_recorded_path_at(granary, 0) != p5) {
        __log_info_native('[test:95] palace push must not clear granary ring')
        __test_signal_ready()
        return
    }
    __log_marker('delivery_paths_palace_ok')

    var bazaar = __test_building_create(BUILDING_BAZAAR, cx + 18, cy)
    if (!bazaar) {
        __log_info_native('[test:95] bazaar create failed')
        __test_signal_ready()
        return
    }
    var bp = test95_push_path(bazaar, cx + 18, cy)
    if (__test_building_recorded_path_at(bazaar, 0) != bp) {
        __log_info_native('[test:95] bazaar should keep recorded path')
        __test_signal_ready()
        return
    }
    __log_marker('delivery_paths_bazaar_ok')

    // Remake UI: off by default since game features default to original Pharaoh (d1117381e).
    if (game_features.default('gameui_show_delivery_paths')) {
        __log_info_native('[test:95] gameui_show_delivery_paths should default OFF')
        __test_signal_ready()
        return
    }
    var prev_paths = game_features.gameui_show_delivery_paths
    game_features.gameui_show_delivery_paths = true
    var enabled = game_features.gameui_show_delivery_paths
    game_features.gameui_show_delivery_paths = false
    var disabled = !game_features.gameui_show_delivery_paths
    game_features.gameui_show_delivery_paths = prev_paths
    if (!enabled || !disabled) {
        __log_info_native('[test:95] failed to toggle delivery paths flag on=' + enabled + ' off=' + disabled)
        __test_signal_ready()
        return
    }
    __log_marker('delivery_paths_feature_ok')

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('delivery_paths_granary_push_ok')
        && __test_find_inlog('delivery_paths_ring4_ok')
        && __test_find_inlog('delivery_paths_evict_ok')
        && __test_find_inlog('delivery_paths_lodge_ok')
        && __test_find_inlog('delivery_paths_palace_ok')
        && __test_find_inlog('delivery_paths_bazaar_ok')
        && __test_find_inlog('delivery_paths_feature_ok')
}

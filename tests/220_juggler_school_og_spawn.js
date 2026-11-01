// Juggler school (JS): OG delays_service + no living-walker gate by default.
// gameplay_juggler_school_one_walker restores remake one-at-a-time.

var __test220_ok = false
var __test220_feat_prev = false

function test220_fail(msg) {
    __log_info_native('[test:220] FAIL: ' + msg)
    game_features.set('gameplay_juggler_school_one_walker', __test220_feat_prev)
    __test_signal_ready()
}

function test220_place_school() {
    var bid = test_building_place(BUILDING_JUGGLER_SCHOOL, -1, -1)
    if (!bid) {
        return 0
    }

    var zt = __building_tile(bid)
    for (var dx = 0; dx < 3; dx++) {
        terrain.add({ x: zt.x + dx, y: zt.y + 2 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_check_kingdome_access()

    __test_building_set_workers(bid, 5)
    var b = city.get_building(bid)
    b.has_road_access = true
    return bid
}

function run_test() {
    __log_info_native('[test:220] juggler school OG spawn')
    __test220_feat_prev = game_features.get('gameplay_juggler_school_one_walker') === true
    game_features.set('gameplay_juggler_school_one_walker', false)

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var bid = test220_place_school()
    if (!bid) {
        test220_fail('place failed')
        return
    }

    var before = __test_count_figures(FIGURE_JUGGLER)
    var b = city.get_building(bid)
    b.figure_spawn_delay = 3
    building_juggler_school_spawn_figure({ bid: bid })
    if (__test_count_figures(FIGURE_JUGGLER) < before + 1) {
        test220_fail('OG: expected juggler after delay>3 at 100% workers')
        return
    }
    __log_marker('test220_og_first_spawn')

    // OG: school may spawn again while previous juggler still lives.
    before = __test_count_figures(FIGURE_JUGGLER)
    b = city.get_building(bid)
    b.figure_spawn_delay = 3
    building_juggler_school_spawn_figure({ bid: bid })
    if (__test_count_figures(FIGURE_JUGGLER) < before + 1) {
        test220_fail('OG: expected overlapping jugglers, got '
            + __test_count_figures(FIGURE_JUGGLER))
        return
    }
    __log_marker('test220_og_overlap')

    // Fresh school for feature path (avoid stale slots after poof).
    game_features.set('gameplay_juggler_school_one_walker', true)
    var bid2 = test220_place_school()
    if (!bid2) {
        test220_fail('place feature school failed')
        return
    }

    before = __test_count_figures(FIGURE_JUGGLER)
    b = city.get_building(bid2)
    b.figure_spawn_delay = 3
    building_juggler_school_spawn_figure({ bid: bid2 })
    if (__test_count_figures(FIGURE_JUGGLER) != before + 1) {
        test220_fail('feature: expected first juggler')
        return
    }

    before = __test_count_figures(FIGURE_JUGGLER)
    b = city.get_building(bid2)
    b.figure_spawn_delay = 3
    building_juggler_school_spawn_figure({ bid: bid2 })
    if (__test_count_figures(FIGURE_JUGGLER) != before) {
        test220_fail('feature: must wait for living juggler, got delta '
            + (__test_count_figures(FIGURE_JUGGLER) - before))
        return
    }
    __log_marker('test220_feature_one_walker')

    __test220_ok = true
    game_features.set('gameplay_juggler_school_one_walker', __test220_feat_prev)
    __test_signal_ready()
}

function check_valid() {
    return __test220_ok
        && __test_find_inlog('[test-marker] test220_og_first_spawn')
        && __test_find_inlog('[test-marker] test220_og_overlap')
        && __test_find_inlog('[test-marker] test220_feature_one_walker')
}

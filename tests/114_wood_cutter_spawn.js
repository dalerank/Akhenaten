// Wood cutter lumberjack spawn (JS in wood_cutter.js):
// OG: worker % → max jacks 1/2/3; capacity (500-stored)/25; spawn needs reachable grown timber.
// Remake feature gameplay_change_wood_cutter_single_gatherer: max 1 + any TERRAIN_TREE gate.
// Markers:
//   [test-marker] test114_empty_yard_has_capacity
//   [test-marker] test114_full_staff_max_3
//   [test-marker] test114_half_staff_max_2
//   [test-marker] test114_remake_feature_caps_1
//   [test-marker] test114_full_stock_no_capacity
//   [test-marker] test114_spawn_figure_ran

var __test114_ok = false
var __test114_feat_prev = false

function test114_fail(msg) {
    game_features.gameplay_change_wood_cutter_single_gatherer = __test114_feat_prev
    __log_info_native('[test:114] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:114] wood cutter lumberjack spawn (OG staffing)')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __test114_feat_prev = !!game_features.gameplay_change_wood_cutter_single_gatherer
    game_features.gameplay_change_wood_cutter_single_gatherer = false

    var bid = test_building_place(BUILDING_WOOD_CUTTERS, -1, -1)
    if (!bid) {
        return test114_fail('place failed')
    }

    __test_building_set_workers(bid, 8)
    var b = city.get_building(bid)
    b.has_road_access = true
    b.figure_spawn_delay = 0

    if (wood_cutter_max_lumberjacks(b) != 3) {
        return test114_fail('full staff should allow 3 lumberjacks, got ' + wood_cutter_max_lumberjacks(b))
    }
    if (!wood_cutter_has_lumberjack_capacity(b)) {
        return test114_fail('empty yard should have lumberjack capacity')
    }
    __log_marker('test114_empty_yard_has_capacity')
    __log_marker('test114_full_staff_max_3')

    __test_building_set_workers(bid, 4)
    if (wood_cutter_max_lumberjacks(b) != 2) {
        return test114_fail('50% staff should allow 2 lumberjacks, got ' + wood_cutter_max_lumberjacks(b))
    }
    __log_marker('test114_half_staff_max_2')

    __test_building_set_workers(bid, 8)
    game_features.gameplay_change_wood_cutter_single_gatherer = true
    if (wood_cutter_max_lumberjacks(b) != 1) {
        return test114_fail('remake feature should cap at 1, got ' + wood_cutter_max_lumberjacks(b))
    }
    game_features.gameplay_change_wood_cutter_single_gatherer = false
    __log_marker('test114_remake_feature_caps_1')

    b.consume_resource(RESOURCE_TIMBER, -500)
    if (wood_cutter_has_lumberjack_capacity(b)) {
        return test114_fail('500 timber should fill spawn capacity')
    }
    __log_marker('test114_full_stock_no_capacity')

    b.consume_resource(RESOURCE_TIMBER, 500)
    // OG spawn gate uses the daily city flag, not a per-tick BFS.
    __map_trees_set_reachable(true)
    building_wood_cutter_spawn_figure({ bid: bid })
    if (b.get_figures_number(FIGURE_LUMBERJACK) < 1) {
        return test114_fail('spawn with trees_reachable should create lumberjacks')
    }
    __log_marker('test114_spawn_figure_ran')

    game_features.gameplay_change_wood_cutter_single_gatherer = __test114_feat_prev
    __test114_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test114_ok
        && __test_find_inlog('[test-marker] test114_empty_yard_has_capacity')
        && __test_find_inlog('[test-marker] test114_full_staff_max_3')
        && __test_find_inlog('[test-marker] test114_half_staff_max_2')
        && __test_find_inlog('[test-marker] test114_remake_feature_caps_1')
        && __test_find_inlog('[test-marker] test114_full_stock_no_capacity')
        && __test_find_inlog('[test-marker] test114_spawn_figure_ran')
}

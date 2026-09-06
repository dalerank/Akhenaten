// FM3-lite / Slice B: gameplay_enhanced_food_mill — food variety before goods.
// Markers:
//   [test-marker] food_mill_flag_off_ok
//   [test-marker] food_mill_target_param_ok
//   [test-marker] food_mill_off_pottery_beats_food2_ok
//   [test-marker] food_mill_on_food2_before_pottery_ok
//   [test-marker] food_mill_on_topup_before_pottery_ok
//   [test-marker] food_mill_satisfied_allows_pottery_ok
//   [test-marker] food_mill_full_foods_pottery_ok

var __test149_ok = {
    flag: false,
    target: false,
    off_beats: false,
    on_food2: false,
    on_topup: false,
    satisfied: false,
    full: false
}

// #644: a granary is reached through its perimeter road tiles, so faking road_network_id is not
// enough -- lay a real road along one side of the footprint and take the network the map computes.
function grant_granary_road(bid) {
    var b = city.get_building(bid)
    var t = __building_tile(bid)
    var dx
    for (dx = -1; dx <= b.size; dx++) {
        terrain.add({ x: t.x + dx, y: t.y - 1 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    b.has_road_access = true
    return __test_tile_road_network(__test_grid_offset_xy(t.x, t.y - 1))
}

function run_test() {
    __log_info_native('[test:149] bazaar food variety (food mill slice B)')
    test_ensure_city_session('data/default.map')

    var mill_prev = game_features.get('gameplay_enhanced_food_mill')
    var multi_prev = game_features.get('gameplay_change_bazaar_multi_buyers')
    if (game_features.default('gameplay_enhanced_food_mill')) {
        __log_info_native('[test:149] food mill flag default should be OFF')
        __test_signal_ready()
        return
    }
    __log_marker('food_mill_flag_off_ok')
    __test149_ok.flag = true

    // Pin foods for --no-resource / empty empire maps.
    __test_set_allowed_food(0, RESOURCE_GRAIN)
    __test_set_allowed_food(1, RESOURCE_FIGS)

    function finish() {
        game_features.set('gameplay_enhanced_food_mill', mill_prev)
        game_features.set('gameplay_change_bazaar_multi_buyers', multi_prev)
        __test_signal_ready()
    }

    if (__test_bazaar_food_variety_target_param() != 2) {
        __log_info_native('[test:149] food_variety_target want 2 got '
            + __test_bazaar_food_variety_target_param())
        finish()
        return
    }
    __log_marker('food_mill_target_param_ok')
    __test149_ok.target = true

    var bid = __test_building_create(BUILDING_BAZAAR, -1, -1)
    var sy = __test_building_create(BUILDING_STORAGE_YARD, -1, -1)
    var granary = __test_building_create(BUILDING_GRANARY, -1, -1)
    if (!bid || !sy || !granary) {
        __log_info_native('[test:149] create failed')
        finish()
        return
    }
    city.get_building(bid).road_network_id = grant_granary_road(granary)
    if (!__test_bazaar_link_storage(bid, sy) || !__test_bazaar_link_storage(bid, granary)) {
        __log_info_native('[test:149] link storage failed')
        finish()
        return
    }
    if (!__test_storage_yard_add_resource(sy, RESOURCE_POTTERY, 400)) {
        __log_info_native('[test:149] pottery stock failed')
        finish()
        return
    }
    if (!__test_granary_add_allowed_food(granary, 0, 400)) {
        __log_info_native('[test:149] food0 stock failed')
        finish()
        return
    }
    if (!__test_granary_add_allowed_food(granary, 1, 400)) {
        __log_info_native('[test:149] food1 stock failed')
        finish()
        return
    }
    __test_bazaar_set_good_demands(bid, 10, 0, 0, 0)

    // OFF + multi: food buyer out → pottery beats food2
    game_features.set('gameplay_enhanced_food_mill', false)
    game_features.set('gameplay_change_bazaar_multi_buyers', true)
    var fid_a = __test_bazaar_attach_buyer(bid, BUILDING_SLOT_MARKET_BUYER, 0)
    if (!fid_a) {
        __log_info_native('[test:149] attach food buyer failed')
        finish()
        return
    }
    __test_figure_set_action(fid_a, 145)
    var inv = __test_bazaar_pick_next_inventory(bid)
    if (inv != 4) {
        __log_info_native('[test:149] OFF complementary want pottery(4) got ' + inv)
        finish()
        return
    }
    __log_marker('food_mill_off_pottery_beats_food2_ok')
    __test149_ok.off_beats = true

    // ON + multi → food2 before pottery
    game_features.set('gameplay_enhanced_food_mill', true)
    inv = __test_bazaar_pick_next_inventory(bid)
    if (inv != 1) {
        __log_info_native('[test:149] ON complementary want food2(1) got ' + inv)
        finish()
        return
    }
    __log_marker('food_mill_on_food2_before_pottery_ok')
    __test149_ok.on_food2 = true

    // Single-buyer topup: only food0 in granary, food0 partial in bazaar.
    // OFF → pottery (empty goods); ON → top up food0.
    __test_figure_set_action(fid_a, -1)
    __test_bazaar_reclaim_slot(bid, BUILDING_SLOT_MARKET_BUYER)
    game_features.set('gameplay_change_bazaar_multi_buyers', false)
    if (!__test_granary_clear_allowed_food(granary, 1)) {
        __log_info_native('[test:149] clear food1 failed')
        finish()
        return
    }
    __test_bazaar_set_inventory(bid, 0, 100)
    __test_bazaar_set_inventory(bid, 1, 0)
    __test_bazaar_set_inventory(bid, 2, 0)
    __test_bazaar_set_inventory(bid, 3, 0)
    if (__test_bazaar_food_types(bid) != 1) {
        __log_info_native('[test:149] food types want 1 got ' + __test_bazaar_food_types(bid))
        finish()
        return
    }

    game_features.set('gameplay_enhanced_food_mill', false)
    inv = __test_bazaar_get_storage_inventory(bid)
    if (inv != 4) {
        __log_info_native('[test:149] OFF single want pottery(4) got ' + inv)
        finish()
        return
    }

    game_features.set('gameplay_enhanced_food_mill', true)
    inv = __test_bazaar_get_storage_inventory(bid)
    if (inv != 0) {
        __log_info_native('[test:149] ON single want food0 topup got ' + inv)
        finish()
        return
    }
    __log_marker('food_mill_on_topup_before_pottery_ok')
    __test149_ok.on_topup = true

    // Variety satisfied → pottery
    if (!__test_granary_add_allowed_food(granary, 1, 400)) {
        __log_info_native('[test:149] restore food1 failed')
        finish()
        return
    }
    __test_bazaar_set_inventory(bid, 1, 50)
    if (__test_bazaar_food_types(bid) != 2) {
        __log_info_native('[test:149] food types want 2 got ' + __test_bazaar_food_types(bid))
        finish()
        return
    }
    inv = __test_bazaar_get_storage_inventory(bid)
    if (inv != 4) {
        __log_info_native('[test:149] satisfied want pottery(4) got ' + inv)
        finish()
        return
    }
    __log_marker('food_mill_satisfied_allows_pottery_ok')
    __test149_ok.satisfied = true

    __test_bazaar_set_inventory(bid, 0, 700)
    __test_bazaar_set_inventory(bid, 1, 700)
    __test_bazaar_set_inventory(bid, 2, 700)
    __test_bazaar_set_inventory(bid, 3, 700)
    inv = __test_bazaar_get_storage_inventory(bid)
    if (inv != 4) {
        __log_info_native('[test:149] full foods want pottery(4) got ' + inv)
        finish()
        return
    }
    __log_marker('food_mill_full_foods_pottery_ok')
    __test149_ok.full = true

    finish()
}

function check_valid() {
    return check_test()
}

function check_test() {
    if (!__test149_ok.flag || !__test149_ok.target || !__test149_ok.off_beats
        || !__test149_ok.on_food2 || !__test149_ok.on_topup || !__test149_ok.satisfied
        || !__test149_ok.full) {
        __log_info_native('[test:149] one or more phases failed')
        return false
    }
    var markers = [
        'food_mill_flag_off_ok',
        'food_mill_target_param_ok',
        'food_mill_off_pottery_beats_food2_ok',
        'food_mill_on_food2_before_pottery_ok',
        'food_mill_on_topup_before_pottery_ok',
        'food_mill_satisfied_allows_pottery_ok',
        'food_mill_full_foods_pottery_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:149] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

// FM3: bazaar buyer → food mill (prefer / soft min-wait / multi-type loop).
// Markers:
//   [test-marker] bazaar_mill_defaults_ok
//   [test-marker] bazaar_mill_preferred_ok
//   [test-marker] bazaar_mill_flag_off_ignores_ok
//   [test-marker] bazaar_mill_min_blocks_ok
//   [test-marker] bazaar_mill_empty_fallback_ok
//   [test-marker] bazaar_mill_multi_type_loop_ok
//   [test-marker] bazaar_mill_food_months_ok

var __test159_ok = {
    defaults: false,
    preferred: false,
    flag_off: false,
    min_blocks: false,
    empty_fallback: false,
    multi: false,
    food_months: false
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
    __log_info_native('[test:159] bazaar mill buyer (FM3)')
    test_ensure_city_session('data/default.map')

    var mill_prev = game_features.get('gameplay_enhanced_food_mill')
    var multi_prev = game_features.get('gameplay_change_bazaar_multi_buyers')
    function finish() {
        game_features.set('gameplay_enhanced_food_mill', mill_prev)
        game_features.set('gameplay_change_bazaar_multi_buyers', multi_prev)
        __test_signal_ready()
    }

    game_features.set('gameplay_enhanced_food_mill', true)
    game_features.set('gameplay_change_bazaar_multi_buyers', false)
    building_menu_ctrl.apply_enhanced_buildings()

    // --no-resource / default.map often has empty allowed_foods; pin two types for FM3.
    __test_set_allowed_food(0, RESOURCE_GRAIN)
    __test_set_allowed_food(1, RESOURCE_FIGS)

    var bid = __test_building_create(BUILDING_BAZAAR, -1, -1)
    var mill = __test_building_create(BUILDING_FOOD_MILL, -1, -1)
    var granary = __test_building_create(BUILDING_GRANARY, -1, -1)
    var sy = __test_building_create(BUILDING_STORAGE_YARD, -1, -1)
    if (!bid || !mill || !granary || !sy) {
        __log_info_native('[test:159] create failed')
        finish()
        return
    }

    if (__test_bazaar_desired_variety(bid) != 2 || __test_bazaar_min_variety(bid) != 1) {
        __log_info_native('[test:159] defaults want desired=2 min=1 got '
            + __test_bazaar_desired_variety(bid) + '/' + __test_bazaar_min_variety(bid))
        finish()
        return
    }
    __log_marker('bazaar_mill_defaults_ok')
    __test159_ok.defaults = true

    city.get_building(bid).road_network_id = grant_granary_road(granary)
    if (!__test_bazaar_link_storage(bid, mill)
        || !__test_bazaar_link_storage(bid, granary)
        || !__test_bazaar_link_storage(bid, sy)) {
        __log_info_native('[test:159] link failed')
        finish()
        return
    }
    __test_building_set_workers(mill, 12)
    __test_building_set_workers(granary, 20)

    var food0 = __test_city_allowed_food(0)
    var food1 = __test_city_allowed_food(1)
    if (!food0 || !food1) {
        __log_info_native('[test:159] need two allowed foods got ' + food0 + '/' + food1)
        finish()
        return
    }

    if (!__test_food_mill_add_resource(mill, food0, 400)) {
        __log_info_native('[test:159] stock mill food0 failed food=' + food0)
        finish()
        return
    }
    if (!__test_granary_add_allowed_food(granary, 0, 400)) {
        __log_info_native('[test:159] stock granary food0 failed food=' + food0
            + ' allowed0=' + __test_city_allowed_food(0))
        finish()
        return
    }
    if (!__test_storage_yard_add_resource(sy, RESOURCE_POTTERY, 400)) {
        __log_info_native('[test:159] pottery stock failed')
        finish()
        return
    }
    __test_bazaar_set_good_demands(bid, 10, 0, 0, 0)

    // Prefer mill over granary for food0
    var dest_id = __test_bazaar_get_storage_destination_id(bid)
    var dest_type = __test_bazaar_get_storage_destination_type(bid)
    if (dest_id != mill || dest_type != BUILDING_FOOD_MILL) {
        __log_info_native('[test:159] prefer mill want ' + mill + '/' + BUILDING_FOOD_MILL
            + ' got ' + dest_id + '/' + dest_type)
        finish()
        return
    }
    __log_marker('bazaar_mill_preferred_ok')
    __test159_ok.preferred = true

    // Flag OFF → ignore mill, go to granary
    game_features.set('gameplay_enhanced_food_mill', false)
    dest_type = __test_bazaar_get_storage_destination_type(bid)
    if (dest_type != BUILDING_GRANARY) {
        __log_info_native('[test:159] flag OFF want granary got ' + dest_type)
        finish()
        return
    }
    __log_marker('bazaar_mill_flag_off_ignores_ok')
    __test159_ok.flag_off = true

    // Soft min-wait: mill has 1 type, min=2 → block trips (incl. pottery)
    game_features.set('gameplay_enhanced_food_mill', true)
    __test_bazaar_set_desired_variety(bid, 2)
    __test_bazaar_set_min_variety(bid, 2)
    if (__test_food_mill_variety(mill) != 1) {
        __log_info_native('[test:159] mill variety want 1 got ' + __test_food_mill_variety(mill))
        finish()
        return
    }
    if (__test_bazaar_waiting_for_mill(bid) != 1) {
        __log_info_native('[test:159] should wait for mill variety')
        finish()
        return
    }
    dest_id = __test_bazaar_get_storage_destination_id(bid)
    if (dest_id != 0) {
        __log_info_native('[test:159] min-wait should block dest, got ' + dest_id)
        finish()
        return
    }
    __log_marker('bazaar_mill_min_blocks_ok')
    __test159_ok.min_blocks = true

    // Empty mill (variety=0) + min=2 → no wait, fallback granary
    // Clear mill stock by removing via force path: re-add after wipe needs helper.
    // Use a fresh mill with no stock linked instead: clear by removing food.
    var mill_amt = __test_food_mill_amount(mill, food0)
    if (mill_amt > 0) {
        // drain via buyer take until empty is heavy; zero via add offset:
        // remove_resource returns remainder — use repeated take from a temp buyer later.
        // Simpler: create second empty mill closer... or set min back and test empty via new mill.
    }
    __test_bazaar_set_min_variety(bid, 1)
    // Drain mill food0 by taking with a buyer (multi-type off since desired may take only one if only one type)
    var fid = __test_bazaar_attach_buyer(bid, BUILDING_SLOT_MARKET_BUYER, 0)
    if (!fid) {
        __log_info_native('[test:159] attach buyer for drain failed')
        finish()
        return
    }
    // Desired=1 so loop takes only food0
    __test_bazaar_set_desired_variety(bid, 1)
    if (__test_market_buyer_take_food(fid, bid, mill) != 1) {
        __log_info_native('[test:159] drain take failed')
        finish()
        return
    }
    __test_figure_set_action(fid, -1)
    __test_bazaar_reclaim_slot(bid, BUILDING_SLOT_MARKET_BUYER)

    if (__test_food_mill_variety(mill) != 0) {
        __log_info_native('[test:159] mill should be empty after drain, variety='
            + __test_food_mill_variety(mill) + ' amt=' + __test_food_mill_amount(mill, food0))
        finish()
        return
    }

    __test_bazaar_set_desired_variety(bid, 2)
    __test_bazaar_set_min_variety(bid, 2)
    if (__test_bazaar_waiting_for_mill(bid) != 0) {
        __log_info_native('[test:159] empty mill should not wait')
        finish()
        return
    }
    dest_type = __test_bazaar_get_storage_destination_type(bid)
    if (dest_type != BUILDING_GRANARY) {
        __log_info_native('[test:159] empty mill fallback want granary got ' + dest_type)
        finish()
        return
    }
    __log_marker('bazaar_mill_empty_fallback_ok')
    __test159_ok.empty_fallback = true

    // Multi-type loop: restock mill with 2 foods, desired=2, take once → both reduced
    if (!__test_food_mill_add_resource(mill, food0, 400)
        || !__test_food_mill_add_resource(mill, food1, 400)) {
        __log_info_native('[test:159] restock mill 2 foods failed')
        finish()
        return
    }
    __test_bazaar_set_desired_variety(bid, 2)
    __test_bazaar_set_min_variety(bid, 1)
    __test_bazaar_set_inventory(bid, 0, 0)
    __test_bazaar_set_inventory(bid, 1, 0)

    var before0 = __test_food_mill_amount(mill, food0)
    var before1 = __test_food_mill_amount(mill, food1)
    fid = __test_bazaar_attach_buyer(bid, BUILDING_SLOT_MARKET_BUYER, 0)
    if (!fid || __test_market_buyer_take_food(fid, bid, mill) != 1) {
        __log_info_native('[test:159] multi take failed')
        finish()
        return
    }
    var after0 = __test_food_mill_amount(mill, food0)
    var after1 = __test_food_mill_amount(mill, food1)
    if (!(after0 < before0 && after1 < before1)) {
        __log_info_native('[test:159] multi loop want both reduced before='
            + before0 + '/' + before1 + ' after=' + after0 + '/' + after1)
        finish()
        return
    }
    __log_marker('bazaar_mill_multi_type_loop_ok')
    __test159_ok.multi = true

    // Mill stock counts toward city food supply (staffed + road access).
    var mt = __building_tile(mill)
    for (var dx = 0; dx < 3; dx++) {
        terrain.add({ x: mt.x + dx, y: mt.y + 3 }, TERRAIN_ROAD)
    }
    __test_building_set_workers(mill, 12)
    __test_granary_clear_allowed_food(granary, 0)
    __test_granary_clear_allowed_food(granary, 1)
    var mill_stock = __test_food_mill_amount(mill, food0)
    if (mill_stock < 100) {
        if (!__test_food_mill_add_resource(mill, food0, 200)) {
            __log_info_native('[test:159] restock for food-months failed')
            finish()
            return
        }
        mill_stock = __test_food_mill_amount(mill, food0)
    }
    var city_stored = __test_city_recalc_granary_stored(food0)
    if (city_stored < mill_stock) {
        __log_info_native('[test:159] city food should include mill want>=' + mill_stock
            + ' got ' + city_stored)
        finish()
        return
    }
    __log_marker('bazaar_mill_food_months_ok')
    __test159_ok.food_months = true

    finish()
}

function check_valid() {
    return check_test()
}

function check_test() {
    if (!__test159_ok.defaults || !__test159_ok.preferred || !__test159_ok.flag_off
        || !__test159_ok.min_blocks || !__test159_ok.empty_fallback || !__test159_ok.multi
        || !__test159_ok.food_months) {
        __log_info_native('[test:159] one or more phases failed')
        return false
    }
    var markers = [
        'bazaar_mill_defaults_ok',
        'bazaar_mill_preferred_ok',
        'bazaar_mill_flag_off_ignores_ok',
        'bazaar_mill_min_blocks_ok',
        'bazaar_mill_empty_fallback_ok',
        'bazaar_mill_multi_type_loop_ok',
        'bazaar_mill_food_months_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:159] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

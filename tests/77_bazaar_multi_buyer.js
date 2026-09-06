// BB0–BB3: multi-buyer bazaar — slots, complementary, fallback, demand, OFF slot1.
// Markers:
//   [test-marker] bazaar_multi_flag_off_ok
//   [test-marker] bazaar_multi_slot_const_ok
//   [test-marker] bazaar_multi_max_buyers_ok
//   [test-marker] bazaar_multi_slot3_alive_ok
//   [test-marker] bazaar_multi_slot2_poof_ok
//   [test-marker] bazaar_multi_count_ok
//   [test-marker] bazaar_multi_finished_not_counted_ok
//   [test-marker] bazaar_multi_cooldown_last_ok
//   [test-marker] bazaar_multi_reclaim_ok
//   [test-marker] bazaar_multi_exclude_ok
//   [test-marker] bazaar_multi_complementary_ok
//   [test-marker] bazaar_multi_pottery_beats_food2_ok
//   [test-marker] bazaar_multi_fallback_food2_ok
//   [test-marker] bazaar_multi_demand_no_burn_on_fail_ok
//   [test-marker] bazaar_multi_demand_freeze_ok
//   [test-marker] bazaar_multi_off_slot1_ok
//   [test-marker] bazaar_multi_off_clears_slot3_ok

var __test77_ok = {
    flag: false,
    slot: false,
    maxb: false,
    slot3: false,
    slot2: false,
    count: false,
    finished: false,
    cooldown: false,
    reclaim: false,
    exclude: false,
    complementary: false,
    beats: false,
    fallback: false,
    demand_fail: false,
    demand: false,
    offslot: false,
    offclear: false
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
    __log_info_native('[test:77] bazaar multi buyers')
    test_ensure_city_session('data/default.map')

    var flag_prev = game_features.get('gameplay_change_bazaar_multi_buyers')
    var flag_default = game_features.default('gameplay_change_bazaar_multi_buyers')
    if (flag_default) {
        __log_info_native('[test:77] flag default should be OFF')
        __test_signal_ready()
        return
    }
    __log_marker('bazaar_multi_flag_off_ok')
    __test77_ok.flag = true

    // Pin foods for --no-resource / empty empire maps.
    __test_set_allowed_food(0, RESOURCE_GRAIN)
    __test_set_allowed_food(1, RESOURCE_FIGS)

    game_features.set('gameplay_change_bazaar_multi_buyers', false)

    function finish() {
        game_features.set('gameplay_change_bazaar_multi_buyers', flag_prev)
        __test_signal_ready()
    }

    if (typeof BUILDING_SLOT_MARKET_BUYER_2 === 'undefined' || BUILDING_SLOT_MARKET_BUYER_2 != 3) {
        __log_info_native('[test:77] MARKET_BUYER_2 want 3 got ' + BUILDING_SLOT_MARKET_BUYER_2)
        finish()
        return
    }
    if (BUILDING_SLOT_MARKET_BUYER != 1 || BUILDING_SLOT_LABOR_SEEKER != 2) {
        __log_info_native('[test:77] slot layout broken')
        finish()
        return
    }
    __log_marker('bazaar_multi_slot_const_ok')
    __test77_ok.slot = true

    var max_buyers = __test_bazaar_max_buyers_param()
    if (max_buyers != 2) {
        __log_info_native('[test:77] max_buyers want 2 got ' + max_buyers)
        finish()
        return
    }
    __log_marker('bazaar_multi_max_buyers_ok')
    __test77_ok.maxb = true

    var bid = __test_building_create(BUILDING_BAZAAR, -1, -1)
    if (!bid) {
        __log_info_native('[test:77] bazaar create failed')
        finish()
        return
    }

    var fid3 = __test_bazaar_attach_buyer(bid, BUILDING_SLOT_MARKET_BUYER_2, 0)
    if (!fid3) {
        __log_info_native('[test:77] buyer on slot 3 poofed or missing')
        finish()
        return
    }
    __log_marker('bazaar_multi_slot3_alive_ok')
    __test77_ok.slot3 = true

    var fid2 = __test_bazaar_attach_buyer(bid, BUILDING_SLOT_LABOR_SEEKER, 4)
    if (fid2) {
        __log_info_native('[test:77] buyer on slot 2 should poof')
        finish()
        return
    }
    __log_marker('bazaar_multi_slot2_poof_ok')
    __test77_ok.slot2 = true

    var n = __test_bazaar_count_buyers(bid)
    if (n != 1) {
        __log_info_native('[test:77] count want 1 got ' + n)
        finish()
        return
    }
    __log_marker('bazaar_multi_count_ok')
    __test77_ok.count = true

    __test_figure_set_action(fid3, -1)
    n = __test_bazaar_count_buyers(bid)
    if (n != 0) {
        __log_info_native('[test:77] finished buyer still counted: ' + n)
        finish()
        return
    }
    __log_marker('bazaar_multi_finished_not_counted_ok')
    __test77_ok.finished = true

    var left = __test_bazaar_reclaim_slot(bid, BUILDING_SLOT_MARKET_BUYER_2)
    if (left != 0) {
        __log_info_native('[test:77] reclaim left figure id ' + left)
        finish()
        return
    }
    __log_marker('bazaar_multi_reclaim_ok')
    __test77_ok.reclaim = true

    game_features.set('gameplay_change_bazaar_multi_buyers', true)
    var fid_a = __test_bazaar_attach_buyer(bid, BUILDING_SLOT_MARKET_BUYER, 0)
    var fid_b = __test_bazaar_attach_buyer(bid, BUILDING_SLOT_MARKET_BUYER_2, 4)
    if (!fid_a || !fid_b) {
        __log_info_native('[test:77] dual attach failed a=' + fid_a + ' b=' + fid_b)
        finish()
        return
    }
    __test_figure_set_action(fid_a, -1)
    var delay = __test_bazaar_on_buyer_returned(fid_b)
    if (delay != -3) {
        __log_info_native('[test:77] cooldown want -3 got ' + delay)
        finish()
        return
    }
    __log_marker('bazaar_multi_cooldown_last_ok')
    __test77_ok.cooldown = true

    __test_figure_set_action(fid_a, 145)
    if (__test_bazaar_busy_excludes(bid, 0) != 1) {
        __log_info_native('[test:77] food0 should be excluded')
        finish()
        return
    }
    if (__test_bazaar_busy_excludes(bid, 4) != 1) {
        __log_info_native('[test:77] good0 should be excluded')
        finish()
        return
    }
    __log_marker('bazaar_multi_exclude_ok')
    __test77_ok.exclude = true

    // --- Complementary + granary setup ---
    __test_figure_set_action(fid_b, -1)
    __test_bazaar_reclaim_slot(bid, BUILDING_SLOT_MARKET_BUYER_2)
    __test_figure_set_action(fid_a, 145)
    if (__test_bazaar_count_buyers(bid) != 1) {
        __log_info_native('[test:77] want one food buyer, got ' + __test_bazaar_count_buyers(bid))
        finish()
        return
    }

    var sy = __test_building_create(BUILDING_STORAGE_YARD, -1, -1)
    var granary = __test_building_create(BUILDING_GRANARY, -1, -1)
    if (!sy || !granary) {
        __log_info_native('[test:77] sy/granary create failed')
        finish()
        return
    }
    city.get_building(bid).road_network_id = grant_granary_road(granary)
    if (!__test_bazaar_link_storage(bid, sy) || !__test_bazaar_link_storage(bid, granary)) {
        __log_info_native('[test:77] link storage failed')
        finish()
        return
    }
    if (!__test_storage_yard_add_resource(sy, RESOURCE_POTTERY, 400)) {
        __log_info_native('[test:77] pottery stock failed')
        finish()
        return
    }
    if (!__test_granary_add_allowed_food(granary, 1, 400)) {
        __log_info_native('[test:77] food1 stock failed (allowed_foods[1] missing?)')
        finish()
        return
    }
    __test_bazaar_set_good_demands(bid, 10, 0, 0, 0)

    // food1+food2 available + pottery → complementary pottery (not food2)
    var inv = __test_bazaar_pick_next_inventory(bid)
    if (inv != 4) {
        __log_info_native('[test:77] complementary want pottery(4) got ' + inv)
        finish()
        return
    }
    __log_marker('bazaar_multi_complementary_ok')
    __test77_ok.complementary = true

    inv = __test_bazaar_pick_next_inventory(bid)
    if (inv != 4) {
        __log_info_native('[test:77] pottery must beat food2, got ' + inv)
        finish()
        return
    }
    __log_marker('bazaar_multi_pottery_beats_food2_ok')
    __test77_ok.beats = true

    // Fallback: goods gated (demand 0) → foods-only → food2 (index 1)
    __test_bazaar_set_good_demands(bid, 0, 0, 0, 0)
    inv = __test_bazaar_pick_next_inventory(bid)
    if (inv != 1) {
        __log_info_native('[test:77] fallback want food2(1) got ' + inv)
        finish()
        return
    }
    __log_marker('bazaar_multi_fallback_food2_ok')
    __test77_ok.fallback = true

    // Failed complementary must not burn demand (goods probe fails → food fallback).
    if (!__test_storage_yard_remove_resource(sy, RESOURCE_POTTERY, 9999)) {
        __log_info_native('[test:77] remove pottery failed')
        finish()
        return
    }
    __test_bazaar_set_good_demands(bid, 5, 0, 0, 0)
    inv = __test_bazaar_pick_next_inventory(bid)
    if (inv != 1) {
        __log_info_native('[test:77] fail-complementary fallback want food2(1) got ' + inv)
        finish()
        return
    }
    if (__test_bazaar_pottery_demand(bid) != 5) {
        __log_info_native('[test:77] demand must stay 5 after failed goods probe, got '
            + __test_bazaar_pottery_demand(bid))
        finish()
        return
    }
    __log_marker('bazaar_multi_demand_no_burn_on_fail_ok')
    __test77_ok.demand_fail = true

    // Demand freeze while buyer out; tick when none out.
    if (!__test_storage_yard_add_resource(sy, RESOURCE_POTTERY, 400)) {
        __log_info_native('[test:77] restore pottery failed')
        finish()
        return
    }
    __test_bazaar_set_good_demands(bid, 5, 0, 0, 0)
    __test_bazaar_pick_next_inventory(bid) // buyer still out → no tick
    if (__test_bazaar_pottery_demand(bid) != 5) {
        __log_info_native('[test:77] demand freeze want 5 got ' + __test_bazaar_pottery_demand(bid))
        finish()
        return
    }
    __test_figure_set_action(fid_a, -1)
    __test_bazaar_reclaim_slot(bid, BUILDING_SLOT_MARKET_BUYER)
    if (__test_bazaar_count_buyers(bid) != 0) {
        __log_info_native('[test:77] expected 0 buyers before demand tick')
        finish()
        return
    }
    __test_bazaar_set_good_demands(bid, 5, 0, 0, 0)
    __test_bazaar_pick_next_inventory(bid)
    if (__test_bazaar_pottery_demand(bid) != 4) {
        __log_info_native('[test:77] demand tick want 4 got ' + __test_bazaar_pottery_demand(bid))
        finish()
        return
    }
    __log_marker('bazaar_multi_demand_freeze_ok')
    __test77_ok.demand = true

    // OFF path: spawn only uses slot 1, never slot 3.
    game_features.set('gameplay_change_bazaar_multi_buyers', false)
    __test_bazaar_reclaim_slot(bid, BUILDING_SLOT_MARKET_BUYER)
    __test_bazaar_reclaim_slot(bid, BUILDING_SLOT_MARKET_BUYER_2)
    __test_bazaar_set_good_demands(bid, 10, 0, 0, 0)
    if (!__test_bazaar_force_spawn(bid)) {
        __log_info_native('[test:77] force spawn failed')
        finish()
        return
    }
    var s1 = __test_bazaar_slot_figure(bid, BUILDING_SLOT_MARKET_BUYER)
    var s3 = __test_bazaar_slot_figure(bid, BUILDING_SLOT_MARKET_BUYER_2)
    if (!s1) {
        __log_info_native('[test:77] OFF spawn should fill slot 1')
        finish()
        return
    }
    if (s3) {
        __log_info_native('[test:77] OFF must not spawn on slot 3, got ' + s3)
        finish()
        return
    }
    // Second spawn while slot1 busy must not fill slot 3.
    __test_bazaar_force_spawn(bid)
    s3 = __test_bazaar_slot_figure(bid, BUILDING_SLOT_MARKET_BUYER_2)
    if (s3) {
        __log_info_native('[test:77] OFF second spawn wrote slot 3')
        finish()
        return
    }
    __log_marker('bazaar_multi_off_slot1_ok')
    __test77_ok.offslot = true

    // OFF must poof a leftover slot-3 buyer on spawn.
    __test_bazaar_reclaim_slot(bid, BUILDING_SLOT_MARKET_BUYER)
    var orphan = __test_bazaar_attach_buyer(bid, BUILDING_SLOT_MARKET_BUYER_2, 0)
    if (!orphan) {
        __log_info_native('[test:77] orphan slot3 attach failed')
        finish()
        return
    }
    __test_bazaar_force_spawn(bid)
    s3 = __test_bazaar_slot_figure(bid, BUILDING_SLOT_MARKET_BUYER_2)
    if (s3) {
        __log_info_native('[test:77] OFF spawn must clear orphan slot3, got ' + s3)
        finish()
        return
    }
    __log_marker('bazaar_multi_off_clears_slot3_ok')
    __test77_ok.offclear = true

    finish()
}

function check_valid() {
    if (!__test77_ok.flag || !__test77_ok.slot || !__test77_ok.maxb
        || !__test77_ok.slot3 || !__test77_ok.slot2 || !__test77_ok.count
        || !__test77_ok.finished || !__test77_ok.cooldown
        || !__test77_ok.reclaim || !__test77_ok.exclude || !__test77_ok.complementary
        || !__test77_ok.beats || !__test77_ok.fallback || !__test77_ok.demand_fail
        || !__test77_ok.demand || !__test77_ok.offslot || !__test77_ok.offclear) {
        __log_info_native('[test:77] one or more phases failed')
        return false
    }

    var markers = [
        'bazaar_multi_flag_off_ok',
        'bazaar_multi_slot_const_ok',
        'bazaar_multi_max_buyers_ok',
        'bazaar_multi_slot3_alive_ok',
        'bazaar_multi_slot2_poof_ok',
        'bazaar_multi_count_ok',
        'bazaar_multi_finished_not_counted_ok',
        'bazaar_multi_cooldown_last_ok',
        'bazaar_multi_reclaim_ok',
        'bazaar_multi_exclude_ok',
        'bazaar_multi_complementary_ok',
        'bazaar_multi_pottery_beats_food2_ok',
        'bazaar_multi_fallback_food2_ok',
        'bazaar_multi_demand_no_burn_on_fail_ok',
        'bazaar_multi_demand_freeze_ok',
        'bazaar_multi_off_slot1_ok',
        'bazaar_multi_off_clears_slot3_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:77] missing marker: ' + marker)
            return false
        }
    }
    return true
}

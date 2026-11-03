// OG market buyer (FIG_BUYER): dual food/goods slots, shopping list.
// Markers:
//   [test-marker] buyer_og_flag_off_ok
//   [test-marker] buyer_og_food_list_ok
//   [test-marker] buyer_og_goods_slot_ok
//   [test-marker] buyer_og_dual_spawn_ok
//   [test-marker] buyer_og_multi_untouched_ok

var __test235_ok = {
    flag: false,
    food_list: false,
    goods: false,
    dual: false,
    multi: false
}

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
    __log_info_native('[test:235] market buyer OG trip')
    test_ensure_city_session('data/default.map')

    var flag_prev = game_features.get('gameplay_change_bazaar_multi_buyers')
    game_features.set('gameplay_change_bazaar_multi_buyers', false)
    if (game_features.get('gameplay_change_bazaar_multi_buyers')) {
        __log_info_native('[test:235] failed to clear multi flag')
        __test_signal_ready()
        return
    }
    __log_marker('buyer_og_flag_off_ok')
    __test235_ok.flag = true

    __test_set_allowed_food(0, RESOURCE_GRAIN)
    __test_set_allowed_food(1, RESOURCE_FIGS)

    function finish() {
        game_features.set('gameplay_change_bazaar_multi_buyers', flag_prev)
        __test_signal_ready()
    }

    var bid = __test_building_create(BUILDING_BAZAAR, -1, -1)
    var gid = __test_building_create(BUILDING_GRANARY, -1, -1)
    var sid = __test_building_create(BUILDING_STORAGE_YARD, -1, -1)
    if (!bid || !gid || !sid) {
        __log_info_native('[test:235] create buildings failed')
        finish()
        return
    }

    var bazaar = city.get_building(bid)
    var granary = city.get_building(gid)
    var sy = city.get_building(sid)

    var net = grant_granary_road(gid)
    var bt = __building_tile(bid)
    var st = __building_tile(sid)
    terrain.add({ x: bt.x, y: bt.y - 1 }, TERRAIN_ROAD)
    terrain.add({ x: st.x, y: st.y - 1 }, TERRAIN_ROAD)
    __test_update_road_network()
    bazaar.has_road_access = true
    bazaar.road_network_id = net
    sy.has_road_access = true
    sy.road_network_id = net
    sy.distance_from_entry = 10
    granary.distance_from_entry = 10
    bazaar.distance_from_entry = 10
    bazaar.num_workers = 5
    __test_bazaar_link_storage(bid, sid)

    if (!__test_granary_add_allowed_food(gid, 0, 400)) {
        __log_info_native('[test:235] granary food0 failed')
        finish()
        return
    }
    if (!__test_granary_add_allowed_food(gid, 1, 400)) {
        __log_info_native('[test:235] granary food1 failed')
        finish()
        return
    }
    if (!__test_storage_yard_add_resource(sid, RESOURCE_POTTERY, 400)) {
        __log_info_native('[test:235] pottery failed')
        finish()
        return
    }

    __test_bazaar_set_inventory(bid, 0, 0)
    __test_bazaar_set_inventory(bid, 1, 0)
    __test_bazaar_set_inventory(bid, 4, 0)
    __test_bazaar_set_good_demands(bid, 10, 0, 0, 0)

    var food_dest = __test_bazaar_og_food_destination(bid)
    if (!food_dest) {
        __log_info_native('[test:235] og food destination missing')
        finish()
        return
    }
    __log_marker('buyer_og_food_list_ok')
    __test235_ok.food_list = true

    var goods_dest = __test_bazaar_og_goods_destination(bid)
    if (!goods_dest) {
        __log_info_native('[test:235] og goods destination missing')
        finish()
        return
    }
    __log_marker('buyer_og_goods_slot_ok')
    __test235_ok.goods = true

    if (!__test_bazaar_force_spawn(bid)) {
        __log_info_native('[test:235] force spawn failed')
        finish()
        return
    }
    var food_fid = __test_bazaar_slot_figure(bid, BUILDING_SLOT_MARKET_BUYER)
    var goods_fid = __test_bazaar_slot_figure(bid, BUILDING_SLOT_MARKET_BUYER_2)
    if (!food_fid || !goods_fid) {
        __log_info_native('[test:235] dual spawn want food+goods, got '
            + food_fid + '/' + goods_fid)
        finish()
        return
    }
    if (!__test_market_buyer_og_is_food_trip(food_fid)) {
        __log_info_native('[test:235] food buyer not food trip')
        finish()
        return
    }
    if (__test_market_buyer_og_is_food_trip(goods_fid) != 0) {
        __log_info_native('[test:235] goods buyer not goods trip')
        finish()
        return
    }
    if (__test_market_buyer_og_resources(food_fid, 0) < 0) {
        __log_info_native('[test:235] food shopping list empty')
        finish()
        return
    }
    __log_marker('buyer_og_dual_spawn_ok')
    __test235_ok.dual = true

    game_features.set('gameplay_change_bazaar_multi_buyers', true)
    __test_bazaar_reclaim_slot(bid, BUILDING_SLOT_MARKET_BUYER)
    __test_bazaar_reclaim_slot(bid, BUILDING_SLOT_MARKET_BUYER_2)
    __test_bazaar_set_inventory(bid, 0, 0)
    __test_bazaar_set_inventory(bid, 4, 0)
    __test_bazaar_set_good_demands(bid, 10, 0, 0, 0)
    if (!__test_bazaar_force_spawn(bid)) {
        __log_info_native('[test:235] multi spawn failed')
        finish()
        return
    }
    var mid = __test_bazaar_slot_figure(bid, BUILDING_SLOT_MARKET_BUYER)
    if (!mid) {
        __log_info_native('[test:235] multi should spawn one buyer')
        finish()
        return
    }
    if (__test_market_buyer_og_storages_visited(mid) != 0) {
        __log_info_native('[test:235] multi buyer should start with 0 visits')
        finish()
        return
    }
    __log_marker('buyer_og_multi_untouched_ok')
    __test235_ok.multi = true

    finish()
}

function check_valid() {
    if (!__test235_ok.flag || !__test235_ok.food_list || !__test235_ok.goods
        || !__test235_ok.dual || !__test235_ok.multi) {
        __log_info_native('[test:235] one or more phases failed')
        return false
    }
    var markers = [
        'buyer_og_flag_off_ok',
        'buyer_og_food_list_ok',
        'buyer_og_goods_slot_ok',
        'buyer_og_dual_spawn_ok',
        'buyer_og_multi_untouched_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:235] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

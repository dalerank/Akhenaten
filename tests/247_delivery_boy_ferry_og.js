// FIG_GRANARY_BOY / FIGURE_DELIVERY_BOY ferry OG (carriers.c figure_delivery_boy_action):
// - no follow while buyer WAIT_FOR_FERRY / ON_FERRY
// - invisible while buyer ON_FERRY
// - invisible if leader is invisible
// Markers:
//   [test-marker] delivery_boy_ferry_wait_no_follow_ok
//   [test-marker] delivery_boy_ferry_wait_visible_ok
//   [test-marker] delivery_boy_ferry_ride_invisible_ok
//   [test-marker] delivery_boy_ferry_leader_ghost_ok
//   [test-marker] delivery_boy_ferry_clear_visible_ok

var ACTION_6_ON_FERRY = 6
var ACTION_7_WAIT_FOR_FERRY = 7
var ACTION_146_MARKET_BUYER_RETURNING = 146

var __test247_ok = false
var __test247_alone_prev = false
var __test247_runaway_prev = false

function test247_finish() {
    game_features.set('gameplay_change_delivery_boy_goes_to_market_alone', __test247_alone_prev)
    game_features.set('gameplay_change_follower_runaway', __test247_runaway_prev)
    __test_signal_ready()
}

function test247_fail(msg) {
    __log_info_native('[test:247] ' + msg)
    test247_finish()
}

function run_test() {
    __log_info_native('[test:247] delivery boy ferry OG')

    test_ensure_city_session('data/default.map')

    __test247_alone_prev = game_features.get('gameplay_change_delivery_boy_goes_to_market_alone')
    __test247_runaway_prev = game_features.get('gameplay_change_follower_runaway')
    game_features.set('gameplay_change_delivery_boy_goes_to_market_alone', false)
    game_features.set('gameplay_change_follower_runaway', false)

    var bid = __test_building_create(BUILDING_BAZAAR, -1, -1)
    if (!bid) {
        return test247_fail('bazaar create failed')
    }
    var tile = __building_tile(bid)
    if (!tile) {
        return test247_fail('bazaar tile missing')
    }

    // ROADS walkers poof on the first off-road tick without a destination.
    terrain.add({ x: tile.x + 2, y: tile.y }, TERRAIN_ROAD)
    terrain.add({ x: tile.x + 3, y: tile.y }, TERRAIN_ROAD)
    terrain.add({ x: tile.x + 4, y: tile.y }, TERRAIN_ROAD)
    __test_update_road_network()

    var buyer = test_figure_create(FIGURE_MARKET_BUYER, tile.x + 2, tile.y)
    var boy1 = test_figure_create(FIGURE_DELIVERY_BOY, tile.x + 3, tile.y)
    var boy2 = test_figure_create(FIGURE_DELIVERY_BOY, tile.x + 4, tile.y)
    if (!buyer || !boy1 || !boy2) {
        return test247_fail('figure create failed')
    }

    test_figure_set_home(buyer, bid)
    test_figure_set_home(boy1, bid)
    test_figure_set_home(boy2, bid)
    __test_figure_set_leading(boy1, buyer)
    __test_figure_set_leading(boy2, boy1)
    __test_figure_set_collecting_item(boy1, 0)
    __test_figure_set_collecting_item(boy2, 0)
    test_figure_set_force_valid_animation(buyer, true)
    test_figure_set_force_valid_animation(boy1, true)
    test_figure_set_force_valid_animation(boy2, true)

    // WAIT_FOR_FERRY: no follow (tile stays), still visible
    __test_figure_set_action(buyer, ACTION_7_WAIT_FOR_FERRY)
    var before = __figure_get_tile(boy1)
    __test_figure_action_perform(boy1)
    var after = __figure_get_tile(boy1)
    if (!before || !after || before.x != after.x || before.y != after.y) {
        return test247_fail('wait: boy should not follow, tile '
            + (before ? before.x + ',' + before.y : '?') + ' -> '
            + (after ? after.x + ',' + after.y : '?'))
    }
    if (__test_figure_is_visible(boy1) != 1) {
        return test247_fail('wait: boy should stay visible')
    }
    __log_marker('delivery_boy_ferry_wait_no_follow_ok')
    __log_marker('delivery_boy_ferry_wait_visible_ok')

    // ON_FERRY: invisible
    __test_figure_set_action(buyer, ACTION_6_ON_FERRY)
    __test_figure_set_visible(boy1, 1)
    __test_figure_action_perform(boy1)
    if (__test_figure_is_visible(boy1) != 0) {
        return test247_fail('ride: boy should be invisible')
    }
    __log_marker('delivery_boy_ferry_ride_invisible_ok')

    // Leader ghost while buyer not on ferry: trailing boy inherits
    __test_figure_set_action(buyer, ACTION_146_MARKET_BUYER_RETURNING)
    __test_figure_set_visible(boy1, 0)
    __test_figure_set_visible(boy2, 1)
    __test_figure_action_perform(boy2)
    if (__test_figure_is_visible(boy2) != 0) {
        return test247_fail('leader ghost: boy2 should be invisible')
    }
    __log_marker('delivery_boy_ferry_leader_ghost_ok')

    // Clear: buyer returning, leader visible → boy visible again
    __test_figure_set_visible(boy1, 1)
    __test_figure_set_visible(boy2, 0)
    __test_figure_action_perform(boy2)
    if (__test_figure_is_visible(boy2) != 1) {
        return test247_fail('clear: boy2 should be visible again')
    }
    __log_marker('delivery_boy_ferry_clear_visible_ok')

    __test247_ok = true
    test247_finish()
}

function check_valid() {
    return __test247_ok
        && __test_find_inlog('[test-marker] delivery_boy_ferry_wait_no_follow_ok')
        && __test_find_inlog('[test-marker] delivery_boy_ferry_wait_visible_ok')
        && __test_find_inlog('[test-marker] delivery_boy_ferry_ride_invisible_ok')
        && __test_find_inlog('[test-marker] delivery_boy_ferry_leader_ghost_ok')
        && __test_find_inlog('[test-marker] delivery_boy_ferry_clear_visible_ok')
}

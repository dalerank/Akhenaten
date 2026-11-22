// OG ferry spawn_ferry delay by worker % (3/7/15/29/-1) + CREATED→crossing.
// Pair sits on opposite banks of a synthetic N–S river (bridge channel).
// Markers:
//   [test-marker] test210_spawn_delay_full_staff
//   [test-marker] test210_created_empty_returns
//   [test-marker] test210_created_with_passenger_crosses

var __test210_ok = false

function test210_fail(msg) {
    __log_info_native('[test:210] FAIL: ' + msg)
    __test_signal_ready()
}

function test210_place_pair() {
    var pair = test_ferry_pair_place()
    if (!pair) {
        return null
    }
    var north = pair.first
    var south = pair.second
    var path = __test_ferry_water_path(north, south) | 0
    var pa = __ferry_partner_id(north) | 0
    var pb = __ferry_partner_id(south) | 0
    if (pa != south || pb != north) {
        var nt = __building_tile(north)
        var st = __building_tile(south)
        __log_info_native('[test:210] no partner route north=' + north + '@' + nt.x + ',' + nt.y
            + ' south=' + south + '@' + st.x + ',' + st.y
            + ' pa=' + pa + ' pb=' + pb + ' path=' + path)
        return null
    }
    return { north: north, south: south }
}

function test210_make_boat(bid, action) {
    var tile = __building_tile(bid)
    var boat = test_figure_create(FIGURE_FERRY_BOAT, tile.x, tile.y)
    if (!boat) {
        return 0
    }
    test_figure_set_home(boat, bid)
    __test_building_set_figure_slot(bid, BUILDING_SLOT_BOAT, boat)
    __test_figure_set_action(boat, action)
    return boat
}

function run_test() {
    __log_info_native('[test:210] ferry spawn delay + CREATED crossing')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_FERRY, true)

    var pair = test210_place_pair()
    if (!pair) {
        return test210_fail('place ferry pair across river failed')
    }

    var bid = pair.north
    var partner = pair.south
    // laborers[5] — full staff → delay 3
    __test_building_set_workers(bid, 5)
    __test_building_set_workers(partner, 5)
    __test_building_force_road_access(bid)

    // Warm to just below full-staff delay (3): days 1..3 hold, day 4 spawns.
    __test_building_set_figure_spawn_delay(bid, 0)
    __test_building_spawn_figure(bid)
    if (__test_building_figure_id(bid, BUILDING_SLOT_BOAT) != 0) {
        return test210_fail('full staff should not spawn on first tick')
    }
    if (__test_building_figure_spawn_delay(bid) != 1) {
        return test210_fail('after 1st tick delay want 1, got ' + __test_building_figure_spawn_delay(bid))
    }

    __test_building_set_figure_spawn_delay(bid, 3)
    __test_building_spawn_figure(bid)
    var boat = __test_building_figure_id(bid, BUILDING_SLOT_BOAT)
    if (!boat) {
        return test210_fail('expected boat spawn after delay>3')
    }
    if (__test_building_figure_spawn_delay(bid) != 0) {
        return test210_fail('spawn should clear delay, got ' + __test_building_figure_spawn_delay(bid))
    }
    if (__test_figure_get_action(boat) != ACTION_0_FERRY_BOAT_CREATED) {
        return test210_fail('spawned boat should start CREATED, got ' + __test_figure_get_action(boat))
    }
    __log_marker('test210_spawn_delay_full_staff')

    // Empty CREATED → CROSSING_BACK (RETURNING) same tick; not WAITING.
    __test_figure_action_perform(boat)
    if (__test_figure_is_dying(boat)) {
        return test210_fail('staffed CREATED should not sink')
    }
    var after_created = __test_figure_get_action(boat)
    if (after_created != ACTION_3_FERRY_BOAT_RETURNING) {
        return test210_fail('empty CREATED should become RETURNING, got ' + after_created)
    }
    __log_marker('test210_created_empty_returns')

    // Same boat, reset to CREATED with a passenger → CROSSING (GOING).
    __test_figure_set_action(boat, ACTION_0_FERRY_BOAT_CREATED)
    var tile = __building_tile(bid)
    var buyer = test_figure_create(FIGURE_MARKET_BUYER, tile.x + 1, tile.y)
    if (!buyer) {
        return test210_fail('create passenger failed')
    }
    if (!__test_ferry_boat_board_passenger(boat, buyer)) {
        return test210_fail('board passenger failed')
    }
    if ((__test_ferry_boat_passenger_count(boat) | 0) < 1) {
        return test210_fail('boat should carry passenger before CREATED tick')
    }
    if ((__ferry_partner_id(bid) | 0) != partner) {
        return test210_fail('partner lost before passenger CREATED tick')
    }
    __test_figure_action_perform(boat)
    if (__test_figure_is_dying(boat)) {
        return test210_fail('passenger CREATED should not sink')
    }
    after_created = __test_figure_get_action(boat)
    if (after_created != ACTION_1_FERRY_BOAT_GOING_TO_DESTINATION) {
        return test210_fail('passenger CREATED should become GOING, got ' + after_created)
    }
    __log_marker('test210_created_with_passenger_crosses')

    __test210_ok = true
    __log_info_native('[test:210] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test210_ok) {
        return false
    }
    return __test_find_inlog('[test-marker] test210_spawn_delay_full_staff')
        && __test_find_inlog('[test-marker] test210_created_empty_returns')
        && __test_find_inlog('[test-marker] test210_created_with_passenger_crosses')
}

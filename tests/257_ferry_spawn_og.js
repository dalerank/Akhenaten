// OG ferry spawn_ferry delay by worker % (3/7/15/29/-1) + CREATED→crossing.
// Pair sits on opposite banks of a synthetic N–S river (bridge channel).
// Markers:
//   [test-marker] test257_spawn_delay_full_staff
//   [test-marker] test257_created_empty_returns
//   [test-marker] test257_created_with_passenger_crosses

var __test257_ok = false

function test257_fail(msg) {
    __log_info_native('[test:257] FAIL: ' + msg)
    __test_signal_ready()
}

function test257_try_place_ferry(x, y) {
    city_planner.update(x, y)
    if (city_planner.can_be_placed() != CAN_PLACE) {
        return 0
    }
    city_planner.construction_start(x, y)
    city_planner.construction_update(x, y)
    city_planner.construction_finalize()
    var bid = city_planner.last_created_building_id()
    city_planner.validate_last_created()
    if (bid && __building_type(bid) == BUILDING_FERRY) {
        return bid
    }
    return 0
}

function test257_place_pair() {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    // N–S river: water [cy .. cy+len), north bank cy-1, south bank cy+len.
    var river_len = 5
    var river_w = 5
    var start = test_prepare_bridge_channel(cx, cy, river_w, river_len)
    __test_set_scenario_river_points(start.x, start.y + 2, start.x, start.y + 2)
    __test_map_routing_update_water()

    if (!test_planner_enter_build_mode(BUILDING_FERRY)) {
        return null
    }

    var north = 0
    var north_cands = [
        { x: cx - 1, y: cy - 1 },
        { x: cx - 2, y: cy - 1 },
        { x: cx, y: cy - 1 }
    ]
    for (var i = 0; i < north_cands.length && !north; i++) {
        north = test257_try_place_ferry(north_cands[i].x, north_cands[i].y)
    }

    // North ferry at cy-1 straddles land/water; south mirror is cy+len-1.
    var south_y = cy + river_len - 1
    var south = 0
    var south_cands = [
        { x: cx - 1, y: south_y },
        { x: cx - 2, y: south_y },
        { x: cx, y: south_y },
        { x: cx - 1, y: south_y + 1 },
        { x: cx - 2, y: south_y + 1 }
    ]
    for (var j = 0; j < south_cands.length && !south; j++) {
        south = test257_try_place_ferry(south_cands[j].x, south_cands[j].y)
    }

    test_planner_exit_build_mode()
    if (!north || !south) {
        __log_info_native('[test:257] place failed north=' + north + ' south=' + south
            + ' river=' + start.x + ',' + start.y + ' len=' + river_len)
        return null
    }

    var path = __test_ferry_water_path(north, south) | 0
    var pa = __ferry_partner_id(north) | 0
    var pb = __ferry_partner_id(south) | 0
    if (pa != south || pb != north) {
        var nt = __building_tile(north)
        var st = __building_tile(south)
        __log_info_native('[test:257] no partner route north=' + north + '@' + nt.x + ',' + nt.y
            + ' south=' + south + '@' + st.x + ',' + st.y
            + ' pa=' + pa + ' pb=' + pb + ' path=' + path)
        return null
    }
    return { north: north, south: south }
}

function test257_make_boat(bid, action) {
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
    __log_info_native('[test:257] ferry spawn delay + CREATED crossing')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_FERRY, true)

    var pair = test257_place_pair()
    if (!pair) {
        return test257_fail('place ferry pair across river failed')
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
        return test257_fail('full staff should not spawn on first tick')
    }
    if (__test_building_figure_spawn_delay(bid) != 1) {
        return test257_fail('after 1st tick delay want 1, got ' + __test_building_figure_spawn_delay(bid))
    }

    __test_building_set_figure_spawn_delay(bid, 3)
    __test_building_spawn_figure(bid)
    var boat = __test_building_figure_id(bid, BUILDING_SLOT_BOAT)
    if (!boat) {
        return test257_fail('expected boat spawn after delay>3')
    }
    if (__test_building_figure_spawn_delay(bid) != 0) {
        return test257_fail('spawn should clear delay, got ' + __test_building_figure_spawn_delay(bid))
    }
    if (__test_figure_get_action(boat) != ACTION_0_FERRY_BOAT_CREATED) {
        return test257_fail('spawned boat should start CREATED, got ' + __test_figure_get_action(boat))
    }
    __log_marker('test257_spawn_delay_full_staff')

    // Empty CREATED → CROSSING_BACK (RETURNING) same tick; not WAITING.
    __test_figure_action_perform(boat)
    if (__test_figure_is_dying(boat)) {
        return test257_fail('staffed CREATED should not sink')
    }
    var after_created = __test_figure_get_action(boat)
    if (after_created != ACTION_3_FERRY_BOAT_RETURNING) {
        return test257_fail('empty CREATED should become RETURNING, got ' + after_created)
    }
    __log_marker('test257_created_empty_returns')

    // Same boat, reset to CREATED with a passenger → CROSSING (GOING).
    __test_figure_set_action(boat, ACTION_0_FERRY_BOAT_CREATED)
    var tile = __building_tile(bid)
    var buyer = test_figure_create(FIGURE_MARKET_BUYER, tile.x + 1, tile.y)
    if (!buyer) {
        return test257_fail('create passenger failed')
    }
    if (!__test_ferry_boat_board_passenger(boat, buyer)) {
        return test257_fail('board passenger failed')
    }
    if ((__test_ferry_boat_passenger_count(boat) | 0) < 1) {
        return test257_fail('boat should carry passenger before CREATED tick')
    }
    if ((__ferry_partner_id(bid) | 0) != partner) {
        return test257_fail('partner lost before passenger CREATED tick')
    }
    __test_figure_action_perform(boat)
    if (__test_figure_is_dying(boat)) {
        return test257_fail('passenger CREATED should not sink')
    }
    after_created = __test_figure_get_action(boat)
    if (after_created != ACTION_1_FERRY_BOAT_GOING_TO_DESTINATION) {
        return test257_fail('passenger CREATED should become GOING, got ' + after_created)
    }
    __log_marker('test257_created_with_passenger_crosses')

    __test257_ok = true
    __log_info_native('[test:257] PASS')
    __test_signal_ready()
}

function check_valid() {
    if (!__test257_ok) {
        return false
    }
    return __test_find_inlog('[test-marker] test257_spawn_delay_full_staff')
        && __test_find_inlog('[test-marker] test257_created_empty_returns')
        && __test_find_inlog('[test-marker] test257_created_with_passenger_crosses')
}

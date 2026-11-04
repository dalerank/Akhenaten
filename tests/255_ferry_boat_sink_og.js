// FIG_FERRY_BOAT OG sink + staff slowness (boats.c ferry_sink / ferry_move).
// Markers:
//   [test-marker] test255_config_defaults
//   [test-marker] test255_unstaffed_waiting_sinks
//   [test-marker] test255_created_unstaffed_sinks
//   [test-marker] test255_no_partner_sinks
//   [test-marker] test255_passenger_dies_with_boat
//   [test-marker] test255_follower_dies_with_boat
//   [test-marker] test255_full_staff_no_slowness_counter
//   [test-marker] test255_zero_staff_skips_nth_tick
//   [test-marker] test255_sinking_then_bubbles_ticks

var __test255_ok = false

function test255_fail(msg) {
    __log_info_native('[test:255] FAIL: ' + msg)
    __test_signal_ready()
}

function test255_make_boat(bid, action) {
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
    __log_info_native('[test:255] ferry boat OG sink + slowness')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_FERRY, true)

    if (dcy_get(figure_ferry_boat.sinking_ticks) != 33
        || dcy_get(figure_ferry_boat.bubbles_frames) != 23
        || dcy_get(figure_ferry_boat.slowness_min) != 2
        || dcy_get(figure_ferry_boat.slowness_step) != 10
        || dcy_get(figure_ferry_boat.tick_counter_limit) != 100) {
        return test255_fail('config defaults mismatch sinking=' + dcy_get(figure_ferry_boat.sinking_ticks)
            + ' bubbles=' + dcy_get(figure_ferry_boat.bubbles_frames)
            + ' min=' + dcy_get(figure_ferry_boat.slowness_min)
            + ' step=' + dcy_get(figure_ferry_boat.slowness_step)
            + ' limit=' + dcy_get(figure_ferry_boat.tick_counter_limit))
    }
    __log_marker('test255_config_defaults')

    var bid = test_shoreline_building_place(BUILDING_FERRY, 2)
    if (!bid) {
        return test255_fail('place ferry failed')
    }
    var tile = __building_tile(bid)

    // --- WAITING + unstaffed → sink ---
    __test_building_set_workers(bid, 8)
    var boat = test255_make_boat(bid, ACTION_4_FERRY_BOAT_WAITING)
    if (!boat) {
        return test255_fail('create waiting boat failed')
    }

    var buyer = test_figure_create(FIGURE_MARKET_BUYER, tile.x + 1, tile.y)
    var boy = test_figure_create(FIGURE_DELIVERY_BOY, tile.x + 2, tile.y)
    if (!buyer || !boy) {
        return test255_fail('create buyer/delivery boy failed')
    }
    __test_figure_set_leading(boy, buyer)
    if (!__test_ferry_boat_board_passenger(boat, buyer)) {
        return test255_fail('board market buyer failed')
    }
    if (__test_ferry_boat_passenger_count(boat) < 1) {
        return test255_fail('boarded passenger missing from boat slots')
    }

    __test_building_set_workers(bid, 0)
    // Call sink() directly — same path WAITING uses when unstaffed / no partner.
    __test_ferry_boat_sink(boat)
    if (!__test_figure_is_dying(boat)) {
        return test255_fail('unstaffed waiting should sink to DYING/CORPSE')
    }
    __log_marker('test255_unstaffed_waiting_sinks')

    if (__test_figure_is_alive(buyer)) {
        return test255_fail('passenger should die with boat (passengers='
            + __test_ferry_boat_passenger_count(boat) + ')')
    }
    __log_marker('test255_passenger_dies_with_boat')

    if (__test_figure_is_alive(boy)) {
        return test255_fail('delivery-boy follower should die with boat')
    }
    __log_marker('test255_follower_dies_with_boat')

    // sinking → bubbles tick phases (corpse handler advances wait_ticks)
    var saw_sinking = false
    var saw_bubbles = false
    for (var t = 0; t < 40; t++) {
        if (!__test_figure_is_dying(boat)) {
            break
        }
        __test_figure_action_perform_dying(boat)
        if (t < 32) {
            saw_sinking = true
        } else {
            saw_bubbles = true
        }
    }
    if (!saw_sinking || !saw_bubbles) {
        return test255_fail('expected sinking then bubbles phase')
    }
    __log_marker('test255_sinking_then_bubbles_ticks')

    // --- CREATED + unstaffed → sink ---
    __test_building_set_workers(bid, 8)
    var boat2 = test255_make_boat(bid, ACTION_0_FERRY_BOAT_CREATED)
    if (!boat2) {
        return test255_fail('create CREATED boat failed')
    }
    __test_building_set_workers(bid, 0)
    __test_figure_action_perform(boat2)
    if (!__test_figure_is_dying(boat2)) {
        return test255_fail('CREATED unstaffed should sink')
    }
    __log_marker('test255_created_unstaffed_sinks')

    // --- staffed but no partner → sink ---
    __test_building_set_workers(bid, 8)
    var boat3 = test255_make_boat(bid, ACTION_4_FERRY_BOAT_WAITING)
    if (!boat3) {
        return test255_fail('create no-partner boat failed')
    }
    __test_figure_action_perform(boat3)
    if (!__test_figure_is_dying(boat3)) {
        return test255_fail('no partner should sink')
    }
    __log_marker('test255_no_partner_sinks')

    // --- staff slowness (ferry_move) ---
    __test_building_set_workers(bid, 8)
    var boat4 = test255_make_boat(bid, ACTION_1_FERRY_BOAT_GOING_TO_DESTINATION)
    if (!boat4) {
        return test255_fail('create slowness boat failed')
    }
    __test_figure_set_wait_ticks(boat4, 0)
    var w_full = __test_ferry_boat_slowness_step(boat4)
    if (w_full != 0) {
        return test255_fail('full staff should not bump wait_ticks, got ' + w_full)
    }
    __log_marker('test255_full_staff_no_slowness_counter')

    // 0% staff → slowness 10: ticks 1..9 move (counter grows), tick 10 skips move.
    __test_building_set_workers(bid, 0)
    __test_figure_set_wait_ticks(boat4, 8)
    var w9 = __test_ferry_boat_slowness_step(boat4)
    if (w9 != 9) {
        return test255_fail('zero-staff tick expect wait=9 got ' + w9)
    }
    var w10 = __test_ferry_boat_slowness_step(boat4)
    if (w10 != 10) {
        return test255_fail('zero-staff skip tick expect wait=10 got ' + w10)
    }
    __log_marker('test255_zero_staff_skips_nth_tick')

    __test255_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test255_ok
        && __test_find_inlog('[test-marker] test255_config_defaults')
        && __test_find_inlog('[test-marker] test255_unstaffed_waiting_sinks')
        && __test_find_inlog('[test-marker] test255_created_unstaffed_sinks')
        && __test_find_inlog('[test-marker] test255_no_partner_sinks')
        && __test_find_inlog('[test-marker] test255_passenger_dies_with_boat')
        && __test_find_inlog('[test-marker] test255_follower_dies_with_boat')
        && __test_find_inlog('[test-marker] test255_full_staff_no_slowness_counter')
        && __test_find_inlog('[test-marker] test255_zero_staff_skips_nth_tick')
        && __test_find_inlog('[test-marker] test255_sinking_then_bubbles_ticks')
}

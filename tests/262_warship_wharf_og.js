// OG warship wharf (shared spawn_wharf): clear stale boat slot, labor seeker when
// houses_covered < 51, and request a warship when staffed without a boat.
// Markers:
//   [test-marker] warship_wharf_og_clear_slot
//   [test-marker] warship_wharf_og_labor_seeker
//   [test-marker] warship_wharf_og_request_ship

var __test262_ok = false

function test262_fail(msg) {
    __log_info_native('[test:262] ' + msg)
    __test_signal_ready()
}

function test262_place_wharf() {
    __scenario_building_allow(BUILDING_WARSHIP_WHARF, true)
    var bid = test_shoreline_building_place(BUILDING_WARSHIP_WHARF, 3)
    if (!bid) {
        return 0
    }
    __test_building_set_workers(bid, 15)
    __test_building_force_road_access(bid)
    return bid
}

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __test_set_city_population(500)

    var bid = test262_place_wharf()
    if (!bid) {
        test262_fail('place failed')
        return
    }

    var junk = test_figure_create(FIGURE_CART_PUSHER, 10, 10)
    if (!junk) {
        test262_fail('junk figure create failed')
        return
    }
    __test_building_set_figure_slot(bid, BUILDING_SLOT_BOAT, junk)
    __test_building_set_houses_covered(bid, 100)
    __test_warship_wharf_spawn_figure(bid)
    if (__test_building_figure_id(bid, BUILDING_SLOT_BOAT) != 0) {
        test262_fail('stale boat slot not cleared, got '
            + __test_building_figure_id(bid, BUILDING_SLOT_BOAT))
        return
    }
    __log_info_native('[test-marker] warship_wharf_og_clear_slot')

    city.figures.remove_figures(FIGURE_LABOR_SEEKER)
    __test_building_set_houses_covered(bid, 0)
    __test_warship_wharf_spawn_figure(bid)
    if (__test_building_figure_id(bid, BUILDING_SLOT_LABOR_SEEKER) <= 0) {
        test262_fail('expected labor seeker with houses_covered=0')
        return
    }
    __log_info_native('[test-marker] warship_wharf_og_labor_seeker')

    __test_warships_requested_set(0)
    __test_building_set_open_water_access(bid, 1)
    __test_building_set_figure_slot(bid, BUILDING_SLOT_BOAT, 0)
    __test_warship_wharf_update_month(bid)
    if (__test_warships_requested() < 1) {
        test262_fail('expected warship request, got ' + __test_warships_requested())
        return
    }
    __log_info_native('[test-marker] warship_wharf_og_request_ship')

    __test262_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test262_ok
        && __test_find_inlog('[test-marker] warship_wharf_og_clear_slot')
        && __test_find_inlog('[test-marker] warship_wharf_og_labor_seeker')
        && __test_find_inlog('[test-marker] warship_wharf_og_request_ship')
}

// OG warship wharf placement: max 6 wharves + open-water site check.
// Markers:
//   [test-marker] warship_wharf_og_place_six
//   [test-marker] warship_wharf_og_refuse_seventh
//   [test-marker] warship_wharf_og_refuse_inland

var __test270_ok = false

function test270_fail(msg) {
    __log_info_native('[test:270] ' + msg)
    __test_signal_ready()
}

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    // Bypass planner so we can seed six wharves without shoreline geometry.
    for (var i = 0; i < 6; i++) {
        var bid = __test_building_create(BUILDING_WARSHIP_WHARF, 20 + i * 4, 20)
        if (!bid) {
            test270_fail('create ' + (i + 1) + ' failed')
            return
        }
    }
    if (city.count_active_buildings(BUILDING_WARSHIP_WHARF) < 6) {
        test270_fail('expected 6 warship wharves, got '
            + city.count_active_buildings(BUILDING_WARSHIP_WHARF))
        return
    }
    __log_info_native('[test-marker] warship_wharf_og_place_six')

    city_planner.build_type = BUILDING_WARSHIP_WHARF
    city_planner.finalize_check_result = CAN_PLACE
    // Seed open-water connectivity so the max-6 check is what refuses (not inland).
    test_prepare_shoreline_patch(40, 40, 8, 3)
    building_warship_wharf_can_place({ start: { x: 39, y: 39 }, end: { x: 39, y: 39 }, state: CAN_PLACE })
    if (city_planner.finalize_check_result != CAN_NOT_PLACE) {
        test270_fail('full complement must refuse 7th warship wharf')
        return
    }
    __log_info_native('[test-marker] warship_wharf_og_refuse_seventh')

    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    // Isolated land tile with no river routing → inland lake refusal.
    __test_set_scenario_river_points(-1, -1, -1, -1)
    city_planner.build_type = BUILDING_WARSHIP_WHARF
    city_planner.finalize_check_result = CAN_PLACE
    building_warship_wharf_can_place({ start: { x: 10, y: 10 }, end: { x: 10, y: 10 }, state: CAN_PLACE })
    if (city_planner.finalize_check_result != CAN_NOT_PLACE) {
        test270_fail('inland site must refuse warship wharf')
        return
    }
    __log_info_native('[test-marker] warship_wharf_og_refuse_inland')

    __test270_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test270_ok
        && __test_find_inlog('[test-marker] warship_wharf_og_place_six')
        && __test_find_inlog('[test-marker] warship_wharf_og_refuse_seventh')
        && __test_find_inlog('[test-marker] warship_wharf_og_refuse_inland')
}

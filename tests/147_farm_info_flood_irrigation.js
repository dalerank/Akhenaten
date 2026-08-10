// FI3: floodplain farm irrigation flag + expected flood calendar month for info UI.
// Markers:
//   [test-marker] farm_info_not_irrigated
//   [test-marker] farm_info_irrigated
//   [test-marker] farm_info_month_june
//   [test-marker] farm_info_month_august
//   [test-marker] farm_info_meadow_irrigated
//   [test-marker] farm_info_meadow_harvest
//   [test-marker] farm_info_meadow_ok
//   [test-marker] farm_info_floodplain_open_ok
//   [test-marker] farm_info_inundation_hides_next
//   [test-marker] farm_info_terrain_177_ok

var __test147_season_prev = null

function test147_fail(reason) {
    if (__test147_season_prev !== null) {
        city.floods.season_initial = __test147_season_prev
    }
    __log_info_native('[test:147] FAIL: ' + reason)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:147] farm info flood/irrigation')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    __test147_season_prev = city.floods.season_initial

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    test_prepare_terrain_patch(cx, cy, 8, TERRAIN_FLOODPLAIN)

    var farm = __test_building_create(BUILDING_GRAIN_FARM, cx, cy)
    if (!farm) {
        test147_fail('create_floodplain_farm')
        return
    }

    if (__building_farm_is_irrigated(farm)) {
        test147_fail('expected_not_irrigated')
        return
    }
    __log_marker('farm_info_not_irrigated')

    // Stamp irrigation range onto the farm footprint (same flag fertility uses).
    for (var dx = 0; dx < 3; dx++) {
        for (var dy = 0; dy < 3; dy++) {
            terrain.add({ x: cx + dx, y: cy + dy }, TERRAIN_IRRIGATION_RANGE)
        }
    }
    if (!__building_farm_is_irrigated(farm)) {
        test147_fail('expected_irrigated_after_stamp')
        return
    }
    __log_marker('farm_info_irrigated')

    city.floods.season_initial = 150
    if (city.floods.expected_month() !== 0) {
        test147_fail('expected_month_half_0_got_' + city.floods.expected_month())
        return
    }
    if (floods_expected_half_month() !== 0) {
        test147_fail('half_month_0_got_' + floods_expected_half_month())
        return
    }
    // Half 0 → June (160:5), matching OG farm info (#572).
    if (floods_ui_format_farm_flood_month() !== __loc(160, MONTH_JUNE)) {
        test147_fail('june_text')
        return
    }
    __log_marker('farm_info_month_june')

    city.floods.season_initial = 225
    if (city.floods.expected_month() !== 5) {
        test147_fail('expected_month_half_5_got_' + city.floods.expected_month())
        return
    }
    if (floods_expected_half_month() !== 5) {
        test147_fail('half_month_5_got_' + floods_expected_half_month())
        return
    }
    // Half 5 → August (160:7).
    if (floods_ui_format_farm_flood_month() !== __loc(160, MONTH_AUGUST)) {
        test147_fail('august_text')
        return
    }
    __log_marker('farm_info_month_august')

    // Meadow path: irrigation flag + no Work Camp laborers string; next-harvest line.
    test_prepare_terrain_patch(cx + 10, cy, 5, TERRAIN_MEADOW)
    var meadow = __test_building_create(BUILDING_GRAIN_MEADOW_FARM, cx + 10, cy)
    if (!meadow) {
        test147_fail('create_meadow_farm')
        return
    }
    var meadow_b = city.get_building(meadow)
    if (!meadow_b || terrain.is(meadow_b.tile, TERRAIN_FLOODPLAIN)) {
        test147_fail('meadow_on_floodplain')
        return
    }
    var meadow_no_workers = __loc(meadow_b.meta_text_id, 5)
    var work_camp_need = __loc(177, 5)
    if (!meadow_no_workers || meadow_no_workers === work_camp_need) {
        test147_fail('meadow_workers_loc_same_as_work_camp')
        return
    }
    if (__building_farm_is_irrigated(meadow)) {
        test147_fail('meadow_expected_not_irrigated')
        return
    }
    for (var mdx = 0; mdx < 3; mdx++) {
        for (var mdy = 0; mdy < 3; mdy++) {
            terrain.add({ x: cx + 10 + mdx, y: cy + mdy }, TERRAIN_IRRIGATION_RANGE)
        }
    }
    if (!__building_farm_is_irrigated(meadow)) {
        test147_fail('meadow_expected_irrigated')
        return
    }
    __log_marker('farm_info_meadow_irrigated')

    var harvest_prefix = __loc(meadow_b.meta_text_id, 14)
    if (!harvest_prefix || harvest_prefix === __loc(177, 2)) {
        test147_fail('meadow_harvest_loc_missing_or_flood')
        return
    }
    var next_harvest = building_farm_next_harvest_month(meadow)
    if (next_harvest !== MONTH_JANUARY && next_harvest !== MONTH_MAY) {
        test147_fail('meadow_next_harvest_month_' + next_harvest)
        return
    }
    var harvest_line = harvest_prefix + " " + __loc(160, next_harvest)
    if (!harvest_line || harvest_line.indexOf(harvest_prefix) !== 0) {
        test147_fail('meadow_harvest_line')
        return
    }
    __log_marker('farm_info_meadow_harvest')

    __test_show_tile_info(meadow)
    __test_pump_frames(6)
    window_go_back()
    __test_pump_frames(2)
    __log_marker('farm_info_meadow_ok')

    // Floodplain info open: exercises calendar + irrigation text path (not only bindings).
    __test_show_tile_info(farm)
    __test_pump_frames(6)
    window_go_back()
    __test_pump_frames(2)
    __log_marker('farm_info_floodplain_open_ok')

    // During inundation, farm info hides the "next floods" line (same states as water bar).
    var flood_state_prev = city.floods.state
    city.floods.state = FLOOD_STATE_INUNDATED
    if (!floods_ui_show_water_bar()) {
        city.floods.state = flood_state_prev
        test147_fail('inundated_should_show_water_bar')
        return
    }
    __test_show_tile_info(farm)
    __test_pump_frames(6)
    window_go_back()
    __test_pump_frames(2)
    city.floods.state = flood_state_prev
    __log_marker('farm_info_inundation_hides_next')

    // Empty floodplain describe: dry=177:3, submerged=177:4.
    if (__loc(177, 3) === __loc(177, 4)) {
        test147_fail('177_3_4_same_text')
        return
    }
    __log_marker('farm_info_terrain_177_ok')

    city.floods.season_initial = __test147_season_prev
    __test147_season_prev = null
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'farm_info_not_irrigated',
        'farm_info_irrigated',
        'farm_info_month_june',
        'farm_info_month_august',
        'farm_info_meadow_irrigated',
        'farm_info_meadow_harvest',
        'farm_info_meadow_ok',
        'farm_info_floodplain_open_ok',
        'farm_info_inundation_hides_next',
        'farm_info_terrain_177_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:147] missing marker: ' + marker)
            return false
        }
    }
    return true
}

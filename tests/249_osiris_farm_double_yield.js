// OG Osiris major farm blessing: floodplain harvest ×2 while city flag set; meadow unchanged.
// Markers:
//   [test-marker] osiris_floodplain_doubled
//   [test-marker] osiris_meadow_unchanged
//   [test-marker] osiris_flag_cleared_after_harvest

var __test249_result = null

function test249_fail(reason) {
    __test249_result = { ok: false, reason: reason }
    __log_info_native('[test:249] FAIL: ' + reason)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:249] osiris floodplain double yield')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var flood_bid = test_farm_place(BUILDING_BARLEY_FARM, TERRAIN_FLOODPLAIN)
    if (!flood_bid) {
        test249_fail('no_floodplain_barley')
        return
    }

    // Offset meadow patch so it does not overwrite the floodplain farm.
    var cx = (__scenario_map.width / 2) | 0
    var cy = ((__scenario_map.height / 2) | 0) + 8
    test_prepare_terrain_patch(cx, cy, 5, TERRAIN_MEADOW)
    var meadow_bid = test_building_place(BUILDING_BARLEY_MEADOW_FARM, cx - 1, cy - 1)
    if (!meadow_bid) {
        test249_fail('no_meadow_barley')
        return
    }

    __building_farm_set_progress(flood_bid, 1000)
    __building_farm_set_progress(meadow_bid, 1000)

    var flood_base = __building_farm_expected_produce(flood_bid)
    var meadow_base = __building_farm_expected_produce(meadow_bid)
    if (flood_base <= 0 || meadow_base <= 0) {
        test249_fail('base_produce_zero')
        return
    }

    __test_set_osiris_double_farm_yield(1)
    var flood_blessed = __building_farm_expected_produce(flood_bid)
    var meadow_blessed = __building_farm_expected_produce(meadow_bid)

    if (flood_blessed !== flood_base * 2) {
        test249_fail('floodplain_not_doubled:' + flood_base + '->' + flood_blessed)
        return
    }
    __log_info_native('[test-marker] osiris_floodplain_doubled')

    if (meadow_blessed !== meadow_base) {
        test249_fail('meadow_changed:' + meadow_base + '->' + meadow_blessed)
        return
    }
    __log_info_native('[test-marker] osiris_meadow_unchanged')

    __test_farm_harvest_and_clear_osiris(flood_bid)
    __building_farm_set_progress(flood_bid, 1000)
    var after = __building_farm_expected_produce(flood_bid)
    if (after !== flood_base) {
        test249_fail('flag_not_cleared_after_harvest:' + after + ' vs ' + flood_base)
        return
    }
    __log_info_native('[test-marker] osiris_flag_cleared_after_harvest')

    __test249_result = { ok: true }
    __test_signal_ready()
}

function check_valid() {
    if (!__test249_result || !__test249_result.ok) {
        return false
    }
    return __test_find_inlog('[test-marker] osiris_floodplain_doubled')
        && __test_find_inlog('[test-marker] osiris_meadow_unchanged')
        && __test_find_inlog('[test-marker] osiris_flag_cleared_after_harvest')
}

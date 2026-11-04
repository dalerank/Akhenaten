// Well OG: stamps TERRAIN_FOUNTAIN_RANGE (r=2); houses charge has_well_access
// 0..5 from coverage and never get has_water_access from the well.
// Markers:
//   [test-marker] well_access_in_ok
//   [test-marker] well_access_out_ok
//   [test-marker] well_no_water_access_ok
//   [test-marker] well_fountain_range_ok

var __test255_ok = false

function test255_fail(msg) {
    __log_info_native('[test:255] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:255] well OG access/range')
    test_ensure_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    terrain.add({ x: cx, y: cy }, TERRAIN_GROUNDWATER)

    var well_id = test_building_place(BUILDING_WELL, cx, cy)
    if (!well_id) {
        return test255_fail('well place failed')
    }

    var hid_in = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx + 2, cy)
    var hid_out = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx + 3, cy)
    if (!hid_in || !hid_out) {
        return test255_fail('house create failed in=' + hid_in + ' out=' + hid_out)
    }

    var house_in = city.get_house(hid_in)
    var house_out = city.get_house(hid_out)
    house_in.has_well_access = 0
    house_in.has_water_access = false
    house_out.has_well_access = 0
    house_out.has_water_access = false

    building_well_update_day({ bid: well_id })
    __test_building_update_day(hid_in)
    __test_building_update_day(hid_out)

    house_in = city.get_house(hid_in)
    house_out = city.get_house(hid_out)
    if ((house_in.has_well_access | 0) < 1) {
        return test255_fail('house at +2 should charge well access, got ' + house_in.has_well_access)
    }
    __log_marker('well_access_in_ok')

    if ((house_out.has_well_access | 0) > 0) {
        return test255_fail('house at +3 should not charge well access')
    }
    __log_marker('well_access_out_ok')

    if (house_in.has_water_access) {
        return test255_fail('well must not grant has_water_access')
    }
    __log_marker('well_no_water_access_ok')

    if (!terrain.is({ x: cx + 2, y: cy }, TERRAIN_FOUNTAIN_RANGE)) {
        return test255_fail('missing FOUNTAIN_RANGE at +2')
    }
    if (terrain.is({ x: cx + 3, y: cy }, TERRAIN_FOUNTAIN_RANGE)) {
        return test255_fail('FOUNTAIN_RANGE should not reach +3')
    }
    __log_marker('well_fountain_range_ok')

    __test255_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test255_ok
        && __test_find_inlog('[test-marker] well_access_in_ok')
        && __test_find_inlog('[test-marker] well_access_out_ok')
        && __test_find_inlog('[test-marker] well_no_water_access_ok')
        && __test_find_inlog('[test-marker] well_fountain_range_ok')
}

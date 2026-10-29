// Water lift OG water-supply: canal wake (has_water=2) + IRRIGATION_RANGE stamp.
// Markers: [test-marker] water_lift_og_wake / water_lift_og_stamp

var __test217_ok = false

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_WATER_LIFT, true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var x0 = cx - 2
    for (var dy = 0; dy < 2; dy++) {
        for (var dx = 0; dx < 4; dx++) {
            terrain.add({ x: x0 + dx, y: cy + dy }, TERRAIN_WATER)
        }
    }
    __map_water_rebuild_shores()

    var bid = test_building_place(BUILDING_WATER_LIFT, cx - 1, cy - 1)
    if (!bid) {
        __log_info_native('[test:217] place failed')
        __test_signal_ready()
        return
    }

    __test_building_set_workers(bid, 8)
    var b = city.get_building(bid)

    // --- Wake: dry lift next to a filled canal gets has_water=2 (OG fill_canals).
    b.has_water_access = 0
    var tile = __building_tile(bid)
    var canal = { x: tile.x - 1, y: tile.y }
    terrain.add(canal, TERRAIN_CANAL)
    __map_canal_fill_from_offset(canal, 32)
    if (b.has_water_access != 2) {
        __log_info_native('[test:217] wake fail: has_water=' + b.has_water_access)
        __test_signal_ready()
        return
    }
    __log_marker('water_lift_og_wake')

    // --- Stamp: working lift with water marks IRRIGATION_RANGE around itself.
    __buildings_update_water_lifts_cycle()
    if (!(b.has_water_access > 0)) {
        __log_info_native('[test:217] stamp prep fail: has_water=' + b.has_water_access)
        __test_signal_ready()
        return
    }

    var stamped = false
    for (var dy = -2; dy <= 3 && !stamped; dy++) {
        for (var dx = -2; dx <= 3; dx++) {
            var t = { x: tile.x + dx, y: tile.y + dy }
            if (terrain.is(t, TERRAIN_WATER) || terrain.is(t, TERRAIN_BUILDING)) {
                continue
            }
            if (terrain.is(t, TERRAIN_IRRIGATION_RANGE)) {
                stamped = true
                break
            }
        }
    }
    if (!stamped) {
        __log_info_native('[test:217] no IRRIGATION_RANGE near lift')
        __test_signal_ready()
        return
    }
    __log_marker('water_lift_og_stamp')
    __test217_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test217_ok
        && __test_find_inlog('[test-marker] water_lift_og_wake')
        && __test_find_inlog('[test-marker] water_lift_og_stamp')
}

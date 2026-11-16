// OG canals: a staffed water lift waters a canal of any length (BFS, no level decay);
// an unstaffed lift waters nothing.
// Markers: [test-marker] canal_og_long_wet:N / canal_og_unstaffed_dry

var __test480_result = null

function test480_fail(reason) {
    __test480_result = { ok: false, reason: reason }
    __log_info_native('[test:480] FAIL: ' + reason)
    __test_signal_ready()
}

function test480_count_wet(tiles) {
    var wet = 0
    for (var i = 0; i < tiles.length; i++) {
        if (__map_canal_at(tiles[i]) > 0) {
            wet++
        }
    }
    return wet
}

function run_test() {
    __log_info_native('[test:480] canal og lift reach')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_WATER_LIFT, true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    for (var dy = 0; dy < 2; dy++) {
        for (var dx = 0; dx < 4; dx++) {
            terrain.add({ x: cx - 2 + dx, y: cy + dy }, TERRAIN_WATER)
        }
    }
    __map_water_rebuild_shores()

    var bid = test_building_place(BUILDING_WATER_LIFT, cx - 1, cy - 1)
    if (!bid) {
        return test480_fail('lift_place')
    }
    __test_building_set_workers(bid, 8)
    __buildings_update_water_lifts_cycle()

    var lt = __building_tile(bid)
    var out = __building_water_output_tile(bid, 0)
    var dx = out.x < lt.x ? -1 : (out.x > lt.x + 1 ? 1 : 0)
    var dy = out.y < lt.y ? -1 : (out.y > lt.y + 1 ? 1 : 0)
    if (dx === 0 && dy === 0) {
        return test480_fail('output_tile_inside_lift:' + out.x + ',' + out.y)
    }

    var len = 45
    var tiles = []
    for (var i = 0; i < len; i++) {
        var t = { x: out.x + dx * i, y: out.y + dy * i }
        if (t.x < 1 || t.y < 1 || t.x >= __scenario_map.width - 1 || t.y >= __scenario_map.height - 1) {
            break
        }
        terrain.remove(t, TERRAIN_WATER | TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_FLOODPLAIN)
        terrain.add(t, TERRAIN_CANAL)
        tiles.push(t)
    }
    if (tiles.length < 40) {
        return test480_fail('canal_too_short:' + tiles.length)
    }

    __buildings_update_water_lifts_cycle()
    var wet = test480_count_wet(tiles)
    if (wet !== tiles.length) {
        return test480_fail('long_canal_not_wet:' + wet + '/' + tiles.length)
    }
    var end = tiles[tiles.length - 1]
    if (!terrain.is(end, TERRAIN_IRRIGATION_RANGE)) {
        return test480_fail('canal_end_not_irrigating')
    }
    __log_marker('canal_og_long_wet:' + tiles.length)

    __test_building_set_workers(bid, 0)
    __buildings_update_water_lifts_cycle()
    wet = test480_count_wet(tiles)
    if (wet !== 0) {
        return test480_fail('unstaffed_lift_still_waters:' + wet)
    }
    if (terrain.is(end, TERRAIN_IRRIGATION_RANGE)) {
        return test480_fail('unstaffed_canal_end_irrigating')
    }
    if (city.get_building(bid).has_water_access === 1) {
        return test480_fail('unstaffed_lift_has_water')
    }
    __log_marker('canal_og_unstaffed_dry')

    __test480_result = { ok: true }
    __log_info_native('[test:480] PASS len=' + tiles.length)
    __test_signal_ready()
}

function check_valid() {
    return !!(__test480_result && __test480_result.ok)
        && __test_find_inlog('[test-marker] canal_og_long_wet:')
        && __test_find_inlog('[test-marker] canal_og_unstaffed_dry')
}

// OG floods_fill_canals: a canal on the floodplain row at the flood front is a water source;
// once the flood moves off that row the canal is dry again.
// Markers: [test-marker] canal_flood_dry_before / canal_flood_wet_at_front / canal_flood_dry_after

var __test380_result = null
var __test380_progress_prev = 30

function test380_fail(reason) {
    __test380_result = { ok: false, reason: reason }
    city.floods.flood_progress = __test380_progress_prev
    __log_info_native('[test:380] FAIL: ' + reason)
    __test_signal_ready()
}

function test380_wet_count(tiles) {
    var wet = 0
    for (var i = 0; i < tiles.length; i++) {
        if (__map_canal_at(tiles[i]) > 0) {
            wet++
        }
    }
    return wet
}

function test380_cycle(progress) {
    city.floods.flood_progress = progress
    __buildings_update_water_lifts_cycle()
}

function run_test() {
    __log_info_native('[test:380] canal og flood front')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __test380_progress_prev = city.floods.flood_progress

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    // Nile row at cy, floodplain rows 0..3 at cy+1..cy+4, dry land below.
    for (var dx = -2; dx < 14; dx++) {
        for (var dy = -3; dy <= 16; dy++) {
            var t = { x: cx + dx, y: cy + dy }
            terrain.remove(t, TERRAIN_WATER | TERRAIN_FLOODPLAIN | TERRAIN_CANAL | TERRAIN_TREE | TERRAIN_ROCK)
            if (dx < 0 || dx >= 12) {
                continue
            }
            if (dy === 0) {
                terrain.add(t, TERRAIN_WATER)
            } else if (dy >= 1 && dy <= 4) {
                terrain.add(t, TERRAIN_FLOODPLAIN)
            }
        }
    }
    __map_water_cache_river_tiles()
    var width = __map_floodplain_rebuild_rows()
    __map_floodplain_rebuild_shores()
    city.floods.floodplain_width = width
    city.floods.has_floodplains = width > 0
    if (width <= 0) {
        return test380_fail('no_floodplain_rows')
    }

    var tiles = []
    for (var y = cy + 3; y <= cy + 14; y++) {
        var c = { x: cx + 5, y: y }
        terrain.add(c, TERRAIN_CANAL)
        tiles.push(c)
    }
    var end = tiles[tiles.length - 1]

    test380_cycle(30)
    if (test380_wet_count(tiles) !== 0) {
        return test380_fail('wet_without_flood:' + test380_wet_count(tiles))
    }
    test380_cycle(28)
    if (test380_wet_count(tiles) !== 0) {
        return test380_fail('wet_before_front_reaches_row2:' + test380_wet_count(tiles))
    }
    __log_marker('canal_flood_dry_before')

    // Front on row 2 (OG list 27): the canal's floodplain tile feeds the whole canal.
    test380_cycle(27)
    if (test380_wet_count(tiles) !== tiles.length) {
        return test380_fail('front_did_not_fill:' + test380_wet_count(tiles) + '/' + tiles.length)
    }
    if (!terrain.is(end, TERRAIN_IRRIGATION_RANGE)) {
        return test380_fail('front_fill_no_irrigation')
    }
    __log_marker('canal_flood_wet_at_front')

    test380_cycle(30)
    if (test380_wet_count(tiles) !== 0) {
        return test380_fail('still_wet_after_flood:' + test380_wet_count(tiles))
    }
    if (terrain.is(end, TERRAIN_IRRIGATION_RANGE)) {
        return test380_fail('irrigation_after_flood')
    }
    __log_marker('canal_flood_dry_after')

    city.floods.flood_progress = __test380_progress_prev
    __test380_result = { ok: true }
    __log_info_native('[test:380] PASS')
    __test_signal_ready()
}

function check_valid() {
    return !!(__test380_result && __test380_result.ok)
        && __test_find_inlog('[test-marker] canal_flood_dry_before')
        && __test_find_inlog('[test-marker] canal_flood_wet_at_front')
        && __test_find_inlog('[test-marker] canal_flood_dry_after')
}

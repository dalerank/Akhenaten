// Marker: [test-marker] test_canal_shore_refresh:...

var __test028_result = null
var __test028_poison = 123456

function test028_fail(reason) {
    __test028_result = { ok: false, reason: reason }
    __test_signal_ready()
}

function test028_clear_tile(tile) {
    terrain.remove(tile, TERRAIN_WATER | TERRAIN_CANAL | TERRAIN_ROAD | TERRAIN_ROCK
        | TERRAIN_TREE | TERRAIN_BUILDING | TERRAIN_SHRUB | TERRAIN_FLOODPLAIN | TERRAIN_RUBBLE)
    __map_image_set(tile, 0)
}

function run_test() {
    __log_info_native('[test:028] canal shore image refresh')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var canal = { x: cx, y: cy }
    var water_e = { x: cx + 1, y: cy }

    test028_clear_tile(canal)
    test028_clear_tile(water_e)
    terrain.set_canal(canal)

    if (!terrain.is(canal, TERRAIN_CANAL)) {
        test028_fail('canal_not_placed')
        return
    }

    __map_image_set(canal, __test028_poison)
    if (__map_image_at(canal) !== __test028_poison) {
        test028_fail('poison_not_set')
        return
    }

    terrain.set_water(water_e)
    if (!terrain.is(water_e, TERRAIN_WATER)) {
        test028_fail('water_not_set')
        return
    }

    var img_after = __map_image_at(canal)
    if (img_after === __test028_poison) {
        test028_fail('canal_not_refreshed')
        return
    }
    if (!img_after) {
        test028_fail('canal_image_zero_after')
        return
    }

    __test028_result = { ok: true, after: img_after }
    __log_marker('test_canal_shore_refresh:' + canal.x + ',' + canal.y + ':after=' + img_after)
    __test_signal_ready()
}

function check_valid() {
    if (!__test028_result || !__test028_result.ok) {
        __log_info_native('[test:028] fail: ' + ((__test028_result && __test028_result.reason) || 'no_result'))
        return false
    }

    if (!__test_find_inlog('[test-marker] test_canal_shore_refresh:')) {
        __log_info_native('[test:028] missing log marker')
        return false
    }

    return true
}

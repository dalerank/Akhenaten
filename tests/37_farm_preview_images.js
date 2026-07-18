// Smoke for farm ghost preview helpers (T1).
// Checks crops anim id, get_image routing (meadow vs floodplain), and draw_from_below.
// Under --no-resource farm_house/farmland packs may resolve to 0; routing is still asserted.
// Markers:
//   [test-marker] farm_preview_crops_ok
//   [test-marker] farm_preview_meadow_route_ok
//   [test-marker] farm_preview_floodplain_route_ok
//   [test-marker] farm_preview_draw_from_below_ok

function run_test() {
    __log_info_native('[test:37] farm preview image/crops smoke')
    // Reload for a clean map: earlier farm tests (34/35) leave MEADOW/FLOODPLAIN
    // terrain flags near map center that would break the meadow-route assertion.
    test_reload_city_session('data/default.map')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var tile = { x: cx, y: cy }

    var meadow_type = BUILDING_GRAIN_MEADOW_FARM
    var flood_type = BUILDING_GRAIN_FARM
    var meadow_params = city.get_building_params_by_type(meadow_type)
    var flood_params = city.get_building_params_by_type(flood_type)

    var crops_meadow = meadow_params.first_img('crops')
    var crops_flood = flood_params.first_img('crops')
    if (!crops_meadow || !crops_flood) {
        __log_info_native('[test:37] crops first_img failed meadow=' + crops_meadow + ' flood=' + crops_flood)
        __test_signal_ready()
        return
    }
    __log_marker('farm_preview_crops_ok')

    test_prepare_terrain_patch(cx, cy, 5, TERRAIN_MEADOW)
    if (terrain.is(tile, TERRAIN_FLOODPLAIN)) {
        __log_info_native('[test:37] expected non-floodplain after meadow paint')
        __test_signal_ready()
        return
    }
    var house_img = meadow_params.first_img('farm_house')
    var meadow_img = building_farm_get_image(meadow_type, tile)
    if (meadow_img != house_img) {
        __log_info_native('[test:37] meadow route mismatch img=' + meadow_img + ' house=' + house_img)
        __test_signal_ready()
        return
    }
    __log_marker('farm_preview_meadow_route_ok')

    test_prepare_terrain_patch(cx, cy, 5, TERRAIN_FLOODPLAIN)
    if (!terrain.is(tile, TERRAIN_FLOODPLAIN)) {
        __log_info_native('[test:37] expected floodplain after paint')
        __test_signal_ready()
        return
    }
    var land_img = flood_params.first_img('farmland')
    var fert = __fertility_for_farm_at_tile(tile.x, tile.y)
    var fertility_index = Math.min(7, Math.max(0, Math.floor(fert / 12)))
    var expected_flood = land_img + fertility_index
    var flood_img = building_farm_get_image(flood_type, tile)
    if (flood_img != expected_flood) {
        __log_info_native('[test:37] floodplain route mismatch img=' + flood_img + ' expected=' + expected_flood)
        __test_signal_ready()
        return
    }
    __log_marker('farm_preview_floodplain_route_ok')

    var pixel = city.planner.tile_to_pixel(tile)
    city.planner.draw_from_below(pixel, crops_flood)
    __log_marker('farm_preview_draw_from_below_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'farm_preview_crops_ok',
        'farm_preview_meadow_route_ok',
        'farm_preview_floodplain_route_ok',
        'farm_preview_draw_from_below_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:37] missing marker: ' + marker)
            return false
        }
    }
    return true
}

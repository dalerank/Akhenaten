// FM1: Food Mill GETTING carts from granary (not farms).
// Markers:
//   [test-marker] food_mill_getting_set_ok
//   [test-marker] food_mill_getting_source_ok
//   [test-marker] food_mill_getting_spawn_ok
//   [test-marker] food_mill_menu_flag_off_clears_ok

var __test156_ok = {
    getting: false,
    source: false,
    spawn: false,
    flag_off: false
}

// #644: a granary is reached through its perimeter road tiles, so faking road_network_id is not
// enough -- lay a real road along one side of the footprint and take the network the map computes.
function grant_granary_road(bid) {
    var b = city.get_building(bid)
    var t = __building_tile(bid)
    var dx
    for (dx = -1; dx <= b.size; dx++) {
        terrain.add({ x: t.x + dx, y: t.y - 1 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    b.has_road_access = true
    return __test_tile_road_network(__test_grid_offset_xy(t.x, t.y - 1))
}

function run_test() {
    __log_info_native('[test:156] food mill getting carts')
    test_ensure_city_session('data/default.map')

    var mill_prev = game_features.get('gameplay_enhanced_food_mill')
    function finish() {
        game_features.set('gameplay_enhanced_food_mill', mill_prev)
        __test_signal_ready()
    }

    game_features.set('gameplay_enhanced_food_mill', true)
    building_menu_ctrl.apply_enhanced_buildings()

    var mill = __test_building_create(BUILDING_FOOD_MILL, -1, -1)
    var granary = __test_building_create(BUILDING_GRANARY, -1, -1)
    if (!mill || !granary) {
        __log_info_native('[test:156] create failed mill=' + mill + ' granary=' + granary)
        finish()
        return
    }

    var mt = __building_tile(mill)
    // Road strip south of 3×3 mill for map_get_road_access_tile.
    for (var dx = 0; dx < 3; dx++) {
        terrain.add({ x: mt.x + dx, y: mt.y + 3 }, TERRAIN_ROAD)
    }

    var road_net = grant_granary_road(granary)
    city.get_building(mill).has_road_access = true
    city.get_building(granary).has_road_access = true
    city.get_building(mill).road_network_id = road_net
    city.get_building(mill).distance_from_entry = 1
    city.get_building(granary).road_network_id = road_net
    city.get_building(granary).distance_from_entry = 2
    __test_building_set_workers(mill, 12)
    __test_building_set_workers(granary, 20)

    if (!__test_granary_add_resource(granary, RESOURCE_GRAIN, 400)) {
        __log_info_native('[test:156] stock granary failed')
        finish()
        return
    }

    if (!__test_food_mill_set_getting(mill, RESOURCE_GRAIN)) {
        __log_info_native('[test:156] set getting failed')
        finish()
        return
    }
    __log_marker('food_mill_getting_set_ok')
    __test156_ok.getting = true

    var src = __test_food_mill_find_getting_source(mill)
    if (src != granary) {
        __log_info_native('[test:156] find source want ' + granary + ' got ' + src)
        finish()
        return
    }
    __log_marker('food_mill_getting_source_ok')
    __test156_ok.source = true

    if (__test_food_mill_spawn_figure(mill) != 1) {
        __log_info_native('[test:156] spawn getting cart failed')
        finish()
        return
    }
    __log_marker('food_mill_getting_spawn_ok')
    __test156_ok.spawn = true

    game_features.set('gameplay_enhanced_food_mill', false)
    building_menu_ctrl.apply_enhanced_buildings()
    if (building_menu_ctrl.is_enabled(BUILDING_FOOD_MILL)) {
        __log_info_native('[test:156] menu should clear when flag OFF')
        finish()
        return
    }
    if (__scenario_building_allowed(BUILDING_FOOD_MILL)) {
        __log_info_native('[test:156] scenario allow should clear when flag OFF')
        finish()
        return
    }
    __log_marker('food_mill_menu_flag_off_clears_ok')
    __test156_ok.flag_off = true

    finish()
}

function check_valid() {
    if (!__test156_ok.getting || !__test156_ok.source || !__test156_ok.spawn
        || !__test156_ok.flag_off) {
        __log_info_native('[test:156] one or more phases failed')
        return false
    }
    var markers = [
        'food_mill_getting_set_ok',
        'food_mill_getting_source_ok',
        'food_mill_getting_spawn_ok',
        'food_mill_menu_flag_off_clears_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:156] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

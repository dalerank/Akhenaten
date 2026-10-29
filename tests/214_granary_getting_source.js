// #701: granary GET lookup must skip non-storage buildings (no null-deref).
// Markers:
//   [test-marker] granary_getting_set_ok
//   [test-marker] granary_getting_source_ok
//   [test-marker] granary_getting_no_source_ok

var __test214_ok = {
    getting: false,
    source: false,
    no_source: false
}

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
    __log_info_native('[test:214] granary getting source (#701)')
    test_ensure_city_session('data/default.map')

    // Non-storage buildings / empty slots used to crash better_getting_storage.
    // Explicit tiles: __test_building_create(-1,-1) reuses the first building of a type.
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var house = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx - 20, cy - 20)
    var source = __test_building_create(BUILDING_GRANARY, cx - 8, cy - 8)
    var getter = __test_building_create(BUILDING_GRANARY, cx + 4, cy - 8)
    if (!house || !source || !getter || source == getter) {
        __log_info_native('[test:214] create failed house=' + house
            + ' source=' + source + ' getter=' + getter)
        __test_signal_ready()
        return
    }

    var road_net = grant_granary_road(source)
    grant_granary_road(getter)
    // Connect both granary road stubs so they share a network.
    var sx = __building_tile(source).x
    var sy = __building_tile(source).y
    var gx = __building_tile(getter).x
    var gy = __building_tile(getter).y
    var x
    for (x = Math.min(sx, gx) - 1; x <= Math.max(sx + 3, gx + 3); x++) {
        terrain.add({ x: x, y: sy - 1 }, TERRAIN_ROAD)
        terrain.add({ x: x, y: gy - 1 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    road_net = __test_tile_road_network(__test_grid_offset_xy(sx, sy - 1))

    city.get_building(source).road_network_id = road_net
    city.get_building(source).distance_from_entry = 1
    city.get_building(getter).road_network_id = road_net
    city.get_building(getter).distance_from_entry = 2
    city.get_building(source).has_road_access = true
    city.get_building(getter).has_road_access = true
    __test_building_set_workers(source, 20)
    __test_building_set_workers(getter, 20)

    if (!__test_granary_add_resource(source, RESOURCE_GRAIN, 400)) {
        __log_info_native('[test:214] stock source failed')
        __test_signal_ready()
        return
    }

    if (!__test_granary_set_getting(getter, RESOURCE_GRAIN)) {
        __log_info_native('[test:214] set getting failed')
        __test_signal_ready()
        return
    }
    __log_marker('granary_getting_set_ok')
    __test214_ok.getting = true

    var src = __test_granary_find_getting_source(getter)
    if (src != source) {
        __log_info_native('[test:214] find source want ' + source + ' got ' + src)
        __test_signal_ready()
        return
    }
    __log_marker('granary_getting_source_ok')
    __test214_ok.source = true

    // Empty lookup must return 0 without touching building 0.
    if (!__test_granary_set_resource(source, RESOURCE_GRAIN, 0)) {
        __log_info_native('[test:214] clear source stock failed')
        __test_signal_ready()
        return
    }
    var none = __test_granary_find_getting_source(getter)
    if (none != 0) {
        __log_info_native('[test:214] expected no source, got ' + none)
        __test_signal_ready()
        return
    }
    __log_marker('granary_getting_no_source_ok')
    __test214_ok.no_source = true

    __test_signal_ready()
}

function check_valid() {
    if (!__test214_ok.getting || !__test214_ok.source || !__test214_ok.no_source) {
        __log_info_native('[test:214] one or more phases failed')
        return false
    }
    var markers = [
        'granary_getting_set_ok',
        'granary_getting_source_ok',
        'granary_getting_no_source_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:214] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}

// OG: only laborers fetch monument materials from a storage yard; a yard never sends sleds itself,
// even with bricks in stock and a mastaba in its brick phase.

var t573_ok = false

function t573_fail(msg) {
    __log_info_native('[test:573] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:573] storage yard sends no sleds')
    test_reload_city_session('data/default.map')
    __scenario_building_allow(BUILDING_SMALL_MASTABA, true)
    __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [{x: cx - 4, y: cy - 4}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_MASTABA, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        return t573_fail('place mastaba')
    }
    __test_monument_set_phase(bid, 2)
    if (city.get_monument(bid).needs_resource(RESOURCE_BRICKS) <= 0) {
        return t573_fail('mastaba phase 2 should need bricks')
    }

    var tile = __building_tile(bid)
    var yard = test_building_place(BUILDING_STORAGE_YARD, tile.x + 14, tile.y) || test_building_place(BUILDING_STORAGE_YARD, -1, -1)
    if (!yard) {
        return t573_fail('place yard')
    }
    city.get_building(yard).has_road_access = true
    __test_building_set_workers(yard, 6)
    __test_storage_yard_add_resource(yard, RESOURCE_BRICKS, 800)

    for (var t = 0; t < 20; t++) {
        __test_building_spawn_figure(yard)
        __test_figures_update()
    }
    if (__test_count_figures(FIGURE_SLED) + __test_count_figures(FIGURE_SLED_PULLER) != 0) {
        return t573_fail('yard spawned a sled train')
    }
    if (city.get_building(yard).stored_resource(RESOURCE_BRICKS) != 800) {
        return t573_fail('bricks left the yard: ' + city.get_building(yard).stored_resource(RESOURCE_BRICKS))
    }
    __log_marker('t573_no_yard_sleds_ok')

    t573_ok = true
    __test_signal_ready()
}

function check_valid() {
    return t573_ok && __test_find_inlog('[test-marker] t573_no_yard_sleds_ok')
}

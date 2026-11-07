// OG laborer block fetch: material by pyramid style/stage, a yard holding a full 400 load, no task without one.

function make_laborer(tile) {
    return __test_figure_create(FIGURE_LABORER, tile.x, tile.y + 3)
}

function run_test() {
    __log_info_native('[test:279] pyramid block material + yard for getting')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_STEPPED_PYRAMID)) {
        __scenario_building_allow(BUILDING_SMALL_STEPPED_PYRAMID, true)
    }
    __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 4, y: cy - 4}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_STEPPED_PYRAMID, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        __log_marker('block_yard_place_fail')
        __test_signal_ready()
        return
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)

    var tile = __building_tile(bid)
    var mason = __test_figure_create(FIGURE_STONEMASON, tile.x, tile.y + 3)
    if (!__test_pyramid_park_waiting_mason(bid, mason)) {
        __log_marker('block_yard_park_fail')
        __test_signal_ready()
        return
    }

    var lab0 = make_laborer(tile)
    __worker_assign_brick_delivery(lab0, bid, mason)
    if (!__test_figure_is_alive(lab0)) {
        __log_marker('block_yard_no_yard_ok')
    } else {
        __log_marker('block_yard_no_yard_fail:' + __figure_get_action_state(lab0))
    }

    var yard = __test_building_create(BUILDING_STORAGE_YARD, tile.x + 12, tile.y)
    if (!yard) {
        __log_marker('block_yard_yard_fail')
        __test_signal_ready()
        return
    }
    city.get_building(yard).has_road_access = true
    __test_storage_yard_add_resource(yard, RESOURCE_STONE, 300)

    var lab1 = make_laborer(tile)
    __worker_assign_brick_delivery(lab1, bid, mason)
    if (!__test_figure_is_alive(lab1)) {
        __log_marker('block_yard_partial_ok')
    } else {
        __log_marker('block_yard_partial_fail:' + __figure_get_action_state(lab1))
    }

    __test_storage_yard_add_resource(yard, RESOURCE_STONE, 100)
    var lab2 = make_laborer(tile)
    __worker_assign_brick_delivery(lab2, bid, mason)
    var res = __figure_get_resource(lab2)
    if (__test_figure_is_alive(lab2) && res == RESOURCE_STONE) {
        __log_marker('block_yard_full_ok')
    } else {
        __log_marker('block_yard_full_fail:' + __test_figure_is_alive(lab2) + ':' + res)
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] block_yard_no_yard_ok')
        && __test_find_inlog('[test-marker] block_yard_partial_ok')
        && __test_find_inlog('[test-marker] block_yard_full_ok')
}

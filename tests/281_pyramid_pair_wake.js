// OG pyramid_laborer_deliver_block: a delivery to one part also wakes the waiting mason on its pair part.

function run_test() {
    __log_info_native('[test:281] pyramid pair mason wake')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_MUDBRICK_PYRAMID)) {
        __scenario_building_allow(BUILDING_SMALL_MUDBRICK_PYRAMID, true)
    }
    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 4, y: cy - 4}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_MUDBRICK_PYRAMID, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        __log_marker('pair_wake_place_fail')
        __test_signal_ready()
        return
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)

    var tile = __building_tile(bid)
    var a = __test_figure_create(FIGURE_BRICKLAYER, tile.x, tile.y + 3)
    var b = __test_figure_create(FIGURE_BRICKLAYER, tile.x + 1, tile.y + 3)
    if (!__test_pyramid_park_pair_masons(bid, a, b)) {
        __log_marker('pair_wake_park_fail')
        __test_signal_ready()
        return
    }

    __pyramid_laborer_wake_mason(a)
    var sa = __figure_get_action_state(a)
    var sb = __figure_get_action_state(b)
    if (sa == ACTION_2_BRICKLAYER_WORK && sb == ACTION_2_BRICKLAYER_WORK) {
        __log_marker('pair_wake_ok')
    } else {
        __log_marker('pair_wake_fail:' + sa + ':' + sb)
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] pair_wake_ok')
}

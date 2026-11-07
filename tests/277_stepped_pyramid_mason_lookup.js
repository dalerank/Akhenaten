// Stone pyramids: the work-camp lookup must find a stonemason waiting for a block (OG laborer task search).

function run_test() {
    __log_info_native('[test:277] stepped pyramid waiting stonemason lookup')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_STEPPED_PYRAMID)) {
        __scenario_building_allow(BUILDING_SMALL_STEPPED_PYRAMID, true)
    }
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
        __log_marker('stepped_mason_lookup_place_fail')
        __test_signal_ready()
        return
    }

    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)

    var tile = __building_tile(bid)
    var fid = __test_figure_create(FIGURE_STONEMASON, tile.x, tile.y + 3)
    var part = __test_pyramid_park_waiting_mason(bid, fid)
    if (!part) {
        __log_marker('stepped_mason_lookup_park_fail')
        __test_signal_ready()
        return
    }

    var mason = __pyramid_find_mason_waiting(bid)
    if (mason == fid) {
        __log_marker('stepped_mason_lookup_ok:' + mason)
    } else {
        __log_marker('stepped_mason_lookup_fail:' + mason + ':' + fid)
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] stepped_mason_lookup_ok:')
}

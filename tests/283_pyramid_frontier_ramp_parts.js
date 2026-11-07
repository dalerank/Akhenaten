// OG pyramid_find_frontier_parts keeps a part that waits for a ramp; pyramid_find_block_task skips it.

function run_test() {
    __log_info_native('[test:283] pyramid frontier keeps ramp-waiting parts')
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
        __log_marker('frontier_ramp_place_fail')
        __test_signal_ready()
        return
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)

    var part = __test_pyramid_boost_until_ramp(bid)
    if (!part) {
        __log_marker('frontier_ramp_no_ramp')
        __test_signal_ready()
        return
    }
    __test_pyramid_level_layer(part)
    var needs = __test_pyramid_part_needs_ramp(part)
    var index = __test_pyramid_frontier_index(bid, part)

    var tile = __building_tile(bid)
    var fid = __test_figure_create(FIGURE_BRICKLAYER, tile.x, tile.y + 3)
    city.get_building(bid).add_workers(fid)
    var claimed = __pyramid_claim_bricklayer_task(fid)
    var claimed_needs = claimed ? __test_pyramid_part_needs_ramp(claimed) : 0

    if (needs != 0 && index >= 0 && claimed != part && claimed_needs == 0) {
        __log_marker('frontier_ramp_ok')
    } else {
        __log_marker('frontier_ramp_fail:' + needs + ':' + index + ':' + claimed + ':' + claimed_needs)
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] frontier_ramp_ok')
}

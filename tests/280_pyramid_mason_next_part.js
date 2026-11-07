// OG place_block: after a block the bricklayer claims the next frontier part instead of going home.

function run_test() {
    __log_info_native('[test:280] pyramid bricklayer moves to the next part after a block')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_MUDBRICK_PYRAMID)) {
        __scenario_building_allow(BUILDING_SMALL_MUDBRICK_PYRAMID, true)
    }
    if (!__scenario_building_allowed(BUILDING_BRICKLAYERS_GUILD)) {
        __scenario_building_allow(BUILDING_BRICKLAYERS_GUILD, true)
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
        __log_marker('next_part_place_fail')
        __test_signal_ready()
        return
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)

    var tile = __building_tile(bid)
    var guild = test_building_place(BUILDING_BRICKLAYERS_GUILD, tile.x + 14, tile.y)
    if (!guild) {
        guild = test_building_place(BUILDING_BRICKLAYERS_GUILD, -1, -1)
    }
    var fid = __test_figure_create(FIGURE_BRICKLAYER, tile.x, tile.y + 3)
    if (guild) {
        __test_figure_set_home(fid, guild)
    }
    city.get_building(bid).add_workers(fid)
    if (!__pyramid_claim_bricklayer_task(fid)) {
        __log_marker('next_part_claim_fail')
        __test_signal_ready()
        return
    }
    __test_figure_set_action(fid, ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK)

    var before = __pyramid_remaining_blocks(bid)
    __pyramid_laborer_wake_mason(fid)
    __test_figure_set_wait_ticks(fid, 200)
    for (var w = 0; w < 20 && __pyramid_remaining_blocks(bid) >= before; w++) {
        __test_figures_update()
    }
    var after = __pyramid_remaining_blocks(bid)
    var action = __figure_get_action_state(fid)
    if (after < before && action != ACTION_3_BRICKLAYER_RETURN_HOME && __test_figure_is_alive(fid)) {
        __log_marker('next_part_ok:' + action)
    } else {
        __log_marker('next_part_fail:' + before + '->' + after + ':' + action)
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] next_part_ok:')
}

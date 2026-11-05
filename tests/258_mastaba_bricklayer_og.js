// Mastaba OG bricklayer: start block phase, claim part, wait_for_block, laborer wake, place block.

function run_test() {
    __log_info_native('[test:258] mastaba bricklayer wait-for-block + laborer wake')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_MASTABA)) {
        __scenario_building_allow(BUILDING_SMALL_MASTABA, true)
    }
    if (!__scenario_building_allowed(BUILDING_BRICKLAYERS_GUILD)) {
        __scenario_building_allow(BUILDING_BRICKLAYERS_GUILD, true)
    }

    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 5, y: cy - 2}, {x: cx - 5, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_MASTABA, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        __log_info_native('[test:258] failed to place mastaba')
        __test_signal_ready()
        return
    }

    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)
    var remaining0 = __pyramid_remaining_blocks(bid)
    if (remaining0 == 55) {
        __log_marker('mastaba_blocks_init_ok:55')
    } else {
        __log_info_native('[test:258] expected 55 blocks, got ' + remaining0)
        __log_marker('mastaba_blocks_init_fail:' + remaining0)
    }

    var tile = __building_tile(bid)
    var guild = test_building_place(BUILDING_BRICKLAYERS_GUILD, tile.x + 14, tile.y)
    if (!guild) {
        guild = test_building_place(BUILDING_BRICKLAYERS_GUILD, -1, -1)
    }
    if (!guild) {
        __log_info_native('[test:258] failed to place guild')
        __test_signal_ready()
        return
    }

    var fid = __test_figure_create(FIGURE_BRICKLAYER, tile.x, tile.y + 3)
    __test_figure_set_home(fid, guild)
    city.get_building(bid).add_workers(fid)

    // Force OG task claim → put figure into wait_for_block without full pathing.
    var part = __pyramid_claim_bricklayer_task(fid)
    if (!part) {
        __log_info_native('[test:258] claim task failed')
        __log_marker('mastaba_wait_for_block_fail')
        __test_signal_ready()
        return
    }
    __test_figure_set_action(fid, ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK)
    __test_figures_update()

    var mason = __pyramid_find_mason_waiting(bid)
    if (mason != fid) {
        __log_info_native('[test:258] waiting mason mismatch ' + mason + ' vs ' + fid)
        __log_marker('mastaba_wait_for_block_fail')
        __test_signal_ready()
        return
    }
    __log_marker('mastaba_wait_for_block_ok:' + mason)

    var before = __pyramid_remaining_blocks(bid)
    __pyramid_laborer_wake_mason(mason)
    // Skip block work timer (block_ticks_a+b ≈ 110); outside-road poof used to kill the walker first.
    __test_figure_set_wait_ticks(fid, 200)
    for (var w = 0; w < 20; w++) {
        __test_figures_update()
        if (__pyramid_remaining_blocks(bid) < before) {
            break
        }
    }

    var after = __pyramid_remaining_blocks(bid)
    if (after >= 0 && after < before) {
        __log_marker('mastaba_block_placed_ok:' + before + '->' + after)
    } else {
        __log_info_native('[test:258] remaining_blocks did not drop (' + before + ' -> ' + after + ')')
        __log_marker('mastaba_block_placed_fail:' + before + '->' + after)
    }

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] mastaba_blocks_init_ok:55')
        && __test_find_inlog('[test-marker] mastaba_wait_for_block_ok:')
        && __test_find_inlog('[test-marker] mastaba_block_placed_ok:')
}

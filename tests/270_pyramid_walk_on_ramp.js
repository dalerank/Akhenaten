// OG pyramid_figure_walk_on_ramp: bricklayer start_climb → climb hops → find/wait.

function run_test() {
    __log_info_native('[test:270] pyramid walk_on_ramp bricklayer climb')
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
        __log_info_native('[test:270] failed to place mudbrick pyramid')
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
    if (!guild) {
        __log_info_native('[test:270] failed to place guild')
        __test_signal_ready()
        return
    }

    var fid = __test_figure_create(FIGURE_BRICKLAYER, tile.x, tile.y + 3)
    __test_figure_set_home(fid, guild)
    city.get_building(bid).add_workers(fid)

    var part = __pyramid_claim_bricklayer_task(fid)
    if (!part) {
        __log_info_native('[test:270] claim task failed')
        __log_marker('pyramid_walk_ramp_fail:claim')
        __test_signal_ready()
        return
    }

    if (!__pyramid_figure_begin_climb(fid)) {
        __log_info_native('[test:270] begin_climb failed')
        __log_marker('pyramid_walk_ramp_fail:begin')
        __test_signal_ready()
        return
    }

    var saw_climb = (__test_figure_get_action(fid) == ACTION_4_BRICKLAYER_CLIMB_RAMP)
    var reached_post = false
    for (var t = 0; t < 400; t++) {
        __test_figures_update()
        if (!__test_figure_is_alive(fid)) {
            break
        }
        var st = __test_figure_get_action(fid)
        if (st == ACTION_4_BRICKLAYER_CLIMB_RAMP) {
            saw_climb = true
        }
        if (st == ACTION_5_BRICKLAYER_FIND_PART
            || st == ACTION_7_BRICKLAYER_WALK_TO_PART
            || st == ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK
            || st == ACTION_2_BRICKLAYER_WORK) {
            reached_post = true
            break
        }
        if (st == ACTION_3_BRICKLAYER_RETURN_HOME || st == ACTION_0_BRICKLAYER_ROAM) {
            break
        }
    }

    if (saw_climb && reached_post) {
        __log_marker('pyramid_walk_ramp_ok')
    } else {
        var st = __test_figure_get_action(fid)
        __log_info_native('[test:270] climb=' + saw_climb + ' post=' + reached_post + ' state=' + st)
        __log_marker('pyramid_walk_ramp_fail:state_' + st)
    }

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] pyramid_walk_ramp_ok')
}

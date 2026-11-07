// OG casing: a stonemason lays a casing block on a true pyramid in pyramid_casing_ticks (40) ticks.

function run_test() {
    __log_info_native('[test:282] true pyramid casing block ticks')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_PYRAMID)) {
        __scenario_building_allow(BUILDING_SMALL_PYRAMID, true)
    }
    if (!__scenario_building_allowed(BUILDING_STONEMASONS_GUILD)) {
        __scenario_building_allow(BUILDING_STONEMASONS_GUILD, true)
    }
    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 4, y: cy - 4}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_PYRAMID, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        __log_marker('casing_ticks_place_fail')
        __test_signal_ready()
        return
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)

    var tile = __building_tile(bid)
    var guild = test_building_place(BUILDING_STONEMASONS_GUILD, tile.x + 14, tile.y)
    if (!guild) {
        guild = test_building_place(BUILDING_STONEMASONS_GUILD, -1, -1)
    }
    var fid = __test_figure_create(FIGURE_STONEMASON, tile.x, tile.y + 3)
    if (guild) {
        __test_figure_set_home_slot(fid, guild)
    }
    city.get_building(bid).add_workers(fid)
    if (!__test_pyramid_casing_part(bid, fid)) {
        __log_marker('casing_ticks_park_fail')
        __test_signal_ready()
        return
    }
    __test_figure_set_wait_ticks(fid, 0)
    __test_figure_set_action(fid, ACTION_21_MASON_PYRAMID_WORK)

    var before = __pyramid_remaining_blocks(bid)
    var ticks = 0
    while (ticks < 100 && __pyramid_remaining_blocks(bid) >= before) {
        __test_figures_update()
        ticks++
    }
    if (ticks == 40) {
        __log_marker('casing_ticks_ok:' + ticks)
    } else {
        __log_marker('casing_ticks_fail:' + ticks + ':' + __figure_get_action_state(fid))
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] casing_ticks_ok:40')
}

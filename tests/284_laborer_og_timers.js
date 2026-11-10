// OG laborer timers: 4 ticks at the storage yard before taking the load, 42 ticks after delivering a block.

function run_test() {
    __log_info_native('[test:284] laborer yard and delivered timers')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_SMALL_MUDBRICK_PYRAMID)) {
        __scenario_building_allow(BUILDING_SMALL_MUDBRICK_PYRAMID, true)
    }
    if (!__scenario_building_allowed(BUILDING_WORK_CAMP)) {
        __scenario_building_allow(BUILDING_WORK_CAMP, true)
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
        __log_marker('laborer_timers_place_fail')
        __test_signal_ready()
        return
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)

    var tile = __building_tile(bid)
    var camp = test_building_place(BUILDING_WORK_CAMP, tile.x + 14, tile.y)
    if (!camp) {
        camp = test_building_place(BUILDING_WORK_CAMP, -1, -1)
    }
    var guild = test_building_place(BUILDING_BRICKLAYERS_GUILD, tile.x + 16, tile.y)
    if (!guild) {
        guild = test_building_place(BUILDING_BRICKLAYERS_GUILD, -1, -1)
    }
    __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    var yx = tile.x + 12
    var yy = tile.y + 4
    var yard = __test_building_create(BUILDING_STORAGE_YARD, yx, yy)
    if (!camp || !guild || !yard) {
        __log_marker('laborer_timers_setup_fail')
        __test_signal_ready()
        return
    }
    city.get_building(yard).has_road_access = true
    __test_storage_yard_add_resource(yard, RESOURCE_BRICKS, 400)

    var bl = __test_figure_create(FIGURE_BRICKLAYER, tile.x, tile.y + 3)
    __test_figure_set_home(bl, guild)
    city.get_building(bid).add_workers(bl)
    if (!__pyramid_claim_bricklayer_task(bl)) {
        __log_marker('laborer_timers_claim_fail')
        __test_signal_ready()
        return
    }
    __test_figure_set_action(bl, 8)

    var ytile = __building_tile(yard)
    var fid = __test_figure_create(FIGURE_LABORER, ytile.x, ytile.y)
    __test_figure_set_home_slot(fid, camp)
    city.get_building(bid).add_workers(fid)
    __worker_assign_brick_delivery(fid, bid, bl)

    var at_yard = -1
    var loaded = -1
    for (var t = 0; t < 60 && loaded < 0; t++) {
        __test_figures_update()
        var a = __figure_get_action_state(fid)
        if (a == 16 && at_yard < 0) { // ACTION_16_LABORER_AT_STORAGE_YARD
            at_yard = t
        }
        if (at_yard >= 0 && (a == 30 || a == 17)) { // loaded: SLED_AT_RAMP or TO_PYRAMID
            loaded = t
        }
    }
    var yard_wait = (at_yard >= 0 && loaded >= 0) ? loaded - at_yard : -1

    var lab = __test_figure_create(FIGURE_LABORER, tile.x, tile.y + 3)
    __test_figure_set_home_slot(lab, camp)
    city.get_building(bid).add_workers(lab)
    __test_storage_yard_add_resource(yard, RESOURCE_BRICKS, 400)
    __worker_assign_brick_delivery(lab, bid, bl)
    __test_figure_set_action(lab, 29) // ACTION_29_LABORER_DELIVERED
    __test_figure_set_wait_ticks(lab, 0)
    var delivered = -1
    for (var d = 1; d <= 60 && delivered < 0; d++) {
        __test_figures_update()
        if (__figure_get_action_state(lab) != 29) {
            delivered = d
        }
    }

    if (yard_wait == 5 && delivered == 43) {
        __log_marker('laborer_timers_ok')
    } else {
        __log_marker('laborer_timers_fail:' + at_yard + ':' + loaded + ':' + delivered)
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] laborer_timers_ok')
}

// Laborer brick delivery: OG sled train (5 pullers + sled) linked via leading_figure_id, spawned once the
// laborer has its load; train members stay in ACTION_8 and follow_closely while the laborer pulls.

function run_test() {
    __log_info_native('[test:275] laborer sled train spawn + follow_closely')
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
    if (!__scenario_building_allowed(BUILDING_STORAGE_YARD)) {
        __scenario_building_allow(BUILDING_STORAGE_YARD, true)
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
        __log_info_native('[test:275] failed to place mudbrick pyramid')
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
    if (!camp) {
        __log_info_native('[test:275] failed to place work camp')
        __test_signal_ready()
        return
    }

    var guild = test_building_place(BUILDING_BRICKLAYERS_GUILD, tile.x + 16, tile.y)
    if (!guild) {
        guild = test_building_place(BUILDING_BRICKLAYERS_GUILD, -1, -1)
    }
    if (!guild) {
        __log_info_native('[test:275] failed to place bricklayers guild')
        __test_signal_ready()
        return
    }

    // OG assign_pyramid: a block fetch needs a yard holding a full 400 load.
    __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    var yard = __test_building_create(BUILDING_STORAGE_YARD, tile.x + 12, tile.y + 4)
    if (!yard) {
        __log_info_native('[test:275] failed to create storage yard')
        __test_signal_ready()
        return
    }
    city.get_building(yard).has_road_access = true
    __test_storage_yard_add_resource(yard, RESOURCE_BRICKS, 400)

    var bl = __test_figure_create(FIGURE_BRICKLAYER, tile.x, tile.y + 3)
    __test_figure_set_home(bl, guild)
    city.get_building(bid).add_workers(bl)
    var part = __pyramid_claim_bricklayer_task(bl)
    if (!part) {
        __log_info_native('[test:275] bricklayer claim failed')
        __log_marker('sled_train_spawn_fail:claim')
        __test_signal_ready()
        return
    }
    // Literal 8 = ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK.
    __test_figure_set_action(bl, 8)

    var sy = test_building_place(BUILDING_STORAGE_YARD, tile.x + 18, tile.y)
    if (!sy) {
        sy = test_building_place(BUILDING_STORAGE_YARD, -1, -1)
    }
    if (!sy || !__test_storage_yard_add_resource(sy, RESOURCE_BRICKS, 400)) {
        __log_info_native('[test:275] failed to stock storage yard with bricks')
        __log_marker('sled_train_spawn_fail:yard')
        __test_signal_ready()
        return
    }

    var ytile = __building_tile(yard)
    var fid = __test_figure_create(FIGURE_LABORER, ytile.x, ytile.y)
    // figure_before_action poofs workers whose home building slot 0 lacks them.
    __test_figure_set_home_slot(fid, camp)
    city.get_building(bid).add_workers(fid)
    __worker_assign_brick_delivery(fid, bid, bl)
    if (__test_figure_get_action(fid) != 15) {
        __log_info_native('[test:275] assign_block_delivery did not enter TO_STORAGE_YARD')
        __log_marker('sled_train_spawn_fail:assign')
        __test_signal_ready()
        return
    }

    // OG at_storage_yard: the train appears only after the load is taken.
    var n = 0
    for (var s = 0; s < 400 && n < 6; s++) {
        __test_figures_update()
        n = __pyramid_count_sled_train_followers(fid)
    }
    if (n < 6) {
        __log_info_native('[test:275] spawn_sled_train expected 6 figures, got ' + n + ' action=' + __test_figure_get_action(fid))
        __log_marker('sled_train_spawn_fail:' + n)
        __test_signal_ready()
        return
    }
    __log_marker('sled_train_spawn_ok:' + n)

    for (var t = 0; t < 5; t++) {
        __test_figures_update()
    }

    var following = __pyramid_count_sled_train_followers(fid)
    if (following < 6) {
        __log_info_native('[test:275] train followers still in ACTION_8 expected >=6 got ' + following)
        __log_marker('sled_train_follow_fail:' + following)
        __test_signal_ready()
        return
    }
    __log_marker('sled_train_follow_ok:' + following)

    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] sled_train_spawn_ok:')
        && __test_find_inlog('[test-marker] sled_train_follow_ok:')
}

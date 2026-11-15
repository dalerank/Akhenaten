// OG follow_on_ground (laborer.c): figure_movement_follow_closely ghosts a train member on its spawn tile,
// but follow_on_ground clears the ghost again while the member is on the ground, so a sled train standing
// at the storage yard where it was spawned stays visible.

var ACTION_15_LABORER_TO_STORAGE_YARD = 15
var ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK = 8

var t577_ok = false

function t577_fail(msg) {
    __log_info_native('[test:577] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:577] sled train visible on its spawn tile')
    test_reload_city_session('data/default.map')

    __scenario_building_allow(BUILDING_SMALL_MUDBRICK_PYRAMID, true)
    __scenario_building_allow(BUILDING_WORK_CAMP, true)
    __scenario_building_allow(BUILDING_BRICKLAYERS_GUILD, true)
    __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [{x: cx - 4, y: cy - 4}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_MUDBRICK_PYRAMID, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        return t577_fail('place pyramid')
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)

    var tile = __building_tile(bid)
    var camp = test_building_place(BUILDING_WORK_CAMP, tile.x + 14, tile.y) || test_building_place(BUILDING_WORK_CAMP, -1, -1)
    var guild = test_building_place(BUILDING_BRICKLAYERS_GUILD, tile.x + 16, tile.y) || test_building_place(BUILDING_BRICKLAYERS_GUILD, -1, -1)
    var yard = __test_building_create(BUILDING_STORAGE_YARD, tile.x + 12, tile.y + 4)
    if (!camp || !guild || !yard) {
        return t577_fail('setup camp=' + camp + ' guild=' + guild + ' yard=' + yard)
    }
    city.get_building(yard).has_road_access = true
    __test_storage_yard_add_resource(yard, RESOURCE_BRICKS, 400)

    var bl = __test_figure_create(FIGURE_BRICKLAYER, tile.x, tile.y + 3)
    __test_figure_set_home(bl, guild)
    city.get_building(bid).add_workers(bl)
    if (!__pyramid_claim_bricklayer_task(bl)) {
        return t577_fail('bricklayer claim')
    }
    __test_figure_set_action(bl, ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK)

    var ytile = __building_tile(yard)
    var fid = __test_figure_create(FIGURE_LABORER, ytile.x, ytile.y)
    __test_figure_set_home_slot(fid, camp)
    city.get_building(bid).add_workers(fid)
    __worker_assign_brick_delivery(fid, bid, bl)
    if (__test_figure_get_action(fid) != ACTION_15_LABORER_TO_STORAGE_YARD) {
        return t577_fail('assign did not go to the yard: ' + __test_figure_get_action(fid))
    }

    var spawned = false
    for (var t = 0; t < 120 && !spawned; t++) {
        __test_figures_update()
        spawned = __pyramid_count_sled_train_followers(fid) >= 6
    }
    if (!spawned) {
        return t577_fail('no train after loading, action=' + __test_figure_get_action(fid))
    }

    var members = []
    var spawn_x = []
    var spawn_y = []
    for (var m = 1; m <= 6; m++) {
        var mid = __pyramid_train_member(fid, m)
        members.push(mid)
        spawn_x.push(__test_figure_tile_x(mid))
        spawn_y.push(__test_figure_tile_y(mid))
    }

    var checked = 0
    for (var k = 0; k < 12; k++) {
        __test_figures_update()
        for (var j = 0; j < members.length; j++) {
            var f = members[j]
            if (!__test_figure_is_alive(f)) {
                return t577_fail('train member ' + (j + 1) + ' died at the yard')
            }
            if (__test_figure_tile_x(f) != spawn_x[j] || __test_figure_tile_y(f) != spawn_y[j]) {
                continue
            }
            checked++
            if (!__test_figure_is_visible(f)) {
                return t577_fail('train member ' + (j + 1) + ' invisible on its spawn tile, tick ' + k
                    + ' height=' + __test_figure_current_height(f))
            }
        }
    }
    if (checked < 6) {
        return t577_fail('train left the spawn tile too fast, checked ' + checked)
    }
    __log_marker('t577_visible_on_spawn_tile_ok:' + checked)

    t577_ok = true
    __test_signal_ready()
}

function check_valid() {
    return t577_ok && __test_find_inlog('[test-marker] t577_visible_on_spawn_tile_ok')
}

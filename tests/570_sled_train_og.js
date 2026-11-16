// OG laborer sled train (laborer.c spawn_sled_train / train_follow / laborer_pulls_train):
// the laborer takes a full load at the yard and only then 5 pullers + a sled of that material
// follow it; the block reaches the bricklayer, the yard loses exactly one load, and the train
// dies once the laborer stops pulling (DELIVERED timer, going back to a yard, SLED_TO_TOMB for pullers).

var ACTION_15_LABORER_TO_STORAGE_YARD = 15
var ACTION_17_LABORER_TO_PYRAMID = 17
var ACTION_29_LABORER_DELIVERED = 29
var ACTION_36_LABORER_SLED_TO_TOMB = 36
var ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK = 8

var t570_ok = false

function t570_fail(msg) {
    __log_info_native('[test:570] FAIL: ' + msg)
    __test_signal_ready()
}

function t570_train_size(fid) {
    return __pyramid_count_sled_train_followers(fid)
}

function run_test() {
    __log_info_native('[test:570] sled train OG')
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
        return t570_fail('place pyramid')
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)

    var tile = __building_tile(bid)
    var camp = test_building_place(BUILDING_WORK_CAMP, tile.x + 14, tile.y) || test_building_place(BUILDING_WORK_CAMP, -1, -1)
    var guild = test_building_place(BUILDING_BRICKLAYERS_GUILD, tile.x + 16, tile.y) || test_building_place(BUILDING_BRICKLAYERS_GUILD, -1, -1)
    var yard = __test_building_create(BUILDING_STORAGE_YARD, tile.x + 12, tile.y + 4)
    if (!camp || !guild || !yard) {
        return t570_fail('setup camp=' + camp + ' guild=' + guild + ' yard=' + yard)
    }
    city.get_building(yard).has_road_access = true
    __test_storage_yard_add_resource(yard, RESOURCE_BRICKS, 400)

    var bl = __test_figure_create(FIGURE_BRICKLAYER, tile.x, tile.y + 3)
    __test_figure_set_home(bl, guild)
    city.get_building(bid).add_workers(bl)
    if (!__pyramid_claim_bricklayer_task(bl)) {
        return t570_fail('bricklayer claim')
    }
    __test_figure_set_action(bl, ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK)

    var ytile = __building_tile(yard)
    var fid = __test_figure_create(FIGURE_LABORER, ytile.x, ytile.y)
    __test_figure_set_home_slot(fid, camp)
    city.get_building(bid).add_workers(fid)
    __worker_assign_brick_delivery(fid, bid, bl)
    if (__test_figure_get_action(fid) != ACTION_15_LABORER_TO_STORAGE_YARD) {
        return t570_fail('assign did not go to the yard: ' + __test_figure_get_action(fid))
    }
    if (__test_count_figures(FIGURE_SLED) + __test_count_figures(FIGURE_SLED_PULLER) != 0) {
        return t570_fail('a train exists before the load is taken')
    }

    var spawned = false
    for (var t = 0; t < 120 && !spawned; t++) {
        __test_figures_update()
        spawned = t570_train_size(fid) >= 6
    }
    if (!spawned) {
        return t570_fail('no train after loading, action=' + __test_figure_get_action(fid))
    }
    var stored = city.get_building(yard).stored_resource(RESOURCE_BRICKS)
    if (stored != 0) {
        return t570_fail('yard should give exactly one load, left ' + stored)
    }
    var sled = __pyramid_train_member(fid, 6)
    if (!sled || __test_figure_resource(sled) != RESOURCE_BRICKS) {
        return t570_fail('sled at the train tail with bricks, sled=' + sled + ' res=' + (sled ? __test_figure_resource(sled) : -1))
    }
    __log_marker('t570_spawn_after_load_ok')

    var delivered = false
    for (var d = 0; d < 6000 && !delivered; d++) {
        __test_figures_update()
        if (__test_figure_get_action(fid) == ACTION_29_LABORER_DELIVERED) {
            delivered = true
        }
        if (!__test_figure_is_alive(fid)) {
            break
        }
    }
    if (!delivered) {
        return t570_fail('laborer never delivered, action=' + __test_figure_get_action(fid))
    }
    if (__test_figure_get_action(bl) == ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK) {
        return t570_fail('bricklayer still waits for its block')
    }
    if (t570_train_size(fid) < 6) {
        return t570_fail('train must keep pulling while DELIVERED')
    }
    __log_marker('t570_block_delivered_ok')

    for (var w = 0; w < 60 && __test_figure_get_action(fid) == ACTION_29_LABORER_DELIVERED; w++) {
        __test_figures_update()
    }
    __test_figures_update()
    if (__test_count_figures(FIGURE_SLED) + __test_count_figures(FIGURE_SLED_PULLER) != 0) {
        return t570_fail('train must die after DELIVERED')
    }
    __log_marker('t570_train_dies_after_delivery_ok')

    // A laborer heading back to a storage yard pulls nothing.
    var lab = __test_figure_create(FIGURE_LABORER, tile.x + 12, tile.y + 8)
    __test_figure_set_home_slot(lab, camp)
    __test_figure_set_collecting_item(lab, RESOURCE_BRICKS)
    __test_figure_set_action(lab, ACTION_17_LABORER_TO_PYRAMID)
    __pyramid_spawn_sled_train(lab, bid)
    if (t570_train_size(lab) != 6) {
        return t570_fail('manual train size ' + t570_train_size(lab))
    }
    var members = []
    for (var i2 = 1; i2 <= 6; i2++) {
        members.push(__pyramid_train_member(lab, i2))
    }
    __test_figure_set_action(lab, ACTION_15_LABORER_TO_STORAGE_YARD)
    for (var i3 = 0; i3 < members.length; i3++) {
        __test_figure_action_perform(members[i3])
    }
    if (__test_count_figures(FIGURE_SLED) + __test_count_figures(FIGURE_SLED_PULLER) != 0) {
        return t570_fail('train must die when the laborer goes to a yard')
    }
    __log_marker('t570_train_dies_at_yard_ok')

    // SLED_TO_TOMB: only the sled keeps following, pullers die.
    __test_figure_set_action(lab, ACTION_17_LABORER_TO_PYRAMID)
    __pyramid_spawn_sled_train(lab, bid)
    var tomb_sled = __pyramid_train_member(lab, 6)
    var first_puller = __pyramid_train_member(lab, 1)
    __test_figure_set_leading(tomb_sled, lab)
    __test_figure_set_action(lab, ACTION_36_LABORER_SLED_TO_TOMB)
    __test_figure_action_perform(first_puller)
    __test_figure_action_perform(tomb_sled)
    if (__test_figure_is_alive(first_puller)) {
        return t570_fail('pullers must die on SLED_TO_TOMB')
    }
    if (!__test_figure_is_alive(tomb_sled)) {
        return t570_fail('a sled right behind its laborer keeps following on SLED_TO_TOMB')
    }
    __log_marker('t570_tomb_sled_only_ok')

    t570_ok = true
    __test_signal_ready()
}

function check_valid() {
    return t570_ok
        && __test_find_inlog('[test-marker] t570_spawn_after_load_ok')
        && __test_find_inlog('[test-marker] t570_block_delivered_ok')
        && __test_find_inlog('[test-marker] t570_train_dies_after_delivery_ok')
        && __test_find_inlog('[test-marker] t570_train_dies_at_yard_ok')
        && __test_find_inlog('[test-marker] t570_tomb_sled_only_ok')
}

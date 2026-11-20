// Sled pullers are ordinary citizens in melee. Remake gameplay_change_sled_pullers_flee: with enemies
// near, the pullers run for the map exit and the sled stays where it is with the laborer's load, following
// nobody; the laborer goes back idle and frees its bricklayer. With the option off the train stays OG.

var ACTION_8_LABORER_IDLE = 8
var ACTION_8_SLED_TRAIN_FOLLOW = 8
var ACTION_9_SLED_DROPPED = 9
var ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK = 8
var FIGURE_ACTION_132_FOLLOWER_RUNAWAY = 132

var t425_ok = false
var t425_prev = false

function t425_finish() {
    game_features.set('gameplay_change_sled_pullers_flee', t425_prev)
    __test_signal_ready()
}

function t425_fail(msg) {
    __log_info_native('[test:425] FAIL: ' + msg)
    t425_finish()
}

function t425_members(lab) {
    var out = []
    for (var p = 1; p <= 6; p++) {
        out.push(__pyramid_train_member(lab, p))
    }
    return out
}

function run_test() {
    __log_info_native('[test:425] sled pullers flee')
    test_reload_city_session('data/default.map')
    t425_prev = game_features.get('gameplay_change_sled_pullers_flee')
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
        return t425_fail('place pyramid')
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)
    var tile = __building_tile(bid)
    var camp = test_building_place(BUILDING_WORK_CAMP, tile.x + 14, tile.y) || test_building_place(BUILDING_WORK_CAMP, -1, -1)
    var guild = test_building_place(BUILDING_BRICKLAYERS_GUILD, tile.x + 16, tile.y) || test_building_place(BUILDING_BRICKLAYERS_GUILD, -1, -1)
    var yard = __test_building_create(BUILDING_STORAGE_YARD, tile.x + 12, tile.y + 4)
    if (!camp || !guild || !yard) {
        return t425_fail('setup')
    }
    city.get_building(yard).has_road_access = true
    __test_storage_yard_add_resource(yard, RESOURCE_BRICKS, 400)

    var bl = __test_figure_create(FIGURE_BRICKLAYER, tile.x, tile.y + 3)
    __test_figure_set_home(bl, guild)
    city.get_building(bid).add_workers(bl)
    if (!__pyramid_claim_bricklayer_task(bl)) {
        return t425_fail('bricklayer claim')
    }
    __test_figure_set_action(bl, ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK)

    var ytile = __building_tile(yard)
    var lab = __test_figure_create(FIGURE_LABORER, ytile.x, ytile.y)
    __test_figure_set_home_slot(lab, camp)
    city.get_building(bid).add_workers(lab)
    __worker_assign_brick_delivery(lab, bid, bl)
    for (var t = 0; t < 120 && __pyramid_count_sled_train_followers(lab) < 6; t++) {
        __test_figures_update()
    }
    var members = t425_members(lab)
    var sled = members[5]
    if (!sled || __pyramid_count_sled_train_followers(lab) != 6) {
        return t425_fail('no loaded train')
    }

    // Melee: a hostile figure fights a puller like any citizen.
    var ptile = __figure_get_tile(members[0])
    var lone = test_figure_create(FIGURE_SLED_PULLER, ptile.x + 6, ptile.y + 6)
    var mummy = test_figure_create(FIGURE_MUMMY, ptile.x + 6, ptile.y + 6)
    if (!lone || !mummy || !__test_figure_combat_attack_at(mummy, ptile.x + 6, ptile.y + 6)) {
        return t425_fail('hostile did not fight a puller')
    }
    __test_figure_kill(mummy)
    __test_figure_kill(lone)
    __log_marker('t425_puller_melee_ok')

    var stile = __figure_get_tile(sled)
    var enemy = test_figure_create(FIGURE_ENEMY_BARBARIAN_ARCHER, ptile.x + 2, ptile.y)
    if (!enemy) {
        return t425_fail('create enemy')
    }

    // Option off: OG, the train keeps following.
    game_features.set('gameplay_change_sled_pullers_flee', false)
    for (var k = 0; k < members.length; k++) {
        __test_figure_action_perform(members[k])
    }
    if (__pyramid_count_sled_train_followers(lab) != 6) {
        return t425_fail('option off: train must stay, size ' + __pyramid_count_sled_train_followers(lab))
    }
    __log_marker('t425_off_og_ok')

    game_features.set('gameplay_change_sled_pullers_flee', true)
    members = t425_members(lab)
    __test_figure_action_perform(members[0])
    for (var p = 0; p < 5; p++) {
        if (!__test_figure_is_alive(members[p]) || __test_figure_get_action(members[p]) != FIGURE_ACTION_132_FOLLOWER_RUNAWAY) {
            return t425_fail('puller ' + p + ' should flee, action ' + __test_figure_get_action(members[p]))
        }
    }
    if (__test_figure_get_action(sled) != ACTION_9_SLED_DROPPED || __test_figure_resource(sled) != RESOURCE_BRICKS
        || __test_figure_carrying_amount(sled) != 400) {
        return t425_fail('sled action ' + __test_figure_get_action(sled) + ' res ' + __test_figure_resource(sled)
            + ' amount ' + __test_figure_carrying_amount(sled))
    }
    if (__test_figure_get_action(lab) != ACTION_8_LABORER_IDLE) {
        return t425_fail('laborer should go idle, action ' + __test_figure_get_action(lab))
    }
    if (__test_figure_get_leading(bl) == lab) {
        return t425_fail('bricklayer still waits on the laborer that dropped its sled')
    }
    __log_marker('t425_drop_ok')

    __test_figure_kill(enemy)
    for (var w = 0; w < 50; w++) {
        __test_figures_update()
    }
    var after = __figure_get_tile(sled)
    if (!__test_figure_is_alive(sled) || after.x != stile.x || after.y != stile.y
        || __test_figure_get_action(sled) != ACTION_9_SLED_DROPPED || __test_figure_carrying_amount(sled) != 400) {
        return t425_fail('dropped sled must stay put with its load')
    }
    __log_marker('t425_sled_stays_ok')

    t425_ok = true
    t425_finish()
}

function check_valid() {
    return t425_ok
        && __test_find_inlog('[test-marker] t425_puller_melee_ok')
        && __test_find_inlog('[test-marker] t425_off_og_ok')
        && __test_find_inlog('[test-marker] t425_drop_ok')
        && __test_find_inlog('[test-marker] t425_sled_stays_ok')
}

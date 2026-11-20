// OG laborer.c at_storage_yard: for every pyramid style (mastaba included) a block load leaves the
// yard on a sled train toward the ramp entry (SLED_AT_RAMP), and the laborer climbs to its mason and
// delivers. No pyramid kind sends the laborer to the mason on foot without a train.

var ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK = 8
var ACTION_16_LABORER_AT_STORAGE_YARD = 16
var ACTION_18_LABORER_CLIMB_RAMP = 18
var ACTION_29_LABORER_DELIVERED = 29
var ACTION_30_LABORER_SLED_AT_RAMP = 30

var t426_kinds = [
    { name: 'mudbrick', type: BUILDING_SMALL_MUDBRICK_PYRAMID, mason: FIGURE_BRICKLAYER },
    { name: 'mastaba', type: BUILDING_SMALL_MASTABA, mason: FIGURE_BRICKLAYER },
    { name: 'stepped', type: BUILDING_SMALL_STEPPED_PYRAMID, mason: FIGURE_STONEMASON },
    { name: 'true', type: BUILDING_SMALL_PYRAMID, mason: FIGURE_STONEMASON },
    { name: 'bent', type: BUILDING_SMALL_BENT_PYRAMID, mason: FIGURE_STONEMASON }
]

var t426_ok = false

function t426_fail(msg) {
    __log_info_native('[test:426] FAIL: ' + msg)
    __test_signal_ready()
}

function t426_place(type) {
    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var candidates = [{x: cx - 4, y: cy - 4}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}]
    for (var i = 0; i < candidates.length; i++) {
        var bid = test_building_place(type, candidates[i].x, candidates[i].y)
        if (bid) {
            return bid
        }
    }
    return 0
}

// Returns '' on success, else the reason.
function t426_run_kind(kind) {
    test_reload_city_session('data/default.map')
    __scenario_building_allow(kind.type, true)
    __scenario_building_allow(BUILDING_WORK_CAMP, true)
    __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    __scenario_building_allow(BUILDING_BRICKLAYERS_GUILD, true)
    __scenario_building_allow(BUILDING_STONEMASONS_GUILD, true)
    __test_set_treasury(500000)

    var bid = t426_place(kind.type)
    if (!bid) {
        return 'place'
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)
    var tile = __building_tile(bid)
    var camp = test_building_place(BUILDING_WORK_CAMP, tile.x + 16, tile.y) || test_building_place(BUILDING_WORK_CAMP, -1, -1)
    var yard = __test_building_create(BUILDING_STORAGE_YARD, tile.x + 12, tile.y + 4)
    if (!camp || !yard) {
        return 'setup'
    }
    city.get_building(yard).has_road_access = true

    var mason = __test_figure_create(kind.mason, tile.x, tile.y + 3)
    if (kind.mason == FIGURE_BRICKLAYER) {
        var guild = test_building_place(BUILDING_BRICKLAYERS_GUILD, tile.x + 18, tile.y) || test_building_place(BUILDING_BRICKLAYERS_GUILD, -1, -1)
        __test_figure_set_home(mason, guild)
        city.get_building(bid).add_workers(mason)
        if (!__pyramid_claim_bricklayer_task(mason)) {
            return 'claim bricklayer'
        }
        __test_figure_set_action(mason, ACTION_8_BRICKLAYER_WAIT_FOR_BLOCK)
    } else {
        var sguild = test_building_place(BUILDING_STONEMASONS_GUILD, tile.x + 18, tile.y) || test_building_place(BUILDING_STONEMASONS_GUILD, -1, -1)
        __test_figure_set_home_slot(mason, sguild)
        city.get_building(bid).add_workers(mason)
        if (!sguild || !__test_pyramid_park_waiting_mason(bid, mason)) {
            return 'park stonemason'
        }
    }

    var material = __worker_block_material_for(bid, mason)
    __test_storage_yard_add_resource(yard, material, 400)
    var ytile = __building_tile(yard)
    var lab = __test_figure_create(FIGURE_LABORER, ytile.x, ytile.y)
    __test_figure_set_home_slot(lab, camp)
    city.get_building(bid).add_workers(lab)
    __worker_assign_brick_delivery(lab, bid, mason)

    var left_yard = -1
    for (var t = 0; t < 200 && left_yard < 0 && __test_figure_is_alive(lab); t++) {
        __test_figures_update()
        var a = __test_figure_get_action(lab)
        if (a != 15 && a != ACTION_16_LABORER_AT_STORAGE_YARD) {
            left_yard = a
        }
    }
    if (left_yard != ACTION_30_LABORER_SLED_AT_RAMP && left_yard != ACTION_18_LABORER_CLIMB_RAMP) {
        return 'laborer left the yard in action ' + left_yard
    }
    if (__pyramid_count_sled_train_followers(lab) != 6) {
        return 'no train, followers ' + __pyramid_count_sled_train_followers(lab)
    }
    var sled = __pyramid_train_member(lab, 6)
    if (__test_figure_resource(sled) != material) {
        return 'sled carries ' + __test_figure_resource(sled) + ' want ' + material
    }

    for (var d = 0; d < 6000 && __test_figure_is_alive(lab); d++) {
        __test_figures_update()
        if (__test_figure_get_action(lab) == ACTION_29_LABORER_DELIVERED) {
            return ''
        }
    }
    return 'not delivered, laborer action ' + __test_figure_get_action(lab)
}

function run_test() {
    __log_info_native('[test:426] laborer yard train for every pyramid kind')
    for (var i = 0; i < t426_kinds.length; i++) {
        var why = t426_run_kind(t426_kinds[i])
        if (why) {
            return t426_fail(t426_kinds[i].name + ': ' + why)
        }
        __log_marker('t426_' + t426_kinds[i].name + '_ok')
    }
    t426_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (!t426_ok) {
        return false
    }
    for (var i = 0; i < t426_kinds.length; i++) {
        if (!__test_find_inlog('[test-marker] t426_' + t426_kinds[i].name + '_ok')) {
            return false
        }
    }
    return true
}

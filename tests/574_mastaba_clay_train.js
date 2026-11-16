// Remake gameplay_change_mastaba_clay_delivery: with the option on, a laborer fetches a load of clay
// at a storage yard and pulls it to the mastaba on a sled train, filling the phase's clay quota.
// With the option off (OG) no clay is hauled.

var ACTION_15_LABORER_TO_STORAGE_YARD = 15
var ACTION_29_LABORER_DELIVERED = 29
var ACTION_37_LABORER_SLED_TO_MASTABA = 37

var t574_ok = false
var t574_prev = false

function t574_finish() {
    game_features.set('gameplay_change_mastaba_clay_delivery', t574_prev)
    __test_signal_ready()
}

function t574_fail(msg) {
    __log_info_native('[test:574] FAIL: ' + msg)
    t574_finish()
}

function run_test() {
    __log_info_native('[test:574] mastaba clay by sled train')
    test_reload_city_session('data/default.map')
    t574_prev = game_features.get('gameplay_change_mastaba_clay_delivery')
    __scenario_building_allow(BUILDING_SMALL_MASTABA, true)
    __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    __scenario_building_allow(BUILDING_WORK_CAMP, true)
    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [{x: cx - 4, y: cy - 4}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SMALL_MASTABA, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        return t574_fail('place mastaba')
    }
    var tile = __building_tile(bid)
    var camp = test_building_place(BUILDING_WORK_CAMP, tile.x + 16, tile.y) || test_building_place(BUILDING_WORK_CAMP, -1, -1)
    var yard = test_building_place(BUILDING_STORAGE_YARD, tile.x + 12, tile.y) || test_building_place(BUILDING_STORAGE_YARD, -1, -1)
    if (!camp || !yard) {
        return t574_fail('setup camp=' + camp + ' yard=' + yard)
    }
    city.get_building(yard).has_road_access = true
    __test_storage_yard_add_resource(yard, RESOURCE_CLAY, 800)
    __test_monument_set_phase(bid, 3)
    var ytile = __building_tile(yard)

    // Option off: OG, the mastaba needs no clay and no laborer goes for it.
    game_features.set('gameplay_change_mastaba_clay_delivery', false)
    if (city.get_monument(bid).needs_resource(RESOURCE_CLAY) != 0) {
        return t574_fail('clay quota must be off without the option')
    }
    var idle = __test_figure_create(FIGURE_LABORER, ytile.x, ytile.y)
    __test_figure_set_home_slot(idle, camp)
    __worker_find_work(idle)
    for (var t0 = 0; t0 < 60; t0++) {
        __test_figures_update()
    }
    if (__test_count_figures(FIGURE_SLED) != 0 || city.get_building(yard).stored_resource(RESOURCE_CLAY) != 800) {
        return t574_fail('clay hauled with the option off')
    }
    if (__test_figure_is_alive(idle)) {
        __test_figure_kill(idle)
    }
    __log_marker('t574_off_no_clay_ok')

    game_features.set('gameplay_change_mastaba_clay_delivery', true)
    var need = city.get_monument(bid).needs_resource(RESOURCE_CLAY)
    if (need <= 400) {
        return t574_fail('phase 3 clay quota ' + need)
    }
    var fid = __test_figure_create(FIGURE_LABORER, ytile.x, ytile.y)
    __test_figure_set_home_slot(fid, camp)
    __worker_find_work(fid)
    if (__test_figure_get_action(fid) != ACTION_15_LABORER_TO_STORAGE_YARD) {
        return t574_fail('laborer did not go for clay, action=' + __test_figure_get_action(fid))
    }

    var sled = 0
    for (var t = 0; t < 200 && !sled; t++) {
        __test_figures_update()
        if (__test_figure_get_action(fid) == ACTION_37_LABORER_SLED_TO_MASTABA && __pyramid_count_sled_train_followers(fid) == 6) {
            sled = __pyramid_train_member(fid, 6)
        }
    }
    if (!sled || __test_figure_resource(sled) != RESOURCE_CLAY) {
        return t574_fail('no clay sled train, action=' + __test_figure_get_action(fid) + ' sled=' + sled)
    }
    if (city.get_building(yard).stored_resource(RESOURCE_CLAY) != 400) {
        return t574_fail('yard should give one load, left ' + city.get_building(yard).stored_resource(RESOURCE_CLAY))
    }
    __log_marker('t574_clay_train_ok')

    var delivered = false
    for (var d = 0; d < 4000 && !delivered && __test_figure_is_alive(fid); d++) {
        __test_figures_update()
        delivered = __test_figure_get_action(fid) == ACTION_29_LABORER_DELIVERED
    }
    var pct = __test_monument_resource_pct(bid, RESOURCE_CLAY)
    var want = Math.floor(400 * 100 / need)
    if (!delivered || pct != want) {
        return t574_fail('clay delivered=' + delivered + ' pct=' + pct + ' want ' + want)
    }
    __log_marker('t574_clay_delivered_ok')

    t574_ok = true
    t574_finish()
}

function check_valid() {
    return t574_ok
        && __test_find_inlog('[test-marker] t574_off_no_clay_ok')
        && __test_find_inlog('[test-marker] t574_clay_train_ok')
        && __test_find_inlog('[test-marker] t574_clay_delivered_ok')
}

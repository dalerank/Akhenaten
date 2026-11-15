// Remake gameplay_change_sled_return_empty: after unloading at the monument the laborer pulls the empty
// sled train back to the storage yard the load came from, and the train disappears there. With the option
// off (OG laborer.c) the train is torn down as soon as the laborer stops pulling after the delivery.
// Uses the clay sled train of gameplay_change_mastaba_clay_delivery, which unloads on the ground.

var ACTION_8_LABORER_IDLE = 8
var ACTION_9_LABORER_GOING_OUT = 9
var ACTION_15_LABORER_TO_STORAGE_YARD = 15
var ACTION_17_LABORER_TO_PYRAMID = 17
var ACTION_29_LABORER_DELIVERED = 29
var ACTION_37_LABORER_SLED_TO_MASTABA = 37
var ACTION_38_LABORER_SLED_RETURN = 38
var ACTION_4_FERRY_BOAT_WAITING_T579 = 4

var t579_ok = false
var t579_prev_clay = false
var t579_prev_return = false
var t579 = {}

function t579_finish() {
    game_features.set('gameplay_change_mastaba_clay_delivery', t579_prev_clay)
    game_features.set('gameplay_change_sled_return_empty', t579_prev_return)
    __test_signal_ready()
}

function t579_fail(msg) {
    __log_info_native('[test:579] FAIL: ' + msg)
    t579_finish()
}

function t579_train_count() {
    return __test_count_figures(FIGURE_SLED) + __test_count_figures(FIGURE_SLED_PULLER)
}

function t579_road_place(x0, x1, y) {
    if (!test_planner_enter_build_mode(BUILDING_ROAD)) {
        return false
    }
    city_planner.update(x1, y)
    city_planner.construction_start(x0, y)
    city_planner.construction_update(x1, y)
    city_planner.construction_finalize()
    test_planner_exit_build_mode()
    __test_update_road_network()
    return __test_tile_road_network(__test_grid_offset_xy(x0, y)) > 0 && __test_tile_road_network(__test_grid_offset_xy(x1, y)) > 0
}

function t579_setup() {
    test_reload_city_session('data/default.map')
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
        return 'place mastaba'
    }
    var tile = __building_tile(bid)
    var camp = test_building_place(BUILDING_WORK_CAMP, tile.x + 16, tile.y) || test_building_place(BUILDING_WORK_CAMP, -1, -1)
    if (!t579_road_place(tile.x + 12, tile.x + 14, tile.y + 3)) {
        return 'setup road'
    }
    var yard = test_building_place(BUILDING_STORAGE_YARD, tile.x + 12, tile.y)
    __test_check_kingdome_access()
    if (!camp || !yard || __test_building_road_access_tile(yard) < 0) {
        return 'setup camp=' + camp + ' yard=' + yard
    }
    __test_storage_yard_add_resource(yard, RESOURCE_CLAY, 800)
    __test_monument_set_phase(bid, 3)
    t579 = {bid: bid, camp: camp, yard: yard, ytile: __building_tile(yard)}
    return ''
}

// Sends a laborer for clay and runs it until it unloads at the mastaba; returns the laborer id or an error.
function t579_haul() {
    var fid = __test_figure_create(FIGURE_LABORER, t579.ytile.x, t579.ytile.y)
    __test_figure_set_home_slot(fid, t579.camp)
    __worker_find_work(fid)
    if (__test_figure_get_action(fid) != ACTION_15_LABORER_TO_STORAGE_YARD) {
        return 'laborer did not go for clay, action=' + __test_figure_get_action(fid)
    }
    var pulling = false
    for (var t = 0; t < 200 && !pulling; t++) {
        __test_figures_update()
        pulling = __test_figure_get_action(fid) == ACTION_37_LABORER_SLED_TO_MASTABA && __pyramid_count_sled_train_followers(fid) == 6
    }
    if (!pulling) {
        return 'no clay sled train, action=' + __test_figure_get_action(fid)
    }
    t579.train_x = __test_figure_tile_x(fid)
    t579.train_y = __test_figure_tile_y(fid)
    var delivered = false
    for (var d = 0; d < 4000 && !delivered && __test_figure_is_alive(fid); d++) {
        __test_figures_update()
        delivered = __test_figure_get_action(fid) == ACTION_29_LABORER_DELIVERED
    }
    if (!delivered) {
        return 'clay never delivered, action=' + __test_figure_get_action(fid)
    }
    return fid
}

function t579_run_off() {
    var err = t579_setup()
    if (err) {
        return err
    }
    game_features.set('gameplay_change_mastaba_clay_delivery', true)
    game_features.set('gameplay_change_sled_return_empty', false)
    var fid = t579_haul()
    if (typeof fid == 'string') {
        return 'off: ' + fid
    }
    for (var w = 0; w < 200 && __test_figure_get_action(fid) == ACTION_29_LABORER_DELIVERED; w++) {
        __test_figures_update()
    }
    __test_figures_update()
    if (__test_figure_get_action(fid) == ACTION_38_LABORER_SLED_RETURN || t579_train_count() != 0) {
        return 'off: train must be torn down after the delivery, action=' + __test_figure_get_action(fid)
            + ' train=' + t579_train_count()
    }
    __log_marker('t579_off_torn_down_ok')
    return ''
}

function t579_run_on() {
    var err = t579_setup()
    if (err) {
        return err
    }
    game_features.set('gameplay_change_mastaba_clay_delivery', true)
    game_features.set('gameplay_change_sled_return_empty', true)
    var fid = t579_haul()
    if (typeof fid == 'string') {
        return 'on: ' + fid
    }
    var returning = false
    for (var w = 0; w < 200 && !returning; w++) {
        __test_figures_update()
        returning = __test_figure_get_action(fid) == ACTION_38_LABORER_SLED_RETURN
    }
    if (!returning || __pyramid_count_sled_train_followers(fid) != 6) {
        return 'on: laborer must pull the train back, action=' + __test_figure_get_action(fid)
            + ' train=' + __pyramid_count_sled_train_followers(fid)
    }
    var sled = __pyramid_train_member(fid, 6)
    __test_figures_update()
    if (__test_figure_anim_key(sled) != 'empty') {
        return 'on: the returning sled must be empty, anim=' + __test_figure_anim_key(sled)
    }
    __log_marker('t579_on_returns_empty_ok')

    var from_x = __test_figure_tile_x(fid)
    var from_y = __test_figure_tile_y(fid)
    var moved = 0
    for (var s = 0; s < 400 && moved < 3 && __test_figure_get_action(fid) == ACTION_38_LABORER_SLED_RETURN; s++) {
        __test_figures_update()
        moved = Math.max(Math.abs(__test_figure_tile_x(fid) - from_x), Math.abs(__test_figure_tile_y(fid) - from_y))
    }
    if (__test_figure_get_action(fid) != ACTION_38_LABORER_SLED_RETURN) {
        return 'on: return ended too early for the save check, action=' + __test_figure_get_action(fid)
    }
    var save_name = 'test_579_sled_return.svx'
    if (!__test_save_memory(save_name)) {
        return 'on: save failed'
    }
    if (!__test_load_memory(save_name)) {
        __test_drop_memory_save(save_name)
        return 'on: load failed'
    }
    __test_drop_memory_save(save_name)
    if (__test_figure_get_action(fid) != ACTION_38_LABORER_SLED_RETURN || __pyramid_count_sled_train_followers(fid) != 6) {
        return 'on: return lost on save/load, action=' + __test_figure_get_action(fid)
            + ' train=' + __pyramid_count_sled_train_followers(fid)
    }
    __log_marker('t579_on_saveload_ok')

    var back = false
    var last_x = -1
    var last_y = -1
    for (var r = 0; r < 4000 && !back; r++) {
        if (__test_figure_get_action(fid) == ACTION_38_LABORER_SLED_RETURN) {
            last_x = __test_figure_tile_x(fid)
            last_y = __test_figure_tile_y(fid)
        }
        __test_figures_update()
        back = __test_figure_get_action(fid) != ACTION_38_LABORER_SLED_RETURN
    }
    __test_figures_update()
    if (!back || t579_train_count() != 0) {
        return 'on: train must disappear at the yard, back=' + back + ' train=' + t579_train_count()
    }
    if (last_x != t579.train_x || last_y != t579.train_y) {
        return 'on: return ended at ' + last_x + ',' + last_y + ' not at the yard ' + t579.train_x + ',' + t579.train_y
    }
    var after = __test_figure_get_action(fid)
    if (__test_figure_is_alive(fid) && after != ACTION_8_LABORER_IDLE && after != ACTION_9_LABORER_GOING_OUT) {
        return 'on: laborer must rejoin the idle pool after the return, action=' + after
    }
    __log_marker('t579_on_gone_at_yard_ok')
    return ''
}

function t579_run_yard_gone() {
    var err = t579_setup()
    if (err) {
        return err
    }
    game_features.set('gameplay_change_mastaba_clay_delivery', true)
    game_features.set('gameplay_change_sled_return_empty', true)
    var fid = t579_haul()
    if (typeof fid == 'string') {
        return 'yard gone: ' + fid
    }
    for (var w = 0; w < 200 && __test_figure_get_action(fid) != ACTION_38_LABORER_SLED_RETURN; w++) {
        __test_figures_update()
    }
    if (__test_figure_get_action(fid) != ACTION_38_LABORER_SLED_RETURN) {
        return 'yard gone: no return, action=' + __test_figure_get_action(fid)
    }
    __test_building_destroy_by_enemy(t579.yard)
    __test_figures_update()
    __test_figures_update()
    if (t579_train_count() != 0 || __test_figure_get_action(fid) == ACTION_38_LABORER_SLED_RETURN) {
        return 'yard gone: train must be torn down, train=' + t579_train_count() + ' action=' + __test_figure_get_action(fid)
    }
    __log_marker('t579_yard_gone_torn_down_ok')
    return ''
}

// The return reuses the OG ferry train handling: the train rides along and lands with its laborer.
function t579_run_ferry() {
    test_reload_city_session('data/default.map')
    game_features.set('gameplay_change_sled_return_empty', true)
    __test_set_treasury(500000)
    __scenario_building_allow(BUILDING_FERRY, true)
    var landing = test_shoreline_building_place(BUILDING_FERRY, 2)
    if (!landing) {
        return 'ferry: place ferry'
    }
    __test_building_set_workers(landing, 8)
    var tile = __building_tile(landing)
    var boat = test_figure_create(FIGURE_FERRY_BOAT, tile.x, tile.y)
    test_figure_set_home(boat, landing)
    __test_building_set_figure_slot(landing, BUILDING_SLOT_BOAT, boat)
    __test_figure_set_action(boat, ACTION_4_FERRY_BOAT_WAITING_T579)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var lab = test_figure_create(FIGURE_LABORER, cx + 8, cy + 8)
    __test_figure_set_collecting_item(lab, RESOURCE_CLAY)
    __test_figure_set_action(lab, ACTION_17_LABORER_TO_PYRAMID)
    __pyramid_spawn_sled_train(lab, landing)
    __test_figure_set_action(lab, ACTION_38_LABORER_SLED_RETURN)
    if (!__test_ferry_landing_enqueue(landing, lab)) {
        return 'ferry: enqueue laborer'
    }
    if (__test_ferry_boat_load(boat, landing) != 1) {
        return 'ferry: boat did not load the laborer'
    }
    var members = []
    for (var p = 1; p <= 6; p++) {
        members.push(__pyramid_train_member(lab, p))
    }
    for (var i = 0; i < members.length; i++) {
        __test_figure_action_perform(members[i])
        if (!__test_figure_is_alive(members[i]) || __test_figure_is_visible(members[i])) {
            return 'ferry: train must ride hidden with its laborer'
        }
    }
    __test_ferry_boat_unload(boat, landing)
    if (__test_figure_get_action(lab) != ACTION_38_LABORER_SLED_RETURN) {
        return 'ferry: return not resumed after unload, action=' + __test_figure_get_action(lab)
    }
    for (var k = 0; k < members.length; k++) {
        __test_figure_action_perform(members[k])
        if (!__test_figure_is_alive(members[k]) || !__test_figure_is_visible(members[k])) {
            return 'ferry: train lost at unload'
        }
    }
    __log_marker('t579_ferry_ok')
    return ''
}

function run_test() {
    __log_info_native('[test:579] empty sled train returns to the yard')
    t579_prev_clay = game_features.get('gameplay_change_mastaba_clay_delivery')
    t579_prev_return = game_features.get('gameplay_change_sled_return_empty')
    var steps = [t579_run_off, t579_run_on, t579_run_yard_gone, t579_run_ferry]
    for (var i = 0; i < steps.length; i++) {
        var err = steps[i]()
        if (err) {
            return t579_fail(err)
        }
    }
    t579_ok = true
    t579_finish()
}

function check_valid() {
    return t579_ok
        && __test_find_inlog('[test-marker] t579_off_torn_down_ok')
        && __test_find_inlog('[test-marker] t579_on_returns_empty_ok')
        && __test_find_inlog('[test-marker] t579_on_saveload_ok')
        && __test_find_inlog('[test-marker] t579_on_gone_at_yard_ok')
        && __test_find_inlog('[test-marker] t579_yard_gone_torn_down_ok')
        && __test_find_inlog('[test-marker] t579_ferry_ok')
}

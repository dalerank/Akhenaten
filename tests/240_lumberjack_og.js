// Lumberjack OG gate + return-home delivery:
// - Spawn gate: grown timber (growth==255) vs remake feature any TERRAIN_TREE
// - ACTION_4 return home: +25 timber then poof
// Markers:
//   [test-marker] test240_ungrown_blocks_og
//   [test-marker] test240_feature_allows_any_tree
//   [test-marker] test240_grown_allows_og
//   [test-marker] test240_return_home_delivered
//   [test-marker] test240_return_home_poofed

var __test240_ok = false
var __test240_feat_prev = false

function test240_fail(msg) {
    game_features.set('gameplay_change_wood_cutter_single_gatherer', __test240_feat_prev)
    __log_info_native('[test:240] FAIL: ' + msg)
    __test_signal_ready()
}

function test240_place_tree_near(bid, growth) {
    var t = __building_tile(bid)
    var rx = t.x + 2
    var ry = t.y
    var tx = t.x + 4
    var ty = t.y
    terrain.add({ x: rx, y: ry }, TERRAIN_ROAD)
    terrain.add({ x: rx + 1, y: ry }, TERRAIN_ROAD)
    terrain.add({ x: tx, y: ty }, TERRAIN_TREE)
    __test_map_set_vegetation_growth(tx, ty, growth)
    __test_building_set_road_access(bid, rx, ry)
    __test_map_routing_update_land()
    return { rx: rx, ry: ry, tx: tx, ty: ty }
}

function run_test() {
    __log_info_native('[test:240] lumberjack grown-timber gate + return home')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __test240_feat_prev = game_features.get('gameplay_change_wood_cutter_single_gatherer') === true
    game_features.set('gameplay_change_wood_cutter_single_gatherer', false)

    var bid = test_building_place(BUILDING_WOOD_CUTTERS, -1, -1)
    if (!bid) {
        return test240_fail('place wood cutter failed')
    }

    __test_building_set_workers(bid, 8)
    var b = city.get_building(bid)
    b.figure_spawn_delay = 0

    var spots = test240_place_tree_near(bid, 0)
    if (!terrain.is({ x: spots.tx, y: spots.ty }, TERRAIN_TREE)) {
        return test240_fail('tree tile missing')
    }

    if (wood_cutter_can_spawn_lumberjack(b)) {
        return test240_fail('OG spawn should block on ungrown tree')
    }
    if (b.citizen_found_timber()) {
        return test240_fail('citizen_found_timber should be false for ungrown tree')
    }
    if (!b.citizen_found_terrain(TERRAIN_TREE)) {
        return test240_fail('citizen_found_terrain(TREE) should see ungrown tree')
    }
    __log_marker('test240_ungrown_blocks_og')

    game_features.set('gameplay_change_wood_cutter_single_gatherer', true)
    if (!wood_cutter_can_spawn_lumberjack(b)) {
        return test240_fail('remake feature should allow spawn on any TERRAIN_TREE')
    }
    game_features.set('gameplay_change_wood_cutter_single_gatherer', false)
    __log_marker('test240_feature_allows_any_tree')

    __test_map_set_vegetation_growth(spots.tx, spots.ty, 255)
    __test_map_routing_update_land()
    if (!b.citizen_found_timber()) {
        return test240_fail('citizen_found_timber should be true for grown tree')
    }
    if (!wood_cutter_can_spawn_lumberjack(b)) {
        return test240_fail('OG spawn should allow grown timber')
    }
    __log_marker('test240_grown_allows_og')

    var before = b.stored_resource(RESOURCE_TIMBER)
    var fid = test_figure_create(FIGURE_LUMBERJACK, spots.rx, spots.ry)
    if (!fid) {
        return test240_fail('create lumberjack failed')
    }
    test_figure_set_home(fid, bid)
    __test_figure_set_action(fid, ACTION_4_LUMBERJACK_RETURN_HOME)
    // Already on road_access: do_goto only resolves DIR_FIGURE_NONE at tile-center.
    var delivered = false
    for (var tick = 0; tick < 64; tick++) {
        if (!__test_figure_is_alive(fid)) {
            delivered = true
            break
        }
        __test_figure_action_perform(fid)
        if (b.stored_resource(RESOURCE_TIMBER) - before >= 25) {
            delivered = true
            break
        }
    }

    var after = b.stored_resource(RESOURCE_TIMBER)
    if (after - before != 25) {
        return test240_fail('return home should store +25 timber, before=' + before
            + ' after=' + after + ' alive=' + __test_figure_is_alive(fid)
            + ' action=' + __test_figure_get_action(fid))
    }
    __log_marker('test240_return_home_delivered')

    if (__test_figure_is_alive(fid)) {
        return test240_fail('lumberjack should poof after delivering timber')
    }
    if (!delivered) {
        return test240_fail('return home did not complete')
    }
    __log_marker('test240_return_home_poofed')

    game_features.set('gameplay_change_wood_cutter_single_gatherer', __test240_feat_prev)
    __test240_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test240_ok
        && __test_find_inlog('[test-marker] test240_ungrown_blocks_og')
        && __test_find_inlog('[test-marker] test240_feature_allows_any_tree')
        && __test_find_inlog('[test-marker] test240_grown_allows_og')
        && __test_find_inlog('[test-marker] test240_return_home_delivered')
        && __test_find_inlog('[test-marker] test240_return_home_poofed')
}

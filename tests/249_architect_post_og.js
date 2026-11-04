// OG Architect's Post / FIG_ENGINEER:
//   labor seeker limit 101, roam 640, repair subtracts risk_reduction_amount
//   (incl. wall tiles), CREATED → ENTER_EXIT → roam under gameplay_og_architect.
// Markers:
//   [test-marker] architect_og_config_ok
//   [test-marker] architect_og_repair_subtract_ok
//   [test-marker] architect_og_wall_repair_ok
//   [test-marker] architect_og_created_exit_ok
//   [test-marker] architect_remake_zero_ok

var __test249_ok = false
var __test249_feat_prev = null
var __test249_patrol_prev = null

function test249_fail(msg) {
    __log_info_native('[test:249] FAIL: ' + msg)
    if (__test249_feat_prev !== null) {
        game_features.set('gameplay_og_architect', __test249_feat_prev)
    }
    if (__test249_patrol_prev !== null) {
        game_features.set('gameplay_change_architect_patrol_most_damaged', __test249_patrol_prev)
    }
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:249] architect post OG behavior')
    test_ensure_city_session('data/default.map')

    __test249_feat_prev = game_features.get('gameplay_og_architect')
    __test249_patrol_prev = game_features.get('gameplay_change_architect_patrol_most_damaged')
    game_features.set('gameplay_change_architect_patrol_most_damaged', false)

    var cfg = building_architect_post
    if (!cfg) {
        return test249_fail('missing building_architect_post config')
    }
    if ((cfg.min_houses_coverage | 0) !== 101) {
        return test249_fail('min_houses_coverage want 101 got ' + cfg.min_houses_coverage)
    }
    if ((cfg.building_size | 0) !== 1) {
        return test249_fail('building_size want 1 got ' + cfg.building_size)
    }
    if ((cfg.laborers[0] | 0) !== 5) {
        return test249_fail('laborers want 5 got ' + cfg.laborers[0])
    }
    if ((__test_figure_type_max_roam(FIGURE_ARCHITECT) | 0) !== 640) {
        return test249_fail('architect max_roam want 640')
    }
    __log_marker('architect_og_config_ok')

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    // --- OG repair: absolute subtract, not zero ---
    game_features.set('gameplay_og_architect', true)
    var hut = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx, cy)
    if (!hut) {
        return test249_fail('create hut failed')
    }
    var hut_b = city.get_building(hut)
    hut_b.collapse_risk = 250
    var arch = test_figure_create(FIGURE_ARCHITECT, cx, cy)
    if (!arch) {
        return test249_fail('create architect for repair failed')
    }
    __test_figure_provide_service(arch)
    var after = hut_b.collapse_risk | 0
    var amount = (figure_architector.risk_reduction_amount | 0) || 100
    var expect = 250 - amount
    if (expect < 0) {
        expect = 0
    }
    if (after !== expect) {
        return test249_fail('OG repair want ' + expect + ' got ' + after + ' (amount=' + amount + ')')
    }
    __log_marker('architect_og_repair_subtract_ok')

    // --- OG wall tile repair ---
    var wx = cx + 2
    var wy = cy
    __test_make_wall(wx, wy)
    __test_map_building_damage_set(wx, wy, 180)
    var wall_arch = test_figure_create(FIGURE_ARCHITECT, wx, wy)
    if (!wall_arch) {
        return test249_fail('create architect for wall failed')
    }
    __test_figure_provide_service(wall_arch)
    var wall_left = __test_map_building_damage_get(wx, wy) | 0
    var wall_expect = 180 - amount
    if (wall_expect < 0) {
        wall_expect = 0
    }
    if (wall_left !== wall_expect) {
        return test249_fail('OG wall repair want ' + wall_expect + ' got ' + wall_left)
    }
    __log_marker('architect_og_wall_repair_ok')

    // --- OG CREATED → ENTER_EXIT → roam (spawn on road_access like create_roaming_figure) ---
    var post_x = cx + 4
    var post_y = cy
    var road_x = post_x + 1
    var road_y = post_y
    var post = __test_building_create(BUILDING_ARCHITECT_POST, post_x, post_y)
    if (!post) {
        return test249_fail('create architect post failed')
    }
    __test_make_road(road_x, road_y)
    __test_building_set_road_access(post, road_x, road_y)
    __test_building_set_workers(post, 5)
    var spawn_fid = test_figure_create(FIGURE_ARCHITECT, road_x, road_y)
    if (!spawn_fid) {
        return test249_fail('create architect for spawn path failed')
    }
    __test_figure_set_home(spawn_fid, post)
    __test_building_set_figure_slot(post, BUILDING_SLOT_SERVICE, spawn_fid)
    __test_figure_set_action(spawn_fid, ACTION_1_ENGINEER_CREATED)
    // wait_ticks starts 0 → first action tick exits CREATED into ENTER_EXIT (or roam if already done).
    __test_figure_action_perform(spawn_fid)
    var st1 = __test_figure_get_action(spawn_fid) | 0
    if (st1 !== ACTION_2_ENGINEER_ENTERING_EXITING && st1 !== ACTION_3_ENGINEER_ROAMING) {
        return test249_fail('after CREATED want ENTER_EXIT/ROAMING got ' + st1)
    }
    // Drive ENTER_EXIT until roam (already-on-road finishes in one cross-country tick).
    for (var i = 0; i < 8; i++) {
        var st = __test_figure_get_action(spawn_fid) | 0
        if (st === ACTION_3_ENGINEER_ROAMING) {
            break
        }
        if (st !== ACTION_2_ENGINEER_ENTERING_EXITING && st !== ACTION_1_ENGINEER_CREATED) {
            return test249_fail('spawn path unexpected action ' + st)
        }
        __test_figure_action_perform(spawn_fid)
    }
    if ((__test_figure_get_action(spawn_fid) | 0) !== ACTION_3_ENGINEER_ROAMING) {
        return test249_fail('never reached ROAMING, stuck at ' + __test_figure_get_action(spawn_fid))
    }
    __log_marker('architect_og_created_exit_ok')

    // --- Remake default: full clear (risk_reduction_strength 100) ---
    game_features.set('gameplay_og_architect', false)
    hut_b.collapse_risk = 250
    var remake_arch = test_figure_create(FIGURE_ARCHITECT, cx, cy)
    if (!remake_arch) {
        return test249_fail('create remake architect failed')
    }
    __test_figure_provide_service(remake_arch)
    if ((hut_b.collapse_risk | 0) !== 0) {
        return test249_fail('remake repair want 0 got ' + hut_b.collapse_risk)
    }
    __log_marker('architect_remake_zero_ok')

    game_features.set('gameplay_og_architect', __test249_feat_prev)
    game_features.set('gameplay_change_architect_patrol_most_damaged', __test249_patrol_prev)
    __test249_ok = true
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'architect_og_config_ok',
        'architect_og_repair_subtract_ok',
        'architect_og_wall_repair_ok',
        'architect_og_created_exit_ok',
        'architect_remake_zero_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:249] missing marker: ' + markers[i])
            return false
        }
    }
    return __test249_ok
}

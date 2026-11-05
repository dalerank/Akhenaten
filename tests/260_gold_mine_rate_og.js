// OG gold mine: produce_uptick = num_workers per day (progress_max 200).
// Remake feature gameplay_change_goldmine_reduced_production: workers/10.
// Markers:
//   [test-marker] gold_mine_rate_og_ok

var __test260_ok = false
var __test260_feat_prev = false

function test260_fail(msg) {
    __log_info_native('[test:260] ' + msg)
    game_features.set('gameplay_change_goldmine_reduced_production', __test260_feat_prev)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:260] gold mine OG worker rate')
    __test260_feat_prev = !!game_features.get('gameplay_change_goldmine_reduced_production')
    game_features.set('gameplay_change_goldmine_reduced_production', false)

    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    terrain.add({ x: cx + 2, y: cy }, TERRAIN_ROCK | TERRAIN_ORE)
    terrain.add({ x: cx + 2, y: cy + 1 }, TERRAIN_ROCK | TERRAIN_ORE)
    terrain.add({ x: cx + 1, y: cy }, TERRAIN_ROCK | TERRAIN_ORE)
    terrain.add({ x: cx + 1, y: cy + 1 }, TERRAIN_ROCK | TERRAIN_ORE)
    __test_map_golden_init()

    var bid = test_building_place(BUILDING_GOLD_MINE, cx, cy)
    if (!bid) {
        bid = __test_building_create(BUILDING_GOLD_MINE, cx, cy)
    }
    if (!bid) {
        test260_fail('gold mine place/create failed')
        return
    }

    __test_building_set_workers(bid, 12)
    city.get_building(bid).houses_covered = 100
    __test_building_update_day(bid)
    var after_day = __building_industry_progress(bid)

    __test_city_industry_update_production()
    var after_og = __building_industry_progress(bid)
    // OG: +12 workers (progress starts at after_day, usually 0 or 1 from update_day)
    if (after_og - after_day != 12) {
        test260_fail('OG tick expected +12 got +' + (after_og - after_day)
            + ' (before=' + after_day + ' after=' + after_og + ')')
        return
    }

    game_features.set('gameplay_change_goldmine_reduced_production', true)
    __test_city_industry_update_production()
    var after_reduced = __building_industry_progress(bid)
    // Remake: floor(12/10)=1
    if (after_reduced - after_og != 1) {
        test260_fail('reduced tick expected +1 got +' + (after_reduced - after_og)
            + ' (before=' + after_og + ' after=' + after_reduced + ')')
        return
    }

    __test260_ok = true
    __log_info_native('[test-marker] gold_mine_rate_og_ok')
    game_features.set('gameplay_change_goldmine_reduced_production', __test260_feat_prev)
    __test_signal_ready()
}

function check_valid() {
    return __test260_ok && __test_find_inlog('[test-marker] gold_mine_rate_og_ok')
}

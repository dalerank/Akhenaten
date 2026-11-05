// OG limestone quarry: kind_b rock placement (not ore rock), produce needs
// houses_covered >= 1. Remake feature: weekly houses-in-radius coverage.
// Markers:
//   [test-marker] limestone_quarry_og_ok

var __test259_ok = false
var __test259_feat_prev = false

function test259_fail(msg) {
    __log_info_native('[test:259] ' + msg)
    game_features.set('gameplay_change_industry_nearby_houses', __test259_feat_prev)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:259] limestone quarry kind_b + houses_covered')
    __test259_feat_prev = !!game_features.get('gameplay_change_industry_nearby_houses')

    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0

    // --- Placement: ore rock alone is not kind_b ---
    terrain.add({ x: cx + 2, y: cy }, TERRAIN_ROCK | TERRAIN_ORE)
    terrain.add({ x: cx + 2, y: cy + 1 }, TERRAIN_ROCK | TERRAIN_ORE)
    if (!test_planner_enter_build_mode(BUILDING_LIMESTONE_QUARRY)) {
        test259_fail('enter limestone build mode failed')
        return
    }
    city_planner.update(cx, cy)
    if (city_planner.can_be_placed() == CAN_PLACE) {
        test259_fail('limestone must refuse ore-only rock (kind_b)')
        return
    }
    test_planner_exit_build_mode()

    // Plain stone quarry still accepts any ROCK bit
    if (!test_planner_enter_build_mode(BUILDING_STONE_QUARRY)) {
        test259_fail('enter stone quarry build mode failed')
        return
    }
    city_planner.update(cx, cy)
    if (city_planner.can_be_placed() != CAN_PLACE) {
        test259_fail('stone quarry should accept ore rock (has_bit1)')
        return
    }
    test_planner_exit_build_mode()

    // Clear ore rock, place plain rock for limestone
    terrain.remove({ x: cx + 2, y: cy }, TERRAIN_ROCK | TERRAIN_ORE)
    terrain.remove({ x: cx + 2, y: cy + 1 }, TERRAIN_ROCK | TERRAIN_ORE)
    terrain.add({ x: cx + 2, y: cy }, TERRAIN_ROCK)
    terrain.add({ x: cx + 2, y: cy + 1 }, TERRAIN_ROCK)
    __test_map_quarry_deposits_init()

    if (!test_planner_enter_build_mode(BUILDING_LIMESTONE_QUARRY)) {
        test259_fail('re-enter limestone build mode failed')
        return
    }
    city_planner.update(cx, cy)
    if (city_planner.can_be_placed() != CAN_PLACE) {
        test259_fail('limestone should accept plain rock (kind_b)')
        return
    }
    test_planner_exit_build_mode()

    var bid = test_building_place(BUILDING_LIMESTONE_QUARRY, cx, cy)
    if (!bid) {
        bid = __test_building_create(BUILDING_LIMESTONE_QUARRY, cx, cy)
    }
    if (!bid) {
        test259_fail('limestone place/create failed')
        return
    }

    __test_building_set_workers(bid, 8)
    __test_building_update_day(bid)
    if (__building_industry_progress(bid) != 1) {
        test259_fail('progress after update_day=' + __building_industry_progress(bid))
        return
    }

    // OG: no houses_covered → no production
    city.get_building(bid).houses_covered = 0
    __test_city_industry_update_production()
    if (__building_industry_progress(bid) != 1) {
        test259_fail('without houses_covered expected progress 1 got ' + __building_industry_progress(bid))
        return
    }

    city.get_building(bid).houses_covered = 100
    __test_city_industry_update_production()
    if (__building_industry_progress(bid) != 5) {
        test259_fail('with houses_covered expected progress 5 got ' + __building_industry_progress(bid))
        return
    }

    // Remake weekly radius coverage (building nearby_houses_radius + need_nearby_houses_for_work)
    game_features.set('gameplay_change_industry_nearby_houses', true)
    city.get_building(bid).houses_covered = 0

    var house_id = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, cx + 3, cy + 3)
    if (!house_id) {
        test259_fail('house create failed')
        return
    }
    __test_house_set_population(house_id, 5)

    __test_city_industry_update_nearby_houses_weekly()
    if (city.get_building(bid).houses_covered < 1) {
        test259_fail('weekly radius scan should set houses_covered, got '
            + city.get_building(bid).houses_covered)
        return
    }

    game_features.set('gameplay_change_industry_nearby_houses', __test259_feat_prev)

    __log_marker('limestone_quarry_og_ok')
    __test259_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test259_ok && __test_find_inlog('[test-marker] limestone_quarry_og_ok')
}

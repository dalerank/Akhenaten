// OG farm_reduce_fertility_of: a floodplain harvest takes 50% of the soil fertility
// from an irrigated farm and 80% from a dry one (never below 1).

var __test271_ok = false
var __test271_feat_prev = false
var FERT_WITH_MALUS = 1

function test271_fail(msg) {
    __log_info_native('[test:271] FAIL: ' + msg)
    game_features.set('gameplay_change_soil_depletion', __test271_feat_prev)
    __test_signal_ready()
}

function test271_set_fert(t, value) {
    for (var dx = 0; dx < 3; dx++) {
        for (var dy = 0; dy < 3; dy++) {
            __map_set_fertility_at({ x: t.x + dx, y: t.y + dy }, value)
        }
    }
}

function test271_harvest(bid, t) {
    city.figures.remove_figures(FIGURE_CART_PUSHER)
    __test_building_set_figure_slot(bid, BUILDING_SLOT_CARTPUSHER, 0)
    test271_set_fert(t, 80)
    __building_farm_set_progress(bid, 1000)
    __test_farm_harvest_and_clear_osiris(bid)
    return __map_get_fertility_at({ x: t.x + 1, y: t.y + 1 }, FERT_WITH_MALUS)
}

function run_test() {
    __log_info_native('[test:271] farm soil depletion OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __test271_feat_prev = game_features.get('gameplay_change_soil_depletion') === true
    game_features.set('gameplay_change_soil_depletion', false)

    var bid = test_farm_place(BUILDING_FIGS_FARM, TERRAIN_FLOODPLAIN)
    if (!bid) {
        return test271_fail('floodplain fig farm place failed')
    }
    var t = __building_tile(bid)

    var dry = test271_harvest(bid, t)
    if (dry != 16) {
        return test271_fail('dry farm must keep 20% of 80, got ' + dry)
    }
    __log_marker('test271_dry_80_ok')

    terrain.add({ x: t.x, y: t.y }, TERRAIN_IRRIGATION_RANGE)
    var wet = test271_harvest(bid, t)
    if (wet != 40) {
        return test271_fail('irrigated farm must keep 50% of 80, got ' + wet)
    }
    __log_marker('test271_irrigated_50_ok')

    game_features.set('gameplay_change_soil_depletion', __test271_feat_prev)
    __test271_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test271_ok
        && __test_find_inlog('[test-marker] test271_dry_80_ok')
        && __test_find_inlog('[test-marker] test271_irrigated_50_ok')
}

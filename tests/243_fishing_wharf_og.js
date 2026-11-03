// OG fishing wharf: boat return sets fish_caught + figure_spawn_delay;
// spawn_figure then clears both and ships a 100-fish cart (not building storage).
// Remake storage/cart stays behind gameplay_change_fishing_boat_remake.
// Markers:
//   [test-marker] fishing_wharf_og_cart
//   [test-marker] fishing_wharf_remake_storage_cart

var __test243_ok = false
var __test243_remake_prev = false
var __test243_spawn_prev = false

function test243_finish() {
    game_features.set('gameplay_change_fishing_boat_remake', __test243_remake_prev)
    game_features.set('gameplay_fishing_wharf_spawn_boats', __test243_spawn_prev)
    __test_signal_ready()
}

function test243_fail(msg) {
    __log_info_native('[test:243] ' + msg)
    test243_finish()
}

function test243_place_wharf() {
    __scenario_building_allow(BUILDING_FISHING_WHARF, true)
    var bid = test_shoreline_building_place(BUILDING_FISHING_WHARF, 2)
    if (!bid) {
        return 0
    }
    __test_building_set_workers(bid, 6)
    __test_building_force_road_access(bid)
    return bid
}

function test243_og_cart(bid) {
    city.figures.remove_figures(FIGURE_CART_PUSHER)
    __test_fishing_wharf_set_fish_caught(bid, 1)
    __test_building_set_figure_spawn_delay(bid, 1)

    var spawned = __test_fishing_wharf_spawn_figure(bid)
    if (spawned != 1) {
        test243_fail('OG cart spawn want 1 got ' + spawned)
        return false
    }
    if (__test_fishing_wharf_fish_caught(bid) != 0) {
        test243_fail('fish_caught should clear after cart, got ' + __test_fishing_wharf_fish_caught(bid))
        return false
    }
    if (__test_building_figure_spawn_delay(bid) != 0) {
        test243_fail('figure_spawn_delay should clear, got ' + __test_building_figure_spawn_delay(bid))
        return false
    }

    var wharf = city.get_building(bid)
    if (wharf.stored_resource(RESOURCE_FISH) != 0) {
        test243_fail('OG path must not use building storage, stored=' + wharf.stored_resource(RESOURCE_FISH))
        return false
    }

    var cart = wharf.get_figure(BUILDING_SLOT_CARTPUSHER)
    if (!cart || !cart.valid) {
        test243_fail('missing cartpusher after OG spawn')
        return false
    }
    var amount = __test_figure_carrying_amount(cart.id)
    var resource = __test_figure_resource(cart.id)
    if (resource != RESOURCE_FISH || amount != 100) {
        test243_fail('cart want fish/100 got resource=' + resource + ' amount=' + amount)
        return false
    }
    __log_marker('fishing_wharf_og_cart')
    return true
}

function test243_remake_storage_cart(bid) {
    city.figures.remove_figures(FIGURE_CART_PUSHER)
    game_features.set('gameplay_change_fishing_boat_remake', true)

    var wharf = city.get_building(bid)
    // remove_figures poofs carts but leaves the building slot pointing at the
    // dead figure; has_figure_of_type still matches by type, so clear the slot.
    __test_building_set_figure_slot(bid, BUILDING_SLOT_CARTPUSHER, 0)
    wharf.store_resource(RESOURCE_FISH, 100)
    __test_fishing_wharf_set_fish_caught(bid, 0)
    __test_building_set_figure_spawn_delay(bid, 0)

    if (wharf.stored_resource(RESOURCE_FISH) < 100) {
        test243_fail('remake store_resource failed, stored=' + wharf.stored_resource(RESOURCE_FISH))
        return false
    }

    var spawned = __test_fishing_wharf_spawn_figure(bid)
    if (spawned != 1) {
        test243_fail('remake cart spawn want 1 got ' + spawned)
        return false
    }
    if (wharf.stored_resource(RESOURCE_FISH) != 0) {
        test243_fail('remake cart should consume storage, left=' + wharf.stored_resource(RESOURCE_FISH))
        return false
    }
    __log_marker('fishing_wharf_remake_storage_cart')
    return true
}

function run_test() {
    __log_info_native('[test:243] fishing wharf OG cart')

    __test243_remake_prev = game_features.get('gameplay_change_fishing_boat_remake') === true
    __test243_spawn_prev = game_features.get('gameplay_fishing_wharf_spawn_boats') === true
    if (game_features.default('gameplay_change_fishing_boat_remake')
        || game_features.default('gameplay_fishing_wharf_spawn_boats')) {
        return test243_fail('fishing remake flags must default OFF')
    }
    game_features.set('gameplay_change_fishing_boat_remake', false)
    game_features.set('gameplay_fishing_wharf_spawn_boats', false)

    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test243_place_wharf()
    if (!bid) {
        return test243_fail('fishing wharf place failed')
    }
    if (!test243_og_cart(bid)) {
        return
    }
    if (!test243_remake_storage_cart(bid)) {
        return
    }

    __test243_ok = true
    test243_finish()
}

function check_valid() {
    return __test243_ok
        && __test_find_inlog('[test-marker] fishing_wharf_og_cart')
        && __test_find_inlog('[test-marker] fishing_wharf_remake_storage_cart')
}

// Senet House spawn_figure (JS): OG beer-per-trip by difficulty funds senet player;
// no beer => no senet player. Drunkard must not drain that beer budget.

var __test219_ok = false

function test219_fail(msg) {
    __log_info_native('[test:219] FAIL: ' + msg)
    __test_signal_ready()
}

function test219_beer_need() {
    var amounts = [5, 10, 20, 40, 60]
    var i = game.difficulty
    if (i < 0) {
        i = 0
    }
    if (i >= amounts.length) {
        i = amounts.length - 1
    }
    return amounts[i]
}

function run_test() {
    __log_info_native('[test:219] senet house beer-per-trip spawn')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)

    var bid = test_building_place(BUILDING_SENET_HOUSE, -1, -1)
    if (!bid) {
        test219_fail('place failed')
        return
    }

    var b = city.get_building(bid)
    if (!b || !b.valid) {
        test219_fail('building missing after place')
        return
    }

    var zt = __building_tile(bid)
    for (var dx = 0; dx < 4; dx++) {
        terrain.add({ x: zt.x + dx, y: zt.y + 4 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_check_kingdome_access()

    __test_building_set_workers(bid, 25)
    b = city.get_building(bid)
    b.has_road_access = true
    b.figure_spawn_delay = 100

    city.figures.remove_figures(FIGURE_SENET_PLAYER)
    city.figures.remove_figures(FIGURE_DRUNKARD)

    // No beer: must not spawn senet player.
    building_senet_house_spawn_figure({ bid: bid })
    if (__test_count_figures(FIGURE_SENET_PLAYER) > 0) {
        test219_fail('senet player spawned without beer')
        return
    }
    __log_marker('test219_no_beer_no_senet')

    var need = test219_beer_need()
    b = city.get_building(bid)
    b.consume_resource(RESOURCE_BEER, -need)
    b.figure_spawn_delay = 100
    var beer_before = b.stored_resource(RESOURCE_BEER)
    if (beer_before < need) {
        test219_fail('failed to stock beer need=' + need + ' got=' + beer_before)
        return
    }

    city.figures.remove_figures(FIGURE_SENET_PLAYER)
    city.figures.remove_figures(FIGURE_DRUNKARD)
    building_senet_house_spawn_figure({ bid: bid })

    if (__test_count_figures(FIGURE_SENET_PLAYER) < 1) {
        test219_fail('expected senet player with beer need=' + need
            + ' difficulty=' + game.difficulty)
        return
    }
    __log_marker('test219_senet_spawned')

    b = city.get_building(bid)
    var beer_after = b.stored_resource(RESOURCE_BEER)
    if (beer_after != beer_before - need) {
        test219_fail('beer consume mismatch before=' + beer_before
            + ' after=' + beer_after + ' need=' + need)
        return
    }
    __log_marker('test219_beer_consumed:' + need)

    var ent = city.get_entertainment_building(bid)
    if (!ent || !(ent.juggler_visited > 0)) {
        test219_fail('expected plays timer after beer-funded spawn'
            + ' juggler_visited=' + (ent ? ent.juggler_visited : -1))
        return
    }
    __log_marker('test219_plays_active')

    // Drunkard path must not steal remaining beer when SERVICE slot is busy.
    var beer_mid = b.stored_resource(RESOURCE_BEER)
    b.consume_resource(RESOURCE_BEER, -(need + 5))
    b = city.get_building(bid)
    beer_before = b.stored_resource(RESOURCE_BEER)
    b.figure_spawn_delay = 100
    building_senet_house_spawn_figure({ bid: bid })
    b = city.get_building(bid)
    if (b.stored_resource(RESOURCE_BEER) != beer_before) {
        test219_fail('drunkard/retry drained beer while senet slot occupied'
            + ' before=' + beer_before + ' after=' + b.stored_resource(RESOURCE_BEER))
        return
    }
    __log_marker('test219_no_extra_beer_drain')

    __test219_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test219_ok
        && __test_find_inlog('[test-marker] test219_no_beer_no_senet')
        && __test_find_inlog('[test-marker] test219_senet_spawned')
        && __test_find_inlog('[test-marker] test219_beer_consumed:')
        && __test_find_inlog('[test-marker] test219_plays_active')
        && __test_find_inlog('[test-marker] test219_no_extra_beer_drain')
}

// Cleopatra Zoo (BUILDING_ZOO): place 6×6, stock dual inputs, spawn zookeeper.
// Markers:
//   [test-marker] test_building_placed:type_<BUILDING_ZOO>:...
//   [test-marker] zoo_stocked_ok
//   [test-marker] zoo_spawn_ok
//   [test-marker] zoo_no_show_ok
//   [test-marker] zoo_no_spawn_without_stock

var __test65_bid = null
var __test65_stock_ok = false
var __test65_spawn_ok = false
var __test65_no_show_ok = false
var __test65_no_spawn_ok = false

function test65_keep_staffed(bid) {
    var b = city.get_building(bid)
    if (!b) {
        return null
    }
    // labor.update (tick 25) clears workers without population — re-staff every frame.
    b.has_road_access = true
    b.num_workers = b.max_workers
    return b
}

function run_test() {
    __log_info_native('[test:65] zoo place + stock + spawn')
    test_reload_city_session('data/default.map')
    __test_set_treasury(50000)
    game.paused = false
    game_features.gameopt_game_speed = 100

    if (!__scenario_building_allowed(BUILDING_ZOO)) {
        __scenario_building_allow(BUILDING_ZOO, true)
    }

    // Both inputs available so C++ on_place_checks does not remove the zoo.
    city.resources.set_produce(RESOURCE_STRAW, true)
    city.resources.set_produce(RESOURCE_GAMEMEAT, true)

    var bid = test_building_place(BUILDING_ZOO, -1, -1)
    __test65_bid = bid
    if (!bid) {
        __log_info_native('[test:65] test_building_place failed')
        __test_signal_ready()
        return
    }

    var size = __building_static_building_size(BUILDING_ZOO)
    if (size != 6) {
        __log_info_native('[test:65] expected building_size 6, got ' + size)
        __test_signal_ready()
        return
    }

    var b = city.get_building(bid)
    if (!b || !b.valid) {
        __log_info_native('[test:65] building missing after place (removed by place_checks?)')
        __test_signal_ready()
        return
    }

    // consume_resource(negative) adds into sparse building storage (see test 28).
    b.consume_resource(RESOURCE_STRAW, -100)
    b.consume_resource(RESOURCE_GAMEMEAT, -100)
    b = city.get_building(bid)
    if (b.stored_resource(RESOURCE_STRAW) < 100 || b.stored_resource(RESOURCE_GAMEMEAT) < 100) {
        __log_info_native('[test:65] failed to stock straw/gamemeat'
            + ' straw=' + b.stored_resource(RESOURCE_STRAW)
            + ' meat=' + b.stored_resource(RESOURCE_GAMEMEAT))
        __test_signal_ready()
        return
    }
    __log_marker('zoo_stocked_ok')
    __test65_stock_ok = true

    // Roads south of 6×6 so spawn uses a valid road_access tile (flag alone is not enough).
    var zt = __building_tile(bid)
    for (var dx = 0; dx < 6; dx++) {
        terrain.add({ x: zt.x + dx, y: zt.y + 6 }, TERRAIN_ROAD)
    }
    __test_update_road_network()
    __test_check_kingdome_access()

    city.figures.remove_figures(FIGURE_ZOOKEEPER)
    test65_keep_staffed(bid)
    b.figure_spawn_delay = 0

    var straw_before = b.stored_resource(RESOURCE_STRAW)
    var meat_before = b.stored_resource(RESOURCE_GAMEMEAT)

    var spawned = false
    var i
    // OG delay at full staff is 7 days (50 ticks); one trip pays walker_cost of each input.
    for (i = 0; i < 700; i++) {
        test65_keep_staffed(bid)
        __test_pump_frames(1)
        if (__test_count_figures(FIGURE_ZOOKEEPER) > 0) {
            spawned = true
            break
        }
    }

    b = city.get_building(bid)
    if (!spawned) {
        __log_info_native('[test:65] no zookeeper spawned with stock+workers+road'
            + ' straw=' + (b ? b.stored_resource(RESOURCE_STRAW) : -1)
            + ' meat=' + (b ? b.stored_resource(RESOURCE_GAMEMEAT) : -1)
            + ' workers=' + (b ? (b.num_workers + '/' + b.max_workers) : '?')
            + ' road=' + (b ? b.has_road_access : '?')
            + ' frames=' + i)
        __test_signal_ready()
        return
    }
    var cost = building_zoo_feed_cost()
    var straw_after = b.stored_resource(RESOURCE_STRAW)
    var meat_after = b.stored_resource(RESOURCE_GAMEMEAT)
    if (straw_after != straw_before - cost || meat_after != meat_before - cost) {
        __log_info_native('[test:65] feed consume mismatch'
            + ' cost=' + cost
            + ' straw ' + straw_before + '->' + straw_after
            + ' meat ' + meat_before + '->' + meat_after)
        __test_signal_ready()
        return
    }
    __log_marker('zoo_spawn_ok')
    __test65_spawn_ok = true

    // Roaming keepers never start a show. Culture counts every staffed zoo as a no-show.
    var zoo = city.get_entertainment_building(bid)
    if (!zoo || zoo.juggler_visited != 0) {
        __log_info_native('[test:65] expected no show timer after spawn'
            + ' juggler_visited=' + (zoo ? zoo.juggler_visited : -1))
        __test_signal_ready()
        return
    }
    __log_marker('zoo_no_show_ok')
    __test65_no_show_ok = true

    // Drain stock and confirm no new spawn once stock is empty.
    city.figures.remove_figures(FIGURE_ZOOKEEPER)
    b = city.get_building(bid)
    b.consume_resource(RESOURCE_STRAW, b.stored_resource(RESOURCE_STRAW))
    b.consume_resource(RESOURCE_GAMEMEAT, b.stored_resource(RESOURCE_GAMEMEAT))

    for (i = 0; i < 200; i++) {
        test65_keep_staffed(bid)
        __test_pump_frames(1)
        if (__test_count_figures(FIGURE_ZOOKEEPER) > 0) {
            __log_info_native('[test:65] zookeeper spawned without stock')
            __test_signal_ready()
            return
        }
    }
    __log_marker('zoo_no_spawn_without_stock')
    __test65_no_spawn_ok = true

    __test_signal_ready()
}

function check_valid() {
    var bid = __test65_bid
    if (!bid) {
        __log_info_native('[test:65] no building id from run_test')
        return false
    }

    if (__building_type(bid) != BUILDING_ZOO) {
        __log_info_native('[test:65] wrong building type for id ' + bid + ' type=' + __building_type(bid))
        return false
    }

    var marker = '[test-marker] test_building_placed:type_' + BUILDING_ZOO
    if (!__test_find_inlog(marker)) {
        __log_info_native('[test:65] missing marker: ' + marker)
        return false
    }

    return __test65_stock_ok
        && __test65_spawn_ok
        && __test65_no_show_ok
        && __test65_no_spawn_ok
        && __test_find_inlog('[test-marker] zoo_stocked_ok')
        && __test_find_inlog('[test-marker] zoo_spawn_ok')
        && __test_find_inlog('[test-marker] zoo_no_show_ok')
        && __test_find_inlog('[test-marker] zoo_no_spawn_without_stock')
}

// Artisans' Guild (AG6): with gameplay_sphinx_artisans the carved Sphinx waits for artisans (painting
// stage); stock paint+clay, spawn FIGURE_TOMB_ARTISAN;
// no spawn without paint or without clay.
// Markers:
//   [test-marker] artisans_sphinx_phase6_ok
//   [test-marker] artisans_stocked_ok
//   [test-marker] artisans_spawn_ok
//   [test-marker] artisans_no_spawn_without_paint
//   [test-marker] artisans_no_spawn_without_clay

var __test70_guild_bid = null
var __test70_sphinx_bid = null
var __test70_ok = {
    phase6: false,
    stocked: false,
    spawn: false,
    no_paint: false,
    no_clay: false
}

function test70_keep_staffed(bid) {
    var b = city.get_building(bid)
    if (!b) {
        return null
    }
    // labor.update (tick 25) clears workers without population — re-staff every frame.
    b.has_road_access = true
    b.num_workers = b.max_workers
    return b
}

function test70_place_sphinx_phase6() {
    if (!__scenario_building_allowed(BUILDING_SPHINX)) {
        __scenario_building_allow(BUILDING_SPHINX, true)
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx - 3, y: cy - 9}, {x: cx, y: cy}, {x: 40, y: 40}, {x: 30, y: 30}, {x: 60, y: 40}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_SPHINX, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        bid = test_building_place(BUILDING_SPHINX, -1, -1)
    }
    if (!bid) {
        return 0
    }

    __test_sphinx_set_stage(bid, 16)
    __test_pump_frames(2)
    if (__test_monument_phase(bid) != 16) {
        __log_info_native('[test:70] expected sphinx painting stage 16, got ' + __test_monument_phase(bid))
        return 0
    }
    return bid
}

function run_test() {
    __log_info_native('[test:70] artisans guild spawn / no-resource')
    game_features.set('gameplay_sphinx_artisans', true)
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    game.paused = false
    game_features.gameopt_game_speed = 100

    if (!__scenario_building_allowed(BUILDING_ARTISANS_GUILD)) {
        __scenario_building_allow(BUILDING_ARTISANS_GUILD, true)
    }

    city.resources.set_produce(RESOURCE_PAINT, true)
    city.resources.set_produce(RESOURCE_CLAY, true)

    var sphinx_bid = test70_place_sphinx_phase6()
    __test70_sphinx_bid = sphinx_bid
    if (!sphinx_bid) {
        __log_info_native('[test:70] failed to place sphinx at phase 6')
        __test_signal_ready()
        return
    }
    __log_marker('artisans_sphinx_phase6_ok')
    __test70_ok.phase6 = true

    var guild_bid = test_building_place(BUILDING_ARTISANS_GUILD, -1, -1)
    __test70_guild_bid = guild_bid
    if (!guild_bid) {
        __log_info_native('[test:70] test_building_place BUILDING_ARTISANS_GUILD failed')
        __test_signal_ready()
        return
    }

    var b = city.get_building(guild_bid)
    if (!b || !b.valid) {
        __log_info_native('[test:70] guild missing after place')
        __test_signal_ready()
        return
    }

    b.consume_resource(RESOURCE_PAINT, -100)
    b.consume_resource(RESOURCE_CLAY, -100)
    b = city.get_building(guild_bid)
    if (b.stored_resource(RESOURCE_PAINT) < 100 || b.stored_resource(RESOURCE_CLAY) < 100) {
        __log_info_native('[test:70] failed to stock paint/clay'
            + ' paint=' + b.stored_resource(RESOURCE_PAINT)
            + ' clay=' + b.stored_resource(RESOURCE_CLAY))
        __test_signal_ready()
        return
    }
    __log_marker('artisans_stocked_ok')
    __test70_ok.stocked = true

    city.figures.remove_figures(FIGURE_TOMB_ARTISAN)
    test70_keep_staffed(guild_bid)

    var spawned = false
    var i
    for (i = 0; i < 400; i++) {
        test70_keep_staffed(guild_bid)
        __test_pump_frames(1)
        if (__test_count_figures(FIGURE_TOMB_ARTISAN) > 0) {
            spawned = true
            break
        }
    }

    b = city.get_building(guild_bid)
    if (!spawned) {
        __log_info_native('[test:70] no tomb artisan spawned with stock+workers+road+phase6'
            + ' paint=' + (b ? b.stored_resource(RESOURCE_PAINT) : -1)
            + ' clay=' + (b ? b.stored_resource(RESOURCE_CLAY) : -1)
            + ' workers=' + (b ? (b.num_workers + '/' + b.max_workers) : '?')
            + ' road=' + (b ? b.has_road_access : '?')
            + ' frames=' + i)
        __test_signal_ready()
        return
    }
    __log_marker('artisans_spawn_ok')
    __test70_ok.spawn = true

    // Drain paint — no new spawn
    city.figures.remove_figures(FIGURE_TOMB_ARTISAN)
    b = city.get_building(guild_bid)
    b.consume_resource(RESOURCE_PAINT, b.stored_resource(RESOURCE_PAINT))
    b.consume_resource(RESOURCE_CLAY, -100)

    for (i = 0; i < 200; i++) {
        test70_keep_staffed(guild_bid)
        __test_pump_frames(1)
        if (__test_count_figures(FIGURE_TOMB_ARTISAN) > 0) {
            __log_info_native('[test:70] tomb artisan spawned without paint')
            __test_signal_ready()
            return
        }
    }
    __log_marker('artisans_no_spawn_without_paint')
    __test70_ok.no_paint = true

    // Drain clay (restore paint) — no new spawn
    city.figures.remove_figures(FIGURE_TOMB_ARTISAN)
    b = city.get_building(guild_bid)
    b.consume_resource(RESOURCE_PAINT, -100)
    b.consume_resource(RESOURCE_CLAY, b.stored_resource(RESOURCE_CLAY))

    for (i = 0; i < 200; i++) {
        test70_keep_staffed(guild_bid)
        __test_pump_frames(1)
        if (__test_count_figures(FIGURE_TOMB_ARTISAN) > 0) {
            __log_info_native('[test:70] tomb artisan spawned without clay')
            __test_signal_ready()
            return
        }
    }
    __log_marker('artisans_no_spawn_without_clay')
    __test70_ok.no_clay = true

    __test_signal_ready()
}

function check_valid() {
    game_features.set('gameplay_sphinx_artisans', false)
    if (!__test70_guild_bid) {
        __log_info_native('[test:70] no guild id from run_test')
        return false
    }
    if (__building_type(__test70_guild_bid) != BUILDING_ARTISANS_GUILD) {
        __log_info_native('[test:70] wrong guild type id=' + __test70_guild_bid
            + ' type=' + __building_type(__test70_guild_bid))
        return false
    }

    return __test70_ok.phase6
        && __test70_ok.stocked
        && __test70_ok.spawn
        && __test70_ok.no_paint
        && __test70_ok.no_clay
        && __test_find_inlog('[test-marker] artisans_sphinx_phase6_ok')
        && __test_find_inlog('[test-marker] artisans_stocked_ok')
        && __test_find_inlog('[test-marker] artisans_spawn_ok')
        && __test_find_inlog('[test-marker] artisans_no_spawn_without_paint')
        && __test_find_inlog('[test-marker] artisans_no_spawn_without_clay')
}

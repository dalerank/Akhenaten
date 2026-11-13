// Artisans guild (OG building_artisans_guild_spawn_figure), driven through the Enhanced
// gameplay_sphinx_artisans painting stage (needs paint and clay):
// - a clay trip is sent before a paint trip, each trip takes one load (100) of one material;
// - no stock, no artisan;
// - staffing caps active artisans at 1/2/3/4 for 25/50/75/100%;
// - the guild animates only with paint in stock.
// Markers:
//   [test-marker] artisans_sphinx_phase6_ok
//   [test-marker] artisans_clay_first_ok
//   [test-marker] artisans_paint_trip_ok
//   [test-marker] artisans_no_spawn_without_stock
//   [test-marker] artisans_staffing_cap_ok
//   [test-marker] artisans_anim_needs_paint_ok

var __test70_guild_bid = null
var __test70_ok = {}
var __test70_workers = -1

function test70_keep_staffed(bid) {
    var b = city.get_building(bid)
    if (!b) {
        return null
    }
    // labor.update (tick 25) clears workers without population — re-staff every frame.
    b.has_road_access = true
    b.num_workers = __test70_workers >= 0 ? __test70_workers : b.max_workers
    return b
}

function test70_place_sphinx_painting() {
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

// Pumps until a new artisan appears in the guild's service slot; returns its figure id.
function test70_slot_figure(guild_bid) {
    var f = city.get_building(guild_bid).get_figure(BUILDING_SLOT_SERVICE)
    return (f && f.valid && f.type == FIGURE_TOMB_ARTISAN) ? f.id : 0
}

function test70_stock(guild_bid) {
    var b = city.get_building(guild_bid)
    return b.stored_resource(RESOURCE_PAINT) + b.stored_resource(RESOURCE_CLAY)
}

// A dispatch takes one load from the guild; returns the new artisan (figure ids are recycled).
function test70_wait_spawn(guild_bid, frames) {
    var before = test70_stock(guild_bid)
    for (var i = 0; i < frames; i++) {
        test70_keep_staffed(guild_bid)
        __test_pump_frames(1)
        if (test70_stock(guild_bid) < before) {
            return test70_slot_figure(guild_bid)
        }
    }
    return 0
}

function test70_set_stock(b, paint, clay) {
    b.consume_resource(RESOURCE_PAINT, b.stored_resource(RESOURCE_PAINT) - paint)
    b.consume_resource(RESOURCE_CLAY, b.stored_resource(RESOURCE_CLAY) - clay)
}

function test70_fail(msg) {
    __log_info_native('[test:70] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:70] artisans guild OG dispatch')
    game_features.set('gameplay_sphinx_artisans', true)
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    game.paused = false
    game_features.gameopt_game_speed = 100

    if (!__scenario_building_allowed(BUILDING_ARTISANS_GUILD)) {
        __scenario_building_allow(BUILDING_ARTISANS_GUILD, true)
    }

    if (!test70_place_sphinx_painting()) {
        return test70_fail('failed to place sphinx at the painting stage')
    }
    __log_marker('artisans_sphinx_phase6_ok')

    var guild_bid = test_building_place(BUILDING_ARTISANS_GUILD, -1, -1)
    __test70_guild_bid = guild_bid
    if (!guild_bid) {
        return test70_fail('test_building_place BUILDING_ARTISANS_GUILD failed')
    }

    var b = city.get_building(guild_bid)
    city.figures.remove_figures(FIGURE_TOMB_ARTISAN)
    test70_set_stock(b, 100, 100)
    test70_keep_staffed(guild_bid)

    var fid = test70_wait_spawn(guild_bid, 400)
    b = city.get_building(guild_bid)
    if (!fid) {
        return test70_fail('no artisan with paint+clay stock workers=' + b.num_workers + '/' + b.max_workers)
    }
    if (__test_figure_resource(fid) != RESOURCE_CLAY
            || b.stored_resource(RESOURCE_CLAY) != 0 || b.stored_resource(RESOURCE_PAINT) != 100) {
        return test70_fail('first trip should carry clay: res=' + __test_figure_resource(fid)
            + ' clay=' + b.stored_resource(RESOURCE_CLAY) + ' paint=' + b.stored_resource(RESOURCE_PAINT))
    }
    __log_marker('artisans_clay_first_ok')
    __test70_ok.clay_first = true

    fid = test70_wait_spawn(guild_bid, 400)
    b = city.get_building(guild_bid)
    if (!fid || __test_figure_resource(fid) != RESOURCE_PAINT || b.stored_resource(RESOURCE_PAINT) != 0) {
        return test70_fail('second trip should carry paint: fid=' + fid
            + ' res=' + (fid ? __test_figure_resource(fid) : -1) + ' paint=' + b.stored_resource(RESOURCE_PAINT))
    }
    __log_marker('artisans_paint_trip_ok')
    __test70_ok.paint_trip = true

    city.figures.remove_figures(FIGURE_TOMB_ARTISAN)
    if (test70_wait_spawn(guild_bid, 200)) {
        return test70_fail('artisan spawned without stock')
    }
    __log_marker('artisans_no_spawn_without_stock')
    __test70_ok.no_stock = true

    // 50% staffing → at most two artisans out, even with four loads of clay.
    b = city.get_building(guild_bid)
    __test70_workers = Math.ceil(b.max_workers / 2)
    test70_set_stock(b, 0, 400)
    // Dispatched artisans are pinned at work (this map has no road to the sphinx) so they stay out.
    var out = []
    var peak = 0
    var stock = test70_stock(guild_bid)
    for (var i = 0; i < 600; i++) {
        test70_keep_staffed(guild_bid)
        __test_pump_frames(1)
        if (test70_stock(guild_bid) < stock) {
            out.push(test70_slot_figure(guild_bid))
        }
        stock = test70_stock(guild_bid)
        for (var k = 0; k < out.length; k++) {
            if (out[k] && __test_figure_is_alive(out[k])) {
                __test_figure_set_action(out[k], 14)
                __test_figure_set_wait_ticks(out[k], 0)
            }
        }
        peak = Math.max(peak, __test_count_figures(FIGURE_TOMB_ARTISAN))
    }
    if (peak != 2) {
        return test70_fail('50% staffing peak artisans ' + peak + ' (want 2)')
    }
    __log_marker('artisans_staffing_cap_ok')
    __test70_ok.cap = true
    __test70_workers = -1

    city.figures.remove_figures(FIGURE_TOMB_ARTISAN)
    b = test70_keep_staffed(guild_bid)
    test70_set_stock(b, 0, 200)
    __test_building_update_day(guild_bid)
    var anim_without = city.get_building(guild_bid).play_animation
    b = test70_keep_staffed(guild_bid)
    test70_set_stock(b, 100, 200)
    __test_building_update_day(guild_bid)
    var anim_with = city.get_building(guild_bid).play_animation
    if (anim_without || !anim_with) {
        return test70_fail('animation without paint=' + anim_without + ' with paint=' + anim_with)
    }
    __log_marker('artisans_anim_needs_paint_ok')
    __test70_ok.anim = true

    __test_signal_ready()
}

function check_valid() {
    game_features.set('gameplay_sphinx_artisans', false)
    if (!__test70_guild_bid || __building_type(__test70_guild_bid) != BUILDING_ARTISANS_GUILD) {
        __log_info_native('[test:70] no guild')
        return false
    }
    var markers = ['artisans_sphinx_phase6_ok', 'artisans_clay_first_ok', 'artisans_paint_trip_ok',
        'artisans_no_spawn_without_stock', 'artisans_staffing_cap_ok', 'artisans_anim_needs_paint_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:70] missing marker ' + markers[i])
            return false
        }
    }
    return __test70_ok.clay_first && __test70_ok.paint_trip && __test70_ok.no_stock
        && __test70_ok.cap && __test70_ok.anim
}

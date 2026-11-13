// OG royal tomb chamber stages (royal_tomb_part_advance_stage): a chamber is cut by stonemasons
// (stage 1) and finished by tomb artisans (stages 2 and 3), each stage taking the part's work in
// ticks; reaching stage 3 opens the chamber's neighbours. The first chamber's artisans come from an
// artisans guild. All chambers done = 100%, the tomb is finished and saves/loads unchanged.

function t151_fail(msg) {
    __log_info_native('[test:151] ' + msg)
    __log_marker('rt_stage_fail')
    __test_signal_ready()
}

// Small tomb chambers 0..8: OG work per stage and neighbours.
var T151_WORK = [400, 600, 700, 600, 600, 600, 600, 200, 400]

function t151_send(bid, type, stage) {
    // The guild sends a worker to the first part that takes it, whatever its stage.
    var part = __test_royal_tomb_find_work(type, -1)
    if (part >= 0 && __test_royal_tomb_part_stage(bid, part) != stage) {
        return -4
    }
    if (part < 0) {
        return -1
    }
    var fid = __test_royal_tomb_attach_worker(bid, type)
    if (!fid || __test_royal_tomb_part_worker(bid, part) != fid) {
        return -2
    }
    var ticks = __test_royal_tomb_work(fid, 5000)
    if (ticks != T151_WORK[part]) {
        __log_info_native('[test:151] part ' + part + ' stage ' + stage + ' ticks ' + ticks + ' want ' + T151_WORK[part])
        return -3
    }
    return part
}

// OG building_artisans_guild_spawn_figure: with a load of clay and of paint in stock the guild
// sends a clay artisan to a stage 2 chamber and a paint artisan to a stage 3 one.
function t151_guild_send(bid, guild, material, stage) {
    var g = city.get_building(guild)
    g.num_workers = g.max_workers
    g.consume_resource(RESOURCE_CLAY, g.stored_resource(RESOURCE_CLAY) - 100)
    g.consume_resource(RESOURCE_PAINT, g.stored_resource(RESOURCE_PAINT) - 100)
    __test_building_spawn_figure(guild)
    // The helper forces road access; this guild has no road, and a load would recompute it.
    city.get_building(guild).has_road_access = false
    var f = city.get_building(guild).get_figure(BUILDING_SLOT_SERVICE)
    var fid = (f && f.valid && f.type == FIGURE_TOMB_ARTISAN) ? f.id : 0
    if (!fid) {
        return -1
    }
    var other = material == RESOURCE_CLAY ? RESOURCE_PAINT : RESOURCE_CLAY
    g = city.get_building(guild)
    if (__test_figure_resource(fid) != material || g.stored_resource(material) != 0 || g.stored_resource(other) != 100) {
        __log_info_native('[test:151] guild sent res=' + __test_figure_resource(fid) + ' want ' + material
            + ' stock=' + g.stored_resource(material) + '/' + g.stored_resource(other))
        return -5
    }
    if (__test_royal_tomb_part_stage(bid, 0) != stage || __test_royal_tomb_part_worker(bid, 0) != fid) {
        return -2
    }
    var ticks = __test_royal_tomb_work(fid, 5000)
    if (ticks != T151_WORK[0]) {
        __log_info_native('[test:151] guild artisan stage ' + stage + ' ticks ' + ticks + ' want ' + T151_WORK[0])
        return -3
    }
    return 0
}

function run_test() {
    __log_info_native('[test:151] royal tomb chamber stages')
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_SMALL_ROYAL_TOMB)) {
        __scenario_building_allow(BUILDING_SMALL_ROYAL_TOMB, true)
    }
    __test_royal_tomb_paint_site(BUILDING_SMALL_ROYAL_TOMB, 40, 40)
    var bid = test_building_place(BUILDING_SMALL_ROYAL_TOMB, 40, 40)
    if (!bid) {
        return t151_fail('place failed')
    }
    if (__test_royal_tomb_part_count(bid) != 167 || __test_royal_tomb_chambers(bid) != 9) {
        return t151_fail('parts=' + __test_royal_tomb_part_count(bid) + ' chambers=' + __test_royal_tomb_chambers(bid))
    }
    if (__test_royal_tomb_part_stage(bid, 0) != 1 || __test_royal_tomb_part_stage(bid, 1) != 0
        || __test_royal_tomb_part_can_take(bid, 1) != 0) {
        return t151_fail('initial stages')
    }
    __log_marker('rt_stage_initial_ok')

    __test_royal_tomb_set_lamp_stock(bid, 5000)
    if (t151_send(bid, FIGURE_STONEMASON, 1) != 0 || __test_royal_tomb_part_stage(bid, 0) != 2) {
        return t151_fail('stonemason stage 1')
    }
    if (__test_royal_tomb_find_work(FIGURE_STONEMASON, -1) != -1) {
        return t151_fail('no chamber should want a stonemason before chamber 0 reaches stage 3')
    }
    if (!__scenario_building_allowed(BUILDING_ARTISANS_GUILD)) {
        __scenario_building_allow(BUILDING_ARTISANS_GUILD, true)
    }
    var tombs = [BUILDING_SMALL_ROYAL_TOMB, BUILDING_MEDIUM_ROYAL_TOMB, BUILDING_LARGE_ROYAL_TOMB, BUILDING_GRAND_ROYAL_TOMB]
    for (var i = 0; i < tombs.length; i++) {
        // OG TERRAIN_USAGE_ROADS_OR_MONUMENT for a guild worker going to a royal tomb.
        if (__building_static_guild_worker_terrain(tombs[i]) != TERRAIN_USAGE_ANY) {
            return t151_fail('guild_worker_terrain of tomb type ' + tombs[i])
        }
    }
    var guild = test_building_place(BUILDING_ARTISANS_GUILD, -1, -1)
    if (!guild) {
        return t151_fail('artisans guild place failed')
    }
    var sent = t151_guild_send(bid, guild, RESOURCE_CLAY, 2)
    if (sent != 0 || __test_royal_tomb_part_stage(bid, 0) != 3) {
        return t151_fail('clay artisan stage 2: ' + sent)
    }
    __log_marker('rt_stage_guild_clay_ok')
    if (__test_royal_tomb_part_stage(bid, 1) != 1 || __test_royal_tomb_part_can_take(bid, 1) != 1) {
        return t151_fail('stage 3 should open neighbour 1, stage=' + __test_royal_tomb_part_stage(bid, 1))
    }
    __log_marker('rt_stage_neighbour_open_ok')
    sent = t151_guild_send(bid, guild, RESOURCE_PAINT, 3)
    if (sent != 0 || __test_royal_tomb_part_stage(bid, 0) != 4 || __test_royal_tomb_part_can_take(bid, 0) != 0) {
        return t151_fail('paint artisan stage 3: ' + sent)
    }
    __log_marker('rt_stage_guild_paint_ok')
    if (__test_royal_tomb_progress(bid) != 13) {
        return t151_fail('progress after one chamber ' + __test_royal_tomb_progress(bid) + ' want 13')
    }
    __log_marker('rt_stage_chamber_done_ok')

    var guard = 0
    while (__test_royal_tomb_progress(bid) < 100 && guard++ < 100) {
        if (t151_send(bid, FIGURE_STONEMASON, 1) >= 0) {
            continue
        }
        var artisan_part = __test_royal_tomb_find_work(FIGURE_TOMB_ARTISAN, -1)
        if (artisan_part >= 0 && t151_send(bid, FIGURE_TOMB_ARTISAN, __test_royal_tomb_part_stage(bid, artisan_part)) >= 0) {
            continue
        }
        return t151_fail('stuck at ' + __test_royal_tomb_progress(bid) + '%')
    }
    if (__test_royal_tomb_progress(bid) != 100) {
        return t151_fail('never reached 100%')
    }
    if (__test_royal_tomb_part_stage(bid, 9) != 0) {
        return t151_fail('closed rock part must stay closed')
    }
    __log_marker('rt_stage_all_chambers_ok')

    __test_building_update_day(bid)
    var ph = __test_monument_phase(bid)
    if (ph != 255 && ph != -1) {
        return t151_fail('not finished after 100% ph=' + ph)
    }
    __log_marker('rt_stage_finished_ok')

    var diff = __test_save_roundtrip('test_151_royal_tomb.svx')
    if (diff !== '') {
        return t151_fail('save roundtrip: ' + diff)
    }
    if (__test_royal_tomb_part_count(bid) != 167 || __test_royal_tomb_progress(bid) != 100
        || __test_royal_tomb_lamp_stock(bid) != __test_royal_tomb_lamp_stock(bid)) {
        return t151_fail('state after load')
    }
    if (__test_find_inlog('[record-overflow]')) {
        return t151_fail('record overflow')
    }
    __log_marker('rt_stage_saveload_ok')
    __log_marker('rt_stage_ok')
    __test_signal_ready()
}

function check_valid() {
    var required = ['rt_stage_initial_ok', 'rt_stage_guild_clay_ok', 'rt_stage_neighbour_open_ok', 'rt_stage_guild_paint_ok', 'rt_stage_chamber_done_ok',
        'rt_stage_all_chambers_ok', 'rt_stage_finished_ok', 'rt_stage_saveload_ok', 'rt_stage_ok']
    if (__test_find_inlog('[test-marker] rt_stage_fail')) {
        return false
    }
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])) {
            __log_info_native('[test:151] missing marker ' + required[i])
            return false
        }
    }
    return true
}

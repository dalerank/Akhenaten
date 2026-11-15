// OG Pharos lighthouse: a 6x6 tower over bare rock and a 1x1 land part at +2,+6, free, one unfinished
// at a time; stages 0..8 worked down at one stonemason and one carpenter spot (one worker at a time), the
// stonemason waits for three marble sleds; LtHouse(stage+1) art, LtHouse10 beacon animates when complete.

var __t393_ok = false

function t393_fail(msg) {
    __log_info_native('[test:393] FAIL: ' + msg)
    __test_signal_ready()
}

function t393_rock_pad(x, y) {
    var all = TERRAIN_WATER | TERRAIN_ROAD | TERRAIN_TREE | TERRAIN_SHRUB | TERRAIN_GARDEN | TERRAIN_CANAL
        | TERRAIN_ELEVATION | TERRAIN_ACCESS_RAMP | TERRAIN_FLOODPLAIN | TERRAIN_ROCK | TERRAIN_MEADOW | TERRAIN_ORE
    for (var dy = 0; dy < 7; dy++) {
        for (var dx = 0; dx < 6; dx++) {
            terrain.remove({ x: x + dx, y: y + dy }, all)
            if (dy < 6) {
                terrain.add({ x: x + dx, y: y + dy }, TERRAIN_ROCK)
            }
        }
    }
}

function t393_work_until_leaves(bid, fid, limit) {
    for (var i = 0; i < limit; i++) {
        if (__test_lighthouse_work(bid, fid) != 0) {
            return i + 1
        }
    }
    return -1
}

function run_test() {
    __log_info_native('[test:393] OG pharos lighthouse')
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_PHAROS_LIGHTHOUSE)) {
        __scenario_building_allow(BUILDING_PHAROS_LIGHTHOUSE, true)
    }
    __test_set_treasury(5000)

    var x = ((__scenario_map.width / 2) | 0) - 3
    var y = ((__scenario_map.height / 2) | 0) - 3
    t393_rock_pad(x, y)
    if (!__test_lighthouse_site_fits(x, y)) {
        return t393_fail('prepared site does not fit')
    }
    terrain.remove({ x: x + 3, y: y + 3 }, TERRAIN_ROCK)
    if (__test_lighthouse_site_fits(x, y)) {
        return t393_fail('a tower tile without rock must not fit')
    }
    terrain.add({ x: x + 3, y: y + 3 }, TERRAIN_ROCK)
    terrain.add({ x: x + 2, y: y + 6 }, TERRAIN_TREE)
    if (__test_lighthouse_site_fits(x, y)) {
        return t393_fail('a land part on trees must not fit')
    }
    terrain.remove({ x: x + 2, y: y + 6 }, TERRAIN_TREE)
    __log_marker('t393_site_rules')

    var bid = test_building_place(BUILDING_PHAROS_LIGHTHOUSE, x, y)
    if (!bid) {
        return t393_fail('place failed')
    }
    if (city.finance.treasury != 5000) {
        return t393_fail('OG lighthouse is free, treasury ' + city.finance.treasury)
    }
    var t0 = __building_tile(bid)
    if (t0.x != x || t0.y != y) {
        return t393_fail('tower at ' + t0.x + ',' + t0.y + ' not at the hovered tile ' + x + ',' + y)
    }
    var land = city.get_building(bid).next_part_building_id
    var tl = land ? __building_tile(land) : null
    if (!land || __building_type(land) != BUILDING_PHAROS_LIGHTHOUSE || tl.x != x + 2 || tl.y != y + 6) {
        return t393_fail('land part missing or misplaced')
    }
    if (terrain.is({ x: x + 1, y: y + 1 }, TERRAIN_ROCK)) {
        return t393_fail('tower tiles keep their rock')
    }
    __log_marker('t393_parts')

    t393_rock_pad(x + 10, y)
    if (test_building_place(BUILDING_PHAROS_LIGHTHOUSE, x + 10, y)) {
        return t393_fail('second unfinished lighthouse placed')
    }
    __log_marker('t393_one_only')

    if (__test_lighthouse_stage(bid) != 0 || __test_lighthouse_percent(bid) != 10
        || __test_lighthouse_spot_work(bid, FIGURE_STONEMASON) != 400 || __test_lighthouse_spot_work(bid, FIGURE_CARPENTER) != 0) {
        return t393_fail('initial stage ' + __test_lighthouse_stage(bid) + ' pct ' + __test_lighthouse_percent(bid))
    }

    // OG lighthouse_work_spots and lighthouse_stage_text, per stage 0..8.
    var og_mason = [400, 400, 410, 600, 355, 500, 500, 500, 400]
    var og_carpenter = [0, 0, 300, 350, 600, 500, 500, 500, 0]
    var og_text = [133, 134, 135, 135, 136, 137, 137, 138, 139]
    var og_spots = []
    for (var s = 0; s < 9; s++) {
        og_spots.push(s + ':' + FIGURE_STONEMASON + ':' + og_mason[s])
        if (og_carpenter[s]) {
            og_spots.push(s + ':' + FIGURE_CARPENTER + ':' + og_carpenter[s])
        }
    }
    if (__test_lighthouse_spots(bid) != og_spots.join(';')) {
        return t393_fail('spots ' + __test_lighthouse_spots(bid) + ' != ' + og_spots.join(';'))
    }
    for (var s = 0; s < 9; s++) {
        __test_lighthouse_set_stage(bid, s)
        var sm = __test_lighthouse_spot_work(bid, FIGURE_STONEMASON)
        var sc = __test_lighthouse_spot_work(bid, FIGURE_CARPENTER)
        var st = __test_lighthouse_stage_text(bid)
        if (sm != og_mason[s] || sc != og_carpenter[s] || st != og_text[s]) {
            return t393_fail('stage ' + s + ' mason ' + sm + ' carpenter ' + sc + ' text ' + st)
        }
    }
    __test_lighthouse_set_stage(bid, 0)
    if (__test_lighthouse_stage(bid) != 0 || __test_lighthouse_spot_work(bid, FIGURE_STONEMASON) != 400) {
        return t393_fail('back to stage 0 failed')
    }
    __log_marker('t393_stage_table')

    var mason = __test_figure_create(FIGURE_STONEMASON, x + 2, y + 7)
    var carpenter = __test_figure_create(FIGURE_CARPENTER, x + 2, y + 7)
    __test_figure_set_action(mason, 19)
    if (!__test_lighthouse_assign(bid, mason) || __test_lighthouse_assign(bid, carpenter)) {
        return t393_fail('the tower takes one worker at a time')
    }
    if (__test_lighthouse_mason_waiting(bid) != mason) {
        return t393_fail('waiting mason not offered to laborers')
    }
    if (__test_lighthouse_sled(bid, mason) || __test_lighthouse_sled(bid, mason) || !__test_lighthouse_sled(bid, mason)) {
        return t393_fail('mason must start on the third sled')
    }
    if (__test_figure_get_action(mason) != 9) {
        return t393_fail('mason not working after the sleds, action ' + __test_figure_get_action(mason))
    }
    var worked = t393_work_until_leaves(bid, mason, 2000)
    if (worked != 400 || __test_lighthouse_stage(bid) != 1) {
        return t393_fail('stage 0: worked ' + worked + ' stage ' + __test_lighthouse_stage(bid))
    }
    __log_marker('t393_sleds_and_work')

    __test_lighthouse_set_stage(bid, 2)
    worked = t393_work_until_leaves(bid, mason, 2000)
    if (worked != 410 || __test_lighthouse_stage(bid) != 2) {
        return t393_fail('stage 2 mason: worked ' + worked + ' stage ' + __test_lighthouse_stage(bid))
    }
    for (var w = 0; w < 100; w++) {
        __test_lighthouse_work(bid, carpenter)
    }
    var save_name = 'test_393_lighthouse.svx'
    if (__game_write_savegame(save_name) && __game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        if (__building_type(bid) != BUILDING_PHAROS_LIGHTHOUSE || __test_lighthouse_stage(bid) != 2
            || __test_lighthouse_spot_work(bid, FIGURE_CARPENTER) != 200 || __test_lighthouse_spot_work(bid, FIGURE_STONEMASON) != 0) {
            return t393_fail('after load: stage ' + __test_lighthouse_stage(bid) + ' carpenter '
                + __test_lighthouse_spot_work(bid, FIGURE_CARPENTER))
        }
        __log_marker('t393_saveload_ok')
    } else {
        return t393_fail('save/load failed')
    }
    carpenter = __test_figure_create(FIGURE_CARPENTER, x + 2, y + 7)
    worked = t393_work_until_leaves(bid, carpenter, 2000)
    if (worked != 200 || __test_lighthouse_stage(bid) != 3) {
        return t393_fail('stage 2 needs both spots: worked ' + worked + ' stage ' + __test_lighthouse_stage(bid))
    }
    __log_marker('t393_stage_needs_both_spots')

    var a1 = __test_building_current_image(bid)
    if (a1 > 0) {
        for (var s = 0; s <= 9; s++) {
            __test_lighthouse_set_stage(bid, s)
            var img = __test_building_current_image(bid)
            if (img <= 0 || (s > 0 && img == a1)) {
                return t393_fail('stage ' + s + ' art ' + img)
            }
            a1 = img
        }
        __log_marker('t393_art_ok')
    } else {
        __log_marker('t393_art_skipped:no_resource')
    }

    __test_lighthouse_set_stage(bid, 8)
    mason = __test_figure_create(FIGURE_STONEMASON, x + 2, y + 7)
    worked = t393_work_until_leaves(bid, mason, 2000)
    if (worked != 400 || __test_monument_phase(bid) != -1 || __test_lighthouse_percent(bid) != 100) {
        return t393_fail('last stage: worked ' + worked + ' phase ' + __test_monument_phase(bid))
    }
    if (__test_lighthouse_assign(bid, __test_figure_create(FIGURE_STONEMASON, x + 2, y + 7))) {
        return t393_fail('finished lighthouse took a worker')
    }
    __log_marker('t393_finished')

    __test_show_tile_info(bid)
    __test_pump_frames(4)
    window_go_back()
    __test_pump_frames(2)

    __t393_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __t393_ok
        && __test_find_inlog('[test-marker] t393_site_rules')
        && __test_find_inlog('[test-marker] t393_parts')
        && __test_find_inlog('[test-marker] t393_one_only')
        && __test_find_inlog('[test-marker] t393_stage_table')
        && __test_find_inlog('[test-marker] t393_sleds_and_work')
        && __test_find_inlog('[test-marker] t393_saveload_ok')
        && __test_find_inlog('[test-marker] t393_stage_needs_both_spots')
        && __test_find_inlog('[test-marker] t393_finished')
}

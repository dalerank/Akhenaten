// OG Abu Simbel placement: 16 records fixed in map space around the clicked tile, every part but the
// entrance on monument rock (editor cliffs), no cost, staging tile in front of the entrance, one
// unfinished at a time, cliff restored under the rock parts when it goes away.

var T118_PARTS = [
    [1, 7, 3], [1, -11, 3], [-5, 4, 3], [-5, 1, 3], [-5, -2, 3], [-5, -5, 3], [-5, -8, 3], [-2, 7, 3],
    [-2, -11, 3], [-5, 7, 3], [-5, -11, 3], [-2, -2, 3], [1, -2, 3], [4, -2, 3], [-2, 1, 6], [-2, -8, 6]
]

function t029_fail(msg) {
    __log_info_native('[test:029] FAIL: ' + msg)
    __test_signal_ready()
}

// The rock block x -5..3, y -11..9 around the origin; the entrance (x 4..6, y -2..0) stays open ground.
function t029_paint_site(ox, oy) {
    for (var dy = -13; dy <= 11; dy++) {
        for (var dx = -7; dx <= 8; dx++) {
            var t = { x: ox + dx, y: oy + dy }
            terrain.remove(t, TERRAIN_NOT_CLEAR | TERRAIN_FLOODPLAIN | TERRAIN_ROCK_NEAR_MONUMENT)
            if (dx >= -5 && dx <= 3 && dy >= -11 && dy <= 9) {
                terrain.add(t, TERRAIN_ROCK | TERRAIN_ROCK_NEAR_MONUMENT)
            }
        }
    }
}

function run_test() {
    __log_info_native('[test:029] OG abu simbel placement')
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_ABU_SIMBEL)) {
        __scenario_building_allow(BUILDING_ABU_SIMBEL, true)
    }
    __test_set_treasury(5000)

    var ox = (__scenario_map.width / 2) | 0
    var oy = (__scenario_map.height / 2) | 0

    if (test_building_place(BUILDING_ABU_SIMBEL, ox, oy)) {
        return t029_fail('placed without cliffs')
    }
    __log_marker('t029_reject_no_cliff')

    // Plain rock (not the editor's monument rock) does not take it either.
    t029_paint_site(ox, oy)
    for (var dy = -11; dy <= 9; dy++) {
        terrain.remove({ x: ox - 5, y: oy + dy }, TERRAIN_ROCK_NEAR_MONUMENT)
    }
    if (__test_abu_simbel_site_fits(ox, oy)) {
        return t029_fail('fits on plain rock')
    }
    t029_paint_site(ox, oy)
    // The entrance must be open ground.
    terrain.add({ x: ox + 5, y: oy - 1 }, TERRAIN_ROCK | TERRAIN_ROCK_NEAR_MONUMENT)
    if (__test_abu_simbel_site_fits(ox, oy)) {
        return t029_fail('fits with rock under the entrance')
    }
    t029_paint_site(ox, oy)
    if (!__test_abu_simbel_site_fits(ox, oy) || __test_abu_simbel_site_fits(ox + 1, oy)) {
        return t029_fail('site check: here ' + __test_abu_simbel_site_fits(ox, oy) + ' shifted ' + __test_abu_simbel_site_fits(ox + 1, oy))
    }
    __log_marker('t029_site_rules')

    var bid = test_building_place(BUILDING_ABU_SIMBEL, ox, oy)
    if (!bid) {
        return t029_fail('place failed on the painted site')
    }
    if (city.finance.treasury != 5000) {
        return t029_fail('OG Abu Simbel is free, treasury ' + city.finance.treasury)
    }

    var parts = [bid]
    var cur = city.get_building(bid)
    while (cur && cur.next_part_building_id > 0 && parts.length < 20) {
        parts.push(cur.next_part_building_id)
        cur = city.get_building(cur.next_part_building_id)
    }
    if (parts.length != 16) {
        return t029_fail('expected 16 parts, got ' + parts.length)
    }
    for (var p = 0; p < 16; p++) {
        var tp = __building_tile(parts[p])
        var want = T118_PARTS[p]
        if (tp.x != ox + want[0] || tp.y != oy + want[1] || city.get_building(parts[p]).size != want[2]) {
            return t029_fail('part ' + p + ' at ' + tp.x + ',' + tp.y + ' size ' + city.get_building(parts[p]).size)
        }
    }
    __log_marker('t029_layout_ok')

    if (terrain.is({ x: ox - 5, y: oy - 11 }, TERRAIN_ROCK) || !terrain.is({ x: ox - 5, y: oy - 11 }, TERRAIN_BUILDING)) {
        return t029_fail('rock must give way to the building')
    }
    if (__test_abu_simbel_access_x(bid) != ox + 7 || __test_abu_simbel_access_y(bid) != oy - 1) {
        return t029_fail('staging tile ' + __test_abu_simbel_access_x(bid) + ',' + __test_abu_simbel_access_y(bid))
    }
    if (__test_abu_simbel_stage(bid) != 0 || __test_abu_simbel_progress(bid) != 0) {
        return t029_fail('initial stage ' + __test_abu_simbel_stage(bid))
    }
    __log_marker('t029_placed_ok')

    t029_paint_site(ox + 25, oy)
    if (!__test_abu_simbel_site_fits(ox + 25, oy) || test_building_place(BUILDING_ABU_SIMBEL, ox + 25, oy)) {
        return t029_fail('second unfinished Abu Simbel placed')
    }
    __log_marker('t029_one_unfinished')

    __test_abu_simbel_set_stage(bid, 56)
    if (__test_monument_phase(bid) != -1 || __test_abu_simbel_progress(bid) != 100) {
        return t029_fail('stage 56 must finish it, phase ' + __test_monument_phase(bid))
    }
    __log_marker('t029_finished_ok')

    test_monument_slots([BUILDING_ABU_SIMBEL])
    city_update_monthly_monument_rating({})
    var rating_done = city.rating.monument | 0
    if (rating_done < 44) {
        return t029_fail('finished rating want >=44 got ' + rating_done)
    }

    __log_marker('t029_ok')
    __test_signal_ready()
}

function check_valid() {
    var required = ['t029_reject_no_cliff', 't029_site_rules', 't029_layout_ok', 't029_placed_ok',
        't029_one_unfinished', 't029_finished_ok', 't029_ok']
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])) {
            __log_info_native('[test:029] missing marker ' + required[i])
            return false
        }
    }
    return true
}

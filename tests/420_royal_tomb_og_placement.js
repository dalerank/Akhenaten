// OG royal tomb placement (royal_tomb_can_place, construction_ghost_royal_tomb): a fixed part
// layout around the clicked tile; every part but the entrance on Valley cliff (rock + rock near
// monument), the entrance on clear land with one clear neighbour; free to build (OG cost 0).

function t420_fail(msg) {
    __log_info_native('[test:420] ' + msg)
    __log_marker('rt_place_fail')
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:420] royal tomb OG placement')
    test_reload_city_session('data/default.map')
    var types = [BUILDING_SMALL_ROYAL_TOMB, BUILDING_MEDIUM_ROYAL_TOMB, BUILDING_LARGE_ROYAL_TOMB, BUILDING_GRAND_ROYAL_TOMB]
    for (var i = 0; i < types.length; i++) {
        if (!__scenario_building_allowed(types[i])) {
            __scenario_building_allow(types[i], true)
        }
    }

    if (__test_royal_tomb_can_place(BUILDING_SMALL_ROYAL_TOMB, 40, 40)) {
        return t420_fail('small tomb fits on clear land')
    }
    // Elevation is not the Valley cliff.
    for (var dy = -12; dy <= 12; dy++) {
        for (var dx = -8; dx <= 8; dx++) {
            terrain.add({ x: 40 + dx, y: 40 + dy }, TERRAIN_ELEVATION)
        }
    }
    if (__test_royal_tomb_can_place(BUILDING_SMALL_ROYAL_TOMB, 40, 40)) {
        return t420_fail('small tomb fits on elevation')
    }
    __log_marker('rt_place_reject_ok')

    __test_royal_tomb_paint_site(BUILDING_SMALL_ROYAL_TOMB, 40, 40)
    if (!__test_royal_tomb_can_place(BUILDING_SMALL_ROYAL_TOMB, 40, 40)) {
        return t420_fail('small tomb rejected on its painted site')
    }
    var treasury = city.finance.treasury
    var bid = test_building_place(BUILDING_SMALL_ROYAL_TOMB, 40, 40)
    if (!bid) {
        return t420_fail('small tomb place failed')
    }
    if (city.finance.treasury != treasury) {
        return t420_fail('tomb cost ' + (treasury - city.finance.treasury) + ', OG cost is 0')
    }
    // OG small tomb: part 0 at (+3,-7), entrance (part 166) at (+5,-6).
    if (__test_royal_tomb_part_tile_x(bid, 0) != 43 || __test_royal_tomb_part_tile_y(bid, 0) != 33
        || __test_royal_tomb_part_tile_x(bid, 166) != 45 || __test_royal_tomb_part_tile_y(bid, 166) != 34) {
        return t420_fail('layout part0=' + __test_royal_tomb_part_tile_x(bid, 0) + ',' + __test_royal_tomb_part_tile_y(bid, 0)
            + ' entrance=' + __test_royal_tomb_part_tile_x(bid, 166) + ',' + __test_royal_tomb_part_tile_y(bid, 166))
    }
    __log_marker('rt_place_layout_ok')

    __test_royal_tomb_paint_site(BUILDING_SMALL_ROYAL_TOMB, 80, 40)
    if (test_building_place(BUILDING_SMALL_ROYAL_TOMB, 80, 40)) {
        return t420_fail('second unfinished small tomb placed')
    }
    __log_marker('rt_place_one_at_a_time_ok')

    // Medium entrance (part 10 at +7,+3) walled in by cliff on all four sides.
    __test_royal_tomb_paint_site(BUILDING_MEDIUM_ROYAL_TOMB, 80, 40)
    if (!__test_royal_tomb_can_place(BUILDING_MEDIUM_ROYAL_TOMB, 80, 40)) {
        return t420_fail('medium tomb rejected on its painted site')
    }
    var ex = 87
    var ey = 43
    var around = [[0, -1], [0, 1], [-1, 0], [1, 0]]
    for (var k = 0; k < around.length; k++) {
        terrain.add({ x: ex + around[k][0], y: ey + around[k][1] }, TERRAIN_ROCK)
    }
    if (__test_royal_tomb_can_place(BUILDING_MEDIUM_ROYAL_TOMB, 80, 40)) {
        return t420_fail('medium tomb placed with a walled-in entrance')
    }
    __log_marker('rt_place_entrance_ok')

    var counts = [167, 158, 437, 513]
    var gx = Math.min(140, __scenario_map.width - 20)
    __test_royal_tomb_paint_site(BUILDING_GRAND_ROYAL_TOMB, gx, 60)
    var gbid = test_building_place(BUILDING_GRAND_ROYAL_TOMB, gx, 60)
    if (!gbid || __test_royal_tomb_part_count(gbid) != counts[3] || __test_royal_tomb_chambers(gbid) != 31) {
        return t420_fail('grand tomb parts=' + (gbid ? __test_royal_tomb_part_count(gbid) : 0))
    }
    __log_marker('rt_place_grand_ok')
    __log_marker('rt_place_ok')
    __test_signal_ready()
}

function check_valid() {
    var required = ['rt_place_reject_ok', 'rt_place_layout_ok', 'rt_place_one_at_a_time_ok', 'rt_place_entrance_ok',
        'rt_place_grand_ok', 'rt_place_ok']
    if (__test_find_inlog('[test-marker] rt_place_fail')) {
        return false
    }
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])) {
            __log_info_native('[test:420] missing marker ' + required[i])
            return false
        }
    }
    return true
}

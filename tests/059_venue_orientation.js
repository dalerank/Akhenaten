// EV1–EV3: venue map vs view orientation — place latch stable across camera;
// ghost view-ori helper; festival 5×5 + unique.
// Markers:
//   [test-marker] venue_orient_booth_ok
//   [test-marker] venue_orient_booth_alt_ok
//   [test-marker] venue_orient_bandstand_ok
//   [test-marker] venue_orient_bandstand_alt_ok
//   [test-marker] venue_orient_pavilion_ok
//   [test-marker] venue_orient_pavilion_odd_ok
//   [test-marker] venue_orient_festival_ok
//   [test-marker] venue_orient_view_stable_ok
//   [test-marker] venue_orient_ok

var CAMS = [0, 2, 4, 6]

function set_camera(cam) {
    __camera_rotate_north()
    // rotate_right from north: 0→2→4→6
    var steps = (cam / 2) | 0
    for (var i = 0; i < steps; i++) {
        __camera_rotate_right()
    }
    if (__camera.orientation != cam) {
        __log_info_native('[test:059] camera want ' + cam + ' got ' + __camera.orientation)
        return false
    }
    return true
}

function cursor_for_origin(ox, oy, size, cam) {
    switch (cam) {
    case 2: return { x: ox + size - 1, y: oy }
    case 4: return { x: ox + size - 1, y: oy + size - 1 }
    case 6: return { x: ox, y: oy + size - 1 }
    default: return { x: ox, y: oy }
    }
}

function paint_roads(ox, oy, pattern) {
    for (var dy = 0; dy < pattern.length; dy++) {
        for (var dx = 0; dx < pattern[dy].length; dx++) {
            if (pattern[dy][dx]) {
                terrain.add({ x: ox + dx, y: oy + dy }, TERRAIN_ROAD)
            }
        }
    }
}

function assert_tile(bid, ox, oy, label) {
    var t = __building_tile(bid)
    if (!t || t.x != ox || t.y != oy) {
        __log_info_native('[test:059] ' + label + ' tile want ' + ox + ',' + oy
            + ' got ' + (t ? (t.x + ',' + t.y) : 'null'))
        return false
    }
    return true
}

function assert_latch(bid, ox, oy, main_dx, main_dy, add_dx, add_dy, label) {
    var b = city.get_entertainment_building(bid)
    if (!b) {
        __log_info_native('[test:059] ' + label + ' get_entertainment_building failed')
        return false
    }
    var main_t = __map_tile_at_grid_offset(b.latched_venue_main_grid_offset)
    var add_t = __map_tile_at_grid_offset(b.latched_venue_add_grid_offset)
    if (!main_t || main_t.x != ox + main_dx || main_t.y != oy + main_dy) {
        __log_info_native('[test:059] ' + label + ' main latch want '
            + (ox + main_dx) + ',' + (oy + main_dy)
            + ' got ' + (main_t ? (main_t.x + ',' + main_t.y) : 'null'))
        return false
    }
    if (!add_t || add_t.x != ox + add_dx || add_t.y != oy + add_dy) {
        __log_info_native('[test:059] ' + label + ' add latch want '
            + (ox + add_dx) + ',' + (oy + add_dy)
            + ' got ' + (add_t ? (add_t.x + ',' + add_t.y) : 'null'))
        return false
    }
    return true
}

// One session: four cam slots spaced apart (no reload per cam).
function run_booth_cams(cx, cy) {
    var pattern = [[0, 1], [1, 1]]
    for (var ci = 0; ci < CAMS.length; ci++) {
        var cam = CAMS[ci]
        if (!set_camera(cam)) {
            return false
        }
        var ox = cx + ci * 8
        var oy = cy
        paint_roads(ox, oy, pattern)
        terrain.add({ x: ox + 1, y: oy + 2 }, TERRAIN_ROAD)
        terrain.add({ x: ox + 2, y: oy + 1 }, TERRAIN_ROAD)

        var cur = cursor_for_origin(ox, oy, 2, cam)
        if (__map_venue_build_orientation(cur, e_venue_mode_booth) < 0) {
            __log_info_native('[test:059] booth ghost fail cam=' + cam)
            return false
        }

        var bid = test_building_place(BUILDING_BOOTH, cur.x, cur.y)
        if (!bid || bid <= 0) {
            __log_info_native('[test:059] booth place fail cam=' + cam)
            return false
        }
        if (!assert_tile(bid, ox, oy, 'booth cam=' + cam)) {
            return false
        }
    }
    return true
}

// Non-zero road patterns (cam=0): ghost view_ori/2 must match pattern half
// (hermetic --no-resource: image ids are 0, so no latch-sprite asserts).
function run_booth_alt_patterns(cx, cy) {
    if (!set_camera(0)) {
        return false
    }
    var cases = [
        { pattern: [[1, 0], [1, 1]], half: 1, extra: [[-1, 1], [0, 2]] },
        { pattern: [[1, 1], [1, 0]], half: 2, extra: [[0, -1], [-1, 0]] },
        { pattern: [[1, 1], [0, 1]], half: 3, extra: [[1, -1], [2, 0]] }
    ]
    for (var i = 0; i < cases.length; i++) {
        var c = cases[i]
        var ox = cx + i * 8
        var oy = cy
        paint_roads(ox, oy, c.pattern)
        for (var e = 0; e < c.extra.length; e++) {
            terrain.add({ x: ox + c.extra[e][0], y: oy + c.extra[e][1] }, TERRAIN_ROAD)
        }
        var view_ori = __map_venue_build_orientation({ x: ox, y: oy }, e_venue_mode_booth)
        if (view_ori < 0) {
            __log_info_native('[test:059] booth alt ghost fail i=' + i)
            return false
        }
        if (((view_ori / 2) | 0) != c.half) {
            __log_info_native('[test:059] booth alt ori i=' + i
                + ' want half=' + c.half + ' got view_ori=' + view_ori)
            return false
        }
        // Even map indices only (booth matcher skips odds) — view_ori at cam=0 == map.
        if (view_ori & 1) {
            __log_info_native('[test:059] booth alt odd map ori i=' + i + ' got ' + view_ori)
            return false
        }
        var bid = test_building_place(BUILDING_BOOTH, ox, oy)
        if (!bid || bid <= 0) {
            __log_info_native('[test:059] booth alt place fail i=' + i)
            return false
        }
        if (!assert_tile(bid, ox, oy, 'booth alt i=' + i)) {
            return false
        }
    }
    return true
}

function run_bandstand_cams(cx, cy) {
    var pattern = [[0, 1, 0], [0, 1, 0], [1, 1, 1]]
    for (var ci = 0; ci < CAMS.length; ci++) {
        var cam = CAMS[ci]
        if (!set_camera(cam)) {
            return false
        }
        var ox = cx + ci * 10
        var oy = cy
        paint_roads(ox, oy, pattern)

        var cur = cursor_for_origin(ox, oy, 3, cam)
        if (__map_venue_build_orientation(cur, e_venue_mode_bandstand) < 0) {
            __log_info_native('[test:059] bandstand ghost fail cam=' + cam)
            return false
        }

        var bid = test_building_place(BUILDING_BANDSTAND, cur.x, cur.y)
        if (!bid || bid <= 0) {
            __log_info_native('[test:059] bandstand place fail cam=' + cam)
            return false
        }
        if (!assert_tile(bid, ox, oy, 'bandstand cam=' + cam)) {
            return false
        }
    }
    return true
}

function run_bandstand_alt_pattern(cx, cy) {
    if (!set_camera(0)) {
        return false
    }
    // ROAD_POSITIONS[1] → half 1; latch main at (1,0), add at (2,0)
    var pattern = [[1, 0, 0], [1, 1, 1], [1, 0, 0]]
    paint_roads(cx, cy, pattern)
    var view_ori = __map_venue_build_orientation({ x: cx, y: cy }, e_venue_mode_bandstand)
    if (view_ori < 0 || ((view_ori / 2) | 0) != 1) {
        __log_info_native('[test:059] bandstand alt ori want half=1 got ' + view_ori)
        return false
    }
    var bid = test_building_place(BUILDING_BANDSTAND, cx, cy)
    if (!bid || bid <= 0) {
        __log_info_native('[test:059] bandstand alt place fail')
        return false
    }
    if (!assert_tile(bid, cx, cy, 'bandstand alt')) {
        return false
    }
    // Hermetic latch check via runtime offsets (images are 0 under --no-resource).
    return assert_latch(bid, cx, cy, 1, 0, 2, 0, 'bandstand alt')
}

function run_pavilion_cams(cx, cy) {
    var pattern = [
        [0, 0, 1, 0],
        [0, 0, 1, 0],
        [0, 0, 1, 0],
        [1, 1, 1, 1]
    ]
    var last_bid = 0
    for (var ci = 0; ci < CAMS.length; ci++) {
        var cam = CAMS[ci]
        if (!set_camera(cam)) {
            return false
        }
        var ox = cx + ci * 12
        var oy = cy
        paint_roads(ox, oy, pattern)

        var cur = cursor_for_origin(ox, oy, 4, cam)
        if (__map_venue_build_orientation(cur, e_venue_mode_pavilion) < 0) {
            __log_info_native('[test:059] pavilion ghost fail cam=' + cam)
            return false
        }

        var bid = test_building_place(BUILDING_PAVILLION, cur.x, cur.y)
        if (!bid || bid <= 0) {
            __log_info_native('[test:059] pavilion place fail cam=' + cam)
            return false
        }
        if (!assert_tile(bid, ox, oy, 'pavilion cam=' + cam)) {
            return false
        }
        last_bid = bid
    }

    // After final place, rotate through cams: latched stand tiles must stay put
    // (update_map_orientation refreshes camera-relative stand sprites).
    var b = city.get_entertainment_building(last_bid)
    if (!b) {
        __log_info_native('[test:059] pavilion rotate get_entertainment_building failed')
        return false
    }
    var main0 = b.latched_venue_main_grid_offset
    var add0 = b.latched_venue_add_grid_offset
    if (!main0 || !add0) {
        __log_info_native('[test:059] pavilion latch offsets missing after place')
        return false
    }
    for (var ri = 0; ri < CAMS.length; ri++) {
        if (!set_camera(CAMS[ri])) {
            return false
        }
        b = city.get_entertainment_building(last_bid)
        if (!b || b.latched_venue_main_grid_offset != main0
            || b.latched_venue_add_grid_offset != add0) {
            __log_info_native('[test:059] pavilion latch moved after cam=' + CAMS[ri])
            return false
        }
    }
    return true
}

// Odd pavilion map_ori=1: ROAD_POSITIONS[0] mirrored on x (3-x).
// place_dir_1: main (0,0), add (0,1).
function run_pavilion_odd(cx, cy) {
    if (!set_camera(0)) {
        return false
    }
    var pattern = [
        [0, 1, 0, 0],
        [0, 1, 0, 0],
        [0, 1, 0, 0],
        [1, 1, 1, 1]
    ]
    paint_roads(cx, cy, pattern)
    var view_ori = __map_venue_build_orientation({ x: cx, y: cy }, e_venue_mode_pavilion)
    if (view_ori != 1) {
        __log_info_native('[test:059] pavilion odd want view_ori=1 got ' + view_ori)
        return false
    }
    var bid = test_building_place(BUILDING_PAVILLION, cx, cy)
    if (!bid || bid <= 0) {
        __log_info_native('[test:059] pavilion odd place fail')
        return false
    }
    if (!assert_tile(bid, cx, cy, 'pavilion odd')) {
        return false
    }
    return assert_latch(bid, cx, cy, 0, 0, 0, 1, 'pavilion odd')
}

function run_festival(cx, cy) {
    var pattern = [
        [0, 0, 1, 0, 0],
        [0, 0, 1, 0, 0],
        [1, 1, 1, 1, 1],
        [0, 0, 1, 0, 0],
        [0, 0, 1, 0, 0]
    ]
    var size = city.get_building_params_by_type(BUILDING_FESTIVAL_SQUARE).building_size
    if (size != 5) {
        __log_info_native('[test:059] festival building_size want 5 got ' + size)
        return false
    }

    // cam≠0 place (first slot) — cursor→origin shift must land on painted mask.
    if (!set_camera(2)) {
        return false
    }
    var ox0 = cx
    var oy0 = cy
    paint_roads(ox0, oy0, pattern)
    var cur0 = cursor_for_origin(ox0, oy0, 5, 2)
    if (__map_venue_build_orientation(cur0, e_venue_mode_festival_square) < 0) {
        __log_info_native('[test:059] festival ghost fail cam=2')
        return false
    }
    var bid = test_building_place(BUILDING_FESTIVAL_SQUARE, cur0.x, cur0.y)
    if (!bid || bid <= 0) {
        __log_info_native('[test:059] festival place cam=2 failed')
        return false
    }
    if (!assert_tile(bid, ox0, oy0, 'festival cam=2')) {
        return false
    }

    if (!set_camera(0)) {
        return false
    }
    var ox2 = cx + 20
    var oy2 = cy
    paint_roads(ox2, oy2, pattern)
    var bid2 = test_building_place(BUILDING_FESTIVAL_SQUARE, ox2, oy2)
    if (bid2 && bid2 > 0) {
        __log_info_native('[test:059] second festival should be rejected, got id ' + bid2)
        return false
    }
    return true
}

// Same map footprint: view_ori = (map_ori + (8-cam)) % 8.
// At cam=0 view==map; at other cams cursor-shifted ghost must obey the formula.
function run_view_stable(cx, cy) {
    var pattern = [[0, 1, 0], [0, 1, 0], [1, 1, 1]]
    paint_roads(cx, cy, pattern)
    if (!set_camera(0)) {
        return false
    }
    var map_ori = __map_venue_build_orientation({ x: cx, y: cy }, e_venue_mode_bandstand)
    if (map_ori < 0) {
        __log_info_native('[test:059] view_stable map_ori fail')
        return false
    }
    for (var ci = 0; ci < CAMS.length; ci++) {
        var cam = CAMS[ci]
        if (!set_camera(cam)) {
            return false
        }
        var cur = cursor_for_origin(cx, cy, 3, cam)
        var view_ori = __map_venue_build_orientation(cur, e_venue_mode_bandstand)
        var want = (map_ori + (8 - cam)) % 8
        if (view_ori != want) {
            __log_info_native('[test:059] view_stable cam=' + cam
                + ' want ' + want + ' got ' + view_ori + ' (map_ori=' + map_ori + ')')
            return false
        }
    }
    return true
}

function run_test() {
    __log_info_native('[test:059] venue orientation (EV1–EV3)')
    test_reload_city_session('data/default.map')
    __test_set_treasury(1000000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    if (cx < 40 || cy < 40) {
        __log_info_native('[test:059] map too small: ' + cx + ',' + cy)
        __test_signal_ready()
        return
    }

    if (!run_booth_cams(cx - 36, cy - 30)) {
        __test_signal_ready()
        return
    }
    __log_marker('venue_orient_booth_ok')

    if (!run_booth_alt_patterns(cx - 36, cy - 22)) {
        __test_signal_ready()
        return
    }
    __log_marker('venue_orient_booth_alt_ok')

    if (!run_bandstand_cams(cx - 36, cy - 10)) {
        __test_signal_ready()
        return
    }
    __log_marker('venue_orient_bandstand_ok')

    if (!run_bandstand_alt_pattern(cx + 20, cy - 10)) {
        __test_signal_ready()
        return
    }
    __log_marker('venue_orient_bandstand_alt_ok')

    if (!run_pavilion_cams(cx - 36, cy + 10)) {
        __test_signal_ready()
        return
    }
    __log_marker('venue_orient_pavilion_ok')

    if (!run_pavilion_odd(cx + 20, cy + 10)) {
        __test_signal_ready()
        return
    }
    __log_marker('venue_orient_pavilion_odd_ok')

    if (!run_festival(cx - 10, cy + 30)) {
        __test_signal_ready()
        return
    }
    __log_marker('venue_orient_festival_ok')

    if (!run_view_stable(cx + 20, cy + 30)) {
        __test_signal_ready()
        return
    }
    __log_marker('venue_orient_view_stable_ok')

    __log_marker('venue_orient_ok')
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'venue_orient_booth_ok',
        'venue_orient_booth_alt_ok',
        'venue_orient_bandstand_ok',
        'venue_orient_bandstand_alt_ok',
        'venue_orient_pavilion_ok',
        'venue_orient_pavilion_odd_ok',
        'venue_orient_festival_ok',
        'venue_orient_view_stable_ok',
        'venue_orient_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:059] missing marker: ' + marker)
            return false
        }
    }
    return true
}

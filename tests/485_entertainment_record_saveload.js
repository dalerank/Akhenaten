// Entertainment venues keep their remake-only fields through save -> load: they now sit in bytes the OG
// entertainment record leaves free, inside the 186-byte record head (they used to run past it and were
// overwritten by the record tail). Also checks the base orientation, which bind_dynamic used to re-read
// from the overflow. Then zeroes the venue anchors (what older saves load) and checks on_post_load rebuilds them.
// Marker: [test-marker] entertainment_record_saveload_ok

var __t485_ok = false

var T485_FIELDS = {
    num_shows: 2,
    juggler_visited: 11,
    musician_visited: 12,
    dancer_visited: 13,
    play_index: 7,
    spawned_entertainer_days: 9,
    conservatory_help: 42,
    consume_material_id: 5
}

var T485_KEPT = ['booth_corner_grid_offset', 'latched_venue_main_grid_offset', 'latched_venue_add_grid_offset', 'orientation']

function t485_fail(msg) {
    __log_info_native('[test:485] FAIL ' + msg)
}

function t485_paint_roads(ox, oy, pattern) {
    for (var dy = 0; dy < pattern.length; dy++) {
        for (var dx = 0; dx < pattern[dy].length; dx++) {
            if (pattern[dy][dx]) {
                terrain.add({ x: ox + dx, y: oy + dy }, TERRAIN_ROAD)
            }
        }
    }
}

function t485_place(type, ox, oy, pattern, extra_roads) {
    t485_paint_roads(ox, oy, pattern)
    for (var i = 0; i < extra_roads.length; i++) {
        terrain.add({ x: ox + extra_roads[i][0], y: oy + extra_roads[i][1] }, TERRAIN_ROAD)
    }
    var bid = test_building_place(type, ox, oy)
    if (!bid || bid <= 0) {
        t485_fail('place type=' + type + ' at ' + ox + ',' + oy)
        return 0
    }
    return bid
}

function t485_snapshot(bid) {
    var b = city.get_entertainment_building(bid)
    var snap = {}
    for (var f in T485_FIELDS) {
        snap[f] = b[f]
    }
    for (var i = 0; i < T485_KEPT.length; i++) {
        snap[T485_KEPT[i]] = b[T485_KEPT[i]]
    }
    return snap
}

function run_test() {
    __log_info_native('[test:485] entertainment record save/load')
    if (!test_reload_city_session('data/default.map')) {
        t485_fail('map load')
        __test_signal_ready()
        return
    }
    __test_set_treasury(1000000)
    __camera_rotate_north()

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var venues = [
        { name: 'booth', bid: t485_place(BUILDING_BOOTH, cx - 30, cy - 20, [[0, 1], [1, 1]], [[1, 2], [2, 1]]) },
        { name: 'bandstand', bid: t485_place(BUILDING_BANDSTAND, cx - 20, cy - 20, [[1, 0, 0], [1, 1, 1], [1, 0, 0]], []) },
        { name: 'pavilion', bid: t485_place(BUILDING_PAVILLION, cx - 10, cy - 20, [[0, 0, 1, 0], [0, 0, 1, 0], [0, 0, 1, 0], [1, 1, 1, 1]], []) }
    ]

    // Let the fresh venues settle (figure slots, road access) so the chunk diff only sees the record layout.
    __test_run_ticks(200)
    __test_process_events()

    var before = []
    for (var i = 0; i < venues.length; i++) {
        var v = venues[i]
        if (!v.bid) {
            __test_signal_ready()
            return
        }
        for (var f in T485_FIELDS) {
            if (!__test_entertainment_set(v.bid, f, T485_FIELDS[f])) {
                t485_fail(v.name + ': cannot set ' + f)
                __test_signal_ready()
                return
            }
        }
        var snap = t485_snapshot(v.bid)
        if (!snap.booth_corner_grid_offset) {
            t485_fail(v.name + ': no booth corner after placement')
        }
        // The bandstand road pattern above gives orientation 1, so a dropped orientation shows up as 0.
        if (v.name == 'bandstand' && snap.orientation != 1) {
            t485_fail('bandstand: orientation ' + snap.orientation + ' after placement, want 1')
        }
        if (v.name != 'booth' && (!snap.latched_venue_main_grid_offset || !snap.latched_venue_add_grid_offset)) {
            t485_fail(v.name + ': no latched stand offsets after placement')
        }
        before.push(snap)
    }

    // city_data may differ: loading recounts the venue show stats from the show days written above.
    var diff = __test_save_roundtrip('test_485_entertainment.svx')
    var records_ok = diff.indexOf('error:') < 0 && diff.indexOf('buildings') < 0
    if (!records_ok) {
        t485_fail('roundtrip: ' + diff)
    }

    var bad = 0
    for (var j = 0; j < venues.length; j++) {
        var after = t485_snapshot(venues[j].bid)
        for (var k in before[j]) {
            if (after[k] != before[j][k]) {
                bad++
                t485_fail(venues[j].name + '.' + k + ' = ' + after[k] + ' after load, saved ' + before[j][k])
            }
        }
    }

    // Saves from before the fix load these as 0 (the bytes they now use were always skipped);
    // on_post_load must rebuild them from the tile and orientation.
    var anchors = ['booth_corner_grid_offset', 'latched_venue_main_grid_offset', 'latched_venue_add_grid_offset']
    for (var m = 0; m < venues.length; m++) {
        for (var a = 0; a < anchors.length; a++) {
            __test_entertainment_set(venues[m].bid, anchors[a], 0)
        }
    }
    __test_save_roundtrip('test_485_entertainment_zeroed.svx')
    for (var n = 0; n < venues.length; n++) {
        var rebuilt = t485_snapshot(venues[n].bid)
        for (var c = 0; c < anchors.length; c++) {
            // A booth has no stands, so it has no latched offsets to rebuild.
            if (venues[n].name == 'booth' && anchors[c] != 'booth_corner_grid_offset') {
                continue
            }
            var want = before[n][anchors[c]]
            if (rebuilt[anchors[c]] != want) {
                bad++
                t485_fail(venues[n].name + '.' + anchors[c] + ' = ' + rebuilt[anchors[c]] + ' after loading it as 0, want ' + want)
            }
        }
    }

    if (records_ok && bad == 0) {
        __log_marker('entertainment_record_saveload_ok')
        __t485_ok = true
    }

    test_reload_city_session('data/default.map')
    __test_signal_ready()
}

function check_valid() {
    return __t485_ok && __test_find_inlog('[test-marker] entertainment_record_saveload_ok')
}

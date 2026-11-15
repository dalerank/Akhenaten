// OG window_building_draw_abu_simbel texts: 178/149 when the site is cut off, the guild text for the
// free spot's figure (16 carpenters, 14 stonemasons guild missing), 178/142 once complete, and the
// percentage line 178/61 (empty at 100%).

function t393_fail(msg) {
    __log_info_native('[test:393] FAIL: ' + msg)
    window_go_back()
    __test_signal_ready()
}

function t393_paint_site(ox, oy) {
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

function t393_open(bid) {
    window_go_back()
    __test_pump_frames(2)
    __test_show_tile_info(bid)
    __test_pump_frames(5)
}

function t393_progress_line(pct) {
    return __loc(178, 61).split('[monument_name]').join(__loc(178, 82)).split('[percent_complete]').join(pct + '%')
}

function t393_expect(label, status_id, pct) {
    var status = __test_info_ui_text('warning_text')
    if (status != __loc(178, status_id)) {
        t393_fail(label + ': status "' + status + '" expected 178/' + status_id + ' "' + __loc(178, status_id) + '"')
        return false
    }
    var progress = __test_info_ui_text('progress_text')
    var expected = pct >= 100 ? '' : t393_progress_line(pct)
    if (progress != expected) {
        t393_fail(label + ': progress "' + progress + '" expected "' + expected + '"')
        return false
    }
    __log_marker('t393_' + label)
    return true
}

function run_test() {
    __log_info_native('[test:393] abu simbel info window')
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_ABU_SIMBEL)) {
        __scenario_building_allow(BUILDING_ABU_SIMBEL, true)
    }
    __test_destroy_buildings_of_type(BUILDING_CARPENTERS_GUILD)
    __test_destroy_buildings_of_type(BUILDING_STONEMASONS_GUILD)
    var ox = (__scenario_map.width / 2) | 0
    var oy = (__scenario_map.height / 2) | 0
    t393_paint_site(ox, oy)
    var bid = test_building_place(BUILDING_ABU_SIMBEL, ox, oy)
    if (!bid) {
        return t393_fail('place failed')
    }
    var main = city.get_building(bid)

    main.distance_from_entry = 0
    t393_open(bid)
    if (!t393_expect('blocked', 149, 0)) {
        return
    }

    main.distance_from_entry = 10
    t393_open(bid)
    if (!t393_expect('no_carpenters', 16, 0)) {
        return
    }

    __test_abu_simbel_set_stage(bid, 12)
    t393_open(bid)
    if (!t393_expect('no_stonemasons', 14, 21)) {
        return
    }

    __test_abu_simbel_set_stage(bid, 56)
    t393_open(bid)
    if (!t393_expect('complete', 142, 100)) {
        return
    }

    __log_marker('t393_ok')
    window_go_back()
    __test_pump_frames(2)
    __test_signal_ready()
}

function check_valid() {
    var required = ['t393_blocked', 't393_no_carpenters', 't393_no_stonemasons', 't393_complete', 't393_ok']
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])) {
            __log_info_native('[test:393] missing marker ' + required[i])
            return false
        }
    }
    return true
}

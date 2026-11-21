// Venue show animations tick: booth, pavilion and bandstand. The juggler config check runs everywhere,
// the animation check only with the Pharaoh data.
// Markers:
//   [test-marker] t567_config_ok
//   [test-marker] t567_ok
//   [test-marker] t567_skipped:no_resource
//   [test-marker] t567_fail:<what>

var __t567_failed = false

function t567_fail(what) {
    __log_info_native('[test-marker] t567_fail:' + what)
    __t567_failed = true
}

function t567_place(type, ox, oy, roads) {
    for (var i = 0; i < roads.length; i++) {
        terrain.add({ x: ox + roads[i][0], y: oy + roads[i][1] }, TERRAIN_ROAD)
    }
    var bid = test_building_place(type, ox, oy)
    if (!bid || bid <= 0) {
        t567_fail('place:' + type)
        return 0
    }
    return bid
}

function t567_start_shows(bid, workers) {
    __test_building_set_workers(bid, workers)
    var e = city.get_entertainment_building(bid)
    e.juggler_visited = 30
    e.musician_visited = 30
    e.dancer_visited = 30
    __test_building_update_day(bid)
}

function t567_expect_moving(name, before, after) {
    __log_info_native('[test:567] ' + name + ' frame ' + before + ' then ' + after)
    if (before <= 0) {
        t567_fail(name + ':no_anim')
    } else if (after == before) {
        t567_fail(name + ':frozen')
    }
}

function t567_sprite_frames(bid, type, keys) {
    var params = city.get_building_params_by_type(type)
    var frames = []
    for (var i = 0; i < keys.length; i++) {
        frames.push(__test_building_sprite_frame_of(bid, params.first_img(keys[i])))
    }
    return frames
}

function t567_slot_frames(bid, keys) {
    var frames = {}
    for (var slot = 0; slot < 4; slot++) {
        var key = __test_building_slot_anim_key(bid, slot)
        if (key) {
            frames[key] = __test_building_slot_anim_frame(bid, slot) + 1
        }
    }
    var out = []
    for (var i = 0; i < keys.length; i++) {
        out.push(frames[keys[i]] || 0)
    }
    return out
}

function t567_check_juggler_config() {
    var venues = [['booth', building_booth], ['pavilion', building_pavilion]]
    for (var i = 0; i < venues.length; i++) {
        var j = venues[i][1].animations.juggler
        if (j.max_frames != 26 || j.duration != 2) {
            t567_fail(venues[i][0] + '_juggler_config:' + j.max_frames + '/' + j.duration)
            return
        }
    }
    __log_info_native('[test-marker] t567_config_ok')
}

function t567_run() {
    t567_check_juggler_config()
    if (__t567_failed) {
        return
    }

    var juggler = building_booth.animations.juggler
    var img = get_image({ pack: juggler.pack, id: juggler.id })
    if (!img || img.height <= 0) {
        __log_info_native('[test-marker] t567_skipped:no_resource')
        return
    }

    if (!test_reload_city_session('data/default.map')) {
        return t567_fail('map_load')
    }
    __test_set_treasury(1000000)
    __camera_rotate_north()

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var booth = t567_place(BUILDING_BOOTH, cx - 30, cy - 20, [[1, 0], [0, 1], [1, 1], [1, 2], [2, 1]])
    var pavilion = t567_place(BUILDING_PAVILLION, cx - 10, cy - 20,
        [[2, 0], [2, 1], [2, 2], [0, 3], [1, 3], [2, 3], [3, 3]])
    var bandstand = t567_place(BUILDING_BANDSTAND, cx - 20, cy - 20, [[0, 0], [0, 1], [0, 2], [1, 1], [2, 1]])
    if (!booth || !pavilion || !bandstand) {
        return
    }

    t567_start_shows(booth, 8)
    t567_start_shows(pavilion, 20)
    t567_start_shows(bandstand, 12)

    var pavilion_keys = ['juggler', 'musician_sn', 'musician_we', 'dancer']
    var bandstand_keys = ['juggler', 'musician_sn']
    __test_run_ticks(2)
    __test_camera_center_building(bandstand)
    __test_draw_frames(1)
    var booth0 = t567_sprite_frames(booth, BUILDING_BOOTH, ['juggler'])
    var pavilion0 = t567_sprite_frames(pavilion, BUILDING_PAVILLION, pavilion_keys)
    var bandstand0 = t567_slot_frames(bandstand, bandstand_keys)
    __test_run_ticks(7)
    __test_draw_frames(1)
    var booth1 = t567_sprite_frames(booth, BUILDING_BOOTH, ['juggler'])
    var pavilion1 = t567_sprite_frames(pavilion, BUILDING_PAVILLION, pavilion_keys)
    var bandstand1 = t567_slot_frames(bandstand, bandstand_keys)

    t567_expect_moving('booth_juggler', booth0[0], booth1[0])
    for (var i = 0; i < pavilion_keys.length; i++) {
        t567_expect_moving('pavilion_' + pavilion_keys[i], pavilion0[i], pavilion1[i])
    }
    for (var j = 0; j < bandstand_keys.length; j++) {
        t567_expect_moving('bandstand_' + bandstand_keys[j], bandstand0[j], bandstand1[j])
    }

    if (!__t567_failed) {
        __log_info_native('[test-marker] t567_ok')
    }
}

function run_test() {
    t567_run()
    __test_signal_ready()
}

function check_valid() {
    return !__t567_failed
        && __test_find_inlog('[test-marker] t567_config_ok')
        && (__test_find_inlog('[test-marker] t567_ok') || __test_find_inlog('[test-marker] t567_skipped:no_resource'))
}

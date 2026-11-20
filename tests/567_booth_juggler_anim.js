// A staffed booth or pavilion with a juggler show must tick its juggler animation. Needs the Pharaoh data.
// Markers:
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
    return test_building_place(type, ox, oy)
}

function t567_check(name, type, bid, workers) {
    if (!bid || bid <= 0) {
        return t567_fail(name + ':place')
    }
    var juggler = city.get_building_params_by_type(type).first_img('juggler')
    // The map has no workforce: labor clears the staff before a day passes, so play_animation is set by hand.
    __test_building_set_workers(bid, workers)
    city.get_entertainment_building(bid).juggler_visited = 30
    __test_building_update_day(bid)
    __test_run_ticks(2)

    var frame = __test_building_sprite_frame_of(bid, juggler)
    __test_run_ticks(10)
    var later = __test_building_sprite_frame_of(bid, juggler)
    __log_info_native('[test:567] ' + name + ' juggler frame ' + frame + ' then ' + later
        + ' play=' + city.get_building(bid).play_animation)
    if (frame <= 0) {
        t567_fail(name + ':no_juggler_anim')
    } else if (later == frame) {
        t567_fail(name + ':juggler_frozen')
    }
}

function t567_run() {
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

    t567_check('booth', BUILDING_BOOTH, booth, 8)
    t567_check('pavilion', BUILDING_PAVILLION, pavilion, 20)
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
        && (__test_find_inlog('[test-marker] t567_ok') || __test_find_inlog('[test-marker] t567_skipped:no_resource'))
}

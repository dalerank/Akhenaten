// The tile heights of a pyramid or mastaba under construction come from the simulation, not from the draw: they
// are set as soon as blocks are laid, stay the same when the camera turns, survive a save and load, and the draw
// never writes them.

var __test580_ok = false

function t580_fail(msg) {
    __log_info_native('[test:580] FAIL: ' + msg)
    __test_signal_ready()
}

function t580_heights(bid) {
    var parts = __test_monument_parts(bid).split(',')
    var out = []
    var max = 0
    for (var i = 0; i < parts.length; i++) {
        var t = __building_tile(parseInt(parts[i]))
        for (var dy = 0; dy < 2; dy++) {
            for (var dx = 0; dx < 2; dx++) {
                var h = __test_map_building_height(t.x + dx, t.y + dy)
                max = Math.max(max, h)
                out.push(h)
            }
        }
    }
    return { max: max, key: out.join(',') }
}

function t580_place(type, x, y, blocks) {
    __scenario_building_allow(type, true)
    var bid = test_building_place(type, x, y)
    if (!bid) {
        return 0
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)
    new Monument(bid).boost_engine_blocks(blocks)
    return bid
}

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(900000)
    __camera_rotate_north()

    var corner = city.get_building_params_by_type(BUILDING_SMALL_PYRAMID).first_img('corner_bricks')
    if (!(corner > 0)) {
        __log_marker('monument_heights_sim_skipped')
        __test580_ok = true
        __test_signal_ready()
        return
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var pyramid = t580_place(BUILDING_SMALL_PYRAMID, cx - 14, cy - 5, 30)
    var mastaba = t580_place(BUILDING_SMALL_MASTABA, cx + 4, cy - 2, 20)
    if (!pyramid || !mastaba) {
        return t580_fail('place pyramid=' + pyramid + ' mastaba=' + mastaba)
    }

    var p0 = t580_heights(pyramid)
    var m0 = t580_heights(mastaba)
    if (p0.max <= 0 || m0.max <= 0) {
        return t580_fail('no height before any draw: pyramid=' + p0.max + ' mastaba=' + m0.max)
    }

    __test_draw_frames(3)
    __camera_rotate_left()
    __test_draw_frames(3)
    var p1 = t580_heights(pyramid)
    var m1 = t580_heights(mastaba)
    __camera_rotate_north()
    if (p1.key != p0.key || m1.key != m0.key) {
        return t580_fail('heights follow the camera: pyramid ' + p0.key + ' -> ' + p1.key + ' mastaba ' + m0.key
            + ' -> ' + m1.key)
    }

    __test_save_memory('t580')
    __test_load_memory('t580')
    var p2 = t580_heights(pyramid)
    var m2 = t580_heights(mastaba)
    if (p2.key != p0.key || m2.key != m0.key) {
        return t580_fail('heights lost on load: pyramid ' + p0.key + ' -> ' + p2.key + ' mastaba ' + m0.key + ' -> '
            + m2.key)
    }

    __log_info_native('[test:580] pyramid max=' + p0.max + ' mastaba max=' + m0.max)
    __log_marker('monument_heights_sim_ok')
    __test580_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (__test_find_inlog('[draw-phase] map_building_height_set')) {
        return false
    }
    return __test580_ok
        && (__test_find_inlog('[test-marker] monument_heights_sim_ok')
            || __test_find_inlog('[test-marker] monument_heights_sim_skipped'))
}

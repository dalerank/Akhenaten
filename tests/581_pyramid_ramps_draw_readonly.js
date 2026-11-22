// Drawing a pyramid with carpenters' ramps reads the parts' ramp state and never writes it: the ramp sprite and
// its offsets are worked out for the current view during the draw, the parts keep what the simulation stored.

var __test581_ok = false

function t581_fail(msg) {
    __log_info_native('[test:581] FAIL: ' + msg)
    __test_signal_ready()
}

function t581_ramp_states(bid) {
    var parts = __test_monument_parts(bid).split(',')
    var out = []
    for (var i = 0; i < parts.length; i++) {
        var s = __test_monument_part_state(parseInt(parts[i])).split(',')
        out.push(s[6] + '/' + s[7])
    }
    return out.join(',')
}

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    __camera_rotate_north()
    __scenario_building_allow(BUILDING_SMALL_STEPPED_PYRAMID, true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = test_building_place(BUILDING_SMALL_STEPPED_PYRAMID, cx - 4, cy - 4)
    if (!bid) {
        return t581_fail('place')
    }
    __test_camera_center_building(bid)
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)
    new Monument(bid).boost_engine_blocks(40)

    var before = t581_ramp_states(bid)
    if (before.indexOf('0/0,') == 0 && before.replace(/0\/0,?/g, '') == '') {
        return t581_fail('no ramps after 40 blocks')
    }

    __test_draw_frames(3)
    __camera_rotate_left()
    __test_draw_frames(3)
    __camera_rotate_left()
    __test_draw_frames(3)
    __camera_rotate_north()
    __test_draw_frames(2)

    if (t581_ramp_states(bid) != before) {
        return t581_fail('ramp heights changed by the draw')
    }

    __log_marker('pyramid_ramps_draw_readonly_ok')
    __test581_ok = true
    __test_signal_ready()
}

function check_valid() {
    if (__test_find_inlog('[draw-phase] pyramid_engine_update_part_ramp_image')) {
        return false
    }
    return __test581_ok && __test_find_inlog('[test-marker] pyramid_ramps_draw_readonly_ok')
}

// OG pyramid_find_frontier_parts: a stepped pyramid lays blocks on every part, outer ring included, so each part
// reaches its top layer and the carpenters' ramps (pyramid_ramp_table) go up on the outer parts.

var __test578_ok = false

function t578_fail(msg) {
    __log_info_native('[test:578] FAIL: ' + msg)
    __test_signal_ready()
}

function t578_states(bid) {
    var parts = __test_monument_parts(bid).split(',')
    var out = []
    for (var i = 0; i < parts.length; i++) {
        var s = __test_monument_part_state(parseInt(parts[i])).split(',')
        out.push({ subtype: parseInt(s[0]), stage: parseInt(s[1]), blocks: parseInt(s[2]), layer: parseInt(s[3]),
            target: parseInt(s[4]), ramp1: parseInt(s[6]) })
    }
    return out
}

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    __scenario_building_allow(BUILDING_SMALL_STEPPED_PYRAMID, true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = test_building_place(BUILDING_SMALL_STEPPED_PYRAMID, cx - 4, cy - 4)
    if (!bid) {
        return t578_fail('place')
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)
    var mon = new Monument(bid)

    mon.boost_engine_blocks(20)
    var ramped = t578_states(bid).filter(function (p) { return p.ramp1 > 0 })
    if (ramped.length == 0) {
        return t578_fail('no ramp after 20 blocks')
    }

    while (__pyramid_remaining_blocks(bid) > 0) {
        if (mon.boost_engine_blocks(10) <= 0) {
            break
        }
    }
    var states = t578_states(bid)
    for (var i = 0; i < states.length; i++) {
        var p = states[i]
        if (p.stage != 1 || p.layer != p.target) {
            return t578_fail('part ' + p.subtype + ' stage=' + p.stage + ' blocks=' + p.blocks + ' layer=' + p.layer
                + '/' + p.target)
        }
    }

    __log_marker('stepped_pyramid_frontier_ok')
    __test578_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test578_ok && __test_find_inlog('[test-marker] stepped_pyramid_frontier_ok')
}

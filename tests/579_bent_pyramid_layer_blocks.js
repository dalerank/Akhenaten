// OG pyramid_part_update_image: a bent pyramid part below its target layer draws the flat layer blocks
// (IMAGE_GROUP_PYRAMID + 95 + blocks, + 6 on odd random tiles), not a slope face.

var __test579_ok = false

function t579_fail(msg) {
    __log_info_native('[test:579] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    __scenario_building_allow(BUILDING_SMALL_BENT_PYRAMID, true)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = test_building_place(BUILDING_SMALL_BENT_PYRAMID, cx - 4, cy - 4)
    if (!bid) {
        return t579_fail('place')
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)

    var corner = city.get_building_params_by_type(BUILDING_SMALL_BENT_PYRAMID).first_img('corner_bricks')
    if (!(corner > 0)) {
        __log_marker('bent_layer_blocks_skipped')
        __test579_ok = true
        __test_signal_ready()
        return
    }

    var parts = __test_monument_parts(bid).split(',')
    var inner = 0
    for (var i = 0; i < parts.length && !inner; i++) {
        var s = __test_monument_part_state(parseInt(parts[i])).split(',')
        if (parseInt(s[3]) < parseInt(s[4])) {
            inner = parseInt(parts[i])
        }
    }
    if (!inner) {
        return t579_fail('no part below its target layer')
    }

    __test_pyramid_part_set_blocks(inner, 0, 3)
    var offset = __test_pyramid_part_draw_image(inner) - corner
    if (offset != 95 + 3 && offset != 95 + 3 + 6) {
        return t579_fail('inner part ' + inner + ' image offset ' + offset)
    }

    __log_marker('bent_layer_blocks_ok')
    __test579_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test579_ok
        && (__test_find_inlog('[test-marker] bent_layer_blocks_ok')
            || __test_find_inlog('[test-marker] bent_layer_blocks_skipped'))
}

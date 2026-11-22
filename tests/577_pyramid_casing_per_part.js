// OG pyramid_part_update_image: a true or mudbrick pyramid part on the casing stage draws
// IMAGE_GROUP_PYRAMID + (11 - blocks) * 8 + kind, so casing shows part by part, not layer by layer.

var __test577_ok = false

function t577_fail(msg) {
    __log_info_native('[test:577] FAIL: ' + msg)
    __test_signal_ready()
}

function t577_check(type, name, x, y) {
    __scenario_building_allow(type, true)
    var bid = test_building_place(type, x, y)
    if (!bid) {
        return 'place ' + name
    }
    __test_monument_set_phase(bid, 2)
    __pyramid_start_block_phase(bid)

    var corner = city.get_building_params_by_type(type).first_img('corner_bricks')
    if (!(corner > 0)) {
        return 'no_art'
    }
    var parts = __test_monument_parts(bid).split(',')
    if (parts.length < 3) {
        return 'parts ' + name + ' ' + parts.length
    }
    var a = parseInt(parts[1])
    var b = parseInt(parts[2])

    __test_pyramid_part_set_blocks(a, 1, 6)
    __test_pyramid_part_set_blocks(b, 1, 6)
    var a6 = __test_pyramid_part_draw_image(a)
    var b6 = __test_pyramid_part_draw_image(b)
    __test_pyramid_part_set_blocks(a, 1, 3)
    var a3 = __test_pyramid_part_draw_image(a)
    var b_after = __test_pyramid_part_draw_image(b)
    __test_pyramid_part_set_blocks(a, 1, 0)
    var a0 = __test_pyramid_part_draw_image(a)

    var kind = a6 - corner - 5 * 8
    if (kind < 0 || kind > 8) {
        return name + ' casing row 5 expected, img=' + a6 + ' corner=' + corner
    }
    if (a3 - a6 != 3 * 8 || a0 - a6 != 6 * 8) {
        return name + ' casing rows a6=' + a6 + ' a3=' + a3 + ' a0=' + a0
    }
    if (b_after != b6) {
        return name + ' neighbour changed ' + b6 + ' -> ' + b_after
    }
    __log_info_native('[test:577] ' + name + ' a6=' + a6 + ' a3=' + a3 + ' a0=' + a0 + ' b=' + b6)
    return ''
}

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var err = t577_check(BUILDING_SMALL_PYRAMID, 'true', cx - 14, cy - 5)
    if (!err) {
        err = t577_check(BUILDING_SMALL_MUDBRICK_PYRAMID, 'mudbrick', cx + 4, cy - 5)
    }
    if (err == 'no_art') {
        __log_marker('pyramid_casing_per_part_skipped')
        __test577_ok = true
        __test_signal_ready()
        return
    }
    if (err) {
        return t577_fail(err)
    }

    __log_marker('pyramid_casing_per_part_ok')
    __test577_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test577_ok
        && (__test_find_inlog('[test-marker] pyramid_casing_per_part_ok')
            || __test_find_inlog('[test-marker] pyramid_casing_per_part_skipped'))
}

// Editor map flags OG (figure_create_editor_flags / figure_editor_flag_action): 40 flags numbered
// 1..3, 0x0C..0x20 and 0x32..0x41, an 8-frame waving cycle, the icon per point kind, and a flag
// sits on its scenario point or stays off the map when the point is unset.

var __test232_ok = false

function test232_fail(msg) {
    __log_info_native('[test:232] FAIL: ' + msg)
    __test_signal_ready()
}

function test232_flags() {
    var flags = {}
    for (var fid = 1; fid < 2000; fid++) {
        if (__figure_is_valid(fid) && __figure_get_type(fid) == FIGURE_MAP_FLAG) {
            flags[__figure_get_resource(fid)] = fid
        }
    }
    return flags
}

function test232_img(pack, id, offset) {
    var img = get_image({ pack: pack, id: id, offset: offset })
    return img ? img.tid : 0
}

function run_test() {
    __log_info_native('[test:232] editor map flags OG')
    if (!game.init_editor()) {
        test232_fail('init_editor failed')
        return
    }

    var flags = test232_flags()
    var expected = [1, 2, 3]
    for (var n = 0x0C; n <= 0x20; n++) expected.push(n)
    for (var m = 0x32; m <= 0x41; m++) expected.push(m)
    var count = Object.keys(flags).length
    if (count != expected.length) {
        test232_fail('expected ' + expected.length + ' flags, got ' + count)
        return
    }
    for (var i = 0; i < expected.length; i++) {
        if (!flags[expected[i]]) {
            test232_fail('missing flag number ' + expected[i])
            return
        }
    }
    __log_marker('test232_numbers')

    var fid0 = flags[1]
    for (var t = 1; t <= 9; t++) {
        __test_figure_action_perform(fid0)
        if (__figure_get_wait_ticks(fid0) != t % 8) {
            test232_fail('frame after ' + t + ' ticks expected ' + (t % 8) + ' got ' + __figure_get_wait_ticks(fid0))
            return
        }
    }
    __log_marker('test232_frames')

    __scenario_editor_clear_fishing_points()
    __scenario_editor_clear_invasion_points()
    var off = [0x0E, 0x32, 0x3A, 0x1A, 0x1E]
    for (var o = 0; o < off.length; o++) {
        var f = flags[off[o]]
        __test_figure_action_perform(f)
        var tile = __figure_get_tile(f)
        if (tile && tile.x >= 0 && tile.y >= 0) {
            test232_fail('flag ' + off[o] + ' with an unset point must stay off the map, at ' + tile.x + ',' + tile.y)
            return
        }
    }
    __log_marker('test232_unset_points')

    var icons = test232_img(PACK_GENERAL, 140, 0)
    if (icons > 0) {
        var checks = [
            [1, icons], [2, icons + 2], [3, icons + 3], [0x0C, icons + 4], [0x0D, icons + 5], [0x32, icons + 1],
            [0x0E, __image_id_resource_icon_int(RESOURCE_FISH)],
            [0x16, test232_img(PACK_GENERAL, 127, 1)],
            [0x1A, test232_img(PACK_GENERAL, 127, 5)],
            [0x1E, test232_img(PACK_GENERAL, 177, 0)],
            [0x3A, test232_img(PACK_GENERAL, 79, 0)]
        ]
        for (var c = 0; c < checks.length; c++) {
            var cf = flags[checks[c][0]]
            __test_figure_action_perform(cf)
            if (__test_figure_cart_image_id(cf) != checks[c][1]) {
                test232_fail('flag ' + checks[c][0] + ' icon expected ' + checks[c][1] + ' got ' + __test_figure_cart_image_id(cf))
                return
            }
        }
        __log_marker('test232_icons')
    } else {
        __log_marker('test232_icons_skipped_no_data')
    }

    __test232_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test232_ok
        && __test_find_inlog('[test-marker] test232_numbers')
        && __test_find_inlog('[test-marker] test232_frames')
        && __test_find_inlog('[test-marker] test232_unset_points')
        && (__test_find_inlog('[test-marker] test232_icons') || __test_find_inlog('[test-marker] test232_icons_skipped_no_data'))
}

// Verifies full COLOR_MASK_* values survive the MuJS -> C++ boundary as color (uint32). [J1]
// COLOR_MASK_GREEN (0xff18ff18) and COLOR_MASK_RED (0xffff0818) exceed INT_MAX and used to
// be corrupted by js_tointeger; color params now use js_touint32. COLOR_MASK_BLUE is a
// control value below INT_MAX.
// Markers:
//   [test-marker] color_mask_green_roundtrip_ok
//   [test-marker] color_mask_red_roundtrip_ok
//   [test-marker] color_mask_blue_roundtrip_ok
//   [test-marker] color_mask_draw_no_throw_ok

function run_test() {
    __log_info_native('[test:38] color mask MuJS->C++ passing (J1)')

    var INT_MAX = 2147483647

    // The two masks that break under js_tointeger must actually be above INT_MAX,
    // otherwise this test would pass trivially and guard nothing.
    if (!(COLOR_MASK_GREEN > INT_MAX) || !(COLOR_MASK_RED > INT_MAX)) {
        __log_info_native('[test:38] precondition failed: masks not above INT_MAX'
            + ' green=' + COLOR_MASK_GREEN + ' red=' + COLOR_MASK_RED)
        __test_signal_ready()
        return
    }

    var green = __test_color_roundtrip(COLOR_MASK_GREEN)
    if (green != COLOR_MASK_GREEN || green <= INT_MAX) {
        __log_info_native('[test:38] green roundtrip corrupted got=' + green
            + ' want=' + COLOR_MASK_GREEN)
        __test_signal_ready()
        return
    }
    __log_marker('color_mask_green_roundtrip_ok')

    var red = __test_color_roundtrip(COLOR_MASK_RED)
    if (red != COLOR_MASK_RED || red <= INT_MAX) {
        __log_info_native('[test:38] red roundtrip corrupted got=' + red
            + ' want=' + COLOR_MASK_RED)
        __test_signal_ready()
        return
    }
    __log_marker('color_mask_red_roundtrip_ok')

    // Control: a mask below INT_MAX must also pass unchanged.
    var blue = __test_color_roundtrip(COLOR_MASK_BLUE)
    if (blue != COLOR_MASK_BLUE) {
        __log_info_native('[test:38] blue roundtrip corrupted got=' + blue
            + ' want=' + COLOR_MASK_BLUE)
        __test_signal_ready()
        return
    }
    __log_marker('color_mask_blue_roundtrip_ok')

    // Exercise the real draw binding (the one J1 changed) with a full mask: it must not
    // raise a MuJS TypeError. draw_flat_tile draws a solid-color tile with no image lookup.
    test_ensure_city_session('data/default.map')
    city.planner.draw_flat_tile({ x: 100, y: 100 }, COLOR_MASK_GREEN)
    __log_marker('color_mask_draw_no_throw_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'color_mask_green_roundtrip_ok',
        'color_mask_red_roundtrip_ok',
        'color_mask_blue_roundtrip_ok',
        'color_mask_draw_no_throw_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:38] missing marker: ' + marker)
            return false
        }
    }
    return true
}

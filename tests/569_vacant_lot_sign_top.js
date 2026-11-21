// The vacant lot sign rises above its tile although the image is exactly one tile high (isometric top height 0).
// Its tile must still be drawn with a top, or the upper rows of the sign are missing. Needs the Pharaoh data.
// Markers:
//   [test-marker] t569_ok
//   [test-marker] t569_skipped:no_resource
//   [test-marker] t569_fail:<what>

var __t569_failed = false

function t569_fail(what) {
    __log_info_native('[test-marker] t569_fail:' + what)
    __t569_failed = true
}

function t569_run() {
    if (!test_reload_city_session('data/default.map')) {
        return t569_fail('map_load')
    }
    ui.window_city_show()

    var x = (__scenario_map.width / 2) | 0
    var y = (__scenario_map.height / 2) | 0
    var lot = __test_building_create(BUILDING_HOUSE_VACANT_LOT, x, y)
    if (!lot) {
        return t569_fail('place')
    }
    var img = get_image({ tid: __test_map_image_at(x, y) })
    if (!img || img.height <= 0) {
        __log_info_native('[test-marker] t569_skipped:no_resource')
        return
    }

    __test_camera_center_building(lot)
    __test_draw_frames(2)
    var tall = __test_map_render_tall(x, y)
    __log_info_native('[test:569] lot image ' + img.tid + ' ' + img.width + 'x' + img.height + ' tall=' + tall)
    if (!tall) {
        t569_fail('lot_top_not_drawn')
    }
}

function run_test() {
    t569_run()
    test_reload_city_session('data/default.map')
    if (!__t569_failed && !__test_find_inlog('[test-marker] t569_skipped:no_resource')) {
        __log_info_native('[test-marker] t569_ok')
    }
    __test_signal_ready()
}

function check_valid() {
    return !__t569_failed
        && (__test_find_inlog('[test-marker] t569_ok') || __test_find_inlog('[test-marker] t569_skipped:no_resource'))
}

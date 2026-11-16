// Issue #695: walkers standing on every tile of a ferry landing, rendered in all four camera
// orientations. Checks only that the frames draw without errors; the depth order itself is
// verified by eye: with Pharaoh data one display screenshot per orientation is saved.
//   build\RelWithDebInfo\akhenaten.exe --integraltests --integraltest-only 491 --nointro --nomouse ^
//     --no-logo --nosound --window --size 1200x800 --screenshot-dir <dir> "d:/Work/Cleop"

var __test491 = { bid: 0, walkers: 0, orientations: 0 }

function run_test() {
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)
    __scenario_building_allow(BUILDING_FERRY, true)

    var bid = test_shoreline_building_place(BUILDING_FERRY, 2)
    __test491.bid = bid
    if (!bid) {
        __log_marker('ferry_draw_place_fail')
        __test_signal_ready()
        return
    }

    var tile = __building_tile(bid)
    var art = false
    for (var dy = 0; dy < 2; dy++) {
        for (var dx = 0; dx < 2; dx++) {
            var fid = __test_figure_create(FIGURE_LABOR_SEEKER, tile.x + dx, tile.y + dy)
            if (fid) {
                __test_figure_update_animation(fid)
                __test_figure_refresh_image(fid)
                art = art || __test_figure_main_image_id(fid) > 0
                __test491.walkers++
            }
        }
    }
    __log_marker('ferry_draw_walkers:' + __test491.walkers)

    __test_process_events()
    window_go_back()
    // Homeless walkers die on the next tick; keep them standing while the frames draw.
    game.paused = true
    __camera_sidebar_collapsed(1)
    __camera_rotate_north()
    for (var orient = 0; orient < 4; orient++) {
        __test_camera_center_building(bid)
        __test_pump_frames(6)
        if (art) {
            __game_save_screenshot(SCREENSHOT_DISPLAY)
            // Screenshot names carry the time in seconds.
            __test_sleep_ms(1100)
        }
        __test491.orientations++
        __camera_rotate_left()
        __test_pump_frames(4)
    }
    __camera_rotate_north()
    game.paused = false
    __log_marker('ferry_draw_orientations:' + __test491.orientations)
    __test_signal_ready()
}

function check_valid() {
    return __test491.bid > 0
        && __test491.walkers == 4
        && __test491.orientations == 4
        && __test_find_inlog('[test-marker] ferry_draw_orientations:4')
}

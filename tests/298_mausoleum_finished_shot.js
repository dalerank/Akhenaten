// Finished OG mausoleum screenshot on default.map.
//   build\RelWithDebInfo\akhenaten.exe --integraltests --integraltest-only 298_mausoleum_finished_shot ^
//     --nointro --nomouse --no-logo --nosound --nocrashdlg --window --size 1200x800 ^
//     --screenshot-dir d:/Work/Akhenaten-wt-mausoleum-og/tmp/mausoleum_shot "d:/Work/Cleop"

function run_test() {
    __log_info_native('[test:298] finished mausoleum screenshot')
    test_reload_city_session('data/default.map')
    if (!__scenario_building_allowed(BUILDING_MAUSOLEUM)) {
        __scenario_building_allow(BUILDING_MAUSOLEUM, true)
    }
    if (!__scenario_building_allowed(BUILDING_STORAGE_YARD)) {
        __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    }
    __test_set_treasury(50000)

    var sy = test_staffed_yard_with_resource(RESOURCE_SANDSTONE, 300, 8, 8)
    if (!sy) {
        sy = test_staffed_yard_with_resource(RESOURCE_SANDSTONE, 300, -1, -1)
    }
    if (!sy) {
        __log_marker('mausoleum_shot_yard_fail')
        __test_signal_ready()
        return
    }

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var bid = 0
    var candidates = [
        {x: cx, y: cy},
        {x: 40, y: 40},
        {x: 50, y: 50},
        {x: 60, y: 45},
        {x: 30, y: 50}
    ]
    for (var i = 0; i < candidates.length && !bid; i++) {
        bid = test_building_place(BUILDING_MAUSOLEUM, candidates[i].x, candidates[i].y)
    }
    if (!bid) {
        __log_marker('mausoleum_shot_place_fail')
        __test_signal_ready()
        return
    }
    __log_marker('mausoleum_shot_placed:' + bid)

    __test_monument_set_phase(bid, -1)
    __test_pump_frames(8)
    if (__test_mausoleum_progress(bid) != 100) {
        __log_marker('mausoleum_shot_finish_fail:' + __test_mausoleum_progress(bid))
        __test_signal_ready()
        return
    }
    __log_marker('mausoleum_shot_finished')

    // Main part is a 4x4 block; also accept a ground part image (fence art from sun-temple extras).
    var img = __test_building_current_image(bid)
    if (img <= 0) {
        var ground = __test_mausoleum_part_id(bid, 4)
        img = ground ? __test_building_current_image(ground) : 0
    }
    if (img <= 0) {
        __log_info_native('[test:298] art packs not loaded — skipping screenshot')
        __log_marker('mausoleum_shot_art_skipped')
        __test_signal_ready()
        return
    }
    __log_marker('mausoleum_shot_art_ok:' + img)

    __test_process_events()
    window_go_back()
    __camera_sidebar_collapsed(1)
    __zoom_set(160)
    __test_pump_frames(10)
    __test_camera_center_building(bid)
    __test_pump_frames(8)
    __game_save_screenshot(SCREENSHOT_DISPLAY)
    __log_marker('mausoleum_shot_display_done')
    __test_pump_frames(2)
    __game_save_screenshot(SCREENSHOT_FULL_CITY)
    __log_marker('mausoleum_shot_fullcity_done')
    __log_marker('mausoleum_shot_done')
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] mausoleum_shot_done')
        || __test_find_inlog('[test-marker] mausoleum_shot_art_skipped')
}

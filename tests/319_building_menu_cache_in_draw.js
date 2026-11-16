// The build-menu caches may first be filled by the sidebar draw, which runs in the frame arena: after a VM
// rebuild in a running city the first count_items/is_submenu call comes from there. Creating the cache objects
// in that draw stored frame-arena objects in a global ("ephemeral object escaped to heap") and aborted the game.
// Markers:
//   [test-marker] building_menu_cache_in_draw_ok

function run_test() {
    __log_info_native('[test:319] building menu caches filled from the draw')
    test_reload_city_session('data/default.map')
    __test_pump_frames(2)

    // The state the draw sees right after a VM rebuild: nothing cached yet.
    building_menu_ctrl.submenu_ids_ready = false
    building_menu_ctrl.invalidate_counts()
    __test_pump_frames(3)

    if (building_menu_ctrl.submenu_ids_ready && !__test_find_inlog('ephemeral object escaped')) {
        __log_marker('building_menu_cache_in_draw_ok')
    } else {
        __log_info_native('[test:319] FAIL: caches ready=' + building_menu_ctrl.submenu_ids_ready)
    }
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('building_menu_cache_in_draw_ok')
}

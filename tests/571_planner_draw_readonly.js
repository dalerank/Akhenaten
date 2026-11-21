// Drawing the city with a build tool active must not change the saved state. With the clear-land tool over a
// building and "visual feedback on delete" on, the tiles to delete are marked by the planner when it handles the
// cursor; frames that only draw (no input) must leave the map as it is.
// Markers:
//   [test-marker] t571_ok
//   [test-marker] t571_fail:<what>

var __t571_failed = false

function t571_fail(what) {
    __log_info_native('[test-marker] t571_fail:' + what)
    __t571_failed = true
}

function t571_run() {
    if (!test_reload_city_session('data/default.map')) {
        return t571_fail('load')
    }
    __camera_rotate_north()
    var bid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, (__scenario_map.width / 2) | 0, (__scenario_map.height / 2) | 0)
    if (!bid) {
        return t571_fail('place')
    }
    if (!test_planner_enter_build_mode(BUILDING_CLEAR_LAND)) {
        return t571_fail('clear_land_mode')
    }
    __test_camera_center_building(bid)
    __test_mouse_move(__camera.offset.x + (__camera.size_pixels.x >> 1), __camera.offset.y + (__camera.size_pixels.y >> 1))
    if (__building_at(city_planner.end.x, city_planner.end.y) != bid) {
        return t571_fail('cursor_not_on_building:' + city_planner.end.x + ',' + city_planner.end.y)
    }

    __map_property_clear_constructing_and_deleted()
    __test_state_mark()
    __test_draw_frames(3)
    var changed = __test_state_diff('t571_draw')
    test_planner_exit_build_mode()
    if (changed != '') {
        return t571_fail('draw_changed:' + changed)
    }
    __log_info_native('[test-marker] t571_ok')
}

function run_test() {
    var feedback = game_features.get('gameui_visual_feedback_on_delete')
    game_features.set('gameui_visual_feedback_on_delete', true)
    t571_run()
    game_features.set('gameui_visual_feedback_on_delete', feedback)
    __test_signal_ready()
}

function check_valid() {
    return !__t571_failed && __test_find_inlog('[test-marker] t571_ok')
}

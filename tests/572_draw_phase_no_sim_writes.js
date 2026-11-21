// The draw may not write the simulation: map images (except the water frames, which follow the OG timing),
// the constructing/deleted map bits and the build planner are written only outside the draw. A write during the
// draw logs "[draw-phase] <where> writes the simulation during the draw". This test draws a city with a build tool
// over a building; check_valid also fails on any such line an earlier test in the same run produced.
// Markers:
//   [test-marker] t572_drawn
//   [draw-phase] <where> writes the simulation during the draw   (must not appear)

var __t572_drawn = false

function run_test() {
    if (!test_reload_city_session('data/default.map')) {
        __test_signal_ready()
        return
    }
    __camera_rotate_north()
    var feedback = game_features.get('gameui_visual_feedback_on_delete')
    game_features.set('gameui_visual_feedback_on_delete', true)

    var bid = __test_building_create(BUILDING_HOUSE_CRUDE_HUT, (__scenario_map.width / 2) | 0, (__scenario_map.height / 2) | 0)
    if (bid && test_planner_enter_build_mode(BUILDING_CLEAR_LAND)) {
        __test_camera_center_building(bid)
        __test_mouse_move(__camera.offset.x + (__camera.size_pixels.x >> 1), __camera.offset.y + (__camera.size_pixels.y >> 1))
        __test_pump_frames(5)
        __test_draw_frames(3)
        test_planner_exit_build_mode()
        __test_pump_frames(5)
        __t572_drawn = true
        __log_info_native('[test-marker] t572_drawn')
    }

    game_features.set('gameui_visual_feedback_on_delete', feedback)
    __test_signal_ready()
}

function check_valid() {
    return __t572_drawn && !__test_find_inlog('[draw-phase]')
}

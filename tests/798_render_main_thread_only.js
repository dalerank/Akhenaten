// The city view draws in parallel blocks; the blocks may only record commands, never draw through SDL.
// A Food Mill and an Industry Office on screen exercise their flat and height draw hooks in those blocks,
// and no render call may report that it ran off the main thread.
// Markers:
//   [test-marker] t798_drawn
//   [render] <function> called off the main thread   (must not appear)

var __t798_ok = false

function t798_place(type) {
    var bid = __test_building_create(type, -1, -1)
    if (!bid) {
        __log_info_native('[test:798] could not place type ' + type)
        return 0
    }
    __test_camera_center_building(bid)
    __test_pump_frames(10)
    return bid
}

function run_test() {
    if (!test_reload_city_session('data/default.map')) {
        __test_signal_ready()
        return
    }
    var mill_prev = game_features.get('gameplay_enhanced_food_mill')
    game_features.set('gameplay_enhanced_food_mill', true)

    var mill = t798_place(BUILDING_FOOD_MILL)
    var office = t798_place(BUILDING_INDUSTRY_OFFICE)
    if (mill && office) {
        __log_info_native('[test-marker] t798_drawn')
        __t798_ok = true
    }

    game_features.set('gameplay_enhanced_food_mill', mill_prev)
    __test_signal_ready()
}

function check_valid() {
    if (!__t798_ok || !__test_find_inlog('[test-marker] t798_drawn')) {
        return false
    }
    if (__test_find_inlog('called off the main thread')) {
        __log_info_native('[test:798] FAIL: a render call ran off the main thread')
        return false
    }
    return true
}

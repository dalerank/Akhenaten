// Food Mill: flag gates menu; apply_enhanced unlocks without mission buildings[];
// place via city_planner.
// Markers:
//   [test-marker] food_mill_menu_flag_off_ok
//   [test-marker] food_mill_menu_apply_enhanced_ok
//   [test-marker] test_building_placed:type_<BUILDING_FOOD_MILL>:...

var __test071_ok = {
    flag_off: false,
    menu_on: false,
    placed: false
}
var __test071_bid = null

function run_test() {
    __log_info_native('[test:071] food mill menu + place')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var mill_prev = game_features.get('gameplay_enhanced_food_mill')
    function finish() {
        game_features.set('gameplay_enhanced_food_mill', mill_prev)
        __test_signal_ready()
    }

    game_features.set('gameplay_enhanced_food_mill', false)
    building_menu_ctrl.enabled[BUILDING_FOOD_MILL] = false
    if (building_menu_ctrl.is_enabled(BUILDING_FOOD_MILL)) {
        __log_info_native('[test:071] menu should be off while flag OFF')
        finish()
        return
    }
    __log_marker('food_mill_menu_flag_off_ok')
    __test071_ok.flag_off = true

    game_features.set('gameplay_enhanced_food_mill', true)
    // Flag toggle emits apply_enhanced; also call explicitly for clarity.
    building_menu_ctrl.apply_enhanced_buildings()
    if (!building_menu_ctrl.is_enabled(BUILDING_FOOD_MILL)) {
        __log_info_native('[test:071] menu should unlock after apply_enhanced')
        finish()
        return
    }
    if (!__scenario_building_allowed(BUILDING_FOOD_MILL)) {
        __log_info_native('[test:071] scenario should allow mill after apply_enhanced')
        finish()
        return
    }
    __log_marker('food_mill_menu_apply_enhanced_ok')
    __test071_ok.menu_on = true

    var bid = test_building_place(BUILDING_FOOD_MILL, -1, -1)
    __test071_bid = bid
    if (!bid) {
        __log_info_native('[test:071] test_building_place failed')
        finish()
        return
    }
    if (__building_type(bid) != BUILDING_FOOD_MILL) {
        __log_info_native('[test:071] wrong type ' + __building_type(bid))
        finish()
        return
    }
    __test071_ok.placed = true
    finish()
}

function check_valid() {
    if (!__test071_ok.flag_off || !__test071_ok.menu_on || !__test071_ok.placed) {
        __log_info_native('[test:071] one or more phases failed')
        return false
    }
    if (!__test071_bid) {
        __log_info_native('[test:071] no building id')
        return false
    }
    var markers = [
        'food_mill_menu_flag_off_ok',
        'food_mill_menu_apply_enhanced_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:071] missing marker: ' + markers[i])
            return false
        }
    }
    var place_marker = '[test-marker] test_building_placed:type_' + BUILDING_FOOD_MILL
    if (!__test_find_inlog(place_marker)) {
        __log_info_native('[test:071] missing marker: ' + place_marker)
        return false
    }
    return true
}

// Weaponsmith update_animation (JS in weaponsmith.js):
// 1) Handler stops animation when progress is 0 and copper is missing.
// 2) Handler keeps animation when copper is present.

var __test116_ok = false

function run_test() {
    __log_info_native('[test:116] weaponsmith animation rules')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_WEAPONSMITH, -1, -1)
    if (!bid) {
        __log_info_native('[test:116] place failed')
        __test_signal_ready()
        return
    }

    var ev = { bid: bid }
    var b

    b = city.get_building(bid)
    b.play_animation = true
    building_weaponsmith_on_update_animation(ev)
    b = city.get_building(bid)
    if (b.play_animation) {
        __log_info_native('[test:116] FAIL: handler left play_animation=true without copper')
        __test_signal_ready()
        return
    }
    __log_marker('test116_handler_stops_without_copper')

    b.consume_resource(RESOURCE_COPPER, -100)
    b.play_animation = true
    building_weaponsmith_on_update_animation(ev)
    b = city.get_building(bid)
    if (!b.play_animation) {
        __log_info_native('[test:116] FAIL: handler cleared play_animation with copper'
            + ' copper=' + b.stored_resource(RESOURCE_COPPER))
        __test_signal_ready()
        return
    }
    __log_marker('test116_handler_keeps_with_copper')

    __test116_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test116_ok
        && __test_find_inlog('[test-marker] test116_handler_stops_without_copper')
        && __test_find_inlog('[test-marker] test116_handler_keeps_with_copper')
}

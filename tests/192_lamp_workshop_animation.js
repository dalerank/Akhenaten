// Lamp workshop update_animation (JS in lamp_workshop.js):
// 1) Handler stops animation when progress is 0 and oil/pottery are missing.
// 2) Handler keeps animation when both inputs are present.

var __test192_ok = false

function run_test() {
    __log_info_native('[test:192] lamp workshop animation rules')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_LAMP_WORKSHOP, -1, -1)
    if (!bid) {
        __log_info_native('[test:192] place failed')
        __test_signal_ready()
        return
    }

    var ev = { bid: bid }
    var b

    b = city.get_building(bid)
    b.play_animation = true
    building_lamp_workshop_on_update_animation(ev)
    b = city.get_building(bid)
    if (b.play_animation) {
        __log_info_native('[test:192] FAIL: handler left play_animation=true without materials')
        __test_signal_ready()
        return
    }
    __log_marker('test192_handler_stops_without_materials')

    b.consume_resource(RESOURCE_OIL, -100)
    b.consume_resource(RESOURCE_POTTERY, -100)
    b.play_animation = true
    building_lamp_workshop_on_update_animation(ev)
    b = city.get_building(bid)
    if (!b.play_animation) {
        __log_info_native('[test:192] FAIL: handler cleared play_animation with oil+pottery'
            + ' oil=' + b.stored_resource(RESOURCE_OIL)
            + ' pottery=' + b.stored_resource(RESOURCE_POTTERY))
        __test_signal_ready()
        return
    }
    __log_marker('test192_handler_keeps_with_materials')

    __test192_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test192_ok
        && __test_find_inlog('[test-marker] test192_handler_stops_without_materials')
        && __test_find_inlog('[test-marker] test192_handler_keeps_with_materials')
}

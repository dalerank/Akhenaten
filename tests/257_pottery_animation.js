// Pottery update_animation (JS in pottery.js):
// 1) Handler stops animation when progress is 0 and clay is missing.
// 2) Output pottery alone must not keep the animation running.
// 3) Handler keeps animation when clay is present.

var __test257_ok = false

function run_test() {
    __log_info_native('[test:257] pottery animation rules')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_POTTERY_WORKSHOP, -1, -1)
    if (!bid) {
        __log_info_native('[test:257] place failed')
        __test_signal_ready()
        return
    }

    var ev = { bid: bid }
    var b

    b = city.get_building(bid)
    b.play_animation = true
    building_pottery_on_update_animation(ev)
    b = city.get_building(bid)
    if (b.play_animation) {
        __log_info_native('[test:257] FAIL: handler left play_animation=true without clay')
        __test_signal_ready()
        return
    }
    __log_marker('test257_handler_stops_without_clay')

    b.consume_resource(RESOURCE_POTTERY, -100)
    b.play_animation = true
    building_pottery_on_update_animation(ev)
    b = city.get_building(bid)
    if (b.play_animation) {
        __log_info_native('[test:257] FAIL: handler left play_animation=true with pottery but no clay'
            + ' pottery=' + b.stored_resource(RESOURCE_POTTERY)
            + ' clay=' + b.stored_resource(RESOURCE_CLAY))
        __test_signal_ready()
        return
    }
    __log_marker('test257_handler_ignores_pottery_stock')

    b.consume_resource(RESOURCE_CLAY, -100)
    b.play_animation = true
    building_pottery_on_update_animation(ev)
    b = city.get_building(bid)
    if (!b.play_animation) {
        __log_info_native('[test:257] FAIL: handler cleared play_animation with clay'
            + ' clay=' + b.stored_resource(RESOURCE_CLAY))
        __test_signal_ready()
        return
    }
    __log_marker('test257_handler_keeps_with_clay')

    __test257_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test257_ok
        && __test_find_inlog('[test-marker] test257_handler_stops_without_clay')
        && __test_find_inlog('[test-marker] test257_handler_ignores_pottery_stock')
        && __test_find_inlog('[test-marker] test257_handler_keeps_with_clay')
}

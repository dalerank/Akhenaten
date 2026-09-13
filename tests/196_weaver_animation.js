// Weaver update_animation (JS in weaver.js):
// 1) Handler stops animation when progress is 0 and flax is missing.
// 2) Handler keeps animation when flax is present.

var __test196_ok = false

function run_test() {
    __log_info_native('[test:196] weaver animation rules')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_WEAVER_WORKSHOP, -1, -1)
    if (!bid) {
        __log_info_native('[test:196] place failed')
        __test_signal_ready()
        return
    }

    var ev = { bid: bid }
    var b

    b = city.get_building(bid)
    b.play_animation = true
    building_weaver_on_update_animation(ev)
    b = city.get_building(bid)
    if (b.play_animation) {
        __log_info_native('[test:196] FAIL: handler left play_animation=true without flax')
        __test_signal_ready()
        return
    }
    __log_marker('test196_handler_stops_without_flax')

    b.consume_resource(RESOURCE_FLAX, -100)
    b.play_animation = true
    building_weaver_on_update_animation(ev)
    b = city.get_building(bid)
    if (!b.play_animation) {
        __log_info_native('[test:196] FAIL: handler cleared play_animation with flax'
            + ' flax=' + b.stored_resource(RESOURCE_FLAX))
        __test_signal_ready()
        return
    }
    __log_marker('test196_handler_keeps_with_flax')

    __test196_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test196_ok
        && __test_find_inlog('[test-marker] test196_handler_stops_without_flax')
        && __test_find_inlog('[test-marker] test196_handler_keeps_with_flax')
}

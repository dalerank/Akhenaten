// Papyrus maker update_animation (JS in papyrus_maker.js):
// 1) Handler stops animation when progress is 0 and reeds are missing.
// 2) Handler keeps animation when reeds are present.

var __test193_ok = false

function run_test() {
    __log_info_native('[test:193] papyrus maker animation rules')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_PAPYRUS_WORKSHOP, -1, -1)
    if (!bid) {
        __log_info_native('[test:193] place failed')
        __test_signal_ready()
        return
    }

    var ev = { bid: bid }
    var b

    b = city.get_building(bid)
    b.play_animation = true
    building_papyrus_maker_on_update_animation(ev)
    b = city.get_building(bid)
    if (b.play_animation) {
        __log_info_native('[test:193] FAIL: handler left play_animation=true without reeds')
        __test_signal_ready()
        return
    }
    __log_marker('test193_handler_stops_without_reeds')

    b.consume_resource(RESOURCE_REEDS, -100)
    b.play_animation = true
    building_papyrus_maker_on_update_animation(ev)
    b = city.get_building(bid)
    if (!b.play_animation) {
        __log_info_native('[test:193] FAIL: handler cleared play_animation with reeds'
            + ' reeds=' + b.stored_resource(RESOURCE_REEDS))
        __test_signal_ready()
        return
    }
    __log_marker('test193_handler_keeps_with_reeds')

    __test193_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test193_ok
        && __test_find_inlog('[test-marker] test193_handler_stops_without_reeds')
        && __test_find_inlog('[test-marker] test193_handler_keeps_with_reeds')
}

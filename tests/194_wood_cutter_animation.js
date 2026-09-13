// Wood cutter update_animation (JS in wood_cutter.js):
// 1) Handler stops animation when timber is at max storage.
// 2) Handler keeps animation when timber is below max storage.

var __test194_ok = false

function run_test() {
    __log_info_native('[test:194] wood cutter animation rules')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_WOOD_CUTTERS, -1, -1)
    if (!bid) {
        __log_info_native('[test:194] place failed')
        __test_signal_ready()
        return
    }

    var ev = { bid: bid }
    var b
    var max_storage = building_wood_cutter.max_storage_amount

    b = city.get_building(bid)
    b.consume_resource(RESOURCE_TIMBER, -max_storage)
    b.play_animation = true
    building_wood_cutter_on_update_animation(ev)
    b = city.get_building(bid)
    if (b.play_animation) {
        __log_info_native('[test:194] FAIL: handler left play_animation=true at full storage')
        __test_signal_ready()
        return
    }
    __log_marker('test194_handler_stops_at_full_storage')

    b.consume_resource(RESOURCE_TIMBER, max_storage)
    b.consume_resource(RESOURCE_TIMBER, -50)
    b.play_animation = true
    building_wood_cutter_on_update_animation(ev)
    b = city.get_building(bid)
    if (!b.play_animation) {
        __log_info_native('[test:194] FAIL: handler cleared play_animation below max'
            + ' timber=' + b.stored_resource(RESOURCE_TIMBER)
            + ' max=' + max_storage)
        __test_signal_ready()
        return
    }
    __log_marker('test194_handler_keeps_below_max')

    __test194_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test194_ok
        && __test_find_inlog('[test-marker] test194_handler_stops_at_full_storage')
        && __test_find_inlog('[test-marker] test194_handler_keeps_below_max')
}

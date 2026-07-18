// Bricks workshop update_animation (JS in workshop.js):
// 1) Handler stops animation when progress is 0 and clay/straw are missing.
// 2) Handler keeps animation when both inputs are present.
// 3) Real day tick also stops animation for a staffed workshop with no materials.
//
// Note: Building JS wrappers can cache property values — always re-fetch via
// city.get_building(bid) after code that mutates play_animation.

var __test28_ok = false

function run_test() {
    __log_info_native('[test:28] bricks workshop animation rules')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_BRICKS_WORKSHOP, -1, -1)
    if (!bid) {
        __log_info_native('[test:28] place failed')
        __test_signal_ready()
        return
    }

    var ev = { bid: bid }
    var b

    // --- handler: no materials → stop ---
    b = city.get_building(bid)
    b.play_animation = true
    building_bricks_workshop_on_update_animation(ev)
    b = city.get_building(bid)
    if (b.play_animation) {
        __log_info_native('[test:28] FAIL: handler left play_animation=true without materials')
        __test_signal_ready()
        return
    }
    __log_marker('test28_handler_stops_without_materials')

    // --- handler: both materials → keep ---
    // consume_resource(negative) adds into sparse building storage.
    b.consume_resource(RESOURCE_CLAY, -100)
    b.consume_resource(RESOURCE_STRAW, -100)
    b.play_animation = true
    building_bricks_workshop_on_update_animation(ev)
    b = city.get_building(bid)
    if (!b.play_animation) {
        __log_info_native('[test:28] FAIL: handler cleared play_animation with clay+straw'
            + ' clay=' + b.stored_resource(RESOURCE_CLAY)
            + ' straw=' + b.stored_resource(RESOURCE_STRAW))
        __test_signal_ready()
        return
    }
    __log_marker('test28_handler_keeps_with_materials')

    // --- integration: day tick with workers, empty stock again ---
    b.consume_resource(RESOURCE_CLAY, b.stored_resource(RESOURCE_CLAY))
    b.consume_resource(RESOURCE_STRAW, b.stored_resource(RESOURCE_STRAW))
    b.num_workers = b.max_workers
    b.play_animation = true

    for (var i = 0; i < 8; i++) {
        __test_pump_frames(120)
        b = city.get_building(bid)
        b.num_workers = b.max_workers
        if (!b.play_animation) {
            break
        }
    }

    b = city.get_building(bid)
    if (b.play_animation) {
        __log_info_native('[test:28] FAIL: day tick left play_animation=true without materials')
        __test_signal_ready()
        return
    }
    __log_marker('test28_day_tick_stops_without_materials')

    __test28_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test28_ok
        && __test_find_inlog('[test-marker] test28_handler_stops_without_materials')
        && __test_find_inlog('[test-marker] test28_handler_keeps_with_materials')
        && __test_find_inlog('[test-marker] test28_day_tick_stops_without_materials')
}

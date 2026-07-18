// Chariots workshop update_animation (JS in chariots_workshop.js):
// 1) Handler stops animation when progress is 0 and timber/weapons are missing.
// 2) Handler keeps animation when both inputs are present.
// 3) Real day tick also stops animation for a staffed workshop with no materials.
//
// Note: Building JS wrappers can cache property values — always re-fetch via
// city.get_building(bid) after code that mutates play_animation.

var __test30_ok = false

function run_test() {
    __log_info_native('[test:30] chariots workshop animation rules')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_CHARIOTS_WORKSHOP, -1, -1)
    if (!bid) {
        __log_info_native('[test:30] place failed')
        __test_signal_ready()
        return
    }

    var ev = { bid: bid }
    var b

    // --- handler: no materials → stop ---
    b = city.get_building(bid)
    b.play_animation = true
    building_chariots_workshop_on_update_animation(ev)
    b = city.get_building(bid)
    if (b.play_animation) {
        __log_info_native('[test:30] FAIL: handler left play_animation=true without materials')
        __test_signal_ready()
        return
    }
    __log_marker('test30_handler_stops_without_materials')

    // --- handler: both materials → keep ---
    b.consume_resource(RESOURCE_TIMBER, -100)
    b.consume_resource(RESOURCE_WEAPONS, -100)
    b.play_animation = true
    building_chariots_workshop_on_update_animation(ev)
    b = city.get_building(bid)
    if (!b.play_animation) {
        __log_info_native('[test:30] FAIL: handler cleared play_animation with timber+weapons'
            + ' timber=' + b.stored_resource(RESOURCE_TIMBER)
            + ' weapons=' + b.stored_resource(RESOURCE_WEAPONS))
        __test_signal_ready()
        return
    }
    __log_marker('test30_handler_keeps_with_materials')

    // --- integration: day tick with workers, empty stock again ---
    b.consume_resource(RESOURCE_TIMBER, b.stored_resource(RESOURCE_TIMBER))
    b.consume_resource(RESOURCE_WEAPONS, b.stored_resource(RESOURCE_WEAPONS))
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
        __log_info_native('[test:30] FAIL: day tick left play_animation=true without materials')
        __test_signal_ready()
        return
    }
    __log_marker('test30_day_tick_stops_without_materials')

    __test30_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test30_ok
        && __test_find_inlog('[test-marker] test30_handler_stops_without_materials')
        && __test_find_inlog('[test-marker] test30_handler_keeps_with_materials')
        && __test_find_inlog('[test-marker] test30_day_tick_stops_without_materials')
}

// Cattle ranch update_animation (JS in cattle_ranch.js):
// 1) Handler stops animation when straw is missing or workers < 50%.
// 2) Handler keeps animation when straw is present and workers are enough.
// 3) Real day tick also stops animation for a staffed ranch with no straw.
//
// Note: Building JS wrappers can cache property values — always re-fetch via
// city.get_building(bid) after code that mutates play_animation.

var __test29_ok = false

function run_test() {
    __log_info_native('[test:29] cattle ranch animation rules')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_CATTLE_RANCH, -1, -1)
    if (!bid) {
        __log_info_native('[test:29] place failed')
        __test_signal_ready()
        return
    }

    var ev = { bid: bid }
    var b

    // --- handler: no straw → stop ---
    b = city.get_building(bid)
    b.num_workers = b.max_workers
    b.play_animation = true
    building_cattle_ranch_on_update_animation(ev)
    b = city.get_building(bid)
    if (b.play_animation) {
        __log_info_native('[test:29] FAIL: handler left play_animation=true without straw')
        __test_signal_ready()
        return
    }
    __log_marker('test29_handler_stops_without_straw')

    // --- handler: straw + full workers → keep ---
    b.consume_resource(RESOURCE_STRAW, -100)
    b.num_workers = b.max_workers
    b.play_animation = true
    building_cattle_ranch_on_update_animation(ev)
    b = city.get_building(bid)
    if (!b.play_animation) {
        __log_info_native('[test:29] FAIL: handler cleared play_animation with straw+workers'
            + ' straw=' + b.stored_resource(RESOURCE_STRAW)
            + ' workers=' + b.worker_percentage)
        __test_signal_ready()
        return
    }
    __log_marker('test29_handler_keeps_with_straw')

    // --- handler: straw but low workers → stop ---
    b.num_workers = 0
    b.play_animation = true
    building_cattle_ranch_on_update_animation(ev)
    b = city.get_building(bid)
    if (b.play_animation) {
        __log_info_native('[test:29] FAIL: handler left play_animation=true with 0 workers')
        __test_signal_ready()
        return
    }
    __log_marker('test29_handler_stops_low_workers')

    // --- integration: day tick with workers, empty straw ---
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
        __log_info_native('[test:29] FAIL: day tick left play_animation=true without straw')
        __test_signal_ready()
        return
    }
    __log_marker('test29_day_tick_stops_without_straw')

    __test29_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test29_ok
        && __test_find_inlog('[test-marker] test29_handler_stops_without_straw')
        && __test_find_inlog('[test-marker] test29_handler_keeps_with_straw')
        && __test_find_inlog('[test-marker] test29_handler_stops_low_workers')
        && __test_find_inlog('[test-marker] test29_day_tick_stops_without_straw')
}

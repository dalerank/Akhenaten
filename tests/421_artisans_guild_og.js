// Artisans guild vs OG:
// - construction_warning_check_artisans: no clay or paint in the city â†’ needs clay and paint
//   (+ the clay pit hint when clay can be produced); clay and paint in a storage yard â†’ no warning;
// - window_building_draw_artisans_guild state line: no workers 312.2, no paint 312.8,
//   no clay 312.9, full staff 312.3 (any stock above zero counts);
// - Pharaoh_Model row 231: 15 workers on very easy, 20 otherwise.
// Markers:
//   [test-marker] t421_warnings_ok
//   [test-marker] t421_info_ok
//   [test-marker] t421_model_ok

var __t421_ok = false

var NEEDS = '#building_needs_clay_and_paint'
var CLAY_PIT = '#build_clay_pit'

function t421_fail(msg) {
    __log_info_native('[test:421] FAIL: ' + msg)
    __test_signal_ready()
}

function t421_place() {
    __test_construction_warnings_reset()
    var bid = test_building_place(BUILDING_ARTISANS_GUILD, -1, -1)
    __test_process_events()
    return bid
}

function t421_state_text(bid) {
    __test_show_tile_info(bid)
    __test_pump_frames(5)
    var text = __test_info_ui_text('warning_text')
    window_go_back()
    __test_pump_frames(2)
    return text
}

function t421_staff(bid, workers) {
    var b = city.get_building(bid)
    b.has_road_access = true
    b.num_workers = workers
    return b
}

function run_test() {
    __log_info_native('[test:421] artisans guild OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(100000)
    if (!__scenario_building_allowed(BUILDING_ARTISANS_GUILD)) {
        __scenario_building_allow(BUILDING_ARTISANS_GUILD, true)
    }

    var bid = t421_place()
    if (!bid) {
        return t421_fail('place without supply')
    }
    if (__test_construction_warning_count(NEEDS) != 1) {
        return t421_fail('expected ' + NEEDS + ' got ' + __test_construction_warning_count(NEEDS))
    }
    var clay_pit = __test_construction_warning_count(CLAY_PIT)
    if (city.resources.clay.can_produce ? clay_pit != 1 : clay_pit != 0) {
        return t421_fail('clay pit hint ' + clay_pit + ' can_produce=' + city.resources.clay.can_produce)
    }

    var b = t421_staff(bid, 0)
    var texts = []
    texts.push([t421_state_text(bid), __loc({group: 312, id: 2})])
    b = t421_staff(bid, b.max_workers)
    b.consume_resource(RESOURCE_PAINT, b.stored_resource(RESOURCE_PAINT))
    b.consume_resource(RESOURCE_CLAY, b.stored_resource(RESOURCE_CLAY))
    texts.push([t421_state_text(bid), __loc({group: 312, id: 8})])
    b = t421_staff(bid, b.max_workers)
    b.consume_resource(RESOURCE_PAINT, -50)
    texts.push([t421_state_text(bid), __loc({group: 312, id: 9})])
    b = t421_staff(bid, b.max_workers)
    b.consume_resource(RESOURCE_CLAY, -50)
    texts.push([t421_state_text(bid), __loc({group: 312, id: 3})])
    for (var i = 0; i < texts.length; i++) {
        if (!texts[i][0] || texts[i][0] != texts[i][1]) {
            return t421_fail('state ' + i + ': "' + texts[i][0] + '" want "' + texts[i][1] + '"')
        }
    }
    __log_marker('t421_info_ok')

    var max_workers = city.get_building(bid).max_workers
    var want = (game.difficulty == 0) ? 15 : 20
    if (max_workers != want) {
        return t421_fail('max_workers ' + max_workers + ' want ' + want + ' difficulty=' + game.difficulty)
    }
    __log_marker('t421_model_ok')

    if (!__scenario_building_allowed(BUILDING_STORAGE_YARD)) {
        __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    }
    var yard = __test_building_create(BUILDING_STORAGE_YARD, -1, -1)
    if (!yard || !__test_storage_yard_add_resource(yard, RESOURCE_CLAY, 100)
            || !__test_storage_yard_add_resource(yard, RESOURCE_PAINT, 100)) {
        return t421_fail('could not stock clay and paint in a storage yard')
    }
    var bid2 = t421_place()
    if (!bid2 || __test_construction_warning_count(NEEDS) != 0 || __test_construction_warning_count(CLAY_PIT) != 0) {
        return t421_fail('supplied city still warns needs=' + __test_construction_warning_count(NEEDS))
    }
    __log_marker('t421_warnings_ok')

    __t421_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __t421_ok
        && __test_find_inlog('[test-marker] t421_warnings_ok')
        && __test_find_inlog('[test-marker] t421_info_ok')
        && __test_find_inlog('[test-marker] t421_model_ok')
}

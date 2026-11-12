// OG building_menu.c: the paint maker button is enabled only while paint can be produced potentially
// (empire_can_produce_resource_potentially(RESOURCE_PAINT): henna can be farmed or imported from any
// trade city, or our city makes paint).

var __test389_ok = false

function test389_fail(msg) {
    __log_info_native('[test:389] FAIL: ' + msg)
    __test_signal_ready()
}

function test389_menu_enabled() {
    __scenario_building_allow(BUILDING_PAINT_WORKSHOP, true)
    building_menu_ctrl.update("stage_normal")
    return building_menu_ctrl.is_enabled(BUILDING_PAINT_WORKSHOP)
}

function run_test() {
    __log_info_native('[test:389] paint workshop menu gate')
    test_reload_city_session('data/default.map')

    var henna_prev = __city_can_produce_resource(RESOURCE_HENNA)
    var paint_prev = __city_can_produce_resource(RESOURCE_PAINT)

    __city_resource_set_produce(RESOURCE_HENNA, true)
    __city_resource_set_produce(RESOURCE_PAINT, false)
    if (!test389_menu_enabled()) {
        test389_fail('henna farms possible must enable the paint maker')
        return
    }
    __log_marker('test389_henna_enables_ok')

    __city_resource_set_produce(RESOURCE_HENNA, false)
    var importable = __city_resource_can_import(RESOURCE_HENNA, false)
    if (test389_menu_enabled() != importable) {
        test389_fail('without henna farms the menu must follow henna imports=' + importable)
        return
    }
    __log_marker('test389_no_henna_ok')

    __city_resource_set_produce(RESOURCE_PAINT, true)
    if (!test389_menu_enabled()) {
        test389_fail('our city making paint must enable the paint maker')
        return
    }
    __log_marker('test389_paint_enables_ok')

    __city_resource_set_produce(RESOURCE_HENNA, henna_prev)
    __city_resource_set_produce(RESOURCE_PAINT, paint_prev)
    __scenario_building_allow(BUILDING_PAINT_WORKSHOP, true)
    building_menu_ctrl.update("stage_normal")
    __test389_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test389_ok
        && __test_find_inlog('[test-marker] test389_henna_enables_ok')
        && __test_find_inlog('[test-marker] test389_no_henna_ok')
        && __test_find_inlog('[test-marker] test389_paint_enables_ok')
}

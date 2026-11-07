// OG DELIVERED (29): after delivered_wait_ticks return to IDLE pool (8).

function test282_fail(msg) {
    __log_info_native('[test:282] ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:282] laborer DELIVERED → IDLE')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_WORK_CAMP)) {
        __scenario_building_allow(BUILDING_WORK_CAMP, true)
    }

    __test_set_treasury(500000)
    var camp = test_building_place(BUILDING_WORK_CAMP, -1, -1)
    if (!camp) {
        return test282_fail('place work camp failed')
    }
    var tile = __building_tile(camp)
    var fid = __test_figure_create(FIGURE_LABORER, tile.x, tile.y)
    if (!fid) {
        return test282_fail('create laborer failed')
    }
    __test_figure_set_home_slot(fid, camp)

    __test_figure_set_action(fid, 29)
    __test_figure_set_wait_ticks(fid, 100)
    __test_figure_action_perform(fid)

    var act = __test_figure_get_action(fid) | 0
    if (act != 8) {
        return test282_fail('DELIVERED→IDLE want 8 got ' + act)
    }
    __log_marker('laborer_delivered_idle_ok')
    __test_signal_ready()
}

function check_valid() {
    return __test_find_inlog('[test-marker] laborer_delivered_idle_ok')
}

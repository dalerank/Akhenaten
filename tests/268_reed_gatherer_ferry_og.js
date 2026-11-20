// OG reed gatherer ferry states (animals.c figure_reed_gatherer_action): waits for the
// ferry boat (7), rides it as a ghost (6), back to find-reeds after 100 ticks unqueued.

var __test268_ok = false

function test268_fail(msg) {
    __log_info_native('[test:268] FAIL: ' + msg)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:268] reed gatherer ferry OG')
    test_reload_city_session('data/default.map')
    __test_set_treasury(10000)

    var bid = test_building_place(BUILDING_REED_GATHERER, -1, -1)
    if (!bid) {
        bid = __test_building_create(BUILDING_REED_GATHERER, -1, -1)
    }
    if (!bid) {
        return test268_fail('reed gatherer place/create failed')
    }
    var t = __building_tile(bid)
    var fid = test_figure_create(FIGURE_REED_GATHERER, t.x + 2, t.y)
    if (!fid) {
        return test268_fail('create reed gatherer failed')
    }
    test_figure_set_home(fid, bid)

    var acts = [0, 1, 2].map(function (k) { return __test_figure_ferry_action(fid, k) }).join(',')
    if (acts != '7,6,8') {
        return test268_fail('ferry actions wait,ride,reroute expected 7,6,8 got ' + acts)
    }
    __log_marker('test268_actions_ok')

    __test_figure_set_action(fid, 6)
    __test_figure_action_perform(fid)
    if (__test_figure_is_visible(fid) != 0 || __test_figure_get_action(fid) != 6) {
        return test268_fail('on ferry must be a ghost, visible=' + __test_figure_is_visible(fid)
            + ' action=' + __test_figure_get_action(fid))
    }
    __log_marker('test268_ride_ghost_ok')

    __test_figure_set_action(fid, 7)
    __test_figure_set_wait_ticks(fid, 99)
    __test_figure_action_perform(fid)
    if (__test_figure_get_action(fid) != 7) {
        return test268_fail('wait must hold up to 100 ticks, action=' + __test_figure_get_action(fid))
    }
    __test_figure_action_perform(fid)
    if (__test_figure_get_action(fid) != 8 || __test_figure_is_visible(fid) != 1) {
        return test268_fail('unqueued wait must return to find-reeds visible, action=' + __test_figure_get_action(fid)
            + ' visible=' + __test_figure_is_visible(fid))
    }
    __log_marker('test268_wait_timeout_ok')

    __test268_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test268_ok
        && __test_find_inlog('[test-marker] test268_actions_ok')
        && __test_find_inlog('[test-marker] test268_ride_ghost_ok')
        && __test_find_inlog('[test-marker] test268_wait_timeout_ok')
}

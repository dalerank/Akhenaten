// A tower sentry request from one game must not survive loading another one.

var __test520_ok = false

function test520_fail(reason) {
    __log_marker('tower_sentry_request_reset_fail:' + reason)
    __test_signal_ready()
}

function run_test() {
    __log_info_native('[test:520] tower sentry request is reset on load')
    test_ensure_city_session('data/default.map')

    __test_tower_sentry_request_clear()
    __test_save_memory('t791')
    __test_barracks_request_tower_sentry()
    if (!__building_barracks_has_tower_sentry_request()) {
        return test520_fail('request_not_set')
    }

    __test_load_memory('t791')
    var left = __building_barracks_has_tower_sentry_request()
    __log_info_native('[test:520] request after load=' + left)
    if (left) {
        return test520_fail('request_survived_load')
    }

    __log_marker('tower_sentry_request_reset_ok')
    __test520_ok = true
    __test_signal_ready()
}

function check_valid() {
    return __test520_ok && __test_find_inlog('[test-marker] tower_sentry_request_reset_ok')
}

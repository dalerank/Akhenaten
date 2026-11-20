// Burial provisions: set requirements, stock a yard, partial + full dispatch,
// complete() gate.

function run_test() {
    __log_info_native('[test:413] burial provisions dispatch')
    test_ensure_city_session('data/default.map')

    if (!__scenario_building_allowed(BUILDING_STORAGE_YARD)) {
        __scenario_building_allow(BUILDING_STORAGE_YARD, true)
    }
    __test_set_treasury(500000)

    __test_burial_provisions_clear()
    if (!__test_burial_provisions_set(RESOURCE_LINEN, 8)) {
        __log_info_native('[test:413] set linen failed')
        __test_signal_ready()
        return
    }
    if (!__test_burial_provisions_set(RESOURCE_LIMESTONE, 32)) {
        __log_info_native('[test:413] set limestone failed')
        __test_signal_ready()
        return
    }

    if (__scenario_burial_provisions_count() !== 2) {
        __log_info_native('[test:413] expected 2 provisions, got ' + __scenario_burial_provisions_count())
        __test_signal_ready()
        return
    }
    if (__scenario_burial_provisions_complete()) {
        __log_info_native('[test:413] complete() true before dispatch')
        __test_signal_ready()
        return
    }
    __log_marker('burial_setup_ok')

    // Empty city â†’ not enough goods
    var empty = __scenario_burial_provisions_dispatch(RESOURCE_LINEN, 4)
    if (empty !== -1) {
        __log_info_native('[test:413] expected -1 empty yards, got ' + empty)
        __test_signal_ready()
        return
    }
    __log_marker('burial_empty_reject_ok')

    var sy = test_staffed_yard_with_resource(RESOURCE_LINEN, 8, -1, -1)
    if (!sy) {
        __log_info_native('[test:413] yard linen failed')
        __test_signal_ready()
        return
    }
    // Limestone in same or another yard
    if (!__test_storage_yard_add_resource(sy, RESOURCE_LIMESTONE, 32)) {
        var sy2 = test_staffed_yard_with_resource(RESOURCE_LIMESTONE, 32, -1, -1)
        if (!sy2) {
            __log_info_native('[test:413] yard limestone failed')
            __test_signal_ready()
            return
        }
    }

    // Partial linen
    var part = __scenario_burial_provisions_dispatch(RESOURCE_LINEN, 3)
    if (part !== 3) {
        __log_info_native('[test:413] partial dispatch expected 3, got ' + part)
        __test_signal_ready()
        return
    }
    if (__scenario_burial_provisions_dispatched(RESOURCE_LINEN) !== 3) {
        __log_info_native('[test:413] dispatched linen != 3')
        __test_signal_ready()
        return
    }
    if (__scenario_burial_provisions_remaining(RESOURCE_LINEN) !== 5) {
        __log_info_native('[test:413] remaining linen != 5')
        __test_signal_ready()
        return
    }
    __log_marker('burial_partial_ok')

    // Finish linen + limestone
    var rest = __scenario_burial_provisions_dispatch(RESOURCE_LINEN, 100)
    if (rest !== 5) {
        __log_info_native('[test:413] rest linen expected 5, got ' + rest)
        __test_signal_ready()
        return
    }
    var lim = __scenario_burial_provisions_dispatch(RESOURCE_LIMESTONE, 32)
    if (lim !== 32) {
        __log_info_native('[test:413] limestone dispatch expected 32, got ' + lim)
        __test_signal_ready()
        return
    }

    if (!__scenario_burial_provisions_complete()) {
        __log_info_native('[test:413] complete() false after full dispatch')
        __test_signal_ready()
        return
    }

    // Already done
    var again = __scenario_burial_provisions_dispatch(RESOURCE_LINEN, 1)
    if (again !== -2) {
        __log_info_native('[test:413] expected -2 all done, got ' + again)
        __test_signal_ready()
        return
    }
    __log_marker('burial_complete_ok')

    __test_burial_provisions_clear()
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'burial_setup_ok',
        'burial_empty_reject_ok',
        'burial_partial_ok',
        'burial_complete_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:413] missing marker: ' + marker)
            return false
        }
    }
    return true
}

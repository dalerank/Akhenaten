// Verifies enemy transports resolve to a registered figure class (E3b). Every
// FIGURE_ENEMY_*_TRANSPORT_SHIP (+ generic 92 / egyptian 101 / barbarian 115)
// must have a C++ class + FIGURE_METAINFO.
// Markers:
//   [test-marker] transport_control_registered_ok
//   [test-marker] transport_hittite_registered_ok
//   [test-marker] transport_generic_registered_ok
//   [test-marker] transport_all_registered_ok

function run_test() {
    __log_info_native('[test:100] enemy transport registration (E3b)')
    test_ensure_city_session('data/default.map')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_HYKSOS_SWORDMAN)) {
        __log_info_native('[test:100] control failed: FIGURE_ENEMY_HYKSOS_SWORDMAN not registered')
        __test_signal_ready()
        return
    }
    __log_marker('transport_control_registered_ok')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_HITTITE_TRANSPORT_SHIP)) {
        __log_info_native('[test:100] FIGURE_ENEMY_HITTITE_TRANSPORT_SHIP not registered')
        __test_signal_ready()
        return
    }
    __log_marker('transport_hittite_registered_ok')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_TRANSPORT)) {
        __log_info_native('[test:100] FIGURE_ENEMY_TRANSPORT not registered')
        __test_signal_ready()
        return
    }
    __log_marker('transport_generic_registered_ok')

    var transports = [
        FIGURE_ENEMY_TRANSPORT,
        FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_BARBARIAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_ASSYRIAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_CANAANITE_TRANSPORT_SHIP,
        FIGURE_ENEMY_HITTITE_TRANSPORT_SHIP,
        FIGURE_ENEMY_HYKSOS_TRANSPORT_SHIP,
        FIGURE_ENEMY_KUSHITE_TRANSPORT_SHIP,
        FIGURE_ENEMY_LIBIAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_NUBIAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_PERSIAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_PHOENICIAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_ROMAN_TRANSPORT_SHIP,
        FIGURE_ENEMY_SEAPEOPLE_TRANSPORT_SHIP
    ]
    for (var i = 0; i < transports.length; i++) {
        if (!__test_enemy_figure_registered(transports[i])) {
            __log_info_native('[test:100] transport type not registered: ' + transports[i])
            __test_signal_ready()
            return
        }
    }
    __log_marker('transport_all_registered_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'transport_control_registered_ok',
        'transport_hittite_registered_ok',
        'transport_generic_registered_ok',
        'transport_all_registered_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:100] missing marker: ' + marker)
            return false
        }
    }
    return true
}

// Verifies enemy warships resolve to a registered figure class (E3a). Every
// FIGURE_ENEMY_*_WAR_SHIP (+ generic FIGURE_ENEMY_WARSHIP / egyptian galera)
// now has a C++ class + FIGURE_METAINFO
// (src/figuretype/figure_enemy_warship.h). Before E3a, spawning one fell through
// figure_impl::acquire to a base figure_impl (dcast_enemy == null; assert(false)
// in debug).
// Markers:
//   [test-marker] warship_control_registered_ok
//   [test-marker] warship_hittite_registered_ok
//   [test-marker] warship_generic_registered_ok
//   [test-marker] warship_all_registered_ok

function run_test() {
    __log_info_native('[test:53] enemy warship registration (E3a)')
    test_ensure_city_session('data/default.map')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_HYKSOS_SWORDMAN)) {
        __log_info_native('[test:53] control failed: FIGURE_ENEMY_HYKSOS_SWORDMAN not registered')
        __test_signal_ready()
        return
    }
    __log_marker('warship_control_registered_ok')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_HITTITE_WAR_SHIP)) {
        __log_info_native('[test:53] FIGURE_ENEMY_HITTITE_WAR_SHIP not registered')
        __test_signal_ready()
        return
    }
    __log_marker('warship_hittite_registered_ok')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_WARSHIP)) {
        __log_info_native('[test:53] FIGURE_ENEMY_WARSHIP not registered')
        __test_signal_ready()
        return
    }
    __log_marker('warship_generic_registered_ok')

    var warships = [
        FIGURE_ENEMY_WARSHIP,
        FIGURE_ENEMY_ASSYRIAN_WAR_SHIP,
        FIGURE_ENEMY_CANAANITE_WAR_SHIP,
        FIGURE_ENEMY_EGYPTIAN_GALERA,
        FIGURE_ENEMY_EGYPTIAN_WARSHIP,
        FIGURE_ENEMY_HITTITE_WAR_SHIP,
        FIGURE_ENEMY_HYKSOS_WAR_SHIP,
        FIGURE_ENEMY_KUSHITE_WAR_SHIP,
        FIGURE_ENEMY_LIBIAN_WAR_SHIP,
        FIGURE_ENEMY_NUBIAN_WAR_SHIP,
        FIGURE_ENEMY_PERSIAN_WAR_SHIP,
        FIGURE_ENEMY_PHOENICIAN_WAR_SHIP,
        FIGURE_ENEMY_ROMAN_WAR_SHIP,
        FIGURE_ENEMY_SEAPEOPLE_WAR_SHIP
    ]
    for (var i = 0; i < warships.length; i++) {
        if (!__test_enemy_figure_registered(warships[i])) {
            __log_info_native('[test:53] warship type not registered: ' + warships[i])
            __test_signal_ready()
            return
        }
    }
    __log_marker('warship_all_registered_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'warship_control_registered_ok',
        'warship_hittite_registered_ok',
        'warship_generic_registered_ok',
        'warship_all_registered_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:53] missing marker: ' + marker)
            return false
        }
    }
    return true
}

// Verifies enemy chariots resolve to a registered figure class (F2). Every
// FIGURE_ENEMY_*_CHARIOT now has a C++ class + FIGURE_METAINFO
// (src/figuretype/figure_enemy_chariot.h). Before F2, spawning one fell through
// figure_impl::acquire to a base figure_impl (dcast_enemy == null; assert(false)
// in debug), so __test_enemy_figure_registered() returned false. Assyrian and
// Hyksos armies actually field chariots (enemies.js type3 = 10%), which blocked
// missions 32/33.
// Markers:
//   [test-marker] chariot_control_registered_ok
//   [test-marker] chariot_hyksos_registered_ok
//   [test-marker] chariot_assyrian_registered_ok
//   [test-marker] chariot_all_registered_ok

function run_test() {
    __log_info_native('[test:39] enemy chariot registration (F2)')
    test_ensure_city_session('data/default.map')

    // Positive control: a long-registered enemy melee class must report true, so
    // a false below is a real registration gap, not a broken test harness.
    if (!__test_enemy_figure_registered(FIGURE_ENEMY_HYKSOS_SWORDMAN)) {
        __log_info_native('[test:39] control failed: FIGURE_ENEMY_HYKSOS_SWORDMAN not registered')
        __test_signal_ready()
        return
    }
    __log_marker('chariot_control_registered_ok')

    // The two nations whose armies actually spawn chariots (blocked missions 32/33).
    if (!__test_enemy_figure_registered(FIGURE_ENEMY_HYKSOS_CHARIOT)) {
        __log_info_native('[test:39] FIGURE_ENEMY_HYKSOS_CHARIOT not registered')
        __test_signal_ready()
        return
    }
    __log_marker('chariot_hyksos_registered_ok')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_ASSYRIAN_CHARIOT)) {
        __log_info_native('[test:39] FIGURE_ENEMY_ASSYRIAN_CHARIOT not registered')
        __test_signal_ready()
        return
    }
    __log_marker('chariot_assyrian_registered_ok')

    // The whole family must resolve to a class so no nation's chariot asserts.
    var chariots = [
        FIGURE_ENEMY_EGYPTIAN_CHARIOT,
        FIGURE_ENEMY_CANAANITE_CHARIOT,
        FIGURE_ENEMY_KUSHITE_CHARIOT,
        FIGURE_ENEMY_HITTITE_CHARIOT,
        FIGURE_ENEMY_PERSIAN_CHARIOT,
        FIGURE_ENEMY_ASSYRIAN_CHARIOT,
        FIGURE_ENEMY_LIBIAN_CHARIOT,
        FIGURE_ENEMY_NUBIAN_CHARIOT,
        FIGURE_ENEMY_PHOENICIAN_CHARIOT,
        FIGURE_ENEMY_ROMAN_CHARIOT,
        FIGURE_ENEMY_SEAPEOPLE_CHARIOT,
        FIGURE_ENEMY_HYKSOS_CHARIOT
    ]
    for (var i = 0; i < chariots.length; i++) {
        if (!__test_enemy_figure_registered(chariots[i])) {
            __log_info_native('[test:39] chariot type not registered: ' + chariots[i])
            __test_signal_ready()
            return
        }
    }
    __log_marker('chariot_all_registered_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'chariot_control_registered_ok',
        'chariot_hyksos_registered_ok',
        'chariot_assyrian_registered_ok',
        'chariot_all_registered_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:39] missing marker: ' + marker)
            return false
        }
    }
    return true
}

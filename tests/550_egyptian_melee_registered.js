// Egyptian melee specials resolve to registered figure classes.
// FIGURE_ENEMY_EGYPTIAN_{FAST_SWORD,SWORD,HEAVY_SWORD,AXE} (45/49/50/53) now
// have FIGURE_METAINFO leaves of figure_enemy_fast_sword
// (src/figuretype/figure_enemy_fast_sword.h). They are not in
// enemy_egyptian.figure_types[] (still archer/spear/chariot); registration
// prevents assert(false) if a mission/console/save spawns them.
// Markers:
//   [test-marker] egyptian_melee_control_registered_ok
//   [test-marker] egyptian_melee_fast_sword_ok
//   [test-marker] egyptian_melee_sword_ok
//   [test-marker] egyptian_melee_heavy_sword_ok
//   [test-marker] egyptian_melee_axe_ok
//   [test-marker] egyptian_melee_all_registered_ok

function run_test() {
    __log_info_native('[test:550] egyptian melee registration (ES2)')
    test_ensure_city_session('data/default.map')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_SPEAR)) {
        __log_info_native('[test:550] control failed: FIGURE_ENEMY_EGYPTIAN_SPEAR not registered')
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_melee_control_registered_ok')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_FAST_SWORD)) {
        __log_info_native('[test:550] FIGURE_ENEMY_EGYPTIAN_FAST_SWORD not registered')
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_melee_fast_sword_ok')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_SWORD)) {
        __log_info_native('[test:550] FIGURE_ENEMY_EGYPTIAN_SWORD not registered')
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_melee_sword_ok')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_HEAVY_SWORD)) {
        __log_info_native('[test:550] FIGURE_ENEMY_EGYPTIAN_HEAVY_SWORD not registered')
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_melee_heavy_sword_ok')

    if (!__test_enemy_figure_registered(FIGURE_ENEMY_EGYPTIAN_AXE)) {
        __log_info_native('[test:550] FIGURE_ENEMY_EGYPTIAN_AXE not registered')
        __test_signal_ready()
        return
    }
    __log_marker('egyptian_melee_axe_ok')
    __log_marker('egyptian_melee_all_registered_ok')

    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'egyptian_melee_control_registered_ok',
        'egyptian_melee_fast_sword_ok',
        'egyptian_melee_sword_ok',
        'egyptian_melee_heavy_sword_ok',
        'egyptian_melee_axe_ok',
        'egyptian_melee_all_registered_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:550] missing marker: ' + marker)
            return false
        }
    }
    return true
}

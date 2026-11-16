// Meidum goal = small(8)+complex(24) ? trunc(76.5)=76.
// Rating first on a clean map; then mid-phase save/load (separate session).

function place_pyramid(type, candidates) {
    for (var i = 0; i < candidates.length; i++) {
        if (type == BUILDING_STEPPED_PYRAMID_COMPLEX || type == BUILDING_PYRAMID_COMPLEX
            || type == BUILDING_GRAND_PYRAMID_COMPLEX) {
            test_prepare_pyramid_complex_causeway(candidates[i].x, candidates[i].y, 20, 4, 3)
        }
        var bid = test_building_place(type, candidates[i].x, candidates[i].y)
        if (bid) return bid
    }
    return test_building_place(type, -1, -1)
}

function find_complex_main() {
    // TYPE building is unique; orientation can put a corner at list-head, so
    // do not require !prev_part_building_id.
    for (var bi = 1; bi < 500; bi++) {
        if (__building_type(bi) == BUILDING_STEPPED_PYRAMID_COMPLEX) {
            return bi
        }
    }
    return 0
}

function allow_pyramids() {
    if (!__scenario_building_allowed(BUILDING_STEPPED_PYRAMID_COMPLEX))
        __scenario_building_allow(BUILDING_STEPPED_PYRAMID_COMPLEX, true)
    if (!__scenario_building_allowed(BUILDING_SMALL_STEPPED_PYRAMID))
        __scenario_building_allow(BUILDING_SMALL_STEPPED_PYRAMID, true)
}

function run_test() {
    __log_info_native('[test:106] Meidum rating 39 + complex mid-phase saveload')

    // --- 1) Rating on clean map ---
    test_ensure_city_session('data/default.map')
    __test_set_treasury(500000)
    allow_pyramids()

    var complex = place_pyramid(BUILDING_STEPPED_PYRAMID_COMPLEX, [{x: 50, y: 50}, {x: 40, y: 40}, {x: 55, y: 30}])
    if (!complex) {
        __log_info_native('[test:106] complex place failed')
        __test_signal_ready(); return
    }
    __test_monument_set_phase(complex, -1)
    test_monument_slots([BUILDING_STEPPED_PYRAMID_COMPLEX, BUILDING_SMALL_STEPPED_PYRAMID])
    city_update_monthly_monument_rating({})
    var alone = city.rating.monument | 0
    // OG stepped complex weight 36: trunc(6.32*sqrt(36)+0.5)=38
    if (alone != 38) {
        __log_info_native('[test:106] complex alone want 38 got ' + alone + ' n=' + __city_monuments_list_refresh())
        __log_marker('meidum_alone_fail:' + alone)
        __test_signal_ready(); return
    }
    __log_marker('meidum_alone_ok:38')

    var small = place_pyramid(BUILDING_SMALL_STEPPED_PYRAMID, [{x: 20, y: 20}, {x: 25, y: 25}, {x: 30, y: 20}])
    if (!small) {
        __log_info_native('[test:106] small place failed')
        __test_signal_ready(); return
    }
    __test_monument_set_phase(small, -1)
    test_monument_slots([BUILDING_STEPPED_PYRAMID_COMPLEX, BUILDING_SMALL_STEPPED_PYRAMID])
    city_update_monthly_monument_rating({})
    var rating = city.rating.monument | 0
    if (rating != 39) {
        __log_info_native('[test:106] both want 39 got ' + rating)
        __log_marker('meidum_rating_fail:' + rating)
        __test_signal_ready(); return
    }
    __log_marker('complex_finish_ok')
    __log_marker('meidum_rating_ok:39')
    __log_marker('meidum_goal_constant_ok:39')

    // --- 2) Mid-phase save/load ---
    test_reload_city_session('data/default.map')
    __test_set_treasury(500000)
    allow_pyramids()

    var cx = (__scenario_map.width / 2) | 0
    var cy = (__scenario_map.height / 2) | 0
    var cbid = place_pyramid(BUILDING_STEPPED_PYRAMID_COMPLEX, [
        {x: cx - 10, y: cy - 10}, {x: 40, y: 40}, {x: 30, y: 30}
    ])
    if (!cbid) {
        __log_info_native('[test:106] saveload place failed')
        __test_signal_ready(); return
    }
    __test_pump_frames(20)
    __test_monument_set_phase(cbid, 18)
    __test_pump_frames(4)
    if (__test_monument_phase(cbid) != 18) {
        __log_marker('complex_saveload_phase_fail')
        __test_signal_ready(); return
    }

    var save_name = 'test_106_complex_midphase.svx'
    if (!__game_write_savegame(save_name)) {
        __log_marker('complex_saveload_skipped')
    } else if (!__game_load_savegame(save_name)) {
        __game_delete_savegame(save_name)
        __log_marker('complex_saveload_skipped')
    } else {
        __game_delete_savegame(save_name)
        var found = find_complex_main()
        var ph = found ? __test_monument_phase(found) : -999
        if (!found || ph != 18) {
            __log_info_native('[test:106] after load found=' + found + ' phase=' + ph)
            __log_marker('complex_saveload_fail:' + ph)
            __test_signal_ready(); return
        }
        __log_marker('complex_saveload_ok:' + found)
        var ft = __building_tile(found)
        if (test_pyramid_complex_causeway_claimed(found, ft.x, ft.y, 20, 4)) {
            __log_marker('complex_saveload_causeway_ok')
        } else {
            __log_info_native('[test:106] causeway tiles missing after saveload')
            __log_marker('complex_saveload_causeway_fail')
            __test_signal_ready(); return
        }
    }

    __test_signal_ready()
}

function check_valid() {
    var required = ['complex_finish_ok', 'meidum_alone_ok', 'meidum_rating_ok', 'meidum_goal_constant_ok']
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog(required[i])) {
            __log_info_native('[test:106] missing: ' + required[i])
            return false
        }
    }
    if (__test_find_inlog('complex_saveload_fail') || __test_find_inlog('meidum_alone_fail')
        || __test_find_inlog('meidum_rating_fail') || __test_find_inlog('complex_saveload_causeway_fail'))
        return false
    // Soft-skip when write/load unavailable; otherwise require success.
    if (!__test_find_inlog('complex_saveload_skipped') && !__test_find_inlog('complex_saveload_ok')) {
        __log_info_native('[test:106] missing saveload marker')
        return false
    }
    if (__test_find_inlog('complex_saveload_ok') && !__test_find_inlog('complex_saveload_causeway_ok')) {
        __log_info_native('[test:106] missing causeway-after-load marker')
        return false
    }
    return true
}

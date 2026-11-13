// Alexandria's Library on custom mission 128 (Alexandria.map sandbox).
// Prefer Maps/Alexandria.map (Cleopatra); if place fails / map missing → default.map.

function run_test() {
    __log_info_native('[test:124] alexandria library m_128 place + finish')

    var cfg = get_mission_config(128)
    if (!cfg) {
        __log_info_native('[test:124] no mission 128 config')
        __test_signal_ready()
        return
    }

    var has_lib = false
    for (var b = 0; b < cfg.buildings.length; b++) {
        if (cfg.buildings[b] == BUILDING_ALEXANDRIA_LIBRARY) {
            has_lib = true
            break
        }
    }
    if (!has_lib) {
        __log_info_native('[test:124] mission 128 buildings[] missing LIBRARY')
        __test_signal_ready()
        return
    }
    __log_marker('alex_m128_cfg_ok')

    var used_m128_map = false
    if (__game_file_exists("Maps/Alexandria.map") && __game_load_map("Alexandria.map", 1)) {
        used_m128_map = true
        __log_marker('alex_m128_map_ok')
    } else {
        __log_marker('alex_m128_map_skipped')
        test_reload_city_session('data/default.map')
    }

    __test_process_events()
    __test_pump_frames(2)

    if (!__scenario_building_allowed(BUILDING_ALEXANDRIA_LIBRARY)) {
        __scenario_building_allow(BUILDING_ALEXANDRIA_LIBRARY, true)
    }
    if (!__scenario_building_allowed(BUILDING_ALEXANDRIA_LIBRARY)) {
        __log_info_native('[test:124] LIBRARY not allowed')
        __test_signal_ready()
        return
    }
    __log_marker('alex_m128_allowed_ok')

    __test_set_treasury(500000)

    function try_place() {
        var spots = [[80, 80], [60, 60], [40, 40], [100, 100], [30, 30], [120, 80]]
        for (var i = 0; i < spots.length; i++) {
            var bid = test_building_place(BUILDING_ALEXANDRIA_LIBRARY, spots[i][0], spots[i][1])
            if (bid) {
                return bid
            }
        }
        return 0
    }

    var bid = try_place()
    if (!bid && used_m128_map) {
        // Hermetic / no-resource: Alexandria.map may load but clear-land place fails.
        __log_marker('alex_m128_place_fallback_default')
        test_reload_city_session('data/default.map')
        __test_process_events()
        __test_pump_frames(2)
        if (!__scenario_building_allowed(BUILDING_ALEXANDRIA_LIBRARY)) {
            __scenario_building_allow(BUILDING_ALEXANDRIA_LIBRARY, true)
        }
        __test_set_treasury(500000)
        used_m128_map = false
        bid = try_place()
    }
    if (!bid) {
        __log_info_native('[test:124] failed to place LIBRARY')
        __test_signal_ready()
        return
    }
    __log_marker('alex_m128_placed_ok:' + bid)

    __test_alexandria_library_finish(bid)
    __test_process_events()
    __test_pump_frames(2)

    var ph = __test_monument_phase(bid)
    if (ph != 255 && ph != -1) {
        __log_info_native('[test:124] not finished after finish helper ph=' + ph)
        __test_signal_ready()
        return
    }
    __log_marker('alex_m128_finished_ok')

    test_monument_slots([BUILDING_ALEXANDRIA_LIBRARY])
    city_update_monthly_monument_rating({})
    var rating_done = city.rating.monument | 0
    // OG weight 12 → trunc(6.32*sqrt(12)+0.5)=22
    if (rating_done < 22) {
        __log_info_native('[test:124] finished rating want >=22 got ' + rating_done)
        __log_marker('alex_m128_rating_fail:' + rating_done)
        __test_signal_ready()
        return
    }
    __log_marker('alex_m128_rating_ok:' + rating_done)

    if (used_m128_map) {
        __log_marker('alex_m128_on_sandbox')
    }

    __log_info_native('[test:124] PASS')
    __log_marker('alex_m128_ok')
    __test_signal_ready()
}

function check_valid() {
    var required = [
        'alex_m128_cfg_ok',
        'alex_m128_allowed_ok',
        'alex_m128_placed_ok',
        'alex_m128_finished_ok',
        'alex_m128_rating_ok',
        'alex_m128_ok'
    ]
    for (var i = 0; i < required.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + required[i])
            && !__test_find_inlog(required[i])) {
            __log_info_native('[test:124] missing marker ' + required[i])
            return false
        }
    }
    if (!__test_find_inlog('[test-marker] alex_m128_map_ok')
        && !__test_find_inlog('alex_m128_map_ok')
        && !__test_find_inlog('[test-marker] alex_m128_map_skipped')
        && !__test_find_inlog('alex_m128_map_skipped')) {
        __log_info_native('[test:124] missing map ok/skipped marker')
        return false
    }
    return true
}
